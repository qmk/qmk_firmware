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


// Buggy, currently disabled
/* #define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100000
#define EXTERNAL_EEPROM_I2C_ADDRESS(loc) (EXTERNAL_EEPROM_I2C_BASE_ADDRESS | ((((loc) >> 8) & 0x07) << 1))
#define EXTERNAL_EEPROM_BYTE_COUNT 2048
#define EXTERNAL_EEPROM_PAGE_SIZE 16
#define EXTERNAL_EEPROM_ADDRESS_SIZE 1
#define EXTERNAL_EEPROM_WRITE_TIME 5 */

#define RGBLIGHT_LAYERS_RETAIN_VAL

#define OLED_DISPLAY_WIDTH 128
#define OLED_DISPLAY_HEIGHT 32
#define OLED_FONT_H "keyboards/tau4/common/glcdfont.c"
