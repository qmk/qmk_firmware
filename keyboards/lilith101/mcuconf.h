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

#define K20x_MCUCONF

/*
 * HAL driver system settings.
 */
#if 1
/* PEE mode - 48MHz system clock driven by (16 MHz) external crystal. */
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_PEE
#define KINETIS_PLLCLK_FREQUENCY    72000000UL
#define KINETIS_SYSCLK_FREQUENCY    72000000UL
#define KINETIS_BUSCLK_FREQUENCY    36000000UL
#define KINETIS_FLASHCLK_FREQUENCY  24000000UL
#endif

#if 0
/* crystal-less FEI mode - 48 MHz with internal 32.768 kHz crystal */
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_FEI
#define KINETIS_MCG_FLL_DMX32       1           /* Fine-tune for 32.768 kHz */
#define KINETIS_MCG_FLL_DRS         1           /* 1464x FLL factor */
#define KINETIS_SYSCLK_FREQUENCY    47972352UL  /* 32.768 kHz * 1464 (~48 MHz) */
#define KINETIS_CLKDIV1_OUTDIV1     1           /* do not divide system clock */
#endif

/*
 * SERIAL driver system settings.
 */
#define KINETIS_SERIAL_USE_UART0              TRUE

/*
 * USB driver settings
 */
#define KINETIS_USB_USE_USB0                  TRUE
/* Need to redefine this, since the default is for K20x */
/* This is for Teensy LC; you should comment it out (or change to 5)
 * for Teensy 3.x */
#define KINETIS_USB_USB0_IRQ_PRIORITY         5


/*
 * I2C driver settings
 */
#define KINETIS_I2C_USE_I2C1                TRUE
#define KINETIS_I2C_I2C1_PRIORITY           4

//#define STM32_I2C_USE_I2C1                TRUE


#endif /* _MCUCONF_H_ */
