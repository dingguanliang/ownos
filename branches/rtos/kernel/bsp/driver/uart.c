#include "../../kernel/include/types.h"
#include "../../kernel/include/register.h"
#include "../../kernel/include/io.h"
#include "../../kernel/include/config.h"

typedef struct uart_regs{
	uint32_t ulcon;		// 0x00.
	uint32_t ucon;		// 0x04.
	uint32_t ufcon;		// 0x08.
	uint32_t umcon;		// 0x0c.
	uint32_t utrstat;	// 0x10.
	uint32_t uerstat;	// 0x14.
	uint32_t ufstat;	// 0x18.
	uint32_t umstat;	// 0x1c.
	uint32_t utxh;		// 0x20.
	uint32_t urxh;		// 0x24.
	uint32_t ubrdiv;	// 0x28.
}uart, *puart;

static puart uartx;

bool uart_init(uint32_t uartx_base, uint32_t baud, uint8_t im, uint8_t pm, uint8_t nosb, uint8_t wl)
{
	uint32_t tmp1, tmp2;
	uartx = (puart)uartx_base;
	
	// initial GPIO.
	tmp1 = READD(GPH_BASE+GPXCON_OFFSET);
	tmp2 = READD(GPH_BASE+GPXUP_OFFSET);
	switch((uartx_base >> 8) & 0xff)
	{
		case 0x00:
			tmp1 |= 0x0a << 4;
			tmp2 |= 0x03 << 2;
			break;
		case 0x40:
			tmp1 |= 0x0a << 8;
			tmp2 |= 0x03 << 4;
			break;
		case 0x80:
			tmp1 |= 0x0a << 12;
			tmp2 |= 0x03 << 6;
			break;
		default:
			return(FALSE);
	};
	WRITED(GPH_BASE+GPXCON_OFFSET, tmp1);
	WRITED(GPH_BASE+GPXUP_OFFSET, tmp2);

	// initial ULCONx register.
	WRITED(&uartx->ulcon, (wl << 0) | (nosb << 2) | (pm << 3) | (im << 6));

	// initial UCONx register.
	WRITED(&uartx->ucon, (1 << 9) | (1 << 6) | (1 << 2) | (1 << 0));

	// initial UBRDIVx register.
	WRITED(&uartx->ubrdiv, (uint16_t)(PCLK / (baud * 16)) - 1);
	
	return(TRUE);
}

bool uart_receive_c(uint8_t *ch)
{
	if((uartx->utrstat & BIT0) && (!uartx->uerstat))
	{
		*ch = uartx->urxh;
		return(TRUE);
	}
	
	return(FALSE);
}

bool uart_send_c(const uint8_t ch)
{
	if(uartx->utrstat & BIT1)
	{
		uartx->utxh = ch;
		return(TRUE);
	}
	
	return(FALSE);
}
