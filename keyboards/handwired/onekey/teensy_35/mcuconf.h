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

#define K60x_MCUCONF

/*
 * HAL driver system settings.
 */

/* Select the MCU clocking mode below by enabling the appropriate block. */

/* PEE mode - 120MHz system clock driven by external crystal. */
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_PEE
#define KINETIS_PLLCLK_FREQUENCY    120000000UL  // 120 MHz (RUN)
#define KINETIS_SYSCLK_FREQUENCY    KINETIS_PLLCLK_FREQUENCY
#define KINETIS_BUSCLK_FREQUENCY    60000000UL
#define KINETIS_FLASHCLK_FREQUENCY  24000000UL  // 24 MHz (RUN)

#define KINETIS_CLKDIV1_OUTDIV1 1  // -> 0
#define KINETIS_CLKDIV1_OUTDIV2 2  // -> 1
#define KINETIS_CLKDIV1_OUTDIV4 5  // -> 4

/*
 * SERIAL driver system settings.
 */
#define KINETIS_SERIAL_USE_UART0              TRUE

/*
 * USB driver settings
 */
#define KINETIS_USB_USE_USB0                  TRUE
#define KINETIS_USB_USB0_IRQ_PRIORITY         5

#endif /* _MCUCONF_H_ */
