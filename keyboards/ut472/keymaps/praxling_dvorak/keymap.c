/* Copyright 2018 Carlos Filoteo
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

#define L3_TAB LT(3, KC_TAB)
#define L5_
#define KC_LOCK RGUI(KC_L)
#define L4_SPACE LT(4, KC_SPC)
#define KC_HYP LCTL(LSFT(LALT(KC_LGUI)))
#define HYP5 LM(5, MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI)
#define TD_LAYER TD(TD_LAYER_SWAP)

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum custom_keycodes {
    TOG_OS = SAFE_RANGE,
    OSM_SHIFT,

    // shortcuts
    UC_COPY,
    UC_PASTE,
    UC_CUT,
    UC_UNDO,
    KC_COMMENT,

    // media
    KC_MUTING,
    KC_VUP,
    KC_VDOWN,

    // mouse
    KC_SCRL_UP,
    KC_SCRL_DWN
};

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap Dance Declarations
enum tapdance_id {
    TD_SCLN = 0,
    TD_COMM,
    TD_DOT,
    TD_MINS,
    TD_QUOT,
    TD_SFT,
    TD_LAYER_SWAP
};

int cur_dance (qk_tap_dance_state_t *state);

//for the sft tap dance. Put it here so it can be used in any keymap
void sft_finished (qk_tap_dance_state_t *state, void *user_data);
void sft_reset (qk_tap_dance_state_t *state, void *user_data);
void tap_finished (qk_tap_dance_state_t *state, void *user_data);
void tap_reset (qk_tap_dance_state_t *state, void *user_data);

bool is_mac = true;
bool mod_shift = false;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Base Layer
	* ,-------------------------------------------------------------------------.
	* | Esc |  ;  |  ,  |  .  |  P  |  Y  |  F  |  G  |  C  |  R  |  L  |Bspace |
	* |-------------------------------------------------------------------------+
	* |Tab/L3|A/Shift|O/Ctrl|E/Alt|U/Gui| I  | D |H/Gui|T/Alt|N/Ctrl|S/Shift| - |
	* |-------------------------------------------------------------------------+
	* | Shift |  '  |  Q  |  J  |  K  |  X  |  B  |  M  |  W  |  V  |  Z  |En/Sh|
	* |-------------------------------------------------------------------------+
	* | Ctrl | Alt | Gui | Hyp |  L2  |  Space/L4   |  L1  |Left|Down| Up |Right|
	* `-------------------------------------------------------------------------'
	*/
	[0] = LAYOUT(
        KC_ESC, TD(TD_SCLN), TD(TD_COMM), KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC, 
        L3_TAB, LSFT_T(KC_A), CTL_T(KC_O), ALT_T(KC_E), GUI_T(KC_U), KC_I, KC_D, RGUI_T(KC_H), RALT_T(KC_T), RCTL_T(KC_N), RSFT_T(KC_S), TD(TD_MINS), 
        // TD(TD_SFT), TD(TD_QUOT), KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_SFTENT, 
        OSM(MOD_LSFT), TD(TD_QUOT), KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_SFTENT, 
        KC_LCTL, KC_LALT, KC_LGUI, HYP5, MO(2), L4_SPACE, MO(1), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),



	/* FN Layer 1
	* ,-------------------------------------------------------------------------.
	* | TOG_OS |  F1  | F2 |  F3  | F4 | F5 | F6 | F7 | F8 | F9 | F10 |  Bspace |
	* |-------------------------------------------------------------------------+
	* | Capsl | Play | Prv | Next |       | Gui+L | Gui+/ | @ |  !  |  ?  |  /  |
	* |-------------------------------------------------------------------------+
	* |        | Mute | Vol - | Vol + |    |    | Copy | Paste | Cut | Undo |   |
	* |-------------------------------------------------------------------------+
	* |      |LEDtg|LED+|LED-|      |           |       | Home| PgDn| PgUp| End |
	* `-------------------------------------------------------------------------'
	*/
	[1] = LAYOUT(
        TOG_OS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, 
        KC_CAPS, KC_MPLY, KC_MRWD, KC_MFFD, KC_F4, KC_NO, KC_LOCK, KC_COMMENT, KC_AT, KC_EXLM, KC_QUES, KC_PSLS, 
        KC_TRNS, KC_MUTING, KC_VDOWN, KC_VUP, KC_NO, KC_NO, KC_NO, UC_COPY, UC_PASTE, UC_CUT, UC_UNDO, KC_TRNS, 
        KC_TRNS, RGB_TOG, RGB_RMOD, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END),



	/* FN Layer 2
	* ,-------------------------------------------------------------------------.
	* |      |  %  |  &  |  #  |  ~  |     |  -  |  $  |  |  |  `  |  |  |Delete|
	* |-------------------------------------------------------------------------+
	* |       |  [  |  {  |  (  |  =  |     |  +  |  ^  |  )  |  }  |  ]  |  \  |
	* |-------------------------------------------------------------------------+
	* |  F9  | F10 | F11 | F12 | F13 | F14 | F15 | F16 | F17 | F18 | F19  | F20 |
	* |-------------------------------------------------------------------------+
	* |     |     |     |     |      |          |       | Home| PgDn| PgUp| End |
	* `-------------------------------------------------------------------------'
	*/
	[2] = LAYOUT(
        KC_ESC, KC_PERC, KC_AMPR, KC_HASH, KC_TILD, KC_NO, KC_PMNS, KC_DLR, KC_PIPE, KC_GRV, KC_NO, KC_DEL, 
        KC_TRNS, KC_LBRC, KC_LCBR, KC_LPRN, KC_EQL, KC_NO, KC_PPLS, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_BSLS, 
        KC_F9, KC_F10, KC_F11, KC_F12, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END),



	/* FN Layer 3
	* ,-------------------------------------------------------------------------.
	* | Esc |  :  |  ,  |  =  |     |     |     |  7  |  8  |   9  |     |Bspace|
	* |-------------------------------------------------------------------------+
	* |      |     |  +  |  -  |     |     |  .  |  4  |  5  |  6  |   *  |  /  |
	* |-------------------------------------------------------------------------+
	* |        |     |     |     |    |    |  0  |  1  |  2  |  3  |    | En/Sh |
	* |-------------------------------------------------------------------------+
	* |      |     |    |    |     |          |      | Left | Down | Up | Right |
	* `-------------------------------------------------------------------------'
	*/
	[3] = LAYOUT(
		KC_ESC, KC_COLN, KC_COMM, KC_EQL, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_NO, KC_BSPC, 
		KC_TRNS, KC_NO, KC_PMNS, KC_PPLS, KC_NO, KC_NO, KC_PDOT, KC_P4, KC_P5, KC_P6, KC_PAST, KC_PSLS, 
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_P0, KC_P1, KC_P2, KC_P3, KC_NO, KC_SFTENT, 
		KC_TRNS, RGB_TOG, RGB_RMOD, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),


    /* FN Layer 4
  * ,-------------------------------------------------------------------------.
  * | Esc |ScrlDn|ScrlUp|Mous1|Mous2|    |   |MousL|MousD|MousU|MousR| Bspace |
  * |-------------------------------------------------------------------------+
  * | Hyp | Shift | Ctrl | Alt | Gui |   |   | Left | Down | Up | Right | Del |
  * |-------------------------------------------------------------------------+
  * |        | Undo | Cut | Copy | Paste |     |     |Home|PgDn|PgUp|End| Ent |
  * |-------------------------------------------------------------------------+
  * |     |    |    |    |       |            |       |      |     |    |     |
  * `-------------------------------------------------------------------------'
  */
  [4] = LAYOUT(
    KC_ESC, KC_NO, KC_SCRL_DWN, KC_SCRL_UP, KC_BTN1, KC_BTN2, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BSPC, 
    KC_HYP, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_DEL, 
    KC_TRNS, UC_UNDO, UC_CUT, UC_COPY, UC_PASTE, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_ENT, 
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO),


  /* FN Layer 5
  * ,-------------------------------------------------------------------------.
  * |     |     |     |     |     |     |     |     | Left |Right|     |      |
  * |-------------------------------------------------------------------------+
  * |      |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |      |
  * |-------------------------------------------------------------------------+
  * |       |     |     |     |     |     |     |     |     |     |     |     |
  * |-------------------------------------------------------------------------+
  * |     |    |    |    |        |              |        |    |    |    |    |
  * `-------------------------------------------------------------------------'
  */
  [5] = LAYOUT(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_LEFT, KC_RGHT, KC_NO, KC_NO, 
    KC_NO, KC_P1, KC_P2, KC_P3, KC_P4, KC_P5, KC_P6, KC_P7, KC_P8, KC_P9, KC_P0, KC_NO, 
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),  
};



