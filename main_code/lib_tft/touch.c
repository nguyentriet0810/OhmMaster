
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
#include "touch.h"

void Touch_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;

    // T_CS = PA4
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_SetBits(GPIOA, GPIO_Pin_4); // CS high

    // T_IRQ = PB0
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

uint16_t XPT2046_ReadChannel(uint8_t cmd) {
	//set clock speed = 2.25M for touch 
	Spi1_SetSpeed(SPI_BaudRatePrescaler_32);
  uint16_t value = 0;

  ILI9341_CS_HIGH();     // Disable TFT
  XPT2046_CS_LOW();      // Enable Touch

  Spi1_SendByte(cmd);                     // G?i l?nh d?c kênh (X/Y)
  value = Spi1_ReceiveByte() << 8;        // Nh?n byte cao
  value |= Spi1_ReceiveByte();            // Nh?n byte th?p
  value >>= 4;                            // L?y 12 bit k?t qu?

  XPT2046_CS_HIGH();      // Disable Touch
	//set clock speed = 18M for TFT 
	Spi1_SetSpeed(SPI_BaudRatePrescaler_4);
  return value;
}

void Touch_ReadPixelXY(uint16_t *x, uint16_t *y) {
    uint16_t rawX = XPT2046_ReadChannel(0x90);
    uint16_t rawY = XPT2046_ReadChannel(0xD0);
//		*x = rawX;
//		*y = rawY;
    // Scale X: map t? [TOUCH_MIN_X ? TOUCH_MAX_X] sang [0 ? LCD_WIDTH-1]
    if (rawX < TOUCH_MIN_X) rawX = TOUCH_MIN_X;
    if (rawX > TOUCH_MAX_X) rawX = TOUCH_MAX_X;
    *x = (uint16_t)(((uint32_t)(rawX - TOUCH_MIN_X)) * (LCD_WIDTH - 1) / (TOUCH_MAX_X - TOUCH_MIN_X));

    // Scale Y: map t? [TOUCH_MIN_Y ? TOUCH_MAX_Y] sang [0 ? LCD_HEIGHT-1]
    if (rawY < TOUCH_MIN_Y) rawY = TOUCH_MIN_Y;
    if (rawY > TOUCH_MAX_Y) rawY = TOUCH_MAX_Y;
    *y = (uint16_t)(((uint32_t)(rawY - TOUCH_MIN_Y)) * (LCD_HEIGHT - 1) / (TOUCH_MAX_Y - TOUCH_MIN_Y));
}

bool Touch_IsPressed(void) {
    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == Bit_RESET;
}
