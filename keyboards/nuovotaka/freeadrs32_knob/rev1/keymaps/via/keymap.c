// SPDX-FileCopyrightText: 2024 Takahiro Natsume ( @nuovotaka )
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"

#define FN MO(1)
#define R_M_F RGB_MODE_FORWARD
#define R_M_R RGB_MODE_REVERSE
#define LALTZ LALT(KC_Z)
#define SFTF11 LSFT(KC_F11)
#define LSFTF LSFT(KC_F)

#define NUM_DIRECTIONS 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        //,------+--------+--------+--------+--------+-------+--------+--------+--------.
        KC_1, KC_ESC, SFTF11, KC_F11, KC_H, KC_I, KC_O, KC_P, KC_DEL,
        //|------+--------+--------+--------+--------+-------+--------+--------+--------|
        KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_TAB,
        //|------+--------+--------+--------+--------+-------+--------+--------+--------|
        KC_1, LSFTF, KC_A, KC_S, KC_D, KC_F, KC_K, KC_L, KC_LGUI,
        //|------+--------+--------+--------+--------+-------+--------+--------+--------|
        KC_1, LALTZ, KC_X, KC_C, KC_G, FN, KC_M, KC_J, KC_ENT
        //|------+--------+--------+--------+--------+-------+--------+--------+--------|
        ),
    [1] = LAYOUT(
        //,-------+--------+--------+--------+--------+--------+--------+--------+--------.
         KC_1, S(KC_ESC), SFTF11, S(KC_F11), S(KC_H), S(KC_I), S(KC_O), S(KC_P), S(KC_DEL),
        //|-------+--------+--------+--------+--------+--------+--------+--------+--------|
        S(KC_Q), S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_TAB),
        //|-------+--------+--------+--------+--------+--------+--------+--------+--------|
        KC_1, LSFTF, S(KC_A), S(KC_S), S(KC_D), S(KC_F), S(KC_K), S(KC_L), S(KC_LGUI),
        //|-------+--------+--------+--------+--------+--------+--------+--------+--------|
         KC_1, LALTZ, S(KC_X), S(KC_C), S(KC_G), _______, LT(2, S(KC_M)), S(KC_J), S(KC_ENT)
        //|-------+--------+--------+--------+--------+--------+--------+--------+--------|
        ),
    [2] = LAYOUT(
        //,-------+--------+--------+--------+--------+--------+--------+--------+--------.
        _______, _______, _______, _______, _______, _______, R_M_F, R_M_R, QK_BOOT,
        //|-------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______, _______,
        //|-------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______, _______, QK_RBT,
        //|-------+--------+--------+--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______, _______, _______, _______
        //|-------+--------+--------+--------+--------+--------+--------+--------+--------|
        )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {
        ENCODER_CCW_CW(KC_PAGE_UP, KC_PAGE_DOWN), // Encoder 1
        ENCODER_CCW_CW(KC_UP, KC_DOWN),           // Encoder 2
        ENCODER_CCW_CW(KC_LEFT, KC_RIGHT)         // Encoder 3
    },
    [1] = {
        ENCODER_CCW_CW(_______, _______), // Encoder 1
        ENCODER_CCW_CW(RGB_HUD, RGB_HUI), // Encoder 2
        ENCODER_CCW_CW(RGB_VAD, RGB_VAI)  // Encoder 3
    },
    [2] = {
        ENCODER_CCW_CW(_______, _______), // Encoder 1
        ENCODER_CCW_CW(_______, _______), // Encoder 2
        ENCODER_CCW_CW(_______, _______)  // Encoder 3
    }};
#endif

#ifdef OLED_ENABLE

#include "keyboards/nuovotaka/lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
    free32knob_oled_render_keyinfo();
    free32knob_oled_render_layerinfo();
}
#endif
