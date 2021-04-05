/*
 * 60 ANSI Arrow Split Backspace & 7U Space Keymap
 * with RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator.
 *
 * Copyright (C) 2020 Sendy YK <https://mr.sendyyk.com>
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

enum layer_names {
    _BASE, // Base Layer
    _FN, // Fn Layer
    _RESET // Reset Layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * [_BASE] Base Layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│1  │2  │3  │4  │5  │6  │7  │8  │9  │0  │-  │+  │\  │Del│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │Tab  │Q  │W  │E  │R  │T  │Y  │U  │I  │O  │P  │[  │]  │Bspc │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │Caps  │A  │S  │D  │F  │G  │H  │J  │K  │L  │;  │'  │Return  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
     * │Shift   │Z  │X  │C  │V  │B  │N  │M  │,  │.  │Shift │↑  │/  │
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴──┬───┼───┼───┤
     * │Ctrl │OS │Alt  │Space                      │Fn │←  │↓  │→  │
     * └─────┴───┴─────┴───────────────────────────┴───┴───┴───┴───┘
     */
    [_BASE] = LAYOUT_60_ansi_arrow_split_bs_7u_spc(
        KC_GESC, KC_1,    KC_2, KC_3,    KC_4, KC_5, KC_6,   KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,
        KC_TAB,           KC_Q, KC_W,    KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_CAPS,          KC_A, KC_S,    KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,          KC_Z, KC_X,    KC_C, KC_V, KC_B,   KC_N, KC_M, KC_COMM, KC_DOT,           KC_RSFT, KC_UP,   KC_SLSH,
        KC_LCTL, KC_LGUI,       KC_LALT,             KC_SPC,                               MO(_FN), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /*
     * [_FN] Fn Layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │`  │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │Ejc│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │     │   │   │End│RGB│   │   │   │Ins│   │PSc│   │   │Mute │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │   │SLc│   │   │   │Hm │   │   │   │   │   │Pause   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
     * │Vol +   │   │   │Cal│   │BLT│NLc│Ml │   │   │      │PgU│MSt│
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴──┬───┼───┼───┤
     * │Vol -│Rwd│FFd  │Play                       │   │Prv│PgD│Nxt│
     * └─────┴───┴─────┴───────────────────────────┴───┴───┴───┴───┘
     */
    [_FN] = LAYOUT_60_ansi_arrow_split_bs_7u_spc(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     _______, KC_EJCT,
        _______,          _______, _______, KC_END,  RGB_TOG, _______, _______, _______, KC_INS,  _______, KC_PSCR, _______,    _______, KC_MUTE,
        _______,          _______, KC_SLCK, _______, _______, _______, KC_HOME, _______, _______, _______, _______, _______,    KC_PAUS,
        KC_VOLU,          _______, _______, KC_CALC, _______, BL_TOGG, KC_NLCK, KC_MAIL, _______, _______,          MO(_RESET), KC_PGUP, KC_MSTP,
        KC_VOLD, KC_MRWD,          KC_MFFD,                   KC_MPLY,                                     _______, KC_MPRV,    KC_PGDN, KC_MNXT
    ),
    /*
     * [_RESET] Reset Layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │     │   │   │   │Rst│   │   │   │   │   │   │   │   │     │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │      │   │   │   │   │   │   │   │   │   │   │   │        │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┬───┤
     * │        │   │   │   │   │   │   │   │   │   │      │   │   │
     * ├─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴──┬───┼───┼───┤
     * │     │   │     │                           │   │   │   │   │
     * └─────┴───┴─────┴───────────────────────────┴───┴───┴───┴───┘
     */
    [_RESET] = LAYOUT_60_ansi_arrow_split_bs_7u_spc(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______,          _______,                   _______,                                     _______, _______, _______, _______
    )
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_setrgb(100, 255, 100);
}

// RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator
void update_led(void) {
    // Num Lock Indicator
    if (host_keyboard_led_state().num_lock) {
        rgblight_setrgb(225, 8, 0);
    }
    // Scroll Lock Indicator
    if (host_keyboard_led_state().scroll_lock) {
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 2);
    }
}

void led_set_user(uint8_t usb_led) {
    // Caps Lock Indicator
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(B2);
        rgblight_setrgb(255, 110, 0);
    }
    // Layer Indicator
    else {
        switch (get_highest_layer(layer_state)) {
            // Fn Layer Indicator
            case _FN:
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 1);
                break;
            // Reset Layer Indicator
            case _RESET:
                rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_GRADIENT + 3);
                break;
            // Base Layer Indicator
            case _BASE:
                rgblight_setrgb(100, 255, 100);
                break;
        }
        update_led();
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    update_led();
    return state;
}
