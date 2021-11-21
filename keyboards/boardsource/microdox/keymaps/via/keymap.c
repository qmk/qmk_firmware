/*
Copyright 2020 Jack Sangdahl <@toastedmangoes>

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_split_3x5_3(
  KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  SFT_T(KC_A),  KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    SFT_T(KC_SCLN),
  CTL_T(KC_Z),  KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  CTL_T(KC_SLSH),
                LT(3, KC_LGUI),   MO(1),   KC_SPC,       KC_BSPC, MO(2),   KC_ENT
),

[1] = LAYOUT_split_3x5_3(
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
  KC_ESC,  KC_TAB,  KC_CAPS, KC_TILD, KC_GRV,       KC_QUOT, KC_DQUO, KC_MPRV, KC_MPLY, KC_MNXT,
                    KC_LGUI, KC_TRNS, KC_SPC,       KC_ENT,  KC_TRNS, KC_RALT
),

[2] = LAYOUT_split_3x5_3(
  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,      KC_PSCR, KC_DEL,  KC_INS,   KC_HOME, KC_END,
  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,      KC_LEFT, KC_DOWN, KC_RIGHT, KC_UP,   KC_VOLU,
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_VOLD,
                    KC_PGDN, KC_TRNS, KC_SPC,       KC_ENT,  KC_TRNS, KC_PGUP
),
[3] = LAYOUT_split_3x5_3(
  RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      RGB_TOG,  RGB_HUD, RGB_HUI, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      RGB_MOD,  RGB_SAD, RGB_SAI, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      RGB_RMOD, RGB_VAD, RGB_VAI, XXXXXXX, XXXXXXX,
                    KC_TRNS, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX
)
};

#ifdef OLED_ENABLE
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
    case 0:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("^\n"), false);
      oled_write_P(PSTR("Layer: Base\n"), false);
      break;
    case 1:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("  ^\n"), false);
      oled_write_P(PSTR("Layer: Raise\n"), false);
      break;
    case 2:
      oled_write_P(PSTR("B R L A O\n"), false);
      oled_write_P(PSTR("    ^\n"), false);
      oled_write_P(PSTR("Layer: Lower\n"), false);
      break;
    case 3:
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
