/* Copyright 2015-2017 Jack Humbert
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

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _NUMER,
  _FUNC,
  _GAME,
  _GAMER,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  GAME
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define CTRLESC LCTRL_T(KC_ESC)
#define NUMTAB LT(_NUMER, KC_TAB)


#define _NAVIGATION 8
#define NAVL MO(_NAVIGATION)
#define NAVSPC LT( 8, KC_SPC)
//#define SHFTENT SHFT_T(KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Tab* |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Ctrl*|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:* |  '"* |
     * |------+------+------+------+------+------|------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  | Shift|
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      | GUI  | Alt  |Lower |    Space    |Raise | Enter| RAlt |      |      |
     * `-----------------------------------------------------------------------------------'
     * 
     * - Tap dance Ctrl/Esc
     * - Tap dance Numeric layer/Tab
     * - Tap dance Numeric layer/double quotes
     * - Tap dance Function layer/Tab
     *
   */
  [_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,           KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,           KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,           KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SFT_T(KC_ENT) ,
    KC_LCTL, LCTL(KC_LSFT),  KC_LGUI, KC_LALT, LOWER,   NAVSPC,  NAVSPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  ),

/* Lower
* ,-----------------------------------------------------------------------------------.
* | Tab  |      |      | Menu |      |      |      |      |      |      | PScrn| Del  |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* | ____ |      | LAlt | LCtrl|LShift|      | Left | Down |  Up  | Right|      | Ins  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | ____ |      |      |      |      |      | Home | PGDN | PGUP | End  |      | _____|
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      | ____ | ____ | HOLD |     ____    | ADJU | ____ | ____ |      |      |
* `-----------------------------------------------------------------------------------'
*/
[_LOWER] = LAYOUT_planck_grid(
   KC_TILD, KC_F7,  KC_F8, KC_F9, KC_F10, KC_F11,  KC_F12, KC_UNDS, KC_PLUS, KC_LCBR,  KC_RCBR,   KC_BSPC ,
   KC_DEL , KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5,  KC_F6, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC,   KC_PIPE ,
   _______, LCTL(KC_Z),  LCTL(KC_X), LCTL(KC_C),  LCTL(KC_V), _______, _______, _______, _______, _______, _______,   KC_ENT ,
   _______, _______, _______, _______, _______, KC_SPC, KC_SPC, _______, KC_HOME, KC_PGDN, KC_PGUP,    KC_END
),

/* Raise
* ,-----------------------------------------------------------------------------------.
* |   `  |  !   |  @   |  #   |  $   |  %   |  ^   |   &  |   *  |   -  |   +  |  -   |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* | Ctrl*|   (  |  )   |  {   |  }   |  =   |  ?   |   :  |   "  |   _  |   =  |  \   |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Shift|   <  |  >   |  [   |  ]   |  >   |  !   |   |  |   ~  |      |      | Shift|
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      | Alt  | ADJU |    Space    | HOLD | Enter| RAlt |      |      |
* `-----------------------------------------------------------------------------------'
*/

[_RAISE] = LAYOUT_planck_grid(
   KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,    KC_BSPC ,
   KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,       KC_BSLS ,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_ENT ,
   _______, _______, _______, _______, _______, KC_SPC, KC_SPC, _______, KC_HOME, KC_PGDN, KC_PGUP,    KC_END
),

/* Functions
* ,-----------------------------------------------------------------------------------.
* | Tab  |  F1  |  F2  |  F3  |  F4  |      |      | Prev | Next |      |      |      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* | Ctrl*|  F5  |  F6  |  F7  |  F8  |      |      | LSht | LCtl | LAlt | HOLD |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* | Shift|  F9  |  F10 |  F11 |  F12 |      |      | MUTE |      |      | BRG- | BRG+ |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Cacl |      |      | Alt  | Vol- |    Play     | Vol+ |      | RGBT | RGB- | RGB+ |
* `-----------------------------------------------------------------------------------'
*/

[_RAISE] = LAYOUT_planck_grid(
   KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,    KC_BSPC ,
   KC_DEL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,       KC_BSLS ,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_ENT ,
   _______, _______, _______, _______, _______, KC_SPC, KC_SPC, _______, KC_HOME, KC_PGDN, KC_PGUP,    KC_END
),

/* GAME
  * ,-----------------------------------------------------------------------------------.
  * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:* |  '"* |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Ctrl |      |      | Alt  | GameL|    Space    |      | Enter| RAlt |      |      |
  * `-----------------------------------------------------------------------------------'
  *
  * This layer is supposed to be used for gaming, you normally cant Ctrl on
  * it's normal position and Space acting as normal. I moved NUM modifier to
  * where Shift is in the base layer. This is mainly thought for LoL as I can
  * have numbers and F keys close to my thumb.
  * - Tap dance Raise/Enter
  * - Tap dance Lower/Backspace
  *
  * */

/* Game Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |      |      |      |      |  UP  |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CAPS |   4  |   5  |   6  |      |      |      | LEFT | DOWN | RIGHT|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | HOLD |    Space    | ADJU | ENTER|      |      |      |
 * `-----------------------------------------------------------------------------------'
 */


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset| Debug|      |      |      |      |      |      |      | GAME |QWERTY|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | HOLD |             | HOLD |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
  QK_BOOT,             XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ,
  LALT(LCTL(KC_DEL)),  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,
  KC_CAPSLOCK,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INS, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX,
  _______,             _______, _______, _______, _______, _______, _______, _______, QWERTY,  COLEMAK, DVORAK, XXXXXXX  //PLOVER
),


};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
  }
  return true;
}
