/* Copyright 2015-2017 Jack Humbert
 *
 * Layout created by John Garrett 2019 <https://github.com/JHGarrett>
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
#include "muse.h"
#include "eeconfig.h"
#include "action_layer.h"


void tap(uint16_t keycode){
    register_code(keycode);
    unregister_code(keycode);
};

enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
   _MOUSE,
  _NUMPAD,
  _SYMB,
  _LOWER,
  _RAISE,
  _ADJUST
 

};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  BACKLIT,
  SPC_MOU,
  ARROW,
  COPY_ALL,
  SEL_CPY,
  NUMPAD,
  SYMB,
  TRIPEQL,
  NOTEQL,
  DISFACE,
  SHRUG,
  TPUT,
  TFLIP,
  CC_PRN,
  CC_BRC,
  CC_CBR,
  DBL_AND
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | BSPC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | BKSP |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | bksp |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | caps| alt   | gui  | ctl  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,  \
  KC_BSPC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_SFTENT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,  \
  KC_LCTL, KC_LALT, KC_LGUI, KC_LCTL, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),
/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | `ESC |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   \  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | caps | alt | gui  | ctrl  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_preonic_1x2uC( \
  KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
  KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
  KC_SFTENT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_SFTENT,  \
  KC_CAPS, KC_LALT, KC_LGUI, KC_LCTL, LOWER,       KC_SPC,       RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

 /* Numpad
  * ,-----------------------------------------------------------------------------------.
  * | Esc  |      |      | PgDn | PgUp | Home |  End  |      |   /  |   *  |   -  | Del  |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Tab  |      |  Up  |      |      |      |      |   7  |   8  |   9  |   +  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Bksp | Left | Down | Right|      |      |      |   4  |   5  |   6  |      |  "   |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shift|      |      |      |      |      |   ,  |   1  |   2  |   3  |      | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | CAPS | Ctrl | Alt  | GUI  |Lower |    Space    |Raise |   0  |   .  | Ctrl | Shift|
  * `-----------------------------------------------------------------------------------'
  */
  [_NUMPAD] = LAYOUT_preonic_1x2uC( \
    KC_ESC,  _______, _______, KC_PGDN, KC_PGUP, KC_END,  KC_HOME, _______, KC_PSLS, KC_PAST, KC_PMNS, KC_DEL,  \
    KC_TAB,  _______, KC_UP,   _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_BSPC, \
    KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   _______, KC_QUOT, \
    KC_SFTENT, _______, _______, _______, _______, _______, KC_COMM, KC_P1,   KC_P2,   KC_P3,   _______, KC_SFTENT, \
    QWERTY, KC_LALT, KC_LGUI, KC_LCTL, LOWER,       KC_SPC,       RAISE,   KC_P0,   KC_PDOT, KC_RCTL, KC_RSFT  \
  ),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | BKSP |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | bksp |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | caps | alt  |gui   | ctl  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,  \
  KC_BSPC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_SFTENT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,  \
  KC_LCTL, KC_LALT, KC_LGUI, KC_LCTL, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Symbol
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   |  |  +   |  <   |  >   |  #   |   ~  |   (  |   )  |   \  |   :  | BSPC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   !  |  -   |  =   |  %   |  @   |   _  |   {  |   }  |   /  |   ?  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |SFENT |   *  |  &   |  /   |  $   |  ^   |   |  |   [  |   ]  |      |      | SFENT|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | exit | alt  |gui   | ctl  |Lower |  §  Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMB] = LAYOUT_preonic_1x2uC( \
	KC_F1,			KC_F2,		KC_F3,			KC_F4,			KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,  \
	_______,		KC_PIPE,	KC_PLUS,		KC_LABK,		KC_RABK,	KC_HASH,	KC_TILD,	KC_LPRN,	KC_RPRN,	KC_BSLS,	KC_COLN,	KC_BSPC, \
	KC_BSPC,		KC_EXLM,	KC_MINS,		KC_EQL,			KC_PERC,	KC_AT,		KC_UNDS,	KC_LCBR,	KC_RCBR,	KC_SLSH,	KC_QUES,	KC_QUOT, \
	KC_SFTENT,	KC_ASTR,	KC_AMPR,		KC_SLSH,		KC_DLR,		KC_CIRC,	KC_PIPE,	KC_LBRC,	KC_RBRC,	_______,	_______,	KC_SFTENT, \
  QWERTY, KC_LALT, KC_LGUI, KC_LCTL, LOWER,       KC_SPC,       RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | BSPC  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   } |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  |  |  ±    |   [   |   ] |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
  KC_BSPC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),KC_LBRC, KC_RBRC, KC_ENT, \
  KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TAB  |      |  UP  | PGUP |CCPRN |   (  |   )  |  === |  !=  |   <  |   >  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | BSPC | LEFT | DOWN | RIGHT|CCCBR |   {  |   }  |   _  |   =  |   @  |  &&  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |SF/ENT|      |      |PGDOWN|CCBRC |   [  |   ]  |   -  |   +  |   \  |   /  |  ENT |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ARROW| COPY |WRDDEL|WRDBKS|      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_TAB, _______, KC_UP,   KC_PGUP, CC_PRN,  KC_LPRN, KC_RPRN, TRIPEQL, NOTEQL, KC_LABK, KC_RABK, KC_DEL,  \
  KC_BSPC,  KC_LEFT,   KC_DOWN,   KC_RIGHT,   CC_CBR,   KC_LCBR,   KC_RCBR,   KC_UNDS, KC_EQL,  KC_AT, DBL_AND, KC_PIPE, \
  KC_SFTENT, _______,   _______,   KC_PGDN,   CC_BRC,  KC_LBRC,  KC_RBRC,  KC_MINS, KC_PLUS, KC_BSLASH, KC_SLSH, KC_ENT, \
  ARROW, COPY_ALL, LCTL(KC_DEL), LCTL(KC_BSPC), _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),


