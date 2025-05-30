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
#ifndef __TOUCH__
#define __TOUCH__

#include <stm32f10x.h>

#include "tft.h"

#define XPT2046_CS_LOW()     GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define XPT2046_CS_HIGH()    GPIO_SetBits(GPIOA, GPIO_Pin_4)

#define TOUCH_MIN_X 100     // giá tr? ADC nh? nh?t tr?c X
#define TOUCH_MAX_X 2047    // giá tr? ADC l?n nh?t tr?c X
#define TOUCH_MIN_Y 100     // giá tr? ADC nh? nh?t tr?c Y
#define TOUCH_MAX_Y 2047    // giá tr? ADC l?n nh?t tr?c Y

#define LCD_WIDTH  320
#define LCD_HEIGHT 240


void Touch_Init(void);
uint16_t XPT2046_ReadChannel(uint8_t cmd);
void Touch_ReadPixelXY(uint16_t *x, uint16_t *y);
bool Touch_IsPressed(void);

#endif /*__TOUCH__*/
