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
#include "tft.h"


void ILI9341_SendCommand(uint8_t cmd) {
	ILI9341_CS_LOW();
  ILI9341_DC_LOW();  // Ch? d? Command
  Spi1_SendByte(cmd);
  ILI9341_CS_HIGH();
}

void ILI9341_SendData(uint8_t data) {
  ILI9341_CS_LOW();
  ILI9341_DC_HIGH(); // Ch? d? Data
  Spi1_SendByte(data);
  ILI9341_CS_HIGH();
}

void ILI9341_Reset(void) {
  // Hardware Reset
  ILI9341_RST_LOW();
  Timer3_Delay_ms(10);   //low in 10m
  ILI9341_RST_HIGH();
  Timer3_Delay_ms(120);  //waitting

  //send reset command
  ILI9341_SendCommand(0x01); // L?nh RESET
  Timer3_Delay_ms(5);  // Ch? màn hình x? lý
}

void ILI9341_Init(void) {
  ILI9341_Reset();  // Reset màn hình

  // L?nh Sleep Out - B?t bu?c tru?c khi c?u hình
  ILI9341_SendCommand(0x11); // Sleep Out
  Timer3_Delay_ms(120);  // Ch? màn hình thoát ch? d? Sleep

  // Power Control
  ILI9341_SendCommand(0xC0);
  ILI9341_SendData(0x23);

  ILI9341_SendCommand(0xC1);
  ILI9341_SendData(0x10);

  // VCOM Control
  ILI9341_SendCommand(0xC5);
  ILI9341_SendData(0x3E);
  ILI9341_SendData(0x28);

  ILI9341_SendCommand(0xC7);
  ILI9341_SendData(0x86);

  // Memory Access Control
  ILI9341_SendCommand(0x36);
  ILI9341_SendData(0xE8);  // Hu?ng quét màn hình (0x48: M?c d?nh)

  // Pixel Format Set (Ch?n 16-bit màu RGB565)
  ILI9341_SendCommand(0x3A);
  ILI9341_SendData(0x55);

  // Frame Rate Control
  ILI9341_SendCommand(0xB1);
  ILI9341_SendData(0x00);
  ILI9341_SendData(0x18);

  // Display Function Control
  ILI9341_SendCommand(0xB6);
  ILI9341_SendData(0x08);
  ILI9341_SendData(0x82);
  ILI9341_SendData(0x27);

  // 3G Gamma Control
  ILI9341_SendCommand(0xF2);
  ILI9341_SendData(0x00);

  // Gamma Set
  ILI9341_SendCommand(0x26);
  ILI9341_SendData(0x01);

  // Positive Gamma Correction
  ILI9341_SendCommand(0xE0);
  ILI9341_SendData(0x0F); ILI9341_SendData(0x31); ILI9341_SendData(0x2B);
  ILI9341_SendData(0x0C); ILI9341_SendData(0x0E); ILI9341_SendData(0x08);
  ILI9341_SendData(0x4E); ILI9341_SendData(0xF1); ILI9341_SendData(0x37);
  ILI9341_SendData(0x07); ILI9341_SendData(0x10); ILI9341_SendData(0x03);
  ILI9341_SendData(0x0E); ILI9341_SendData(0x09); ILI9341_SendData(0x00);

  // Negative Gamma Correction
  ILI9341_SendCommand(0xE1);
  ILI9341_SendData(0x00); ILI9341_SendData(0x0E); ILI9341_SendData(0x14);
  ILI9341_SendData(0x03); ILI9341_SendData(0x11); ILI9341_SendData(0x07);
  ILI9341_SendData(0x31); ILI9341_SendData(0xC1); ILI9341_SendData(0x48);
  ILI9341_SendData(0x08); ILI9341_SendData(0x0F); ILI9341_SendData(0x0C);
  ILI9341_SendData(0x31); ILI9341_SendData(0x36); ILI9341_SendData(0x0F);

  // Display ON
  ILI9341_SendCommand(0x29);
}
void ILI9341_SetAddressWindow(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
  // Ch?n vùng c?t (X)
  ILI9341_SendCommand(0x2A);
  ILI9341_SendData(x1 >> 8); ILI9341_SendData(x1 & 0xFF);
  ILI9341_SendData(x2 >> 8); ILI9341_SendData(x2 & 0xFF);

  // Ch?n vùng hàng (Y)
  ILI9341_SendCommand(0x2B);
  ILI9341_SendData(y1 >> 8); ILI9341_SendData(y1 & 0xFF);
  ILI9341_SendData(y2 >> 8); ILI9341_SendData(y2 & 0xFF);

  // L?nh ghi d? li?u vào b? nh? GRAM
  ILI9341_SendCommand(0x2C);
}
void ILI9341_FillScreen(uint16_t color) {
  uint32_t totalPixels = 320 * 240;  // T?ng s? pixel màn hình
  ILI9341_SetAddressWindow(0, 0, 319, 239); // Ch?n toàn b? màn hình
  ILI9341_CS_LOW();
  ILI9341_DC_HIGH();  // Ch? d? g?i d? li?u

  for (uint32_t i = 0; i < totalPixels; i++) {
		Spi1_SendByte(color >> 8);  // G?i byte cao
    Spi1_SendByte(color & 0xFF); // G?i byte th?p
  }

  ILI9341_CS_HIGH();
}
void ILI9341_SetRotation(uint8_t rotation) {
  uint8_t madctl = 0;

  switch (rotation) {
		case 0:  // 0° (m?c d?nh, d?c)
			madctl = 0x48;
      break;
    case 1:  // 90° (xoay ph?i)
      madctl = 0x28;
      break;
    case 2:  // 180° (ngu?c)
      madctl = 0x88;
      break;
    case 3:  // 270° (xoay trái)
      madctl = 0xE8;
      break;
    default:
      return; // N?u sai giá tr?, không làm gì
	}
  ILI9341_SendCommand(0x36); // set command
  ILI9341_SendData(madctl);
}
void ILI9341_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    if (x >= 320 || y >= 240) return; // Gi?i h?n màn hình

    ILI9341_SetAddressWindow(x, y, x, y);
    ILI9341_CS_LOW();
    ILI9341_DC_HIGH();
    Spi1_SendByte(color >> 8);
    Spi1_SendByte(color & 0xFF);
    ILI9341_CS_HIGH();
}

