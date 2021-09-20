/* Copyright 2021 Jessica Sullivan and Don Kjer
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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xD60D
#define MANUFACTURER    Hoksi Technology

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

// Dynamic EEPROM
// Something sensible or else VIA may crash
// Users may enable more if they wish
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR  4095

// Increase VIA layer count
#define DYNAMIC_KEYMAP_LAYER_COUNT 16

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#define BOOTMAGIC_LITE_ROW                 0
#define BOOTMAGIC_LITE_COLUMN              0

/* LED indicator pins */
#define LED_CAPS_LOCK_PIN   C4
#define LED_WIN_LOCK_PIN    C5
#define LED_SCROLL_LOCK_PIN A8
#define LED_MR_LOCK_PIN     LED_SCROLL_LOCK_PIN
#define LED_PIN_ON_STATE    0

#ifdef RGB_MATRIX_ENABLE
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 00 <-> GND
// 01 <-> SCL
// 10 <-> SDA
// 11 <-> VCC
// ADDR1 represents A1:A0 of the 7-bit address.
// ADDR2 represents A3:A2 of the 7-bit address.
// The result is: 0b101(ADDR2)(ADDR1)

#define DRIVER_ADDR_1 0b1010000
#define DRIVER_ADDR_2 0b1010011

#define DRIVER_COUNT 2
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

/* I2C Alternate function settings */
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

/* Set I2C speed to 400kHz, 300ns Tr, 14ns Tf */
#define I2C1_TIMINGR_PRESC   0x1U
#define I2C1_TIMINGR_SCLDEL  0x9U
#define I2C1_TIMINGR_SDADEL  0x0U
#define I2C1_TIMINGR_SCLH   0x0cU
#define I2C1_TIMINGR_SCLL   0x22U

#    define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_LED_PROCESS_LIMIT 4
#    define RGB_MATRIX_LED_FLUSH_LIMIT 26

#    define DISABLE_RGB_MATRIX_HUE_BREATHING
#    define DISABLE_RGB_MATRIX_HUE_PENDULUM
#    define DISABLE_RGB_MATRIX_HUE_WAVE

// This allows VIA to control RGB Matrix settings in the 'Lighting' section.
#define VIA_QMK_RGBLIGHT_ENABLE

#endif /* RGB_MATRIX_ENABLE */
