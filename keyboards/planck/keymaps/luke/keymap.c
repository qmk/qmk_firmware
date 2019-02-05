/*
 * A keyboard layout for the gridded planck.
 *
 * Copyright (C) 2017 Luke Silva
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
 * This layout uses colemak by default, and is designed for programming, with easy access to symbols
 * through either double purpose modifiers or colemak style rolling for commonly used symbol clusters
 * Eg: compare colemak 'this' to '(){\n}' on the symbol layer.
 *
 * The layout also supports a range of multilingual characters, covering those
 * needed for French, German, Swedish and likely some other European Languages.
 * In the future full support for Colemak's multilingual deadkeys may be introduced.
 *
 * The multilingual characters are inputted through QMK's unicode engine, using
 * the Linux input method by default, however this can be changed at runtime.
 *
 */


#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO


// Layers
#define _COLEMAK 0
#define _QWERTY 1
#define _SYM 2
#define _NUM 3
#define _GR  4
#define _GR_S 5
#define _ADJ 6
#define _NAV 7
#define _PLOVER 8

// Macro ID numbers
#define M_ALT_HASH 1
#define M_GR_DASH  2
#define M_SYM_LPRN 3
#define M_NAV_UNDS 4
#define M_NUM_RPRN 5
#define M_CTRL_DLR 6
#define M_LCBR_ENT 7
#define M_PLOVER   8
#define M_EXT_PLV  9
#define M_WINDOWS 10
#define M_LINUX   11
#define M_OSX     12
#define M_FUNCTION 13
#define M_THEN     14
#define M_CATCH    15

// Macro keys
#define ALT_HASH MACROTAP(M_ALT_HASH)   // tap for #, hold for Alt
#define GR_DASH  MACROTAP(M_GR_DASH)    // tap for -, hold for GR layer            a-class-name
#define SYM_LPRN MACROTAP(M_SYM_LPRN)   // tap for (, hold for symbols layer       if()
#define NAV_UNDS MACROTAP(M_NAV_UNDS)   // tap for _, hold for navigation layer    snake_case_variable
#define NUM_RPRN MACROTAP(M_NUM_RPRN)   // tap for ), hold for numbers layer       else if()
#define CTRL_DLR MACROTAP(M_CTRL_DLR)   // tap for $, hold for ctrl                $php_is_really_weird
#define LCBR_ENT M(M_LCBR_ENT)          // {\n                                     easier code formatting
#define PLOVER   M(M_PLOVER)            // PHROPB (plover) or ERFVIK(qwerty)       starts plover
#define EXT_PLV  M(M_EXT_PLV)           // PHRO*F (plover) or ERFVYU(qwerty)       stops plover
#define WINDOWS  M(M_WINDOWS)           // Sets Unicode handler to windows
#define LINUX    M(M_LINUX)             // Sets Unicode handler to linux
#define OSX      M(M_OSX)               // Sets Unicode handler to OSX
#define FUNCTION M(M_FUNCTION)
#define THEN     M(M_THEN)
#define CATCH    M(M_CATCH)


// Renames of QMK keys... (would have otherwise been a macro)
#define QWERTY DF(_QWERTY)
#define COLEMAK DF(_COLEMAK)





const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |  ;:  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Bksp |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  '"  |
 * |------+------+------+------+------+------+------+------+------+------+------+------`---.
 * |Shift=|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |  ,<  |  .>  |  /?  |Shift/Ent |
 * |------+------+------+------+------+------+------+------+------+------+------+----------|
 * |CtCaps|GUIF4 | Alt# | Gr-  | Sym( | Nav_ |Space | Num) |Ctrl$ | F11  | F12  |Nav toggle|
 * `---------------------------------------------------------------------------------------'
 */

[_COLEMAK] = {
  {KC_TAB,         KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC},
  {KC_BSPC,        KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT},
  {SFT_T(KC_EQL),  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_T(KC_ENT) },
  {CTL_T(KC_CAPS), KC_LGUI,  ALT_HASH, GR_DASH, SYM_LPRN, NAV_UNDS,  KC_SPC, NUM_RPRN, CTRL_DLR, KC_F11, KC_F12, TG(_NAV)}
},



/* QWERTY
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Bksp |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:  |  '"  |
 * |------+------+------+------+------+------+------+------+------+------+------+------`---.
 * |Shift=|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  |Shift/Ent |
 * |------+------+------+------+------+------+------+------+------+------+------+----------|
 * |CtCaps|GUIF4 | Alt# | Gr-  | Sym( | Nav_ |Space | Num) |Ctrl$ | F11  | F12  |Nav toggle|
 * `---------------------------------------------------------------------------------------'
 */

