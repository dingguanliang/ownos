#include "../../include/types.h"
#include "../../include/own.h"

// ϵͳʱ�䡣
uint32_t sys_time = 0;

// ϵͳTICK��������
void own_tick()
{
	pown_TCB pTCB;
	
	sys_time++;											// ϵͳʱ���Լӡ�
	
	// �����������ֵ��
	ptsk_pend_list_cur = ptsk_pend_head;
	do {
		pTCB = ptsk_pend_list_cur->pnext_TCB;
		if(NO_PEND == ptsk_pend_list_cur->pend_flag) {
			ptsk_pend_list_cur->cnt--;
			if(0 == ptsk_pend_list_cur->cnt) {
				OWN_DEL_PEND_LIST(ptsk_pend_list_cur);	// �ӹ�������������ɾ��TCB��
				OWN_INS_RDY_LIST(ptsk_pend_list_cur);	// ���������ϣ����������������������С�
			}
		}
		ptsk_pend_list_cur = pTCB;
	}while(ptsk_pend_head != ptsk_pend_list_cur);
}
