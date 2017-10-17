/* Copyright 2017 MogranJM
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
#include "terminus_mini.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum terminus_mini_layers {
  _COLEMAK,
  _LOWER,
  _RAISE,
  _FUNCTION,
  _MOUSE,
  _ADJUST
};

enum terminus_mini_keycodes {
  COLEMAK = SAFE_RANGE,
  LOWER,
  RAISE,
  FUNCTION,
  MOUSE
};

  // Enable these functions using FUNC(n) macro.
  const uint16_t PROGMEM fn_actions[] = { //ACTION_LAYER_TAP_TOGGLE requires that number of taps be defined in *config.h* - default set to 5
      [0] = ACTION_LAYER_TAP_KEY(_LOWER, KC_SPC),    //Hold for momentary Lower layer, Tap for Space, 
      [1] = ACTION_LAYER_TAP_KEY(_RAISE, KC_ENT),    //Hold for momentary Mouse layer, Tap for Enter,
      [2] = ACTION_LAYER_TAP_TOGGLE(_LOWER),         //Hold for momentary Lower, Tap for toggle Lower
      [3] = ACTION_LAYER_TAP_TOGGLE(_MOUSE),         //Hold for momentary Mouse, Tap for toggle Mouse
      [4] = ACTION_LAYER_MOMENTARY(_FUNCTION),       //Hold for momentary Function
   };
#define SPC_LW FUNC(0)
#define ENT_RS FUNC(1)
#define LWR FUNC(2)
#define MSE FUNC(3)
#define FNC FUNC(4)

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak -
 * ,----------------------------------------------------------------------------------.
 * | Tab |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  |  Del |
 * |-----+------+------+------+------+-------------+------+------+------+------+------|
 * | BS  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |-----+------+------+------+------+-------------+------+------+------+------+------|
 * | LSPO|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  | RSPC |
 * |-----+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl| LGUI | LAlt | Lower|    SpaceLW  |    RSEnter  |  Fn  | Mouse| Menu | Ctrl |
 * `----------------------------------------------------------------------------------'
 */
[_COLEMAK] = TERMINUS_MINI(
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,      KC_Y,    KC_SCLN, KC_DEL , \
  KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,      KC_I,    KC_O,    KC_QUOT, \
  KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM,   KC_DOT,  KC_SLSH, KC_RSPC, \
  KC_LCTL, KC_LGUI, KC_LALT, LWR,          SPC_LW,           ENT_RS,      FNC,       MSE,     KC_APP,  KC_RCTL \
  ),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  Tab | PgUp | Home |  Up  |  End |   /  |   7  |   8  |   9  |  *   |      |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  BS  | PgDn | Left | Down |Right |   -  |   4  |   5  |   6  |  +   |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LSPO |   Z  |   X  |   C  |   V  |   =  |   1  |   2  |   3  | Enter|      | RSPC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | LGUI | Alt  | Lower| Space/Lower |      0      |   .  |  Fn  | Menu | Ctrl |
 * `-----------------------------------------------------------------------------------'
 Want to add tap-dance function to 0 key: Tap=0, doubleTap=Ent
 */

[_LOWER] = TERMINUS_MINI(
  KC_TAB,  KC_PGUP,  KC_HOME,  KC_UP,    KC_END,   KC_PSLS,  KC_7,  KC_8,  KC_9,   KC_PAST,  XXXXXXX, _______, \
  _______, KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_MINS,  KC_4,  KC_5,  KC_6,   KC_PPLS,  XXXXXXX, _______, \
  _______, _______,  _______,  _______,  _______,  KC_EQL,   KC_1,  KC_2,  KC_3,   KC_PENT,  XXXXXXX, _______, \
  _______, _______,  _______,  _______,       _______,       KC_0,       KC_DOT,   FNC,      _______, _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  Esc |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   -  |   +  |  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  BS  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   "  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LSPO |      |      |   {  |   [  |   `  |   \  |   ]  |   }  |   .  |   ?  | RSPC |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | LGUI | Alt  |      | Space/Lower | Raise/Enter |  Fn  | Mouse| Menu | Ctrl |
 * `-----------------------------------------------------------------------------------'
  */

[_RAISE] = TERMINUS_MINI(
   KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC, KC_CIRC,  KC_AMPR, KC_ASTR, KC_MINS, KC_EQL,  _______, \
   _______, KC_1,    KC_2,    KC_3,    KC_4,     KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    _______, \
   _______, XXXXXXX, XXXXXXX, KC_LCBR, KC_LBRC,  KC_GRV,  KC_BSLS,  KC_RBRC, KC_RCBR, KC_DOT,  KC_SLSH, _______, \
   _______, _______, _______, _______,        SPC_LW,            ENT_RS,     FNC,     MSE,     _______, _______ \
   ),

/*Function
 * ,-----------------------------------------------------------------------------------.
 * | Esc  | Mute | Vol- | Vol+ |      | RESET| POWER|  F1  |  F2  |  F3  |  F4  | Ins  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Caps | Stop | |<<  | >/|| |  >>| |      |      |  F5  |  F6  |  F7  |  F8  |PrtSc |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | LSOB |      |      |      |      |      |      |  F9  | F10  | F11  | F12  |ScrLk |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | LGUI | Alt  |      | Space/Lower | Enter/Raise |  Fn  |      |      |PsBrk |
 * `-----------------------------------------------------------------------------------'
 */

[_FUNCTION] = TERMINUS_MINI( 
  _______, KC_MUTE, KC_VOLD, KC_VOLU,  XXXXXXX,   RESET,  KC_PWR,  KC_F1,  KC_F2,   KC_F3,   KC_F4, KC_INS , \
  KC_CAPS, KC_MSTP, KC_MPRV, KC_MPLY,  KC_MNXT, XXXXXXX, XXXXXXX,  KC_F5,  KC_F6,   KC_F7,   KC_F8, KC_PSCR, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,  KC_F9,  KC_F10, KC_F11,  KC_F12, KC_SLCK, \
  _______, _______, _______, _______,         _______,        _______,     FNC,   _______, _______, KC_PAUS \
  ),

/* MOUSE
 * ,---------------------------------------------------------------------------------------.
 * |  Esc | WhlU  | WhlL  | MsUp | WhlR |      |      |   M1  |   M2  |  M3  |      |      |
 * |------+-------+------+-------+------+------+------+-------+-------+------+------+------|
 * |      | WhlD  | MsL   | MsDn | MsR  |      |      |LClick |RClick |      |      |      |
 * |------+-------+------+-------+------+------+------+-------+-------+------+------+------|
 * | LSPO |       |      |       |      |      |      |       |       |      |      | RSCB |
 * |------+-------+------+-------+------+------+------+-------+-------+------+------+------|
 * | Ctrl |       |      |       | Sensitivity |  Sensitivity |       |MOUSE |      | Ctrl |
 * `---------------------------------------------------------------------------------------'
 */

[_MOUSE] = TERMINUS_MINI(
   KC_ESC,  KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R,  XXXXXXX, XXXXXXX, KC_BTN3, KC_BTN4,  KC_BTN5, XXXXXXX, XXXXXXX, \
   KC_BSPC, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R,  XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2,  XXXXXXX, XXXXXXX, XXXXXXX, \
   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_RSPC, \
   _______, XXXXXXX, XXXXXXX, XXXXXXX,      KC_ACL2,           KC_ACL0,     XXXXXXX,      MSE, XXXXXXX, KC_RCTL \
  ),

};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_COLEMAK);
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
  }
  return true;
}


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
