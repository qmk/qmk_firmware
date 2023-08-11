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

#include "scotto.h"

#define LAYOUT_ortho_4x10_wrapper(...)  LAYOUT_ortho_4x10(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_4x10_wrapper(
        _________________KEYMAP1__________________,
        _________________KEYMAP2__________________,
        _________________KEYMAP3a_________________,
        KC_NO, KC_NO, _______THUMB6_1_______, KC_NO, KC_NO
    ),
    [1] = LAYOUT_ortho_4x10_wrapper(
        ______________SYM_MEDIA_NAV1______________,
        ______________SYM_MEDIA_NAV2______________,
        ______________SYM_MEDIA_NAV3______________,
        KC_NO, KC_NO, _____THUMB6_TRNS______, KC_NO, KC_NO
    ),
    [2] = LAYOUT_ortho_4x10_wrapper(
        _________________NUM_SYM1_________________,
        _________________NUM_SYM2_________________,
        _________________NUM_SYM3a________________,
        KC_NO, KC_NO, _____THUMB6_TRNS______, KC_NO, KC_NO
    ),
    [3] = LAYOUT_ortho_4x10_wrapper(
        ________________FUNC_SYS1a________________,
        ________________FUNC_SYS2_________________,
        ________________FUNC_SYS3_________________,
        KC_NO, KC_NO, _____THUMB6_TRNS______, KC_NO, KC_NO
    ),
    [4] = LAYOUT_ortho_4x10_wrapper(
        _________________KEYMAP1__________________,
        _________________KEYMAP2__________________,
        _________________KEYMAP3a_________________,
        KC_NO, KC_NO, _______THUMB6_4_______, KC_NO, KC_NO
    ),
    [5] = LAYOUT_ortho_4x10_wrapper(
        _________________KEYMAP1__________________,
        _________________KEYMAP2__________________,
        _________________KEYMAP3b_________________,
        KC_NO, KC_NO, _______THUMB6_5_______, KC_NO, KC_NO
    ),
    [6] = LAYOUT_ortho_4x10_wrapper(
        ______________SYM_MEDIA_NAV1______________,
        ______________SYM_MEDIA_NAV2______________,
        ______________SYM_MEDIA_NAV3______________,
        KC_NO, KC_NO, _____THUMB6_TRNS______, KC_NO, KC_NO
    ),
    [7] = LAYOUT_ortho_4x10_wrapper(
        _________________NUM_SYM1_________________,
        _________________NUM_SYM2_________________,
        _________________NUM_SYM3b________________,
        KC_NO, KC_NO, _____THUMB6_TRNS______, KC_NO, KC_NO
    ),
    [8] = LAYOUT_ortho_4x10_wrapper(
        ________________FUNC_SYS1b________________,
        ________________FUNC_SYS2_________________,
        ________________FUNC_SYS3_________________,
        KC_NO, KC_NO, _____THUMB6_TRNS______, KC_NO, KC_NO
    )
};
