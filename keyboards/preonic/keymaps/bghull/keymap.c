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
//#include "muse.h"
#include "keymap_steno.h"

enum preonic_layers {
  _QWERTY,
  _STENO,
  _NUMPAD
};

/*
enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE
};
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | '  " |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |NUMPAD|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  | /  ? |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Es/Ctl| FUNC | STENO| Alt  |    Bspc     |    Space    | Ctrl | Left | Down | Right|
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  _______ ,      KC_1,    KC_2,   KC_3,     KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_QUOT, \
  KC_TAB ,       KC_Q,    KC_W,   KC_E,     KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,  \
  MO(_NUMPAD),   KC_A,    KC_S,   KC_D,     KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT, \
  KC_LSFT ,      KC_Z,    KC_X,   KC_C,     KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_SLSH,  \
  LCTL_T(KC_ESC),KC_LGUI, DF(_STENO),       KC_LALT, _______, KC_BSPC, _______, KC_SPC,  KC_LCTL, KC_LEFT, KC_DOWN,  KC_RGHT  \
),


/* Steno
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  FN  |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |QWERTY|   A  |      O      |      E      |   U  |  PWR | RES1 | RES2 |
 * `-----------------------------------------------------------------------------------'
 */
[_STENO] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______,  _______, _______, _______, _______,  _______, _______, _______, _______,    \
  STN_N1,  STN_N2,  STN_N3,  STN_N4,  STN_N5,  STN_N6,  STN_N7,  STN_N8,  STN_N9,  STN_NA,  STN_NB,  STN_NC ,
  STN_FN,  STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1, STN_ST3, STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR ,
  XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2, STN_ST4, STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR ,
  XXXXXXX, XXXXXXX, DF(_QWERTY),STN_A,XXXXXXX, STN_O,   XXXXXXX, STN_E,   STN_U,   STN_PWR, STN_RE1, STN_RE2
),

/* 
 * ,-----------------------------------------------------------------------------------.
 * |      |RClick|  MsU |LClick|WheelU|   (  |  )   |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  MsL |  MsD |  MsR |WheelD|  [{  |  ]}  |   4  |   5  |   6  |   +  |  -_  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Mute | VolD | VolU |  `~  |   _  |  =   |   1  |   2  |   3  | PgUp | \  | |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | RESET|      |      |             |      |   .  | Home | PgDn | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_grid( \
  _______, _______,_______, _______,  _______, _______, _______, _______,  _______, _______, _______, _______,    \
  _______, KC_BTN2, KC_MS_U, KC_BTN1,  KC_WH_U, KC_LPRN, KC_RPRN,    KC_7,     KC_8,    KC_9,    KC_0, _______, \
  _______, KC_MS_L, KC_MS_D, KC_MS_R,  KC_WH_D, KC_LBRC, KC_RBRC,    KC_4,     KC_5,    KC_6, KC_PPLS, KC_MINS, \
  _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_GRAVE, KC_UNDS,  KC_EQL,    KC_1,     KC_2,    KC_3, KC_PGUP, KC_BSLS, \
  _______, XXXXXXX, RESET, _______,  _______, _______, _______, _______,  KC_PDOT, KC_HOME, KC_PGDN, KC_END   \
)

};


/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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
*/