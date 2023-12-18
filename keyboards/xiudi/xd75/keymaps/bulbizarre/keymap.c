/* Copyright 2017 Wunder
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


// Layer shorthand
#define _QW 0
#define _FN 1
#define _FS 2

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    SWITCH_FN = SAFE_RANGE,
    SWITCH_FS
};

uint16_t lt12_timer;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | `      | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | ENTER  | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | H      | J      | K      | L      | :      | @      | ~      | ENTER  | HOME   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | B      | N      | M      | ,      | .      | /      | RSHIFT | UP     | END    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | DEL    | LALT   | PSCR   | SPACE  | SPACE  | SPACE  | SPACE  | ALTGR  | FN     | FX     | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

    [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
        KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,      KC_9,      KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,      KC_P,      KC_LBRC, KC_RBRC, KC_ENT,  KC_DEL,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,      KC_SCLN,   KC_QUOT, KC_NUHS, KC_ENT,  KC_HOME,
        KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM,   KC_DOT,    KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_DEL,  KC_LALT, KC_PSCR, KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_ALGR, SWITCH_FN, SWITCH_FS, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | =      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | ENTER  | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | H      | J      | K      | L      | :      | @      | ~      | ENTER  | HOME   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | B      | N      | M      | ,      | .      | /      | RSHIFT | UP     | END    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | DEL    | LALT   | PSCR   | SPACE  | SPACE  | SPACE  | SPACE  | ALTGR  | FN     | FX     | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

    [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_EQL,  KC_BSPC,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(_QW), TO(_FS), _______, _______, _______, _______
    ),

/* FUNCTIONS
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | RGB+   | BL_BRT | F3     | F4     | F5     | F6     | F7     | F8     | F9     | /      | *      | -      | +      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | RGB_H+ | RGB-   | BL-    | E      | R      | T      | Y      | U      | I      | O      | 7      | 8      | 9      | ENTER  | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | RGB_H- | RGB_M+ | BL+    | VOL+   | F      | G      | H      | J      | K      | L      | 4      | 5      | 6      | ENTER  | QK_BOOT  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | RGB_S+ | RGB_M- | BL_S   | VOL-   | V      | B      | B      | N      | M      | ,      | 1      | 2      | 3      | UP     | END    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | RGB_S- | RGB_T  | BL_T   | MUTE   | SPACE  | SPACE  | SPACE  | SPACE  | ALTGR  | FN     | FX     | 0      | .      | .      | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

    [_FS] = LAYOUT_ortho_5x15( /* FUNCTION */
        _______, RGB_VAI, BL_BRTG, _______, _______, _______, _______, _______, _______, _______, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, _______,
        RGB_HUI, RGB_VAD, BL_UP,   _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______,
        RGB_HUD, RGB_RMOD,BL_DOWN, KC_VOLU, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, QK_BOOT,
        RGB_SAI, RGB_MOD, BL_STEP, KC_VOLD, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   _______, _______,
        RGB_SAD, RGB_TOG, BL_TOGG, KC_MUTE, _______, _______, _______, _______, _______, TO(_FN), TO(_QW), KC_P0,   KC_PDOT, KC_DOT,  _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SWITCH_FN:
        if (record->event.pressed) {
            lt12_timer = timer_read();
            layer_on(_FN);
            gp100_led_on();
        } else {
            if (timer_elapsed(lt12_timer) > 200) {  
            layer_off(_FN);
            gp100_led_off();
            }
        }
        return false;
        break;
        case SWITCH_FS:
        if (record->event.pressed) {
            lt12_timer = timer_read();
            layer_on(_FS);
            gp100_led_on();
        } else {
            if (timer_elapsed(lt12_timer) > 200) {  
            layer_off(_FS);
            gp100_led_off();
            }
        }
        return false;
        break;
    }
    return true;
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {
        capslock_led_on();
    } else {
        capslock_led_off();
    }
    if (IS_LAYER_ON(_FN) || IS_LAYER_ON(_FS)) {
        gp100_led_on();
    } else {
        gp100_led_off();
    }
    return false;
}
