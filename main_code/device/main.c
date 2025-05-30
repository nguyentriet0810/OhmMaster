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
#include "main.h"

float res;
uint8_t Sema_COM, Sema_SD, Sema_Value;
uint8_t X_Coordinate = 15, Y_Coordinate = 160;
Enable_Peripheral device;
uint16_t axis_x, axis_y;

void Draw_Display(void) {
	while (1) {
		axis_y++;
		switch (device.Ranges) {
			case 1:
				ILI9341_DrawText( 35, 160, "RGS:20  R"  , GREEN, BLACK, 2);
				break;
			case 2:
				ILI9341_DrawText( 35, 160, "RGS:200 R"  , GREEN, BLACK, 2);
				break;
			case 3:
				ILI9341_DrawText( 35, 160, "RGS:2K  R"  , GREEN, BLACK, 2);
				break;
			case 4:
				ILI9341_DrawText( 35, 160, "RGS:20K R"  , GREEN, BLACK, 2);
				break;
			case 5:
				ILI9341_DrawText( 35, 160, "RGS:200KR"  , GREEN, BLACK, 2);
				break;
			case 6:
				ILI9341_DrawText( 35, 160, "RGS:2M  R"  , GREEN, BLACK, 2);
				break;
			case 7:
				ILI9341_DrawText( 35, 160, "RGS:20M R"  , GREEN, BLACK, 2);
				break;
			default:
				ILI9341_DrawText( 35, 160, "RGS: AUTO"  , GREEN, BLACK, 2);
				break;
		}
		switch (device.Frequency) {
			case 0:
				ILI9341_DrawText( 35, 190, "SPS:8   Hz" , GREEN, BLACK, 2);
				break;
			case 1:
				ILI9341_DrawText( 35, 190, "SPS:16  Hz" , GREEN, BLACK, 2);
				break;
			case 2:
				ILI9341_DrawText( 35, 190, "SPS:32  Hz" , GREEN, BLACK, 2);
				break;
			case 3:
				ILI9341_DrawText( 35, 190, "SPS:64  Hz" , GREEN, BLACK, 2);
				break;
			default:
				ILI9341_DrawText( 35, 190, "SPS:128 Hz" , GREEN, BLACK, 2);
				break;
		}
		switch (device.Uart) {
			case 1:
				ILI9341_DrawText(200, 160, "COM PORT"   , GREEN, BLACK, 2);
				break;
			default:
				ILI9341_DrawText(200, 160, "COM PORT"   , RED  , BLACK, 2);
				break;
		}
		switch (device.SD) {
			case 1: 
				ILI9341_DrawText(200, 190, "SD CARD"    , GREEN, BLACK, 2);
				break;
			default:
				ILI9341_DrawText(200, 190, "SD CARD"    , RED  , BLACK, 2);
				break;
		}
		switch (device.Graph) {
			case 1:
				ILI9341_DrawText(200, 220, "GRAPH "     , GREEN, BLACK, 2);
				break;
			default:
				ILI9341_DrawText(200, 220, "GRAPH "     , RED  , BLACK, 2);
				break;
		}
		ILI9341_DrawRectangle(15 ,160, 20,100,BLACK);
		ILI9341_DrawRectangle(180,160, 20,100,BLACK);
		ILI9341_DrawText(X_Coordinate,  Y_Coordinate, ">" , YELLOW, BLACK, 2);
		osCooperative_Wait(&Sema_Value);
		uint8_t data[4];
		tach_4_chu_so_dau(res, data);
		Display_Init(&device,res,data);
	}
}

