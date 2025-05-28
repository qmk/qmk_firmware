// Copyright 2025 Ryan Chomistek
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t volDown = KC_AUDIO_VOL_DOWN;
const uint16_t volMute = KC_AUDIO_MUTE;
const uint16_t volUp = KC_AUDIO_VOL_UP;

const uint16_t prevTrack = KC_MEDIA_PREV_TRACK;
const uint16_t playPause = KC_MEDIA_PLAY_PAUSE;
const uint16_t nextTrack = KC_MEDIA_NEXT_TRACK;

const uint16_t MOMENTARY = MO(1);
const uint16_t TRANS = KC_TRNS;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
    //  1           2               3               4               5               6           7           8           9           10          11          12          13          14          15          16              17              18          19
        KC_NO,      KC_KP_SLASH,    KC_KP_ASTERISK, KC_KP_MINUS,    KC_ESCAPE,      KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINUS,       KC_EQUAL,       KC_BSPC,    KC_GRAVE,
        KC_KP_7,    KC_KP_8,        KC_KP_9,        KC_KP_PLUS,     KC_TAB,         KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,        KC_RBRC,        KC_BSLS,    KC_PGDN,
        KC_KP_4,    KC_KP_5,        KC_KP_6,        KC_NO,          MO(1),          KC_A,       KC_S,       KC_D,       KC_F,       KC_G,       KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOTE,       KC_NO,          KC_ENTER,   KC_DELETE,
        KC_KP_1,    KC_KP_2,        KC_KP_3,        KC_KP_ENTER,    KC_LSFT,        KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMMA,   KC_DOT,     KC_SLASH,   KC_NO,          KC_RSFT,        KC_UP,      KC_NO,
        KC_KP_0,    KC_NO,          KC_KP_DOT,      KC_NO,          KC_LCTL,        KC_LWIN,    KC_LALT,    KC_NO,      KC_NO,      KC_SPACE,   KC_NO,      KC_NO,      KC_NO,      KC_RALT,    KC_RWIN,    KC_RCTL,        KC_LEFT,        KC_DOWN,    KC_RIGHT
    ),
    [1] = LAYOUT(
    //  1           2               3               4               5               6           7           8           9           10          11          12          13          14          15          16              17              18          19
        TRANS,      TRANS,          TRANS,          TRANS,          KC_GRAVE,       KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,         KC_F12,         TRANS,      KC_PGUP,
        TRANS,      TRANS,          TRANS,          TRANS,          TRANS,          volDown,    volMute,    volUp,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,          TRANS,          TRANS,      KC_PGDN,
        TRANS,      TRANS,          TRANS,          TRANS,          MOMENTARY,      prevTrack,  playPause,  nextTrack,  TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,          TRANS,          TRANS,      TRANS,
        TRANS,      TRANS,          TRANS,          TRANS,          TRANS,          TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,          TRANS,          TRANS,      TRANS,
        TRANS,      TRANS,          TRANS,          TRANS,          TRANS,          TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,      TRANS,          TRANS,          TRANS,      TRANS
    ),

};
