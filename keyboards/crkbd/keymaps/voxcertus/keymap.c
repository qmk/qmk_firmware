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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
      KC_NO, KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,            KC_J,   KC_L,         KC_U,         KC_Y,         KC_BSPC,      KC_NO,
      KC_NO, LGUI_T(KC_A), LALT_T(KC_R), LSFT_T(KC_S), LCTL_T(KC_T), KC_G,            KC_M,   RCTL_T(KC_N), RSFT_T(KC_E), LALT_T(KC_I), RGUI_T(KC_O), KC_NO,
      KC_NO, KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,            KC_K,   KC_H,         KC_COMM,      KC_DOT,       KC_SLSH,      KC_NO,
                                         KC_TAB,       MO(1),        KC_ENT,          KC_SPC, MO(2),        KC_ESC
  ),
  [1] = LAYOUT_split_3x6_3(
      KC_NO, KC_INS, KC_PGUP,  KC_UP,   KC_HOME, KC_VOLU,           KC_7,  KC_8,    KC_9,   KC_ASTR, KC_SLSH, KC_NO,
      KC_NO, KC_DEL, KC_LEFT,  KC_DOWN, KC_RGHT, KC_VOLD,           KC_4,  KC_5,    KC_6,   KC_PLUS, KC_MINS, KC_NO,
      KC_NO, KC_NO,  KC_PGDN,  KC_PSCR, KC_END,  KC_MUTE,           KC_1,  KC_2,    KC_3,   KC_NO,   KC_NO,   KC_NO,
                               KC_TRNS, KC_TRNS, KC_TRNS,           MO(3), KC_0,    KC_DOT
  ),
  [2] = LAYOUT_split_3x6_3(
      KC_NO, KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,            KC_MINS, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_NO,
      KC_NO, KC_COLN, KC_SCLN, KC_AMPR, KC_ASTR, KC_UNDS,           KC_PLUS, KC_QUOT, KC_DQUO, KC_BSLS, KC_PIPE, KC_NO,
      KC_NO, KC_NO,   KC_NO,   KC_CIRC, KC_PERC, KC_NO,             KC_EQL,  KC_LBRC, KC_RBRC, KC_NO,   KC_NO,   KC_NO,
                               KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
  ),
  [3] = LAYOUT_split_3x6_3(
      KC_NO, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_VOLU,           KC_BRIU, KC_CUT,  KC_COPY, KC_PSTE, KC_NO,  KC_NO,
      KC_NO, KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_VOLD,           KC_BRID, KC_CALC, KC_NO,   KC_NO,   KC_NO,  KC_NO,
      KC_NO, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MUTE,           KC_NO,   KC_NO,   KC_NO,   QK_BOOT, EE_CLR, KC_NO,
                               KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS
  )
};

#ifdef OLED_ENABLE
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
            oled_write_ln_P(PSTR("Colmak-DH"), false);
            break;
        case L_LOWER:
            oled_write_ln_P(PSTR("Nav || Num"), false);
            break;
        case L_RAISE:
            oled_write_ln_P(PSTR("Special Area"), false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            oled_write_ln_P(PSTR("Effin Keys"), false);
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
//static void render_logo(void) {
//    static const unsigned char PROGMEM raw_logo[] = {
//        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,252,  4,244, 20,212, 84, 84, 84, 20,244,  4,252,  4,244, 20,212, 84, 84, 84, 84, 84, 84,212, 20,244,  4,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,  2,250, 10,234, 42,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170, 42,234, 10,250,  2,254,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,255,  0,127, 64, 95, 65,125,  5,244, 23,208, 95,208, 23,244,  5,125, 65, 95, 80, 87, 80, 95, 64,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,191,160,175,160,191,128,255,128,190,162,170,170,170,170,170,170,170,170, 42,234, 10,250,  2,254,  0,255,  0,255,  0,255,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
//        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  4,245, 21,213, 21,117, 69, 29,241,  7,252,  1,253,  5,244, 23,209, 93, 69,117,  5,253,  1,255,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,254,  2,250,  2,254,  0,255,128,190,162,170,170,170,170,170,170,170,171,168,175,160,191,128,255,  0,255,  0,255,  0,255,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
//        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31, 16, 23, 20, 21, 21, 21, 21, 21, 21, 20, 23, 16, 31,  0, 31, 16, 23, 20, 21, 21, 21, 21, 20, 23, 16, 31,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,128,191,160,175,168,171,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,170,171,168,175,160,191,128,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
//    };
//    oled_write_raw_P(raw_logo, sizeof(raw_logo));
//}

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
