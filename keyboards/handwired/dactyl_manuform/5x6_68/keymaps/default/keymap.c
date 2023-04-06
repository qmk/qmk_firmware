// Copyright 2023 Kostas Pagratis (@kpagratis)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers {
    _QWERTY,
    _LAYER2,
};

#define GUI_J   RGUI_T(KC_J)
#define GUI_F   LGUI_T(KC_F)
#define SFT_A   LSFT_T(KC_A)
#define CTL_S   LCTL_T(KC_S)
#define ALT_D   LALT_T(KC_D)
#define ALT_K   RALT_T(KC_K)
#define CTL_L   RCTL_T(KC_L)
#define SFT_SC  RSFT_T(KC_SCLN)
#define IMPORTS LALT(LCTL(KC_O))    //Intellij Organize Imports
#define LINES   LALT(LGUI(KC_L))    //Intellij Reformat Code
#define USAGES  LALT(KC_F7)         //Intelllj Find Usages
#define RENAME  LSFT(KC_F6)         //Intellij Refactor Rename

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
                 KC_EQL , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                          KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS,
                 KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                          KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS,
                 KC_ESC , SFT_A  , CTL_S  , ALT_D  , GUI_F  , KC_G   ,                          KC_H   , GUI_J  , ALT_K  , CTL_L  , SFT_SC , KC_QUOT,
                 KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,                          KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                 KC_GRV , KC_INS , KC_LEFT, KC_RGHT,                                                              KC_DOWN, KC_UP  , KC_LBRC, KC_RBRC,
                                                     KC_LCTL, KC_LALT, KC_HOME,        KC_DEL , KC_PGUP, KC_BSPC,
                                                     KC_SPC , KC_DEL , KC_END ,        MO(_LAYER2), KC_PGDN, KC_ENT
    ),
    [_LAYER2] = LAYOUT(
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
                 XXXXXXX, IMPORTS, XXXXXXX, USAGES , RENAME , XXXXXXX,                          XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
                 XXXXXXX, LINES  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                                              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                     XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX,XXXXXXX, XXXXXXX, 
                                                     XXXXXXX, XXXXXXX, XXXXXXX,         _______,XXXXXXX, XXXXXXX
    )
};
