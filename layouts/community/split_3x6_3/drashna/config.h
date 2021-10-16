/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS
#define SPLIT_MODS_ENABLE

#undef USE_I2C
#undef SSD1306OLED

// #define TAPPING_FORCE_HOLD
// #define TAPPING_TERM 100

#ifdef RGBLIGHT_ENABLE
#    undef RGBLED_NUM
#    define RGBLED_NUM         27

#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  5
#    define RGBLIGHT_LIMIT_VAL 120
#endif

#ifdef RGB_MATRIX_ENABLE
#    ifdef CONVERT_TO_PROTON_C
#        undef RGB_DI_PIN
#        define RGB_DI_PIN A3
#    endif
#    define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    ifndef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#        define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120  // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#    endif
#    define RGB_MATRIX_HUE_STEP               8
#    define RGB_MATRIX_SAT_STEP               8
#    define RGB_MATRIX_VAL_STEP               5
#    define RGB_MATRIX_SPD_STEP               10
#endif

#ifdef CONVERT_TO_PROTON_C
#    define WS2812_PWM_DRIVER   PWMD2                 // default: PWMD2
#    define WS2812_PWM_CHANNEL  4                     // default: 2
#    define WS2812_PWM_PAL_MODE 1                     // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#    define WS2812_DMA_STREAM   STM32_DMA1_STREAM2    // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMA_CHANNEL  2                     // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#    define WS2812_DMAMUX_ID    STM32_DMAMUX1_TIM2_UP // DMAMUX configuration for TIMx_UP -- only required if your MCU has a DMAMUX peripheral, see the respective reference manual for the appropriate values for your MCU.

#    undef SOFT_SERIAL_PIN
#    define SOFT_SERIAL_PIN          D3
#    define SERIAL_USART_DRIVER      SD1 // USART driver of TX pin. default: SD1
#    define SERIAL_USART_TX_PAL_MODE 7   // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7

// #define INIT_EE_HANDS_LEFT
// #define INIT_EE_HANDS_RIGHT
#endif

#if defined(AUDIO_ENABLE) && !defined(CONVERT_TO_PROTON_C)
#    define AUDIO_PIN B6
#    define NO_MUSIC_MODE
#endif

#ifdef HAPTIC_ENABLE
#    define SOLENOID_PIN B7
#endif

#undef PRODUCT
#ifdef CONVERT_TO_PROTON_C
#    define PRODUCT Drashna Hacked ARM Corne Keyboard
#else
#    define PRODUCT Drashna Hacked Corne Keyboard
#endif

#define TAPPING_TERM_PER_KEY
