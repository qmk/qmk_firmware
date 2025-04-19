/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)

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

/* key matrix size */
#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)

#define ROWS_EXPANDED \
    { true, true, true, true, true, true, true, false, false, false, false, false, false, false }
#define DIODE_DIRECTION COL2ROW
#define EXPANDER_COL_REGISTER MCP23018_GPIOB
#define EXPANDER_ROW_REGISTER MCP23018_GPIOA
#define MATRIX_EXPANDER_COL_PINS \
    { 5, 4, 3, 2, 1, 0 }
#define MATRIX_EXPANDER_ROW_PINS \
    { 0, 1, 2, 3, 4, 5, 6 }

#define BOOTMAGIC_ROW_RIGHT 13
#define BOOTMAGIC_COLUMN_RIGHT 0

/* key combination for command */
#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))

#ifndef LED_BRIGHTNESS_LO
#    define LED_BRIGHTNESS_LO 15
#endif
#ifndef LED_BRIGHTNESS_HI
#    define LED_BRIGHTNESS_HI 255
#endif
#define LED_BRIGHTNESS_DEFAULT (LED_BRIGHTNESS_HI)

#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND
#define IS31FL3731_I2C_ADDRESS_2 IS31FL3731_I2C_ADDRESS_VCC
