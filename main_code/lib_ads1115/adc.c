/*
MIT License

Copyright (c) 2025 Nguyen Hoang Minh Triet

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

-----------------------------------------------------------------------
Author : Nguyen Hoang Minh Triet 
Email  : 23trietminh23@gmail.com  
GitHub : https://github.com/nguyentriet0810  
YouTube: https://www.youtube.com/@hoangtriet9999
-----------------------------------------------------------------------
*/
#include "adc.h"

void ADC_GPIO_Measurement_Range(void) {
	// Enable clock for GPIOA, GPIOB and AFIO
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
        
	GPIO_InitTypeDef GPIO_InitStructure;
  
  // Configure PA8, PA11, PA12, PA15 as output push-pull
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  // Configure PB1, PB3 as output push-pull
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// Configure PC13, PC14, PC15 as output push-pull
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	// Set initial output low for all configured pins range 1-6
  GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15);
  GPIO_ResetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_3);
	
	// Set initial output high for all configured pins advance range
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
  GPIO_SetBits(GPIOC, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}
void ADC_GPIO_Reset(void) {
	// Set initial output low for all configured pins range 1-6
  GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15);
  GPIO_ResetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_3);
	
	// Set initial output high for all configured pins advance range
	GPIO_SetBits(GPIOA, GPIO_Pin_0);
  GPIO_SetBits(GPIOC, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}
//config = 0x8483
void ADC_Differential_Init(uint16_t freq, uint16_t pga) {
	volatile uint16_t config = 0;
	volatile uint16_t status;
  config |= 0x1u       << 15;  // ADS1115_OS_SINGLE:
  config |= 0x0u       << 12;  // ADS1115_MUX_AIN0_AIN1: 
  config |= pga        << 9 ;  // ADS1115_PGA_2_048V: 
  config |= 0x1u       << 8 ;  // ADS1115_MODE_SINGLE: 
  config |= freq       << 5 ;  // ADS1115_DR_16SPS: 
  config |= 0x0u       << 4 ;  // ADS1115_COMP_MODE_TRAD: 
  config |= 0x0u       << 3 ;  // ADS1115_COMP_POL_LOW: 
  config |= 0x0u       << 2 ;  // ADS1115_COMP_LAT_NON: 
  config |= 0x3u       << 0 ;  // ADS1115_COMP_QUE_DIS: 
	IIC2_Write(ADS1115_ADDR, ADS1115_REG_CONFIG, config);
	do {
    status = IIC2_Read(ADS1115_ADDR, ADS1115_REG_CONFIG);
	} while ((status & 0x8000) == 0);  // Bit OS == 0 ? chua xong
}

void ADC_Single_Init(uint16_t mux, uint16_t freq, uint16_t pga) {
	volatile uint16_t config = 0;
	volatile uint16_t status;
  config |= 0x1u       << 15;  // ADS1115_OS_SINGLE:
  config |= mux        << 12;  // ADS1115_MUX_AIN0_AIN1: 
  config |= pga        << 9 ;  // ADS1115_PGA_2_048V: 
  config |= 0x1u       << 8 ;  // ADS1115_MODE_SINGLE: 
  config |= freq       << 5 ;  // ADS1115_DR_16SPS: 
  config |= 0x0u       << 4 ;  // ADS1115_COMP_MODE_TRAD: 
  config |= 0x0u       << 3 ;  // ADS1115_COMP_POL_LOW: 
  config |= 0x0u       << 2 ;  // ADS1115_COMP_LAT_NON: 
  config |= 0x3u       << 0 ;  // ADS1115_COMP_QUE_DIS: 
	IIC2_Write(ADS1115_ADDR, ADS1115_REG_CONFIG, config);
	do {
    status = IIC2_Read(ADS1115_ADDR, ADS1115_REG_CONFIG);
	} while ((status & 0x8000) == 0);  // Bit OS == 0 ? chua xong
}

uint16_t ADC_Differential_Read(uint16_t freq, uint16_t pga) {
	ADC_Differential_Init(freq, pga_2V);
	int16_t val = IIC2_Read(ADS1115_ADDR, ADS1115_REG_CONVERSION);
	return val;
}

