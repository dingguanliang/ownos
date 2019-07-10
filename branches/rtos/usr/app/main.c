#include "../../kernel/kernel/include/types.h"
#include "../../kernel/kernel/include/include.h"
#include "../../kernel/kernel/include/stdio.h"

extern void sys_con_init();
extern void sys_tick_init();

OWN_STK	start_stk[STK_SIZE];
OWN_STK	tsk1_stk[STK_SIZE];
OWN_STK	tsk2_stk[STK_SIZE];

static void start_tsk(void *parg);
static void tsk1_func(void *parg);
static void tsk2_func(void *parg);

int32_t main()
{
	own_init();
	own_creat_tsk(start_tsk, &start_stk[STK_SIZE], 1);
	own_start();
	
	return(0);
}

static void start_tsk(void *parg)
{
	parg = parg;
	
	sys_con_init();
	
	puts("\n\r");
	puts("*************** own RTOS running ***************\n\r");
	printf("system version:%s\n\r", OWN_GET_SYS_VER());
	printf("author name:%s\n\r", OWN_GET_AUTHOR_NAME());
	printf("author E-mail:%s\n\r", OWN_GET_AUTHOR_EMAIL());
	puts("************************************************\n\r");

	own_creat_tsk(tsk1_func, &tsk1_stk[STK_SIZE], 2);
	puts("initial task 1 ok!\n\r");
	own_creat_tsk(tsk2_func, &tsk2_stk[STK_SIZE], 3);
	puts("initial task 2 ok!\n\r");
	
	sys_tick_init();

	own_delete_tsk();

	while(1) {	

	};
}

static void tsk1_func(void *parg)
{
	parg = parg;
	
	while(1) {
		puts("task1 running...\n\r");
		own_cur_tsk_delay(1000);
	};
}

static void tsk2_func(void *parg)
{
	parg = parg;
	
	while(1) {
		puts("task2 running...\n\r");
		own_cur_tsk_delay(2000);
	};
}
