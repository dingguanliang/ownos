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

// ��ʼ�������ջ������
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

// ������������
void own_creat_tsk(void (*ptsk)(void *), OWN_STK *pstk, uint32_t prio)
{
	pown_TCB pTCB;
	
	own_enter_critical();	// �����ٽ�����
	
	OWN_DEL_TCB_LIST(pTCB);	// ��TCB������β��ȡһ��TCB��
	
	// ��ʼ������TCB��
	pTCB->pstk = own_stk_init(ptsk, 0, pstk);
	pTCB->prio = prio;
	pTCB->pend_flag = NO_PEND;
	pTCB->cnt = 0;
	pTCB->ptsk = ptsk;
	
	OWN_INS_RDY_LIST(pTCB);	// ����ʼ��ϵ��������������������С�
	
	own_exit_critical();	// �˳��ٽ�����
}

// ɾ����������
void own_delete_tsk()
{
	OWN_DEL_RDY_LIST(pcur_TCB);	// ��TCB�Ӿ�������������ɾ����
	OWN_INS_TCB_LIST(pcur_TCB);	// ��ɾ�����TCB�Ż�TCB�����С�
	own_ts();					// ����������ȡ�
}

// ������������
void own_pend_tsk()
{
	OWN_DEL_RDY_LIST(pcur_TCB);		// ��TCB�Ӿ�������������ɾ����
	pcur_TCB->pend_flag = PEND;		// ����TCB�����־��
	OWN_INS_PEND_LIST(pcur_TCB);	// ��ɾ�����TCB������������С�
	own_ts();						// ����������ȡ�
}

// �ָ���������
void own_resume_tsk(void (*ptsk)(void *))
{	
	ptsk_pend_list_cur = ptsk_pend_head;						// ָ���һ��TCB��
	do {
		if(ptsk_pend_list_cur->ptsk == ptsk) {
			OWN_DEL_PEND_LIST(ptsk_pend_list_cur);				// ��TCB�ӹ�������������ɾ����
			ptsk_pend_list_cur->pend_flag = NO_PEND;			// ����TCB�����־��
			OWN_INS_RDY_LIST(ptsk_pend_list_cur);				// ��ɾ�����TCB������������С�
			break;
		}
		else
			ptsk_pend_list_cur = ptsk_pend_list_cur->pnext_TCB; // ָ����һ��TCB��
	}while(ptsk_pend_head != ptsk_pend_list_cur);
	own_ts();													// ����������ȡ�
}
