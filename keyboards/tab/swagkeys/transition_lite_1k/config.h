/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

#ifdef RGB_MATRIX_ENABLE
// /** RGB MATRIX CONFIGS ----- B13 TIM1_CH1N */
#define WS2812_PWM_COMPLEMENTARY_OUTPUT                 /** TIMx_CHyN   需要带N结尾*/
#define WS2812_PWM_DRIVER           PWMD1               /** TIMx        对应x*/
#define WS2812_PWM_CHANNEL          1                   /** TIMx_CHy    对应y */
#define WS2812_PWM_PAL_MODE         2
#define WS2812_DMA_STREAM           STM32_DMA1_STREAM5  /** TIMx_UP     对应x的UP，DMA数据表*/
#define WS2812_DMA_CHANNEL          5                   /** STM32_DMAx_STREAMy 对应y*/

#define RGB_MATRIX_DISABLE_KEYCODES

#define RBG_INDEX_CAPS                  62  /** Caps 指示灯索引 **/
#define RBG_INDEX_SCROLL                14  /** Scorll 指示灯索引 **/
#define RBG_INDEX_FN                    80  /** FN   指示灯索引 **/
#endif

