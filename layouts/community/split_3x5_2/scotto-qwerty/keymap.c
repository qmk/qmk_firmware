/*
Copyright 2023 Joe Scotto

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "scotto.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
        _________________QWERTY1__________________,
        _________________QWERTY2__________________,
        _________________QWERTY3a_________________,
        _______THUMB4_1_______
    ),
    [1] = LAYOUT_split_3x5_2(
        ______________SYM_MEDIA_NAV1______________,
        ______________SYM_MEDIA_NAV2______________,
        ______________SYM_MEDIA_NAV3______________,
        _____THUMB4_TRNS______
    ),
    [2] = LAYOUT_split_3x5_2(
        _________________NUM_SYM1_________________,
        _________________NUM_SYM2_________________,
        _________________NUM_SYM3a________________,
        _____THUMB4_TRNS______
    ),
    [3] = LAYOUT_split_3x5_2(
        ________________FUNC_SYS1a________________, 
        ________________FUNC_SYS2_________________,
        ________________FUNC_SYS3_________________,
        _____THUMB4_TRNS______
    ),
    [4] = LAYOUT_split_3x5_2(
        _________________QWERTY1__________________,
        _________________QWERTY2__________________,
        _________________QWERTY3a_________________,
        _______THUMB4_4_______
    ),
    [5] = LAYOUT_split_3x5_2(
        _________________QWERTY1__________________,
        _________________QWERTY2__________________,
        _________________QWERTY3b_________________,
        _______THUMB4_5_______
    ),
    [6] = LAYOUT_split_3x5_2(
        ______________SYM_MEDIA_NAV1______________,
        ______________SYM_MEDIA_NAV2______________,
        ______________SYM_MEDIA_NAV3______________,
        _____THUMB4_TRNS______
    ),
    [7] = LAYOUT_split_3x5_2(
        _________________NUM_SYM1_________________,
        _________________NUM_SYM2_________________,
        _________________NUM_SYM3b________________,
        _____THUMB4_TRNS______
    ),
    [8] = LAYOUT_split_3x5_2(
        ________________FUNC_SYS1b________________, 
        ________________FUNC_SYS2_________________,
        ________________FUNC_SYS3_________________,
        _____THUMB4_TRNS______
    )
};
