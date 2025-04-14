#include "button.h"

void Button_GPIO_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // B?t clock GPIOB

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;  // Ch? d? input pull-up
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_Init(GPIOB, &GPIO_InitStruct);  // C?u hình PB4 -> PB7

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_Init(GPIOB, &GPIO_InitStruct);  // C?u hình PB8, PB9
}