[_QWERTY] = {
  {KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_T(KC_ENT) },
  {CTL_T(KC_CAPS),    KC_LGUI, KC_LALT, GR_DASH, SYM_LPRN,KC_SPC,  KC_SPC, NUM_RPRN, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT}
},


/* Symbols
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  `   |  @   |  /   |  *   |  ^   |  %   |  :   |  +   |  -   | Del  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  [   |  ;   |  }   |  (   |  "   |  '   |  )   | {\n  |  !   |  ]   |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shift |  .   |  {   |  <   |  >   |  ~   |  X2  |  =   |  &   |  |   |  ?   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | Sym  |  _   |Space | NUM  |  X2  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_SYM] = {
  {KC_TAB,  KC_GRV,  KC_AT,   KC_SLSH, KC_ASTR, KC_CIRC, KC_PERC, KC_COLN, KC_PLUS, KC_MINS, KC_DEL,  KC_BSPC},
  {FUNCTION,KC_LBRC, KC_SCLN, KC_RCBR, KC_LPRN, KC_DQT,  KC_QUOT, KC_RPRN, LCBR_ENT,KC_EXLM, KC_RBRC, KC_BSLS},
  {KC_LSFT, KC_DOT,  KC_LCBR, KC_LABK, KC_RABK, KC_TILD, _______, KC_EQL,  KC_AMPR, KC_PIPE, KC_QUES, KC_ENT },
  {THEN,    CATCH,   XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, _______}
},


/* Numbers
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  1   |  2   |  3   |  4   |  5   |  6   |  7   |  8   |  9   |  0   | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Bksp |  x   |  D   |  E   |  F   |  +   |  -   |  4   |  5   |  6   |  0   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Shift |  (   |  A   |  B   |  C   |  *   |  /   |  1   |  2   |  3   |  )   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  GR  | SYM  |  _   |Space | NUM  |  0   |  .   |  f   |      |
 * `-----------------------------------------------------------------------------------'
 */

[_NUM] = {
  {KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_BSPC, KC_X,    S(KC_D), S(KC_E), S(KC_F), KC_PLUS, KC_MINS, KC_4,    KC_5,    KC_6,    KC_0,    KC_ENT },
  {KC_LSFT, KC_LPRN, S(KC_A), S(KC_B), S(KC_C), KC_ASTR, KC_SLSH, KC_1,    KC_2,    KC_3,    KC_RPRN, KC_ENT },
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_DOT,  KC_F,    _______}
},


/* Gr layer / international keys
 * ,-----------------------------------------------------------------------------------.
 * |      |  ä   |  å   |      |  ¢£  |  €¥  |      |  ë   |  ê   |  ü   |  ù   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  â   |  à   |  ß   |      |      |      |  è   |  é   |  ï   |  ö   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  æ   |  ô   |  ç   |  œ   |      |      |  û   |  «   |  »   |  î   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_GR] = {
  {_______,  UC(0xE4),UC(0xE5), _______,UC(0xA2), UC(0x20AC),_______,UC(0xEB),UC(0xEA),UC(0xFC),UC(0xF9), _______},
  {_______,  UC(0xE2),UC(0xE0),UC(0xDF), _______, _______,   _______,UC(0xE8),UC(0xE9),UC(0xEF),UC(0xF6), _______},
  {MO(_GR_S),UC(0xE6),UC(0xF4),UC(0xE7),UC(0x153),_______,   _______,UC(0xFB),UC(0xAB),UC(0xBB),UC(0xEE), MO(_GR_S)},
  {_______,  _______, _______, _______, _______,  _______,   _______, _______, _______, _______, _______, _______}
},

// Shifted layer of the above
[_GR_S] = {
  {_______,  UC(0xC4),UC(0xC5), _______, UC(0xA3), UC(0xA5),_______, UC(0xCB),UC(0xCA),UC(0xDC),UC(0xD9),_______},
  {_______,  UC(0xC2),UC(0xC0), UC(0xDF),_______,  _______, _______, UC(0xC8),UC(0xC9),UC(0xCF),UC(0xD6),_______},
  {MO(_GR_S),UC(0xC6),UC(0xD4), UC(0xC7),UC(0x152),_______, _______, UC(0xDB),UC(0xAB),UC(0xBB),UC(0xCE),MO(_GR_S)},
  {_______,  _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______}
},


/* Adjust Layer (Gr + Num)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+-------------+------+------+------+------+------+------+------+------+------|
 * |      |     |Prntscr| ESC  |VOLUP | PLAY | PREV |QWERTY|COLEMAK|PLOVER|     |      |
 * |------+-------------+------+------+------+------+------+------+------+------+------|
 * |      |     |BACKLIT| INS  |VOLDWN| MUTE | NEXT | WIND |LINUX | OSX  |      |      |
 * |------+-------------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_ADJ] = {
  {KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12 },
  {XXXXXXX, XXXXXXX, KC_PSCR, KC_ESC,  KC_VOLU, KC_MPLY, KC_MPRV, QWERTY,  COLEMAK, PLOVER,  XXXXXXX, XXXXXXX},
  {XXXXXXX, XXXXXXX, BL_STEP, KC_INS,  KC_VOLD, KC_MUTE, KC_MNXT, WINDOWS, LINUX,   OSX,     XXXXXXX, XXXXXXX},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},


/* Navigation
 * ,-----------------------------------------------------------------------------------.
 * |      |      | BTN3 | BTN2 | BTN1 |      | ACL0 | HOME | PGDN | PGUP | END  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |MSLEFT| MSDN | MSUP |MSRGHT|      | ACL1 | LEFT | DOWN | UP   | RGHT |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |WHLEFT| WHDN | WHUP |WHRGHT|      | ACL2 |C-LEFT|C-PGDN|C-PGUP|C-RGHT|Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |  _   |Space | ACL0 | ACL1 | ACL2 |      |TGLNAV|
 * `-----------------------------------------------------------------------------------'
 */

