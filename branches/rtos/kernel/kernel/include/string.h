#ifndef __STRING_H__
#define __STRING_H__

unsigned int strlen(const char *s);
unsigned int strnlen(const char *s, unsigned int count);
int strcmp(const char *cs, const char *ct);
char *strcat(char *dest, const char *src);
char *strcpy(char *dest, const char *src);
void *memset(void *s, int c, long count);
void *memcpy(void *dest, const void *src, long count);
int memcmp(const void * cs, const void * ct, long count);

#endif
