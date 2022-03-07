// Copyright 2022 Takuya Urakawa @hsgw (dm9records.com, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers { BASE, NUM, FUNC, CONF };
enum custom_keycodes { LED_EN = SAFE_RANGE };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_RBRC,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,               KC_INS, KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,
        KC_LCTL,                   KC_LALT, KC_LGUI, MO(NUM), KC_SPC,    KC_ENT, MO(FUNC), KC_RALT, KC_MENU, KC_RCTL,  KC_RSFT
    ),
    [NUM] = LAYOUT(
        KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,      KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,
        KC_CAPS, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6),   S(KC_7), S(KC_8), S(KC_9), S(KC_0), S(KC_MINS),S(KC_EQL),
        _______, _______, _______, _______, _______, _______,            KC_PSCR, _______, _______, _______, _______,  KC_BSLS,
        _______,                   _______, _______, _______, _______,   _______, _______, _______, _______, _______,  _______
    ),
    [FUNC] = LAYOUT(
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, _______, _______, _______, _______, _______, _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
        _______,                   _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______
    ),
    [CONF] = LAYOUT(
        RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        LED_EN,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LED_EN:
            if (record->event.pressed) {
                lain_enable_leds_toggle();
            }
            return false;
        default:
            break;
    }
    return true;
}

// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_t computed = update_tri_layer_state(state, NUM, FUNC, CONF);
    switch (get_highest_layer(computed)) {
        case NUM:
            lain_set_led(1, 1);
            lain_set_led(2, 0);
            break;
        case FUNC:
            lain_set_led(1, 0);
            lain_set_led(2, 1);
            break;
        case CONF:
            lain_set_led(1, 1);
            lain_set_led(2, 1);
            break;
        default:
            lain_set_led(1, 0);
            lain_set_led(2, 0);
            break;
    }
    return computed;
}

bool led_update_user(led_t led_state) {
    lain_set_led(0, led_state.caps_lock);
    return false;
}
