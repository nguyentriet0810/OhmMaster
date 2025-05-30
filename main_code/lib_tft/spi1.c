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
#include "spi1.h"

void Spi1_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;
    SPI_InitTypeDef SPI_InitStruct;
    DMA_InitTypeDef DMA_InitStruct;

    // 1. Enable Clock cho SPI1, GPIOA và DMA1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // B?t clock cho DMA1

    // 2. C?u hình chân SPI1 (SCK, MISO, MOSI)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;  // Ch? d? Alternate Function Push-Pull
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 3. C?u hình các chân CS, RESET, D/C là OUTPUT
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  // Ch? d? Output Push-Pull
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 4. C?u hình SPI1
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;  // Ði?u khi?n CS b?ng ph?n m?m
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // 72MHz / 4 = 18MHz
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStruct);

    // 5. Kích ho?t SPI1
    SPI_Cmd(SPI1, ENABLE);

    // 6. Thi?t l?p tr?ng thái m?c d?nh cho GPIO di?u khi?n
    GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3); // CS, RESET, D/C = HIGH

    // 7. C?u hình DMA cho SPI1_TX (DMA1 Channel 3 trên STM32F1)
    DMA_DeInit(DMA1_Channel3); // Reset DMA1 Channel 3 (SPI1_TX)
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&SPI1->DR; // Ð?a ch? thanh ghi d? li?u SPI1
    DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)0; // Ð?a ch? b? nh? s? du?c c?p nh?t sau
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST; // Truy?n t? Memory -> Peripheral
    DMA_InitStruct.DMA_BufferSize = 0; // Kích thu?c buffer, s? du?c c?p nh?t sau
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // Không tang d?a ch? peripheral
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable; // Tang d?a ch? b? nh?
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // Kích thu?c d? li?u 8-bit
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; // Kích thu?c d? li?u 8-bit
    DMA_InitStruct.DMA_Mode = DMA_Mode_Normal; // Ch? d? Normal (không vòng l?p)
    DMA_InitStruct.DMA_Priority = DMA_Priority_High; // Ð? uu tiên cao
    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable; // Không ph?i Memory-to-Memory
    DMA_Init(DMA1_Channel3, &DMA_InitStruct);

    // 8. Kích ho?t DMA request t? SPI1_TX
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
}

void Spi1_SetSpeed(uint16_t prescaler) {
    SPI1->CR1 &= ~SPI_BaudRatePrescaler_256; // Clear bits
    SPI1->CR1 |= prescaler;                  // Set new prescaler
    SPI_Cmd(SPI1, ENABLE);                   // Enable l?i SPI n?u c?n
}

// Hàm truy?n d? li?u qua SPI1 b?ng DMA
void Spi1_DmaTransmit(uint8_t* data, uint16_t size) {
    // C?p nh?t d?a ch? b? nh? và kích thu?c buffer
    DMA1_Channel3->CMAR = (uint32_t)data; // Ð?a ch? d? li?u c?n truy?n
    DMA1_Channel3->CNDTR = size; // S? byte c?n truy?n

    // Kích ho?t DMA
    DMA_Cmd(DMA1_Channel3, ENABLE);

    // Ch? truy?n hoàn t?t (có th? dùng ng?t thay th?)
    while (DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC3); // Xóa c? hoàn t?t
    DMA_Cmd(DMA1_Channel3, DISABLE); // T?t DMA sau khi truy?n xong
}

uint8_t Spi1_SendByte(uint8_t data) {
    // Ð?i TXE (TX buffer empty) d? d?m b?o có th? g?i d? li?u
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    
    // G?i d? li?u qua SPI
    SPI_I2S_SendData(SPI1, data);
    
    // Ð?i RXNE (RX buffer not empty) d? d?m b?o d? li?u dã du?c nh?n
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    
    // Ð?c và tr? v? d? li?u nh?n du?c t? SPI
    return SPI_I2S_ReceiveData(SPI1);
}
void Spi1_SendBuffer(uint8_t *buffer, uint16_t length) {
    for (uint16_t i = 0; i < length; i++) {
        Spi1_SendByte(buffer[i]);
    }
}
uint8_t Spi1_ReceiveByte(void) {
    return Spi1_SendByte(0xFF); // G?i 0xFF d? nh?n d? li?u
}
void Spi1_ReceiveBuffer(uint8_t *buffer, uint16_t length) {
    for (uint16_t i = 0; i < length; i++) {
        buffer[i] = Spi1_ReceiveByte();
    }
}
