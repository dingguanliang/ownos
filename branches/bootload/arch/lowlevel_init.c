#include "../include/types.h"
#include "../include/register.h"
#include "../include/io.h"
#include "wdt_off.h"
#include "int_off.h"
#include "clock_init.h"
#include "mem_init.h"

void lowlevel_init()
{
	WT_OFF();
	INT_OFF();
	CLK_INIT();
	MEM_INIT();
}
