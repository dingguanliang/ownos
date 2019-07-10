#include "../../kernel/kernel/include/types.h"
#include "../../kernel/kernel/include/register.h"
#include "../../kernel/kernel/include/include.h"
#include "../../kernel/kernel/include/debug.h"
#include "../../kernel/kernel/include/interrupt.h"
#include "../../kernel/kernel/include/timer.h"
#include "../../kernel/kernel/include/uart.h"

extern void own_tick();

void timer2_svr()
{
	#if 1 == TIMER_SVR_DEBUG
		timer_svr_debug_hook();
	#endif
	own_tick();   
}

void sys_con_init()
{
	while(!uart_init(UART0, 115200, NOMAL_MODE, NP, OSB, _8BIT));
}

void sys_tick_init()
{
	while(!int_init(INT_TIMER2, timer2_svr));
	while(!timer_init(TIMER2_BASE, AUTO_RELOAD, 0, 10, 100000 / SYS_TICK));
}
