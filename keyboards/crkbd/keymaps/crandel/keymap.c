/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2023 Vitalii Drevenchuk <@Crandel>

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

enum custom_keycodes {
  TRM_COPY = SAFE_RANGE,
  TRM_PSTE,
  QWRT_UA,
  CLM_EN,
  UML_SEQ,
};

enum layers {
  COLMAK_LAYER = 0,
  NUMBER_LAYER,
  CHARS_LAYER,
  MOUSE_LAYER,
  QWERTY_LAYER,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [COLMAK_LAYER] = LAYOUT_split_3x6_3(
  //,----------------------------------------------------------------------.    ,----------------------------------------------------------------------------.
       KC_TAB,    KC_Q, RALT_T(KC_W), LCTL_T(KC_F),    LSFT_T(KC_P), KC_B,         KC_J,     LSFT_T(KC_L), LCTL_T(KC_U), RALT_T(KC_Y),       KC_SCLN, KC_BSPC,
  //|--------+--------+-------------+-------------+----------------+-------|    |------+-----------------+-------------+-------------+--------------+--------|
      KC_LCTL,    KC_A,         KC_R,         KC_S,            KC_T, KC_G,         KC_M,             KC_N,         KC_E,         KC_I,          KC_O, KC_QUOT,
  //|--------+--------+-------------+-------------+----------------+-------|    |------+-----------------+-------------+-------------+--------------+--------|
      KC_LSFT,    KC_Z,         KC_X,         KC_C,            KC_D, KC_V,         KC_K,             KC_H,      KC_COMM,       KC_DOT, LSFT(KC_SLSH),  KC_ESC,
  //|--------+--------+-------------+-------------+----------------+-------|    |------+-----------------+-------------+-------------+--------------+--------|
                                           KC_LGUI,TO(NUMBER_LAYER), KC_SPC,     KC_ENT, TO(COLMAK_LAYER),      KC_RALT
                                           //`-----------------------------'    `--------------------------------------'

  ),

  [NUMBER_LAYER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------------------.   ,-----------------------------------------------------------------------------.
       KC_DELETE, KC_F5, LALT_T(KC_7), LCTL_T(KC_4),    LSFT_T(KC_2),  KC_F1,         KC_HOME,  LSFT_T(KC_PGDN), LCTL_T(KC_PGUP),    KC_END, UML_SEQ,  KC_BSPC,
  //|-----------+------+-------------+-------------+----------------+-------|   |------------+-----------------+----------------+----------+--------+---------|
         KC_CAPS, KC_F4,         KC_8,         KC_5,            KC_1,   KC_3,         KC_LEFT,          KC_DOWN,           KC_UP,  KC_RIGHT, KC_LCTL, KC_MINUS,
  //|-----------+------+-------------+-------------+----------------+-------|   |------------+-----------------+----------------+----------+--------+---------|
         KC_LSFT, KC_F3,         KC_9,         KC_6,            KC_0,  KC_F2,         KC_MINS,          KC_UNDS,         KC_ASTR,   KC_BSLS, KC_SLSH,   KC_ESC,
  //|-----------+------+-------------+-------------+----------------+-------|   |------------+-----------------+----------------+----------+--------+---------|
                                            KC_LGUI, TO(CHARS_LAYER), KC_SPC,          KC_ENT, TO(COLMAK_LAYER),         KC_RALT
                                            //`-----------------------------'   `-----------------------------------------------'
  ),

