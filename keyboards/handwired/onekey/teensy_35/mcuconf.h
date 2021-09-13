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

/* PEE mode - 48MHz system clock driven by external crystal. */
#if 1
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_PEE
#define KINETIS_PLLCLK_FREQUENCY    96000000UL
#define KINETIS_SYSCLK_FREQUENCY    48000000UL
#endif

/* FEI mode (~48MHz) */
#if 0
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_FEI
#define KINETIS_MCG_FLL_DMX32       1           /* Fine-tune for 32.768 kHz */
#define KINETIS_MCG_FLL_DRS         1           /* 1464x FLL factor */
#define KINETIS_SYSCLK_FREQUENCY    47972352UL  /* 32.768 kHz * 1464 (~48 MHz) */
#define KINETIS_CLKDIV1_OUTDIV1     1           /* Divide MCGCLKOUT (~48MHz) by 1 to SYSCLK */
#define KINETIS_CLKDIV1_OUTDIV2     1           /* Divide by 1 for (~48MHz) peripheral clock */
#define KINETIS_CLKDIV1_OUTDIV4     2           /* Divide by 2 for (~24MHz) flash clock */
#define KINETIS_BUSCLK_FREQUENCY    KINETIS_SYSCLK_FREQUENCY
#define KINETIS_FLASHCLK_FREQUENCY  KINETIS_SYSCLK_FREQUENCY/2
#endif /* 0 */

/* FEE mode - 24 MHz with external 32.768 kHz crystal */
/* not implemented */
#if 0
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_FEE
#define KINETIS_MCG_FLL_DMX32       1           /* Fine-tune for 32.768 kHz */
#define KINETIS_MCG_FLL_DRS         0           /* 732x FLL factor */
#define KINETIS_CLKDIV1_OUTDIV1     1           /* Divide 48 MHz FLL by 1 => 24 MHz */
#define KINETIS_CLKDIV1_OUTDIV4     2           /* Divide OUTDIV1 output by 2 => 12 MHz */
#define KINETIS_SYSCLK_FREQUENCY    23986176UL  /* 32.768 kHz*732 (~24 MHz) */
#define KINETIS_UART0_CLOCK_FREQ    (32768 * 732) /* FLL output */
#define KINETIS_UART0_CLOCK_SRC     1           /* Select FLL clock */
#define KINETIS_BUSCLK_FREQUENCY    (KINETIS_SYSCLK_FREQUENCY / KINETIS_CLKDIV1_OUTDIV4)
#endif /* 0 */

/* FEE mode - 48 MHz */
/* not implemented */
#if 0
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_FEE
#define KINETIS_MCG_FLL_DMX32       1           /* Fine-tune for 32.768 kHz */
#define KINETIS_MCG_FLL_DRS         1           /* 1464x FLL factor */
#define KINETIS_CLKDIV1_OUTDIV1     1           /* Divide 48 MHz FLL by 1 => 48 MHz */
#define KINETIS_CLKDIV1_OUTDIV4     2           /* Divide OUTDIV1 output by 2 => 24 MHz */
#define KINETIS_SYSCLK_FREQUENCY    47972352UL  /* 32.768 kHz * 1464 (~48 MHz) */
#endif /* 0 */

/*
 * SERIAL driver system settings.
 */
#define KINETIS_SERIAL_USE_UART0              TRUE

/*
 * USB driver settings
 */
#define KINETIS_USB_USE_USB0                  TRUE

/* Need to redefine this, since the default (configured for K20x) might not apply
 *   2 for Teensy LC
 *   5 for Teensy 3.x */
#define KINETIS_USB_USB0_IRQ_PRIORITY         5

#endif /* _MCUCONF_H_ */
