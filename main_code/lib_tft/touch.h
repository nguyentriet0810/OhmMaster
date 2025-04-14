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
