/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include "users/toinux/keymap_qwerty_fr.h"

#define CTRLSC LCTL_T(KC_ESC)
#define MOSCLN LT(_MOUSE,KC_SCLN)
#define ACCENTS LT(_ACCENTS,KC_RALT)
#define FUN LT(_FUN,KC_SPC)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SPCNAV LT(_NAV,KC_SPC)
#define SFTENT MT(MOD_RSFT,KC_ENT)
#define TABLGUI LGUI_T(KC_TAB)

#define SC_F1 LSFT(LCTL(KC_F1))
#define SC_F2 LSFT(LCTL(KC_F2))
#define SC_F3 LSFT(LCTL(KC_F3))
#define SC_F4 LSFT(LCTL(KC_F4))

enum crkbd_layers {
  _BASE,
  _GAMING,
  _ACCENTS,
  _LOWER,
  _RAISE,
  _FUN,
  _NAV,
  _MOUSE,
  _ADJUST
};
// TODO : gérer ctrl + shift + escape
// faire un LT avec TAB ?
// remplacer spacefn avec nav sur ; à la place de la souris ?
// => ins et del seraient inaccessible, utiliser des combos à la place ?

// TEMPLATE
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  |        |        |        |
//                                      `--------------------------'  `--------------------------'


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Base
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |Tab/LGui|   Q    |   W    |   E    |   R    |   T    |                    |   Y    |   U    |   I    |   O    |   P    | Bksp   |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  | CtrlSc |   A    |   S    |   D    |   F    |   G    |                    |   H    |   J    |   K    |   L    | ;/Mous |   '    |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  | Shift  |   Z    |   X    |   C    |   V    |   B    |                    |   N    |   M    |   ,    |   .    |   /    | SftEnT |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |  LALT  | LOWER  |Spc/FUN |  | Spc/NAV| RAISE  |ACCENTS |
//                                      `--------------------------'  `--------------------------'
  [_BASE] = LAYOUT_split_3x6_3(
      TABLGUI,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
       CTRLSC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,  MOSCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  SFTENT,
                                          KC_LALT,   LOWER,     FUN,     SPCNAV,   RAISE, ACCENTS

  ),

// TEMPLATE
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  |        |        |        |
//                                      `--------------------------'  `--------------------------'
  [_GAMING] = LAYOUT_split_3x6_3(
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
       CTRLSC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,  MOSCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  SFTENT,
                                          KC_LALT,   LOWER,     FUN,     SPCNAV,   RAISE, ACCENTS

  ),

// Accents, see http://marin.jb.free.fr/qwerty-fr/
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |        |   â    |   é    |   è    |   ê    |   €    |                    |   û    |   ù    |   î    |   ô    |   œ    |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |   à    |   æ    |   ë    |        |   «    |                    |   »    |   ü    |   ï    |   ö    |   °    |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |   à    |        |   ç    |        |        |                    |        |        |        |        |        |        |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  |        |        |        |
//                                      `--------------------------'  `--------------------------'
  [_ACCENTS] = LAYOUT_split_3x6_3(
      _______, QF_ACIR, QF_EACU, QF_EGRV, QF_ECIR, QF_EURO,                      QF_UCIR, QF_UGRV, QF_ICIR, QF_OCIR,   QF_OE, _______,
      _______, QF_AGRV,   QF_AE, QF_EDIA, _______, QF_LDAQ,                      QF_RDAQ, QF_UDIA, QF_IDIA, QF_ODIA,  QF_DEG, _______,
      _______, QF_AGRV, _______, QF_CCED, _______, _______,                      _______, _______, _______, _______, _______, _______,
                                          _______, _______, _______,    _______, _______, _______

  ),

// Lower
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |   ~    |   !    |   @    |   #    |   $    |   %    |                    |   ^    |   &    |   *    |   (    |   )    |  Del   |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |   _    |   +    |   {    |   }    |   |    |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  |        |        |        |
//                                      `--------------------------'  `--------------------------'
  [_LOWER] = LAYOUT_split_3x6_3(
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
      _______, _______, _______, _______, _______, _______,                      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
                                          _______, _______, _______,   _______,  _______, _______

  ),

// Raise
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |   `    |   1    |   2    |   3    |   4    |   5    |                    |   6    |   7    |   8    |   9    |   0    |  Del   |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |   -    |   =    |   [    |   ]    |   \    |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |        |        |        |        |        |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  |        |        |        |
//                                      `--------------------------'  `--------------------------'
  [_RAISE] = LAYOUT_split_3x6_3(
       KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
      _______, _______, _______, _______, _______, _______,                      _______, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
      _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
                                          _______, _______, _______,   _______,  _______, _______

  ),

