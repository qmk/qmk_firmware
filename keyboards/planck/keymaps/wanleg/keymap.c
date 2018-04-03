/* Copyright 2018 Brian Fong
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
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QW,
  _GK,
  SUB,
  SUP,
  gNUM,
  gDIR,
  gETC
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  GHERKIN,
  SUBTER,
  SUPRA,
  gNUMBER,
  gDIRECTION,
  gETCETERA,
};

/////////////// TAP DANCE SECTION START ///////////////
//Tap Dance Declarations (list of my tap dance configurations)
enum {
  TD_SFT_CAPS = 0
  ,TD_Q_ESC
};

///// QUAD FUNCTION TAP DANCE GENERAL SETUP SECTION START /////
///// (no need to edit this section) /////
//Enums used to clearly convey the state of the tap dance
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5 //send SINGLE_TAP twice - NOT DOUBLE_TAP
  // Add more enums here if you want for triple, quadruple, etc.
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted || !state->pressed) return SINGLE_TAP;
    if (state->interrupted) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap. In example below, that means to send `ff` instead of `Escape`.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else return 6; //magic number. At some point this method will expand to work for more presses
}

//Tap Dance Definitions
//THIS SECTION HAS TO BE AT THE END OF THE TAP DANCE SECTION
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
// Other declarations would go here, separated by commas, if you have them
 ,[TD_Q_ESC]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC)
};

//In Layer declaration, add tap dance item in place of a key code
//TD(TD_SFT_CAPS)

///////////// TAP DANCE SECTION END ///////////////

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------------------------------------------------------------------------------.
 * | Esc   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp  |
 * |-------+------+------+------+------+-------------+------+------+------+------+-------|
 * | Tab   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '    |
 * |-------+------+------+------+------+------|------+------+------+------+------+-------|
 * |Sft/Cps|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |ENT/SFT|
 * |-------+------+------+------+------+------+------+------+------+------+------+-------|
 * | LCTRL | LGUI | ALT  | ALT  | SUB  | SHIFT| SPACE| SUP  | RGUI | RALT | DEL  | CTRL  |
 * `-------------------------------------------------------------------------------------'
 */
