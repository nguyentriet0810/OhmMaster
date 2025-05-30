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
#ifndef __MAIN__
#define __MAIN__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_flash.h>

#include "os.h"
#include "timer.h"
#include "adc.h"
#include "tft.h"
//#include "touch.h"
#include "button.h"
#include "com.h"
#include "sdcard.h"
#include "fonts.h"

#define quanta 1 //(ms)

//typedef struct {
//	uint8_t 
//} state;

typedef struct {
	uint8_t Ranges;
	uint8_t Frequency;
	uint8_t Uart;
	uint8_t SD;
	uint8_t Graph;
} Enable_Peripheral;

void RCC_Clock_Init (void);
void tach_4_chu_so_dau(float so, uint8_t out[4]);
void Display_Init(Enable_Peripheral *dev, float val,  uint8_t out[4]);

void Draw_Display(void);
void Check_Button(void);
void Read_Sensor(void);
void Transmit_To_PC(void);
void SD_Save_Data(void);
	
int main (void);

#endif /*__MAIN__*/
