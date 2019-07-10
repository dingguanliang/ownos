#ifndef __OWN_H__
#define __OWN_H__

#define NO_PEND	0
#define PEND	1

#define INVALID	0
#define VALID	1

#define SYS_TICK		100	
#define TSK_NUM_MAX		64	 
#define IDLE_STK_SIZE	128

// 获取系统时间（单位为：ms）。
#define OWN_GET_SYS_TIME()	(sys_time * 10)

// 将TCB插入双向循环链表中。
#define OWN_INS_TSK_LIST(p_pre_TCB, pTCB) do { \
	(pTCB)->ppre_TCB = (p_pre_TCB); \
	(pTCB)->pnext_TCB = (p_pre_TCB)->pnext_TCB; \
	(p_pre_TCB)->pnext_TCB->ppre_TCB = (pTCB); \
	(p_pre_TCB)->pnext_TCB = (pTCB); \
}while(0)

// 将TCB从双向循环链表中删除。
#define OWN_DEL_TSK_LIST(pTCB) do { \
	(pTCB)->ppre_TCB->pnext_TCB = (pTCB)->pnext_TCB; \
	(pTCB)->pnext_TCB->ppre_TCB = (pTCB)->ppre_TCB; \
	(pTCB)->ppre_TCB = NULL; \
	(pTCB)->pnext_TCB = NULL; \
}while(0)
	
// 将TCB放回TCB链表中。
#define OWN_INS_TCB_LIST(pTCB) do { \
	OWN_INS_TSK_LIST(pTCB_list_tail, pTCB); \
	pTCB_list_tail = (pTCB); \
}while(0)
	
// 从TCB链表中取出TCB。
#define OWN_DEL_TCB_LIST(pTCB) do { \
	(pTCB) = pTCB_list_tail; \
	pTCB_list_tail = pTCB_list_tail->ppre_TCB; \
	OWN_DEL_TSK_LIST(pTCB); \
}while(0)

// 将TCB插入挂起任务链表中。
#define OWN_INS_PEND_LIST(pTCB) do { \
	OWN_INS_TSK_LIST(ptsk_pend_tail, pTCB); \
	ptsk_pend_tail = (pTCB); \
}while(0)
	
// 从挂起任务链表中删除TCB。
#define OWN_DEL_PEND_LIST(pTCB) do { \
	if(ptsk_pend_tail == (pTCB)) \
		ptsk_pend_tail = ptsk_pend_tail->ppre_TCB; \
	OWN_DEL_TSK_LIST(pTCB); \
}while(0)

// 将TCB插入就绪任务链表中。
#define OWN_INS_RDY_LIST(pTCB) do { \
	ptsk_rdy_list_cur = ptsk_rdy_null; \
	do { \
		if((pTCB)->prio < ptsk_rdy_list_cur->prio) { \
			ptsk_rdy_list_cur = ptsk_rdy_list_cur->ppre_TCB; \
			OWN_INS_TSK_LIST(ptsk_rdy_list_cur, pTCB); \
			break; \
		} \
		else if(ptsk_rdy_tail == ptsk_rdy_list_cur) { \
			OWN_INS_TSK_LIST(ptsk_rdy_list_cur, pTCB); \
			ptsk_rdy_tail = ptsk_rdy_tail->pnext_TCB; \
			break; \
		} \
		ptsk_rdy_list_cur = ptsk_rdy_list_cur->pnext_TCB; \
	}while(ptsk_rdy_null != ptsk_rdy_list_cur); \
}while(0)
	
// 从就绪任务链表中删除TCB。
#define OWN_DEL_RDY_LIST(pTCB) do { \
	if(ptsk_rdy_tail == (pTCB)) \
		ptsk_rdy_tail = ptsk_rdy_tail->ppre_TCB; \
	OWN_DEL_TSK_LIST(pTCB); \
	CHECK_RDY_LIST(); \
}while(0)

// 检查就绪任务链表是否为空，为空时运行空闲任务。
#define CHECK_RDY_LIST() do { \
	if(ptsk_rdy_null != ptsk_rdy_null->ppre_TCB->ppre_TCB) { \
		ptsk_rdy_null->ppre_TCB->valid_flag = INVALID; \
	} \
	else { \
		ptsk_rdy_null->ppre_TCB->valid_flag = VALID; \
	} \
}while(0)
	
typedef uint32_t OWN_STK;
typedef void (*pfunc)(void *);

// 任务控制块。
typedef struct TCB{
	OWN_STK *pstk;
	uint8_t prio;
	uint8_t pend_flag;
	uint8_t valid_flag;
	uint32_t cnt;
	pfunc ptsk;
	struct TCB *ppre_TCB, *pnext_TCB;
}own_TCB, *pown_TCB;

extern uint32_t sys_time;

extern pown_TCB pcur_TCB;

extern own_TCB	TCB_list[];
extern own_TCB	pool_TCB, pend_TCB, rdy_TCB;

extern pown_TCB pTCB_list_head;
extern pown_TCB pTCB_list_tail;

extern pown_TCB ptsk_pend_head;
extern pown_TCB ptsk_pend_tail;
extern pown_TCB ptsk_pend_list_cur;

extern pown_TCB ptsk_rdy_null;
extern pown_TCB ptsk_rdy_head;
extern pown_TCB ptsk_rdy_tail;
extern pown_TCB ptsk_rdy_list_cur;

void own_start_tsk();
void own_irq_handle();
void own_enter_critical();
void own_exit_critical();

#endif
