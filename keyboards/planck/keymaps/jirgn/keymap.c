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

#pragma message "You may need to add LAYOUT_planck_grid to your keymap layers - see default for an example"
#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST,
  _NAVIGATION
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  PLOVER,
  LOWER,
  RAISE,
  EXT_PLV
};

// keycode aliases
#define _______ KC_TRNS
#define ___x___ KC_NO
#define KC_EUR LALT(S(KC_2))
#define KC_SEC LALT(KC_6)
#define CTL_DEL CTL_T(KC_DEL)
#define NAV_SCLN LT(_NAVIGATION, KC_SCLN)
#define NAV_A LT(_NAVIGATION, KC_A)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*              Qwerty
 *              ,-----------------------------------------------------------------------------------.
 *              | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 *              |------+------+------+------+------+-------------+------+------+------+------+------|
 * Tab for Esc--| Ctrl | A Nav|   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | ; Nav| Ctrl |--Tab for "
 *              |------+------+------+------+------+------|------+------+------+------+------+------|
 *              | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|--Tab for Enter
 *              |------+------+------+------+------+------+------+------+------+------+------+------|
 *              |      | Hyper| Alt  | Super| Lower|    Space    | Raise| Super| ALt  | Hyper|      |
 *              `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC},
  {CTL_T(KC_ESC), NAV_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    NAV_SCLN, KC_QUOT},
  {KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  SFT_T(KC_ENT)},
  {___x___,       KC_HYPR, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LGUI, KC_LALT, KC_HYPR,  ___x___}
},

/*              Lower
 *              ,-----------------------------------------------------------------------------------.
 *              |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 *              |------+------+------+------+------+-------------+------+------+------+------+------|
 * Tab to Del---| Ctrl |  ¡   |  ™   |  €   |  ¢   |  ∞   |  §   |   _  |   +  |   {  |   }  |  |   |
 *              |------+------+------+------+------+------|------+------+------+------+------+------|
 *              |      |      |      |      |      |      |      |ISO ~ |ISO | |      |      |      |
 *              |------+------+------+------+------+------+------+------+------+------+------+------|
 *              |      |      |      |      |      |             |      |      |      |      |      |
 *              `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, S(KC_1),    S(KC_2),    S(KC_3), S(KC_4),    S(KC_5),    S(KC_6),    S(KC_7),    S(KC_8),    S(KC_9), S(KC_0), KC_BSPC},
  {CTL_DEL, LALT(KC_1), LALT(KC_2), KC_EUR,  LALT(KC_4), LALT(KC_5), LALT(KC_6), KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, ___x___,    ___x___,    ___x___, ___x___,    ___x___,    ___x___,    S(KC_NUHS), S(KC_NUBS), _______, _______, _______},
  {_______, _______,    _______,    _______, _______,    _______,    _______,    _______,    _______,    _______, _______, _______}
},

/*              Raise
 *              ,-----------------------------------------------------------------------------------.
 *              |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 *              |------+------+------+------+------+-------------+------+------+------+------+------|
 * Tab to Del---| Ctrl |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 *              |------+------+------+------+------+------|------+------+------+------+------+------|
 *              |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 *              |------+------+------+------+------+------+------+------+------+------+------+------|
 *              |      |      |      |      |      |             |      |      |      |      |      |
 *              `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {CTL_DEL, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/*              Navigation
 *              ,-----------------------------------------------------------------------------------.
 *              |      |      |      |      |      |      |      |      |      |      |      |      |
 *              |------+------+------+------+------+-------------+------+------+------+------+------|
 *              |      |      | HOME | PGUP | PGDN | END  | LEFT | DOWN | UP   | RIGHT|      |      |
 *              |------+------+------+------+------+------|------+------+------+------+------+------|
 *              |      |      |      |      |      |      |      |      |      |      |      |      |
 *              |------+------+------+------+------+------+------+------+------+------+------+------|
 *              |      |      |      |      |      |             |      |      |      |      |      |
 *              `-----------------------------------------------------------------------------------'
 */
[_NAVIGATION] = {
  {___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,  ___x___, ___x___},
  {_______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END , KC_LEFT, KC_DOWN, KC_UP  , KC_RIGHT, _______, ___x___},
  {_______, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,  ___x___, _______},
  {___x___, _______, _______, _______, ___x___, ___x___, ___x___, ___x___, _______, _______,  _______, ___x___}
},

/*              Plover layer (http://opensteno.org)
 *              ,-----------------------------------------------------------------------------------.
 *              |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 *              |------+------+------+------+------+-------------+------+------+------+------+------|
 *              |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 *              |------+------+------+------+------+------|------+------+------+------+------+------|
 *              |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 *              |------+------+------+------+------+------+------+------+------+------+------+------|
 *              | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 *              `-----------------------------------------------------------------------------------'
 */

[_PLOVER] = {
  {KC_1,    KC_1,    KC_1,    KC_1, KC_1, KC_1,    KC_1,    KC_1, KC_1, KC_1,    KC_1,    KC_1   },
  {___x___, KC_Q,    KC_W,    KC_E, KC_R, KC_T,    KC_Y,    KC_U, KC_I, KC_O,    KC_P,    KC_LBRC},
  {___x___, KC_A,    KC_S,    KC_D, KC_F, KC_G,    KC_H,    KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT},
  {EXT_PLV, ___x___, ___x___, KC_C, KC_V, ___x___, ___x___, KC_N, KC_M, ___x___, ___x___, ___x___}
},

/*              Adjust (Lower + Raise)
 *              ,-----------------------------------------------------------------------------------.
 *              |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 *              |------+------+------+------+------+-------------+------+------+------+------+------|
 *              |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Plover|      |      |      |
 *              |------+------+------+------+------+------|------+------+------+------+------+------|
 *              |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 *              |------+------+------+------+------+------+------+------+------+------+------+------|
 *              |      |      |      |      |      |             |      |      |      |      |      |
 *              `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL },
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  PLOVER,  _______, _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
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
      return false; break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false; break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false; break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false; break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false; break;
  }
  return true;
}
