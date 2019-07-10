#ifndef __TIMER_H__
#define __TIMER_H__

#define ONE_SHOT	0x00
#define AUTO_RELOAD 0x01

bool timer_init(uint32_t timerx_base, uint8_t mode, uint8_t scale, uint32_t time, uint16_t cnt);
inline void timer_start(uint32_t timerx_base);
inline void timer_stop(uint32_t timerx_base);

#endif
