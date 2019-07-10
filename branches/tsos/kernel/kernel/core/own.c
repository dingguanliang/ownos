#include "../include/types.h"
#include "../include/own.h"
#include "../include/debug.h"

OWN_STK idle_tsk_stk[IDLE_STK_SIZE];

pown_TCB pcur_TCB = NULL;

extern void own_creat_tsk(void *ptsk, uint32_t *pstk, uint32_t prio);

static void idle_tsk(void *parg);

void own_init()
{
	uint8_t i;
	pown_TCB pTCB;
	
	// 初始化TCB块链表。
	pool_TCB.ppre_TCB = &pool_TCB;
	pool_TCB.pnext_TCB = &pool_TCB;
	pTCB_list_head = &pool_TCB;
	pTCB_list_tail = pTCB_list_head;
	for(i = 0; i < TSK_NUM_MAX; i++) {
		pTCB = &TCB_list[i];
		OWN_INS_TCB_LIST(pTCB);
	}
	
	// 初始化挂起任务链表。
	pend_TCB.pend_flag = PEND;
	pend_TCB.ppre_TCB = &pend_TCB;
	pend_TCB.pnext_TCB = &pend_TCB;
	ptsk_pend_head = &pend_TCB;
	ptsk_pend_tail = ptsk_pend_head;
	
	// 初始化就绪任务链表。
	rdy_TCB.prio = 0;
	rdy_TCB.valid_flag = INVALID;
	rdy_TCB.ppre_TCB = &rdy_TCB;
	rdy_TCB.pnext_TCB = &rdy_TCB;
	ptsk_rdy_null = &rdy_TCB;
	ptsk_rdy_head = ptsk_rdy_null->pnext_TCB;
	ptsk_rdy_tail = ptsk_rdy_head;
	
	own_creat_tsk(idle_tsk, &idle_tsk_stk[IDLE_STK_SIZE], TSK_NUM_MAX - 1);	// 创建空闲任务。
}

void own_start()
{
	ptsk_rdy_head = ptsk_rdy_null->pnext_TCB;
	own_start_tsk();
}

static void idle_tsk(void *parg)
{
	parg = parg;
	
	while(1) {
		#if 1 == IDLE_TSK_DEBUG
			idle_tsk_debug_hook();
		#endif
	};
}
