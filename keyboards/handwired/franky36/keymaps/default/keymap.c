// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │   │   │ C │ G │ L │ R │ A │ S │   │   │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_QWERTY] = LAYOUT_ortho_4x10(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        _______, _______, KC_LCTL, KC_LALT,KC_LSFT,  KC_RSFT,    KC_RALT, KC_RSFT, _______, _______
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │   │   │ C │ G │ L │ R │ A │ S │   │   │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_LOWER] = LAYOUT_ortho_4x10(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        _______, _______, KC_LCTL, KC_LGUI,LOWER,   RAISE,    KC_RALT, KC_RSFT, _______, _______
    ),
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │   │   │ C │ G │ L │ R │ A │ S │   │   │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_RAISE] = LAYOUT_ortho_4x10(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
        _______, _______, KC_LCTL, KC_LGUI,LOWER,   RAISE,    KC_RALT, KC_RSFT, _______, _______
    )
};