void ILI9341_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
    int16_t dx = abs(x2 - x1);  // Kho?ng cách theo x
    int16_t dy = abs(y2 - y1);  // Kho?ng cách theo y
    int16_t sx = (x1 < x2) ? 1 : -1;  // Hu?ng x
    int16_t sy = (y1 < y2) ? 1 : -1;  // Hu?ng y
    int16_t err = dx - dy;  // Sai s? ban d?u

    while (1) {
        // V? pixel t?i v? trí hi?n t?i
        ILI9341_DrawPixel(x1, y1, color);

        // Ki?m tra n?u dã d?n di?m cu?i
        if (x1 == x2 && y1 == y2) break;

        int16_t e2 = 2 * err;
        if (e2 > -dy) {  // Sai s? theo x
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {  // Sai s? theo y
            err += dx;
            y1 += sy;
        }
    }
}
void ILI9341_DrawIntro(void) {
	for (uint16_t y = 239; y > 1; y--) {
		ILI9341_DrawLine(0,0,319,y,0xFFFF);
	}
	for (uint16_t i = 319; i > 1; i--) {
		ILI9341_DrawLine(0,0,i,239,0xF800);
	}
}
void ILI9341_DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
    // 1. Thi?t l?p vùng c?t (x)
    ILI9341_SendCommand(ILI9341_CASET);
    ILI9341_SendData((x >> 8) & 0xFF);        // X b?t d?u (byte cao)
    ILI9341_SendData(x & 0xFF);               // X b?t d?u (byte th?p)
    ILI9341_SendData(((x + width - 1) >> 8) & 0xFF); // X k?t thúc (byte cao)
    ILI9341_SendData((x + width - 1) & 0xFF); // X k?t thúc (byte th?p)

    // 2. Thi?t l?p vùng hàng (y)
    ILI9341_SendCommand(ILI9341_RASET);
    ILI9341_SendData((y >> 8) & 0xFF);        // Y b?t d?u (byte cao)
    ILI9341_SendData(y & 0xFF);               // Y b?t d?u (byte th?p)
    ILI9341_SendData(((y + height - 1) >> 8) & 0xFF); // Y k?t thúc (byte cao)
    ILI9341_SendData((y + height - 1) & 0xFF); // Y k?t thúc (byte th?p)

    // 3. G?i l?nh ghi d? li?u vào RAM
    ILI9341_SendCommand(ILI9341_RAMWR);

    // 4. G?i d? li?u màu cho toàn b? vùng (width × height pixel)
    uint32_t totalPixels = (uint32_t)width * height; // T?ng s? pixel
    ILI9341_CS_LOW();
		ILI9341_DC_HIGH();
    for (uint32_t i = 0; i < totalPixels; i++) {
        Spi1_SendByte(color >> 8);  // G?i byte cao
				Spi1_SendByte(color & 0xFF); // G?i byte th?p
    }
    ILI9341_CS_HIGH();
}

