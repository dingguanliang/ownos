#include "../include/types.h"
#include "../include/own.h"

// ��ǰ������ʱ��������λΪ��ms����
void own_cur_tsk_delay(uint32_t time)
{
	own_enter_critical();
	
	pcur_TCB->cnt = (time / 1000) * SYS_TICK;	// �����������������������TCB�С�
	OWN_DEL_RDY_LIST(pcur_TCB);					// ��TCB�Ӿ�������������ɾ����
	OWN_INS_PEND_LIST(pcur_TCB);				// ����ǰ�������������������С�
	
	own_exit_critical();	
}
