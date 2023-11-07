/* Copyright 2021 Simon Arlott
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

#define HAL_USE_PAL                 TRUE
#define PAL_USE_CALLBACKS           TRUE

#define HAL_USE_GPT                 TRUE
//define STM32_GPT_USE_TIM3          TRUE

/* enable I2C, used for OLED & 3731 LED Driver */
#define HAL_USE_I2C     TRUE      // 이전과 다르게 I2C를 사용안하면  꺼야 컴파일 에러가 없음

/* enable SPI, used for WS2812underglow(RGB BackLight)/WS2812 RGB-Matrix SPI driver */
#define HAL_USE_SPI     TRUE

/* enable PWM, used for BackLight/WS2812 underglow(RGB BackLight)/WS2812 RGB-Matrix PWM driver */
//#define HAL_USE_PWM TRUE

#define HAL_USE_ADC     TRUE

#include_next <halconf.h>
