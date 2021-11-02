/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#pragma once

#include "nvic.h"

#define HT32F52342_MCUCONF

/*
 * HAL driver system settings.
 */

/*
 * Clock configuration.
 */

// This configuration:
// 8 MHz HSE crystal
// PLL multiplies HSE to 48 MHz core and peripheral clock
// 48 MHz to UART
// 48 MHz to USB

#define HT32_CK_HSE_FREQUENCY 8000000UL  // 8 MHz
#define HT32_CKCU_SW CKCU_GCCR_SW_PLL
#define HT32_PLL_USE_HSE TRUE
#define HT32_PLL_FBDIV 6  // 8 MHz -> 48 MHz
#define HT32_PLL_OTDIV 0
#define HT32_AHB_PRESCALER 1    // 48 MHz -> 48 MHz
#define HT32_USART_PRESCALER 1  // 48 MHz
#define HT32_USB_PRESCALER 1    // 48 MHz -> 48 MHz
// SysTick uses processor clock at 48MHz
#define HT32_ST_USE_HCLK TRUE

/*
 * Peripheral driver settings
 */

#define HT32_SERIAL_USE_USART0 TRUE
#define HT32_USART0_IRQ_PRIORITY 6

#define HT32_SERIAL_USE_USART1 TRUE
#define HT32_USART1_IRQ_PRIORITY 7

/*
 * USB driver settings
 */

#define HT32_USB_USE_USB0 TRUE
#define HT32_USB_USB0_IRQ_PRIORITY 5
