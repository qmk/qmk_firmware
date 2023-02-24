/* Copyright 2021 QMK Contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include_next <mcuconf.h>

// The SysTick timer from the normal quantum/stm32 uses TIM2 -- the WS2812 pin used
// on the Planck requires the use of TIM2 to run PWM -- rework which timers are
// allocated for PWM usage.
#undef STM32_PWM_USE_TIM2
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM2 TRUE
#define STM32_PWM_USE_TIM3 FALSE

// As mentioned above, we need to reallocate the SysTick timer used from
// TIM2 to TIM3.
#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER 3
