/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#include "ps2avrGB.h"
#include "action_layer.h"
#include "rgblight.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KC_KEYMAP(
        ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,HOME,END,
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     DEL,
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     INS,
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,           PGUP,
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,          UP,  PGDN,
        LCTL,LALT,LGUI,          SPC,                     RGUI,RALT,RCTL,LEFT,DOWN,RGHT
    )
};

enum function_id {
    RGBLED_TOGGLE,
    RGBLED_STEP_MODE,
    RGBLED_INCREASE_HUE,
    RGBLED_DECREASE_HUE,
    RGBLED_INCREASE_SAT,
    RGBLED_DECREASE_SAT,
    RGBLED_INCREASE_VAL,
    RGBLED_DECREASE_VAL,
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION(RGBLED_TOGGLE),
    [1] = ACTION_FUNCTION(RGBLED_STEP_MODE),
    [2] = ACTION_FUNCTION(RGBLED_INCREASE_HUE),
    [3] = ACTION_FUNCTION(RGBLED_DECREASE_HUE),
    [4] = ACTION_FUNCTION(RGBLED_INCREASE_SAT),
    [5] = ACTION_FUNCTION(RGBLED_DECREASE_SAT),
    [6] = ACTION_FUNCTION(RGBLED_INCREASE_VAL),
    [7] = ACTION_FUNCTION(RGBLED_DECREASE_VAL),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
        case RGBLED_TOGGLE:
            if (record->event.pressed) {
                rgblight_toggle();
            }
            break;
        case RGBLED_STEP_MODE:
            if (record->event.pressed) {
                rgblight_step();
            }
            break;
        case RGBLED_INCREASE_HUE:
            if (record->event.pressed) {
                rgblight_increase_hue();
            }
            break;
        case RGBLED_DECREASE_HUE:
            if (record->event.pressed) {
                rgblight_decrease_hue();
            }
            break;
        case RGBLED_INCREASE_SAT:
            if (record->event.pressed) {
                rgblight_increase_sat();
            }
            break;
        case RGBLED_DECREASE_SAT:
            if (record->event.pressed) {
                rgblight_decrease_sat();
            }
            break;
        case RGBLED_INCREASE_VAL:
            if (record->event.pressed) {
                rgblight_increase_val();
            }
            break;
        case RGBLED_DECREASE_VAL:
            if (record->event.pressed) {
                rgblight_decrease_val();
            }
            break;
    }
};
