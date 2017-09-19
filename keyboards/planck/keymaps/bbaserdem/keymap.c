/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"

#define _______ KC_TRNS
#define XXX KC_NO

#define _DV 0
#define _TD 1
#define _GM 2
#define _MO 3
#define _SY 4
#define _FN 5
#define _MS 6

#define PARAN TD(PAR)
#define CURLY TD(CUR)
#define SQUAR TD(SQU)
#define ANGUL TD(ANG)

#define UNDO    LCTL(KC_Z)
#define REDO    LCTL(KC_Y)
#define COPYCUT TD(CPC)
#define PASTE   LCTL(KC_V)

#define MO_SC_U KC_MS_WH_UP
#define MO_SC_D KC_MS_WH_DOWN
#define MO_SC_L KC_MS_WH_LEFT
#define MO_SC_R KC_MS_WH_RIGHT
#define MO_U    KC_MS_UP
#define MO_D    KC_MS_DOWN
#define MO_L    KC_MS_LEFT
#define MO_R    KC_MS_RIGHT
#define MO_CL_L KC_MS_BTN1
#define MO_CL_R KC_MS_BTN2
#define MO_CL_M KC_MS_BTN3
#define MO_CL_1 KC_MS_BTN4
#define MO_CL_2 KC_MS_BTN5
#define MO_AC_0 KC_MS_ACCEL0
#define MO_AC_1 KC_MS_ACCEL1
#define MO_AC_2 KC_MS_ACCEL2

#define PHY_HB UC(0x0127)
#define PHY_DE UC(0xc2b0)
#define TUR_TL UC(0x20ba)
#define EUR_ER UC(0x20ac)
#define EUR_PN UC(0x00a3)

enum custom_keycodes {
    TUR_A = SAFE_RANGE,
    TUR_C,
    TUR_G,
    TUR_I,
    TUR_O,
    TUR_S,
    TUR_U,
    UNI_LI,
    UNI_WN
};