  [CHARS_LAYER] = LAYOUT_split_3x6_3(
  //,------------------------------------------------------------------------.    ,-------------------------------------------------------------------------------------------.
      KC_DELETE, XXXXXXX, LSFT(KC_7), LSFT(KC_4),      LSFT(KC_2),    KC_MUTE,            KC_MPRV,           KC_LSFT,           KC_LCTL,      KC_MNXT,       KC_EQUAL, KC_BSPC,
  //|----------+--------+-----------+-----------+----------------+-----------|    |--------------+------------------+------------------+-------------+---------------+--------|
        KC_LCTL, KC_VOLU, LSFT(KC_8), LSFT(KC_5),      LSFT(KC_1), LSFT(KC_3),            KC_LBRC,        LSFT(KC_9),        LSFT(KC_0),      KC_RBRC,   LSFT(KC_GRV),  KC_GRV,
  //|----------+--------+-----------+-----------+----------------+-----------|    |--------------+------------------+------------------+-------------+---------------+--------|
        KC_LSFT, KC_VOLD,    KC_BRID, LSFT(KC_6),         KC_BRIU,    KC_MSTP,     LSFT(KC_COMMA),     LSFT(KC_LBRC),     LSFT(KC_RBRC), LSFT(KC_DOT), LSFT(KC_EQUAL),  KC_ESC,
  //|----------+--------+-----------+-----------+----------------+-----------|    |--------------+------------------+------------------+-------------+---------------+--------|
                                         KC_LGUI, TO(MOUSE_LAYER),     KC_SPC,             KC_ENT,  TO(COLMAK_LAYER), KC_RALT
                                         //`---------------------------------'    `-----------------------------------------'
  ),

  [MOUSE_LAYER] = LAYOUT_split_3x6_3(
  //,-------------------------------------------------------.              ,---------------------------------------------------------.
      XXXXXXX,  XXXXXXX, KC_LALT,  KC_LCTL, KC_LSFT, XXXXXXX,                   KC_PSCR,          KC_WH_D, KC_WH_U,   KC_F6,   KC_F7,  KC_F8,
  //|--------+---------+--------+---------+--------+--------|              |-----------+-----------------+--------+--------+--------+-------|
      XXXXXXX,  XXXXXXX, KC_SLCT,  KC_BTN2, KC_BTN1, KC_BTN3,                   KC_MS_L,          KC_MS_D, KC_MS_U, KC_MS_R,   KC_F9, KC_F10,
  //|--------+---------+--------+---------+--------+--------|              |-----------+-----------------+--------+--------+----------------|
     TRM_COPY, TRM_PSTE,  KC_CUT,  KC_COPY,  KC_APP, KC_PSTE,                   KC_WBAK,          KC_PGDN, KC_PGUP, KC_WFWD,  KC_F11, KC_F12,
  //|--------+---------+--------+------------------+--------|              |-----------+-----------------+--------+--------+--------+-------|
                                   KC_LGUI, QWRT_UA,  KC_SPC,                    KC_ENT, TO(COLMAK_LAYER), KC_RALT
                                   //`----------------------'              `--------------------------------------'
  ),

  [QWERTY_LAYER] = LAYOUT_split_3x6_3(
  //,----------------------------------------------------------------.       ,-------------------------------------------------------------------------.
       KC_TAB, KC_Q, RALT_T(KC_W), LCTL_T(KC_E), LSFT_T(KC_R),   KC_T,          KC_Y, LSFT_T(KC_U), LCTL_T(KC_I), RALT_T(KC_O),        KC_P,    KC_BSPC,
  //|--------+-----+-------------+-------------+-------------+-------|       |------+-------------+-------------+-------------+------------+-----------|
      KC_CAPS, KC_A,         KC_S,         KC_D,         KC_F,   KC_G,          KC_H,         KC_J,         KC_K,         KC_L,     KC_SCLN,    KC_QUOT,
  //|--------+-----+-------------+-------------+-------------+-------|       |------+-------------+-------------+-------------+------------+-----------|
      KC_LSFT, KC_Z,         KC_X,         KC_C,         KC_V,   KC_B,          KC_N,         KC_M,      KC_COMM,       KC_DOT,     KC_LBRC,    KC_BSLS,
  //|--------+-----+-------------+-------------+-------------+-------|       |------+-------------+-------------+-------------+------------+-----------|
                                        KC_LGUI,       CLM_EN, KC_SPC,        KC_ENT,       CLM_EN,      KC_RALT
                                        //`--------------------------'       `----------------------------------'
  )
};


