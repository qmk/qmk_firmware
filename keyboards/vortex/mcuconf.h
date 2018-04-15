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

#ifndef _MCUCONF_H_
#define _MCUCONF_H_

#include "nvic.h"

#define HT32_MCUCONF

/*
 * HAL driver system settings.
 */

/*
 * Clock configuration.
 */

// This configuration:
// 8 MHz HSE crystal
// PLL multiplies HSE to 72 MHz core and peripheral clock
// 72 MHz to UART
// 48 MHz to USB

#define HT32_CK_HSE_FREQUENCY   8000000UL           // 8 MHz
#define HT32_CKCU_SW            CKCU_GCCR_SW_PLL
#define HT32_PLL_USE_HSE        TRUE
#define HT32_PLL_FBDIV          18                  // 8 MHz -> 144 MHz
#define HT32_PLL_OTDIV          0
#define HT32_AHB_PRESCALER      2                   // 144 MHz -> 72 MHz
#define HT32_USART_PRESCALER    1                   // 72 MHz
#define HT32_USB_PRESCALER      3                   // 144 MHz -> 48 MHz
// SysTick uses processor clock at 72MHz
#define HT32_ST_USE_HCLK        TRUE

/*
 * Peripheral driver settings
 */

#define HT32_SPI_USE_SPI1                   TRUE
#define HT32_SPI1_IRQ_PRIORITY              5

#define HT32_UART_USE_USART0                TRUE
#define HT32_USART0_IRQ_PRIORITY            5

/*
 * USB driver settings
 */

#define HT32_USB_USE_USB0                   TRUE
#define HT32_USB_USB0_IRQ_PRIORITY          5

#define HT32_PWM_USE_MCTM0                  TRUE

#endif /* _MCUCONF_H_ */