/* Adjust (Lower + Raise)   
 * ,-----------------------------------------------------------------------------------.
 * |      |QWERTY|COLEMA|DVORAK|MOUSE |NUMPAD| SYMB |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |TERMON|TOFF  |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|  calc| tr/bk|tr/fwd|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |DISFAC|TFLIP |TPUT  |SHRUG |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  _______, QWERTY, COLEMAK, DVORAK, SPC_MOU, NUMPAD, SYMB, _______, _______, _______, _______, _______,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______,  _______, _______,  _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  KC_CALC, KC_MRWD, KC_MFFD, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),
/* Mouse 
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | WHL_U|Mclick|      | HU_D | HU_I | LCTL | MS_U | WHL_U|      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      | WHL_D|Rclick|Lclick| SA_D | SA_I | MS_L | MS_D | MS_R |      | ACL0 |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      | VA_D | VA_I | WHL_D| WHL_L| WHL_R|      | ACL1 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | ACL2 |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_preonic_1x2uC(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, _______, KC_WH_U, KC_BTN3, _______, RGB_HUD, RGB_HUI, KC_LCTL, KC_MS_U, KC_WH_U, _______, KC_DEL,  \
  _______, _______, KC_WH_D, KC_BTN2, KC_BTN1, RGB_SAD, RGB_SAI, KC_MS_L, KC_MS_D, KC_MS_R, _______, KC_ACL0, \
  _______,_______, _______, SEL_CPY, _______, RGB_VAD, RGB_VAI, KC_WH_D, KC_WH_L, KC_WH_R, _______, KC_ACL1, \
  QWERTY, _______, _______, _______, LOWER, _______,  RAISE, _______, _______, _______, KC_ACL2  \
  )

};






bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
           case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
       case SPC_MOU:
         if (record->event.pressed) {
            set_single_persistent_default_layer(_MOUSE);
          }
          return false;
          break;
          case NUMPAD:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_NUMPAD);
          }
          return false;
          break;
           case SYMB:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_SYMB);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;

          
// custom stuff
        
           case SEL_CPY:
            // Select word under cursor and copy. Double mouse click then ctrl+c
            if (record->event.pressed) {
                tap_code16(KC_BTN1);
                tap_code16(KC_BTN1);
                tap_code16(C(KC_C));
            }
         case COPY_ALL:
            if (record->event.pressed) {
                // Selects all and text and copy
                SEND_STRING(SS_LCTRL("ac"));
            }
            return false;
             case ARROW:
            if (record->event.pressed){
                SEND_STRING("=>");
            } 
            return false;

             case TRIPEQL:
            if (record->event.pressed){
                SEND_STRING("===");
            } 
            return false;

             case NOTEQL:
            if (record->event.pressed){
                SEND_STRING("!=");
            } 
            return false;
            
            case DBL_AND:
            if (record->event.pressed){
                SEND_STRING("&&");
            } 
            return false;

            case CC_PRN:
            if (record->event.pressed){
            SEND_STRING("()"SS_TAP(X_LEFT));
            } 
            return false;
            
            case CC_BRC:
            if (record->event.pressed){
            SEND_STRING("[]"SS_TAP(X_LEFT));
            } 
            return false;
            
            case CC_CBR:
            if (record->event.pressed){
            SEND_STRING("{}"SS_TAP(X_LEFT));
            } 
            return false;

      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
