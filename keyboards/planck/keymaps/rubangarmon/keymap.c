/* Copyright 2015-2021 Jack Humbert
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

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _GAME,
  _LOWER,
  _RAISE,
  _NUMER,
  _FUNC,
  _GAMEL,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  GAME
};

#define LOWER MO(_LOWER)
#define GAMEL MO(_GAMEL)
#define RAISE MO(_RAISE)
#define ADJUS MO(_ADJUST)
#define LCTLESC LCTL_T(KC_ESC)
#define NUMTAB LT(_NUMER, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
*/

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
  * - Tap dance Function layer/semi-colon
  *
  */
[_QWERTY] = LAYOUT_planck_grid(
    NUMTAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    , KC_BSPC,
    LCTLESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    LT(_FUNC, KC_SCLN), LT(_NUMER, KC_QUOT),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH , KC_RSFT ,
    XXXXXXX, XXXXXXX, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_ENT , KC_RALT, XXXXXXX , XXXXXXX
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab* |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;: | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl*|   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O* |  '"* |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |  ,<  |  .>  |  /?  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | GUI  | Alt  |Lower |    Space    |Raise | Enter| RAlt |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid(
    NUMTAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN , KC_BSPC,
    LCTLESC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    LT(_FUNC, KC_O), LT(_NUMER, KC_QUOT),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH , KC_RSFT ,
    XXXXXXX, XXXXXXX, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_ENT , KC_RALT, XXXXXXX , XXXXXXX
),

/* Lower
* ,-----------------------------------------------------------------------------------.
* | Tab  |      |      | Menu |      |      |      |      |      |      | PScrn| Del  |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |      | LAlt | LCtrl|LShift|      | Left | Down |  Up  | Right|      | Ins  |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |      |      |      | Home | PGDN | PGUP | End  |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      | HOLD |     ____    | ADJU |      |      |      | CLOCK|
* `-----------------------------------------------------------------------------------'
*/
[_LOWER] = LAYOUT_planck_grid(
    KC_TAB , _______, _______, KC_LGUI, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_DEL ,
    _______, _______, KC_LALT, KC_LCTL, KC_LSFT, _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, KC_INS ,
    _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END , _______, _______,
    _______, _______, _______, _______, _______, _______, _______, ADJUS  , _______, _______, _______, KC_CAPS
),

/* Raise
* ,-----------------------------------------------------------------------------------.
* |   `  |  !   |  @   |  #   |  $   |  %   |  ^   |   &  |   *  |   -  |   +  |      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |   (  |  )   |  {   |  }   |  =   |  ?   |   :  |   "  |   _  |   =  |  \   |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |   <  |  >   |  [   |  ]   |  >   |  !   |   |  |   ~  |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      | ADJU |             |      |      |      |      |      |
* `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV , KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS, _______,
    _______, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_EQL , KC_QUES, KC_COLN, KC_DQUO, KC_UNDS, KC_EQL , KC_BSLS,
    _______, KC_LT  , KC_GT  , KC_LBRC, KC_RBRC, KC_GT  , KC_EXLM, KC_PIPE, KC_TILD, _______, _______, _______,
    _______, _______, _______, _______, ADJUS  , _______, _______, _______, _______, _______, _______, _______
),

/* Numeric
* ,-----------------------------------------------------------------------------------.
* | HOLD |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |      |      |   -  |   +  |      |      |   4  |   5  |   6  |   +  | HOLD |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |   /  |   *  |      |      |   1  |   2  |   3  |   -  |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |     ____    |   0  | ENTER|   ,  |   /  |  *   |
* `-----------------------------------------------------------------------------------'
*/
[_NUMER] = LAYOUT_planck_grid(
    _______, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
    _______, _______, _______, KC_PMNS, KC_PPLS, XXXXXXX, XXXXXXX, KC_4   , KC_5   , KC_6   , KC_PPLS, _______,
    _______, _______, _______, KC_PSLS, KC_PAST, XXXXXXX, XXXXXXX, KC_1   , KC_2   , KC_3   , KC_PMNS, XXXXXXX,
    _______, _______, _______, XXXXXXX, XXXXXXX, KC_ESC , KC_ESC , KC_0   , KC_ENT , KC_PDOT, KC_PSLS, KC_PAST
),


