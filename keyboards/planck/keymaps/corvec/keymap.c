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

#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "action_layer.h"

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

#define KC_ KC_TRNS
#define KC_____ KC_TRNS
#define KC_XXXX KC_NO
#define KC_LOWR LOWER
#define KC_RASE RAISE

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

  [_COLEMAK] = KC_KEYMAP(
  //-----+----+----+----+----+----+----+----+----+----+----+----
     TAB , Q  , W  , F  , P  , G  , J  , L  , U  , Y  ,SCLN,BSPC,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     RESC, A  , R  , S  , T  , D  , H  , N  , E  , I  , O  ,TQTD,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     LSFT, Z  , X  , C  , V  , B  , K  , M  ,COMM,DOT ,SLSH,RSFT,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     LCTL,LGUI,WOBL,LALT,LENT, SPC, SPC,RASE,SDEL,TALT,TGUI,RCTL
  ),

  [_QWERTY] = KC_KEYMAP(
  //-----+----+----+----+----+----+----+----+----+----+----+----
     TAB , Q  , W  , E  , R  , T  , Y  , U  , I  , O  , P  ,BSPC,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     RESC, A  , S  , D  , F  , G  , H  , J  , K  , L  ,SCLN,TQTD,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     LSFT, Z  , X  , C  , V  , B  , N  , M  ,COMM,DOT ,SLSH,RSFT,
  //-----+----+----+----+----+----+----+----+----+----+----+----
     LCTL,LGUI,WOBL,LALT,LENT, SPC, SPC,RASE,RALT,SAPP,RGUI,RCTL
  ),

  [_LOWER] = KC_KEYMAP(
     GRV ,EXLM, AT ,HASH, DLR,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,____,
     ____,LPRN,RPRN,LBRC,RBRC,XXXX,LEFT,DOWN, UP ,RGHT,XXXX,MINS,
     ____,BSLS,TILD,PIPE,EQL ,UNDS,HOME,PGDN,PGUP,END ,BSLS,____,
     ____,____,____,____,____,____,____,____,____,____,____,____
  ),

  [_LEANDOWN] = KC_KEYMAP(
     GRV ,EXLM, AT ,HASH, DLR,PERC,CIRC,AMPR,ASTR,LPRN,RPRN,____,
     ____,LPRN,RPRN,LBRC,RBRC,LCBR,LCBR,DLR ,PERC,CIRC,____,____,
     ____,BSLS,TILD,PIPE,EQL ,UNDS,HOME,EXLM, AT ,HASH,BSLS,____,
     ____,____,____,____,____,____,____,____,LEFT,DOWN, UP ,RGHT
  ),

  [_RAISE] = KC_KEYMAP(
     GRV ,  1 ,  2 ,  3 ,  4 ,  5 ,  6 ,  7 ,  8 ,  9 ,  0 ,____,
     ____,LPRN,RPRN,LCBR,RCBR,XXXX,XXXX,  4 ,  5 ,  6 ,PPLS,MINS,
     ____,BSLS,TILD,PIPE,EQL ,UNDS,XXXX,  1 ,  2 ,  3 ,PAST,____,
     ____,____,____,____,____,____,____,____,____,____,____,____
  ),

  [_WOBBLE] = KC_KEYMAP(
     GRV , F1 , F2 , F3 , F4 , NO ,MUTE,VOLD,VOLU, NO , NO , DEL,
         , F5 , F6 , F7 , F8 , NO ,MPRV,MPLY,MSTP,MNXT, NO ,BSLS,
         , F9 , F10, F11, F12, NO , NO , NO , NO , INS,PSCR,    ,
         ,    ,    ,    ,    ,    ,    ,    ,    ,    ,    ,
  ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Colemk|      | Debug|RGB Tg|RGB Md|RGB H+|RGB H-|RGB S+|RGB S-|RGB V+|RGB V-|Qwerty|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|      |AS On | AS + |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|AS Rep|AS Off| AS - |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      | Reset|
 * `-----------------------------------------------------------------------------------'
 */

[_ADJUST] = {
  {COLEMAK, _______,   DEBUG,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, QWERTY },
  {_______, _______, MU_MOD,   AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK, _______, KC_ASON, KC_ASUP},
  {_______, MUV_DE,  MUV_IN,   MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF,KC_ASRP, KC_ASOFF,KC_ASDN},
  {_______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, RESET  }
}


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
