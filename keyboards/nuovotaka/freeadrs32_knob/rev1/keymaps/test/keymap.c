// SPDX-FileCopyrightText: 2024 Takahiro Natsume ( @nuovotaka )
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"

#define NUM_DIRECTIONS 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        //,------+--------+--------+--------+--------+-------+--------+--------+--------.
        KC_1, KC_ESC, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,
        //|------+--------+--------+--------+--------+-------+--------+--------+--------|
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,
        //|------+--------+--------+--------+--------+-------+--------+--------+--------|
        KC_1, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J,
        //|------+--------+--------+--------+--------+-------+--------+--------+--------|
        KC_1, KC_LALT, KC_Z, KC_X, KC_C, KC_V, KC_N, KC_M, KC_ENT
        //|------+--------+--------+--------+--------+-------+--------+--------+--------|
        )};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {
        ENCODER_CCW_CW(KC_PAGE_UP, KC_PAGE_DOWN), // Encoder 1
        ENCODER_CCW_CW(KC_UP, KC_DOWN),           // Encoder 2
        ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)         // Encoder 3
    }};
#endif

void keyboard_post_init_user()
{
#ifdef RGBLIGHT_ENABLE
    // Force RGB lights to show test animation without writing EEPROM.
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
#endif
}
