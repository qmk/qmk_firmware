/* Copyright 2019 Stefano Marago'
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


/*
 * The 25% SuperMicro keyboard: a pure - full features - "Alpha 26" keymap on Gherkin, compatible also with 28 and 30 keys layouts
 * See https://github.com/stevexyz/qmk_firmware/blob/master/keyboards/40percentclub/gherkin/keymaps/stevexyz/readme.md for more information
 */


#include QMK_KEYBOARD_H

enum layers {
  LAYER_HOME, // home base layer
  LAYER_FUNC, // function keys and cursors
  LAYER_NUMSYM, // numbers and other characters
  LAYER_SYST, // media, mouse and other system keys
  LAYER_ARROWPAD,
  LAYER_NUMPAD,
  LAYER_MEDIAPAD,
};

enum custom_keycodes {
  CK_TRIPLEZERO = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * LEGEND:
 *
 * ,--------------------------------.
 * |     Top row: shifted character |
 * | Central row: standard char     |
 * |  Bottom row: hold modifier     |
 * `--------------------------------'
 *
 *  "____" means free to be assigned
 *
 */

/* Qwerty Home Layer
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |
 * | ____ | ____ | ____ | ____ | ____ | FnNav|NumSym|  Alt | Ctrl | Shift|
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | Enter|
 * | Shift| FnNav|NumSym| AltGr| OSkey| OSkey| AltGr| FnNav|NumSym| Shift|
 * '------+------+------+------+------+------|------+------+------+------'
 *        |      |      |      |      |      |      |      |      |       
 *        |   Z  |   X  |   C  |   V  |   B  |   N  |   M  | Space|       
 *        | Ctrl |  Alt | FnNav|NumSym| Shift|  Alt | Ctrl | Shift|       
 *        '-------------------------------------------------------'       
 */
  [LAYER_HOME] = LAYOUT_ortho_3x10(
    LT(LAYER_ARROWPAD, KC_Q), LT(LAYER_NUMPAD, KC_W), LT(LAYER_MEDIAPAD, KC_E), KC_R, KC_T, LT(LAYER_FUNC, KC_Y), LT(LAYER_NUMSYM, KC_U), MT(MOD_LALT, KC_I), MT(MOD_RCTL, KC_O), MT(MOD_RSFT, KC_P),
    MT(MOD_LSFT, KC_A), LT(LAYER_FUNC, KC_S), LT(LAYER_NUMSYM, KC_D), MT(MOD_RALT, KC_F), MT(MOD_LGUI, KC_G), MT(MOD_RGUI, KC_H), MT(MOD_RALT, KC_J), LT(LAYER_FUNC, KC_K), LT(LAYER_NUMSYM, KC_L), MT(MOD_RSFT, KC_ENT),
    KC_DOWN, MT(MOD_LCTL, KC_Z), MT(MOD_LALT, KC_X), LT(LAYER_FUNC, KC_C), LT(LAYER_NUMSYM, KC_V), MT(MOD_LSFT, KC_B), MT(MOD_LALT, KC_N), MT(MOD_RCTL, KC_M), MT(MOD_RSFT, KC_SPC), KC_BSPC
  ),

/* Function and Navigation Layer
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |
 * | ____ | ____ | ____ | ____ | ____ | ____ |SysLay|  Alt | Ctrl | Shift|
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |  ESC | Home | PgDn | PgUp |  End | Left | Down |  Up  | Right|Backsp|
 * | Shift| ____ |SysLay| AltGr| OSkey| OSkey| AltGr| ____ |SysLay| Shift|
 * '------+------+------+------+------+------|------+------+------+------'
 *        |      |      |      |      |      |      |      |      |       
 *        |  F11 |  F12 |      | Space|PrnScr|ScrLck|Pause |Backsp|       
 *        | Ctrl |  Alt | ____ |SysLay| Shift|  Alt | Ctrl | Shift|       
 *        '-------------------------------------------------------'       
 */
  [LAYER_FUNC] = LAYOUT_ortho_3x10(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, LT(LAYER_SYST, KC_F7), MT(MOD_LALT, KC_F8), MT(MOD_RCTL,KC_F9), MT(MOD_RSFT, KC_F10),
    MT(MOD_LSFT, KC_ESC), KC_HOME, LT(LAYER_SYST, KC_PGDN), MT(MOD_RALT, KC_PGUP), MT(MOD_LGUI, KC_END), MT(MOD_RGUI, KC_LEFT), MT(MOD_RALT, KC_DOWN), KC_UP, LT(LAYER_SYST, KC_RGHT), MT(MOD_RSFT, KC_BSPC),
    KC_DOWN, MT(KC_LCTL, KC_F11), MT(KC_LALT, KC_F12), KC_NO, LT(LAYER_SYST, KC_SPACE), MT(KC_LSFT, KC_PSCR), MT(KC_LALT, KC_SCRL), MT(KC_RCTL, KC_PAUS), MT(MOD_RSFT, KC_BSPC), KC_UP
  ),

/* Number and Symbols Layer
 * ,---------------------------------------------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |
 * |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |
 * | ____ | ____ | ____ | ____ | ____ |SysLay| ____ |  Alt | Ctrl | Shift|
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |   ~  |   _  |   +  |   {  |   }  |  |   |   :  |   "  |      |
 * |  TAB |   `  |   -  |   =  |   [  |   ]  |  \   |   ;  |   '  | Del  |
 * | Shift|SysLay| ____ | AltGr| OSkey| OSkey| AltGr|SysLay| ____ | Shift|
 * ' -----+------+------+------+------+------|------+------+------+------'
 *        |      |      |      |      |   <  |   >  |   ?  |      |       
 *        |BackSp|  Del | Enter|      |   ,  |   .  |   /  | Enter|       
 *        | Ctrl |  Alt |SysLay| ____ | Shift|  Alt | Ctrl | Shift|       
 *        '-------------------------------------------------------'       
 */
  [LAYER_NUMSYM] = LAYOUT_ortho_3x10(
    KC_1, KC_2, KC_3, KC_4, KC_5, LT(LAYER_SYST, KC_6), KC_7, MT(MOD_LALT, KC_8), MT(MOD_RCTL,KC_9), MT(MOD_RSFT, KC_0),
    MT(MOD_LSFT, KC_TAB), LT(LAYER_SYST, KC_GRV), KC_MINS, MT(MOD_RALT, KC_EQL), MT(MOD_LGUI, KC_LBRC), MT(MOD_RGUI, KC_RBRC), MT(MOD_RALT, KC_BSLS), LT(LAYER_SYST, KC_SCLN), KC_QUOT, MT(MOD_RSFT, KC_DEL),
    KC_LEFT, MT(KC_LCTL, KC_BSPC), MT(KC_LALT, KC_DEL), LT(LAYER_SYST, KC_ENT), KC_NO, MT(MOD_LSFT, KC_COMM), MT(MOD_LALT, KC_DOT), MT(MOD_RCTL, KC_SLSH), MT(MOD_RSFT, KC_ENT), KC_RGHT
  ),

/* System Layer
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * | Play | Stop | Prev | Next |MsBtn1|MsLeft|MSDown| MsUp |MsRigh|MsBtn2|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | Shift|
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |Backsp| Mute | Vol- | Vol+ |MsWhlD| Left | Down |  Up  | Right|Backsp|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * '------+------+------+------+------+------|------+------+------+------'
 *        |      |      |      |      |      |      |      |      |       
 *        | ____ | ____ | Enter| Space| Mute | Vol- | Vol+ | Space|       
 *        | Ctrl |  Alt | ____ | ____ | Shift| Alt  | Ctrl | ____ |       
 *        '-------------------------------------------------------'       
 */
  [LAYER_SYST] = LAYOUT_ortho_3x10(
    KC_MPLY, KC_STOP, KC_MPRV, KC_MNXT, KC_MS_BTN1, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, MT(MOD_RSFT, KC_MS_BTN2),
    KC_BSPC, KC_DEL, KC_PGDN, KC_PGUP, KC_APP, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BSPC,
    KC_PGDN, MT(KC_LCTL, KC_CAPS), MT(KC_LALT, KC_INS), KC_ENT, KC_SPC, MT(MOD_RSFT, KC_MUTE), MT(MOD_LALT, KC_VOLD), MT(MOD_RCTL, KC_VOLU), KC_SPC, KC_PGUP
  ),

