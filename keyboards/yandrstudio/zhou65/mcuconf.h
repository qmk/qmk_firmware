/* Copyright 2020 QMK
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

#undef STM32_NO_INIT
#undef STM32_HSI_ENABLED
#undef STM32_LSI_ENABLED
#undef STM32_HSE_ENABLED
#undef STM32_LSE_ENABLED
#undef STM32_CLOCK48_REQUIRED
#undef STM32_SW
#undef STM32_PLLSRC
#undef STM32_PLLM_VALUE
#undef STM32_PLLN_VALUE
#undef STM32_PLLP_VALUE
#undef STM32_PLLQ_VALUE
#undef STM32_HPRE
#undef STM32_PPRE1
#undef STM32_PPRE2
#undef STM32_RTCSEL
#undef STM32_RTCPRE_VALUE
#undef STM32_MCO1SEL
#undef STM32_MCO1PRE
#undef STM32_MCO2SEL
#undef STM32_MCO2PRE
#undef STM32_I2SSRC
#undef STM32_PLLI2SN_VALUE
#undef STM32_PLLI2SR_VALUE
#undef STM32_PVD_ENABLE
#undef STM32_PLS
#undef STM32_BKPRAM_ENABLE

#define STM32_NO_INIT                       FALSE
#define STM32_HSI_ENABLED                   TRUE
#define STM32_LSI_ENABLED                   TRUE
#define STM32_HSE_ENABLED                   TRUE
#define STM32_LSE_ENABLED                   FALSE
#define STM32_CLOCK48_REQUIRED              TRUE
#define STM32_SW                            STM32_SW_PLL
#define STM32_PLLSRC                        STM32_PLLSRC_HSE
#define STM32_PLLM_VALUE                    8
#define STM32_PLLN_VALUE                    192
#define STM32_PLLP_VALUE                    4
#define STM32_PLLQ_VALUE                    4
// AHB prescaler value.
#define STM32_HPRE                          STM32_HPRE_DIV1
//APB1 prescaler value.
#define STM32_PPRE1                         STM32_PPRE1_DIV4
//APB2 prescaler value.
#define STM32_PPRE2                         STM32_PPRE2_DIV2
#define STM32_RTCSEL                        STM32_RTCSEL_LSI
#define STM32_RTCPRE_VALUE                  8
#define STM32_MCO1SEL                       STM32_MCO1SEL_HSI
#define STM32_MCO1PRE                       STM32_MCO1PRE_DIV1
#define STM32_MCO2SEL                       STM32_MCO2SEL_SYSCLK
#define STM32_MCO2PRE                       STM32_MCO2PRE_DIV5
#define STM32_I2SSRC                        STM32_I2SSRC_CKIN
#define STM32_PLLI2SN_VALUE                 192
#define STM32_PLLI2SR_VALUE                 5
#define STM32_PVD_ENABLE                    FALSE
#define STM32_PLS                           STM32_PLS_LEV0
#define STM32_BKPRAM_ENABLE                 FALSE
