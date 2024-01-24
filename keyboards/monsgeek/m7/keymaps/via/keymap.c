// Copyright 2024 jonylee@hfd (@jonylee1986)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
// clang-format off
enum __layers {
    WIN_B,
    WIN_FN,
    MAC_B,
    MAC_FN
};
#define KC_SIRI LGUI(KC_SPC)
#define KC_TASK LGUI(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [WIN_B] = LAYOUT_ansi( /* Base */
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,KC_EQL,   KC_BSPC, KC_INS,  KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,KC_RBRC,  KC_BSLS, KC_DEL,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT,MO(WIN_FN),KC_RCTL,         KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_FN] = LAYOUT_ansi( /* FN */
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11, KC_F12,   _______, _______, KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  DF(MAC_B),KC_PSCR,RGB_SPD, RGB_SPI, _______, RGB_MOD, KC_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______,          RGB_HUI,
        _______, _______, _______, KC_CALC, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, RGB_VAI,
        _______, GU_TOGG, _______,                   _______,                            _______, _______, _______,          RGB_SAD, RGB_VAD, RGB_SAI),

    [MAC_B] = LAYOUT_ansi( /* Base */
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,KC_EQL,   KC_BSPC, KC_INS,  KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,KC_RBRC,  KC_BSLS, KC_DEL,  KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                   KC_RSFT, KC_UP,
        KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI,MO(MAC_FN),KC_RCTL,         KC_LEFT, KC_DOWN, KC_RGHT),

    [MAC_FN] = LAYOUT_ansi( /* FN */
        KC_GRV,  KC_BRID, KC_BRIU, KC_MCTL, KC_SIRI, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_INS,  DF(WIN_B),KC_PSCR,RGB_SPD, RGB_SPI, _______, RGB_MOD, KC_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, _______, _______,          RGB_HUI,
        _______, _______, _______, KC_CALC, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,                   _______, RGB_VAI,
        _______, _______, _______,                   _______,                            _______, _______, _______,          RGB_SAD, RGB_VAD, RGB_SAI),
};
// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case RGB_TOG:
        if (record->event.pressed)
        {
            switch (rgb_matrix_get_flags())
            {
            case LED_FLAG_ALL:
            {
                rgb_matrix_set_flags(LED_FLAG_NONE);
                rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
            default:
            {
                rgb_matrix_set_flags(LED_FLAG_ALL);
            }
            break;
            }
        }
        if (!rgb_matrix_is_enabled())
        {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable();
        }
        return false;
    default:
        return true;
    }
}
#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max)
{

    if (host_keyboard_led_state().caps_lock)
    {
        RGB_MATRIX_INDICATOR_SET_COLOR(32, 125, 125, 125);
    }
    else
    {
        if (!rgb_matrix_get_flags())
        {
            RGB_MATRIX_INDICATOR_SET_COLOR(32, 0, 0, 0);
        }
    }
    if (keymap_config.no_gui)
    {
        RGB_MATRIX_INDICATOR_SET_COLOR(59, 125, 125, 125);
    }
    else
    {
        if (!rgb_matrix_get_flags())
        {
            RGB_MATRIX_INDICATOR_SET_COLOR(59, 0, 0, 0);
        }
    }

    return true;
}
#endif
