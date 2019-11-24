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

//Tap Dance Declarations
enum tap_dance {
  TD_PRNSL,
  TD_PRNSR,
  TD_PIPE,
};

// Nicer keycode alias for keymap readability
#define x KC_NO // No action
#define _v_ KC_TRNS // Pass through
#define L_SYMB LT(_SYMB,KC_CAPSLOCK)
#define L_NAV LT(_NAV,KC_TAB)
#define L_ADJUST LT(_ADJUST,KC_ESC)
#define L_TOGGLE LT(_TOGGLE,KC_HOME)
#define L_GAMING TG(_GAMING)
#define L_LOCK TO(_LOCK)
#define L_UNLOCK TO(_QWERTY)
#define L_LOWER MO(_LOWER)

#define HYP_MINS ALL_T(KC_MINS)
#define MEH_PLUS MEH_T(KC_PPLS)
#define CUT LGUI(KC_X)
#define COPY LGUI(KC_C)
#define PASTE LGUI(KC_V)
#define UNDO LGUI(KC_Z)
#define REDO LSFT(LGUI(KC_Z))

// VSCODE keys
#define CONSOLE LCTL(KC_C)
#define DEL_LINE MEH(KC_K)
#define LINE_DOWN LALT(KC_DOWN)
#define LINE_UP LALT(KC_UP)
#define PANE_1 LGUI(KC_1)
#define PANE_2 LGUI(KC_2)
#define PANE_3 LGUI(KC_3)
#define SORT_LINES KC_F5

// Gaming
#define SCRSHT MEH(KC_PSCR)
#define STATS MEH(8)

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _ADJUST,
  _SYMB,
  _NAV,
  _MOUSE,
  _TOGGLE,
  _GAMING,
  _LOCK,
  _UNLOCK,
  _RESET
};

// enum preonic_keycodes {
//   QWERTY = SAFE_RANGE,
//   LOWER,
//   RAISE,
//   BACKLIT
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_preonic_grid( \
  L_ADJUST, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  L_NAV,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE,
  L_SYMB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SFTENT,
  KC_LCTL, KC_LALT, KC_LGUI, L_LOWER, KC_SPC,  KC_SPC,  KC_BSPC, KC_BSPC, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT
),

[_SYMB] = LAYOUT_preonic_grid( \
  x,       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_LBRC, KC_RBRC, KC_F9,   KC_F10,  LSFT(KC_EQL),
  x,       x,       x,       x,       x,       x,       KC_EXLM, KC_LPRN, KC_RPRN, KC_DLR,  KC_PERC, KC_MINS,
  _v_,     x,       PANE_1,  PANE_2,  PANE_3,  x,       KC_PIPE, KC_LCBR, KC_RCBR, KC_EQL,  KC_COLN, KC_GRV,
  _v_,     x,       CUT,       COPY, PASTE,       x,       KC_AMPR, KC_LT,   KC_GT,   LSFT(KC_MINS), KC_SLSH, LSFT(KC_GRV),
  x,       x,       _v_,    _v_,      _v_,     _v_,     KC_DEL,  KC_DEL,     _v_,     _v_,     _v_,     _v_
),


[_LOWER] = LAYOUT_preonic_grid( \
  x,       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  L_LOCK,
  _______, _______, _______, _______, MO(_RESET), _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, L_GAMING, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, KC_DEL, KC_DEL, _______, _______, _______, _______
),

[_RESET] = LAYOUT_preonic_grid( \
  RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  DEBUG,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_LOCK] = LAYOUT_preonic_grid( \
  x, x, x, x, x, x, x, x, x, x, x, x,
  x, x, x, x, x, x, x, x, x, x, x, x,
  x, x, x, x, x, x, x, x, x, x, x, x,
  x, x, x, x, x, x, x, x, x, x, x, x,
  x, x, x, MO(_UNLOCK), x, x, x, x, x, x, x, x
),

[_UNLOCK] = LAYOUT_preonic_grid( \
  x, x, x, x, x, x, x, x, x, x, x, L_UNLOCK,
  x, x, x, x, x, x, x, x, x, x, x, x,
  x, x, x, x, x, x, x, x, x, x, x, x,
  x, x, x, x, x, x, x, x, x, x, x, x,
  x, x, x, x, x, x, x, x, x, x, x, x
),