 /* ArrowPad (mod su Q)  /------mouse-------\ /-----cursor-------\
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |MsBtn1| MsUp |MsBtn2| Home |  Up  | PgUp |Backsp|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |MsLeft|MsDown|MsRigh| Left | Down | Right| Enter|
 * | Shift| ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * '------+------+------+------+------+------|------+------+------+------'
 *        |      |      |      |      |      |      |      |      |        
 *        |      |      |MsWhlU|MsDown|MsWhlD|  End | PgDn | PgDn |       
 *        | Ctrl |  Alt | ____ | ____ | ____ | ____ | ____ | ____ |       
 *        '-------------------------------------------------------'       
 */
  [LAYER_ARROWPAD] = LAYOUT_ortho_3x10(
    KC_NO, KC_NO, KC_NO, KC_MS_BTN1, KC_MS_UP, KC_MS_BTN2, KC_HOME, KC_UP, KC_PGUP, KC_BSPC, 
    KC_LSFT, KC_NO, KC_NO, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT, 
    XXXXXXX, KC_LCTL, KC_LALT, KC_MS_WH_UP, KC_MS_DOWN, KC_MS_WH_DOWN, KC_END, KC_PGDN, KC_PGDN, XXXXXXX 
  ),

/* NumPad (mod su W)
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |      |      |   3  |   *  |   -  |Backsp|   7  |   8  |   9  |  0   |
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |      |      |   /  |   =  |   +  |   .  |   4  |   5  |   6  | Enter|
 * | Shift| ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * '------+------+------+------+------+------|------+------+------+------'
 *        |      |      |      |      |      |      |      |      |       
 *        |      |      |      |  Tab |   ,  |   1  |   2  |   3  |       
 *        | Ctrl |  Alt | ____ | ____ | ____ | ____ | ____ | ____ |       
 *        '-------------------------------------------------------'       
 */
  [LAYER_NUMPAD] = LAYOUT_ortho_3x10(
    KC_NO, KC_NO, KC_3, KC_KP_ASTERISK, KC_KP_MINUS, KC_BSPC, KC_7, KC_8, KC_9, KC_0, 
    KC_LSFT, KC_NO, KC_KP_SLASH, KC_KP_EQUAL, KC_KP_PLUS, KC_DOT, KC_4, KC_5, KC_6, KC_ENT, 
    XXXXXXX, KC_LCTL, KC_LALT, KC_NO, KC_TAB, KC_COMM, KC_1, KC_2, KC_3, XXXXXXX 
  ),
 
