/*
Copyright 2022 Hector Galindo <hi@hsuchil.com>

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

#include QMK_KEYBOARD_H
#include "hsuchil.h"

#define G_TIMEOUT 1500

enum sweet16_layers {
    _FNKEYS,
    _NUMS,
    _QWER,
    _ADJUST,
};

enum sweet16_keycodes {
    TOG_MASHG = NEW_SAFE_RANGE,
};

#define ADJUST MO(_ADJUST)
#define FNKEYS DF(_FNKEYS)
#define NUMS   DF(_NUMS)
#define QWER   DF(_QWER)

#define SLSH_ADJ LT(_ADJUST, KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_FNKEYS] = LAYOUT_ortho_4x4(
    KC_F24,  KC_F16,  KC_F20,  ADJUST,
    KC_VOLU, KC_F15,  KC_F19,  KC_F23,
    KC_VOLD, KC_F14,  KC_F18,  KC_F22,
    KC_MPLY, KC_F13,  KC_F17,  TOG_MASHG
),

[_NUMS] = LAYOUT_ortho_4x4(
    KC_7,    KC_8,    KC_9,    SLSH_ADJ,
    KC_4,    KC_5,    KC_6,    KC_ASTR,
    KC_1,    KC_2,    KC_3,    KC_MINUS,
    KC_ENT,  KC_0,    KC_DOT,  KC_PLUS
),

[_QWER] = LAYOUT_ortho_4x4(
    KC_GRV,  KC_6,    KC_7,    ADJUST,
    KC_Q,    KC_W,    KC_E,    KC_R,
    KC_A,    KC_S,    KC_D,    KC_F,
    KC_Z,    KC_X,    KC_C,    KC_V
),

[_ADJUST] = LAYOUT_ortho_4x4(
    QWER,    FNKEYS,  NUMS,    _______,
    _______, RGB_TOG, RGB_MOD, RESET,
    _______, _______, _______, _______,
    _______, _______, _______, _______
),

};

static bool mash_g = false;
static uint16_t g_timer;

bool extra_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TOG_MASHG:
            if (record->event.pressed){
                mash_g = mash_g ? false : true;
                g_timer = timer_read();
            }

            return false;
            break;
    }

    return true;
}

void extra_housekeeping_task_user(void) {
    if (mash_g && timer_elapsed(g_timer) > G_TIMEOUT) {
        tap_code(KC_G);
        g_timer = timer_read();
    }
}
