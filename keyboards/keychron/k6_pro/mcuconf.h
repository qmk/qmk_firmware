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

<<<<<<< HEAD:keyboards/keychron/k6_pro/mcuconf.h
/* Set HCLK to 48 MHz as tradeoff of USB lowest clockand and 
 * lower power comsumption for bluetooth. Will use dynamic 
 * clock when STM32L4 is supported in ChibiOS */
#undef STM32_PLLM_VALUE
#define STM32_PLLM_VALUE 2
=======
/* TIM1 PWM used for audio driver */
#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1 TRUE
>>>>>>> master:keyboards/yanghu/unicorne/f411/mcuconf.h

#undef STM32_PLLN_VALUE
#define STM32_PLLN_VALUE 12

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#ifdef BLUETOOTH_ENABLE
#    undef STM32_SERIAL_USE_USART2
#    define STM32_SERIAL_USE_USART2 TRUE
#endif