// Tap dance
enum {
    ATD = 0,
    CLS,
    SCL,
    QUO,
    PAR,
    CUR,
    SQU,
    ANG,
    CPC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Dvorak
 * ,------------------------------------------------------------------------.
 * | Blt |  "  |  ,  |  .  |  P  |  Y  ||  F  |  G  |  C  |  R  |  L  | Bkp |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Esc |  A  |  O  |  E  |  U  |  I  ||  D  |  H  |  T  |  N  |  S  | Del |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |Sh\CL| ; : |  Q  |  J  |  K  |  X  ||  B  |  M  |  W  |  V  |  Z  |MOUSE|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Ctl | Alt | Meta| Tab | SYM | Spc || Ent | FUN | Lft | Dwn |  Up | Rgt |
 * `------------------------------------------------------------------------'
 */
[_DV] = {
  {BL_STEP,TD(QUO),KC_COMM,KC_DOT, KC_P,   KC_Y,   KC_F,   KC_G,   KC_C,   KC_R,   KC_L,   KC_BSPC},
  {KC_ESC ,KC_A,   KC_O,   KC_E,   KC_U,   KC_I,   KC_D,   KC_H,   KC_T,   KC_N,   KC_S,   KC_DEL },
  {TD(CLS),TD(SCL),KC_Q,   KC_J,   KC_K,   KC_X,   KC_B,   KC_M,   KC_W,   KC_V,   KC_Z,   TT(_MO)},
  {KC_LCTL,TD(ATD),KC_LGUI,KC_TAB, TT(_SY),KC_SPC, KC_ENT, TT(_FN),KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT}
},
[_TD] = {
  {_______,_______,_______,_______,_______,_______,_______, TUR_G, TUR_C,  _______,_______,_______},
  {_______, TUR_A,  TUR_O, _______, TUR_U,  TUR_I, _______, PHY_HB,_______,_______, TUR_S, _______},
  {_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______},
  {_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______}
},

/* Game layer
 * ,------------------------------------------------------------------------.
 * | OFF |  Q  |  W  |  E  |  R  |  T  ||  F1 |  F2 | Ctrl|  ^  |Shift| Esc |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |  ~  |  A  |  S  |  D  |  F  |  G  ||  F3 |  F4 |  <  |  v  |  >  |Enter|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Shf |  Z  |  X  |  C  |  V  |  B  ||  F5 |  F6 |  ,  |  .  | / ? | Alt |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * | Alt | Ctrl| ` ~ | - _ |     | Spc || Spc |     |  1  |  2  |  3  |  4  |
 * `------------------------------------------------------------------------'
 */
[_GM] = {
  {TG(_GM),KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_F1,  KC_F2,  KC_RCTL,KC_UP,  KC_RSFT,KC_ESC },
  {KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_F3,  KC_F4,  KC_LEFT,KC_DOWN,KC_RGHT,KC_ENT },
  {KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_F5,  KC_F6,  KC_COMM,KC_DOT, KC_SLSH,KC_RALT},
  {KC_LALT,KC_LCTL,KC_GRV, KC_MINS,_______,KC_SPC, KC_SPC, _______,KC_1,   KC_2,   KC_3,   KC_4   }
},

/* Mouse control layer
 * ,------------------------------------------------------------------------.
 * |     |.....|  ^  |.....|.....|Acc 2||.....|.....|.....| |^| |.....|     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |  <  |  v  |  >  |.....|Acc 1||.....|.....| <-- | |v| | --> |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     | Left| Mid |Right|.....|Acc 0||.....|.....|Btn 4|.....|Btn 5|     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |     ||     |     |     |     |     |     |
 * `------------------------------------------------------------------------'
 */
[_MO] = {
  {TG(_MO),XXX,    MO_U,   XXX,    XXX,    MO_AC_2,XXX,    XXX,    XXX,    MO_SC_U,XXX,    _______},
  {_______,MO_L,   MO_D,   MO_R,   XXX,    MO_AC_1,XXX,    XXX,    MO_SC_L,MO_SC_D,MO_SC_R,_______},
  {_______,MO_CL_L,MO_CL_M,MO_CL_R,XXX,    MO_AC_0,XXX,    XXX,    MO_CL_1,XXX,    MO_CL_2,_______},
  {_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______}
},

/* Symbols layer
 * ,------------------------------------------------------------------------.
 * | OFF |  !  |  1  |  2  |  3  |  &  ||  =  |  +  |  -  |  *  |  %  |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |  _  | ( ) |  4  |  5  |  6  |  \  ||  /  | [ ] | { } | < > |  |  |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |degre|  ?  |  7  |  8  |  9  |  ~  ||  `  |  @  |  #  |  $  |  ^  |     |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |  0  |     |     ||     |     |TLira| Euro|Pound|     |
 * `------------------------------------------------------------------------'
 */

[_SY] = {
  {TG(_SY),KC_EXLM,KC_1,   KC_2,   KC_3,   KC_AMPR,KC_EQL, KC_PLUS,KC_MINS,KC_ASTR,KC_PERC,_______},
  {KC_UNDS,PARAN,  KC_4,   KC_5,   KC_6,   KC_BSLS,KC_SLSH,SQUAR,  CURLY,  ANGUL,  KC_PIPE,_______},
  {PHY_DE, KC_QUES,KC_7,   KC_8,   KC_9,   KC_TILD,KC_GRV, KC_AT,  KC_HASH,KC_DLR, KC_CIRC,_______},
  {_______,_______,_______,KC_0,   _______,_______,_______,_______,TUR_TL, EUR_ER, EUR_PN, _______}
},

/* Function layer
 * ,------------------------------------------------------------------------.
 * | OFF | game|music|     |     |RESET||RESET| win | lin | wake|sleep|power|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 ||  F7 |  F8 |  F9 | F10 | F11 | F12 |
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     | undo| redo|cutcp|paste|vol 0||prtsc| ins | rev.| stop| play| next|
 * |-----+-----+-----+-----+-----+-----++-----+-----+-----+-----+-----+-----|
 * |     |     |     |     |     |vol -||vol +|     | home|pg dn|pg up| end |
 * `------------------------------------------------------------------------'
 */

[_FN] = {
  {TG(_FN),TG(_GM),MU_ON,  _______,_______,RESET,  RESET,  UNI_LI, UNI_WN ,KC_WAKE,KC_SLEP,KC_PWR },
  {KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12 },
  {_______,UNDO,   REDO,   COPYCUT,PASTE,  KC_MUTE,KC_PSCR,KC_INS, KC_MPRV,KC_MSTP,KC_MPLY,KC_MNXT},
  {_______,_______,_______,_______,_______,KC_VOLD,KC_VOLU,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END }
},

/* Music layer
 * ,-----------------------------------------------------------------------.
 * | OFF |rec S| stop| play|sped^|spedv|cycle|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |.....|.....|.....|.....|.....|.....|.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |.....|.....|.....|.....|.....|.....|.....|.....|.....|.....|.....|.....|
 * |-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
 * |.....|.....|.....|.....|.....|.....|.....|.....|.....|.....|.....|.....|
 * `-----------------------------------------------------------------------'
 */
[_MS] = {
    { MU_OFF, KC_LCTL, KC_LALT, KC_LGUI, KC_UP, KC_DOWN, MU_MOD, XXX, XXX, XXX, XXX, XXX },
    { XXX,    XXX,     XXX,     XXX,     XXX,   XXX,     XXX,    XXX, XXX, XXX, XXX, XXX },
    { XXX,    XXX,     XXX,     XXX,     XXX,   XXX,     XXX,    XXX, XXX, XXX, XXX, XXX },
    { XXX,    XXX,     XXX,     XXX,     XXX,   XXX,     XXX,    XXX, XXX, XXX, XXX, XXX }
}
};

