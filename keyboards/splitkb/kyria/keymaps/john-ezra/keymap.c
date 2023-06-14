/* Copyright 2021 John Ezra
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

enum kyria_layers {
  _HNTS,
  _GAME,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum kyria_keycodes {
  HNTS = SAFE_RANGE,
  ESC_NUM,
  LOWER,
  RAISE,
  MSS_CTL,
  CPY_PST,
  UNDO,
  FIND
};

#define HNTS DF(_HNTS)
#define GAME TG(_GAME)
#define NUMPAD TG(_NUMPAD)
#define MSS_CTL MT(MOD_LCTL, C(KC_UP))
#define BSP_CMD MT(MOD_LGUI, KC_BSPC)
#define TAB_CMD MT(MOD_LGUI, KC_TAB)
#define SFT_ENT MT(MOD_LSFT, KC_ENT)
#define ALT_ESC MT(MOD_LALT, KC_ESC)
#define ALT_TAB A(KC_TAB)
#define UNDO G(KC_Z)
#define FIND G(KC_F)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Default: HNTS
 *
 * ,-----------------------------------------------.                                  ,-----------------------------------------------.
 * |  Find |   Z   |   R   |   L   |   D   |   W   |                                  |   Y   |   P   |   U   |   X   |   Q   |  | \  |
 * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
 * |Cpy/Pst|   H   |   N   |   T   |   S   |   C   |                                  |   B   |   I   |   E   |   O   |   A   |  ` ~  |
 * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
 * |  Undo |   K   |   V   |   M   |   F   |   G   |  Esc  |MssnCtl|  |MssnCtl|  Esc  |   J   |  ; :  |  , <  |  . >  |  / ?  |  ' "  |
 * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
 *                         | Numpad| Enter | Lower | Space | BSPC  |  |  Tab  | Shift | Raise |  Del  | Caps  |
 *                         `---------------------------------------'  `---------------------------------------'
 */

[_HNTS] = LAYOUT(
       FIND,    KC_Z,    KC_R,    KC_L,    KC_D,    KC_W,                                         KC_Y,    KC_P,    KC_U,    KC_X,    KC_Q, KC_BSLS,
    CPY_PST,    KC_H,    KC_N,    KC_T,    KC_S,    KC_C,                                         KC_B,    KC_I,    KC_E,    KC_O,    KC_A,  KC_GRV,
       UNDO,    KC_K,    KC_V,    KC_M,    KC_F,    KC_G, ALT_ESC, MSS_CTL,   MSS_CTL, ALT_ESC,   KC_J, KC_SCLN, KC_COMM,  KC_DOT, KC_SLSH, KC_QUOT,
                                NUMPAD, SFT_ENT,   LOWER,  KC_SPC, BSP_CMD,   TAB_CMD, SFT_ENT,  RAISE,  KC_DEL, KC_CAPS
),

/*
 * Game: Gaming Layer
 *
 * ,-----------------------------------------------.                                  ,-----------------------------------------------.
 * |   0   |   Z   |   R   |   L   |   D   |   W   |                                  |   Y   |   P   |   U   |   X   |   Q   |  Esc  |
 * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
 * |   1   |   H   |   N   |   T   |   S   |   C   |                                  |   B   |   I   |   E   |   O   |   A   | Enter |
 * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
 * |   2   |   K   |   V   |   M   |   F   |   G   |   8   |   9   |  |Default|  Esc  |   J   |  ; :  |  , <  |  . >  |  / ?  |Alt+Tab|
 * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
 *                         |   3   |   4   |   5   |   6   |   7   |  |  Tab  | Shift | Raise |  Del  | Caps  |
 *                         `---------------------------------------'  `---------------------------------------'
 */

[_GAME] = LAYOUT(
       KC_0,    KC_Z,    KC_R,    KC_L,    KC_D,    KC_W,                                         KC_Y,    KC_P,    KC_U,    KC_X,    KC_Q,  KC_ESC,
       KC_1,    KC_H,    KC_N,    KC_T,    KC_S,    KC_C,                                         KC_B,    KC_I,    KC_E,    KC_O,    KC_A,  KC_ENT,
       KC_2,    KC_K,    KC_V,    KC_M,    KC_F,    KC_G,    KC_8,    KC_9,      GAME, ALT_ESC,   KC_J, KC_SCLN, KC_COMM,  KC_DOT, KC_SLSH, ALT_TAB,
                                  KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   TAB_CMD, SFT_ENT,  RAISE,  KC_DEL, KC_CAPS
),

/*
 * Numpad
 *
 * ,-----------------------------------------------.                                  ,-----------------------------------------------.
 * |   *   |   +   |   7   |   8   |   9   |   0   |                                  |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
 * |   /   |   -   |   4   |   5   |   6   |   (   |                                  |       | Left  |  Up   | Down  | Right |       |
 * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
 * |   =   |   .   |   1   |   2   |   3   |   )   |       |       |  |       |       |       |       |       |       |       |       |
 * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
 *                         |       |       |       |       |       |  |       |       |       |       |       |
 *                         `---------------------------------------'  `---------------------------------------'
 */

[_NUMPAD] = LAYOUT(
    KC_ASTR, KC_PLUS,    KC_7,    KC_8,    KC_9,    KC_0,                                      _______, _______, _______, _______, _______, _______,
    KC_SLSH, KC_MINS,    KC_4,    KC_5,    KC_6, KC_LPRN,                                      _______, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, _______,
     KC_EQL,  KC_DOT,    KC_1,    KC_2,    KC_3, KC_RPRN, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),

