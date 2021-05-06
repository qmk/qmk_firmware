// based on lib/chibios-contrib/demos/KINETIS/RT-TEENSY3_6/mcuconf.h:
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

#define MK66FX1M0_MCUCONF

/*
 * HAL driver system settings.
 */

/* Select the MCU clocking mode below by enabling the appropriate block. */

/* PEE mode - 180 MHz system clock driving by 16 MHz xtal */
#define KINETIS_MCG_MODE KINETIS_MCG_MODE_PEE
//#define KINETIS_PLLCLK_FREQUENCY 180000000UL  // 180 MHz (HSRUN)
#define KINETIS_PLLCLK_FREQUENCY 120000000UL  // 120 MHz (RUN)
#define KINETIS_SYSCLK_FREQUENCY KINETIS_PLLCLK_FREQUENCY
#define KINETIS_BUSCLK_FREQUENCY 60000000UL
//#define KINETIS_FLASHCLK_FREQUENCY 28000000UL  // 28 MHz (HSRUN)
#define KINETIS_FLASHCLK_FREQUENCY 24000000UL  // 24 MHz (RUN)

#if KINETIS_PLLCLK_FREQUENCY == 180000000UL
#    define KINETIS_CLKDIV1_OUTDIV1 1  // -> 0
#    define KINETIS_CLKDIV1_OUTDIV2 3  // -> 2
#    define KINETIS_CLKDIV1_OUTDIV4 7  // -> 6
#else
#    define KINETIS_CLKDIV1_OUTDIV1 1  // -> 0
#    define KINETIS_CLKDIV1_OUTDIV2 2  // -> 1
#    define KINETIS_CLKDIV1_OUTDIV4 5  // -> 4
#endif

/*
 * SERIAL driver system settings.
 */
#define KINETIS_SERIAL_USE_UART4 TRUE

/*
 * USB driver settings
 */
#define KINETIS_USB_USE_USB0 TRUE
#define KINETIS_USB_USB0_IRQ_PRIORITY 5

/*
 * I2C driver settings
 */
#define KINETIS_I2C_USE_I2C0 TRUE
#define KINETIS_I2C_I2C0_PRIORITY 4

#endif /* _MCUCONF_H_ */