[_NAV] = LAYOUT_preonic_grid(
  x,       x,       x,       x,       x,       x,       x,       KC_MRWD, KC_MPLY, KC_MFFD, KC__MUTE,KC_VOLU,
  _v_,     x,       x,       x,       x,       x,       x,       x,       KC_UP,   x,       x,       KC_VOLD,
  x,       x,       x,       x,       x,       x,       x,       KC_LEFT, KC_DOWN, KC_RGHT, x,       KC_MPLY,
  x,       x,       x,       x,       x,       x,        x,    LALT(KC_LEFT),x,    LALT(KC_RGHT),x,   x,
  x, x, x, x, x, x, x, x, x, x, x, x
),

[_GAMING] = LAYOUT_preonic_grid( \
  KC_ESC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_TAB, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_LSFT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ENT,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|AudOff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______,  _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)


};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//         case QWERTY:
//           if (record->event.pressed) {
//             set_single_persistent_default_layer(_QWERTY);
//           }
//           return false;
//           break;
//         case COLEMAK:
//           if (record->event.pressed) {
//             set_single_persistent_default_layer(_COLEMAK);
//           }
//           return false;
//           break;
//         case DVORAK:
//           if (record->event.pressed) {
//             set_single_persistent_default_layer(_DVORAK);
//           }
//           return false;
//           break;
//         case LOWER:
//           if (record->event.pressed) {
//             layer_on(_LOWER);
//             update_tri_layer(_LOWER, _RAISE, _ADJUST);
//           } else {
//             layer_off(_LOWER);
//             update_tri_layer(_LOWER, _RAISE, _ADJUST);
//           }
//           return false;
//           break;
//         case RAISE:
//           if (record->event.pressed) {
//             layer_on(_RAISE);
//             update_tri_layer(_LOWER, _RAISE, _ADJUST);
//           } else {
//             layer_off(_RAISE);
//             update_tri_layer(_LOWER, _RAISE, _ADJUST);
//           }
//           return false;
//           break;
//         case BACKLIT:
//           if (record->event.pressed) {
//             register_code(KC_RSFT);
//             #ifdef BACKLIGHT_ENABLE
//               backlight_step();
//             #endif
//             #ifdef __AVR__
//             PORTE &= ~(1<<6);
//             #endif
//           } else {
//             unregister_code(KC_RSFT);
//             #ifdef __AVR__
//             PORTE |= (1<<6);
//             #endif
//           }
//           return false;
//           break;
//       }
//     return true;
// };

// bool muse_mode = false;
// uint8_t last_muse_note = 0;
// uint16_t muse_counter = 0;
// uint8_t muse_offset = 70;
// uint16_t muse_tempo = 50;

// void encoder_update_user(uint8_t index, bool clockwise) {
//   if (muse_mode) {
//     if (IS_LAYER_ON(_GAMING)) {
//       if (clockwise) {
//         muse_offset++;
//       } else {
//         muse_offset--;
//       }
//     } else {
//       if (clockwise) {
//         muse_tempo+=1;
//       } else {
//         muse_tempo-=1;
//       }
//     }
//   } else {
//     if (clockwise) {
//       register_code(KC_PGDN);
//       unregister_code(KC_PGDN);
//     } else {
//       register_code(KC_PGUP);
//       unregister_code(KC_PGUP);
//     }
//   }
// }

// void dip_update(uint8_t index, bool active) {
//   switch (index) {
//     case 0:
//       if (active) {
//         layer_on(_ADJUST);
//       } else {
//         layer_off(_ADJUST);
//       }
//       break;
//     case 1:
//       if (active) {
//         muse_mode = true;
//       } else {
//         muse_mode = false;
//         #ifdef AUDIO_ENABLE
//           stop_all_notes();
//         #endif
//       }
//    }
// }

// void matrix_scan_user(void) {
//   #ifdef AUDIO_ENABLE
//     if (muse_mode) {
//       if (muse_counter == 0) {
//         uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
//         if (muse_note != last_muse_note) {
//           stop_note(compute_freq_for_midi_note(last_muse_note));
//           play_note(compute_freq_for_midi_note(muse_note), 0xF);
//           last_muse_note = muse_note;
//         }
//       }
//       muse_counter = (muse_counter + 1) % muse_tempo;
//     }
//   #endif
// }

// bool music_mask_user(uint16_t keycode) {
//   switch (keycode) {
//     case _LOWER:
//       return false;
//     default:
//       return true;
//   }
// }
