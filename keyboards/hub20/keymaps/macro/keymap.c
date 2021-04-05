/* Copyright 2020 joshajohnson
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
#define KC_WRAP KC_F23

// Keyboard Layers
enum keyboard_layers{
    _BASE = 0,
    _CTRL
};

// Tap Dance stuff
void td_ctrl (qk_tap_dance_state_t *state, void *user_data);

enum tap_dance {
    CTRL = 0,
    BASE = 1
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for standard key, twice to toggle layers
    [CTRL] = ACTION_TAP_DANCE_FN(td_ctrl),
    [BASE] = ACTION_TAP_DANCE_LAYER_MOVE(_______, _BASE)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_all(
              KC_W,  KC_Z,
       KC_A,  KC_B,  KC_C,  TD(CTRL),
       KC_E,  KC_F,  KC_G,  KC_H,
       KC_I,  KC_J,  KC_K,  KC_L,
       KC_M,  KC_N,  KC_O,  KC_P,
       KC_Q,  KC_R,  KC_S,  KC_T
),
    [_CTRL] = LAYOUT_all(
                   RESET,  _______,
       RGB_TOG, RGB_RMOD,  RGB_MOD,   TD(BASE),
       _______,  RGB_VAD,  RGB_VAI,    _______,
       _______,  RGB_HUD,  RGB_HUI,    _______,
       _______,  RGB_SAD,  RGB_SAI,    _______,
       _______,  _______,  _______,    _______
)
};

// Keyboard is setup to 'wrap' the pressed key with an unused Fxx key,
// allowing for easy differentiation from a real keyboard.
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left Encoder */
        if (clockwise) {
            register_code(KC_WRAP);
            tap_code(KC_U);
            unregister_code(KC_WRAP);
        } else {
            register_code(KC_WRAP);
            tap_code(KC_V);
            unregister_code(KC_WRAP);
        }
    } else if (index == 1) { /* Right Encoder */
        if (clockwise) {
            register_code(KC_WRAP);
            tap_code(KC_X);
            unregister_code(KC_WRAP);
        } else {
            register_code(KC_WRAP);
            tap_code(KC_Y);
            unregister_code(KC_WRAP);
        }
    }
}

// Below stolen from TaranVH (https://github.com/TaranVH/2nd-keyboard/blob/master/HASU_USB/F24/keymap.c)
// Shoutout to drashna on the QMK discord for basically writing this for me.... :P
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t f23_tracker;
    switch (keycode) {
        // Wrap sent keys in KC_WRAP
        case KC_A ... KC_F22:
        case KC_EXECUTE ... KC_EXSEL:
            if (record->event.pressed) {
                register_code(KC_WRAP);
                f23_tracker++;
                register_code(keycode);
            } else {
                unregister_code(keycode);
                f23_tracker--;
                if (!f23_tracker) {
                    unregister_code(KC_WRAP);
                }
            }
            return false;
            break;
    }
    return true;
}

// Below works around TD() not running key press through process_record_user
void td_ctrl (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code(KC_WRAP);
    tap_code(KC_D);
    unregister_code(KC_WRAP);
  } else if (state->count == 2) {
    layer_move(_CTRL);
  }
}
