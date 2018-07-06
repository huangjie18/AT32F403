#ifndef  __DELAY_H
#define  __DELAY_H
#include "sys.h"
#define delay_mode 1  

void delay_init(int SYSCLK);
void delay_us(u32 gd_us);
void delay_ms(u32 ms);

void delay_decrement(void);
#endif
