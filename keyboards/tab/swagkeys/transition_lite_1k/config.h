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

// "vid": "0x534B" /** SK */
// "pid": "0x5431" /** T1 */


/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define EEPROM_SIZE 4096

#if 0
// valid config.
// /** A1 TIM2_CH2 */
// #define WS2812_PWM_COMPLEMENTARY_OUTPUT                /** TIMx_CHyN   需要带N结尾*/
#define WS2812_PWM_DRIVER           PWMD2               /** TIMx        对应x*/
#define WS2812_PWM_CHANNEL          2                   /** TIMx_CHy    对应y */
#define WS2812_PWM_PAL_MODE         2
#define WS2812_DMA_STREAM           STM32_DMA1_STREAM2  /** TIMx_UP     对应x的UP，DMA数据表*/
#define WS2812_DMA_CHANNEL          2                   /** STM32_DMAx_STREAMy 对应y*/

// /** A2 TIM2_CH3 */
// #define WS2812_PWM_COMPLEMENTARY_OUTPUT                /** TIMx_CHyN   需要带N结尾*/
#define WS2812_PWM_DRIVER           PWMD2               /** TIMx        对应x*/
#define WS2812_PWM_CHANNEL          3                   /** TIMx_CHy    对应y */
#define WS2812_PWM_PAL_MODE         2
#define WS2812_DMA_STREAM           STM32_DMA1_STREAM2  /** TIMx_UP     对应x的UP，DMA数据表*/
#define WS2812_DMA_CHANNEL          2                   /** STM32_DMAx_STREAMy 对应y*/
#endif

// A1 TIM2_CH2
#define WS2812_RGBLIGHT_DI_PIN              A2
// #define WS2812_RGBLIGHT_PWM_COMPLEMENTARY_OUTPUT                /** TIMx_CHyN   需要带N结尾*/
#define WS2812_RGBLIGHT_PWM_DRIVER           PWMD2               /** TIMx        对应x*/
#define WS2812_RGBLIGHT_PWM_CHANNEL          3                   /** TIMx_CHy    对应y */
#define WS2812_RGBLIGHT_PWM_PAL_MODE         2
#define WS2812_RGBLIGHT_DMA_STREAM           STM32_DMA1_STREAM2  /** TIMx_UP     对应x的UP，DMA数据表*/
#define WS2812_RGBLIGHT_DMA_CHANNEL          2                   /** STM32_DMAx_STREAMy 对应y*/

#ifdef RGBLIGHT_ENABLE
#   define RGBLIGHT_LAYERS
#   define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#   define RGBLIGHT_LAYERS_RETAIN_VAL
#   define RGBLIGHT_DEFAULT_MODE       RGBLIGHT_MODE_RAINBOW_SWIRL
#endif

#ifdef RGB_MATRIX_ENABLE
// /** RGB MATRIX CONFIGS ----- B13 TIM1_CH1N */
#define WS2812_PWM_COMPLEMENTARY_OUTPUT                 /** TIMx_CHyN   需要带N结尾*/
#define WS2812_PWM_DRIVER           PWMD1               /** TIMx        对应x*/
#define WS2812_PWM_CHANNEL          1                   /** TIMx_CHy    对应y */
#define WS2812_PWM_PAL_MODE         2
#define WS2812_DMA_STREAM           STM32_DMA1_STREAM5  /** TIMx_UP     对应x的UP，DMA数据表*/
#define WS2812_DMA_CHANNEL          5                   /** STM32_DMAx_STREAMy 对应y*/

#   define RGB_MATRIX_KEYPRESSES
#   define RGB_MATRIX_DISABLE_KEYCODES

#   define RBG_INDEX_CAPS                  62  /** Caps 指示灯索引 **/
#   define RBG_INDEX_SCROLL                14  /** Scorll 指示灯索引 **/
#   define RBG_INDEX_FN                    80  /** FN   指示灯索引 **/
// #   define RBG_INDEX_FN2                   80  /** FN2  指示灯索引 **/
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

 /* disable debug print */
 //#define NO_DEBUG

 /* disable print */
 //#define NO_PRINT

 /* disable action features */
 //#define NO_ACTION_LAYER
 //#define NO_ACTION_TAPPING
 //#define NO_ACTION_ONESHOT
