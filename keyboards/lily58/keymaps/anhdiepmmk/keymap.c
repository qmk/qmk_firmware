 /* Copyright 2020 Naoki Katahira
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H
#include <stdio.h>

//extern uint8_t is_master;

// home row mod
#define HO_A MT(MOD_LCTL, KC_A)
#define HO_S MT(MOD_LSFT, KC_S)
#define HO_D MT(MOD_LALT, KC_D)
#define HO_F MT(MOD_LCTL, KC_F)
#define HO_J MT(MOD_RGUI, KC_J)
#define HO_K MT(MOD_RALT, KC_K)
#define HO_L MT(MOD_RSFT, KC_L)
#define HO_SCLN MT(MOD_RCTL, KC_SCLN)

enum layer_number {
  _BASE = 0,
  _NAV,
  _NUM,
  _SYM,
  _MED,
  _FUN,
};

#define TH_NAV LT(_NAV, KC_TAB)
#define TH_NUM LT(_NUM, KC_BSPC)
#define TH_SYM LT(_SYM, KC_ENT)
#define TH_MED LT(_MED, KC_ESC)
#define TH_FUN LT(_FUN, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* 
 * BASE
 */

 [_BASE] = LAYOUT(
  _______,  _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
  _______,  KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                             KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , _______,
  _______,  HO_A   , HO_S   , HO_D   , HO_F   , KC_G   ,                             KC_H   , HO_J   , HO_K   , HO_L   , HO_SCLN, _______,
  _______,  KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , _______,           _______, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, _______,
                              _______, TH_MED , TH_NAV , KC_SPC ,           TH_SYM , TH_NUM , TH_FUN , _______
),
/* 
 * NAV
 */
[_NAV] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______ , _______     , _______,
  _______, _______, _______, _______, _______, _______,                          _______, KC_HOME, _______, KC_END  , KC_PAGE_UP  , _______,
  _______, _______, _______, _______, _______, _______,                          KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT, KC_PAGE_DOWN, _______,
  _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______ , _______     , _______,
                             _______, _______, _______, _______,        _______, _______, _______, _______
),
/* 
 * NUM
 */
[_NUM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  _______, KC_LBRC, KC_7   , KC_8   , KC_9   , KC_RBRC,                       _______, _______, _______, _______, _______, _______,
  _______, KC_QUOT, KC_4   , KC_5   , KC_6   , KC_EQL ,                       _______, _______, _______, _______, _______, _______,
  _______, KC_GRV , KC_1   , KC_2   , KC_3   , KC_BSLS, _______,     _______, _______, _______, _______, _______, _______, _______,
                             _______, KC_DOT , KC_0   , KC_MINS,     _______, _______, _______, _______
),
/* 
 * SYM
 */
[_SYM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  _______, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                       _______, _______, _______, _______, _______, _______,
  _______, KC_DQT , KC_DLR , KC_PERC, KC_CIRC, KC_PLUS,                       _______, _______, _______, _______, _______, _______,
  _______, KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_PIPE, _______,     _______, _______, _______, _______, _______, _______, _______,
                             _______, KC_LPRN, KC_RPRN, KC_UNDS,     _______, _______, _______, _______
),
/* 
 * MED
 */
[_MED] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                       _______, _______   , _______          , _______        , _______, _______,
  _______, _______, _______, _______, _______, _______,                       _______, _______   , _______          , _______        , _______, _______,
  _______, _______, _______, _______, _______, _______,                       _______, KC_MPRV   , KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_MNXT, _______,
  _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______   , _______          , _______        , _______, _______,
                             _______, _______, _______, _______,     KC_MSTP, KC_MPLY, KC_KB_MUTE, _______
),
/* 
 * FUN
 */
[_FUN] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  _______, KC_F12 , KC_F7  , KC_F8  , KC_F9  , KC_PSCR,                       _______, _______, _______, _______, _______, _______,
  _______, KC_F11 , KC_F4  , KC_F5  , KC_F6  , KC_SCRL,                       _______, _______, _______, _______, _______, _______,
  _______, KC_F10 , KC_F1  , KC_F2  , KC_F3  , KC_PAUS, _______,     _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______,     _______, _______, _______, _______
),
};

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // state = update_tri_layer_state(state, _RAISE, _NAV, _ADJUST);
    return state;
}

static void render_logo(void) {
    static const char PROGMEM logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(logo, false);
}
char keylog_str[24] = {};
char keylogs_str[21] = {};
int keylogs_str_idx = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);

  // update keylogs
  if (keylogs_str_idx == sizeof(keylogs_str) - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < sizeof(keylogs_str) - 1; i++) {
      keylogs_str[i] = ' ';
    }
  }

  keylogs_str[keylogs_str_idx] = name;
  keylogs_str_idx++;
}

const char *read_keylog(void) {
  return keylog_str;
}

const char *read_keylogs(void) {
  return keylogs_str;
}
//new

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
    case _BASE:
        oled_write_ln_P(PSTR("Base"), false);
        break;
    case _NAV:
        oled_write_ln_P(PSTR("Nav"), false);
        break;
    case _NUM:
        oled_write_ln_P(PSTR("Num"), false);
        break;
    case _SYM:
        oled_write_ln_P(PSTR("Sym"), false);
        break;
    case _MED:
        oled_write_ln_P(PSTR("Med"), false);
        break;
    case _FUN:
        oled_write_ln_P(PSTR("Fun"), false);
        break;
    default:
        oled_write_ln_P(PSTR("Undefined"), false);
    }

    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);

  } else {
      render_logo();
  }
    return false;
}
#endif // OLED_ENABLE


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
