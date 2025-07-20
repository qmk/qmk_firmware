// Copyright 2022 Ethan (@rocketstrong)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/*
 *          ┌──┐┌──┐┌──┐┌──┐┌──┐            ┌──┐┌──┐┌──┐┌──┐┌──┐
 *┌────┐┌──┐│  ││  ││  ││  ││  │            │  ││  ││  ││  ││  │┌──┐┌────┐
 *│    ││  │└──┘└──┘└──┘└──┘└──┘            └──┘└──┘└──┘└──┘└──┘│  ││    │
 *└────┘└──┘┌──┐┌──┐┌──┐┌──┐┌──┐            ┌──┐┌──┐┌──┐┌──┐┌──┐└──┘└────┘
 *┌────┐┌──┐│  ││  ││  ││  ││  │            │  ││  ││  ││  ││  │┌──┐┌────┐
 *│    ││  │└──┘└──┘└──┘└──┘└──┘            └──┘└──┘└──┘└──┘└──┘│  ││    │
 *└────┘└──┘┌──┐┌──┐┌──┐┌──┐┌──┐            ┌──┐┌──┐┌──┐┌──┐┌──┐└──┘└────┘
 *┌────┐┌──┐│  ││  ││  ││  ││  │            │  ││  ││  ││  ││  │┌──┐┌────┐
 *│    ││  │└──┘└──┘└──┘└──┘└──┘            └──┘└──┘└──┘└──┘└──┘│  ││    │
 *└────┘└──┘┌──┐┌──┐┌──┐┌──┐                    ┌──┐┌──┐┌──┐┌──┐└──┘└────┘
 *┌────┐┌──┐│  ││  ││  ││  │                    │  ││  ││  ││  │┌──┐┌────┐
 *│    ││  │└──┘└──┘└──┘└──┘                    └──┘└──┘└──┘└──┘│  ││    │
 *└────┘└──┘┌──┐┌──┐                                    ┌──┐┌──┐└──┘└────┘
 *  ┌──┐┌──┐│  ││  │  ┌──┐ ┌──┐              ┌──┐ ┌──┐  │  ││  │┌──┐┌──┐
 *  │  ││  │└──┘└──┘  │  │ │  │              │  │ │  │  └──┘└──┘│  ││  │
 *  └──┘└──┘          │  │ │  │              │  │ │  │          └──┘└──┘
 *                    │  │ └──┘              └──┘ │  │
 *                    └──┘ ┌──┐ ┌──┐    ┌──┐ ┌──┐ └──┘
 *                         │  │ │  │    │  │ │  │
 *                         └──┘ └──┘    └──┘ └──┘
 *                         ┌──┐┌──┐      ┌──┐┌──┐
 *                         │  ││  │      │  ││  │
 *                         └──┘└──┘      └──┘└──┘
 */

enum Colemaklayers {
  _ARSTG,
  _NUMPAD,
  _SYMBOLS
};

enum custom_keycodes {
    AD_DDS = SAFE_RANGE,
    AD_SCOPE
};

#define TT_NUM TT(_NUMPAD)
#define TT_SYM TT(_SYMBOLS)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AD_DDS:
            if (!record->event.pressed) {
                // when keycode AD_DDS is pressed
                SEND_STRING("../");
            } else {
                // when keycode AD_DDS is released
            }
            break;
        case AD_SCOPE:
            if (!record->event.pressed) {
                // when keycode AD_DDS is pressed
                SEND_STRING("::");
            } else {
                // when keycode AD_DDS is released
            }
            break;
    }
    return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_ARSTG] = LAYOUT(
        KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_MINS  ,      KC_EQL  , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_ESC  ,
        KC_TAB  , KC_Q    , KC_W    , KC_F    , KC_P    , KC_B    , KC_LBRC ,       KC_RBRC , KC_J    , KC_L    , KC_U    , KC_Y    , KC_SCLN , KC_BSLS ,
        KC_ESC  , KC_A    , KC_R    , KC_S    , KC_T    , KC_G    , KC_PSCR ,       KC_PAUS , KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , KC_QUOT ,
        KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_D    , KC_V    ,                           KC_K    , KC_H    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT ,
        KC_LCTL , KC_LGUI , KC_LALT , KC_DEL  ,                                                                   KC_LEFT , KC_UP   , KC_DOWN , KC_RIGHT,
                                                        KC_SPC  , KC_BSPC ,           KC_TAB  , KC_ENT  ,
                                                          TT_NUM  , KC_LSFT ,       KC_RSFT , TT_SYM  ,
                                                          KC_LCTL , KC_LALT ,       KC_RALT , KC_RCTL
    ),
    [_NUMPAD] = LAYOUT(
        KC_NO   , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,       KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_NO   ,
        KC_TRNS , KC_PGUP , KC_HOME , KC_UP   , KC_END  , KC_NO   , KC_NO   ,       KC_NO   , KC_NUM  , KC_P7   , KC_P8   , KC_P9   , KC_PMNS , KC_NO   ,
        KC_TRNS , KC_PGDN , KC_LEFT , KC_DOWN , KC_RIGHT, KC_NO   , KC_TRNS ,       KC_TRNS , KC_PSLS , KC_P4   , KC_P5   , KC_P6   , KC_PPLS , KC_NO   ,
        KC_TRNS , KC_NO   , KC_NO   , KC_NO   , KC_NO   , KC_NO   ,                           KC_PAST , KC_P1   , KC_P2   , KC_P3   , KC_PEQL , KC_NO   ,
        KC_TRNS , KC_NO   , KC_NO   , KC_NO   ,                                                                   KC_P0   , KC_PDOT , KC_PCMM , KC_NO   ,
                                                        KC_TRNS , KC_TRNS ,           KC_TRNS , KC_PENT ,
                                                          KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS ,
                                                          KC_TRNS , QK_BOOT ,       KC_TRNS , KC_TRNS
    ),
    [_SYMBOLS] = LAYOUT(
        KC_NO   , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,       KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , KC_NO   ,
        KC_TRNS , KC_QUOT , KC_LT   , KC_GT   , KC_DQT  , KC_DOT  , KC_NO   ,       KC_NO   , KC_AMPR , AD_SCOPE, KC_LBRC , KC_RBRC , KC_PERC , KC_NO   ,
        KC_TRNS , KC_EXLM , KC_MINS , KC_PLUS , KC_EQL  , KC_HASH , KC_NO   ,       KC_NO   , KC_PIPE , KC_COLN , KC_LPRN , KC_RPRN , KC_QUES , KC_NO   ,
        KC_TRNS , KC_CIRC , KC_SLSH , KC_ASTR , KC_BSLS , AD_DDS  ,                           KC_TILD , KC_DLR  , KC_LCBR , KC_RCBR , KC_AT   , KC_NO   ,
        KC_TRNS , KC_NO   , KC_NO   , KC_NO   ,                                                                   KC_NO   , KC_NO   , KC_NO   , KC_NO   ,
                                                        KC_TRNS , KC_TRNS ,           KC_TRNS , KC_PENT ,
                                                          KC_TRNS , KC_TRNS ,       KC_TRNS , KC_TRNS ,
                                                          KC_TRNS , KC_TRNS ,       QK_BOOT , KC_TRNS
    )
};
