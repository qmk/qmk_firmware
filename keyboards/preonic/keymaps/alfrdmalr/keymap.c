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
  // _COLEMAK,
  // _DVORAK,
  _SETTINGS,
  _SYMBOLS,
  _NAVIGATION,
  _NUMPAD,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  // COLEMAK,
  // DVORAK,
  // BACKLIT,
  SYMBOLS,
  NAVIGATION,
  NUMPAD,
  SETTINGS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NAV  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | SHIFT|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |SHIFT |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CTRL | HYPR | LGUI | LALT | SYMB |  SPACE/NUM  | SYMB | RALT | num? |mu tog| CTRL |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GRV,      KC_1,    KC_2,    KC_3,    KC_4,    KC_5,               KC_6,                KC_7,    KC_8,    KC_9,    KC_0,           KC_BSPC, \
  KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,               KC_Y,                KC_U,    KC_I,    KC_O,    KC_P,           KC_DEL,  \
  NAVIGATION,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,               KC_H,                KC_J,    KC_K,    KC_L,    KC_SCLN,        KC_QUOT, \
  KC_LSFT,     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,               KC_N,                KC_M,    KC_COMM, KC_DOT,  KC_SLSH,        KC_RSFT,  \
  KC_LCTL,     NUMPAD,  KC_LGUI, KC_LALT, SYMBOLS, LT(_NUMPAD, KC_SPC), LT(_NUMPAD, KC_SPC),  SYMBOLS, KC_RALT, SETTINGS,  MU_TOG, KC_RCTRL  \
),

/* SYMBOLS
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   #  |   $  |   {  |   }  |      |      |   ^  |   *  |   |  |   ~  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   <  |   >  |   (  |   )  |      |      |   -  |   +  |   &  |   `  |ENTER |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   @  |   !  |   [  |   ]  |      |      |   _  |   =  |   %  |   /  |SHIFT |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS | TRNS | TRNS | TRNS | TRNS |    TRNS     | TRNS | TRNS | TRNS | TRNS | TRNS |
 * `-----------------------------------------------------------------------------------'
 */
[_SYMBOLS] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,       KC_3,       KC_4,       KC_5,     KC_6,     KC_7,       KC_8,     KC_9,     KC_0,    KC_BSPC, \
  KC_TAB,  KC_HASH, KC_DOLLAR,  KC_LCBR,    KC_RCBR,    KC_NO,    KC_NO,    KC_CIRC,    KC_ASTR,  KC_PIPE,  KC_TILD, KC_DEL,  \
  KC_NO,   KC_LABK, KC_RABK,    KC_LPRN,    KC_RPRN,    KC_NO,    KC_NO,    KC_MINS,    KC_PLUS,  KC_AMPR,  KC_GRV,  KC_ENT, \
  KC_LSFT, KC_AT,   KC_EXCLAIM, KC_LBRC,    KC_RBRC,    KC_NO,    KC_NO,    KC_UNDS,    KC_EQL,   KC_PERC,  KC_SLSH, KC_RSFT,  \
  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS,    KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS  \
),

/* NAVIGATION
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS |      |      | SPC  |  F5  |      |      | HOME | END  | TAB  |      | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NAV  | SHIFT| CTRl | ALT  | GUI  |      | LEFT | DOWN | UP   | RIGHT|      | ENTER|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | SHIFT|      | CUT  | COPY | PASTE|      | SPC  | PGDO | PGUP |      |      | SHIFT|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS | TRNS | TRNS | TRNS | TRNS |     ESC     | TRNS | TRNS | TRNS | TRNS | TRNS |
 * `-----------------------------------------------------------------------------------'
 */
[_NAVIGATION] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,     KC_3,    KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,      KC_0,    KC_BSPC, \
  KC_TRNS, KC_NO,   KC_NO,    KC_SPC,  KC_F5,    KC_NO,   KC_NO,   KC_HOME, KC_END,  KC_TAB,    KC_NO,   KC_DEL,  \
  KC_TRNS, KC_LSFT, KC_LCTRL, KC_LALT, KC_LGUI,  KC_NO,   KC_LEFT,   KC_DOWN, KC_UP,   KC_RIGHT,  KC_NO,   KC_ENT, \
  KC_TRNS, KC_UNDO, KC_CUT,   KC_COPY, KC_PASTE, KC_NO,   KC_SPC,  KC_PGDN, KC_PGUP, KC_NO,     KC_NO,   KC_TRNS,  \
  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,  KC_ESC,  KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS  \
),

