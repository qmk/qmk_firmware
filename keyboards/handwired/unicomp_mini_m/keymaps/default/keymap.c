/* Copyright 2021 stevendlander
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

// Layer shortcuts
enum custom_layers {
    _QWERTY,
    _NUMPAD,
};

enum custom_keycodes {
    NUMSLCK = SAFE_RANGE, // Num Lock on shift, Scroll Lock regularly
    PAUSRST,  // Resets keyboard on shift, Pause|break regularly
    PSCSYSR,  // Sends SYSREQ on alt, Print Screen regularly
};

// Mod key detection
#define MODS_SHIFT_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))
#define MODS_ALT_MASK (MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             PSCSYSR, NUMSLCK, PAUSRST,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_NO,   KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,            KC_DEL,  KC_END,  KC_PGDN,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NO,   KC_ENT,                              
    KC_LSFT, KC_NO,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_NO,   KC_RSFT,                     KC_UP,           
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT
  ),
  [_NUMPAD] = LAYOUT(
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, NUMSLCK, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P7,   KC_P8,   KC_P9,   KC_TRNS, KC_PMNS, KC_PPLS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P4,   KC_P5,   KC_P6,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P1,   KC_P2,   KC_P3,   KC_PAST, KC_TRNS, KC_TRNS, KC_TRNS,                              
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0,   KC_TRNS, KC_PDOT, KC_PSLS, KC_TRNS, KC_TRNS,                     KC_TRNS,             
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case NUMSLCK: {
            if (record->event.pressed) {
                if (keyboard_report->mods & MODS_SHIFT_MASK) {
                    tap_code(KC_NLCK);
                } else {
                    register_code(KC_SLCK);
                }
            } else {
                unregister_code(KC_SLCK);
            }
            break;
        }
        case PAUSRST: {
            if (record->event.pressed) {
                if (keyboard_report->mods & MODS_SHIFT_MASK) {
                    reset_keyboard();
                } else {
                    register_code(KC_PAUS);
                }
            } else {
                unregister_code(KC_PAUS);
            }
            break;
        }
        case PSCSYSR: {
            if (record->event.pressed) {
                if (keyboard_report->mods & MODS_ALT_MASK) {
                    tap_code(KC_SYSREQ);
                } else {
                    register_code(KC_PAUS);
                }
            } else {
                unregister_code(KC_PAUS);
            }
            break;
        }
    }
    return true;
}

bool led_update_user(led_t led_state) {
    static bool num_state = false;
    if (num_state != led_state.num_lock) {
        if (led_state.num_lock) {
            layer_on(_NUMPAD);
        } else { 
            layer_off(_NUMPAD);
        }
        num_state = led_state.num_lock;
    }
    return true;
}
