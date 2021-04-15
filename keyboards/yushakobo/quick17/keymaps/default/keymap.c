/* Copyright 2020 yushakobo
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    BASE = SAFE_RANGE,
    KC_LSPC
};

enum layer_names {
    _CONTROL,
    _EDIT1,
    _EDIT2,
    _NUMPAD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_CONTROL] = LAYOUT(
    KC_TAB, KC_PGUP,KC_UP,  KC_PGDN,KC_HOME,KC_INS,
    KC_LCTL,KC_LEFT,KC_DOWN,KC_RGHT,KC_END, KC_DEL,
    KC_LSFT,KC_LGUI,KC_ESC, KC_LALT,KC_SPC, TO(1)
),
    [_EDIT1] = LAYOUT(
    KC_ESC, KC_W,   KC_E,   KC_R,   KC_Y,   KC_BSPC,
    KC_LCTL,KC_A,   KC_D,   KC_F,   KC_H,   LCTL(KC_Z),
    KC_LSFT,KC_X,   KC_V,   KC_B,   KC_LSPC,LCTL(KC_S)
),
    [_EDIT2] = LAYOUT(
    KC_ESC, KC_Q,   KC_BTN3,KC_INS, KC_NO,  KC_DEL,
    KC_LCTL,KC_LBRC,KC_RBRC,KC_PGDN,KC_PGUP,LCTL(KC_Y),
    KC_LSFT,TO(3),  RGB_TOG,TO(0),  _______,RESET
),
    [_NUMPAD] = LAYOUT(
    KC_ESC, KC_P0,  KC_P7,  KC_P8,  KC_P9,  KC_NLCK,
    KC_TAB, KC_PDOT,KC_P4,  KC_P5,  KC_P6,  KC_BSPC,
    KC_LSFT,KC_ENT, KC_P1,  KC_P2,  KC_P3,  TO(1)
)
};

static bool layer_shift = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LSPC:
            if (record->event.pressed){
                layer_shift = 1;
                layer_on(2);
            }else{
                layer_off(2);
                if(layer_shift){
                    register_code(KC_SPC);
                    unregister_code(KC_SPC);
                }
            }
            return false;
            break;
        default:
            if (record->event.pressed){
                layer_shift = 0;
            }
            break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise){
    if (index == 0) {
        if (IS_LAYER_ON(_EDIT1) && !layer_shift){
                if (clockwise) {
                    tap_code(KC_WH_U);
                } else {
                    tap_code(KC_WH_D);
                }
        } else if (IS_LAYER_ON(_EDIT2)){
                if (clockwise) {
                    tap_code(KC_LBRC);
                } else {
                    tap_code(KC_RBRC);
                }
        } else if (IS_LAYER_ON(_NUMPAD)){
                if (clockwise) {
                    tap_code(KC_UP);
                } else {
                    tap_code(KC_DOWN);
                }
        } else { // IS_LAYER_ON(_CONTROL)
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
        }
        
    }
}

void keyboard_post_init_user(void){
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
}