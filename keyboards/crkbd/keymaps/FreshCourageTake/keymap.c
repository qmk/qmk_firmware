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

#define _QWERTY 0
#define _ARROWS 1
#define _SYMBOLS 2
#define _FUNPAD 3
#define _NUMPAD 4
#define _META 5
#define _MACRO 6

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                         ,-----------------------------------------------------.
       KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                                               KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_MINUS,
  //|--------+--------+--------+--------+--------+--------|                                                         |--------+--------+--------+--------+--------+--------|
      KC_TAB,  LT(_MACRO, KC_A), KC_S, KC_D, LT(_NUMPAD, KC_F), KC_G,                                                   KC_H,    LT(_MACRO, KC_J), KC_K, KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                                                         |--------+--------+--------+--------+--------+--------|
      KC_CAPSLOCK, KC_Z, KC_X,  LGUI_T(KC_C), LT(_FUNPAD, KC_V), KC_B,                                                  KC_N,   LT(_META, KC_M), RGUI_T(KC_COMM),  KC_DOT, KC_SLSH,  KC_BSLS,
  //|--------+--------+--------+--------+--------+--------+--------|                                                |--------+--------+--------+--------+--------+--------+--------|
                                LCTL_T(KC_DEL), OSM(MOD_LSFT), LT(_ARROWS, KC_ENT),                    LT(_SYMBOLS, KC_SPC), RCTL_T(KC_BSPC), OSM(MOD_RSFT)
                                      //`--------------------------'                                                `--------------------------'

  ),

  [_ARROWS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                                                            _______, KC_HOME, KC_UP, KC_END, KC_LCBR, KC_LABK,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_LCTL,    KC_LSFT,   KC_LALT,   KC_LGUI, _______,                                                     _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_RCBR, KC_RABK,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                                          _______, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_LBRACKET, KC_RBRACKET, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      KC_TILDE, KC_GRAVE,    KC_PERCENT,  KC_PIPE,   KC_AMPR, KC_EQUAL,                                                  _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_EXCLAIM,    KC_AT,  KC_HASH,   KC_DOLLAR, KC_RABK,                                                    _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, KC_CIRC,    KC_ASTR,  KC_UNDERSCORE,   KC_PLUS, KC_MINUS,                                                _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_FUNPAD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, _______,  _______, _______, _______, _______,                                                            _______, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,                                                            _______, KC_F4, KC_F5, KC_F6, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      RGB_RMOD, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,                                                             _______, KC_F1, KC_F2, KC_F3, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_NUMPAD] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      RESET, _______, _______, _______, _______, _______,                                                            _______, KC_7, KC_8, KC_9, SGUI(KC_S), _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                                            _______, KC_4, KC_5, KC_6, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                                                            _______, KC_1, KC_2, KC_3, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          KC_MINUS, KC_KP_0, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_META] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, KC_BRIU,                                                             _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_BRID,                                                             _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, KC_VOLD, KC_VOLU, _______,                                                             _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),

  [_MACRO] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                                                          ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                                                            _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, DM_REC1, DM_RSTP, DM_PLY1, _______,                                                            _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______,
  //|--------+--------+--------+--------+--------+--------|                                                          |--------+--------+--------+--------+--------+--------|
      _______, _______, DM_REC2, DM_RSTP, DM_PLY2, _______,                                                           RGB_RMOD, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______,
  //|--------+--------+--------+--------+--------+--------+--------|                                        |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,                                          _______, _______, _______
                                      //`--------------------------'                                        `--------------------------'
  ),
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Do work, son"), false);
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
    if (is_master) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    // set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
      switch (keycode) {
         case LT(_NUMPAD, KC_F):
         case LT(_MACRO, KC_J):
         case LGUI_T(KC_C):
         case LT(_FUNPAD, KC_V):
         case LT(_META, KC_M):
         case RGUI_T(KC_COMM):
         case LCTL_T(KC_DEL):
         case LT(_ARROWS, KC_ENT):
         case LT(_SYMBOLS, KC_SPC):
         case RCTL_T(KC_BSPC):
            return true;
         default:
            return false;
      }
}