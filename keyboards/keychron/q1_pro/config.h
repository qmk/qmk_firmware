/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

/* Turn off effects when suspended */
#define RGB_DISABLE_WHEN_USB_SUSPENDED

/* DIP switch for Mac/win OS switch */
#define DIP_SWITCH_PINS { A8 }

#ifdef KC_BLUETOOTH_ENABLE
/* Hardware configuration */
#    define USB_BT_MODE_SELECT_PIN C15

#    define CKBT51_RESET_PIN A9
#    define CKBT51_INT_INPUT_PIN A5
#    define BLUETOOTH_INT_INPUT_PIN A6

#    define USB_POWER_SENSE_PIN B1
#    define USB_POWER_CONNECTED_LEVEL 0

#    define HOST_DEVICES_COUNT 3

#    if defined(RGB_MATRIX_ENABLE)

#        define LED_DRIVER_SHUTDOWN_PIN C14

#        define HOST_LED_MATRIX_LIST \
            { 16, 17, 18 }

#        define BAT_LEVEL_LED_LIST \
            { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 }

/* Backlit disable timeout when keyboard is disconnected(unit: second) */
#        define DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT 40

/* Backlit disable timeout when keyboard is connected(unit: second) */
#        define CONNECTED_BACKLIGHT_DISABLE_TIMEOUT 600
#    endif

/* Keep USB connection in blueooth mode */
#    define KEEP_USB_CONNECTION_IN_BLUETOOTH_MODE

/* Enable bluetooth NKRO */
#    define BLUETOOTH_NKRO_ENABLE

/* Raw hid command for factory test and bluetooth DFU */
#    define RAW_HID_CMD 0xAA ... 0xAB
#else
/* Raw hid command for factory test */
#    define RAW_HID_CMD 0xAB
#endif

/* Emulated EEPROM configuration */
#define WEAR_LEVELING_LOGICAL_SIZE 2048
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 2047

/* Encoder Configuration */
#ifdef ENCODER_ENABLE
#    define ENCODER_DEFAULT_POS 0x3
#endif

/* Factory test keys */
#define FN_KEY1 MO(1)
#define FN_KEY2 MO(3)
#define BL_TEST_KEY2 KC_END

#define INVERT_OS_SWITCH_STATE