 /* MediaPad (mod su E)
 * ,---------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |      |      |      |      | Vol+ |      |      |
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * |------+------+------+------+-------------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |
 * |      |      |      |      |      |      | Prev | Play | Next |      |
 * | Shift| ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * '------+------+------+------+------+------|------+------+------+------'
 *        |      |      |      |      |      |      |      |      |        
 *        |      |      |      |      |      | Mute | Vol- |      |       
 *        | Ctrl |  Alt | ____ | ____ | ____ | ____ | ____ | ____ |       
 *        '-------------------------------------------------------'       
 */
  [LAYER_MEDIAPAD] = LAYOUT_ortho_3x10(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_VOLU, KC_NO, KC_NO, 
    KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO, 
    XXXXXXX, KC_LCTL, KC_LALT, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_NO, XXXXXXX 
  ),  
    
};


void matrix_init_user(void) {
  // eeconfig_init(); // reset keyboard to a standard default state; useful when new releases messup with eeprom values
  // set num lock on at start (for numonly layer to work)
  if (!host_keyboard_led_state().num_lock) {
      tap_code(KC_NUM_LOCK);
  }
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CK_TRIPLEZERO:
      if (record->event.pressed) {
        SEND_STRING("000");
      } // else { when released }
      break;
  }
  return true;
};

void keyboard_pre_init_user(void) {
  // Set our LED pins as output
  setPinOutput(D5);
  setPinOutput(B0);
}

bool led_update_user(led_t led_state) {
    writePin(D5, !led_state.num_lock);
    writePin(B0, !led_state.caps_lock);
    return false; // prevent keyboard from processing state
}
