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
#include "iic.h"

void IIC2_GPIO_Init(void) {
    // B?t clock cho GPIOB và AFIO (n?u c?n)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    // Reset I2C2 d? tránh l?i treo
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);

    // Ð?t m?c cao tru?c khi chuy?n ch? d? sang AF_OD
    GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);

    GPIO_InitTypeDef GPIO_InitStructure;
    
    // C?u hình PB10 (SCL) và PB11 (SDA) là Alternate Function Open-Drain
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void IIC2_Init(void) {	
	  I2C_InitTypeDef I2C_InitStructure;
  // B?t clock cho GPIOB và AFIO
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  // Reset I2C2 d? tránh l?i treo
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);

  // Ð?t m?c cao tru?c khi chuy?n ch? d? sang AF_OD
  GPIO_SetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11);

  GPIO_InitTypeDef GPIO_InitStructure;
    
  // C?u hình PB10 (SCL) và PB11 (SDA) là Alternate Function Open-Drain
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// B?t clock cho I2C2
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	
  // C?u hình I2C2
  I2C_DeInit(I2C2);
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = 100000; // 100kHz
  I2C_Init(I2C2, &I2C_InitStructure);

  // B?t I2C2
  I2C_Cmd(I2C2, ENABLE);
}

void IIC2_Write(uint8_t deviceAddr, uint8_t regAddr, uint16_t data) {
    // 1. Ð?i bus r?nh
    while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));

    // 2. G?i START
    I2C_GenerateSTART(I2C2, ENABLE);
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

    // 3. G?i d?a ch? slave (ghi)
    I2C_Send7bitAddress(I2C2, deviceAddr << 1, I2C_Direction_Transmitter);
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);

    // 4. G?i d?a ch? thanh ghi
    I2C_SendData(I2C2, regAddr);
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);

    // 5. G?i byte MSB
    I2C_SendData(I2C2, (uint8_t)(data >> 8));
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);

    // 6. G?i byte LSB
    I2C_SendData(I2C2, (uint8_t)(data & 0xFF));
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);

    // 7. G?i STOP
    I2C_GenerateSTOP(I2C2, ENABLE);
}
uint16_t IIC2_Read(uint8_t deviceAddr, uint8_t regAddr) {
    uint16_t data = 0;

    // 1. Ð?i bus r?nh
    while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));

    // 2. G?i START d? ghi d?a ch? thanh ghi
    I2C_GenerateSTART(I2C2, ENABLE);
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

    // 3. G?i d?a ch? slave (ghi)
    I2C_Send7bitAddress(I2C2, deviceAddr << 1, I2C_Direction_Transmitter);
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS);

    // 4. G?i d?a ch? thanh ghi mu?n d?c
    I2C_SendData(I2C2, regAddr);
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS);

    // 5. G?i l?nh START l?i (repeated start)
    I2C_GenerateSTART(I2C2, ENABLE);
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS);

    // 6. G?i d?a ch? slave (d?c)
    I2C_Send7bitAddress(I2C2, deviceAddr << 1, I2C_Direction_Receiver);
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS);

    // 7. Ð?c byte MSB
    I2C_AcknowledgeConfig(I2C2, ENABLE);
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
    data = I2C_ReceiveData(I2C2) << 8;

    // 8. Ð?c byte LSB, không ACK
    I2C_AcknowledgeConfig(I2C2, DISABLE);
    while (I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS);
    data |= I2C_ReceiveData(I2C2);

    // 9. STOP
    I2C_GenerateSTOP(I2C2, ENABLE);

    return data;
}