// Set unicode method to linux.
void matrix_init_user(){
  set_unicode_input_mode(UC_LNX);
}

// User defined keys
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // This section is a bit tedious in VIM, so I shortened lines
  // Check for shift letter
  bool is_capital = ( keyboard_report->mods &
      (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) ) ^
      ( keyboard_report->mods & MOD_BIT(KC_CAPS) );
  switch (keycode) {
    // Add music layer to music functionality
    case MU_ON:
      if (record->event.pressed) { layer_on(_MS); }
      return true; break;
    case MU_OFF:
      if (record->event.pressed) { layer_off(_MS); }
      return true; break;
    // Turkish letters keycodes
    case TUR_A:
      if (record->event.pressed) {
        if ( is_capital ) {
            unicode_input_start(); register_hex(0x00c2); unicode_input_finish();
        } else {
            unicode_input_start(); register_hex(0x00e2); unicode_input_finish();
        }
      }
      return false; break;
    case TUR_U:
      if (record->event.pressed) {
        if ( is_capital ) {
            unicode_input_start(); register_hex(0x00dc); unicode_input_finish();
        } else {
            unicode_input_start(); register_hex(0x00fc); unicode_input_finish();
        }
      }
      return false; break;
    case TUR_I:
      if (record->event.pressed) {
        if ( is_capital ) {
            unicode_input_start(); register_hex(0x0130); unicode_input_finish();
        } else {
            unicode_input_start(); register_hex(0x0131); unicode_input_finish();
        }
      }
      return false; break;
    case TUR_O:
      if (record->event.pressed) {
        if ( is_capital ) {
            unicode_input_start(); register_hex(0x00d6); unicode_input_finish();
        } else {
            unicode_input_start(); register_hex(0x00f6); unicode_input_finish();
        }
      }
      return false; break;
    case TUR_S:
      if (record->event.pressed) {
        if ( is_capital ) {
            unicode_input_start(); register_hex(0x015e); unicode_input_finish();
        } else {
            unicode_input_start(); register_hex(0x015f); unicode_input_finish();
        }
      }
      return false; break;
    case TUR_G:
      if (record->event.pressed) {
        if ( is_capital ) {
            unicode_input_start(); register_hex(0x011e); unicode_input_finish();
        } else {
            unicode_input_start(); register_hex(0x011f); unicode_input_finish();
        }
      }
      return false; break;
    case TUR_C:
      if (record->event.pressed) {
        if ( is_capital ) {
            unicode_input_start(); register_hex(0x00c7); unicode_input_finish();
        } else {
            unicode_input_start(); register_hex(0x00e7); unicode_input_finish();
        }
      }
      return false; break;
    // Keys to change unicode mode
    case UNI_LI:
      if( record->event.pressed ) {
          set_unicode_input_mode(UC_LNX);
      }
      return false; break;
    case UNI_WN:
      if( record->event.pressed ) {
          set_unicode_input_mode(UC_WIN);
      }
      return false; break;
  }
  return true;
}

