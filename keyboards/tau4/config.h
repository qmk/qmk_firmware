/*
Copyright 2020 Oliver Gaskell <me@gaskell.tech>

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

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

/* key matrix pins */
#define MATRIX_ROW_PINS { F4, F5, F6, F7 }
#define MATRIX_COL_PINS { D4, D6, D7, B4, B5, B6, C6, C7, F1, F0, B0, B1 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define RGB_DI_PIN B2
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LAYERS
#define RGBLED_NUM 10
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 16
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 128
#endif

#define ENCODERS_PAD_A { B3 }
#define ENCODERS_PAD_B { B7 }
#define ENCODER_RESOLUTION 1

// Buggy, currently disabled
/* #define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100000
#define EXTERNAL_EEPROM_I2C_ADDRESS(loc) (EXTERNAL_EEPROM_I2C_BASE_ADDRESS | ((((loc) >> 8) & 0x07) << 1))
#define EXTERNAL_EEPROM_BYTE_COUNT 2048
#define EXTERNAL_EEPROM_PAGE_SIZE 16
#define EXTERNAL_EEPROM_ADDRESS_SIZE 1
#define EXTERNAL_EEPROM_WRITE_TIME 5 */

#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_BRIGHTNESS 255
#define OLED_IC OLED_IC_SSD1306
#define OLED_DISPLAY_WIDTH 128
#define OLED_DISPLAY_HEIGHT 32
#define OLED_FONT_H "keyboards/tau4/common/glcdfont.c"