void Check_Button(void) {
	while (1) {
		axis_x++;
		if        ( GPIO_ReadInputDataBit(Button_Port, Button_Hold  ) == 0) {
			if        ((X_Coordinate == 15) && (Y_Coordinate == 160)) {
				device.Ranges++;
				if (device.Ranges > 8) {
					device.Ranges = 1;
				}
			} else if ((X_Coordinate == 15) && (Y_Coordinate == 190)) {
				device.Frequency = device.Frequency + 1;
				if (device.Frequency > 4) {
					device.Frequency = 0;
				}
			}
		} else if ( GPIO_ReadInputDataBit(Button_Port, Button_Choose) == 0) {
			if (X_Coordinate == 180) { 
				switch (Y_Coordinate) {
					case 160: 
						if (device.Uart == 0) {
							device.Uart = 1;
						} else {
							device.Uart = 0;
						}
						break;
					case 190:
						if (device.SD == 0) {
							device.SD = 1;
						} else {
							device.SD = 0;
						}
						break;
					default:
						if (device.Graph ==  0) {
							device.Graph = 1;
						} else {
							device.Graph = 0;
						}
						break;
				}
			}
		} else if ( GPIO_ReadInputDataBit(Button_Port, Button_Top   ) == 0) {
			if (Y_Coordinate > 160) {
				Y_Coordinate = Y_Coordinate - 30;
			} else {
				Y_Coordinate = 160;
			}
		} else if ( GPIO_ReadInputDataBit(Button_Port, Button_Bottom) == 0) {
			if (X_Coordinate == 15) {
				Y_Coordinate = Y_Coordinate + 30;
				if ( Y_Coordinate > 190) {
					Y_Coordinate = 190;
				}
			} else {
				Y_Coordinate = Y_Coordinate + 30;
				if (Y_Coordinate > 220) {
					Y_Coordinate = 220;
				}
			}
		} else if ( GPIO_ReadInputDataBit(Button_Port, Button_Left  ) == 0) {
			X_Coordinate = 15;
			Y_Coordinate = 160;
		} else if ( GPIO_ReadInputDataBit(Button_Port, Button_Right ) == 0) {
			X_Coordinate = 180;
			Y_Coordinate = 160;
		}
		osThreadsSleep(20);
	}
}
void Read_Sensor(void) {
	while (1) {
		float value;
		switch (device.Ranges) {
			case 1:
				res = ADC_Range1_Resistance(device.Frequency, pga_2V);
				break;
			case 2:
				res = ADC_Range2_Resistance(device.Frequency, pga_2V);
				break;
			case 3:
				res = ADC_Range3_Resistance(device.Frequency, pga_2V);
				break;
			case 4:
				res = ADC_Range4_Resistance(device.Frequency, pga_2V);
				break;
			case 5:
				res = ADC_Range5_Resistance(device.Frequency, pga_2V);
				break;
			case 6:
				res = ADC_Range6_Resistance(device.Frequency);
				break;
			case 7:
				res = ADC_Range7_Resistance(device.Frequency);
				break;
			default:
				value = ADC_Range7_Resistance(device.Frequency);
				if (value > 2000000) {
					res = value;
					break;
				} 
				value = ADC_Range6_Resistance(device.Frequency);
				if (value > 200000) {
					res = value;
					break;
				} 
				value = ADC_Range5_Resistance(device.Frequency, pga_2V);
				if (value > 20000) {
					res = value;
					break;
				}
				value = ADC_Range4_Resistance(device.Frequency, pga_2V);
				if (value > 2000) {
					res = value;
					break;
				}
				value = ADC_Range3_Resistance(device.Frequency, pga_2V);
				if (value > 200) {
					res = value;
					break;
				}
				value = ADC_Range2_Resistance(device.Frequency, pga_2V);
				if (value > 20) {
					res = value;
					break;
				}
				value = ADC_Range1_Resistance(device.Frequency, pga_2V);
				res = value;
				break;
		}
		osSemaphore_Give(&Sema_Value);
	}
}

void Transmit_To_PC(void) {
	while (1) {
		if (device.Uart == 1) {
			osCooperative_Wait(&Sema_COM);
			if (((device.Ranges) >= 6 && (res > 910000)) || ((device.Ranges) == 5 && (res > 200000)) || ((device.Ranges) == 4 && (res > 20000)) \
					|| ((device.Ranges) == 3 && (res > 2000)) || ((device.Ranges) == 2 && (res > 200)) || ((device.Ranges) == 1 && (res > 20))) {
				Usart_printf("0,0,0,0,0,OL,0,0\n");
			} else if (((device.Ranges) == 6 && (res < 200000)) || ((device.Ranges) == 5 && (res < 3000)) || ((device.Ranges) == 4 && (res < 300)) \
					|| ((device.Ranges) == 3 && (res < 30)) || ((device.Ranges) == 2 && (res < 3)) || ((device.Ranges) == 1 && (res < 0.4))) {
				Usart_printf("0,0,0,0,0,0.0,0,0\n");
			} else {
				Usart_printf("0,0,0,0,0,%s,0,0 \n", float_to_string(res,3));
			}
			osThreadYield();
		} else {
			osThreadYield();
		}
	}
}
void SD_Save_Data(void) {
	while (1) {
		if (device.SD == 1) {
			osCooperative_Wait(&Sema_SD);
			osThreadYield();
		} else {
			osThreadYield();
		}
	}
}