[_QW] = {
  {KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {TD(TD_SFT_CAPS), 
            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_T(KC_ENT) },
  {KC_LCTL, KC_LGUI, KC_LALT, KC_LALT, SUBTER,  KC_LSFT, KC_SPC,  SUPRA,   KC_RGUI, KC_RALT, KC_DEL,  KC_RCTL}
},

/* Gherkin
 * .-----------------------------------------------------------------------------------------------------------.
 * | ESC    | Q//ESC | W      | E      | R      | T      | Y      | U      | I      | O      | P      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | TAB    | A      | S      | D      | F      | G      | H      | J      | K      | L      | ENTER  |  '     |
 * |        |        |        |        |        |        |        |        |        |        |SFThold |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |SFT/CAPS| Z      | X      | C      | V/gNUM | B/gETC | N      | M/gDIR | ,/GUI  | ./ALT  | BKSC   | ENT/SFT|
 * |        |SFThold |        |        |        |        |        |        |        |        |CTRLhold|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | LCTRL  | LGUI   | ALT    | ALT    | gNUM   | gETC   | SPACE  | gDIR   | RGUI   | ALT    | DEL    | CTRL   |
 * '-----------------------------------------------------------------------------------------------------------'
 */
[_GK] = {
  { KC_ESC, TD(TD_Q_ESC),   KC_W,    KC_E,    KC_R,           KC_T,          KC_Y,  KC_U,            KC_I,           KC_O,          KC_P,           KC_BSPC    },
  { KC_TAB, KC_A,           KC_S,    KC_D,    KC_F,           KC_G,          KC_H,  KC_J,            KC_K,           KC_L,          SFT_T(KC_SPC),  KC_QUOT    },
  { TD(TD_SFT_CAPS), 
			SFT_T(KC_Z),    KC_X,    KC_C,    LT(gNUM, KC_V), LT(gETC, KC_B),KC_N,  LT(gDIR, KC_M),  GUI_T(KC_COMM), ALT_T(KC_DOT), CTL_T(KC_BSPC), SFT_T(KC_ENT)},
  {KC_LCTL, KC_LGUI,        KC_LALT, KC_LALT, gNUMBER,        gETCETERA,     KC_SPC,gDIRECTION,      KC_RGUI,        KC_RALT,       KC_DEL,         KC_RCTL}
},

/* myGherkin Directional Modifiers
 * .-----------------------------------------------------------------------------------------------------------.
 * |        | TAB    |   up   |        | INS    | CTRL   | SHIFT  | PgUp   | HOME   |  -     |  =     | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | left   |  down  | right  | PrScr  | SHIFT  | CTRL   | PgDn   | END    |  [     |  ]     |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | P-Brk  |        |        |        |        |        |        | RGUI   | ALT    |  /     |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | qwerty |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */

 [gDIR] = { /* myGherkin Directional Modifiers */
  { _______, KC_TAB,  KC_UP,   _______, KC_INS,  KC_LCTL, KC_RSFT, KC_PGUP, KC_HOME, KC_MINS, KC_EQL , KC_DEL   },
  { _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PSCR, KC_LSFT, KC_RCTL, KC_PGDN, KC_END,  KC_LBRC, KC_RBRC, _______  },
  { _______, KC_PAUS, _______, _______, _______, _______, _______, _______, KC_RGUI, KC_RALT, KC_SLSH, _______  },
  { _______, _______, QWERTY,  _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },

/* myGherkin Numbers
 * .-----------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F11    | F12    |        |        |        | ENTER  | SHIFT  | RGUI   | ./ALT  | BKSC   |        |
 * |        |        |        |        |        |        |        |        |        |        |CTRLhold|		   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | ENTER  | SHIFT  | RGUI   |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */

 [gNUM] = { /* myGherkin Numbers */
  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______  },
  { _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______  },
  { _______, KC_F11,  KC_F12,  _______, _______, _______, KC_ENT,  KC_RSFT, KC_RGUI, ALT_T(KC_DOT), CTL_T(KC_BSPC), _______  },
  { _______, _______, _______, _______, _______, _______, KC_ENT,  KC_RSFT, KC_RGUI, _______, _______, _______  },
 },

/* myGherkin ETC
 * .-----------------------------------------------------------------------------------------------------------.
 * | RESET  |  `     | mUP    |        |        |        | SHIFT  | mUp    | mDown  |        |  \     | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | mLeft  | mDown  | mRight |        | SHIFT  |        | mBtn1  | mBtn2  |  ;     |  '     |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | Sft//Cp|        |        |        |        | C-A-D  |        |        | ALT    |  DEL   |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | C-A-D  |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */

 [gETC] = { /* myGherkin ETC */
  { RESET,   KC_GRV,  KC_MS_U, _______, _______, _______, KC_RSFT, _______, _______, _______, KC_BSLS, KC_DEL   },
  { _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_LSFT, KC_TRNS, KC_BTN1, KC_BTN2, KC_SCLN, KC_QUOT, _______  },
  { _______, TD(TD_SFT_CAPS), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LALT(LCTL(KC_DEL)), KC_TRNS, KC_TRNS, KC_LALT, KC_DEL,  _______  },
  { _______, _______, _______, _______, _______, _______, LALT(LCTL(KC_DEL)), _______, _______, _______, _______, _______  },
 },

/* SUB
 * .-----------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |    `   | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | F11    | F12    |        |        |        |        |musicOFF| RGUI   | ./ALT  | BKSC   |        |
 * |        |        |        |        |        |        |        |        |        |        |CTRLhold|		   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | gherkin|        |        |        | ENTER  | SHIFT  |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */
[SUB] = {
  { _______,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_F7,   KC_F8,  KC_F9,          KC_F10,         _______  },
  { KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,   KC_9,           KC_0,           _______  },
  { _______, KC_F11,  KC_F12,  _______, _______, _______, _______, MU_OFF,  KC_RGUI,ALT_T(KC_DOT),  CTL_T(KC_BSPC), _______  },
  { _______, _______, GHERKIN, _______, _______, _______, KC_ENT,  KC_LSFT, _______, _______,       _______,        _______  }
},

/* SUPRA
 * .-----------------------------------------------------------------------------------------------------------.
 * | RESET  | TAB    |   up   |        | INS    | CTRL   | SHIFT  | PgUp   | Home   |   -    |   =    |  DEL   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |  left  |  down  | right  | PrScr  | SHIFT  | CTRL   | PgDn   | End    |   [    |   ]    |   \    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | P-Brk  |        |        |        |        |        | musicON| RGUI   | ALT    |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------'
 */
[SUP] = {
  { RESET,   KC_TAB,  KC_UP,   _______, KC_INS,  KC_LCTL, KC_RSFT, KC_PGUP, KC_HOME, KC_MINS, KC_EQL,  KC_DEL   },
  { _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PSCR, KC_LSFT, KC_RCTL, KC_PGDN, KC_END,  KC_LBRC, KC_RBRC, KC_BSLS  },
  { _______, KC_PAUS, _______, _______, _______, _______, _______, MU_ON,   KC_RGUI, KC_RALT, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  }
},
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QW);
      }
      return false;
      break;
    case GHERKIN:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GK);
      }
      return false;
      break;
    case SUBTER:
      if (record->event.pressed) {
        layer_on(SUB);
      } else {
        layer_off(SUB);
      }
      return false;
      break;
    case SUPRA:
      if (record->event.pressed) {
        layer_on(SUP);
      } else {
        layer_off(SUP);
      }
      return false;
      break;
	case gNUMBER:
      if (record->event.pressed) {
        layer_on(gNUM);

      } else {
        layer_off(gNUM);
      }
      return false;
      break;
	case gDIRECTION:
      if (record->event.pressed) {
        layer_on(gDIR);

      } else {
        layer_off(gDIR);
      }
      return false;
      break;
	case gETCETERA:
      if (record->event.pressed) {
        layer_on(gETC);

      } else {
        layer_off(gETC);
      }
      return false;
      break;
  }
  return true;
}
