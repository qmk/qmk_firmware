/* Copyright 2020-2021 James Young (@noroadsleft)
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

#include "noroadsleft.h"

#define LAYOUT_75_ansi_wkl( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,       K114, K115, \
    K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K315, \
    K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411,       K413, K414, K415, \
    K500, K501,                         K506,                         K510, K512, K513, K514, K515  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  KC_NO, K114,  K115 }, \
    { K200,  KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214,  K215 }, \
    { K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315 }, \
    { K400,  KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  KC_NO, K413,  K414,  K415 }, \
    { K500,  K501,  KC_NO, KC_NO, KC_NO, KC_NO, K506,  KC_NO, KC_NO, KC_NO, K510,  KC_NO, K512,  K513,  K514,  K515 }  \
}

enum layer_names {
    _DV,
    _QW,
    _Q2,
    _FN,
    _SY
};

// Tap Dance declarations
enum tap_dances {
    LAG,
    RAG,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [LAG] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LGUI),
    [RAG] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_RGUI),
};

#define FN_CAPS LT(_FN,KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DV] = LAYOUT_75_ansi_wkl(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, MO(_SY),
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC,          KC_BSPC, KC_HOME,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS,          KC_PGUP,
        FN_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,             KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, TD(LAG),                                     KC_SPC,                                      TD(RAG), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_QW] = LAYOUT_75_ansi_wkl(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, MO(_SY),
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC, KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, TD(LAG),                                     KC_SPC,                                      TD(RAG), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_Q2] = LAYOUT_75_ansi_wkl(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, KC_LALT,                                     _______,                                     KC_RALT, _______, _______, _______, _______
    ),
    [_FN] = LAYOUT_75_ansi_wkl(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_DEL,  _______,
        _______, KC_CALC, KC_APP,  G_PUSH,  _______, _______, KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_PSCR, KC_SLCK, KC_PAUS,          _______,
        _______, M_SALL,  _______, G_FTCH,  _______, _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,          _______,          _______,
        _______,          M_UNDO,  M_CUT,   M_COPY,  M_PASTE, G_BRCH,  _______, KC_MUTE, KC_VOLD, KC_VOLU, _______,          _______, _______, _______,
        _______, _______,                                     _______,                                     _______, _______, _______, _______, _______
    ),
    [_SY] = LAYOUT_75_ansi_wkl(
        _______, TO(_DV), TO(_QW), _______, TG(_Q2), _______, _______, _______, RESET,   EEP_RST, DEBUG,   _______, VRSN,    _______, _______, _______,
        _______, _______, M_MDSWP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_DEL,  _______,
        _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, BL_DEC,  BL_TOGG, BL_INC,  BL_BRTG, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______,                                     _______,                                     _______, _______, _______, _______, _______
    ),
};

bool led_update_user(led_t led_state) {
    writePin(B2, !led_state.caps_lock);
    return false;
}