//test tounch

int main (void) {
	
	device.Ranges = 1;
	device.Frequency = 0;
	device.Uart = 0;
	device.SD = 0;
	device.Graph = 0;
	
	RCC_Clock_Init();
	
	Timer2_Init();
	
	Timer3_Init();

	Usart1_Init();
	
	IIC2_Init();
	
	ADC_GPIO_Measurement_Range();
	
	Button_GPIO_Init();
	
	Spi1_Init();
  ILI9341_Reset();
	ILI9341_Init();  // Kh?i t?o màn hình
  ILI9341_FillScreen(BLACK);  // Ð?t n?n màu d?
	
	draw7Segment(5  ,   5,     11, RED   );  // Ch? s? 1, màu d?
	drawDot     (68 , 115,         BLACK );  // D?u ch?m, màu d?
	draw7Segment(75 ,   5,      0, RED   );  // Ch? s? 2, màu d?
	drawDot     (138, 115,         RED   );  // D?u ch?m, màu d?
	draw7Segment(145,   5,     10, RED   );  // Ch? s? 3, màu d?
	drawDot     (208, 115,         BLACK );  // D?u ch?m, màu d?
	draw7Segment(215,   5,     11, RED   );  // Ch? s? 4, màu d?
		
	ILI9341_DrawLine (0  , 129, 319, 129, WHITE);
	ILI9341_DrawLine (0  , 130, 319, 130, WHITE);
	ILI9341_DrawLine (160, 129, 160, 239, WHITE);
	ILI9341_DrawLine (161, 129, 161, 239, WHITE);
	
	ILI9341_DrawText( 10, 135, "SETTINGS:"  , BLUE  , BLACK, 2);
	ILI9341_DrawText( 35, 160, "RGS:20  R"  , GREEN , BLACK, 2);
	ILI9341_DrawText( 35, 190, "SPS:8   Hz" , GREEN , BLACK, 2);
	ILI9341_DrawText(175, 135, "OPTIONS:"   , BLUE  , BLACK, 2);
	ILI9341_DrawText(200, 160, "COM PORT"   , RED   , BLACK, 2);
	ILI9341_DrawText(200, 190, "SD CARD"    , RED   , BLACK, 2);
	ILI9341_DrawText(200, 220, "GRAPH "     , RED   , BLACK, 2);
	ILI9341_DrawText( 15, 160, ">"          , YELLOW, BLACK, 2);
	
	osSemaphore_Init(&Sema_COM  , 0);
	osSemaphore_Init(&Sema_SD   , 0);
	osSemaphore_Init(&Sema_Value, 0);
	
	osKernelInit();
	osKernelAdd1Thread(*(Draw_Display));
	osKernelAdd1Thread(*(Check_Button));
	osKernelAdd1Thread(*(Read_Sensor));
	osKernelAdd1Thread(*(Transmit_To_PC));
	osKernelAdd1Thread(*(SD_Save_Data));
	osKernelLaunch(quanta);
	
	//Touch_Init();
	
	while (1){
//		if (Touch_IsPressed()) {
//      Touch_ReadPixelXY(&axis_x, &axis_y);
//    }
	}
}

