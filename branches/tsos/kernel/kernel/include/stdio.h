#ifndef	__STDIO_H__
#define __STDIO_H__

inline uint8_t getc();
void scanf(uint8_t *buf);

inline void putc(const char ch);
inline void puts(const char *str);
void printf(const char *buf, ...);
inline uint16_t atoi(const uint8_t *buf);
inline void printf_matrix(uint8_t col, uint32_t size, uint8_t *data);

#endif