/*
 * Lower: Symbols & Media
 *
 * ,-----------------------------------------------.                                  ,-----------------------------------------------.
 * |  Tab  |   *   |   /   |   +   |   -   |   =   |                                  |   |   |   {   |   }   |   @   |   !   |   `   |
 * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
 * | Enter | Left  |  Up   | Down  | Right |       |                                  |   \   |   (   |   )   |   $   |   #   |   ~   |
 * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
 * |  Esc  | Vol-  | Vol+  | Prev  | Play  |  Next |       |       |  |       |       |   _   |   [   |   ]   |   ^   |   %   |   &   |
 * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
 *                         |       |       |       |       |       |  |       |       |       |       |       |
 *                         `---------------------------------------'  `---------------------------------------'
 */

[_LOWER] = LAYOUT(
    KC_TAB,  KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS,  KC_EQL,                                      KC_PIPE, KC_LCBR, KC_RCBR,   KC_AT, KC_EXLM,  KC_GRV,
    KC_ENT,  KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, _______,                                      KC_BSLS, KC_LPRN, KC_RPRN,  KC_DLR, KC_HASH, KC_TILD,
    KC_ESC,  KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______,  _______, _______, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, KC_PERC, KC_AMPR,
                               _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),

/*
 * Raise: Numbers
 *
 * ,-----------------------------------------------.                                  ,-----------------------------------------------.
 * |       |  F1   |  F2   |  F3   |  F4   |  F5   |                                  |   F6  |   F7  |   F8  |   F9  |  F10  |  F11  |
 * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
 * |       |   1   |   2   |   3   |   4   |   5   |                                  |   6   |   7   |   8   |   9   |   0   |  F12  |
 * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |  |       |       |       |  Left |   Up  |  Down | Right |  Esc  |
 * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
 *                         |       |       |       |       |       |  |       |       |       |       |       |
 *                         `---------------------------------------'  `---------------------------------------'
 */

[_RAISE] = LAYOUT(
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
    _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_F12,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT,  KC_ESC,
                               _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),

/*
 * Adjust: Function Keys & RGB
 *
 * ,-----------------------------------------------.                                  ,-----------------------------------------------.
 * | Reset |       |       |       |       |       |                                  |       |  NKRO |CG SWAP|       |       | HNTS  |
 * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
 * |       |  TOG  |  SAI  |  HUI  |  VAI  |  MOD  |                                  |       |Bright+|Bright-|       |       |       |
 * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
 * |       |       |  SAD  |  HUD  |  VAD  | RMOD  |       |       |  |       |       |       |       |       |       |       |       |
 * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
 *                         |       |       |       |       |       |  |       |       |       |       |       |
 *                         `---------------------------------------'  `---------------------------------------'
 */

[_ADJUST] = LAYOUT(
   QK_BOOT, _______, _______, _______, _______, _______,                                     _______, NK_TOGG, CG_TOGG, _______,    GAME,    HNTS,
   _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, KC_BRIU, KC_BRID, _______, _______, _______,
   _______, _______, RGB_SAD, RGB_HUD, RGB_VAD,RGB_RMOD,_______, _______,  _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
    case CPY_PST:  // Hold to Copy, Hold with GUI to Cut, Tap to Paste
      {
      static uint16_t copy_paste_timer;
        if (record->event.pressed) {
          copy_paste_timer = timer_read();
        } else {
           if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {
             if (get_mods() & MOD_MASK_GUI) {
               tap_code16(LGUI(KC_X));
             } else {
               tap_code16(LGUI(KC_C));
             }
           } else {
             tap_code16(LGUI(KC_V));
           }
        }
      }
      break;
    case MSS_CTL:
      if (record->event.pressed && record->tap.count) {
          tap_code16(C(KC_UP));
          return false;
      }
      break;
    case UNDO:  // Tap to Undo, Tap with GUI to Redo
      if (get_mods() & MOD_MASK_GUI) {
        if (record->event.pressed) {
          tap_code(KC_Y);
        }
        return false;
      }
      break;
    case FIND:  // Tap to Find, Tap with GUI to Select All
      if (get_mods() & MOD_MASK_GUI) {
        if (record->event.pressed) {
          tap_code(KC_A);
        }
        return false;
      }
      break;
    }
  return true;
};

const key_override_t ctrl_h = ko_make_basic(MOD_MASK_CTRL, KC_H, C(KC_LEFT)); //MocOS Desktop Navigation
const key_override_t ctrl_n = ko_make_basic(MOD_MASK_CTRL, KC_N, C(KC_UP));  //MocOS Desktop Navigation
const key_override_t ctrl_t = ko_make_basic(MOD_MASK_CTRL, KC_T, C(KC_DOWN));  //MocOS Desktop Navigation
const key_override_t ctrl_s = ko_make_basic(MOD_MASK_CTRL, KC_S, C(KC_RGHT));  //MocOS Desktop Navigation
const key_override_t bsp_del = ko_make_basic(MOD_MASK_SHIFT, BSP_CMD, KC_DEL);  //  Shift+Bksp sends Delete

const key_override_t **key_overrides = (const key_override_t *[]){
    &ctrl_h,
    &ctrl_n,
    &ctrl_t,
    &ctrl_s,
    &bsp_del,
    NULL
};
