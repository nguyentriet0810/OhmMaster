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
#include "touch.h"
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
