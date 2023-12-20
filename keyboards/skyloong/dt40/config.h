/* Copyright 2021 JZ-Skyloong (@JZ-Skyloong)
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

#define RGB_MATRIX_LED_COUNT 44   //The number of LEDs connected
#define RGB_MATRIX_KEYPRESSES  //Reacts to keypress
#define RGB_MATRIX_SLEEP   //turn off effects when suspended

#define RGB_MATRIX_DEFAULT_VAL 150  //Sets the default mode, if none has been set
#define RGB_TRIGGER_ON_KEYDOWN  //Triggers RGB keypress events on key down
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 1

//Set WS2812 driver
#define WS2812_TRST_US 200  //The Trst period between frames
//set ' WS2812_DRIVER = pwm ' in rule.mk
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_DMA_CHANNEL 3


