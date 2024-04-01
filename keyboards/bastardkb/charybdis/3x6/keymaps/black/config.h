/**
 * Copyright 2022 Andrew Ostroumov <andrew.ostroumov@gmail.com> (@andrewostroumov)
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

#ifdef VIA_ENABLE
#    define DYNAMIC_KEYMAP_LAYER_COUNT 4
#endif // VIA_ENABLE

#ifdef RGB_MATRIX_ENABLE
#    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    undef RGB_MATRIX_DEFAULT_MODE
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_RAINBOW_BEACON
#endif

#define NO_ACTION_ONESHOT

#ifdef POINTING_DEVICE_ENABLE
#    define CHARYBDIS_MINIMUM_DEFAULT_DPI 1200
#    define CHARYBDIS_DEFAULT_DPI_CONFIG_STEP 400
#    define CHARYBDIS_MINIMUM_SNIPING_DPI 200
#    define CHARYBDIS_SNIPING_DPI_CONFIG_STEP 100
// #    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 3000
// #    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 4
// #    define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#endif // POINTING_DEVICE_ENABLE

#ifdef BOOTMAGIC_ENABLE
#    define BOOTMAGIC_LITE_ROW 0
#    define BOOTMAGIC_LITE_COLUMN 0
#    define BOOTMAGIC_LITE_ROW_RIGHT 4
#    define BOOTMAGIC_LITE_COLUMN_RIGHT 0
#    define BOOTMAGIC_LITE_EEPROM_ROW 1
#    define BOOTMAGIC_LITE_EEPROM_COLUMN 0
#    define BOOTMAGIC_LITE_EEPROM_ROW_RIGHT 5
#    define BOOTMAGIC_LITE_EEPROM_COLUMN_RIGHT 0
#endif // BOOTMAGIC_ENABLE