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

enum custom_layers {
    _QWERTY,
    _SYMBOL,
    _NAVIGATION,
    _FKEYS,
};


#define SYM MO(_SYMBOL)
#define NAV MO(_NAVIGATION)
#define MED MO(_FKEYS)

#define ECTRL LCTL_T(KC_ESC)
#define JCTRL RCTL_T(KC_J)
#define KALT LALT_T(KC_K)        
#define DASHMED LT(MED, KC_MINS)    
#define TMUX LCTL(KC_B)
#define KILL LALT(KC_F4)
#define CTL0 LCTL(KC_0)
#define CTL1 LCTL(KC_1)
#define CTL2 LCTL(KC_2)
#define CTL3 LCTL(KC_3)
#define CTL4 LCTL(KC_4)
#define CTL5 LCTL(KC_5)
#define CTL6 LCTL(KC_6)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ECTRL,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  DASHMED,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,     KC_D,   KC_F,    KC_G,                         KC_H,   JCTRL,    KALT,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          SYM,    KC_SPC,  KC_BSPC,     KC_DEL,   KC_ENT, NAV
                                      //`--------------------------'  `--------------------------'

  ),

  [_SYMBOL] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ECTRL,  KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                      KC_PEQL, KC_7,    KC_8,    KC_9,    KC_ASTR, KC_AMPR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,  KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                       KC_DOT,  KC_4,    KC_5,    KC_6,    KC_PLUS, KC_RCTL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD,                      KC_0,    KC_1,    KC_2,    KC_3,    KC_BSLS, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,  KC_SPC,  KC_BSPC,   KC_DEL,   KC_ENT, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAVIGATION] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      ECTRL,  XXXXXXX, KC_LCMD, KC_MS_U,  KC_F5, KC_WH_U,                       KC_PGUP, KC_HOME, KC_MINS, XXXXXXX, KC_END,  XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TAB,  XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                      KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, XXXXXXX, KC_MPLY,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, KC_PSCR, KC_COPY,  KC_PASTE, TMUX,                       KC_PGDN, XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,  KC_BTN1,  KC_BTN2,   KC_DEL,   KC_ENT, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

  [_FKEYS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_F1,   KC_F2,     KC_F3,   KC_F4,   KC_F5,  KC_F6,                       KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LALT, KC_VOLU, XXXXXXX, KC_MRWD, XXXXXXX, KC_MNXT,                    XXXXXXX, CTL4,    CTL5,    CTL6,    XXXXXXX, KILL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_VOLD, KC_MUTE, DT_UP, DT_DOWN, DT_PRNT,                 CTL0,    CTL1,    CTL2,    CTL3,    XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX,  KC_SPC,  KC_BSPC,   KC_DEL,   KC_ENT, XXXXXXX
                                      //`--------------------------'  `--------------------------'
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


char     key_name = ' ';
uint16_t last_keycode;
uint8_t  last_row;
uint8_t  last_col;

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
