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
#ifndef __ADC__
#define __ADC__

#include <stdint.h>
#include <stm32f10x.h>

#include "iic.h"
#include "timer.h"

#define ADS1115_ADDR  0x48U
#define ADS1115_REG_CONVERSION  0x00U
#define ADS1115_REG_CONFIG      0x01U

#define range_1 10U
#define range_2 100U
#define range_3 1000U
#define range_4 10000U
#define range_5 100000U
#define range_6 470000U

#define A0_GND 0x4U
#define A2_GND 0x6U

#define pga_2V    0x2U  // 2.048V
#define pga_4V    0x1U  // 4.096V
#define pga_6V    0x0U  // 6.144V
//#define dr_8sps   0x0U  // 8   SPS
//#define dr_16sps  0x1U  // 16  SPS
//#define dr_32sps  0x2U  // 32  SPS
//#define dr_64sps  0x3U  // 64  SPS
//#define dr_128sps 0x4U  // 128 SPS

void ADC_GPIO_Measurement_Range (void);
void ADC_GPIO_Reset(void);
void ADC_Differential_Init(uint16_t freq, uint16_t pga);
uint16_t ADC_Differential_Read(uint16_t freq, uint16_t pga);
void ADC_Single_Init(uint16_t mux, uint16_t freq, uint16_t pga);

// float ADC_Differential_Voltage(void);
float ADC_Range1_Resistance(uint16_t freq, uint16_t pga);
float ADC_Range2_Resistance(uint16_t freq, uint16_t pga);
float ADC_Range3_Resistance(uint16_t freq, uint16_t pga);
float ADC_Range4_Resistance(uint16_t freq, uint16_t pga);
float ADC_Range5_Resistance(uint16_t freq, uint16_t pga);
float ADC_Range6_Resistance(uint16_t freq);
float ADC_Range7_Resistance(uint16_t freq);

#endif /*__ADC__*/
