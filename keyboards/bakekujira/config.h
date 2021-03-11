/*

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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0921
#define PRODUCT_ID      0x0100
#define DEVICE_VER      0x0001
#define MANUFACTURER    papadakko
#define PRODUCT         bakekujira

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 17
#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3 }

// wiring of each half
#define MATRIX_ROW_PINS_RIGHT { D4, C6, D7, E6, B4 }
#define MATRIX_COL_PINS_RIGHT { B6, B2, B3, B1, F7, F6, F5, F4 }

#define DIODE_DIRECTION COL2ROW
#define SPLIT_TRANSPORT_MIRROR
#define EE_HANDS

#undef USE_I2C
#undef SSD1306OLED

#define USE_SERIAL_PD2

#define RGBLIGHT_SPLIT
#define RGB_SPLIT { 42, 62}

/* ws2812 RGB LED */
/* All things RGB */
#define RGB_DI_PIN B0
#define RGBLED_NUM 104
#define DRIVER_LED_TOTAL 104
#define RGBLIGHT_LIMIT_VAL 100
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
// #define RGBLIGHT_LAYERS // enables rgb lighting underglow that indicates status of the keyboard (capslock, current layer, etc)

#define RGBLIGHT_ANIMATIONS // enables all animation modes

/* RGB MATRIX stuff */
#define EECONFIG_RGB_MATRIX (uint32_t *)28
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_DISABLE_TIMEOUT 2 // number of milliseconds to wait until rgb automatically turns off
#define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
#define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255

/* number of backlight levels */
#define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

//RGB using PWM on pin B0
#define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#define WS2812_PWM_CHANNEL 3  // default: 2
#define WS2812_PWM_PAL_MODE 2  // Pin "alternate function" - default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM3  // DMA Stream for TIMx_UP
#define WS2812_DMA_CHANNEL 3  // DMA Channel for TIMx_UP

//Serial over USART config
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D3  // USART TX pin
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
#define SERIAL_USART_DRIVER SD1 // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function" - default: 7

// #define OLED_FONT_H "keyboards/bakekujira/lib/glcdfont.c"
