#include "../include/types.h"
#include "../include/own.h"

own_TCB	TCB_list[TSK_NUM_MAX];
own_TCB	pool_TCB, pend_TCB, rdy_TCB;

pown_TCB pTCB_list_head = NULL;
pown_TCB pTCB_list_tail = NULL;

pown_TCB ptsk_pend_head = NULL;
pown_TCB ptsk_pend_tail = NULL;
pown_TCB ptsk_pend_list_cur = NULL;

pown_TCB ptsk_rdy_null = NULL;
pown_TCB ptsk_rdy_head = NULL;
pown_TCB ptsk_rdy_tail = NULL;
pown_TCB ptsk_rdy_list_cur = NULL;

// 初始化任务堆栈函数。
static OWN_STK *own_stk_init(void (*ptsk)(void *), void *parg, OWN_STK *pstk)
{
	OWN_STK *stk;

    stk = pstk;                                 
    *(stk) = (OWN_STK)ptsk;                             
    *(--stk) = (OWN_STK)0;                           
    *(--stk) = (OWN_STK)0;                           
    *(--stk) = (OWN_STK)0;                          
    *(--stk) = (OWN_STK)0;                           
    *(--stk) = (OWN_STK)0;                      
    *(--stk) = (OWN_STK)0;                            
    *(--stk) = (OWN_STK)0;                         
    *(--stk) = (OWN_STK)0;                                  
    *(--stk) = (OWN_STK)0;                      
    *(--stk) = (OWN_STK)0;                     
    *(--stk) = (OWN_STK)0;                  
    *(--stk) = (OWN_STK)0;                             
    *(--stk) = (OWN_STK)0;                     
    *(--stk) = (OWN_STK)parg;                             
    *(--stk) = (OWN_STK)(0x13 | 0x0);                                          
    *(--stk) = (OWN_STK)(0x13 | 0x0);       
	
	return(stk);
}

// 创建任务函数。
void own_creat_tsk(void (*ptsk)(void *), OWN_STK *pstk, uint32_t prio)
{
	pown_TCB pTCB;
	
	own_enter_critical();	// 进入临界区。
	
	OWN_DEL_TCB_LIST(pTCB);	// 从TCB块链表尾部取一块TCB。
	
	// 初始化任务TCB。
	pTCB->pstk = own_stk_init(ptsk, 0, pstk);
	pTCB->prio = prio;
	pTCB->pend_flag = NO_PEND;
	pTCB->cnt = 0;
	pTCB->ptsk = ptsk;
	
	OWN_INS_RDY_LIST(pTCB);	// 将初始完毕的任务插入就绪任务链表中。
	
	own_exit_critical();	// 退出临界区。
}

// 删除任务函数。
void own_delete_tsk()
{
	OWN_DEL_RDY_LIST(pcur_TCB);	// 将TCB从就绪任务链表中删除。
	OWN_INS_TCB_LIST(pcur_TCB);	// 将删除后的TCB放回TCB链表中。
	own_ts();					// 进行任务调度。
}

// 挂起任务函数。
void own_pend_tsk()
{
	OWN_DEL_RDY_LIST(pcur_TCB);		// 将TCB从就绪任务链表中删除。
	pcur_TCB->pend_flag = PEND;		// 设置TCB挂起标志。
	OWN_INS_PEND_LIST(pcur_TCB);	// 将删除后的TCB插入挂起链表中。
	own_ts();						// 进行任务调度。
}

// 恢复任务函数。
void own_resume_tsk(void (*ptsk)(void *))
{	
	ptsk_pend_list_cur = ptsk_pend_head;						// 指向第一个TCB。
	do {
		if(ptsk_pend_list_cur->ptsk == ptsk) {
			OWN_DEL_PEND_LIST(ptsk_pend_list_cur);				// 将TCB从挂起任务链表中删除。
			ptsk_pend_list_cur->pend_flag = NO_PEND;			// 设置TCB挂起标志。
			OWN_INS_RDY_LIST(ptsk_pend_list_cur);				// 将删除后的TCB插入就绪链表中。
			break;
		}
		else
			ptsk_pend_list_cur = ptsk_pend_list_cur->pnext_TCB; // 指向下一个TCB。
	}while(ptsk_pend_head != ptsk_pend_list_cur);
	own_ts();													// 进行任务调度。
}
