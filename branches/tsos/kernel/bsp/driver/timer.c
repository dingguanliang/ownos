#include "../../kernel/include/types.h"
#include "../../kernel/include/register.h"
#include "../../kernel/include/io.h"
#include "../../kernel/include/config.h"

#define LOAD_VAL(shift)	WRITED(TCON, 0x01 << shift)

typedef struct timer_regs{
	uint32_t tcntb;
	uint32_t tcmpb;
	uint32_t tcnto;
}timer, *ptimer;

static ptimer timerx;

bool timer_init(uint32_t timerx_base, uint8_t mode, uint8_t scale, uint32_t time, uint16_t cnt)
{
	uint8_t i;
	uint32_t pre, cmp_cnt, tmp1, tmp2, tmp3;
	const uint8_t div[4] = {2, 4, 8, 16};
	timerx = (ptimer)timerx_base;
	
	// calc pre and div.
	for(i = 0; i < 4; i++)
	{
		pre = (uint32_t)((time * (PCLK / 1000000)) / div[i]);
		if(pre > 256)
			continue;
		else if(pre < 1)
			return(FALSE);
		else 
			break;
	}
	
	cmp_cnt = (cnt * scale) / 100;
	WRITED(&timerx->tcntb, cnt);
	WRITED(&timerx->tcmpb, cmp_cnt);
	
	// register init.
	tmp1 = READD(TCFG0);
	tmp2 = READD(TCFG1);
	switch(timerx_base)
	{
		case TIMER0_BASE:
			tmp1 |= ((pre - 1) << 0);
			tmp2 = (tmp2 & ~(0x0f << 0)) | (i << 0);
			tmp3 = (0x01 << 0) | (mode << 3);
			LOAD_VAL(1);
			break;
		case TIMER1_BASE:
			tmp1 |= ((pre - 1) << 0);
			tmp2 = (tmp2 & ~(0x0f << 4)) | (i << 4);
			tmp3 = (0x01 << 8) | (mode << 11);
			LOAD_VAL(9);
			break;
		case TIMER2_BASE:
			tmp1 |= ((pre - 1) << 8);
			tmp2 = (tmp2 & ~(0x0f << 8)) | (i << 8);
			tmp3 = (0x01 << 12) | (mode << 15);
			LOAD_VAL(13);
			break;
		case TIMER3_BASE:
			tmp1 |= ((pre - 1) << 8);
			tmp2 = (tmp2 & ~(0x0f << 12)) | (i << 12);
			tmp3 = (0x01 << 16) | (mode << 19);
			LOAD_VAL(17);
			break;
		default:
			return(FALSE);
	};
	WRITED(TCFG0, tmp1);
	WRITED(TCFG1, tmp2);
	WRITED(TCON, tmp3);
	
	return(TRUE);
}

inline void timer_start(uint32_t timerx_base)
{
	switch(timerx_base)
	{
		case TIMER0_BASE:
			WRITED(TCON, READD(TCON) | (0x01 << 0));
			break;
		case TIMER1_BASE:
			WRITED(TCON, READD(TCON) | (0x01 << 8));
			break;
		case TIMER2_BASE:
			WRITED(TCON, READD(TCON) | (0x01 << 12));
			break;
		case TIMER3_BASE:
			WRITED(TCON, READD(TCON) | (0x01 << 16));
			break;
	};
}

inline void timer_stop(uint32_t timerx_base)
{
	switch(timerx_base)
	{
		case TIMER0_BASE:
			WRITED(TCON, READD(TCON) & ~(0x01 << 0));
			break;
		case TIMER1_BASE:
			WRITED(TCON, READD(TCON) & ~(0x01 << 8));
			break;
		case TIMER2_BASE:
			WRITED(TCON, READD(TCON) & ~(0x01 << 12));
			break;
		case TIMER3_BASE:
			WRITED(TCON, READD(TCON) & ~(0x01 << 16));
			break;
	};
}
