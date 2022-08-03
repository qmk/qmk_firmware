/*
Copyright 2021-2022 Alin M Elena <alinm.elena@gmail.com>

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
#include "keymap_danish.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QW] = LAYOUT_ortho_5x13(
       KC_ESC, DK_1   , DK_2    , DK_3   , DK_4    , DK_5  , DK_6  , DK_7  , DK_8   , DK_9   , DK_0   , DK_PLUS, KC_BSPC ,
       KC_TAB, DK_Q   , DK_W    , DK_E   , DK_R    , DK_T  , DK_Y  , DK_U  , DK_I   , DK_O   , DK_P   , DK_ARNG, DK_DIAE ,
      DK_QUOT, DK_A   , DK_S    , DK_D   , DK_F    , DK_G  , DK_H  , DK_J  , DK_K   , DK_L   , DK_AE  , DK_OSTR, KC_ENT  ,
      KC_LSPO, DK_LABK, DK_Z    , DK_X   , DK_C    , DK_V  , DK_B  , DK_N  , DK_M   , DK_COMM, DK_DOT , KC_UP  , DK_MINS ,
      KC_LCTL, KC_LGUI, TT(_LWR), KC_LALT, TT(_RSE), KC_SPC, KC_SPC, KC_SPC, KC_RALT, KC_RSPC, KC_LEFT, KC_DOWN, KC_RGHT),

  [_LWR] = LAYOUT_ortho_5x13(
       DK_HALF, KC_MUTE, KC_VOLU, KC_VOLD, KC_MPRV, KC_MPLY, KC_MNXT, G(KC_P), KC_SLEP, KC_WAKE, KC_PSCR, KC_DEL , DK_ACUT  ,
       KC_BTN3, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
       KC_BTN2, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
       _______, KC_BTN1, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_U, _______ ,
       _______, KC_BTN4, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R),

  [_RSE] = LAYOUT_ortho_5x13(
      KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12  ,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
      KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ ,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_U, _______ ,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R),

    [_ADJ] = LAYOUT_ortho_5x13(
      RGB_MOD,RGB_RMOD, A(KC_F2), _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_T, RGB_M_SW ,
      RGB_HUI, RGB_HUD, RGB_M_P , _______, QK_BOOT, _______, _______, _______, _______, _______, _______, _______, RGB_M_SN ,
      RGB_SAI, RGB_SAD, RGB_M_B , _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_K ,
      RGB_VAI, RGB_VAD, RGB_M_R , _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_X ,
      RGB_TOG, _______, _______ , _______, _______, _______, _______, _______, _______, _______, _______, RGB_M_TW, RGB_M_G),

};
// clang-format on

bool led_update_user(led_t led_state) {
    // Disable the default LED update code, so that lock LEDs could be reused to show layer status.
    return false;
}

void matrix_scan_user(void) {

    toggle_leds();

}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case (TT(_LWR)):
            if (!record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
                // This runs before the TT() handler toggles the layer state, so the current layer state is the opposite of the final one after toggle.
                set_led_toggle(_LWR, !layer_state_is(_LWR));
            }
            return true;
            break;
        case (TT(_RSE)):
            if (record->event.pressed && record->tap.count == TAPPING_TOGGLE) {
                set_led_toggle(_RSE, !layer_state_is(_RSE));
            }
            return true;
            break;
        default:
            return true;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {

#ifdef RGBLIGHT_ENABLE

    set_rgb_layers(state);

#endif

    return update_tri_layer_state(state, _LWR, _RSE, _ADJ);
}

#ifdef RGBLIGHT_ENABLE

layer_state_t default_layer_state_set_user(layer_state_t state) {
    set_default_rgb_layers(state);
    return state;
}

#endif

void keyboard_post_init_user(void) {

#ifdef RGBLIGHT_ENABLE

    // Enable the LED layers
    rgblight_layers = my_rgb();

#endif

#ifdef OLED_ENABLE

    init_timer();

#endif

}
