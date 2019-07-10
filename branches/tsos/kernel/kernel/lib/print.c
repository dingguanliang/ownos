#include "../include/types.h"
#include "../include/stdarg.h"
#include "../include/uart.h"

extern int vsprintf(char *buf, const char *fmt, va_list args);
extern unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base);

inline void putc(const char ch)
{
	while(!uart_send_c(ch));
}

inline void puts(const char *str)
{
	while('\0' != *str)
		putc(*str++);
}

void printf(const char *fmt, ...)
{
	va_list ap;
	char buf[128];
	uint16_t i;
	int j;
	
	va_start(ap, fmt);
	j = vsprintf(buf, fmt, ap);
	va_end(ap);
	
	for(i = 0; i < j; i++)
		putc(buf[i]);
}

inline uint16_t atoi(const uint8_t *buf)
{	
	return((uint16_t)simple_strtoul((const char *)buf, (char **)0, 0));
}

inline void printf_matrix(uint8_t col, uint32_t size, uint8_t *data)
{
	uint32_t i, j;

	for(i = 0; i < (size / col); i++)
	{
		for(j = 0; j < col; j++)
			printf("0x%2x	", data[(i * 16) + j]);
		puts("\n\r");
	}
}
