/* Copyright 2015-2017 Jack Humbert, Christoffer Holmberg
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
#include "keymap_swedish.h"
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _DEFAULT,
  _LOWER,
  _RAISE,
  _UTILITY,
  _ADJUST
};

enum planck_keycodes {
  DEFAULT = SAFE_RANGE,
  RAISE,
  LOWER,
  UTILITY,
  BACKLIT,
  S1, S2, S3, S4, S5, S6, S7, S8, S9
};

#define ESC_LOW LT(_LOWER, KC_ESC)
#define BSP_RAI LT(_RAISE, KC_BSPC)
#define LFT_CTR CTL_T(SE_QUOT)
#define RGT_CTR CTL_T(KC_TILD)
#define UTILITY MO(_UTILITY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |  Å   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Fn   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |  Ä   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Super| Alt  |      |L/Esc | Ret  | Space|R/Bspc|      |AltGr |   *  |  ¨   |
 * `-----------------------------------------------------------------------------------'
 */
[_DEFAULT] = LAYOUT_planck_grid(
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y    , KC_U   , KC_I   , KC_O   , KC_P   , SE_ARNG,
    UTILITY, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H    , KC_J   , KC_K   , KC_L   , SE_ODIA, SE_ADIA,
    SC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N    , KC_M   , KC_COMM, KC_DOT , SE_MINS, SC_RSPC,
    LFT_CTR, KC_LALT, KC_LGUI, SE_AT  , ESC_LOW, KC_ENT , KC_SPC  , BSP_RAI, _______, KC_ALGR, SE_ASTR, RGT_CTR
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   +  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_PLUS,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, SE_RABK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    SE_HALF, LSFT(KC_1), SE_DQUO, LSFT(KC_3), SE_CURR, LSFT(KC_5), SE_AMPR, SE_SLSH, SE_LPRN, SE_RPRN, SE_EQL , SE_QUES,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, SE_LABK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Utility layer
 * ,-----------------------------------------------------------------------------------.
 * |      |      |  up  |      |      |      |      |      |  S1  |  S2  |  S3  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      | left | down | right|      |      |      |      |  S4  |  S5  |  S6  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |  S7  |  S8  |  S9  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Del  |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */

[_UTILITY] = LAYOUT_planck_grid(
    _______, _______, KC_UP  , _______, _______, _______, _______, _______, S1     , S2     , S3     , _______,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, S4     , S5     , S6     , _______,
    _______, _______, _______, _______, _______, _______, _______, _______, S7     , S8     , S9     , _______,
    _______, _______, _______, _______, _______, _______, _______, KC_DEL , _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |Reset |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |Utilit|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9   , KC_F10 , KC_F11 , KC_F12 ,
    _______, QK_BOOT, MU_MOD , AU_ON  , AU_OFF , AG_NORM, AG_SWAP, DEFAULT, XXXXXXX , XXXXXXX, UTILITY, _______,
    _______, SE_PIPE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)


};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
  float s1[][2]              = SONG(NUMBER_ONE);
  float s2[][2]              = SONG(ZELDA_PUZZLE);
  float s3[][2]              = SONG(ZELDA_TREASURE);
  float s4[][2]              = SONG(OVERWATCH_THEME);
  float s5[][2]              = SONG(IMPERIAL_MARCH);
  float s6[][2]              = SONG(E1M1_DOOM);
  float s7[][2]              = SONG(COIN_SOUND);
  float s8[][2]              = SONG(ONE_UP_SOUND);
  float s9[][2]              = SONG(SONIC_RING);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DEFAULT:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DEFAULT);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
    case S1:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s1);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S2:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s2);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S3:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s3);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S4:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s4);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S5:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s5);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S6:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s6);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S7:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s7);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S8:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s8);
        #endif //AUDIO_ENABLE
      }
      return false;
      break;
    case S9:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
            PLAY_SONG(s9);
        #endif //AUDIO_ENABLE
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
