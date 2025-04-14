#include "com.h"

void Usart1_GPIO_Init(void) {
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;

  // C?u hình TX (PA9)
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  // C?u hình RX (PA10)
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
}
void Usart1_Init(void) {
	// B?t clock cho USART1
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	Usart1_GPIO_Init();
	
  // C?u hình USART1
  USART_InitTypeDef USART_InitStruct;
  USART_InitStruct.USART_BaudRate = 115200;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_Init(USART1, &USART_InitStruct);

  // B?t USART1
  USART_Cmd(USART1, ENABLE);

	// C?u hình NVIC cho USART1
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Usart1_SendChar(char c) {
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
  USART_SendData(USART1, c);
}

void Usart1_SendString(const char *str) {
  while (*str) {
		Usart1_SendChar(*str++);
  }
}

// H m printf
void Usart_printf(const char *format, ...) {
  char buffer[128];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  Usart1_SendString(buffer);
}

char* float_to_string(float value, int precision) {
    static char buffer[32];  // buffer tinh d? gi? k?t qu?
    char *ptr = buffer;

    int int_part = (int)value;
    float frac_part = fabsf(value - (float)int_part);

    if (value < 0 && int_part == 0) {
        strcpy(ptr, "-0");
    } else {
        sprintf(ptr, "%d", int_part);
    }

    // Di chuy?n con tr? d?n cu?i chu?i d? n?i ti?p
    ptr = buffer + strlen(buffer);
    *ptr++ = '.';

    for (int i = 0; i < precision; i++) {
        frac_part *= 10.0f;
        int digit = (int)frac_part;
        *ptr++ = digit + '0';
        frac_part -= digit;
    }

    *ptr = '\0';  // k?t thúc chu?i
    return buffer;
}