#ifdef OLED_ENABLE
#include <stdio.h>

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case COLMAK_LAYER:
            oled_write_ln_P(PSTR("Colemak"), false);
            break;
        case NUMBER_LAYER:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case CHARS_LAYER:
            oled_write_ln_P(PSTR("Chars"), false);
            break;
        case MOUSE_LAYER:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case QWERTY_LAYER:
          oled_write_ln_P(PSTR("QWERTY"), false);
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

#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case TRM_COPY:
    if (record->event.pressed) {
      // when keycode TRM_COPY is pressed
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      tap_code(KC_C);
      unregister_code(KC_LSFT);
      unregister_code(KC_LCTL);
    }
    break;
  case TRM_PSTE:
    if (record->event.pressed) {
      // when keycode TRM_PSTE is pressed
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      tap_code(KC_V);
      unregister_code(KC_LSFT);
      unregister_code(KC_LCTL);
    }
    break;
  case QWRT_UA:
    if (record->event.pressed) {
      // when keycode QWRT_UA is pressed
      layer_clear();
      layer_on(QWERTY_LAYER);
      register_code(KC_LSFT);
      tap_code(KC_CAPS);
      unregister_code(KC_LSFT);
    }
    break;
  case CLM_EN:
    if (record->event.pressed) {
      // when keycode CLM_EN is pressed
      tap_code(KC_CAPS);
      layer_clear();
      layer_on(COLMAK_LAYER);
    }
    break;
  case UML_SEQ:
    if (record->event.pressed) {
      // when keycode UML_SEQ is pressed
      tap_code(KC_PSCR);
      register_code(KC_LSFT);
      tap_code(KC_QUOT);
      unregister_code(KC_LSFT);
    }
    break;
  }
#ifdef OLED_ENABLE
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
#endif // oled_enable

  return true;
};

#ifdef COMBO_ENABLE
enum combo_events {
  QWERTY_COMBO,
  ESC_COMBO,
  UML_COMBO,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM qwerty_combo[] = {KC_B, KC_J, COMBO_END};
const uint16_t PROGMEM esc_combo[] = {KC_G, KC_M, COMBO_END};
const uint16_t PROGMEM uml_combo[] = {KC_V, KC_K, COMBO_END};
combo_t key_combos[] = {
    [QWERTY_COMBO] = COMBO_ACTION(qwerty_combo), // keycodes with modifiers are possible too!
    [ESC_COMBO] = COMBO_ACTION(esc_combo),
    [UML_COMBO] = COMBO_ACTION(uml_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
  case QWERTY_COMBO:
    if (pressed) {
      layer_clear();
      layer_on(QWERTY_LAYER);
      register_code(KC_LSFT);
      tap_code(KC_CAPS);
      unregister_code(KC_LSFT);
    }
    break;
  case ESC_COMBO:
    if (pressed) {
      tap_code(KC_ESC);
    }
    break;
  case UML_COMBO:
    if (pressed) {
      tap_code(KC_PSCR);
      register_code(KC_LSFT);
      tap_code(KC_QUOT);
      unregister_code(KC_LSFT);
    }
    break;
  }
}
#endif // COMBO_ENABLE

#ifdef RGBLIGHT_ENABLE

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (state) {
        case COLMAK_LAYER:
            rgblight_setrgb(RGB_GREEN);
            break;
        case NUMBER_LAYER:
            rgblight_setrgb(RGB_YELLOW);
            break;
        case CHARS_LAYER:
            rgblight_setrgb(RGB_BLUE);
            break;
        case MOUSE_LAYER:
            rgblight_setrgb(RGB_RED);
            break;
        case QWERTY_LAYER:
            rgblight_setrgb(RGB_MAGENTA);
            break;
        default:
            rgblight_setrgb(RGB_GOLD);
            break;
    }
    return state;
}
#endif // RGBLIGHT_ENABLE
