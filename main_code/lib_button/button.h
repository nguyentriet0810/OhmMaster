#ifndef __BUTTON__
#define __BUTTON__

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_exti.h>

#define Button_Port   GPIOB
#define Button_Hold   GPIO_Pin_8  
#define Button_Choose GPIO_Pin_9
#define Button_Top    GPIO_Pin_6
#define Button_Bottom GPIO_Pin_7
#define Button_Left   GPIO_Pin_4
#define Button_Right  GPIO_Pin_5


void Button_GPIO_Init(void);

#endif /*__BUTTON__*/
