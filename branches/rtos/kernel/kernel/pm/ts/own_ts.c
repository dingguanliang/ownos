#include "../../include/types.h"
#include "../../include/own.h"

// 系统时间。
uint32_t sys_time = 0;

// 系统TICK处理函数。
void own_tick()
{
	pown_TCB pTCB;
	
	sys_time++;											// 系统时间自加。
	
	// 调整任务计数值。
	ptsk_pend_list_cur = ptsk_pend_head;
	do {
		pTCB = ptsk_pend_list_cur->pnext_TCB;
		if(NO_PEND == ptsk_pend_list_cur->pend_flag) {
			ptsk_pend_list_cur->cnt--;
			if(0 == ptsk_pend_list_cur->cnt) {
				OWN_DEL_PEND_LIST(ptsk_pend_list_cur);	// 从挂起任务链表中删除TCB。
				OWN_INS_RDY_LIST(ptsk_pend_list_cur);	// 任务计数完毕，将任务插入就绪任务链表中。
			}
		}
		ptsk_pend_list_cur = pTCB;
	}while(ptsk_pend_head != ptsk_pend_list_cur);
}
