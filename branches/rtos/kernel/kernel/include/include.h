#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#define VERSION	"1.00"
#define CODER	"Ding Guanliang"
#define EMAIL	"343399208@qq.com"

#define SYS_TICK	100	
#define STK_SIZE	1024

// 获取系统版本。
#define OWN_GET_SYS_VER()		(VERSION)

// 获取作者姓名。
#define OWN_GET_AUTHOR_NAME()	(CODER)

// 获取作者邮箱。
#define OWN_GET_AUTHOR_EMAIL()	(EMAIL)

// 获取系统时间（单位为：ms）。
#define OWN_GET_SYS_TIME()		(sys_time * 10)

typedef uint32_t OWN_STK;

extern uint32_t sys_time;

// own core run.
void own_init();
void own_start();

// own task manage.
void own_creat_tsk(void (*ptsk)(void *), OWN_STK *pstk, uint32_t prio);
void own_delete_tsk();
void own_pend_tsk();
void own_resume_tsk(void (*ptsk)(void *));
void own_cur_tsk_delay(uint32_t time);

#endif
