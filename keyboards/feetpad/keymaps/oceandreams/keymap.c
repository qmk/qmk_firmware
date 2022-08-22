/* Copyright 2021 Fe
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
#include QMK_KEYBOARD_H
#include "snowe.h"
#include "oceandream.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
        KC_L, KC_O, KC_V, KC_E,
        KC_F, KC_E, KC_E, KC_RCTL, KC_RCTL
    ),
    [1] = LAYOUT(
        _______, _______, _______,_______,\
        _______, _______, _______,_______,_______ \

    ),
    [2] = LAYOUT(
        _______, _______, _______,_______,\
        _______, _______, _______,_______,_______ \

    ),
    [3] = LAYOUT(
        _______, _______, _______,_______,\
        _______, _______, _______,_______,_______ \
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
        case KC_RCTL:
#ifdef OCEAN_DREAM_ENABLE
            is_calm = (record->event.pressed) ? true : false;
#endif
#ifdef LUNA_ENABLE
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
#endif
            break;
        case KC_SPC:
#ifdef LUNA_ENABLE
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
#endif
            break;
    }
    return true;
}

/*
#ifdef OLED_ENABLE
#    ifdef OCEAN_DREAM_ENABLE
        render_stars();
#    endif
*/
