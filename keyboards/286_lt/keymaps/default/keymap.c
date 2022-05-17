/*
 *
 * Copyright (C) 2022
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define XX KC_NO
enum layer_names {
    _BASE,
    _NUM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * default _BASE keymap
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│   │Num│Scl│Prt│Pus│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
     * │ ~ │1  │2  │3  │4  │5  │6  │7  │8  │9  │0  │-  │+  │Bspc   │Hom│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │Tab  │Q  │W  │E  │R  │T  │Y  │U  │I  │O  │P  │[  │]  │Enter│PUp│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
     * │Caps  │A  │S  │D  │F  │G  │H  │J  │K  │L  │;  │'  │\  │    │PDn│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
     * │Shift   │Z  │X  │C  │V  │B  │N  │M  │,  │.  │/  │Shift │↑  │End│
     * ├─────┬──┴─┬─┴─┬─┴─┬─┴───┴───┴───┴───┴───┴─┬─┴─┬─┴──┬───┼───┼───┤
     * │Ctrl │Alt │Del│Ins│           Space       │Alt│Ctrl│←  │↓  │→  │
     * └─────┴────┴───┴───┴───────────────────────┴───┴────┴───┴───┴───┘
     */
    [_BASE] = LAYOUT_tkl_iso(
        KC_ESCAPE,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_NLCK, KC_SCROLLLOCK, KC_PRINT_SCREEN, KC_PAUS,
        KC_GRAVE,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL,        KC_BSPC,         KC_HOME,
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,       KC_ENT,          KC_PAGE_UP,
        KC_CAPS,    KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN, KC_QUOT, KC_BSLASH,                     KC_PAGE_DOWN,
        KC_LSFT,    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,             KC_UP,           KC_END,
        KC_LCTL, KC_LALT, KC_DEL, KC_INSERT,                 KC_SPC,                          KC_RALT, KC_RCTL, KC_LEFT,    KC_DOWN,         KC_RGHT
    ),
    /*
     * default _NUM (Numlock) keymap
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│   │Num│Scl│Prt│Pus│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┼───┤
     * │   │   │   │   │   │   │   │7  │8  │9  │*  │-  │+  │Bspc   │Hom│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
     * │Tab  │   │   │   │   │   │   │4  │5  │6  │-  │[  │]  │Enter│PUp│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
     * │Caps  │   │   │   │   │   │   │1  │2  │3  │+  │   │   │    │PDn│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
     * │Shift   │   │   │   │   │   │   │0  │   │.  │/  │Shift │↑  │End│
     * ├─────┬──┴─┬─┴─┬─┴─┬─┴───┴───┴───┴───┴───┴─┬─┴─┬─┴──┬───┼───┼───┤
     * │Ctrl │Alt │Del│Ins│           Space       │Alt│Ctrl│←  │↓  │→  │
     * └─────┴────┴───┴───┴───────────────────────┴───┴────┴───┴───┴───┘
     */
    [_NUM] = LAYOUT_tkl_iso(
        KC_ESCAPE,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_NLCK, KC_SCROLLLOCK, KC_PRINT_SCREEN, KC_PAUS,
        XX,         XX,     XX,     XX,     XX,     XX,     XX,     KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_ASTERISK,  XX, XX,     KC_BSPC,         KC_HOME,
        XX,         XX,     XX,     XX,     XX,     XX,     XX,     KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_MINUS, XX, XX,         KC_ENT,          KC_PAGE_UP,
        KC_CAPS,    XX,     XX,     XX,     XX,     XX,     XX,     KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_PLUS, XX, XX,                           KC_PAGE_DOWN,
        KC_LSFT,    XX,     XX,     XX,     XX,     XX,     XX,     KC_KP_0, XX, KC_KP_DOT, KC_KP_SLASH, KC_RSFT,           KC_UP,           KC_END,
        KC_LCTL, KC_LALT, KC_DEL, KC_INSERT,                 KC_SPC,                          KC_RALT, KC_RCTL, KC_LEFT,    KC_DOWN,         KC_RGHT
    ),
};
/*
    { "label": "XX",            "matrix": [6, 6],   "x": 16,    "y": 0 },
    { "label": "XX",            "matrix": [6, 8],   "x": 16,    "y": 1 },
    { "label": "XX",            "matrix": [7, 1],   "x": 16,    "y": 2 },
    { "label": "XX",            "matrix": [7, 6],   "x": 16,    "y": 3 },
    { "label": "XX",            "matrix": [7, 8],   "x": 16,    "y": 5 },
*/

bool led_update_user(led_t led_state) {
    if(led_state.num_lock == 0) {
        set_single_persistent_default_layer(_BASE);
    }else{
        set_single_persistent_default_layer(_NUM);
    }
    return true;
}
