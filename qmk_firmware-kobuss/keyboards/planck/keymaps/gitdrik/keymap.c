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

/* Modified from planck default to Finnish SFS 5966 by gitdrik, 2020. */

#include QMK_KEYBOARD_H
#include "muse.h"

enum planck_layers {
  _BASE,
  _LEFT,
  _RIGHT,
  _LEFTER,
  _RIGHTER
};

#define LEFT TT(_LEFT)
#define RIGHT MO(_RIGHT)
#define LEFTER MO(_LEFTER)
#define RIGHTER MO(_RIGHTER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |   Å  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   Ö  |   Ä  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Shift|   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  | Shift| Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   Z  | GUI  | Alt  |Left2 | Left |BkSpc | Spc  |Right |Rghter|   <  |   -  |   /  |
 * `-----------------------------------------------------------------------------------'
 */
[_BASE] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,    KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC,
    KC_ESC,  KC_A,    KC_S,    KC_D,   KC_F,   KC_G,    KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LCTL, KC_LSFT, KC_X,    KC_C,   KC_V,   KC_B,    KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_RSFT, KC_ENT ,
    KC_Z,    KC_LGUI, KC_LALT, LEFTER, LEFT,   KC_BSPC, KC_SPC, RIGHT,  RIGHTER, KC_NUBS, KC_SLSH, LSFT(KC_7)
),

/* Left
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  F10 |  F9  |  F8  |  F7  |   {  |   }  |   7  |   8  |   9  |   ^  |   =  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  F11 |  F6  |  F5  |  F4  |   (  |   )  |   4  |   5  |   6  |   +  |   *  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | RCtrl| Shift|  F3  |  F2  |  F1  |   [  |   ]  |   1  |   2  |   3  | Shift| Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | F12  | GUI  | Alt  |Lefter| Left |BkSpc | Spc  |Right |   0  |   ,  |   -  |   /  |
 * `-----------------------------------------------------------------------------------'
 */
[_LEFT] = LAYOUT_planck_grid(
    KC_TRNS, KC_F10,  KC_F9,   KC_F8,   KC_F7,   RALT(KC_7), RALT(KC_0), KC_7,    KC_8,   KC_9,    LSFT(KC_RBRC), LSFT(KC_0),
    KC_TRNS, KC_F11,  KC_F6,   KC_F5,   KC_F4,   LSFT(KC_8), LSFT(KC_9), KC_4,    KC_5,   KC_6,    KC_PPLS,       KC_PAST,
    KC_RCTL, KC_TRNS, KC_F3,   KC_F2,   KC_F1,   RALT(KC_8), RALT(KC_9), KC_1,    KC_2,   KC_3,    KC_TRNS,       KC_TRNS,
    KC_F12,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS, KC_0,   KC_COMM, KC_PMNS,       KC_PSLS
),

/* Right
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  ◌̄   |  ◌̈	  |  ◌́	  |  ◌̀	  |  ◌̃	  |  ◌̆   | Home |  Up  | End  | Ins  | PgUp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  @   |   $  |   °  |   &  |   #  |   %  | Left | Down | Right| Del  | PgDn |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | RCtrl| Shift|   ”  |   «  |   »  |  ‚ „ |   ‰  |PlayPs|  <<  |  >>  | Shift| Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   “  | GUI  | Alt  |Lefter|      |BkSpc | Spc  |Right |Rghter| Vol- | Vol+ | Mute |
 * `-----------------------------------------------------------------------------------'
 */
 [_RIGHT] = LAYOUT_planck_grid(
    KC_TRNS,          RALT(LSFT(KC_RBRC)), KC_RBRC,          KC_EQL ,          LSFT(KC_EQL),     RALT(KC_RBRC), RALT(KC_NUHS), KC_HOME, KC_UP,   KC_END , KC_INS , KC_PGUP,
    KC_TRNS,          RALT(KC_2),          RALT(KC_4),       RALT(LSFT(KC_0)), LSFT(KC_6),       LSFT(KC_3),    LSFT(KC_5),    KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_PGDN,
    KC_RCTRL,         KC_TRNS,             RALT(LSFT(KC_2)), RALT(LSFT(KC_4)), RALT(LSFT(KC_3)), RALT(KC_6),    RALT(KC_5),    KC_MPLY, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
    RALT(LSFT(KC_5)), KC_TRNS,             KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,       KC_TRNS,       KC_TRNS, KC_TRNS,  KC_VOLD, KC_VOLU, KC_MUTE
),

/* Lefter
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |  § ½ |   "  |   €  |      |  þ Þ |   ¡  |   !  |   ı  |  œ Œ |  ◌̛ ◌̉ | ◌̋  ◌̊ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |  ə Ə |  ß ẞ |  ð Ð |   '  |      |      |      |   ĸ  |   ◌̵  |  ø Ø |  æ Æ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Shift|  × · | ◌̧  ◌̨ |      |   \  |  ŋ Ŋ |  µ — |  ’ ‘ | ◌̣  ◌̇ | Shift| Enter|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  ʒ Ʒ | GUI  | Alt  |Lefter|      | BkSpc| NbSp |      |Rghter|   |  | – ◌̦  |   ?  |
 * `-----------------------------------------------------------------------------------'
 */
 [_LEFTER] = LAYOUT_planck_grid(
    KC_TRNS,   KC_GRV,    LSFT(KC_2), RALT(KC_E),   RALT(KC_R), RALT(KC_T),    RALT(LSFT(KC_1)), LSFT(KC_1), RALT(KC_I),    RALT(KC_O),    RALT(KC_P),    RALT(KC_LBRC),
    KC_TRNS,   RALT(KC_A),RALT(KC_S), RALT(KC_D),   KC_NUHS,    RALT(KC_G),    RALT(KC_H),       RALT(KC_J), RALT(KC_K),    RALT(KC_L),    RALT(KC_SCLN), RALT(KC_QUOT),
    KC_TRNS,   KC_TRNS,   RALT(KC_X), RALT(KC_EQL), RALT(KC_V), RALT(KC_MINS), RALT(KC_N),       RALT(KC_M), RALT(KC_COMM), RALT(KC_DOT),  KC_TRNS,       KC_TRNS,
    RALT(KC_Z),KC_TRNS,   KC_TRNS,    KC_TRNS,      KC_TRNS,    RALT(KC_BSPC), RALT(KC_SPC),     KC_TRNS,    KC_TRNS,        RALT(KC_NUBS), RALT(KC_SLSH), LSFT(KC_MINS)
),

/* Righter
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset| Debug|      |      |      |      |WheLft|  MUp |WheRgt| MBt2 | WheUp|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | MBt4 | MBt3 | MBt2 | MBt1 |      |      | MLeft| MDown|MRight| MBt1 | WheDn|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Mus on|Musoff|      |      | MBt1 | MBt2 | MBt3 |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |Rghter|Light-|Light+|      |
 * `-----------------------------------------------------------------------------------'
 */
 [_RIGHTER] = LAYOUT_planck_grid(
    KC_TRNS, RESET,   DEBUG,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_WH_L, KC_MS_U, KC_WH_R, KC_BTN2, KC_WH_U,
    KC_TRNS, KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, KC_WH_D,
    KC_TRNS, KC_TRNS, MU_MOD,  MU_ON,   MU_OFF,  KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_BTN3, KC_TRNS, KC_TRNS,
    KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_BRID, KC_BRIU, KC_NO
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

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RIGHT)) {
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
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
}

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
                layer_on(_LEFTER);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_LEFTER);
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

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case _LEFTER:
      return false;
    default:
      return true;
  }
}
