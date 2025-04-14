#include "adc.h"

void ADC_GPIO_Measurement_Range(void) {
	// Enable clock for GPIOA, GPIOB and AFIO
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
        
	GPIO_InitTypeDef GPIO_InitStructure;
  
  // Configure PA8, PA11, PA12, PA15 as output push-pull
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
  // Configure PB1, PB3 as output push-pull
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
    
  // Set initial output low for all configured pins
  GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15);
  GPIO_ResetBits(GPIOB, GPIO_Pin_1 | GPIO_Pin_3);
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
float ADC_Range6_Resistance(uint16_t freq, uint16_t pga) {
	GPIOB->BSRR = GPIO_BSRR_BS1;
	int16_t val = (int16_t)ADC_Differential_Read(freq, pga);
	float voltage = (val * 2.048) / 32768;
	float Resistance = (voltage * range_6) - 50000; // 0.005mA
	GPIOB->BSRR = GPIO_BSRR_BR1;
	return Resistance;
}