/* NUMPAD
 * By not having r5/c11 be transparent, we can soft lock the layer by using that key from the base 
 * layer to get here. can always untoggle with one of the other keys (space, r5/c2)
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS |  F9  |  F10 |  F11 |  F12 |      |      |   7  |   8  |   9  |   -  | DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ESC  |  F5  |  F6  |  F7  |  F8  | SPC  | SPC  |   4  |   5  |   6  |   +  | ENTR |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TRNS |  F1  |  F2  |  F3  |  F4  | ALT  | CAPS |   1  |   2  |   3  |   /  | TRNS |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 *j | TRNS | TRNS | TRNS | TRNS | TRNS |    TRNS     |   0  |   ,  |   .  |   *  | TRNS |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,     KC_0,     KC_BSPC, \
  KC_TAB,  KC_F9,   KC_F10,   KC_F11,  KC_F12,  KC_NO,   KC_NO,    KC_7,    KC_8,    KC_9,     KC_MINS,  KC_DEL,  \
  KC_ESC,  KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_SPC,  KC_SPC,   KC_4,    KC_5,    KC_6,     KC_PLUS,  KC_ENT, \
  KC_LSFT, KC_F1,   KC_F2,    KC_F3,   KC_F4,   KC_LALT, KC_CAPS,  KC_1,    KC_2,    KC_3,     KC_SLSH,  KC_TRNS,  \
  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_0, KC_COMM,    KC_DOT,   KC_ASTR,  KC_TRNS  \
),

/* SETTINGS
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
[_SETTINGS] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  _______, RESET,   DEBUG,   _______, _______, _______, _______, TERM_ON, TERM_OFF,_______, _______, KC_DEL,  \
  _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______,  _______, _______, \
  _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
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
        // case COLEMAK:
        //   if (record->event.pressed) {
        //     set_single_persistent_default_layer(_COLEMAK);
        //   }
        //   return false;
        //   break;
        // case DVORAK:
        //   if (record->event.pressed) {
        //     set_single_persistent_default_layer(_DVORAK);
        //   }
        //   return false;
        //   break;
        case SYMBOLS:
          if (record->event.pressed) {
            layer_on(_SYMBOLS);
          } else {
            layer_off(_SYMBOLS);
          }
          return false;
          break;
        case NUMPAD:
          if (record->event.pressed) {
            layer_on(_NUMPAD);
          } else {
            layer_off(_NUMPAD);
          }
          return false;
          break;
        case NAVIGATION:
          if (record->event.pressed) {
            layer_on(_NAVIGATION);
          } else {
            layer_off(_NAVIGATION);
          } 
          return false;
          break;
        case SETTINGS:
          if (record->event.pressed) {
            layer_on(_SETTINGS);
          } else {
            layer_off(_SETTINGS);
          } 
          return false;
          break;

    //     case BACKLIT:
    //       if (record->event.pressed) {
    //         register_code(KC_RSFT);
    //         #ifdef BACKLIGHT_ENABLE
    //           backlight_step();
    //         #endif
    //         #ifdef __AVR__
    //         writePinLow(E6);
    //         #endif
    //       } else {
    //         unregister_code(KC_RSFT);
    //         #ifdef __AVR__
    //         writePinHigh(E6);
    //         #endif
    //       }
    //       return false;
    //       break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

// void encoder_update_user(uint8_t index, bool clockwise) {
//   if (muse_mode) {
//     if (IS_LAYER_ON(_RAISE)) {
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

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            // if (active) {
            //     layer_on(_ADJUST);
            // } else {
            //     layer_off(_ADJUST);
            // }
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
    // case RAISE:
    // case LOWER:
    //   return false;
    default:
      return true;
  }
}