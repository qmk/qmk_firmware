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

  //  /------------------------------------------                     /------------------------------------------ 
  //  |      |   Q  |   W  |   E  |   R  |   T   |                    |   Y  |   U  |   I  |   O  |   P   |  ~`  |
  //  |------+------+------+------+------+-------+                    +------+------+------+------+-------+------|
  //  |      |   A  |   S  |   D  |   F  |   G   |                    |   H  |   J  |   K  |   L  |   ;:  |  '"  |
  //  |------+------+------+------+------+-------+                    +------+------+------+------+-------+------|
  //  |      |   Z  |   X  |   C  |   V  |   B   |                    |   N  |   M  |  ,<  |  .>  |  /?   |      |
  //  \------+------+------|------+------+-------+-------\   /--------+------+------+------+------+-------+------/
  //                              | Ctrl |  OS   |  Alt  |   |        | Spc  |      |
  //                              \------+-------+-------/   \--------+------+------/

  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,KC_LSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTRL, KC_LGUI, KC_LALT,  MO(1),  KC_SPC, KC_RSFT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_PGUP,    KC_HOME,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX ,KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PGDN, KC_END, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT,   MO(3), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

const uint16_t PROGMEM combo_esc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_O, KC_P, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  COMBO(combo_esc, KC_ESC),
  COMBO(combo_tab, KC_TAB),
  COMBO(combo_bspc, KC_BSPC),
  COMBO(combo_ent, KC_ENT),
  COMBO(combo_del, KC_DEL),
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  // if (is_keyboard_master()) {
    return OLED_ROTATION_180;
  // }

  // return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
  oled_write_P(PSTR("| layer : "), false);
  switch (layer_state) {
    case L_BASE:
      oled_write_ln_P(PSTR("Dflt. |"), false);
      break;
    case L_LOWER:
      oled_write_ln_P(PSTR("Lowr. |"), false);
      break;
    case L_RAISE:
      oled_write_ln_P(PSTR("Rais. |"), false);
      break;
    case L_ADJUST:
    case L_ADJUST|L_LOWER:
    case L_ADJUST|L_RAISE:
    case L_ADJUST|L_LOWER|L_RAISE:
      oled_write_ln_P(PSTR("Adjs. |"), false);
      break;
  }
}

int type_count = 0;
int oled_dimm_value = 0;

static uint16_t scroll_resume_timer;

char keylog_str[24] = "|       :       |";

const char code_to_name[60] = {
  ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
  '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '
};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX)
    || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)
  ) {
      keycode = keycode & 0xFF;
  }

  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  if (keycode > 99) {
    keycode = 99;
    name = '?';
  }

  int16_t row = record->event.key.row;
  int16_t col = record->event.key.col;

  if (9 < row) {
    row = 0;
  }

  if (9 < col) {
    col = 0;
  }

  snprintf(
    keylog_str,
    sizeof(keylog_str),
    "| %dx%d   : k %3d |  %c",
    row, 
    col,
    keycode, 
    name
  );
}

void oled_render_keylog(void) {
  oled_write_ln(keylog_str, false);
}

void oled_render_count(void) {
  char str[128];
  
  sprintf(str, "| count : %5d |\n|_______________|", type_count);
  oled_write_ln(str, false);
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

void oled_render_symmetry(uint8_t x, uint8_t y) {
  if (x >= 128) {
    x = x - 128;
  }

  oled_write_pixel(x, y, true);
  oled_write_pixel(x, 32 - y, true);
}

void oled_render_band(uint8_t x, uint8_t y, uint8_t width) {
  for (size_t i = 0; i < width; i++)
  {
    oled_render_symmetry(x + i + y, y);
  }
}

void oled_render_logo(void) {
  for (size_t x = 0; x < 128; x = x + 64)
  {
    for (size_t y = 16; y < 32; y = y + 1)
    {
      oled_render_band(x, y, 34);
    }
  }
}

void oled_dimm(void) {
  oled_dimm_value = oled_dimm_value + 1;

  if (0 > (255 - oled_dimm_value)) {
    oled_set_brightness(0);
    return;
  }

  oled_set_brightness(255 - oled_dimm_value);
}

void oled_resume_scroll(void) {
  if (oled_dimm_value >= 255 || timer_elapsed(scroll_resume_timer) < 10000) {
    return;
  }


  oled_scroll_left();
  // oled_dimm();
}

void oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_render_layer_state();
    oled_render_keylog();
    oled_render_count();
    oled_resume_scroll();

    return;
  }

  oled_render_logo();
  oled_scroll_left();
  oled_set_brightness(255);
  oled_scroll_set_speed(4);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  scroll_resume_timer = timer_read();
  oled_dimm_value = 0;
  oled_set_brightness(255);

  if (record->event.pressed) {
    oled_scroll_off();
    set_keylog(keycode, record);
  }

  type_count++;

  return true;
}