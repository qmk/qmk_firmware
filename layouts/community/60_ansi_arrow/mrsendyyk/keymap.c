/*
 * Copyright (C) 2020 Sendy YK <mr@sendyyk.com>.
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

/*
 * 60% ANSI Arrow Keyboard Layout and Keymap
 * with RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator
 * by Sendy YK <https://mr.sendyyk.com>.
 */

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE, // Default Layer
    _FN, // Fn Layer 1
    _SETTINGS // Fn Layer 2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default Layer
    [_BASE] = LAYOUT_60_ansi_arrow(
        KC_GESC, KC_1,    KC_2, KC_3,    KC_4, KC_5, KC_6,   KC_7, KC_8, KC_9,    KC_0,           KC_MINS,        KC_EQL,           KC_BSPC,
        KC_TAB,           KC_Q, KC_W,    KC_E, KC_R, KC_T,   KC_Y, KC_U, KC_I,    KC_O,           KC_P,           KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS,          KC_A, KC_S,    KC_D, KC_F, KC_G,   KC_H, KC_J, KC_K,    KC_L,           KC_SCLN,        KC_QUOT, KC_ENT,
        KC_LSFT,          KC_Z, KC_X,    KC_C, KC_V, KC_B,   KC_N, KC_M, KC_COMM, KC_DOT,                         KC_RSFT, KC_UP,   KC_SLSH,
        KC_LCTL, KC_LGUI,       KC_LALT,             KC_SPC,                      LT(2, KC_RALT), LT(1, KC_RCTL), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    // Fn Layer 1
    [_FN] = LAYOUT_60_ansi_arrow(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
        KC_BRIU,          KC_TRNS, KC_TRNS, KC_END,  RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_TRNS, KC_PSCR, KC_TRNS, KC_TRNS, KC_EJCT,
        KC_BRID,          KC_TRNS, KC_SLCK, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE,
        KC_VOLU,          KC_TRNS, KC_TRNS, KC_CALC, KC_TRNS, KC_TRNS, KC_NLCK, KC_MAIL, KC_TRNS, KC_TRNS,          KC_PAUS, KC_PGUP, KC_TRNS,
        KC_VOLD, KC_MRWD,          KC_MFFD,                   KC_MPLY,                            KC_MSTP, KC_TRNS, KC_MPRV, KC_PGDN, KC_MNXT
    ),
    // Fn Layer 2
    [_SETTINGS] = LAYOUT_60_ansi_arrow(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,          KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(0, 0, 0);
}

// RGB Lighting/LED/Underglow as Caps Lock, Num Lock, Scroll Lock, and Layer Indicator
void update_led(void) {
    // Num Lock Indicator
    if (host_keyboard_led_state().num_lock) {
        rgblight_setrgb(225, 8, 0);
    }
    // Scroll Lock Indicator
    if (host_keyboard_led_state().scroll_lock) {
        rgblight_setrgb(255, 110, 0);
    }
}

void led_set_user(uint8_t usb_led) {
    // Caps Lock Indicator
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(B2);
        rgblight_setrgb(100, 255, 100);
    }
    // Layer Indicator
    else {
        switch (get_highest_layer(layer_state)) {
            // Fn Layer 1 Indicator
            case _FN:
                rgblight_setrgb(100, 255, 100);
                break;
            // Fn Layer 2 Indicator
            case _SETTINGS:
                rgblight_setrgb(100, 255, 100);
                break;
            // Default Layer Indicator
            case _BASE:
                rgblight_setrgb(0, 0, 0);
                break;
        }
        update_led();
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    update_led();
    return state;
}
