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

#ifndef MCUCONF_H
#define MCUCONF_H

/*
 * SN32F24xx drivers configuration.
 * The following settings override the default settings present in
 * the various device driver implementation headers.
 * Note that the settings for each driver only have effect if the whole
 * driver is enabled in halconf.h.
 *
 * IRQ priorities:
 * 3...0       Lowest...Highest.
 *
 * DMA priorities:
 * 0...3        Lowest...Highest.
 */

#define SN32F24xx_MCUCONF

/*
 * HAL driver system settings.
 */

/*
 * SN driver system settings.
 */
#define SN32_CT_IRQ_PRIORITY 2
#define SN32_CT_USE_TIMER 2

#define SN32_HAS_GPIOA TRUE
#define SN32_HAS_GPIOB TRUE
#define SN32_HAS_GPIOC TRUE
#define SN32_HAS_GPIOD TRUE

/*
 * USB driver system settings.
 */
#define SN32_USB_USE_USB1 TRUE
#define SN32_USB_LOW_POWER_ON_SUSPEND TRUE
#define STM32_USB_USB1_HP_IRQ_PRIORITY 13
#define STM32_USB_USB1_LP_IRQ_PRIORITY 14

#define CRT1_AREAS_NUMBER 1

#define PLATFORM_USB_USE_USB1 TRUE

/*
 * Timer driver system settings.
 */
#define SN32_PWM_USE_TIM1                  FALSE
#define SN32_PWM_USE_TIM2                  TRUE
#define SN32_PWM_TIM1_IRQ_PRIORITY         3
#define SN32_PWM_TIM2_IRQ_PRIORITY         3

#define SYS_CLOCK_SETUP 1
#define SYS0_CLKCFG_VAL 0
#define AHB_PRESCALAR 0x2
#define CLKOUT_SEL_VAL 0x0
#define CLKOUT_PRESCALAR 0x0

/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/
#define IHRC 	0
#define ILRC 	1
#define EHSXTAL	2
#define ELSXTAL	3
#define PLL		4

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __IHRC_FREQ 	(12000000UL)
#define __ILRC_FREQ 	(32000UL)
#define __ELS_XTAL_FREQ	(32768UL)

#if (SYS_CLOCK_SETUP)
#define SYS0_PLLCTRL_VAL	(PLL_ENABLE<<15) | (PLL_CLKIN<<12) | (PLL_FSEL<<8) | (PLL_PSEL<<5) |  PLL_MSEL
#endif

// #endif /* _MCUCONF_H_ */

#define PLATFORM_MCUCONF

#endif /* MCUCONF_H */