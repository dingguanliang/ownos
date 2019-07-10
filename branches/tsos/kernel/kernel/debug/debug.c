#include "../include/types.h"
#include "../include/own.h"
#include "../include/stdio.h"

void idle_tsk_debug_hook()
{
	puts("idle task running...\n\r");
}

void timer_svr_debug_hook()
{
	printf("timer_svr_debug_hook-system time:%d ms\n\r", OWN_GET_SYS_TIME());
}
