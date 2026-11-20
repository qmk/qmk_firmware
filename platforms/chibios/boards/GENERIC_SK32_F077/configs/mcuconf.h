/*
    ChibiOS - Copyright (C) 2006-2026 Giovanni Di Sirio.

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
 * SK32F0xx drivers configuration.
 *
 * The SK32F077 is register-compatible with the STM32F072 but is served
 * exclusively by the native SK32 HAL port (os/hal/ports/SK32/SK32F0xx) in
 * ChibiOS-Contrib: no shared STM32 low level driver is compiled for this
 * platform, so only the SK32_* switches below are effective. There are
 * deliberately no STM32_* settings here - they would be silently ignored.
 *
 * IRQ priorities:
 * 3...0       Lowest...Highest.
 *
 * DMA priorities:
 * 0...3        Lowest...Highest.
 */

#define SK32F0xx_MCUCONF

/*
 * HAL system clock settings: 72MHz SYSCLK from the 8MHz HSI through the main
 * PLL (HSI/PREDIV1(=1) * PLLMUL(=9)).
 */
#define SK32_SW SK32_SW_PLL
#define SK32_PREDIV_VALUE 1
#define SK32_PLLMUL_VALUE 9
#define SK32_HPRE SK32_HPRE_DIV1
#define SK32_PPRE SK32_PPRE_DIV1

/*
 * ADC driver system settings.
 */
#define SK32_ADC_USE_ADC1 FALSE

/*
 * GPT driver system settings.
 * The SK32F077 variant only has the TIM3, TIM6, TIM16 and TIM17 timers.
 */
#define SK32_GPT_USE_TIM3 FALSE
#define SK32_GPT_USE_TIM16 FALSE
#define SK32_GPT_USE_TIM17 FALSE

/*
 * I2C driver system settings.
 * I2C1 is wired to PB6 (SCL) and PB7 (SDA), alternate function 13, open
 * drain with external pull-ups.
 */
#define SK32_I2C_USE_I2C1 TRUE
#define SK32_I2C_I2C1_PRIORITY 3
#define SK32_I2C_BUSY_TIMEOUT 50

/*
 * RTC driver system settings.
 * SK32_RTC_USE_LSE selects the 32768Hz LSE crystal, FALSE uses the internal
 * LSI oscillator instead.
 */
#define SK32_RTC_USE_LSE FALSE
#define SK32_RTC_IRQ_PRIORITY 3

/*
 * SERIAL driver system settings.
 * QMK uses the USB console, no USART channel is enabled by default.
 */
#define SK32_SERIAL_USE_USART1 FALSE
#define SK32_SERIAL_USE_USART2 FALSE

/*
 * SPI driver system settings.
 */
#define SK32_SPI_USE_SPI1 FALSE
#define SK32_SPI_USE_SPI2 FALSE

/*
 * ST driver system settings.
 * The SK32 port uses its native SysTick based ST driver, which requires
 * periodic mode (CH_CFG_ST_TIMEDELTA is forced to zero for this series in
 * platforms/chibios/mcu_selection.mk).
 */
#define SK32_ST_IRQ_PRIORITY 2

/*
 * USB driver system settings.
 * The SK32 musbfsfc USB LLD is used, not the STM32 USBv1 LLD.
 */
#define SK32_USB_USE_USB1 TRUE

/*
 * WDG driver system settings.
 * Set the matching switch to TRUE (together with HAL_USE_WDG in halconf.h)
 * to enable the IWDG (WDGD1, LSI clocked) or WWDG (WDGD2, PCLK1 clocked).
 */
#define SK32_WDG_USE_IWDG FALSE
#define SK32_WDG_USE_WWDG FALSE

#endif /* MCUCONF_H */
