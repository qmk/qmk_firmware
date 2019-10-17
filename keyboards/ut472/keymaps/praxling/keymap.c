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

// Custom Layer keycodes
#define L3_TAB LT(3, KC_TAB)
#define L4_SPACE LT(4, KC_SPC)

enum custom_keycodes {
  TOG_OS = SAFE_RANGE,

  // shortcuts
  UC_LOCK,
  UC_COPY,
  UC_PASTE,
  UC_CUT,
  UC_UNDO,
  UC_COMMENT,

  // mouse
  UC_SCRL_UP,
  UC_SCRL_DWN
};

//Tap Dance Declarations
enum tapdance_id {
  TD_SCLN = 0,
  TD_COMM,
  TD_DOT,
  TD_MINS,
  TD_QUOT
};

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
    L3_TAB, SFT_T(KC_A), CTL_T(KC_O), ALT_T(KC_E), GUI_T(KC_U), KC_I, KC_D, GUI_T(KC_H), ALT_T(KC_T), CTL_T(KC_N), SFT_T(KC_S), TD(TD_MINS), 
    OSM(MOD_LSFT), TD(TD_QUOT), KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_SFTENT, 
    KC_LCTL, KC_LALT, KC_LGUI, MO(5), MO(2), L4_SPACE, MO(1), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),



	/* FN Layer 1
	* ,-------------------------------------------------------------------------.
	* |     |  F1  | F2 |  F3  | F4 | F5 | F6 | F7 | F8 | F9 | F10 |   Bspace   |
	* |-------------------------------------------------------------------------+
	* | Capsl | Play | Prv | Next |       | Gui+L | Gui+/ | @ |  !  |  ?  |  /  |
	* |-------------------------------------------------------------------------+
	* |        | Mute | Vol - | Vol + |    |    | Copy | Paste | Cut | Undo |   |
	* |-------------------------------------------------------------------------+
	* |      |LEDtg|LED+|LED-|      |           |       | Home| PgDn| PgUp| End |
	* `-------------------------------------------------------------------------'
	*/
	[1] = LAYOUT(
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, 
    KC_CAPS, KC_MPLY, KC_MRWD, KC_MFFD, KC_NO, KC_NO, UC_LOCK, UC_COMMENT, KC_AT, KC_EXLM, KC_QUES, KC_PSLS, 
    KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, UC_COPY, UC_PASTE, UC_CUT, UC_UNDO, KC_TRNS, 
    // KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, G(KC_C), G(KC_V), G(KC_X), G(KC_Z), KC_TRNS,  
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
	* |      |     |  +  |  -  |     |     |     |  4  |  5  |  6  |   *  |  /  |
	* |-------------------------------------------------------------------------+
	* |        |     |     |     |    |    |  .  |  1  |  2  |  3  |    | En/Sh |
	* |-------------------------------------------------------------------------+
	* |      |     |    |    |     |          |   0  | Left | Down | Up | Right |
	* `-------------------------------------------------------------------------'
	*/
	[3] = LAYOUT(
		KC_ESC, KC_COLN, KC_COMM, KC_EQL, KC_NO, KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_NO, KC_BSPC, 
		KC_TRNS, KC_NO, KC_PMNS, KC_PPLS, KC_NO, KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_PAST, KC_PSLS, 
		KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PDOT, KC_P1, KC_P2, KC_P3, KC_NO, KC_SFTENT, 
		KC_TRNS, RGB_TOG, RGB_RMOD, RGB_MOD, KC_TRNS, KC_TRNS, KC_P0, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),


    /* FN Layer 4
  * ,-------------------------------------------------------------------------.
  * | Esc |ScrlDn|ScrlUp|Mous1|Mous2|    |   |MousL|MousD|MousU|MousR| Bspace |
  * |-------------------------------------------------------------------------+
  * | Hyp | Shift | Ctrl | Alt | Gui |   |   | Left | Down | Up | Right | Del |
  * |-------------------------------------------------------------------------+
  * | Reset | TOG_OS |    |    |    |    |    |    |Home|PgDn|PgUp| End | Ent |
  * |-------------------------------------------------------------------------+
  * |     |    |    |    |       |            |       |      |     |    |     |
  * `-------------------------------------------------------------------------'
  */
  [4] = LAYOUT(
    KC_ESC, KC_NO, UC_SCRL_DWN, UC_SCRL_UP, KC_BTN1, KC_BTN2, KC_NO, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BSPC, 
    KC_TRNS, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_DEL,  
    RESET, CG_TOGG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_ENT, 
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO),


  /* FN Layer 5 (for switching virtual desktops)
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
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, HYPR(KC_LEFT), HYPR(KC_RGHT), KC_NO, KC_NO, 
    KC_NO, HYPR(KC_P1), HYPR(KC_P2), HYPR(KC_P3), HYPR(KC_P4), HYPR(KC_P5), HYPR(KC_P6), HYPR(KC_P7), HYPR(KC_P8), HYPR(KC_P9), HYPR(KC_P0), HYPR(KC_NO), 
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),  
};



//Custom functions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    // case TOG_OS:
    case CG_TOGG:
      if (record->event.pressed) {
        curr_os_is_mac = keymap_config.swap_lctl_lgui;
      }
      break;

    case UC_LOCK:
      if (record->event.pressed) {
        if (curr_os_is_mac) {
          SEND_STRING(SS_LCTRL(SS_LGUI("q")));
        } else {
          SEND_STRING(SS_LGUI("l"));
        }
      }
      return false;
      break;      

    case UC_COPY:
      if (record->event.pressed) {
        register_mods(mod_config(MOD_BIT(KC_LGUI)));
        tap_code(KC_C);
        unregister_mods(mod_config(MOD_BIT(KC_LGUI)));
      }
      return false;
      break;

    case UC_PASTE:
      if (record->event.pressed) {
        register_mods(mod_config(MOD_BIT(KC_LGUI)));
        tap_code(KC_V);
        unregister_mods(mod_config(MOD_BIT(KC_LGUI)));
      }
      return false;
      break;

    case UC_CUT:
      if (record->event.pressed) {
        register_mods(mod_config(MOD_BIT(KC_LGUI)));
        tap_code(KC_X);
        unregister_mods(mod_config(MOD_BIT(KC_LGUI)));
      }
      return false;
      break;

    case UC_UNDO:
      if (record->event.pressed) {
        register_mods(mod_config(MOD_BIT(KC_LGUI)));
        tap_code(KC_Z);
        unregister_mods(mod_config(MOD_BIT(KC_LGUI)));
      }
      return false;
      break;

    case UC_COMMENT:
      if (record->event.pressed) {
        register_mods(mod_config(MOD_BIT(KC_LGUI)));
        tap_code(KC_PSLS);
        unregister_mods(mod_config(MOD_BIT(KC_LGUI)));
      }
      return false;
      break;      

    case UC_SCRL_UP:
      if (record->event.pressed) {
        if (curr_os_is_mac) {
          register_code(KC_WH_D);
        } else {
          register_code(KC_WH_U);
        }
      } else {
        if (curr_os_is_mac) {
          unregister_code(KC_WH_D);
        } else {
          unregister_code(KC_WH_U);
        }            
      }
      return false;
      break;

    case UC_SCRL_DWN:
      if (record->event.pressed) {
        if (curr_os_is_mac) {
          register_code(KC_WH_U);
        } else {
          register_code(KC_WH_D);
        }
      } else {
        if (curr_os_is_mac) {
          unregister_code(KC_WH_U);
        } else {
          unregister_code(KC_WH_D);
        }            
      }
      return false;
      break;
    }
  return true;
};

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
};