// Copyright 2022 Steven Karrmann (@skarrmann)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _SYMBOL,
    _NAVIGATION,
    _FUNCTION
};

#define MO_SYM MO(_SYMBOL)
#define MO_NAV MO(_NAVIGATION)
#define MO_FUN MO(_FUNCTION)
#define OS_LCTL OSM(MOD_LCTL)
#define OS_LSFT OSM(MOD_LSFT)
#define OS_LALT OSM(MOD_LALT)
#define OS_LGUI OSM(MOD_LGUI)
#define OS_RCTL OSM(MOD_RCTL)
#define OS_RSFT OSM(MOD_RSFT)
#define OS_RALT OSM(MOD_RALT)
#define OS_RGUI OSM(MOD_RGUI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x5_2(
        KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   ,
        KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_QUOT,
        KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,
                                   MO_NAV , KC_LSFT, KC_SPC , MO_SYM
    ),
    [_SYMBOL] = LAYOUT_split_3x5_2(
        KC_SCLN, KC_LBRC, KC_RBRC, KC_5   , XXXXXXX, XXXXXXX, KC_6   , KC_MINS, KC_EQL , KC_GRV ,
        KC_1   , KC_2   , KC_3   , KC_4   , KC_BSLS, XXXXXXX, KC_7   , KC_8   , KC_9   , KC_0   ,
        OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX, XXXXXXX, OS_RCTL, OS_RSFT, OS_RALT, OS_RGUI,
                                   MO_FUN , _______, _______, _______
    ),
    [_NAVIGATION] = LAYOUT_split_3x5_2(
        KC_PSCR, KC_INS , KC_APP , KC_DEL , XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END ,
        KC_ESC , KC_TAB , KC_ENT , KC_BSPC, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT,
        OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX, XXXXXXX, OS_RCTL, OS_RSFT, OS_RALT, OS_RGUI,
                                   _______, _______, _______, MO_FUN
    ),
    [_FUNCTION] = LAYOUT_split_3x5_2(
        KC_F1  , KC_F2  , KC_F3  , KC_F4  , QK_BOOT, KC_SCRL, KC_F9  , KC_F10 , KC_F11 , KC_F12 ,
        KC_F5  , KC_F6  , KC_F7  , KC_F8  , XXXXXXX, KC_CAPS, KC_MUTE, KC_VOLD, KC_VOLU, KC_PAUS,
        OS_LGUI, OS_LALT, OS_LSFT, OS_LCTL, XXXXXXX, KC_NUM,  OS_RCTL, OS_RSFT, OS_RALT, OS_RGUI,
                                   _______, _______, _______, _______
    ),
};