/*
Copyright 2019 Yaotian Feng(Codetector) <codetector@codetector.cn>

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


#define MATRIX_ROWS 14
#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_COLS 6
/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    keyboard_report->mods == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

// i2c_master driver config
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