//Custom functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) { // process on key down
  	  case TOG_OS:
        	is_mac = ! is_mac;
        	return false;

      case UC_COPY:
      	if (is_mac) {
      		SEND_STRING(SS_LGUI("c"));
      	}
      	else {
      		SEND_STRING(SS_LCTRL("c"));
      	}
      	return false;

      case UC_PASTE:
      	if (is_mac) {
      		SEND_STRING(SS_LGUI("v"));
      	}
      	else {
      		SEND_STRING(SS_LCTRL("v"));
      	}
      	return false;

      case UC_CUT:
      	if (is_mac) {
      		SEND_STRING(SS_LGUI("x"));
      	}
      	else {
      		SEND_STRING(SS_LCTRL("x"));
      	}
      	return false;

      case UC_UNDO:
      	if (is_mac) {
      		SEND_STRING(SS_LGUI("z"));
      	}
      	else {
      		SEND_STRING(SS_LCTRL("z"));
      	}
      	return false;

      case KC_COMMENT:
      	if (is_mac) {
      		SEND_STRING(SS_LGUI("/"));
      	}
      	else {
      		SEND_STRING(SS_LCTRL("/"));
      	}
      	return false;

      case KC_MUTING:
      	if (is_mac) {
      		SEND_STRING(SS_TAP(X__MUTE));
      	}
      	else {
      		tap_code(KC_MUTE);
      	}
      	return false;

      case KC_VUP:
      	if (is_mac) {
      		SEND_STRING(SS_TAP(X__VOLUP));
      	}
        	else {
        		tap_code(KC_VOLU);
        	}
        	return false;

        case KC_VDOWN:
        	if (is_mac) {
        		SEND_STRING(SS_TAP(X__VOLDOWN));
        	}
        	else {
        		tap_code(KC_VOLD);
        	}
        	return false;

        case KC_SCRL_UP:
          if (is_mac) {
            register_code(KC_WH_D);
          }
          else {
            register_code(KC_WH_U);
          }
          return false;

        case KC_SCRL_DWN:
          if (is_mac) {
            register_code(KC_WH_U);
          }
          else {
            register_code(KC_WH_D);
          }
          return false;
    }
  } else {  // process on key up
    switch(keycode) {
      case KC_SCRL_UP:
        if (is_mac) {
          unregister_code(KC_WH_D);
        }
        else {
          unregister_code(KC_WH_U);
        }
        return false;

      case KC_SCRL_DWN:
        if (is_mac) {
          unregister_code(KC_WH_U);
        }
        else {
          unregister_code(KC_WH_D);
        }
        return false;
    }
  }

  if (mod_shift) {
    mod_shift = false;
    return false;
  } else {
    return true;
  }
};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicative that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//******instantiate an instance of 'tap' for the 'sft' tap dance.******//
static tap sft_tap_state = {
  .is_press_action = true,
  .state = 0
};

