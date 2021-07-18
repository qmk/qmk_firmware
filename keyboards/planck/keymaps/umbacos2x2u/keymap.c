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
#include "keymap_italian.h"

#define MT_RSFT_ENT MT(MOD_RSFT, KC_ENT)
#define MT_RSFT_TAB MT(MOD_RSFT, KC_TAB)

enum planck_layers {
  _QWERTY,
  _SHIFT,
  _NUMBER,
  _SYMBOL,
  _ACCENT,
  _SERVICE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_2x2u(
  KC_ESC,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC,  \
  KC_TAB,       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   IT_MINS,   KC_SFTENT,  \
  LT(_SHIFT, KC_DEL),  KC_Z,  KC_X,  KC_C,  KC_V,   KC_B,    KC_N,    KC_M,    IT_COMM, IT_DOT,  IT_SLSH,   LT(_SHIFT, IT_APOS), \
  KC_LCTL, KC_LALT, MO(_SERVICE), KC_LGUI, LT(_NUMBER, KC_DEL), LT(_ACCENT, KC_SPC),  KC_UP,   KC_LEFT, KC_DOWN, KC_RGHT  \
),

[_SHIFT] = LAYOUT_planck_2x2u(
  S(KC_ESC),  S(KC_Q),    S(KC_W), S(KC_E), S(KC_R), S(KC_T), S(KC_Y), S(KC_U), S(KC_I), S(KC_O), S(KC_P), S(KC_BSPC),  \
  S(KC_TAB),  S(KC_A),    S(KC_S), S(KC_D), S(KC_F), S(KC_G), S(KC_H), S(KC_J), S(KC_K), S(KC_L), IT_UNDS, S(KC_ENT), \
  IT_QST,    S(KC_Z),    S(KC_X), S(KC_C), S(KC_V), S(KC_B), S(KC_N), S(KC_M), IT_SCLN,  IT_COLN, IT_QST, IT_DQOT,  \
  S(KC_LCTL), S(KC_LALT), MO(_SERVICE), S(KC_LGUI), LT(_SYMBOL, KC_DEL), LT(_ACCENT, KC_SPC),  S(KC_UP), S(KC_LEFT), S(KC_DOWN), S(KC_RGHT)  \
),

[_NUMBER] = LAYOUT_planck_2x2u(
  IT_LESS,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    IT_EQL, \
  KC_TAB, KC_PPLS, KC_PMNS, KC_PSLS, KC_PAST, XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6, KC_0, KC_SFTENT,
  LT(_SYMBOL, KC_DEL), IT_EQL,  IT_LBRC, IT_RBRC,   KC_DOT,   KC_F5,   KC_F6,   KC_1,    KC_2,    KC_3, KC_DOT, LT(_SYMBOL, KC_DEL),
  KC_F1,   KC_F2,   KC_F3,   KC_F4, _______, _______, KC_VOLU, _______, KC_VOLD, KC_MUTE \
),

[_SYMBOL] = LAYOUT_planck_2x2u(
    IT_MORE, IT_EXLM, IT_AT,   IT_SHRP, IT_DLR,  IT_PERC, IT_CRC,  IT_AMPR, IT_ASTR, IT_LPRN, IT_RPRN, IT_PLUS, \
    S(KC_TAB), KC_PPLS, IT_UNDS, KC_PSLS, KC_PAST,XXXXXXX, IT_MORE, IT_LESS,  IT_LCBR, IT_LCBR, IT_RCBR, KC_SFTENT,
    KC_LSFT, _______, _______, _______, _______, _______, IT_BKSL,  IT_PIPE, IT_UNDS, IT_PLUS, _______, IT_QST, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

[_ACCENT] = LAYOUT_planck_2x2u(
    _______, IT_EURO, IT_AT, IT_EACC, _______, _______, _______, IT_UACC, IT_IACC, IT_OACC, _______, _______,  \
    _______, IT_AACC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   \
    KC_LSFT, _______, _______, _______, _______, _______, _______, _______, IT_SCLN, IT_COLN, _______, _______,   \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

[_SERVICE] = LAYOUT_planck_2x2u(
  RESET,  KC_BTN1, KC_MS_U, KC_BTN2, _______, MUV_DE, MU_ON, AU_ON, _______, _______, _______, _______,
  _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, MU_MOD, MU_OFF, AU_OFF, _______, _______, _______, _______,
  KC_LSFT, _______, _______, _______, _______, MUV_IN, _______, _______, _______, _______, KC_VOLU, KC_RSFT,
  _______, _______, _______, _______, _______,     _______,       _______, _______, KC_VOLD, KC_MUTE
),

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_SERVICE);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_SERVICE);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
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
