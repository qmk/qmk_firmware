/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "layers.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: DREN
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RAIS/ESC|   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/BS |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |LShift|LShift|  |LShift|LShift|   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GUI  | Del  | Enter| Space| Esc  |  | Enter| Space| Tab  | Bksp | AltGr|
 *                        |      |      | Alt  | Lower| Raise|  | Lower| Raise|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_BASE] = LAYOUT(
      LT(_NAVIGATION, KC_ESC),       KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE,
      MT(MOD_LCTL, KC_BSPC),   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,                 KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LSFT,   KC_LSFT, KC_LSFT, KC_LSFT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
              KC_LGUI, KC_DEL, MT(MOD_LALT, KC_ENT), LT(_SYMBOLS, KC_SPC), LT(_NAVIGATION, KC_ESC), LT(_SYMBOLS, KC_ENT), LT(_NAVIGATION, KC_SPC), KC_TAB,  KC_BSPC, KC_RALT
    ),

    // #todo: format base layer
    [_BASE] = LAYOUT(KC_TAB, KC_Q, KC_W, KC_O, KC_L, KC_P, KC_Y, KC_U, KC_G, KC_M, KC_J, KC_BSPC, KC_ESC, LCTL_T(KC_D), LALT_T(KC_R), LGUI_T(KC_E), LSFT_T(KC_N), SGUI_T(KC_F), SGUI_T(KC_SCLN), RSFT_T(KC_I), RGUI_T(KC_S), RALT_T(KC_T), RCTL_T(KC_A), KC_QUOT, KC_P0, KC_Z, KC_C, KC_X, KC_H, KC_V, KC_NO, KC_NO, KC_NO, KC_NO, KC_K, KC_B, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LALT, KC_LGUI, KC_ESC, LT(3,KC_ENT), LT(5,KC_TAB), LT(6,KC_BSPC), LT(4,KC_SPC), KC_ESC, KC_RCTL, KC_RSFT),

