#ifndef __TIMER__
#define __TIMER__

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>

void Timer2_Init(void);
void Timer3_Init(void);
void Timer3_Delay_us(uint16_t us);
void Timer3_Delay_ms(uint16_t ms);

#endif /*__TIMER__*/
