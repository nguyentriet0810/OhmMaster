#ifndef __IIC__
#define __IIC__

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_i2c.h>

//#define FLAG_Mask  ((uint32_t)0x00FFFFFF)

void IIC2_GPIO_Init(void);
void IIC2_Init(void);
void IIC2_Write(uint8_t deviceAddr, uint8_t regAddr, uint16_t data);
uint16_t IIC2_Read(uint8_t deviceAddr, uint8_t regAddr);
#endif /*__IIC__*/
