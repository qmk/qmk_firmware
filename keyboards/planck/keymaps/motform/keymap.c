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
#include "keymap_swedish.h"

extern keymap_config_t keymap_config;

enum planck_layers {
                    _COLEMAK,
                    _LOWER,
                    _RAISE,
                    _ADJUST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

/* These definitions can be removed once keymap_swe is properly vetted against MacOS */
#define NO_DLR_MAC_V  ALGR(LALT(KC_4))
#define NO_AT_MAC_V   ALGR(LALT(KC_2))

/* Esc when pressed, ctrl when used as a modifier */
#define KC_ECTL MT(MOD_LCTL, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak_se
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   Ö  |  Å   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ECTR |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  Ä   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | SCSHE|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   -  |SCSHE |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | esc  | CTRL | Alt  | CMD  |Lower |Space |Bksp  |Raise | CMD  | RALT | HYPER| MEH  |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_planck_grid
(
 KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    NO_OSLH, NO_AA,
 KC_ECTL,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    NO_AE,
 KC_SFTENT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  NO_MINS, KC_SFTENT,
 KC_ESC,    KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_BSPC, RAISE,   KC_RGUI, KC_RALT, KC_HYPR, KC_MEH
 ),

/* Lower
* ,-----------------------------------------------------------------------------------.
* |      | PIPE |   '  |   @  |   &  |      | DOWN |      | RIGHT|   `  |   ´  |  ~   |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |      |   !  |   "  |   #  |   ?  |   %  | LEFT |   /  |   \  |   =  |   +  |  *   |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |   [  |   {  |      | UP   |   }  |   ]  |      |      |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |      | DEL  |      | Next | Vol- | Vol+ | Play |
* `-----------------------------------------------------------------------------------'
*/
[_LOWER] = LAYOUT_planck_grid
(
 _______, NO_PIPE_MAC, NO_APOS, NO_AT_MAC_V, NO_AMPR,     _______, KC_DOWN, KC_NO,       KC_RGHT,     NO_GRV,  NO_GRV,  NO_TILD,
 _______, KC_EXLM,     NO_QUO2, KC_HASH,     NO_QUES,     KC_PERC, KC_LEFT, NO_SLSH,     NO_BSLS_MAC, NO_EQL,  KC_PPLS, KC_PAST,
 _______, KC_NO,       KC_NO,   NO_LBRC,     NO_LCBR_MAC, KC_NO,   KC_UP,   NO_RCBR_MAC, NO_RBRC,     KC_NO,   KC_NO,   _______,
 _______, _______,     _______, _______,     _______,     _______, KC_DEL,  _______,     KC_MNXT,     KC_VOLD, KC_VOLU, KC_MPLY
 ),

/* Raise
* ,-----------------------------------------------------------------------------------.
* |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
* |------+------+------+------+------+-------------+------+------+------+------+------|
* |   ^  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  $   |
* |------+------+------+------+------+------|------+------+------+------+------+------|
* |      |      |      |   <  |   (  |      |      |  )   |   >  |Pg Up |Pg Dn |      |
* |------+------+------+------+------+------+------+------+------+------+------+------|
* |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
* `-----------------------------------------------------------------------------------'
*/
[_RAISE] = LAYOUT_planck_grid
(
 KC_F1,   KC_F2,   KC_F3,   KC_F4,       KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,       KC_F10,  KC_F11,  KC_F12,
 NO_CIRC, KC_1,    KC_2,    KC_3,        KC_4,    KC_5,    KC_6,    KC_7,    KC_8,        KC_9,    KC_0,    NO_DLR_MAC_V,
 _______, KC_NO,   KC_NO,   NO_LESS_MAC, NO_LPRN, KC_NO,   KC_NO,   NO_RPRN, NO_GRTR_MAC, KC_PGUP, KC_PGDN, KC_NO,
 _______, _______, _______, _______,     _______, _______, _______, _______, KC_MNXT,     KC_VOLD, KC_VOLU, KC_MPLY
 ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset| Debug|      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TRMon |TRMoff|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid
(
 _______, RESET,   DEBUG,   _______, _______, _______, _______, _______, _______,  _______, _______, _______,
 _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______,  _______, _______, _______,
 _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
 )

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
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
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_DOWN);
        unregister_code(KC_MS_WH_DOWN);
      #else
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        register_code(KC_MS_WH_UP);
        unregister_code(KC_MS_WH_UP);
      #else
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      #endif
    }
  }
}

void dip_update(uint8_t index, bool active) {
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
        #ifdef AUDIO_ENABLE
          stop_all_notes();
        #endif
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