void drawDot(uint16_t x, uint16_t y, uint16_t color) {
    ILI9341_DrawRectangle(x, y, 5, 5, color); // D?u ch?m d?ng hình vuông nh?
}

void draw7Segment(uint16_t x, uint16_t y, uint8_t number, uint16_t color) {
    bool segments[7] = {0}; // a, b, c, d, e, f, g
    switch (number) {
      case  0: segments[0] = 1; segments[1] = 1; segments[2] = 1; segments[3] = 1; segments[4] = 1; segments[5] = 1; segments[6] = 0; break; // 0
      case  1: segments[0] = 0; segments[1] = 1; segments[2] = 1; segments[3] = 0; segments[4] = 0; segments[5] = 0; segments[6] = 0; break; // 1
      case  2: segments[0] = 1; segments[1] = 1; segments[2] = 0; segments[3] = 1; segments[4] = 1; segments[5] = 0; segments[6] = 1; break; // 2
      case  3: segments[0] = 1; segments[1] = 1; segments[2] = 1; segments[3] = 1; segments[4] = 0; segments[5] = 0; segments[6] = 1; break; // 3
      case  4: segments[0] = 0; segments[1] = 1; segments[2] = 1; segments[3] = 0; segments[4] = 0; segments[5] = 1; segments[6] = 1; break; // 4
      case  5: segments[0] = 1; segments[1] = 0; segments[2] = 1; segments[3] = 1; segments[4] = 0; segments[5] = 1; segments[6] = 1; break; // 5
      case  6: segments[0] = 1; segments[1] = 0; segments[2] = 1; segments[3] = 1; segments[4] = 1; segments[5] = 1; segments[6] = 1; break; // 6
      case  7: segments[0] = 1; segments[1] = 1; segments[2] = 1; segments[3] = 0; segments[4] = 0; segments[5] = 0; segments[6] = 0; break; // 7
      case  8: segments[0] = 1; segments[1] = 1; segments[2] = 1; segments[3] = 1; segments[4] = 1; segments[5] = 1; segments[6] = 1; break; // 8
      case  9: segments[0] = 1; segments[1] = 1; segments[2] = 1; segments[3] = 1; segments[4] = 0; segments[5] = 1; segments[6] = 1; break; // 9
			case 10: segments[0] = 0; segments[1] = 0; segments[2] = 0; segments[3] = 1; segments[4] = 1; segments[5] = 1; segments[6] = 0; break; // L
			case 11: segments[0] = 0; segments[1] = 0; segments[2] = 0; segments[3] = 0; segments[4] = 0; segments[5] = 0; segments[6] = 0; break; // Disable all
			default : break;
    }

    // Kích thu?c ch? s?: rong 60, cao 100, do day doan 5
    uint8_t thickness = 5;
    if (segments[0]) {
			//ILI9341_DrawRectangle(x + 5  , y - 5  , 50       , thickness    , BLACK);       // a: ngang trên
			ILI9341_DrawRectangle(x + 5  , y      , 50       , thickness    , color);       // a: ngang trên
			ILI9341_DrawRectangle(x + 5  , y + 5  , 50       , thickness    , BLACK);       // a: ngang trên
		}	else {
			ILI9341_DrawRectangle(x + 5  , y      , 50       , thickness + 9, BLACK);
		}
    if (segments[1]) {
			ILI9341_DrawRectangle(x + 55 , y + 5  , thickness, 50           , color);       // b: phai trên
		}	else {
			ILI9341_DrawRectangle(x + 55 , y + 5  , thickness, 50           , BLACK);
		}
    if (segments[2]) {
			ILI9341_DrawRectangle(x + 55 , y + 60 , thickness, 50           , color);       // c: phai duoi
		}	else {
			ILI9341_DrawRectangle(x + 55 , y + 60 , thickness, 50           , BLACK);
		}
    if (segments[3]) {
			//ILI9341_DrawRectangle(x + 5  , y + 105, 50       , thickness    , BLACK);       // d: ngang duoi
			ILI9341_DrawRectangle(x + 5  , y + 110, 50       , thickness    , color);       // d: ngang duoi
			ILI9341_DrawRectangle(x + 5  , y + 115, 50       , thickness    , BLACK);       // d: ngang duoi
		}	else {
			ILI9341_DrawRectangle(x + 5  , y + 110, 50       , thickness + 4, BLACK);
		}
    if (segments[4]) {
			ILI9341_DrawRectangle(x      , y + 60 , thickness, 50           , color);       // e: trái duoi
		}	else {
			ILI9341_DrawRectangle(x      , y + 60 , thickness, 50           , BLACK);
		}
    if (segments[5]) {
			ILI9341_DrawRectangle(x      , y + 5  , thickness, 50           , color);       // f: trái trên
		}	else {
			ILI9341_DrawRectangle(x      , y + 5  , thickness, 50           , BLACK);
		}
		if (segments[6]) {
			//ILI9341_DrawRectangle(x + 5  , y + 50 , 50       , thickness    , BLACK);       // g: ngang giua
			ILI9341_DrawRectangle(x + 5  , y + 55 , 50       , thickness    , color);       // g: ngang giua
			ILI9341_DrawRectangle(x + 5  , y + 60 , 50       , thickness    , BLACK);       // g: ngang giua
		}	else	{
			ILI9341_DrawRectangle(x + 5  , y + 55 , 50       , thickness + 9, BLACK);
		}
}

