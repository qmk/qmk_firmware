/* Copyright 2022 TW59420 <https://github.com/TW59420>
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

#define FORCE_NKRO


#define RGB_DI_PIN B8
#define DRIVER_LED_TOTAL 34
#define RGBLED_NUM 34

#define WS2812_PWM_DRIVER PWMD4               // default: PWMD2
#define WS2812_PWM_CHANNEL 3                  // default: 2
//#define WS2812_PWM_COMPLEMENTARY_OUTPUT       // Define for a complementary timer output (TIMx_CHyN); omit for a normal timer output (TIMx_CHy).
#define WS2812_PWM_PAL_MODE 1                 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM7  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 2  