void RCC_Clock_Init (void) {
	// Enable clock AFIO
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;  
	//Disable JTAG but keep SWD enabled (free pb3 pb4 pa15)
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	// Step 1: Enable HSE and wait for it to be ready
  RCC_HSEConfig(RCC_HSE_ON);
  while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

  // Step 2: Configure Flash memory latency and enable Prefetch Buffer
  FLASH_SetLatency(FLASH_Latency_2);
  FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

  // Step 3: Configure PLL (HSE as source, PLL multiplier x9)
  RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
  RCC_PLLCmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

  // Step 4: Configure bus clocks (after PLL is ready)
  RCC_HCLKConfig(RCC_SYSCLK_Div1);   // AHB = SYSCLK = 72MHz
  RCC_PCLK1Config(RCC_HCLK_Div2);    // APB1 = AHB / 2 = 36MHz
  RCC_PCLK2Config(RCC_HCLK_Div1);    // APB2 = AHB / 1 = 72MHz

  // Step 5: Switch system clock to PLL
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  while (RCC_GetSYSCLKSource() != 0x08); // 0x08: PLL used as system clock
}
void tach_4_chu_so_dau(float so, uint8_t out[4]) {
    uint32_t so_nguyen = (uint32_t)so;
    float phan_thap_phan = so - (float)so_nguyen;
    int count = 0;

    // X? lý ph?n nguyên
    if (so_nguyen == 0) {
        out[count++] = 0;
    } else {
        // Ð?m s? ch? s? trong ph?n nguyên
        uint32_t temp = so_nguyen;
        int so_chu_so = 0;
        while (temp > 0) {
            temp /= 10;
            so_chu_so++;
        }

        // Trích t?ng ch? s? t? trái sang
        for (int i = so_chu_so - 1; i >= 0 && count < 4; i--) {
            uint32_t mu_10 = 1;
            for (int j = 0; j < i; j++) mu_10 *= 10;
            out[count++] = (so_nguyen / mu_10) % 10;
        }
    }

    // B? sung ph?n th?p phân n?u chua d? 4 ch? s?
    while (count < 4) {
        phan_thap_phan *= 10.0f;
        out[count++] = (uint8_t)phan_thap_phan;
        phan_thap_phan -= (uint8_t)phan_thap_phan;
    }
}
void Display_Init(Enable_Peripheral *dev, float val,  uint8_t out[4]) {
	uint8_t counter = 0;
	if ((val >= 10000000) && (val <= 99999999)) {
		ILI9341_DrawText(285,  10,        "MR"  , RED  , BLACK, 3);
		counter = 2;
	}
	else if ((val >= 1000000) && (val <= 9999999)) {
		ILI9341_DrawText(285,  10,        "MR"  , RED  , BLACK, 3);
		counter = 1;
	} else if ((val >= 100000)&&(val <= 999999)) {
		ILI9341_DrawText(285,  10,        "KR"  , RED  , BLACK, 3);
		counter = 3;
	} else if ((val >= 10000)&&(val <= 99999)) {
		ILI9341_DrawText(285,  10,        "KR"  , RED  , BLACK, 3);
		counter = 2;
	} else if ((val >= 1000)&&(val <= 9999)) {
		ILI9341_DrawText(285,  10,        "KR"  , RED  , BLACK, 3);
		counter = 1;
	} else if ((val >= 100)&&(val <= 999)) {
		ILI9341_DrawText(285,  10,        "R "  , RED  , BLACK, 3);
		counter = 3;
	} else if ((val >= 10)&&(val <= 99)) {
		ILI9341_DrawText(285,  10,        "R "  , RED  , BLACK, 3);
		counter = 2;
	} else if ((val >= 0.1)&&(val <= 9)) {
		ILI9341_DrawText(285,  10,        "R "  , RED  , BLACK, 3);
		counter = 1;
	} 
//	if ((dev->Ranges) >= 6 && (val > 950000)) {
//		counter = 0;
//	} else if ((dev->Ranges) == 5 && (val > 200000)) { 
//		counter = 0;
//	} else if ((dev->Ranges) == 4 && (val > 20000)) { 
//		counter = 0;
//	} else if ((dev->Ranges) == 3 && (val > 2000)) { 
//		counter = 0;
//	} else if ((dev->Ranges) == 2 && (val > 200)) { 
//		counter = 0;
//	} else if ((dev->Ranges) == 1 && (val > 20)) { 
//		counter = 0;
//	} 
	if (((dev->Ranges) >= 7 && (val > 22000000)) ||((dev->Ranges) == 6 && (val > 2000000)) || ((dev->Ranges) == 5 && (val > 200000)) || ((dev->Ranges) == 4 && (val > 20000)) \
			|| ((dev->Ranges) == 3 && (val > 2000)) || ((dev->Ranges) == 2 && (val > 200)) || ((dev->Ranges) == 1 && (val > 20))) {
		counter = 0;
	} else if (((dev->Ranges) == 7 && (val < 2000000)) || ((dev->Ranges) == 6 && (val < 200000)) || ((dev->Ranges) == 5 && (val < 3000)) || ((dev->Ranges) == 4 && (val < 300)) \
			|| ((dev->Ranges) == 3 && (val < 30)) || ((dev->Ranges) == 2 && (val < 3)) || ((dev->Ranges) == 1 && (val < 0.4))) {
		counter = 4;
	}
	switch (counter) {
		case 0: //0.L
			draw7Segment(5  ,   5,     11, RED   );  // Ch? s? 1, màu d?
			drawDot     (68 , 115,         BLACK );  // D?u ch?m, màu d?
			draw7Segment(75 ,   5,      0, RED   );  // Ch? s? 2, màu d?
			drawDot     (138, 115,         RED   );  // D?u ch?m, màu d?
			draw7Segment(145,   5,     10, RED   );  // Ch? s? 3, màu d?
			drawDot     (208, 115,         BLACK );  // D?u ch?m, màu d?
			draw7Segment(215,   5,     11, RED   );  // Ch? s? 4, màu d?
			break;
		case 1:
			draw7Segment(5  ,   5, out[0], RED   );  // Ch? s? 1, màu d?
			drawDot     (68 , 115,         RED   );  // D?u ch?m, màu d?
			draw7Segment(75 ,   5, out[1], RED   );  // Ch? s? 2, màu d?
			drawDot     (138, 115,         BLACK );  // D?u ch?m, màu d?
			draw7Segment(145,   5, out[2], RED   );  // Ch? s? 3, màu d?
			drawDot     (208, 115,         BLACK );  // D?u ch?m, màu d?
			draw7Segment(215,   5, out[3], RED   );  // Ch? s? 4, màu d?
			break;
		case 2:
			draw7Segment(5  ,   5, out[0], RED   );  // Ch? s? 1, màu d?
			drawDot     (68 , 115,         BLACK );  // D?u ch?m, màu d?
			draw7Segment(75 ,   5, out[1], RED   );  // Ch? s? 2, màu d?
			drawDot     (138, 115,         RED   );  // D?u ch?m, màu d?
			draw7Segment(145,   5, out[2], RED   );  // Ch? s? 3, màu d?
			drawDot     (208, 115,         BLACK );  // D?u ch?m, màu d?
			draw7Segment(215,   5, out[3], RED   );  // Ch? s? 4, màu d?
			break;
		case 3:
			draw7Segment(5  ,   5, out[0], RED   );  // Ch? s? 1, màu d?
			drawDot     (68 , 115,         BLACK );  // D?u ch?m, màu d?
			draw7Segment(75 ,   5, out[1], RED   );  // Ch? s? 2, màu d?
			drawDot     (138, 115,         BLACK );  // D?u ch?m, màu d?
			draw7Segment(145,   5, out[2], RED   );  // Ch? s? 3, màu d?
			drawDot     (208, 115,         RED   );  // D?u ch?m, màu d?
			draw7Segment(215,   5, out[3], RED   );  // Ch? s? 4, màu d?
			break;
		default: //0.0
			draw7Segment(5  ,   5,     11, RED   );  // Ch? s? 1, màu d?
			drawDot     (68 , 115,         BLACK );  // D?u ch?m, màu d?
			draw7Segment(75 ,   5,      0, RED   );  // Ch? s? 2, màu d?
			drawDot     (138, 115,         RED   );  // D?u ch?m, màu d?
			draw7Segment(145,   5,      0, RED   );  // Ch? s? 3, màu d?
			drawDot     (208, 115,         BLACK );  // D?u ch?m, màu d?
			draw7Segment(215,   5,     11, RED   );  // Ch? s? 4, màu d?
			break;
	} 
}

