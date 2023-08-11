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

#define LAYOUT_split_3x5_3_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_3_wrapper(
        _________________KEYMAP1__________________,
        _________________KEYMAP2__________________,
        _________________KEYMAP3a_________________,
        _______THUMB6_1_______
    ),
    [1] = LAYOUT_split_3x5_3_wrapper(
        ______________SYM_MEDIA_NAV1______________,
        ______________SYM_MEDIA_NAV2______________,
        ______________SYM_MEDIA_NAV3______________,
        _____THUMB6_TRNS______
    ),
    [2] = LAYOUT_split_3x5_3_wrapper(
        _________________NUM_SYM1_________________,
        _________________NUM_SYM2_________________,
        _________________NUM_SYM3a________________,
        _____THUMB6_TRNS______
    ),
    [3] = LAYOUT_split_3x5_3_wrapper(
        ________________FUNC_SYS1a________________,
        ________________FUNC_SYS2_________________,
        ________________FUNC_SYS3_________________,
        _____THUMB6_TRNS______
    ),
    [4] = LAYOUT_split_3x5_3_wrapper(
        _________________KEYMAP1__________________,
        _________________KEYMAP2__________________,
        _________________KEYMAP3a_________________,
        _______THUMB6_4_______
    ),
    [5] = LAYOUT_split_3x5_3_wrapper(
        _________________KEYMAP1__________________,
        _________________KEYMAP2__________________,
        _________________KEYMAP3b_________________,
        _______THUMB6_5_______
    ),
    [6] = LAYOUT_split_3x5_3_wrapper(
        ______________SYM_MEDIA_NAV1______________,
        ______________SYM_MEDIA_NAV2______________,
        ______________SYM_MEDIA_NAV3______________,
        _____THUMB6_TRNS______
    ),
    [7] = LAYOUT_split_3x5_3_wrapper(
        _________________NUM_SYM1_________________,
        _________________NUM_SYM2_________________,
        _________________NUM_SYM3b________________,
        _____THUMB6_TRNS______
    ),
    [8] = LAYOUT_split_3x5_3_wrapper(
        ________________FUNC_SYS1b________________,
        ________________FUNC_SYS2_________________,
        ________________FUNC_SYS3_________________,
        _____THUMB6_TRNS______
    )
};
