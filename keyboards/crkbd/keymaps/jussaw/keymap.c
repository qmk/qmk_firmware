/*
Copyright 2019 @foostan
Copyrig2ht 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

enum layers {
    _QWERTY,
    _COLEMAKDH,
    _LOWER,
    _UPPER,
    _ADJUST,
    _GAME,
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    COLEMAKDH,
    LOWER,
    UPPER,
    ADJUST,
    GAME,
};

#define LOWER MO(_LOWER)
#define UPPER MO(_UPPER)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------------------.                    ,-----------------------------------------------------.
   * |  Tab   |    Q   |    W   |    E   |    R   |    T   |                    |    Y   |    U   |    I   |    O   |    P   |  Bksp  |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |  Esc   |    A   |    S   |    D   |    F   |    G   |                    |    H   |    J   |    K   |    L   |    ;   |   ""   |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |  Alt   |    Z   |    X   |    C   |    V   |    B   |                    |    N   |    M   |    ,   |    .   |    /   | Enter  |
   * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
   *                                     |  Ctrl  | Lower  | Space  |  | Shift  | Upper  |  GUI   |
   *                                     `--------------------------'  `--------------------------'
   */
  [_QWERTY] = LAYOUT_split_3x6_3(
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
       KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
      KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
                                          KC_LCTL,   LOWER,  KC_SPC,    KC_RSFT,   UPPER,  KC_RGUI
  ),

  /* Colemak Mod-DH
   * ,-----------------------------------------------------.                    ,-----------------------------------------------------.
   * |  Tab   |    Q   |    W   |    F   |    P   |    B   |                    |    J   |    L   |    U   |    Y   |    ;   |  Bksp  |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |  Esc   |    A   |    R   |    S   |    T   |    G   |                    |    M   |    N   |    E   |    I   |    O   |   ""   |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |  Alt   |    Z   |    X   |    C   |    D   |    V   |                    |    K   |    H   |    ,   |    .   |    /   | Enter  |
   * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
   *                                     |  Ctrl  | Lower  | Space  |  | Shift  | Upper  |  GUI   |
   */
  [_COLEMAKDH] = LAYOUT_split_3x6_3(
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
       KC_ESC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
      KC_LALT,    KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
                                          KC_LCTL,   LOWER,  KC_SPC,    KC_RSFT,   UPPER, KC_RGUI
  ),

  /* Lower
   * ,-----------------------------------------------------.                    ,-----------------------------------------------------.
   * |  Tab   |    !   |    @   |    #   |    $   |    %   |                    |    ^   |    &   |    *   |    (   |    )   |  Bksp  |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |   F11  |   F1   |   F2   |   F3   |   F4   |   F5   |                    |    `   |    -   |    =   |    [   |    ]   |   \    |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |   F12  |   F6   |   F7   |   F8   |   F9   |  F10   |                    |    ~   |    _   |    +   |    {   |    }   |   |    |
   * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
   *                                     |  Ctrl  | Trans  | Space  |  | Shift  | Adjust |  Alt   |
   *                                     `--------------------------'  `--------------------------'
   */
  [_LOWER] = LAYOUT_split_3x6_3(
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
       KC_F11,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_GRV, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
       KC_F12,   KC_F5,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_TILD, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
                                          KC_LCTL, KC_TRNS,  KC_SPC,    KC_RSFT,  ADJUST, KC_RALT
  ),


  /* Upper
   * ,-----------------------------------------------------.                    ,-----------------------------------------------------.
   * |  Tab   |    1   |    2   |    3   |    4   |    5   |                    |    6   |    7   |    8   |    9   |    0   |  Bksp  |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |  Del   |        |        |        |        |        |                    |        |  Left  |  Down  |   Up   | Right  |   ""   |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |  Alt   |        |        |        |        |        |                    |        |  Home  |Pg Down | Pg Up  |  End   | Enter  |
   * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
   *                                     |  Ctrl  | Adjust | Space  |  | Shift  | Trans  |  GUI   |
   *                                     `--------------------------'  `--------------------------'
   */
  [_UPPER] = LAYOUT_split_3x6_3(
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
       KC_DEL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_QUOT,
      KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_ENT,
                                          KC_LCTL,  ADJUST,  KC_SPC,    KC_RSFT, KC_TRNS, KC_RGUI
  ),


  /* Adjust
   * ,-----------------------------------------------------.                    ,-----------------------------------------------------.
   * |  Reset |DF(QWRT)|DF(CMDH)|        |        |TG(GAME)|                    |  Play  | Mouse1 | Mouse2 | Mouse4 | Mouse5 |Ms Acc1 |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |  RGB   |  Hue+  |  Sat+  |Bright+ |Effect- |AG_SWAP |                    |  Vol+  |Ms Left |Ms Down | Ms Up  |Ms Right|Ms Acc2 |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |RGB Mode|  Hue-  |  Sat-  |Bright- |Effect+ |AG_NORM |                    |  Vol-  | MsWl L | MsWl D | MsWl U | MsWl R |Ms Acc3 |
   * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
   *                                     |  Ctrl  | Lower  | Space  |  | Shift  | Upper  |  GUI   |
   *                                     `--------------------------'  `--------------------------'
   */
  [_ADJUST] = LAYOUT_split_3x6_3(
        RESET,DF(_QWERTY),DF(_COLEMAKDH),XXXXXXX, XXXXXXX,TG(_GAME),             KC_MPLY, KC_BTN1, KC_BTN2, KC_BTN4, KC_BTN5, KC_ACL0,
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, AG_SWAP,                      KC_VOLU, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ACL1,
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, AG_NORM,                      KC_VOLD, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_ACL2,
                                          XXXXXXX, KC_TRNS, XXXXXXX,    XXXXXXX, KC_TRNS, XXXXXXX
  ),


  /* Game
   * ,-----------------------------------------------------.                    ,-----------------------------------------------------.
   * |  Bksp  |  Tab   |    Q   |    W   |    E   |    R   |                    |    T   |    Y   |    U   |    I   |    O   |    P   |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * |   ""   |  Shift |    A   |    S   |    D   |    F   |                    |    G   |    H   |    J   |    K   |    L   |    ;   |
   * |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   * | Enter  |  Ctrl  |    Z   |    X   |    C   |    V   |                    |    B   |    N   |    M   |    ,   |    .   |    /   |
   * |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
   *                                     |   Esc  |  Alt   | Space  |  |        |        | 
   */
  [_GAME] = LAYOUT_split_3x6_3(
      KC_BSPC,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                         KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_QUOT,  KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,                         KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
       KC_ENT,  KC_LCTL,   KC_Z,    KC_X,    KC_C,    KC_V,                         KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,
                                           KC_ESC, KC_LALT, KC_SPC,     XXXXXXX, XXXXXXX,    TG(_GAME)
  ),
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE
