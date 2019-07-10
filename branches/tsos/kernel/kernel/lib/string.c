unsigned int strlen(const char *s)
{
	const char *sc;

	for(sc = s; *sc != '\0'; ++sc);
	
	return(sc - s);
}

unsigned int strnlen(const char *s, unsigned int count)
{
	const char *sc;

	for(sc = s; count-- && *sc != '\0'; ++sc);

	return(sc - s);
}

int strcmp(const char *cs, const char *ct)
{
	register signed char __res;

	while(1){
		if((__res = *cs - *ct++) != 0 || !*cs++)
			break;
	};

	return(__res);
}

char *strcat(char *dest, const char *src)
{
	char *tmp = dest;

	while(*dest)
		dest++;
	while((*dest++ = *src++) != '\0');

	return(tmp);
}

char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	while((*dest++ = *src++) != '\0');

	return(tmp);
}

void *memset(void *s, int c, long count)
{
	unsigned long *sl = (unsigned long *)s;
	unsigned long cl = 0;
	char *s8;
	int i;

	/* do it one word at a time (32 bits or 64 bits) while possible */
	if(((unsigned long)s & (sizeof(*sl) - 1)) == 0) 
	{
		for(i = 0; i < sizeof(*sl); i++) 
		{
			cl <<= 8;
			cl |= c & 0xff;
		}
		while(count >= sizeof(*sl))
		{
			*sl++ = cl;
			count -= sizeof(*sl);
		}
	}
	
	/* fill 8 bits at a time */
	s8 = (char *)sl;
	while(count--)
		*s8++ = c;

	return(s);
}

void *memcpy(void *dest, const void *src, long count)
{
	unsigned long *dl = (unsigned long *)dest, *sl = (unsigned long *)src;
	char *d8, *s8;

	/* while all data is aligned (common case), copy a word at a time */
	if((((unsigned long)dest | (unsigned long)src) & (sizeof(*dl) - 1)) == 0) 
	{
		while(count >= sizeof(*dl)) 
		{
			*dl++ = *sl++;
			count -= sizeof(*dl);
		}
	}
	
	/* copy the reset one byte at a time */
	d8 = (char *)dl;
	s8 = (char *)sl;
	while (count--)
		*d8++ = *s8++;

	return(dest);
}

int memcmp(const void * cs, const void * ct, long count)
{
	const unsigned char *su1, *su2;
	int res = 0;

	for(su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if((res = *su1 - *su2) != 0)
			break;
			
	return(res);
}