void sft_finished (qk_tap_dance_state_t *state, void *user_data) {
  sft_tap_state.state = cur_dance(state);
  switch (sft_tap_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); tap_code(state->interrupting_keycode); break;
    case SINGLE_HOLD: register_code(KC_LSFT); break;
    // case DOUBLE_TAP: register_code(KC_ESC); break;
    // case DOUBLE_HOLD: register_code(KC_LALT); break;
    // case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void sft_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (sft_tap_state.state) {
    case SINGLE_TAP: clear_keyboard(); mod_shift = true; break;
    case SINGLE_HOLD: unregister_code(KC_LSFT); break;
    // case DOUBLE_TAP: unregister_code(KC_ESC); break;
    // case DOUBLE_HOLD: unregister_code(KC_LALT);
    // case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  sft_tap_state.state = 0;
}
//****************************************************************************//

//******instantiate an instance of 'tap' for the 'layer swap' tap dance.******//
static tap layer_tap_state = {
  .is_press_action = true,
  .state = 0
};

void tap_finished (qk_tap_dance_state_t *state, void *user_data) {
  layer_tap_state.state = cur_dance(state);
  switch (layer_tap_state.state) {
    case SINGLE_HOLD: layer_off(0); layer_on(2); break;
    case DOUBLE_HOLD: layer_off(0); layer_on(5); break;
  }
}

void tap_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (layer_tap_state.state) {
    case SINGLE_HOLD: layer_off(2); layer_on(0); break;
    case DOUBLE_HOLD: layer_off(5); layer_on(0); break;
  }
  layer_tap_state.state = 0;
}
//****************************************************************************//

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for semicolon, twice for colon
  [TD_SCLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),

  //Tap once for comma, twice for <
  [TD_COMM] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_LT),

  //Tap once for period, twice for >
  [TD_DOT] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_GT),

  //Tap once for hyphen/minuse, twice for underscore
  [TD_MINS] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),

  //Tap once for single quote, twice for double quote
  [TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQUO),

  // Tap dance for shift
  [TD_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_finished, sft_reset),

  // Tap dance for layer 2/layer 5
  [TD_LAYER_SWAP] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, tap_finished, tap_reset)
};