[_NAV] = {
  {XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN2, KC_BTN1, XXXXXXX, KC_ACL0, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_BSPC},
  {XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, KC_ACL1, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_ENT },
  {XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, KC_ACL2, LCTL(KC_LEFT), LCTL(KC_PGDN), LCTL(KC_PGUP), LCTL(KC_RIGHT), KC_ENT },
  {_______, _______, _______, _______, _______, _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______}
},

/* Plover Layer
 * ,-----------------------------------------------------------------------------------.
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |TogOut|   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   #  |   A  |   O  |   E  |   U  |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = {
  {XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC},
  {XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   },
  {EXT_PLV, XXXXXXX, XXXXXXX, KC_1,    KC_C,    KC_V,    KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX}
}


};

void matrix_init_user(){
  set_unicode_input_mode(UC_LNX);
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  switch(id) {
    case M_ALT_HASH:
      return MACRO_TAP_SHFT_KEY_HOLD_MOD(record, 3, LALT);
    case M_GR_DASH:
      {
        const macro_t* macro = MACRO_TAP_HOLD_LAYER(record, MACRO(T(MINS)), _GR);
        update_tri_layer(_NUM, _GR, _ADJ);
        return macro;
      }
    case M_SYM_LPRN:
      return MACRO_TAP_SHFT_KEY_HOLD_LAYER(record, 9, _SYM);
    case M_NAV_UNDS:
      return MACRO_TAP_SHFT_KEY_HOLD_LAYER(record, MINS, _NAV);
    case M_NUM_RPRN:
      {
        const macro_t* macro = MACRO_TAP_SHFT_KEY_HOLD_LAYER(record, 0, _NUM);
        update_tri_layer(_NUM, _GR, _ADJ);
        return macro;
      }
    case M_CTRL_DLR:
      return MACRO_TAP_SHFT_KEY_HOLD_MOD(record, 4, LCTL);
    case M_LCBR_ENT:
      return MACRODOWN(I(10), D(LSFT), T(LBRC), U(LSFT), T(ENT), END);
    case M_PLOVER:
      if (record->event.pressed) {
        layer_and(0);
        layer_on(_PLOVER);
        default_layer_set(_PLOVER);

        // Starts plover
        return MACRO(I(10), D(E), D(R), D(F), D(V), D(I), D(K), U(E), U(R), U(F), U(V), U(I), U(K), END);
      }
      break;
    case M_EXT_PLV:
      if (!record->event.pressed) {
        layer_off(_PLOVER);
        default_layer_set(_COLEMAK);

        //Pauses plover
        return MACRO(I(10), D(E), D(R), D(F), D(V), D(Y), D(U), U(E), U(R), U(F), U(V), U(Y), U(U), END);
      }
      break;
    case M_WINDOWS:
      set_unicode_input_mode(UC_WIN);
      break;
    case M_LINUX:
      set_unicode_input_mode(UC_LNX);
      break;
    case M_OSX:
      set_unicode_input_mode(UC_OSX);
      break;
    case M_FUNCTION:
      if (record->event.pressed) {
        SEND_STRING("function");
      }
      break;
    case M_THEN:
      if (record->event.pressed) {
        SEND_STRING("then");
      }
      break;
    case M_CATCH:
      if (record->event.pressed) {
        SEND_STRING("catch");
      }
      break;
  }
  return MACRO_NONE;
};
