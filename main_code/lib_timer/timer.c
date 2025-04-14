#include "timer.h"

void Timer2_Init(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_Prescaler = 7199;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 99;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);      // Cho ph�p ng?t
    TIM_Cmd(TIM2, ENABLE);                          // B?t d?u timer

    NVIC_InitTypeDef nvicStructure;
    nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 1;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
}

void Timer3_Init(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); // B?t clock cho TIM3

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_TimeBaseStructure.TIM_Prescaler = 71;  // Chia t?n s? 72 MHz xu?ng c�n 1 MHz (1 tick = 1 �s)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF; // Gi� tr? t?i da
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_Cmd(TIM3, ENABLE); // B?t d?u Timer3
}

// H�m delay theo micro gi�y (�s)
void Timer3_Delay_us(uint16_t us) {
  TIM3->CNT = 0; // Reset b? d?m
  while (TIM3->CNT < us); // �?i d?n khi d?t s? micro gi�y mong mu?n
}

// H�m delay theo mili gi�y (ms)
void Timer3_Delay_ms(uint16_t ms) {
  while (ms--) {
		Timer3_Delay_us(1000); // M?i l?n delay 1000 �s = 1 ms
  }
}