/* Functions
* ,-----------------------------------------------------------------------------------.
* | Tab  |  F1  |  F2  |  F3  |  F4  |      |      | Prev | Next |      |      |      |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |  F5  |  F6  |  F7  |  F8  |      |      | LShft| LCtl | LAlt | HOLD |      |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |  F9  |  F10 |  F11 |  F12 |      |      | Mute |      |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* | Calc |      |      |      | Vol- |     Play    | Vol+ |      |      |      |      |
* `-----------------------------------------------------------------------------------'
*/
[_FUNC] = LAYOUT_planck_grid(
    KC_TAB , KC_F1  , KC_F2  , KC_F3  , KC_F4  , _______, _______, KC_MPRV, KC_MNXT, _______, _______, _______,
    _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , _______, _______, KC_LSFT, KC_LCTL, KC_LALT, _______, _______,
    _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , _______, _______, KC_MUTE, _______, _______, _______, _______,
    KC_CALC, _______, _______, _______, KC_VOLU, KC_MPLY, KC_MPLY, KC_VOLU, _______, _______, _______, _______
),
/* Game
  * ,-----------------------------------------------------------------------------------.
  * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | CLck |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  ;:* |  '"* |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shft |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |  ,<  |  .>  |  /?  | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Ctrl |      |      | Alt  | GAMEL|    Space    |      | Enter| RAlt |      |      |
  * `-----------------------------------------------------------------------------------'
  * 
  * - Tap dance Ctrl/Esc
  * - Tap dance Numeric layer/Tab
  * - Tap dance Numeric layer/double quotes
  * - Tap dance Function layer/semi-colon
  *
  */
[_GAME] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P    , KC_BSPC,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    LT(_FUNC, KC_SCLN), LT(_NUMER, KC_QUOT),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH , KC_RSFT ,
    KC_LCTL, XXXXXXX, XXXXXXX, KC_LALT, GAMEL,   KC_SPC,  KC_SPC,  RAISE,   KC_ENT , KC_RALT, XXXXXXX , XXXXXXX
),

/* Game Lower
 * ,------------------------------------------------------------------------------------.
 * | Esc  |  1   |  2   |  3   |      |      |      |      |  Up  |       |      |      |
 * |------+------+------+------+------+-------------+------+------+-------+------+------|
 * |      |  4   |  5   |  6   |      |      |      | Left | Down | Right |      |      |
 * |------+------+------+------+------+------|------+------+------+-------+------+------|
 * |      |      |      |      |      |      |      |      |      |       |      |      |
 * |------+------+------+------+------+------+------+------+------+-------+------+------|
 * |      |      |      |      | HOLD |    Space    | ADJU |      |       |      |QWERTY|
 * `------------------------------------------------------------------------------------'
 */
[_GAMEL] = LAYOUT_planck_grid(
    KC_ESC , KC_1   , KC_2   , KC_3   , _______, _______, _______, _______, KC_UP  , _______, _______, _______,
    _______, KC_4   , KC_5   , KC_6   , _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, KC_SPC , KC_SPC , ADJUS  , _______, _______, _______, QWERTY
),

/* Adjust (Lower + Raise)
 * ,------------------------------------------------------------------------------------.
 * |      | Reset| Debug|      |      |      |      |      |      |COLEMAK|      |QWERTY|
 * |------+------+------+------+------+-------------+------+------+-------+------+------|
 * |      |      |      | BRG+ |      |      |      |      |      |       |      |GAME  |
 * |------+------+------+------+------+------|------+------+------+-------+------+------|
 * |      | RGB  |RGBMOD| HUE+ | HUE- |      |      |      |      |       |      |      |
 * |------+------+------+------+------+------+------+------+------+-------+------+------|
 * |      |      |      |      | HOLD |             | HOLD |      |       |      |      |
 * `------------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    XXXXXXX, QK_BOOT, DEBUG  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, COLEMAK, XXXXXXX, QWERTY ,
    XXXXXXX, XXXXXXX, XXXXXXX, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, GAME   ,
    _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
)

};

// #ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float colemak_song[][2]    = SONG(COLEMAK_SOUND);
  float imperial_song[][2]   = SONG(IMPERIAL_MARCH);
  float gameover_song[][2]   = SONG(MARIO_GAMEOVER);
// #endif

// layer_state_t layer_state_set_user(layer_state_t state) {
//   state = update_tri_layer_state(state, _GAMEL, _RAISE, _ADJUST);
//   state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
//   return state;
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");        
        rgblight_setrgb(RGB_TEAL);
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case GAME:
      if (record->event.pressed) {
        print("GAME MODE\n");
        rgblight_setrgb(RGB_GREEN);
        // #ifdef AUDIO_ENABLE
            PLAY_SONG(gameover_song);
        // #endif //AUDIO_ENABLE        
        set_single_persistent_default_layer(_GAME);
      }
      return false;
      break;       
    case COLEMAK:
      if (record->event.pressed) {
        print("COLEMAK MODE\n");
        rgblight_setrgb(RGB_YELLOW);
        // #ifdef AUDIO_ENABLE
            PLAY_SONG(imperial_song);
        // #endif //AUDIO_ENABLE        
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;     
  }
  return true;
}
