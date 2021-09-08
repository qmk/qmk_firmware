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
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum kyria_keycodes {
  HNTS = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  CPY_PST
};

#define BSP_CMD MT(MOD_LGUI, KC_BSPC)
#define SFT_ENT MT(MOD_LSFT, KC_ENT)
#define NKRO MAGIC_TOGGLE_NKRO
#define OS_SWAP MAGIC_TOGGLE_CTL_GUI

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*
 * Default: HNTS
 *
 * ,-----------------------------------------------.                                  ,-----------------------------------------------.
 * |   `   |   Z   |   R   |   L   |   C   |   G   |                                  |   P   |   Y   |   J   |   X   |   Q   |  | \  |
 * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
 * |  Esc  |   H   |   N   |   T   |   S   |   D   |                                  |   U   |   I   |   E   |   A   |   O   |  Esc  |
 * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
 * |Cpy/Pst|   V   |   F   |   M   |   W   |   B   | Ctrl  |  Alt  |  |  Caps |  Del  |   K   |  ; :  |  , <  |  . >  |  / ?  |  ' "  |
 * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
 *                         |  Up   | Down  | Lower | Space | BSPC  |  |  Tab  | Shift | Raise |  Left | Right |
 *                         `---------------------------------------'  `---------------------------------------'
 */

[_HNTS] = LAYOUT(
     KC_GRV,    KC_Z,    KC_R,    KC_L,    KC_C,    KC_G,                                         KC_P,    KC_Y,    KC_J,    KC_X,    KC_Q, KC_BSLS,
     KC_ESC,    KC_H,    KC_N,    KC_T,    KC_S,    KC_D,                                         KC_U,    KC_I,    KC_E,    KC_A,    KC_O,  KC_ESC,
    CPY_PST,    KC_V,    KC_F,    KC_M,    KC_W,    KC_B, KC_LCTL, KC_LALT,  KC_CAPS,  KC_DEL,    KC_K, KC_SCLN, KC_COMM,  KC_DOT, KC_SLSH, KC_QUOT,
                                 KC_UP, KC_DOWN,   LOWER,  KC_SPC, BSP_CMD,   KC_TAB, SFT_ENT,   RAISE, KC_LEFT, KC_RGHT
),

/*
 * Default: QWERTY
 *
 * ,-----------------------------------------------.                                  ,-----------------------------------------------.
 * |   `   |   Q   |   W   |   E   |   R   |   T   |                                  |   Y   |   U   |   I   |   O   |   P   |  | \  |
 * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
 * |  Esc  |   A   |   S   |   D   |   F   |   G   |                                  |   H   |   J   |   K   |   L   |   ;   |  ' "  |
 * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
 * |Cpy/Pst|   Z   |   X   |   C   |   V   |   B   | Ctrl  |  Alt  |  |  Caps |  Del  |   N   |   M   |  , <  |  . >  |  / ?  |Cpy/Pst|
 * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
 *                         |  Up   | Down  | Lower | Space | BSPC  |  |  Tab  | Shift | Raise |  Left | Right |
 *                         `---------------------------------------'  `---------------------------------------'
 */

[_QWERTY] = LAYOUT(
     KC_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
     KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
    CPY_PST,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LCTL, KC_LALT,  KC_CAPS,  KC_DEL,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, CPY_PST,
                                 KC_UP, KC_DOWN,   LOWER,  KC_SPC, BSP_CMD,   KC_TAB, SFT_ENT,   RAISE, KC_LEFT, KC_RGHT
),

/*
 * Lower: Symbols
 *
 * ,-----------------------------------------------.                                  ,-----------------------------------------------.
 * |       |   !   |   @   |   {   |   }   |   |   |                                  |       |       |       |       |       |  | \  |
 * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
 * |       |   #   |   $   |   (   |   )   |   `   |                                  |   +   |   -   |   /   |   *   |   %   |  - _  |
 * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
 * |       |   %   |   ^   |   [   |   ]   |   ~   |       |       |  |       |       |   &   |   =   |  , <  |  . >  |  / ?  |  ' "  |
 * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
 *                         |       |       |       |       |       |  |       |       |       |       |       |
 *                         `---------------------------------------'  `---------------------------------------'
 */

