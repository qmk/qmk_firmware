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

#ifdef WORK_MODE
#    undef WORK_MODE
#endif
#define WORK_MODE THREE_MODE

#define DYNAMIC_KEYMAP_MACRO_DELAY 8
#define TAPPING_TERM 200
#define TAP_CODE_DELAY 8

#define DEVICE_MODE_PIN C0
#define OS_MODE_PIN C1
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

#define DRIVER_MATRIX_DI_PIN A7
#define DRIVER_MATRIX_CS_PIN C6
#define DRIVER_SIDE_DI_PIN C8
#define DRIVER_SIDE_CS_PIN C9

#define SERIAL_DRIVER SD1
#define UART_TX_PIN B6
#define UART_TX_PAL_MODE 0
#define UART_RX_PIN B7
#define UART_RX_PAL_MODE 0

#ifdef VIA_ENABLE
#    define VIA_EEPROM_CUSTOM_CONFIG_SIZE 22 // sizeof via_config
#else
#    define EECONFIG_KB_DATA_SIZE 20
#endif
#ifdef RGB_MATRIX_LED_COUNT
#    undef RGB_MATRIX_LED_COUNT
#endif
#define RGB_MATRIX_LED_COUNT 84 // sides 6 + 6, not included here

#define RGB_MATRIX_SLEEP

#define WS2812_SIDE_REFRESH
// #define DEBUG_MATRIX_SCAN_RATE

// NOTE: uncomment if you want to have random colors in Reactive RGB effects
// #define RGB_MATRIX_SOLID_REACTIVE_GRADIENT_MODE

#define DEBOUNCE_STEP 1

// USB sleep workaround :D
#ifdef USB_SUSPEND_WAKEUP_DELAY
#    undef USB_SUSPEND_WAKEUP_DELAY
#endif
#define USB_SUSPEND_WAKEUP_DELAY 50

// sleep timeout change step (minutes)
#define SLEEP_TIMEOUT_STEP 1
// #define LED_HITS_TO_REMEMBER 16
#define WS2812_SPI_USE_CIRCULAR_BUFFER

// debounce override - for clangd compliance - info_json.h - doesn't work most of the times
#define DEBOUNCE 5
#define RELEASE_DEBOUNCE (DEBOUNCE)
// use dedicated timer for wait_us interrupts instead on ChibiOS defaulting to minimum 100us even if you sleep for 10us
#define WAIT_US_TIMER GPTD14

/*
 * DEFAULT VALUES FOR INITIAL CONFIG to allow override in user keymap
 */
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_DEFAULT_COLOR 168

// Keyboard-specific defaults (override common/config.h defaults)
#ifndef DEFAULT_SLEEP_TIMEOUT
#    define DEFAULT_SLEEP_TIMEOUT 5
#endif
#ifndef DEFAULT_SIDE_MODE
#    define DEFAULT_SIDE_MODE 0
#endif
#ifndef DEFAULT_SIDE_BRIGHTNESS
#    define DEFAULT_SIDE_BRIGHTNESS 3
#endif
#ifndef DEFAULT_SIDE_SPEED
#    define DEFAULT_SIDE_SPEED 2
#endif
#ifndef DEFAULT_SIDE_RGB
#    define DEFAULT_SIDE_RGB 1
#endif
#ifndef DEFAULT_SIDE_COLOR
#    define DEFAULT_SIDE_COLOR 0
#endif
#ifndef DEFAULT_BATTERY_INDICATOR_BRIGHTNESS
#    define DEFAULT_BATTERY_INDICATOR_BRIGHTNESS 100
#endif
#ifndef DEFAULT_LIGHT_CUSTOM_KEYS
#    define DEFAULT_LIGHT_CUSTOM_KEYS 0
#endif
#ifndef DEFAULT_DETECT_NUMLOCK
#    define DEFAULT_DETECT_NUMLOCK 0
#endif
#ifndef DEFAULT_BATTERY_INDICATOR_NUMERIC
#    define DEFAULT_BATTERY_INDICATOR_NUMERIC 0
#endif
#ifndef DEFAULT_SHOW_SOCD_INDICATOR
#    define DEFAULT_SHOW_SOCD_INDICATOR 0
#endif

// LED position defines for indicators
#define WIN_LOCK_ROW 0
#define WIN_LOCK_COL 15
#define NUM_LOCK_ROW 0
#define NUM_LOCK_COL 14

// Additional defines needed for common code compatibility
#define SYS_SW_WIN 0xa1
#define SYS_SW_MAC 0xa2
#define TIMER_STEP 10

/*
 * END OF DEFAULT VALUES
 */
#define CFW_VERSION "put_version_here"
