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
#include "muse.h"
#include "kuatsure.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _GAME,
  _GAME_LOWER,
  _GAME_RAISE,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = USER_SAFE_RANGE,
  GAME,
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define G_LOWER MO(_GAME_LOWER)
#define G_RAISE MO(_GAME_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab/M|   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc/C|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Ent  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Mute | Ldr  | Alt  | GUI  |Lower |  RSE |     SPC     | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid_wrapper(
    KT_MTAB, _________________QWERTY_L1_________________, _________________QWERTY_R1_________________, KC_BSPC,
    KT_CESC, _________________QWERTY_L2_________________, _________________QWERTY_R2_________________, KC_QUOT,
    KT_LSFT, _________________QWERTY_L3_________________, _________________QWERTY_R3_________________, KC_ENT,
    KC_MPLY, KC_LEAD, KC_LALT, KC_LGUI, LOWER,     RAISE, KC_SPC, KC_SPC,     KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   &  |  Up  |      |   `  |      |   {  |   }  |  _   |      |  |   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | Del  | Left | Down | Right|   ~  |   =  |   (  |   )  |  +   |  :   |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      | Prev | Play | Next |      |   -  |   [  |   ]  |      |  ?   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid_wrapper(
    _______, KC_EXLM, KC_AMPR, KC_UP,   _______,  KC_GRV,  _______, ____CRBRACES____, KC_UNDS, _______, KC_PIPE,
    _______, KC_DEL,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_TILD, KC_EQL,  _____PARENS_____, KC_PLUS, KC_COLN, KC_DQT ,
    _______, _______, KC_MPRV, KC_MPLY, KC_MNXT,  _______, KC_MINS, ___SQBRACKETS___, _______, KC_QUES, _______,
    _______, _______, _______, _______, _______,  _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |  F9  |  F10 |  F11 |  F12 |      |  *   |  7   |  8   |  9   |  0   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F5  |  F6  |  F7  |  F8  |      |  =   |  4   |  5   |  6   |  +   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |      |  -   |  1   |  2   |  3   |  /   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  0   |  0   |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid_wrapper(
    _______, ____________FUNCTION_3____________, _______, KC_ASTR, KC_7,    KC_8,    KC_9,    KC_0,     _______,
    _______, ____________FUNCTION_2____________, _______, KC_EQL,  KC_4,    KC_5,    KC_6,    KC_PLUS,  _______,
    _______, ____________FUNCTION_1____________, _______, KC_MINS, KC_1,    KC_2,    KC_3,    KC_SLASH, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_0,    _______, _______,  _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | MAKE | FLSH |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | RESET| DEBUG|      |      |Aud on|AudOff|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | VRSN |      |      |MusMod|Mus on|MusOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |Qwerty| Game |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid_wrapper(
    _______, KB_MAKE, KB_FLSH, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
    _______, RESET,   DEBUG,   _______, _______, AU_ON,   AU_OFF,  _______, _______, _______, _______, _______,
    _______, KB_VRSN, _______, _______, MU_MOD,  MU_ON,   MU_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, QWERTY,  GAME,    _______, _______
),

/* Game
 *
 * Mostly transparent, but wanted to disable gui key.
 * Also give a key to get back to qwerty layout.
 *
 * Disabling the `Controlled ESC` key is also plus.
 * Think BDO / Monster Hunter
 *
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |  ESC |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl |      |  Spc | gLWR | gRSE |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME] = LAYOUT_planck_grid_wrapper(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_LCTL, _______, KC_SPC,  G_LOWER, G_RAISE, _______, _______, QWERTY,  _______, _______, _______
),

/* Game Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   `  |      |  F9  |  F10 |  F11 |  F12 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   5  |   6  |   7  |   8  |      |      |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   9  |   0  |   -  |   =  |      |      |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME_LOWER] = LAYOUT_planck_grid_wrapper(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_GRV,  _______, ____________FUNCTION_3____________, _______,
    _______, KC_5,    KC_6,    KC_7,    KC_8,    _______, _______, ____________FUNCTION_2____________, _______,
    _______, KC_9,    KC_0,    KC_MINS, KC_EQL,  _______, _______, ____________FUNCTION_1____________, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Game Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |  p7  |  p8  |  p9  |  p0  |   `  |      |  F9  |  F10 |  F11 |  F12 |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  p4  |  p5  |  p6  |  p+  |      |      |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  p1  |  p2  |  p3  |  pE  |      |      |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAME_RAISE] = LAYOUT_planck_grid_wrapper(
    _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_GRV,  _______, ____________FUNCTION_3____________, _______,
    _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______, _______, ____________FUNCTION_2____________, _______,
    _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______, _______, ____________FUNCTION_1____________, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;

    case GAME:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_GAME);
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
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
      tap_code(KC__VOLUP);
    } else {
      tap_code(KC__VOLDOWN);
    }
  }
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_song);
        #endif
        layer_on(_ADJUST);
      } else {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_ADJUST);
      }
      break;
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
      }
   }
}

void matrix_scan_keymap(void) {
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
