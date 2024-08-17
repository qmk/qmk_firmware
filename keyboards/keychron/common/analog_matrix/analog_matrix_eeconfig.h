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

#ifndef PROFILE_COUNT
#    define PROFILE_COUNT 3
#endif

#ifndef OKMC_COUNT
#    define OKMC_COUNT 20
#endif

#define CURVE_POINTS_COUNT  4

#define KC_ANALOG_MATRIX_VERSION 0x34340002
#define SIZE_OF_CALIB_VALUE_T 3             // Size of calibrated_value_t
#define SIZE_OF_ANALOG_KEY_CONFIG_T 4       // Size of analog_key_config_t
#define SIZE_OF_OKMC_CONFIG_T 19            // Size of okmc_config_t
#define SIZE_OF_POINT_T 2                   // Size of point_t
#define PROFILE_NAME_LEN 30

#define PROFILE_SIZE (2 + SIZE_OF_ANALOG_KEY_CONFIG_T*(MATRIX_ROWS*MATRIX_COLS+1) + PROFILE_NAME_LEN + SIZE_OF_OKMC_CONFIG_T*OKMC_COUNT)

#define OFFSET_CALIBRATION 0
#define OFFSET_CURRENT_PROFILE (OFFSET_CALIBRATION+1)

#define CALIBRATED_CONFIG_START (OFFSET_CURRENT_PROFILE + 1)
#define CALIBRATED_CONFIG_END (CALIBRATED_CONFIG_START + MATRIX_ROWS * MATRIX_COLS * SIZE_OF_CALIB_VALUE_T)

#define OFFSET_PROFILES_START (CALIBRATED_CONFIG_END + 1)
#define OFFSET_PROFILES_END (OFFSET_PROFILES_START + PROFILE_SIZE*PROFILE_COUNT)

#define OFFSET_CURVE_PTS_START (OFFSET_PROFILES_END + 1)
#define OFFSET_CURVE_PTS_END (OFFSET_CURVE_PTS_START + CURVE_POINTS_COUNT*SIZE_OF_POINT_T)

#define OFFSET_GAME_CONTROLLER_MODE_START OFFSET_CURVE_PTS_END
#define OFFSET_GAME_CONTROLLER_MODE_END (OFFSET_GAME_CONTROLLER_MODE_START+1)

#define EECONFIG_KB_DATA_VERSION   KC_ANALOG_MATRIX_VERSION
#define EECONFIG_KB_DATA_SIZE   OFFSET_GAME_CONTROLLER_MODE_END

#define EXTERNAL_EEPROM_OFFSET  4

