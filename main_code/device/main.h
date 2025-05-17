#ifndef __MAIN__
#define __MAIN__

/* Include standard headers */
#include <stdio.h>      /* Standard input/output */
#include <stdint.h>     /* Standard integer types */
#include <stdlib.h>     /* Standard library functions */
#include <string.h>     /* String handling */
#include <ctype.h>      /* Character handling */
#include <math.h>       /* Math functions */

/* Include device-specific headers from STM32 SPL */
#include <stm32f10x.h>          /* Device header */
#include <stm32f10x_rcc.h>      /* RCC configuration */
#include <stm32f10x_gpio.h>     /* GPIO configuration */
#include <stm32f10x_flash.h>    /* Flash memory configuration */

/* Include application-specific modules */
#include "os.h"         /* OS abstraction or scheduler */
#include "timer.h"      /* Timer utilities */
#include "adc.h"        /* ADC drivers */
#include "tft.h"        /* TFT display drivers */
#include "touch.h"      /* Touch screen drivers */
#include "button.h"     /* Button input handling */
#include "com.h"        /* Communication interface */
#include "sdcard.h"     /* SD card interface */
#include "fonts.h"      /* Font definitions */

/* Time quantum for scheduler loop (in milliseconds) */
#define quanta 1U  /* MISRA: Suffix U for unsigned constants */

/* Structure to enable/disable specific peripherals */
typedef struct
{
    uint8_t Ranges;     /* Enable range selector */
    uint8_t Frequency;  /* Enable frequency counter */
    uint8_t Uart;       /* Enable UART communication */
    uint8_t SD;         /* Enable SD card storage */
    uint8_t Graph;      /* Enable graphical output */
} Enable_Peripheral;

/* Function Prototypes */

/**
 * @brief Initialize system clocks and RCC configuration.
 */
void RCC_Clock_Init(void);

/**
 * @brief Extracts the first 4 digits of a float number for display.
 * @param[in] so: Float value to process.
 * @param[out] out: Array of 4 digits extracted from 'so'.
 */
void tach_4_chu_so_dau(float so, uint8_t out[4]);

/**
 * @brief Initializes display and peripherals for measurement.
 * @param[in] dev: Pointer to peripheral enable configuration.
 * @param[in] val: Initial float value to display.
 * @param[out] out: Processed digits of 'val' to be displayed.
 */
void Display_Init(Enable_Peripheral *dev, float val, uint8_t out[4]);

/**
 * @brief Draw the full display interface.
 */
void Draw_Display(void);

/**
 * @brief Check status of buttons and trigger actions.
 */
void Check_Button(void);

/**
 * @brief Read sensor data and prepare for display or transmission.
 */
void Read_Sensor(void);

/**
 * @brief Send processed data to connected PC via UART.
 */
void Transmit_To_PC(void);

/**
 * @brief Save current data to SD card.
 */
void SD_Save_Data(void);

/**
 * @brief Entry point of the firmware application.
 * @return Returns 0 (not used in embedded context).
 */
int main(void);

#endif /* __MAIN__ */