/* Copyright 2022 QMK
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

#undef STM32_HSECLK
#define STM32_HSECLK            16000000

#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE        8

#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE                    96

#undef STM32_PLLP_VALUE
#define STM32_PLLP_VALUE                    4 // HCLK 48MHz, MCU current = 14 mA
//#define STM32_PLLP_VALUE                    6 // HCLK 32MHz, MCU current = 10 mA

#undef STM32_PLLQ_VALUE
#define STM32_PLLQ_VALUE                    4

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#ifdef LK_WIRELESS_ENABLE
#    undef STM32_SPI_USE_SPI1
#    define STM32_SPI_USE_SPI1 TRUE

#    undef STM32_ADC_USE_ADC1
#    define STM32_ADC_USE_ADC1 TRUE
#endif

#    undef STM32_SPI_USE_SPI1
#    define STM32_SPI_USE_SPI1 TRUE

