// Copyright 2021 Bartosz Nowak (@dumam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_layers {
    _QWERTY,   // daily use and coding
    _MOVE,     // mouse, arrows, browsing useful keys
    _CONF,     // machine settings, keyboard settings, backlight
};
#define _KC_SPC LT(_CONF, KC_SPC)
#define _KC_ENT LT(_MOVE, KC_ENT)

#define KC_SPEC SC_SENT // Right Shift when held, Enter when tapped
#define KC_INS_ KC_INS
#define KC_TAB_ KC_TAB
#define RESET__ QK_BOOT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_6x6_5_thumb(

    KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,                          KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,
    KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,                          KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,
    KC_BSLS,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,                          KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_EQL ,
    KC_SLSH,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,                          KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_LBRC,KC_RBRC,
    KC_LSFT,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,                          KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SCLN,KC_QUOT,
                    KC_LGUI,KC_ESC ,                                                          KC_HOME,KC_END ,
                                    _KC_SPC,                                          _KC_ENT,
                                            KC_TAB_,KC_BSPC,          KC_DEL ,KC_RSFT,
                                            KC_LCTL,KC_LALT,          KC_RALT,KC_RCTL
  ),

  [_CONF] = LAYOUT_6x6_5_thumb(

    RESET__,XXXXXXX,XXXXXXX,XXXXXXX,KC_SLEP,KC_WAKE,                          XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,RESET__,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                          XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                          XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_PGUP,XXXXXXX,                          XXXXXXX,KC_PGUP,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,KC_CAPS,KC_MENU,XXXXXXX,KC_PGDN,KC_LGUI,                          KC_LGUI,KC_PGDN,XXXXXXX,KC_INS_,KC_PSCR,XXXXXXX,
                    _______,_______,                                                          _______,_______,
                                    _______,                                          _______,
                                            _______,_______,          _______,_______,
                                            _______,_______,          _______,_______
  ),

  [_MOVE] = LAYOUT_6x6_5_thumb(

    RESET__,XXXXXXX,XXXXXXX,KC_MPRV,KC_MPLY,KC_MPLY,                          KC_MUTE,KC_VOLD,KC_VOLU,XXXXXXX,XXXXXXX,RESET__,
    XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                          XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,XXXXXXX,KC_MS_U,XXXXXXX,XXXXXXX,                          XXXXXXX,XXXXXXX,KC_UP  ,XXXXXXX,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,KC_MS_L,KC_MS_D,KC_MS_R,XXXXXXX,                          XXXXXXX,KC_LEFT,KC_DOWN,KC_RGHT,XXXXXXX,XXXXXXX,
    XXXXXXX,XXXXXXX,KC_BTN1,KC_BTN3,KC_BTN2,XXXXXXX,                          XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
                    _______,_______,                                                          _______,_______,
                                    _______,                                          _______,
                                            _______,_______,          _______,_______,
                                            _______,_______,          _______,_______
  ),
};
