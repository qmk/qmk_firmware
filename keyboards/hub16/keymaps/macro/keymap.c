/* Copyright 2019 Josh Johnson
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

// Function key we are 'wrapping' usual key presses in
#define KC_WRAP KC_F24

// Keyboard Layers
enum keyboard_layers{
    _BASE = 0,
    _CTRL
};

// Tap Dance Declarations
void td_ctrl (tap_dance_state_t *state, void *user_data);

enum tap_dance { CTRL = 0, BASE = 1 };

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for standard key on base layer, twice to toggle to control layer
    [CTRL] = ACTION_TAP_DANCE_FN(td_ctrl),
    [BASE] = ACTION_TAP_DANCE_LAYER_MOVE(_______, _BASE)};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Base */
        KC_S,      KC_V,
    KC_A, KC_B, KC_C, KC_D,
    KC_E, KC_F, KC_G, KC_H,
    KC_I, KC_J, KC_K, KC_L,
    KC_M, KC_N, KC_O, TD(CTRL)
  ),

  [_CTRL] = LAYOUT( /* Control */
          KC_NO,            KC_NO,
    _______, RGB_MOD, RGB_RMOD, RGB_TOG,
    RGB_VAD, RGB_VAI, RGB_HUD,  RGB_HUI,
    RGB_SAD, RGB_SAI, _______,  _______,
    _______, _______, QK_BOOT,  TD(BASE)
  ),
};

// Keyboard is setup to 'wrap' the pressed key with an unused Fxx key,
// allowing for easy differentiation from a real keyboard.
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left Encoder */
        if (clockwise) {
            register_code(KC_WRAP);
            tap_code(KC_R);
            unregister_code(KC_WRAP);
        } else {
            register_code(KC_WRAP);
            tap_code(KC_Q);
            unregister_code(KC_WRAP);
        }
    } else if (index == 1) { /* Right Encoder */
        if (clockwise) {
            register_code(KC_WRAP);
            tap_code(KC_U);
            unregister_code(KC_WRAP);
        } else {
            register_code(KC_WRAP);
            tap_code(KC_T);
            unregister_code(KC_WRAP);
        }
    }
    return true;
}

// Below stolen from TaranVH (https://github.com/TaranVH/2nd-keyboard/blob/master/HASU_USB/F24/keymap.c)
// Shoutout to drashna on the QMK discord for basically writing this for me.... :P
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t f24_tracker;
    switch (keycode) {
        case KC_A ... KC_F23:
        case KC_EXECUTE ... KC_EXSEL:
            if (record->event.pressed) {
                register_code(KC_WRAP);
                f24_tracker++;
                register_code(keycode);
            } else {
                unregister_code(keycode);
                f24_tracker--;
                if (!f24_tracker) {
                    unregister_code(KC_WRAP);
                }
            }
            return false;
            break;
    }
    return true;
}

// Below works around TD() not running key press through process_record_user.
// Fixes bug of CTRL layer move key not being wrapped in by modifier on single tap
void td_ctrl (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_WRAP);
    tap_code(KC_P);
    unregister_code(KC_WRAP);
  } else if (state->count == 2) {
    layer_move(_CTRL);
  }
}
