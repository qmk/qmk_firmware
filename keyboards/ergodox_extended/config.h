/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2017 Erin Call <hello@erincall.com>
Copyright 2020 Marcus Young <myoung34@my.apsu.edu>
Copyright 2024 Adam Coleman <gephorian@gmail.com>

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

/* Matrix config */
#define DIODE_DIRECTION COL2ROW
#define MATRIX_ROWS 7
#define MATRIX_COLS 14
#define COL_EXPANDED { true, true, true, true, true, true, true, false, false, false, false, false, false, false }
#define MATRIX_ONBOARD_ROW_PINS { F0, F1, F4, F5, F6, F7, D7 }
#define MATRIX_ONBOARD_COL_PINS { 0, 0, 0, 0, 0, 0, 0, B0, B1, B2, B3, D2, D3, C6 }
#define EXPANDER_COL_REGISTER GPIOB
#define EXPANDER_ROW_REGISTER GPIOA
#define MATRIX_EXPANDER_COL_PINS {0, 1, 2, 3, 4, 5, 6}
#define MATRIX_EXPANDER_ROW_PINS {0, 1, 2, 3, 4, 5, 6}

/* I2C config */
#define I2C_TIMEOUT 100
#define I2C_ADDR        (0b0100000<<1)
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

/* fix space cadet rollover issue */
#define DISABLE_SPACE_CADET_ROLLOVER
