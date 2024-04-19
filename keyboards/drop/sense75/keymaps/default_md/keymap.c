// Copyright 2022 Massdrop, Inc.
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_keycodes {
    TEST_1 = SAFE_RANGE,
    TEST_2,
    TEST_3,
    TEST_4,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     * ┌───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐┌───┐
     * │Esc││F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12││PSc││   │
     * └───┘└───┴───┴───┴───┘└───┴───┴───┴───┴└───┴───┴───┴───┘└───┘└───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐┌───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp││Del│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤├───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  ││PgU│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤├───┤
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter ││PgD│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘└───┘
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│┌───┐
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┘│ ↑ │
     * │Ctrl│GUI │Alt │                        │Alt│GUI│Ctl│┌───┼───┼───┐
     * └────┴────┴────┴────────────────────────┴───┴───┴───┘│ ← │ ↓ │ → │
     *                                                      └───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_MPLY,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, RGB_TOG, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
        _______, RGB_MOD, RGB_VAD, RGB_SPD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______,          KC_END,
        _______,          RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW,_______, NK_TOGG, _______, _______, _______, _______,          _______, _______,
        MO(2),   _______, _______,                            EE_CLR,                             KC_APP,  _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, TEST_1,  TEST_2,  TEST_3,  TEST_4,  _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, AG_TOGG, _______, _______, _______, CL_TOGG,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [2] = { ENCODER_CCW_CW(_______, _______) }
};
#endif

static bool test_mode = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        switch (keycode) {
            case TEST_1:
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_RED);
                test_mode = true;
                break;
            case TEST_2:
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_GREEN);
                test_mode = true;
                break;
            case TEST_3:
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_BLUE);
                test_mode = true;
                break;
            case TEST_4:
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
                rgb_matrix_sethsv_noeeprom(HSV_WHITE);
                test_mode = true;
                break;
        }
    }
    return true;
};

bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(62, RGB_WHITE);
    } else if ((rgb_matrix_get_flags() & (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR)) == 0) {
        rgb_matrix_set_color(62, RGB_OFF);
    }

    if (get_highest_layer(layer_state) == 2) {
        if (!test_mode) {
            rgb_matrix_set_color_all(RGB_OFF);
        }

        if (keymap_config.swap_lalt_lgui) {
            rgb_matrix_set_color(55, RGB_GREEN);
        } else {
            rgb_matrix_set_color(55, RGB_RED);
        }
        if (keymap_config.swap_control_capslock) {
            rgb_matrix_set_color(59, RGB_GREEN);
        } else {
            rgb_matrix_set_color(59, RGB_RED);
        }
    } else if ((rgb_matrix_get_flags() & (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR)) == 0) {
        rgb_matrix_set_color(55, RGB_OFF);
        rgb_matrix_set_color(59, RGB_OFF);
    }
    return false;
}