float ADC_Range1_Resistance(uint16_t freq, uint16_t pga) {
	GPIOA->BSRR = GPIO_BSRR_BS8;
	int16_t val = (int16_t)ADC_Differential_Read(freq, pga);
	float voltage = (val * 2.048) / 32768.0;
	float Resistance = (voltage * range_1) - 0.4; // 100mA
	GPIOA->BSRR = GPIO_BSRR_BR8;
	return Resistance;
}
float ADC_Range2_Resistance(uint16_t freq, uint16_t pga) {
	GPIOA->BSRR = GPIO_BSRR_BS11;
	int16_t val = (int16_t)ADC_Differential_Read(freq, pga);
	float voltage = (val * 2.048) / 32768.0;
	float Resistance = (voltage * range_2) - 0.4; // 10mA
	GPIOA->BSRR = GPIO_BSRR_BR11;
	return Resistance;
}
float ADC_Range3_Resistance(uint16_t freq, uint16_t pga) {
	GPIOA->BSRR = GPIO_BSRR_BS12;
	int16_t val = (int16_t)ADC_Differential_Read(freq, pga);
	float voltage = (val * 2.048) / 32768.0;
	float Resistance = (voltage * range_3) - 0.4; // 1mA
	GPIOA->BSRR = GPIO_BSRR_BR12;
	return Resistance;
}
float ADC_Range4_Resistance(uint16_t freq, uint16_t pga) {
	GPIOA->BSRR = GPIO_BSRR_BS15;
	int16_t val = (int16_t)ADC_Differential_Read(freq, pga);;
	float voltage = (val * 2.048) / 32768.0;
	float Resistance = voltage * range_4; // 0.1mA
	GPIOA->BSRR = GPIO_BSRR_BR15;
	return Resistance;
}
float ADC_Range5_Resistance(uint16_t freq, uint16_t pga) {
	GPIOB->BSRR = GPIO_BSRR_BS3;
	int16_t val = (int16_t)ADC_Differential_Read(freq, pga);
	float voltage = (val * 2.048) / 32768.0;
	float Resistance = voltage * range_5; // 0.01mA
	GPIOB->BSRR = GPIO_BSRR_BR3;
	return Resistance;
}
//float ADC_Range6_Resistance(uint16_t freq, uint16_t pga) {
//	GPIOB->BSRR = GPIO_BSRR_BS1;
//	int16_t val = (int16_t)ADC_Differential_Read(freq, pga);
//	float voltage = (val * 2.048) / 32768;
//	float Resistance = (voltage * range_6) - 50000; // 0.005mA
//	GPIOB->BSRR = GPIO_BSRR_BR1;
//	return Resistance;
//}
float ADC_Range6_Resistance(uint16_t freq) {
	ADC_GPIO_Reset();
	GPIOC->BSRR = GPIO_BSRR_BR14;
	float voltage1, voltage2, resister;
	ADC_Single_Init(A0_GND, freq, pga_6V);
	int16_t val = (int16_t)IIC2_Read(ADS1115_ADDR, ADS1115_REG_CONVERSION);
	voltage2 = (val * 6.144) / 32768.0;
	for(int i = 0; i < 50; i++) {
		ADC_Single_Init(A2_GND, 6, pga_4V);
		val = (int16_t)IIC2_Read(ADS1115_ADDR, ADS1115_REG_CONVERSION);
		voltage1 = (val * 4.096) / 32768.0;
		resister += ((voltage2 - voltage1) * 560000) / voltage1;
	}
	resister = resister / 50;
	GPIOC->BSRR = GPIO_BSRR_BS14;
	return resister;
}

float ADC_Range7_Resistance(uint16_t freq) {
	ADC_GPIO_Reset();
	GPIOA->BSRR = GPIO_BSRR_BR0;
	float voltage1, voltage2, resister;
	ADC_Single_Init(A0_GND, freq, pga_6V);
	int16_t  val = IIC2_Read(ADS1115_ADDR, ADS1115_REG_CONVERSION);
	voltage2 = (val * 6.144) / 32768.0;
	for (int i = 0; i < 50; i++) {
		ADC_Single_Init(A2_GND, 6, pga_4V);
		val = IIC2_Read(ADS1115_ADDR, ADS1115_REG_CONVERSION);
		voltage1 = (val * 4.096) / 32768.0;
		resister += ((voltage2 - voltage1) * 5600000) / voltage1;
	}
	resister = resister / 50;
	GPIOA->BSRR = GPIO_BSRR_BS0;
	return resister;
}

//float ADC_Range5_Resistance(uint16_t freq, uint16_t pga) {
//	GPIOB->BSRR = GPIO_BSRR_BS3;
//	int16_t val = (int16_t)ADC_Differential_Read(freq, pga);
//	float voltage = (val * 2.048) / 32768.0;
//	float Resistance = voltage * range_5; // 0.01mA
//	GPIOB->BSRR = GPIO_BSRR_BR3;
//	return Resistance;
//}
