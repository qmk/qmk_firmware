/* Copyright 2025 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include_next <mcuconf.h>

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

/* Run off the internal HSI RC oscillator with HSE disabled. Keyboardio's own
 * DAPBoot for this board is built with USE_HSI (CLOCK_MHZ 48), i.e. it does not
 * rely on an external crystal — so the Model 100 very likely has no usable HSE,
 * and a ChibiOS HSE config would spin forever on HSERDY in stm32_clock_init.
 * On STM32F103 the HSI PLL source is fixed at HSI/2 = 4 MHz; x12 = 48 MHz
 * sysclk, USBPRE /1 = 48 MHz USB. */
#undef STM32_HSE_ENABLED
#define STM32_HSE_ENABLED   FALSE
#undef STM32_PLLSRC
#define STM32_PLLSRC        STM32_PLLSRC_HSI
#undef STM32_PLLMUL_VALUE
#define STM32_PLLMUL_VALUE  12
#undef STM32_USBPRE
#define STM32_USBPRE        STM32_USBPRE_DIV1
#undef STM32_RTCSEL
#define STM32_RTCSEL        STM32_RTCSEL_NOCLOCK
