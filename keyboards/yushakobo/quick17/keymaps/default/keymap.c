/* Copyright 2021 yushakobo
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
#include "quick17_prefs.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    KC_LANG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_CONTROL] = LAYOUT(
        KC_TAB, KC_PGUP,KC_UP,  KC_PGDN,KC_HOME,KC_INS,
        KC_LCTL,KC_LEFT,KC_DOWN,KC_RGHT,KC_END, KC_DEL,
        KC_LSFT,KC_LGUI,KC_ESC, KC_LALT,LT(3,KC_SPC),TO(1)
    ),
        [_EDIT1] = LAYOUT(
        KC_ESC, KC_W,   KC_E,   KC_R,   KC_Y,   KC_BSPC,
        KC_LCTL,KC_A,   KC_D,   KC_F,   KC_H,   LCTL(KC_Z),
        KC_LSFT,KC_X,   KC_V,   KC_B,   LT(2,KC_SPC),LCTL(KC_S)
    ),
        [_EDIT2] = LAYOUT(
        KC_ESC, KC_Q,   KC_BTN3,KC_INS, KC_ENT, KC_DEL,
        KC_LCTL,KC_LBRC,KC_RBRC,KC_PGDN,KC_PGUP,LCTL(KC_Y),
        KC_LSFT,TO(3),  RGB_TOG,TO(0),  _______,KC_NO
    ),
        [_FN] = LAYOUT(
        KC_ESC, KC_LANG,KC_NO,  RGB_TOG,KC_MNXT,KC_VOLU,
        KC_CAPS,KC_NLCK,KC_NO,  RGB_MOD,KC_MPRV,KC_VOLD,
        CG_NORM,LCG_SWP,EEP_RST,RESET,  TO(0),  KC_MUTE
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LANG:
            if (record->event.pressed){
                if (keymap_config.swap_lctl_lgui == false){
                    tap_code16(LALT(KC_GRV));
                } else {
                    if(input_mode()){
                        register_code(KC_LANG2);
                        set_input_mode(false);
                    } else {
                        register_code(KC_LANG1);
                        set_input_mode(true);
                    }
                }
            } else {
                unregister_code(KC_LANG1);
                unregister_code(KC_LANG2);
            }
            break;
        default:
            break;
    }
    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise){
    if (index == 0) {
        if (IS_LAYER_ON(_EDIT2)){
            if (clockwise) {
                tap_code(KC_LBRC);
            } else {
                tap_code(KC_RBRC);
            }
        } else if (IS_LAYER_ON(_EDIT1)){
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        } else if (IS_LAYER_ON(_FN)){
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
        } else { // IS_LAYER_ON(_CONTROL)
            if (clockwise) {
                tap_code(KC_WH_U);
            } else {
                tap_code(KC_WH_D);
            }
        }
    }
    return false;
}

#ifdef RGB_MATRIX_ENABLE
    void keyboard_post_init_user(void){
        rgb_matrix_mode(RGB_MATRIX_CUSTOM_quick17_rgbm_effect);
        set_input_mode(false);
    }
#else
    void keyboard_post_init_user(void){
        rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL);
        set_input_mode(false);
    }
#endif
