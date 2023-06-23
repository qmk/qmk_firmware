/* Copyright 2015-2018 Jack Humbert, Corey Kump
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

extern keymap_config_t keymap_config;

enum planck_layers {
  _COLEMAK,
  _QWERTY,
  _LOWER,
  _LEANDOWN,
  _RAISE,
  _WOBBLE,
  _PLOVER,
  _ADJUST
};

/* This include relies on the layer constants above and so must be declared after them */
#include "tapdance.c"

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  BACKLIT
};

/**
 * Custom Corvec Bindings
 *
 * Previously used but currently unused bindings are commented out.
 **/

// Activate the Wobble layer
#define KC_WOBL MO(_WOBBLE)
// Dual function with Raise
#define KC_RESC LT(_RAISE, KC_ESC)
// Dual functions with Lower
#define KC_LENT LT(_LOWER, KC_ENT)
#define KC_LQUT LT(_LEANDOWN, KC_QUOT)
// Dual functions with Shift
#define KC_SDEL MT(MOD_LSFT, KC_DEL)
#define KC_SAPP MT(MOD_LSFT, KC_APP)

/**
 * Functions taking advantage of tap dance:
 **/
// Tap once: quote. Hold: LEANDOWN layer. Tap twice: minus.
#define KC_TQTD TD(TD_QUOT_LEAN_MINS)
// Tap once: [. Hold: RALT. Tap twice: {
#define KC_TALT TD(TD_LBRC_RALT_LCBR)
// Tap once: ]. Hold: RGUI. Tap twice: }
#define KC_TGUI TD(TD_RBRC_RGUI_RCBR)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT_planck_grid(
  //-----+----+----+----+----+----+----+----+----+----+----+----
     KC_TAB , KC_Q  , KC_W  , KC_F  , KC_P  , KC_G  , KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN,KC_BSPC,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     KC_RESC, KC_A  , KC_R  , KC_S  , KC_T  , KC_D  , KC_H  , KC_N  , KC_E  , KC_I  , KC_O  ,KC_TQTD,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_K  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     KC_LCTL,KC_LGUI,KC_WOBL,KC_LALT,KC_LENT, KC_SPC, KC_SPC,RAISE,KC_SDEL,KC_TALT,KC_TGUI,KC_RCTL
  ),

  [_QWERTY] = LAYOUT_planck_grid(
  //-----+----+----+----+----+----+----+----+----+----+----+----
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSPC,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     KC_RESC, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  , KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,KC_TQTD,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     KC_LSFT, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     KC_LCTL,KC_LGUI,KC_WOBL,KC_LALT,KC_LENT, KC_SPC, KC_SPC,RAISE,KC_RALT,KC_SAPP,KC_RGUI,KC_RCTL
  ),

  [_LOWER] = LAYOUT_planck_grid(
     KC_GRV ,KC_EXLM, KC_AT ,KC_HASH, KC_DLR,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
     _______,KC_LPRN,KC_RPRN,KC_LBRC,KC_RBRC,XXXXXXX,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT,XXXXXXX,KC_MINS,
     _______,KC_BSLS,KC_TILD,KC_PIPE,KC_EQL ,KC_UNDS,KC_HOME,KC_PGDN,KC_PGUP,KC_END ,KC_BSLS,_______,
     _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

  [_LEANDOWN] = LAYOUT_planck_grid(
     KC_GRV ,KC_EXLM, KC_AT ,KC_HASH, KC_DLR,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
     _______,KC_LPRN,KC_RPRN,KC_LBRC,KC_RBRC,KC_LCBR,KC_LCBR,KC_DLR ,KC_PERC,KC_CIRC,_______,_______,
     _______,KC_BSLS,KC_TILD,KC_PIPE,KC_EQL ,KC_UNDS,KC_HOME,KC_EXLM, KC_AT ,KC_HASH,KC_BSLS,_______,
     _______,_______,_______,_______,_______,_______,_______,_______,KC_LEFT,KC_DOWN, KC_UP ,KC_RGHT
  ),

  [_RAISE] = LAYOUT_planck_grid(
     KC_GRV ,  KC_1 ,  KC_2 ,  KC_3 ,  KC_4 ,  KC_5 ,  KC_6 ,  KC_7 ,  KC_8 ,  KC_9 ,  KC_0 ,_______,
     _______,KC_LPRN,KC_RPRN,KC_LCBR,KC_RCBR,XXXXXXX,XXXXXXX,  KC_4 ,  KC_5 ,  KC_6 ,KC_PPLS,KC_MINS,
     _______,KC_BSLS,KC_TILD,KC_PIPE,KC_EQL ,KC_UNDS,XXXXXXX,  KC_1 ,  KC_2 ,  KC_3 ,KC_PAST,_______,
     _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

  [_WOBBLE] = LAYOUT_planck_grid(
     KC_GRV , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_NO ,KC_MUTE,KC_VOLD,KC_VOLU, KC_NO , KC_NO , KC_DEL,
     _______, KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_NO ,KC_MPRV,KC_MPLY,KC_MSTP,KC_MNXT, KC_NO ,KC_BSLS,
     _______, KC_F9 , KC_F10, KC_F11, KC_F12, KC_NO , KC_NO , KC_NO , KC_NO , KC_INS,KC_PSCR,_______,
     _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
  ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Colemk|      | Debug|RGB Tg|RGB Md|RGB H+|RGB H-|RGB S+|RGB S-|RGB V+|RGB V-|Qwerty|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|      |AS On | AS + |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |AS Rep|AS Off| AS - |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | Reset|
 * `-----------------------------------------------------------------------------------'
 */

[_ADJUST] = LAYOUT_planck_grid(
  COLEMAK, _______, DB_TOGG,  RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, QWERTY ,
  _______, _______, MU_NEXT,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, _______, AS_ON,   AS_UP,
  _______, AU_PREV, AU_NEXT,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, AS_RPT,  AS_OFF,  AS_DOWN,
  _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT  
)


};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
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
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        PORTE &= ~(1<<6);
      } else {
        unregister_code(KC_RSFT);
        PORTE |= (1<<6);
      }
      return false;
      break;
  }
  return true;
}