/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RAIS/ESC|   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/BS |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |LShift|LShift|  |LShift|LShift|   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GUI  | Del  | Enter| Space| Esc  |  | Enter| Space| Tab  | Bksp | AltGr|
 *                        |      |      | Alt  | Lower| Raise|  | Lower| Raise|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ALT] = LAYOUT(
      LT(_NAVIGATION, KC_ESC),       KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE,
      MT(MOD_LCTL, KC_BSPC),   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,                 KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LSFT,   KC_LSFT, KC_LSFT, KC_LSFT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
              KC_LGUI, KC_DEL, MT(MOD_LALT, KC_ENT), LT(_SYMBOLS, KC_SPC), LT(_NAVIGATION, KC_ESC), LT(_SYMBOLS, KC_ENT), LT(_NAVIGATION, KC_SPC), KC_TAB,  KC_BSPC, KC_RALT
    ),

    // #todo: format base layer
    [_ALT] = LAYOUT(KC_TRNS, KC_TAB, KC_W, KC_B, KC_G, KC_Q, KC_J, KC_L, KC_O, KC_Y, KC_SCLN, KC_TRNS, KC_TRNS, LCTL_T(KC_D), LALT_T(KC_S), LGUI_T(KC_T), LSFT_T(KC_R), SGUI_T(KC_W), SGUI_T(KC_DOT), RSFT_T(KC_N), RGUI_T(KC_I), RALT_T(KC_A), RCTL_T(KC_U), KC_QUOT, KC_TRNS, KC_Z, KC_V, KC_C, KC_H, KC_X, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_COMM, KC_M, KC_F, KC_P, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LT(3,KC_E), LT(5,KC_ENT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

/*
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RAIS/ESC|   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/BS |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |LShift|LShift|  |LShift|LShift|   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GUI  | Del  | Enter| Space| Esc  |  | Enter| Space| Tab  | Bksp | AltGr|
 *                        |      |      | Alt  | Lower| Raise|  | Lower| Raise|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_QWERTY] = LAYOUT(
      LT(_NAVIGATION, KC_ESC),       KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE,
      MT(MOD_LCTL, KC_BSPC),   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,                 KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_LSFT,   KC_LSFT, KC_LSFT, KC_LSFT, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
              KC_LGUI, KC_DEL, MT(MOD_LALT, KC_ENT), LT(_SYMBOLS, KC_SPC), LT(_NAVIGATION, KC_ESC), LT(_SYMBOLS, KC_ENT), LT(_NAVIGATION, KC_SPC), KC_TAB,  KC_BSPC, KC_RALT
    ),

    // #todo: format base layer
    [_QWERTY] = LAYOUT(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_NO, KC_NO, KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RGUI, KC_RALT, KC_RCTL),

/*
 * Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |      |      |      |      |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |  ;   |  =   |  |  =   |  ;   |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMBOLS] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                     _______, _______, _______, _______, _______, KC_BSLS,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                                 _______, _______, _______, KC_SCLN, KC_EQL,  KC_EQL,  KC_SCLN, _______, _______, _______
    ),

    // #todo: format base layer
    [_SYMBOLS] = LAYOUT(KC_AMPR, KC_CIRC, KC_AT, KC_LBRC, KC_RBRC, KC_HASH, KC_PERC, KC_7, KC_8, KC_9, KC_PSLS, KC_BSPC, KC_UNDS, KC_DLR, KC_EXLM, KC_LPRN, KC_RPRN, KC_GRV, KC_PPLS, KC_4, KC_5, KC_6, KC_PAST, KC_COLN, TG(3), KC_LT, KC_GT, KC_LCBR, KC_RCBR, KC_BSLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_PDOT, KC_1, KC_2, KC_3, KC_0, KC_PCMM, KC_TILD, KC_DQUO, KC_QUOT, KC_NO, KC_NO, KC_PEQL, KC_PMNS, KC_RGUI, KC_RALT, KC_RCTL),

/*
 * Navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next | VolUp|                              | Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | Mute | VolDn|      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NAVIGATION] = LAYOUT(
      _______, KC_1, 	  KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                                     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
      _______, _______, _______, _______, KC_MUTE, KC_VOLD, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    // #todo: format base layer
    [_NAVIGATION] = LAYOUT(DF(2), KC_NO, KC_NO, KC_BRID, KC_BRIU, KC_VOLU, LGUI(KC_LEFT), LALT(KC_LEFT), LALT(KC_RGHT), LGUI(KC_RGHT), KC_NO, KC_DEL, DF(1), KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, DF(0), KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLD, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO, TO(6), KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_BSPC, KC_NO, KC_NO, RGUI(KC_V), RGUI(KC_C), RGUI(KC_X)),

/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_VISUALSTUDIO] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    // #todo: format base layer
    [_VISUALSTUDIO] = LAYOUT(LCTL(KC_PAUS), KC_NO, LCTL(KC_K), LCTL(KC_F9), KC_F9, LALT(KC_G), KC_NO, LCTL(KC_LEFT), LCTL(KC_RGHT), KC_NO, KC_NO, KC_DEL, KC_NO, KC_TAB, KC_NO, KC_F11, KC_F10, KC_F5, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_NO, KC_PSLS, KC_NO, KC_NO, LSFT(KC_F11), LCTL(KC_F10), KC_I, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LALT(KC_LEFT), LALT(KC_RGHT), KC_NO, KC_NO, KC_APP, TG(5), KC_NO, KC_LALT, KC_ENT, KC_NO, MO(7), KC_ENT, KC_NO, KC_NO, KC_NO),

    // #todo: format base layer
    [_MOUSE] = LAYOUT(TO(0), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_U, KC_WH_L, KC_WH_R, KC_NO, KC_ACL2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_MS_L, KC_MS_U, KC_MS_R, KC_ACL1, TO(0), KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MS_D, KC_NO, KC_ACL0, KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN4, KC_BTN5),

    // #todo: format base layer
    [_FUNCTIONKEYS] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_LSFT, KC_LCTL, KC_LALT, KC_RGUI, KC_NO, KC_NO, KC_F5, KC_F6, KC_F7, KC_F8, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO)

// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, _SYMBOLS, _NAVIGATION, _VISUALSTUDIO);
// }


