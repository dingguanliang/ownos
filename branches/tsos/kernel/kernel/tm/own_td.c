#include "../include/types.h"
#include "../include/own.h"

// 当前任务延时函数（单位为：ms）。
void own_cur_tsk_delay(uint32_t time)
{
	own_enter_critical();
	
	pcur_TCB->cnt = (time / 1000) * SYS_TICK;	// 计算计数次数，并将其填入TCB中。
	OWN_DEL_RDY_LIST(pcur_TCB);					// 将TCB从就绪任务链表中删除。
	OWN_INS_PEND_LIST(pcur_TCB);				// 将当前任务插入挂起任务链表中。
	
	own_exit_critical();	
}
