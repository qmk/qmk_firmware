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

enum preonic_layers {
  _QWERTY,
  _COLEMAK_DHM,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK_DHM,
  LOWER,
  RAISE,
  BACKLIT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,--------------------------------------------------------------------------------------------.
 * | GEsc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp          |
 * |------+------+------+------+------+------+------+------+------+------+------+---------------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del           |
 * |------+------+------+------+------+-------------+------+------+------+------+---------------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "            |
 * |------+------+------+------+------+------|------+------+------+------+------+---------------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Rshift + Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+---------------|
 * | Lctl | RAlt | LGui | LAlt |Lower |    Space    |Raise | Left | Down |  Up  |Right          |
 * `--------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
  KC_LCTL, KC_RALT, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Colemak DhM
 * ,--------------------------------------------------------------------------------------------.
 * | GEsc |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp          |
 * |------+------+------+------+------+------+------+------+------+------+------+---------------|
 * | Tab  |   Q  |   W  |   F  |   P  |   V  |   J  |   L  |   U  |   Y  |   ;  | Del           |
 * |------+------+------+------+------+-------------+------+------+------+------+---------------|
 * | Esc  |   A  |   R  |   S  |   T  |   G  |   M  |   N  |   E  |   I  |   O  |  "            |
 * |------+------+------+------+------+------|------+------+------+------+------+---------------|
 * | Shift|   Z  |   X  |   C  |   D  |   B  |   K  |   H  |   ,  |   .  |   /  |Rshift + Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+---------------|
 * | Lctl | RAlt | LGui | LAlt |Lower |    Space    |Raise | Left | Down |  Up  |Right          |
 * `--------------------------------------------------------------------------------------------'
 */
[_COLEMAK_DHM] = LAYOUT_preonic_grid(
  KC_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
  KC_LCTL,  KC_RALT, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),


/* Lower
 * ,------------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #   |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+-------+------+-------------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #   |   $  |   %  |   ^  |   &  |   (  |   )  |   :  | Del  |
 * |------+------+------+-------+------+-------------+------+------+------+------+------|
 * | Del  |   `  |PrtSn |^+PrtSn|alt+F4| ISO ~| ISO ||   _  |   {  |   }  |   *  |  +   |
 * |------+------+------+-------+------+------|------+------+------+------+------+------|
 * |      | VOL- | VOL+ | Play  | Next |Insert|  |   |  \   |  [   |   ]  |   \  |  *   |
 * |------+------+------+-------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | GUI  | ALT   |      |             |      | Home | PgeDn| PgeUp| End  |
 * `------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,      KC_PERC,    KC_CIRC,    KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,      KC_PERC,    KC_CIRC,    KC_AMPR, KC_LPRN, KC_RPRN, KC_COLN, KC_DEL,
  KC_DEL,  KC_GRV, KC_PSCR, LSFT(LCTL(KC_PSCR)), LALT(KC_F4), S(KC_NUHS), S(KC_NUBS), KC_UNDS, KC_LCBR, KC_RCBR, KC_ASTR, KC_PLUS,
  _______, KC_VOLD, KC_VOLU, KC_MPLY, KC_MNXT,     KC_INS,     KC_PIPE,    KC_BSLS, KC_LBRC, KC_RBRC, KC_BSLS, KC_ASTR,
  KC_RCTL,  RAISE, KC_LGUI, KC_RALT, _______,     _______,    _______,     _______,KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  ESC |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  | F9   | F10  |BckSpc|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  Tab | F11  |  F12 |shf+F2| PrtSn|ScrLck|Pause |   =  |   7  |   8  |   9  |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  | Home | PgUp | PgDn | End  |      |      |   -  |   4  |   5  |   6  |  +   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Left | Down |  Up  | Right|rs+ins|      |   /  |   1  |   2  |   3  |  *   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Rctl | RAlt | RGUI | RAlt |      |             |      |   .  |   0  |   ,  |  =   |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,          KC_F6,   KC_F7,   KC_F8,  KC_F9, KC_F10, KC_BSPC,
  KC_TAB,  KC_F11, KC_F12, LSFT(KC_F2), KC_PSCR, KC_SLCK,        KC_PAUS, KC_EQL,  KC_P7,   KC_P8,   KC_P9,   KC_DEL,
  KC_DEL,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,        _______, KC_MINS, KC_P4,   KC_P5,   KC_P6,   KC_PLUS,
  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, RSFT_T(KC_INS), KC_RCTL, KC_SLSH, KC_P1,   KC_P2,   KC_P3,   KC_ASTR,
  KC_RCTL,  KC_RALT, KC_RGUI, KC_RALT, _______, _______,        _______, _______, KC_DOT, KC_P0,   KC_COMM,KC_EQL
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |RGB_TG|RGBnxt|RGB_T |RGB_P | RGB_B| RGB_R|RGB_SW|RGB_SN|RGB_K |RGB_X |RGB_G |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |CapsLk|      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Numlck|Brght+|Effct+|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|Reset | Debug|      |Brght-|Effct-|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  RGB_TOG, RGB_MOD, RGB_M_T,   RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K,RGB_M_X, RGB_M_G, KC_DEL,
  _______, KC_CAPS, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  COLEMAK_DHM, KC_NLCK,  RGB_VAI, RGB_SPI,
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  RESET, DEBUG, _______, RGB_VAD, RGB_SPD,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK_DHM:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK_DHM);
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
            #ifdef RGBLIGHT_ENABLE
              rgblight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
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

bool encoder_update_user(uint8_t index, bool clockwise) {
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
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
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
    return true;
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
