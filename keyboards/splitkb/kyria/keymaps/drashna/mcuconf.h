/* Copyright 2020 Nick Brassel (tzarc)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include_next <mcuconf.h>

#if defined(KEYBOARD_splitkb_kyria_rev3)
#    undef STM32_PWM_USE_ADVANCED
#    define STM32_PWM_USE_ADVANCED TRUE

#    undef STM32_PWM_USE_TIM2
#    define STM32_PWM_USE_TIM2 TRUE
#    undef STM32_PWM_USE_TIM3
#    define STM32_PWM_USE_TIM3 FALSE

#    undef STM32_SERIAL_USE_USART1
#    define STM32_SERIAL_USE_USART1 TRUE

#    undef STM32_ST_USE_TIMER
#    define STM32_ST_USE_TIMER 3
#endif
