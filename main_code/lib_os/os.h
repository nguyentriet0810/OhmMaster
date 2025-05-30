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
#ifndef __OS__
#define __OS__

#include <stm32f10x.h>

#include <stdint.h>

//khai bao so thread toi da co the co trong os
#define NUM_OF_THREADS	6
//khai bao vung stack cho moi thread
#define STACK_SIZE 			250

//khoi tao tan so cho systick	
#define BUS_FREQ 			72000000

//tao macro de bat ngat cho systick
#define INTCTRL (*((volatile uint32_t *)0XE000ED04))
#define PENDSTSET   (1<<26)

void osKernelInit(void);
void osKernelLaunch(uint8_t quanta);
void osSchedulerLaunch(void);
void osKernelStackInit(int i);
uint8_t osKernelAdd1Thread(void (*task)(void));
void osSchedulerRoundRobin(void);
void osThreadYield(void);
void osSemaphore_Init(uint8_t *semaphore, uint8_t val);
void osSemaphore_Give(uint8_t *semaphore);
void osCooperative_Wait(uint8_t *semaphore);
void osThreadsSleep(uint32_t sleeptime);

#endif /*__OS__*/
