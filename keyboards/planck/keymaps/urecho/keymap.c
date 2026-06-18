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

#include "planck.h"
#include "action_layer.h"
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif

// Left-hand home row mods
#define HOME_A LCTL_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// // Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RCTL_T(KC_SCLN)

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _MOUSE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
  EXT_PLV,
  MOUSE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------------------------------------------------------------------------------------.
 * | Tab       |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Bksp     |
 * |-----------+------+------+------+------+-------------+------+------+------+------+---------|
 * | Ctrl(Esc) |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter    |
 * |-----------+------+------+------+------+------|------+------+------+------+------+---------|
 * | Shift     |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift(') |
 * |-----------+------+------+------+------+------+------+------+------+------+------+---------|
 * | LCAG      | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | GUI  | Alt  | Ctrl |         |
 * `-------------------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC               },
  {CTL_T(KC_ESC), HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,    KC_H,    HOME_J,  HOME_K,  HOME_L,  HOME_SCLN, KC_ENT              },
  {KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MT(MOD_RSFT, KC_QUOT) },
  {LCAG_T(KC_NO), KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_RGUI, KC_RALT, KC_RCTL, HYPR_T(KC_NO)         }
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Home | End  |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | PgUp | PgDn |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL},
  {_______, KC_HOME, KC_END,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, KC_PGUP, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Lower
 * ,----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |  6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  | Left| Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|-----+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 | F11 | F12  |      |      |      |      |
 * |------+------+------+------+------+------+-----+------+------+------+------+- -----|
 * |      |      |      |      |      |            |      |      |      |      |      |
 * `----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL},
  {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______},
  {_______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
},

/* Mouse/Keypad Layer
  .-----------------------------------------------------------------------------------------------------------.
  |        | MS WHL | MS U   | MS WHR | MS WHU | XXXXXX | Numlock| KP 7   | KP 8   | KP 9   | =      |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        | MS L   | MS D   | MS R   | MS WHD | XXXXXX | /      | KP 4   | KP 5   | KP 6   | -      | Enter  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        | MS BT5 | MS BT4 | MS BT3 | MS BT2 | MS BT1 | *      | KP 1   | KP 2   | KP 3   | +      |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        | KP 0   | .      | ,      |        |
  '-----------------------------------------------------------------------------------------------------------'
*/
[_MOUSE] = {
  { _______, KC_WH_L, KC_MS_U, KC_WH_R, KC_WH_U, XXXXXXX, KC_NUMLOCK    , KC_KP_7, KC_KP_8, KC_KP_9  , KC_KP_EQUAL, _______     },
  { _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, XXXXXXX, KC_KP_SLASH   , KC_KP_4, KC_KP_5, KC_KP_6  , KC_KP_MINUS, KC_KP_ENTER },
  { _______, KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, XXXXXXX, KC_KP_ASTERISK, KC_KP_1, KC_KP_2, KC_KP_3  , KC_KP_PLUS , _______     },
  { _______, _______, _______, _______, _______, _______, _______       , _______, KC_KP_0, KC_KP_DOT, KC_KP_COMMA, _______     }
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |MS HWL| MS U |MS WHR|MS WHU|      |      |Qwerty|Mouse |Backli|Reset |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | MS L | MS D | MS R |MS WHD|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |MS BT4|MS BT3|MS BT2|MS BT1|      |Musmod|Aud on|Audoff|Mus on|Musoff|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, _______, _______, _______, _______, _______, _______, QWERTY , MOUSE  , BACKLIT, RESET  , _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  {_______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MNXT, MU_MOD , AU_ON  , AU_OFF , MU_ON  , MU_OFF , _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
}
 

};

#ifdef AUDIO_ENABLE
// float startup_song[][2]     = SONG(STARTUP_SOUND);
float qwerty_song[][2]      = SONG(QWERTY_SOUND);
// float dvorak_song[][2]      = SONG(DVORAK_SOUND);
// float colemak_song[][2]     = SONG(COLEMAK_SOUND);
// float plover_song[][2]      = SONG(PLOVER_SOUND);
// float plover_gb_song[][2]   = SONG(PLOVER_GOODBYE_SOUND);
// float music_scale_song[][2] = SONG(MUSIC_SCALE_SOUND);
float tone_goodbye[][2]     = SONG(GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(qwerty_song);
        #endif
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_MOUSE);
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

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_J:
            return false;
        case HOME_K:
            return false;
        case HOME_L:
            return false;
        case HOME_D:
            return false;
        case HOME_F:
            return false;
        default:
            return true;
    }
}

