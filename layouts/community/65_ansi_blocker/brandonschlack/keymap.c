/* Copyright 2019 Brandon Schlack
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
#include "brandonschlack.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base Layer
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │Esc│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ Bckspc│Hom│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│|   \│PgU│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │HyCaps│ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│   Enter│PgD│
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │Shift   │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│ Shift│ Up│End│
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │Ctrl│ Opt│ Cmd│          Space         │Cmd │FnPy│ │Lef│Dow│Rig│
 * └────┴────┴────┴────────────────────────┴────┴────┴─┴───┴───┴───┘
 */
[_BASE] = LAYOUT_65_ansi_blocker( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, \
    HY_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN, \
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,  \
    KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                    KC_RGUI, PLY_FN1,          KC_LEFT, KC_DOWN, KC_RGHT  \
),
/* Function Layer
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │` ~│ F1│ F2│ F3│ F4│ F5│ F6│ F7│ F8│ F9│F10│F11│F12│ Delete│SlD│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │RMod │RH+│RS+│RV+│AS+│   │   │   │   │   │F13│F14│F15│ LHP │VlU│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │RTgl  │RH-│RS-│RV-│AS-│   │   │   │   │   │   │   │        │VlD│
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │        │LYR│Thm│   │   │RST│   │Mke│Prv│Nxt│Ply│      │PgU│Mut│
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │    │    │    │                        │    │    │ │Hom│PgD│End│
 * └────┴────┴────┴────────────────────────┴────┴────┴─┴───┴───┴───┘
 */
[_FN1] = LAYOUT_65_ansi_blocker( \
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DELT, MC_SLPD, \
    RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, KC_F13,  KC_F14,  KC_F15,  MC_LHPD, KC_VOLU, \
    RGB_TOG, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______, _______, _______,          _______, KC_VOLD, \
    _______,          RGB_LYR, RGB_THM, _______, _______, RESET,   _______, QM_MAKE, KC_MPRV, KC_MNXT, KC_MPLY, _______, KC_PGUP, KC_MUTE, \
    _______, _______, _______,                            _______,                   _______, _______,          KC_HOME, KC_PGDN, KC_END   \
),
/* Blank Layout
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │   │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │      │   │   │   │   │   │   │   │   │   │   │   │        │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │        │   │   │   │   │   │   │   │   │   │   │      │   │   │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │    │    │    │                        │    │    │ │   │   │   │
 * └────┴────┴────┴────────────────────────┴────┴────┴─┴───┴───┴───┘
[X] = LAYOUT_65_ansi_blocker( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______,                            _______,                   _______, _______,          _______, _______, _______  \
),
*/
};

// Runs just one time when the keyboard initializes.
void matrix_init_keymap(void) {
};

// Runs once after keyboard initializes
void keyboard_post_init_keymap(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_keymap(void) {
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    #ifdef KEYBOARD_massdrop
        case RGB_TOG:
            if (record->event.pressed) {
                rgb_matrix_cycle_flag();
            }
            return false;
    #endif
        default:
            return true; //Process all other keycodes normally
    }
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_user(void) {
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(USB_LED_CAPS_LOCK_SCANCODE, RGB_GREEN);
    } else if (!HAS_ANY_FLAGS(rgb_matrix_get_flags(), LED_FLAG_KEYS)){
        rgb_matrix_set_color(USB_LED_CAPS_LOCK_SCANCODE, 0, 0, 0);
    }
}
#endif

