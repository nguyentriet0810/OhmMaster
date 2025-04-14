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
