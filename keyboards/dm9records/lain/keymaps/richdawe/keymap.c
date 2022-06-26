// Copyright 2022 Takuya Urakawa @hsgw (dm9records.com, 5z6p.com)
// Copyright 2022 Richard Dawe
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers { BASE, NUM, SYM, FUNC, CONF };
enum custom_keycodes { LED_EN = SAFE_RANGE };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [BASE] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_RBRC,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,               KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SFTENT,
        KC_LCTL,                   KC_LGUI, KC_LALT, MO(SYM), KC_SPC,    KC_SPC, MO(NUM), KC_RALT, KC_RCTL, KC_GRV,  KC_SLSH
    ),
    [NUM] = LAYOUT(
        _______, _______, KC_1,    KC_2,    KC_3,    KC_COLON,_______,   _______, KC_MINS, KC_EQL,  _______, _______, KC_DEL,
        _______, _______, KC_4,    KC_5,    KC_6,    KC_DOT,  _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
        _______, _______, KC_7,    KC_8,    KC_9,    KC_0,               _______, _______, _______, _______, _______, _______,
        _______,                   _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______
    ),
    [SYM] = LAYOUT(
        _______, _______, S(KC_1), S(KC_2), S(KC_3), _______, KC_LPRN,   _______, S(KC_MINS), S(KC_EQL), _______, _______, KC_DEL,
        _______, _______, S(KC_4), S(KC_5), S(KC_6), _______, KC_RPRN,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
        _______, _______, S(KC_7), S(KC_8), S(KC_9), S(KC_0),            _______, _______, _______, _______, _______, _______,
        _______,                   _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______
    ),
    [FUNC] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_CAPS, _______, _______, _______, _______, _______, _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
        _______, _______, _______, _______, _______, _______,            _______, _______, _______, _______, _______, _______,
        _______,                   _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______
    ),
    [CONF] = LAYOUT(
        QK_BOOT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
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
        case SYM:
            lain_set_led(1, 0);
            lain_set_led(2, 1);
            break;
        case FUNC:
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
