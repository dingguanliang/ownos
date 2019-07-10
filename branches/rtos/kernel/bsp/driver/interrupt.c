#include "../../kernel/include/types.h"
#include "../../kernel/include/register.h"
#include "../../kernel/include/io.h"

#define EINT0			0
#define EINT1			1
#define EINT2			2
#define EINT3			3
#define EINT4_7			4
#define EINT8_23		5
#define INT_CAM			6
#define NBATT_FLT		7
#define INT_TICK		8
#define INT_WDT_AC97	9
#define INT_TIMER0		10
#define INT_TIMER1		11
#define INT_TIMER2		12
#define INT_TIMER3		13
#define INT_TIMER4		14
#define INT_UART2		15
#define INT_LCD			16
#define INT_DMA0		17
#define INT_DMA1		18
#define INT_DMA2		19
#define INT_DMA3		20
#define INT_SDI			21
#define INT_SPI0		22
#define INT_UART1		23
#define INT_NFCON		24
#define INT_USBD		25
#define INT_USBH		26
#define INT_IIC			27
#define INT_UART0		28
#define INT_SPI1		29
#define INT_RTC			30
#define INT_ADC			31

#define EINT4			32
#define EINT5			33
#define EINT6			34
#define EINT7			35
#define EINT8			36
#define EINT9			37
#define EINT10			38
#define EINT11			39
#define EINT12			40
#define EINT13			41
#define EINT14			42
#define EINT15			43
#define EINT16			44
#define EINT17			45
#define EINT18			46
#define EINT19			47
#define EINT20			48
#define EINT21			49
#define EINT22			50
#define EINT23			51
#define INT_RXD0		52
#define INT_TXD0		53
#define INT_ERR0		54
#define INT_RXD1		55
#define INT_TXD1		56
#define INT_ERR1		57
#define INT_RXD2		58
#define INT_TXD2		59
#define INT_ERR2		60
#define INT_TC			61
#define INT_ADC_S		62
#define INT_CAM_C		63
#define INT_CAM_P		64
#define INT_WDT			65
#define INT_AC97		66

#define INT_NUM			(60 + 7)

#define BIT_READ(regs, shift)			(READD(regs) & (1 << (shift)))
#define BIT_SET_0(regs, shift)			(WRITED(regs, READD(regs) & ~(1 << (shift))))	
#define BIT_SET_1(regs, shift)			(WRITED(regs, READD(regs) | (1 << (shift))))	

#define OPEN_INT(int_shift)				BIT_SET_0(INTMSK, int_shift)
#define OPEN_SUB_INT(int_shift)			BIT_SET_0(INTSUBMSK, int_shift)
#define OPEN_EXT_INT(int_shift)			BIT_SET_0(EINTMASK, int_shift)

#define	SUB_INT_PND_CHECK(int_shift)	BIT_READ(SUBSRCPND, int_shift)
#define	EXT_INT_PND_CHECK(int_shift)	BIT_READ(EINTPEND, int_shift)

#define CLEAR_INT(int_shift)			BIT_SET_1(INTPND, int_shift)
#define CLEAR_SRC_INT(int_shift)		BIT_SET_1(SRCPND, int_shift)
#define CLEAR_SUB_SRC_INT(int_shift)	BIT_SET_1(SUBSRCPND, int_shift)
#define CLEAR_EXT_SRC_INT(int_shift)	BIT_SET_1(EINTPEND, int_shift)

#define INT_CONNECT(intx_handle, svr_func)	(int_svr_t[intx_handle] = (int_handle)svr_func)

typedef void (*int_handle)();
int_handle int_svr_t[INT_NUM];

void ext_svr();
void sub_svr();

bool int_init(uint32_t int_type, void *svr_func)
{
	// open irq int.
	asm volatile("mrs r0, cpsr");
	asm volatile("bic r0, #0x80");
	asm volatile("msr cpsr, r0");

	// change int mode.
	WRITED(INTMOD, 0x00);
	
	INT_CONNECT(EINT4_7, 		ext_svr);
	INT_CONNECT(EINT8_23, 		ext_svr);
	INT_CONNECT(INT_CAM, 		sub_svr);
	INT_CONNECT(INT_WDT_AC97,	sub_svr);
	INT_CONNECT(INT_UART2, 		sub_svr);
	INT_CONNECT(INT_UART1, 		sub_svr);
	INT_CONNECT(INT_UART0, 		sub_svr);
	INT_CONNECT(INT_ADC, 		sub_svr);

	if((int_type >= EINT0) && (int_type <= INT_ADC))
	{
		CLEAR_SRC_INT(int_type);
		CLEAR_INT(int_type);
		OPEN_INT(int_type);
		INT_CONNECT(int_type, svr_func);
	}
	else if((int_type >= EINT4) && (int_type <= EINT23))
	{
		CLEAR_EXT_SRC_INT(int_type - 28);
		if((int_type >= EINT4) && (int_type <= EINT7))
		{
			CLEAR_SRC_INT(EINT4_7);
			CLEAR_INT(EINT4_7);
			OPEN_INT(EINT4_7);
		}
		else if((int_type >= EINT8) && (int_type <= EINT23))
		{
			CLEAR_SRC_INT(EINT8_23);
			CLEAR_INT(EINT8_23);
			OPEN_INT(EINT8_23);
		}
		INT_CONNECT(int_type, svr_func);
		OPEN_EXT_INT(int_type - 28);
	}
	else if((int_type >= INT_RXD0) && (int_type <= INT_AC97))
	{
		CLEAR_SUB_SRC_INT(int_type - 52);
		if((int_type >= INT_RXD0) && (int_type <= INT_ERR0))
		{
			CLEAR_SRC_INT(INT_UART0);
			CLEAR_INT(INT_UART0);
			OPEN_INT(INT_UART0);
		}
		else if((int_type >= INT_RXD1) && (int_type <= INT_ERR1))
		{
			CLEAR_SRC_INT(INT_UART1);
			CLEAR_INT(INT_UART1);
			OPEN_INT(INT_UART1);
		}
		else if((int_type >= INT_RXD2) && (int_type <= INT_ERR2))
		{
			CLEAR_SRC_INT(INT_UART2);
			CLEAR_INT(INT_UART2);
			OPEN_INT(INT_UART2);
		}
		else if((int_type >= INT_TC) && (int_type <= INT_ADC_S))
		{
			CLEAR_SRC_INT(INT_ADC);
			CLEAR_INT(INT_ADC);
			OPEN_INT(INT_ADC);
		}
		else if((int_type >= INT_CAM_C) && (int_type <= INT_CAM_P))
		{
			CLEAR_SRC_INT(INT_CAM);
			CLEAR_INT(INT_CAM);
			OPEN_INT(INT_CAM);
		}
		else if((int_type >= INT_WDT) && (int_type <= INT_AC97))
		{
			CLEAR_SRC_INT(INT_WDT_AC97);
			CLEAR_INT(INT_WDT_AC97);
			OPEN_INT(INT_WDT_AC97);
		}
		INT_CONNECT(int_type, svr_func);
		OPEN_SUB_INT(int_type - 52);
	}
	else
		return(FALSE);
		
	return(TRUE);
}

void do_irq(uint32_t *regs)
{
	uint32_t tmp;

	tmp = READD(INTOFFSET);
	int_svr_t[tmp]();
	CLEAR_SRC_INT(tmp);
	CLEAR_INT(tmp);
}

void ext_svr()
{
	uint8_t i;

	for(i = 4; i <= 23; i++)
	{
		if(EXT_INT_PND_CHECK(i))
		{
			int_svr_t[i + 28]();
			CLEAR_EXT_SRC_INT(i);
		}	
	}
}

void sub_svr()
{
	uint8_t i;
	
	for(i = 0; i <= 14; i++)
	{
		if(SUB_INT_PND_CHECK(i))
		{
			int_svr_t[i + 52]();
			CLEAR_SUB_SRC_INT(i);
		}		
	}
}
