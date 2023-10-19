// Copyright 2022 Conor Burns (@Conor-Burns)
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H
// clang-format off
enum layer_names {
  _HOME,
  _FN2,
  _FN3,
  _FN4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_HOME] = LAYOUT(
    KC_MPRV, KC_MNXT, KC_MPLY,
    KC_PGUP, KC_PGDN, TO(3),
    KC_HOME, KC_END,  TO(1)
),
[_FN2] = LAYOUT(
    _______, _______, _______,
    _______, _______, TO(0),
    _______, _______, TO(2)
),
[_FN3] = LAYOUT(
    RGB_HUI, RGB_HUD, RGB_MOD,
    RGB_SAI, RGB_SAD, TO(1),
    RGB_SPI, RGB_SPD, TO(3)
),
[_FN4] = LAYOUT(
    _______, _______, _______,
    _______, _______, TO(2),
    _______, _______, TO(0)
)
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_HOME] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN2]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_FN3]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_FN4]  = {ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
};
#endif
/* CAPS indicator */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        for (uint8_t i = led_min; i <= led_max; i++) {
            if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW) {
                rgb_matrix_set_color(i, RGB_RED);
            }
        }
    }
    return false;
}
/* oled stuff :) */
#ifdef OLED_ENABLE
/* Shows the name of the current layer and locks for the host (CAPS etc.) */
bool oled_task_user(void) {
    led_t led_state = host_keyboard_led_state();
    // clang-format off
    static const char PROGMEM logo[8][3][9] = {
        {{0x97, 0x98, 0x99, 0x9A, 0}, {0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0}, {0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0}},              /* L      num      CB */
        {{0xB7, 0xB8, 0xB9, 0xBA, 0}, {0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0}, {0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0}},              /* 1      num      CB */
        {{0xD7, 0xD8, 0xD9, 0xDA, 0}, {0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0}, {0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0}},              /* 1      cap      CB */
        {{0xC6, 0xC7, 0xC8, 0xC9, 0}, {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0}, {0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0}},              /* L      cap      CB */
        {{0xB7, 0x88, 0x89, 0xBA, 0}, {0xB7, 0x8A, 0x8B, 0xBA, 0},             {0xB7, 0x8C, 0x8D, 0xBA, 0}},                    /* 2       3       4  */
        {{0xD7, 0xA8, 0xA9, 0xDA, 0}, {0xD7, 0xAA, 0xAB, 0xDA, 0},             {0xD7, 0xAC, 0xAD, 0xDA, 0}},                    /* 2       3       4  */
        {{0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0},             {0xB8, 0xB9, 0x8A, 0x8B, 0x8A, 0x8B, 0x8E, 0x8F, 0}}, /* 0xcb    1337       */
        {{0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0},             {0xD8, 0xD9, 0xAA, 0xAB, 0xAA, 0xAB, 0xAE, 0xAF, 0}}, /* 0xcb    1337       */

    };
    // clang-format on
    oled_set_cursor(0, 0);
    oled_write_P(logo[0][0], false);
    oled_set_cursor(0, 3);
    oled_write_P(logo[3][0], false);
    switch (get_highest_layer(layer_state)) {
        case _HOME:
            oled_set_cursor(0, 1);
            oled_write_P(logo[1][0], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[2][0], false);
            break;
        case _FN2:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][0], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][0], false);
            break;
        case _FN3:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][1], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][1], false);
            break;
        case _FN4:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][2], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][2], false);
            break;
        default:
            oled_set_cursor(0, 1);
            oled_write_P(PSTR("    "), false);
            oled_set_cursor(0, 2);
            oled_write_P(PSTR("    "), false);
    }
    oled_set_cursor(8, 0);
    oled_write_P(led_state.num_lock ? logo[0][1] : PSTR("      "), false);
    oled_set_cursor(8, 1);
    oled_write_P(led_state.num_lock ? logo[1][1] : PSTR("      "), false);
    oled_set_cursor(8, 2);
    oled_write_P(led_state.caps_lock ? logo[2][1] : PSTR("      "), false);
    oled_set_cursor(8, 3);
    oled_write_P(led_state.caps_lock ? logo[3][1] : PSTR("      "), false);

    oled_set_cursor(16, 0);
    oled_write_P(logo[0][2], false);
    oled_set_cursor(16, 1);
    oled_write_P(logo[1][2], false);
    oled_set_cursor(16, 2);
    oled_write_P(logo[2][2], false);
    oled_set_cursor(16, 3);
    oled_write_P(logo[3][2], false);

    /* 0xCB 1337 */
    oled_set_cursor(0, 6);
    oled_write_P(logo[6][0], false);
    oled_set_cursor(0, 7);
    oled_write_P(logo[7][0], false);

    oled_set_cursor(13, 6);
    oled_write_P(logo[6][1], false);
    oled_set_cursor(13, 7);
    oled_write_P(logo[7][1], false);
    return false;
}
#endif
