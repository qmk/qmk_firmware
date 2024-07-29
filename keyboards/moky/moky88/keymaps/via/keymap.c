// Copyright 2023 VertorWang (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_tkl_f13_ansi( /* Base */
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, KC_PSCR, KC_SCRL, KC_PAUSE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,                   KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

    [1] = LAYOUT_tkl_f13_ansi( /* Base */
        QK_BOOT, KC_MSEL, KC_VOLD, KC_VOLU, KC_MUTE, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_MAIL, KC_WHOM, KC_CALC, KC_WSCH, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, RGB_TOG, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_SAI, RGB_MOD, _______, _______, _______,
        _______, TO(0),   TO(2),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                   RGB_VAI,
        _______, GU_TOGG, _______,                            _______,                            _______, _______, _______, _______, RGB_HUD, RGB_VAD, RGB_HUI),

    [2] = LAYOUT_tkl_f13_ansi(  /* Base */
        KC_ESC,  KC_BRMD, KC_BRMU, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_MUTE, KC_PSCR, KC_SCRL, KC_PAUSE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,                   KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(3),   KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

    [3] = LAYOUT_tkl_f13_ansi(  /* FN */
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE, KC_PSCR, KC_SCRL, KC_PAUSE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SPD, RGB_SPI, RGB_TOG, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_SAD, RGB_SAI, RGB_MOD, _______, _______, _______,
        _______, TO(0),   TO(2),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                   RGB_VAI,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, RGB_HUD, RGB_VAD, RGB_HUI),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {

    [0] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [1] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
};

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (get_highest_layer(default_layer_state | layer_state) == 1) {
        rgb_matrix_set_color(52, RGB_WHITE);
    } else if (get_highest_layer(default_layer_state | layer_state) == 3) {
        rgb_matrix_set_color(53, RGB_WHITE);
    }

    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(51, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    }
    if (host_keyboard_led_state().scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(15, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
    }
    if (keymap_config.no_gui) {
        if (get_highest_layer(default_layer_state) == 0) {
            RGB_MATRIX_INDICATOR_SET_COLOR(80, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
        } else if (get_highest_layer(default_layer_state) == 2) {
            RGB_MATRIX_INDICATOR_SET_COLOR(81, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS, RGB_MATRIX_MAXIMUM_BRIGHTNESS);
        }
    }

    return true;
}
