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

// External 8MHz crystal with internal PLL for 72MHz system clock
#define HT32_HSE_FREQUENCY          8000000UL                                   // 8 MHz
#define HT32_PLL_FBDIV              18
#define HT32_CK_SYS_FREQUENCY       HT32_HSE_FREQUENCY * HT32_PLL_FBDIV         // 144 MHz
#define HT32_AHB_PRESCALER          2
#define HT32_CK_AHB_FREQUENCY       HT32_CK_SYS_FREQUENCY / HT32_AHB_PRESCALER  // 72 MHz
#define HT32_USB_PRESCALER          3
#define HT32_STCLK_FREQUENCY        HT32_CK_AHB_FREQUENCY / 1                   // 72 MHz

/*
 * USB driver settings
 */

#define HT32_USB_USE_USB0                   TRUE
#define HT32_USB_USB0_IRQ_PRIORITY          5

#define HT32_PWM_USE_MCTM0                  TRUE

#endif /* _MCUCONF_H_ */