[_LOWER] = LAYOUT(
    _______, KC_EXLM,   KC_AT, KC_LCBR, KC_RCBR, KC_PIPE,                                      _______, _______, _______, _______, _______, _______,
    _______, KC_HASH,  KC_DLR, KC_LPRN, KC_RPRN,  KC_GRV,                                      KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_MINS,
    KC_CAPS, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______,  _______, _______, KC_AMPR,  KC_EQL, KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
                               _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),

/*
 * Raise: Numbers & Media
 *
 * ,-----------------------------------------------.                                  ,-----------------------------------------------.
 * |       |   1   |   2   |   3   |   4   |   5   |                                  |   6   |   7   |   8   |   9   |   0   |       |
 * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
 * |       | Prev  | Play  | Next  | VolUp | Mute  |                                  |Bright+|  Left |  Down |  Up   | Right |       |
 * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       | VolDn |       |       |       |  |       |       |Bright-|       |       |       |       |       |
 * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
 *                         |       |       |       |       |       |  |       |       |       |       |       |
 *                         `---------------------------------------'  `---------------------------------------'
 */

[_RAISE] = LAYOUT(
    _______,    KC_1, 	 KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
    _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU, _______,                                      KC_BRIU, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______,
    _______, _______, _______, KC_MUTE, KC_VOLD, _______, _______, _______,  _______, _______, KC_BRID, _______, _______, _______, _______, _______,
                               _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),

 /*
  * Adjust: Function Keys & RGB
  *
  * ,-----------------------------------------------.                                  ,-----------------------------------------------.
  * |       |  F1   |  F2   |  F3   |  F4   |  F5   |                                  |   F6  |   F7  |   F8  |   F9  |  F10  |       |
  * |-------+-------+-------+-------+-------+-------|                                  |-------+-------+-------+-------+-------+-------|
  * |       |  TOG  |  SAI  |  HUI  |  VAI  |  MOD  |                                  |       |       |       |  F11  |  F12  |  NKRO |
  * |-------+-------+-------+-------+-------+-------+---------------.  ,---------------+-------+-------+-------+-------+-------+-------|
  * |       |       |  SAD  |  HUD  |  VAD  | RMOD  |       |       |  |       |       |       |       |       |       |       |       |
  * `-------+-------+-------+-------+-------+-------+-------+-------|  |-------+-------+-------+-------+-------+-----------------------'
  *                         |       |       |       |       |       |  |       |       |       |       |       |
  *                         `---------------------------------------'  `---------------------------------------'
  */

[_ADJUST] = LAYOUT(
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,    NKRO,
    _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______,  KC_F11,  KC_F12, OS_SWAP,
    _______, _______, RGB_SAD, RGB_HUD, RGB_VAD,RGB_RMOD,_______, _______,  _______, _______, _______, _______, _______, _______,  QWERTY,    HNTS,
                              _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case HNTS:  //Layer Control
          if (record->event.pressed) {
            set_single_persistent_default_layer(_HNTS);
          }
          return false;
          break;
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
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
        case CPY_PST:  // One key copy/paste
            {
                static uint16_t copy_paste_timer;
                if (record->event.pressed) {
                    copy_paste_timer = timer_read();
                } else {
                    if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                      register_mods(mod_config(MOD_LGUI));
                      tap_code(KC_C);
                      unregister_mods(mod_config(MOD_LGUI));
                    } else {  // Tap, paste
                      register_mods(mod_config(MOD_LGUI));
                      tap_code(KC_V);
                      unregister_mods(mod_config(MOD_LGUI));
                    }
                }
            }
            break;
      }
    return true;
};
