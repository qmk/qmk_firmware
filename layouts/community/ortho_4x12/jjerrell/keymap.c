/* Copyright 2015-2017 Jack Humbert
 * Copyright 2021 Jacob Jerrell <@jjerrell>
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

#include "jjerrell.h"

enum planck_keycodes {
  BACKLIT = NEW_SAFE_RANGE,
  TH_LVL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_WORKMAN] = LAYOUT_planck_mods(
      __________________WORKMN_L1__________________,       __________________WORKMN_R1__________________,
      __________________WORKMN_L2__________________,       __________________WORKMN_R2__________________,
      __________________WORKMN_L3__________________,       __________________WORKMN_R3__________________,
                                          LW_BSPC, SH_SPCE, RS_ENTR
  ),

  /* Lower
  * ,-----------------------------------------------------------------------------------.
  * | PGUP | BSPC |  UP  | DEL  | PGDN |      |      |      |   7  |   8  |   9  |  *   |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | HOME | LEFT | DOWN | RGHT | END  |      |      |      |   4  |   5  |   6  |  /   |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | ESC  | TAB  |      | ENTR |      |      |      |      |   1  |   2  |   3  |  -   |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      |      |      |      | held |    SPACE    | ENTR |   0  |   .  |   ,  |  +   |
  * `-----------------------------------------------------------------------------------'
  */
  [_LOWER] = LAYOUT_planck_mods(
      KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN,     XXXXXXX, KC_7, KC_8,   KC_9,    KC_ASTR,
      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,      XXXXXXX, KC_4, KC_5,   KC_6,    KC_SLSH,
      KC_ESC,  KC_TAB,  XXXXXXX, KC_ENT,  XXXXXXX,     XXXXXXX, KC_1, KC_2,   KC_3,    KC_MINS,
                                          LW_BSPC, SH_SPCE, RS_ENTR
  ),

  /* Raise
  * ,-----------------------------------------------------------------------------------.
  * |      |   _  |   [  |   ]  |   ^  |      |      |   !  |   <  |   >  |   =  |      |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |   \  |   /  |   {  |   }  |   *  |      |      |   ?  |   (  |   )  |   -  |  :   |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |   #  |   $  |   |  |   ~  |   `  |      |      |   @  |   %  |   '  |   +  |  &   |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      | LEAD |      |      | TAB  |    SPACE    | held |      |      |      |      |
  * `-----------------------------------------------------------------------------------'
  */
  [_RAISE] = LAYOUT_planck_common(
      XXXXXXX, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC,       KC_EXLM, KC_LABK, KC_RABK, KC_EQL , XXXXXXX,
      KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,       KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_SCLN,
      KC_HASH, KC_DLR , KC_PIPE, KC_TILD, KC_GRV ,       KC_AT,   KC_PERC, KC_QUOT, KC_PLUS, KC_AMPR,
                                          LW_BSPC, SH_SPCE, RS_ENTR
  ),

  /* Adjust (Lower + Raise)
  *                      v------------------------RGB CONTROL--------------------v
  * ,-----------------------------------------------------------------------------------.
  * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      |      |      |      |      |             |      |      |      |      |      |
  * `-----------------------------------------------------------------------------------'
  */
  [_ADJUST] = LAYOUT_planck_common(
      RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI,      RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD,
      _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM,      AG_SWAP, QWERTY,  WORKMN,   _______, _______,
      MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,        MI_OFF,  TERM_ON, TERM_OFF, _______, _______,
                                          LW_BSPC, SH_SPCE, RS_ENTR
  )

};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BACKLIT:
    if (record->event.pressed) {
      register_code(KC_RSFT);
      # ifdef BACKLIGHT_ENABLE
        backlight_step();
      # endif
    # ifdef KEYBOARD_planck_rev5
      writePinLow(E6);
    # endif
    } else {
      unregister_code(KC_RSFT);
    # ifdef KEYBOARD_planck_rev5
      writePinHigh(E6);
    # endif
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

bool encoder_update(bool clockwise) {
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
  return true;
}

// void dip_switch_update_keymap(uint8_t index, bool active) {
//     switch (index) {
//         case 0: {
//             if (active) {
//                 layer_on(_ADJUST);
//             } else {
//                 layer_off(_ADJUST);
//             }
//             break;
//         }
//         case 1:
//             if (active) {
//                 muse_mode = true;
//             } else {
//                 muse_mode = false;
//             }
//     }
// }

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
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_keymap(uint16_t keycode) {
  switch (keycode) {
    case _RAISE:
    case _LOWER:
      return false;
    default:
      return true;
  }
}