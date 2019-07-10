#ifndef __UART_H__
#define __UART_H__

#define NOMAL_MODE	0x00
#define IR_MODE		0x01

#define NP			0x00
#define OP			0x04
#define EP			0x05
#define PFCA1		0x06
#define PFCA0		0x07

#define OSB			0x00
#define TSB			0x01

#define _5BIT		0x00
#define _6BIT		0x01
#define _7BIT		0x02
#define _8BIT		0x03

bool uart_init(uint32_t uartx_base, uint32_t baud, uint8_t im, uint8_t pm, uint8_t nosb, uint8_t wl);
bool uart_receive_c(uint8_t *ch);
bool uart_send_c(const uint8_t ch);

#endif
