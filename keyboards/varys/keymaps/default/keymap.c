// Copyright 2023 Vinay Komaravolu
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_number {
    _QWERTY,
    _LOWER,
    _RAISE,
    _MISC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Default keyboard settings
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   WHOM|    |   Mute|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | Lower |LGUI | /Space  /       \Enter \  |BackSP |Upper | RAlt |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
    [_QWERTY] = LAYOUT(
    KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                              KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
    KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_WHOM,    KC_AUDIO_MUTE,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                               KC_LALT, TL_LOWR,KC_LGUI, KC_SPC,   KC_ENT, KC_BSPC,  TL_UPPR , KC_RALT
    ),
    [_LOWER] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  ,                   KC_F7  ,KC_F8   ,KC_F9   ,KC_F10  ,KC_F11  ,KC_F12,
    KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
    KC_CAPS, KC_SCRL, KC_NUM, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                               _______, _______, _______, _______, _______,  _______, _______, _______ 
    ),
    [_RAISE] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_KB_MUTE, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP	,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK,
    KC_F13 ,KC_F14  ,KC_F15  ,KC_F16  ,KC_F17  ,KC_F18  ,                   KC_F19 ,KC_F20  ,KC_F21  ,KC_F22  ,KC_F23  ,KC_F24  ,
    KC_PSCR, KC_INS, KC_HOME, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, KC_PAGE_UP, KC_PAGE_DOWN,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,
                              _______, _______, _______, _______, _______,  _______, _______, _______ 
    ),
    [_MISC] = LAYOUT(
    KC_SYSTEM_POWER, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_MY_COMPUTER,
    KC_SYSTEM_WAKE, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_WWW_HOME,
    KC_SYSTEM_SLEEP, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_MAIL,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,  _______, _______, _______ 
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_QWERTY] = {ENCODER_CCW_CW(KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP),
                 ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_RAISE] = {ENCODER_CCW_CW(_______, _______),
                ENCODER_CCW_CW(_______, _______)},
    [_LOWER] = {ENCODER_CCW_CW(_______, _______),
                ENCODER_CCW_CW(_______, _______)},
    [_MISC] = {ENCODER_CCW_CW(_______, _______),
               ENCODER_CCW_CW(_______, _______)}};
#endif