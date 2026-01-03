/* Copyright 2024 Epomaker
 * Copyright 2024 Epomaker <https://github.com/Epomaker>
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

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Define less important options */

/*
 * Force NKRO
 *
 * Force NKRO (nKey Rollover) to be enabled by default, regardless of the saved
 * state in the bootmagic EEPROM settings. (Note that NKRO must be enabled in the
 * makefile for this to work.)
 *
 * If forced on, NKRO can be disabled via magic key (default = LShift+RShift+N)
 * until the next keyboard reset.
 *
 * NKRO may prevent your keystrokes from being detected in the BIOS, but it is
 * fully operational during normal computer usage.
 *
 * For a less heavy-handed approach, enable NKRO via magic key (LShift+RShift+N)
 * or via bootmagic (hold SPACE+N while plugging in the keyboard). Once set by
 * bootmagic, NKRO mode will always be enabled until it is toggled again during a
 * power-up.
 *
 */
// #define FORCE_NKRO // deprecated in favor of host.default.nkro in keyboard.json
/*
 * Feature disable options
 * These options are also useful to firmware size reduction.
 */

#define MATRIX_UNSELECT_DRIVE_HIGH
#define CORTEX_ENABLE_WFI_IDLE          FALSE

/* Ensure we jump to bootloader if the RESET keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#define DEBOUNCE 2

#ifndef NOP_FUDGE
#define NOP_FUDGE 0.4
#endif

#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 1151
#define EEPROM_SIZE 1152
#define FEE_PAGE_SIZE (0x200)
#define FEE_PAGE_COUNT (8)
#define FEE_PAGE_BASE_ADDRESS (0x1F000)
#define FEE_MCU_FLASH_SIZE (0x1000)
#define EECONFIG_USER_DATA_SIZE 4
#define EECONFIG_KB_DATA_SIZE 1
#define TRANSIENT_EEPROM_SIZE 4096

#define RGB_MATRIX_LED_COUNT 101
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#define RGB_MATRIX_SLEEP

// BLE configuration
#define USER_BLE_ID (0X00A5)
#define USER_BLE1_NAME "Galaxy68-1"
#define USER_BLE2_NAME "Galaxy68-2"
#define USER_BLE3_NAME "Galaxy68-3"

/* LED Index Definitions required by lib/rdmctmzt_common/keyboard_common.h */
#define LOGO_LED_ENABLE 1       // Enable Logo LED functionality
#define LED_LOGO_INDEX 68       // Logo LED starting index (68-99 are logo/bottom LEDs)
#define LOGO_LED_COUNT 32       // Number of logo/bottom LEDs
#define LED_CONNECTION_INDEX 67 // Connection type indicator (BLE/2.4G/USB)
#define LED_CAP_INDEX 32        // Caps Lock indicator
#define LED_WIN_L_INDEX 45      // Win Lock indicator
#define LED_BATT_INDEX 38       // Battery status indicator
#define LED_BLE_1_INDEX 17      // BLE 1 indicator
#define LED_BLE_2_INDEX 18      // BLE 2 indicator
#define LED_BLE_3_INDEX 19      // BLE 3 indicator
#define LED_2P4G_INDEX 20       // 2.4G indicator
#define LED_USB_INDEX 21        // USB indicator