// Functions and keypad
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |        | SC_F1  | SC_F2  | SC_F3  | SC_F4  |        |                    |        |   7    |   8    |   9    |        |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |  Vol-  |  Vol+  |  Mute  |                    |        |   4    |   5    |   6    |   -    |   /    |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        |        |        |        |        |                    |        |   1    |   2    |   3    |   +    |   *    |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  |   =    |   0    |   .    |
//                                      `--------------------------'  `--------------------------'
  [_FUN] = LAYOUT_split_3x6_3(
      _______,   SC_F1,   SC_F2,   SC_F3,   SC_F4, _______,                      _______,   KC_P7,   KC_P8,   KC_P9, _______, _______,
      _______, _______, _______, KC_VOLD, KC_VOLU, KC_MUTE,                      _______,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_PSLS,
      _______, _______, _______, _______, _______, _______,                      _______,   KC_P1,   KC_P2,   KC_P3, KC_PPLS, KC_PAST,
                                          _______, _______, _______,   KC_PENT,    KC_P0, KC_PDOT

  ),

//  Navigation and function keys
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |        |   F1   |   F2   |   F2   |   F4   |        |                    |        | Pg Up  |   Up   | Pg Dn  |  Ins   |  Del   |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |   F5   |   F6   |   F7   |   F8   |        |                    |  Home  |  Left  |  Down  |  Right |        |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |   F9   |   F10  |   F11  |   F12  |        |                    |  Space |  End   |        |        |        |        |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  |        |        |        |
//                                      `--------------------------'  `--------------------------'
  [_NAV] = LAYOUT_split_3x6_3(
      _______,   KC_F1,    KC_F2,  KC_F3,   KC_F4, XXXXXXX,                      XXXXXXX, KC_PGUP,   KC_UP, KC_PGDN, KC_INS,   KC_DEL,
      _______,   KC_F5,    KC_F6,  KC_F7,   KC_F8, XXXXXXX,                      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
      _______,   KC_F9,   KC_F10, KC_F11,  KC_F12, XXXXXXX,                       KC_SPC,  KC_END, XXXXXXX, XXXXXXX, XXXXXXX, _______,
                                        _______,   _______, _______,    _______, _______, _______

  ),

// Mouse
//  ,-----------------------------------------------------.                    ,-----------------------------------------------------.
//  |        |        | Wh up  | Ms up  | Wh dn  |        |                    |        |        |        |        |        |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        | Ms lft | Ms dn  | Ms rgt |        |                    |        |  btn1  |  btn3  |  btn2  |        |        |
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//  |        |        | Wh lft |        | Wh rgt |        |                    |        |        |        |        |        |        |
//  `--------+--------+--------+--------+--------+--------+--------.  .--------+--------+--------+--------+--------+--------+--------'
//                                      |        |        |        |  |        |        |        |
//                                      `--------------------------'  `--------------------------'
  [_MOUSE] = LAYOUT_split_3x6_3(
      _______, _______, KC_WH_U, KC_MS_U, KC_WH_D, _______,                      _______, _______, _______, _______, _______, _______,
      _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______,                      _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______,
      _______, _______, KC_WH_L, _______, KC_WH_R, _______,                      _______, _______, _______, _______, _______, _______,
                                          _______, _______, _______,    _______, _______, _______

  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                          _______, _______, _______,    _______, _______, _______
  )
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
    case _BASE:
        oled_write_ln_P(PSTR("Default"), false);
        break;
    case _GAMING:
       oled_write_ln_P(PSTR("Gaming"), false);
        break;
    case _ACCENTS:
       oled_write_ln_P(PSTR("Accents"), false);
        break;
    case _LOWER:
       oled_write_ln_P(PSTR("Lower"), false);
        break;
    case _RAISE:
       oled_write_ln_P(PSTR("Raise"), false);
        break;
    case _FUN:
       oled_write_ln_P(PSTR("Fun"), false);
        break;
    case _NAV:
       oled_write_ln_P(PSTR("Nav"), false);
        break;
    case _MOUSE:
       oled_write_ln_P(PSTR("Mouse"), false);
        break;
    case _ADJUST:
       oled_write_ln_P(PSTR("Adjust"), false);
        break;
    default: //  for any other layers, or the default layer
        oled_write_ln_P(PSTR("???"), false);
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

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_ENABLE
