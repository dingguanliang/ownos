#ifndef __INTERRUPT_H__
#define	__INTERRUPT_H__

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

bool int_init(uint32_t int_type, void *svr_func);

#endif
