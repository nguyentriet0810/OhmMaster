#ifndef __COM__
#define __COM__

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>

void Usart1_GPIO_Init(void);
void Usart1_Init(void);
void Usart1_SendChar(char c);
void Usart1_SendString(const char *str);
void Usart_printf(const char *format, ...);
char* float_to_string(float value, int precision);
#endif /*__COM__*/
