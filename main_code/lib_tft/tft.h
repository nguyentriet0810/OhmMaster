#ifndef __TFT__
#define __TFT__

#include <stm32f10x.h>

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "spi1.h"
#include "timer.h"
#include "fonts.h"

#define ILI9341_CS_LOW()   GPIO_ResetBits(GPIOA, GPIO_Pin_1)
#define ILI9341_CS_HIGH()  GPIO_SetBits(GPIOA, GPIO_Pin_1)

#define ILI9341_DC_LOW()   GPIO_ResetBits(GPIOA, GPIO_Pin_3)  // Ch? d? Command
#define ILI9341_DC_HIGH()  GPIO_SetBits(GPIOA, GPIO_Pin_3)   // Ch? d? Data

#define ILI9341_RST_LOW()  GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define ILI9341_RST_HIGH() GPIO_SetBits(GPIOA, GPIO_Pin_2)

#define BLACK      				0x0000
#define NAVY        			0x000F
#define DARKGREEN   			0x03E0
#define DARKCYAN    			0x03EF
#define MAROON      			0x7800
#define PURPLE      			0x780F
#define OLIVE       			0x7BE0
#define LIGHTGREY   			0xC618
#define DARKGREY    			0x7BEF
#define BLUE        			0x001F
#define GREEN       			0x07E0
#define CYAN        			0x07FF
#define RED         			0xF800
#define MAGENTA     			0xF81F
#define YELLOW      			0xFFE0
#define WHITE       			0xFFFF
#define ORANGE      			0xFD20
#define GREENYELLOW 			0xAFE5
#define PINK        			0xF81F

// Ð?nh nghia các l?nh ILI9341
#define ILI9341_CASET   0x2A  // Column Address Set
#define ILI9341_RASET   0x2B  // Row Address Set
#define ILI9341_RAMWR   0x2C  // Memory Write

void ILI9341_SendCommand(uint8_t cmd);
void ILI9341_SendData(uint8_t data);
void ILI9341_Reset(void);
void ILI9341_Init(void);
void ILI9341_SetAddressWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void ILI9341_FillScreen(uint16_t color);
void ILI9341_SetRotation(uint8_t rotation);
void ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void ILI9341_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ILI9341_DrawIntro(void);
void ILI9341_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void drawDot(uint16_t x, uint16_t y, uint16_t color);
void draw7Segment(uint16_t x, uint16_t y, uint8_t number, uint16_t color);
void ILI9341_DrawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bgcolor, uint8_t size);
void ILI9341_DrawText(uint16_t x, uint16_t y, char *text, uint16_t color, uint16_t bgcolor, uint8_t size);

#endif /*__TFT__*/
