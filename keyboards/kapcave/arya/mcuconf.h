/*
Copyright 2021 KapCave

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include_next <mcuconf.h>

/* enable TIM1, used for backlight PWM */
#undef STM32_PWM_USE_TIM1
#define STM32_PWM_USE_TIM1                  TRUE

/* enable TIM2, used for underglow PWM driver */
#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2                  TRUE

/* move system from TIM2 (default) to TIM3 (since TIM2 is needed for underglow) */
#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3                  FALSE
#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER                  3
