/*
Copyright 2020 Cole Smith <cole@boadsource.xyz>

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
#include "split_util.h"

enum layers {
    _QWERTY,
    _RAISE,
    _LOWER,
    _ADJUST
};

#define KC_CTSC RCTL_T(KC_SCLN)
#define LOWER_SPC LT(_LOWER, KC_SPC)
#define RASE_BACK LT(_RAISE, KC_BSPC)
#define SHFT_Z MT(MOD_LSFT, KC_Z)
#define SHIFT_SLASH MT(MOD_RSFT,KC_SLSH)
#define RASE_ENT LT(_RAISE, KC_ENT)
#define CTRL_A MT(MOD_LCTL,KC_A)
#define PREVWINDOW MT(MOD_LCTL, KC_LEFT)
#define NEXTWINDOW MT(MOD_LCTL, KC_RGHT)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3( 
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  
      CTRL_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,    KC_J,    KC_K,    KC_L, KC_CTSC, 
     SHFT_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_N,    KC_M, KC_COMM,  KC_DOT, SHIFT_SLASH, 
                       MO(_LOWER),KC_LGUI, RASE_ENT,       RASE_BACK, LOWER_SPC, KC_TAB
    ),
  [_RAISE] = LAYOUT_split_3x5_3( 
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0, 
      KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,            KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_QUOT, 
     KC_LSFT, KC_GRV, PREVWINDOW, NEXTWINDOW, XXXXXXX,           KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, 
                         _______, KC_LGUI, KC_ENT,           KC_BSPC,  KC_SPC, _______
                         ),
  [_LOWER] = LAYOUT_split_3x5_3( 
       KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,             KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
       KC_ESC,   XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,            KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_DQT, 
       KC_ESC,   KC_TILD, PREVWINDOW, NEXTWINDOW, RGB_MODE_FORWARD,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, 
                            _______,  KC_LGUI,  KC_ENT,         KC_BSPC,  KC_SPC, _______
                            )
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_180;
  return rotation;
}

static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0
  };
  oled_write_P(qmk_logo, false);
}                                                                                 

static void render_status(void) {
   switch (get_highest_layer(layer_state)) {
    case _QWERTY:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("^\n"), false);
      oled_write_P(PSTR("Layer: Base\n"), false);
      break;
    case _RAISE:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("  ^\n"), false);
      oled_write_P(PSTR("Layer: Raise\n"), false);
      break;
    case _LOWER:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("    ^\n"), false);
      oled_write_P(PSTR("Layer: Lower\n"), false);
      break;
    case _ADJUST:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("      ^\n"), false);
      oled_write_P(PSTR("Layer: Adjust\n"), false);
      break;
    default:
      oled_write_P(PSTR("B R L A O"), false);
      oled_write_P(PSTR("        ^\n"), false);
      oled_write_P(PSTR("Layer: Other\n"), false);
  }
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    oled_scroll_left();
  }
}

#endif