// Tap dance feature for the altgr implementation
void altgr_dvo_tap (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_RALT);
  } else if (state->count == 2) {
    unregister_code (KC_RALT);
    layer_on(_TD);
  } else if (state->count == 3) {
      layer_off(_TD);
  }
}
void altgr_dvo_end (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
      unregister_code (KC_RALT);
  } else if (state->count == 2) {
      layer_off(_TD);
  }
}

// Shift vs capslock function
void caps_tap (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_LSFT);
    } else if (state->count == 2) {
        unregister_code (KC_LSFT);
        register_code (KC_CAPS);
    }
}
void caps_tap_end (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_LSFT);
    } else {
        unregister_code (KC_CAPS);
    }
}

// Parantheses
void paranthesis_dance (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("()"); register_code(KC_LEFT); unregister_code(KC_LEFT);
        } else if (state->count == 2) {
            SEND_STRING("(");
        } else if (state->count == 3) {
            SEND_STRING(")");
    }
}
void curly_dance (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("{}"); register_code(KC_LEFT); unregister_code(KC_LEFT);
        } else if (state->count == 2) {
            SEND_STRING("{");
        } else if (state->count == 3) {
            SEND_STRING("}");
    }
}

void square_dance (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("[]"); register_code(KC_LEFT); unregister_code(KC_LEFT);
        } else if (state->count == 2) {
            SEND_STRING("[");
        } else if (state->count == 3) {
            SEND_STRING("]");
    }
}

void angular_dance (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        SEND_STRING("<>"); register_code(KC_LEFT); unregister_code(KC_LEFT);
        } else if (state->count == 2) {
            SEND_STRING("<");
        } else if (state->count == 3) {
            SEND_STRING(">");
    }
}

// Copy or cut feature
void copy_cut (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_LCTL);
        register_code (KC_C);
        unregister_code (KC_C);
        unregister_code (KC_LCTL);
    } else if (state->count == 2) {
        register_code (KC_LCTL);
        register_code (KC_X);
        unregister_code (KC_X);
        unregister_code (KC_LCTL);
    }
}

// Tap dance feature
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Left Ctrl, second one is momentory switch to layer TUR
     [ATD] = ACTION_TAP_DANCE_FN_ADVANCED( altgr_dvo_tap, NULL, altgr_dvo_end )
    // Advanced tap dance feature allows for immediate response to shift
    ,[CLS] = ACTION_TAP_DANCE_FN_ADVANCED( caps_tap, NULL, caps_tap_end )
    // Shifting for double quote and semicolon
    ,[SCL] = ACTION_TAP_DANCE_DOUBLE( KC_SCLN, KC_COLN )
    ,[QUO] = ACTION_TAP_DANCE_DOUBLE( KC_QUOT, KC_DQUO )
    // Tap dances for paranthesis, which sends macros
    ,[PAR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, paranthesis_dance )
    ,[CUR] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, curly_dance )
    ,[SQU] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, square_dance )
    ,[ANG] = ACTION_TAP_DANCE_FN_ADVANCED( NULL, NULL, angular_dance )
    // Tap dance for copy/cutting
    ,[CPC] = ACTION_TAP_DANCE_FN( copy_cut )
};
