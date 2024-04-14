/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

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

#define USB_MODE 0
#define THREE_MODE 1
#define WORK_MODE THREE_MODE

#define DYNAMIC_KEYMAP_MACRO_DELAY 8
#define TAPPING_TERM 200
#define TAP_CODE_DELAY 8

#define DEV_MODE_PIN C0
#define SYS_MODE_PIN C1
#define DC_BOOST_PIN C2
#define NRF_RESET_PIN B4
#define NRF_TEST_PIN B5
#define NRF_WAKEUP_PIN B8

#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#define WS2812_DMA_CHANNEL 3
#define WS2812_PWM_TARGET_PERIOD 800000

#define DRIVER_RGB_DI_PIN A7
#define DRIVER_LED_CS_PIN C6
#define DRIVER_SIDE_PIN C8
#define DRIVER_SIDE_CS_PIN C9

#define SERIAL_DRIVER SD1
#define SD1_TX_PIN B6
#define SD1_TX_PAL_MODE 0
#define SD1_RX_PIN B7
#define SD1_RX_PAL_MODE 0

#define EECONFIG_KB_DATA_SIZE 8 // sizeof user_config_t
#define RGB_MATRIX_LED_COUNT 101 // 93  // RGB总灯数 (88轴灯+5侧灯)

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_position_mode
#define RGB_DEFAULT_COLOUR 168

#define USB_SLEEP_ENABLED true

#define DEBOUNCE 5
// #define DEBUG_MATRIX_SCAN_RATE

// configurations for CAPS_WORD feature
// #define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// #define CAPS_WORD_INVERT_ON_SHIFT

// NOTE: uncomment if you want to have random colors in Reactive RGB effects
// #define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE

#define DEBOUNCE_STEP 1

// USB sleep workaround :D
#define USB_SUSPEND_WAKEUP_DELAY 250

// sleep timeout change step (minutes)
#define SLEEP_TIMEOUT_STEP 1

#define USE_ASYM_DEBOUNCE 1
