#include "../include/types.h"
#include "../include/uart.h"

inline uint8_t getc()
{
	uint8_t ch;
	
	while(!uart_receive_c(&ch));
	
	return(ch);
}

void scanf(uint8_t *buf)
{
	uint8_t ch;
	
	while(1){
		ch = getc();
		if(0x0d != ch)
			*buf++ = ch;
		else{
			*buf = '\0';
			break;
		}
	};
}
