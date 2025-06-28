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

#define DYNAMIC_KEYMAP_MACRO_DELAY 8
#define TAPPING_TERM 200
#define TAP_CODE_DELAY 8

#define DEV_MODE_PIN C0
#define SYS_MODE_PIN C1
#define DC_BOOST_PIN C2
#define NRF_RESET_PIN B4
#define NRF_TEST_PIN B5
#define NRF_WAKEUP_PIN C4

#define RGB_DRIVER_SDB1 C6
#define RGB_DRIVER_SDB2 C7

#define SERIAL_DRIVER SD1
#define UART_TX_PIN B6
#define UART_TX_PAL_MODE 0
#define UART_RX_PIN B7
#define UART_RX_PAL_MODE 0

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b1110100 AD <-> GND
// 0b1110111 AD <-> VCC
// 0b1110101 AD <-> SCL
// 0b1110110 AD <-> SDA
#define IS31FL3733_I2C_ADDRESS_1 0b1010000
#define IS31FL3733_I2C_ADDRESS_2 0b1010011

#define ISSI_TIMEOUT 1

/* I2C Alternate function settings */
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN B8
#define I2C1_SDA_PIN B9
#define I2C1_CLOCK_SPEED 1000000

#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

#define I2C1_TIMINGR_PRESC 0U
#define I2C1_TIMINGR_SCLDEL 0U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 0U
#define I2C1_TIMINGR_SCLL 0U
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_16_9

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 64
#define DRIVER_2_LED_TOTAL 64
#undef RGB_MATRIX_LED_COUNT
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

#define IS31FL3733_SW_PULLUP  IS31FL3733_PUR_0K5_OHM
#define IS31FL3733_CS_PULLDOWN IS31FL3733_PDR_0K5_OHM

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES

#ifdef VIA_ENABLE
#    define VIA_EEPROM_CUSTOM_CONFIG_SIZE 19 // sizeof via_config
#else
#    define EECONFIG_KB_DATA_SIZE 17
#endif

#define RGB_MATRIX_SLEEP

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
#define USB_POLLING_INTERVAL_MS 1

/*
 * DEFAULT VALUES FOR INITIAL CONFIG to allow override in user keymap
 */
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_position_mode
#define RGB_DEFAULT_COLOR 168

#define DEFAULT_SLEEP_TOGGLE true
#define DEFAULT_USB_SLEEP_TOGGLE false
#define DEFAULT_DEEP_SLEEP_TOGGLE true
#define DEFAULT_SLEEP_TIMEOUT 5
#define DEFAULT_TOGGLE_POWER_ON_ANIMATION 1
#define DEFAULT_CAPS_INDICATOR_TYPE CAPS_INDICATOR_SIDE
#define DEFAULT_BATTERY_INDICATOR_BRIGHTNESS 100
#define DEFAULT_LIGHT_CUSTOM_KEYS 0
#define DEFAULT_SIDE_MODE_A 0
#define DEFAULT_SIDE_MODE_B 3
#define DEFAULT_SIDE_BRIGHTNESS 2
#define DEFAULT_SIDE_SPEED 2
#define DEFAULT_SIDE_RGB 1
#define DEFAULT_SIDE_COLOR 0
#define DEFAULT_BATTERY_INDICATOR_NUMERIC 0
#define DEFAULT_DETECT_NUMLOCK 0
#define DEFAULT_SHOW_SOCD_INDICATOR 0
/*
 * END OF DEFAULT VALUES
 */
#define CFW_VERSION "put_version_here"
