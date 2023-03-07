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

#define EE_HANDS

#ifdef OLED_ENABLE
#    ifdef OLED_DRIVER_SH1107
#        undef OLED_DISPLAY_128X64
#        define OLED_DISPLAY_128X128
#    endif
#endif

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP
#    undef RGBLIGHT_LIMIT_VAL
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_SPLIT
#    define RGBLIGHT_LAYERS
#endif

#define KEYLOGGER_LENGTH            10

#define QMK_ESC_INPUT               D4
#define QMK_ESC_OUTPUT              B2

#ifndef KEYBOARD_splitkb_kyria_rev3
#    define BOOTMAGIC_LITE_ROW 0
#    define BOOTMAGIC_LITE_COLUMN 7
#    define BOOTMAGIC_LITE_ROW_RIGHT 4
#    define BOOTMAGIC_LITE_COLUMN_RIGHT 7

#    define BOOTMAGIC_LITE_EEPROM_ROW 1
#    define BOOTMAGIC_LITE_EEPROM_COLUMN 7
#    define BOOTMAGIC_LITE_EEPROM_ROW_RIGHT 5
#    define BOOTMAGIC_LITE_EEPROM_COLUMN_RIGHT 7
#endif

#define SERIAL_USART_SPEED       921600

#if defined(KEYBOARD_splitkb_kyria_rev1_proton_c)
#    define WEAR_LEVELING_BACKING_SIZE 16384
#    define WEAR_LEVELING_LOGICAL_SIZE 8192
#endif