void ILI9341_DrawChar(uint16_t x, uint16_t y, char c, uint16_t color, uint16_t bgcolor, uint8_t size) {
    if (c < 32 || c > 126) return;
    c -= 32;

    uint16_t scaled_size = size;  // Ép ki?u d? tránh tràn s?
    uint16_t base_x, base_y;

    for (uint8_t i = 0; i < 5; i++) {
        uint8_t line = font5x8[c][i];
        base_x = x + (i * scaled_size);

        for (uint8_t j = 0; j < 8; j++) {
            base_y = y + (j * scaled_size);
            uint16_t pixel_color = (line & (1 << j)) ? color : bgcolor;

            // V? t?t c? pixel, không b? qua b?t k? pixel nào
            for (uint8_t sx = 0; sx < scaled_size; sx++) {
                uint16_t current_x = base_x + sx;
                for (uint8_t sy = 0; sy < scaled_size; sy++) {
                    ILI9341_DrawPixel(current_x, base_y + sy, pixel_color);
                }
            }
        }
    }
}
void ILI9341_DrawText(uint16_t x, uint16_t y, char *text, uint16_t color, uint16_t bgcolor, uint8_t size) {
    while (*text) {
        ILI9341_DrawChar(x, y, *text, color, bgcolor, size);
        x += 6 * size; // D?ch chuy?n theo kích thu?c m?i
        text++;
    }
}

void DrawPixelFrom16BitHex(uint16_t x, uint16_t y, uint16_t hexValue) {
    // V? 16 pixel theo chi?u ngang d?a trên 16 bit c?a hexValue
    for (int i = 0; i < 16; i++) {
        // Ki?m tra t?ng bit t? trái sang ph?i (MSB d?n LSB)
        uint16_t bit = (hexValue >> (15 - i)) & 0x0001;
        
        // Ch? v? pixel n?u bit = 1
        if (bit) {
            // Ki?m tra gi?i h?n màn hình
            if ((x + i) >= 320 || y >= 240) continue;

            ILI9341_SetAddressWindow(x + i, y, x + i, y);
            ILI9341_CS_LOW();
            ILI9341_DC_HIGH();
            // Màu tr?ng (0xFFFF) cho pixel du?c v?
            Spi1_SendByte(0xFF);
            Spi1_SendByte(0xFF);
            ILI9341_CS_HIGH();
        }
    }
}

