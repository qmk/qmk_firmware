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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_WORKMAN] = LAYOUT_planck_base(
      __________________WORKMN_L1__________________,       __________________WORKMN_R1__________________,
      __________________WORKMN_L2__________________,       __________________WORKMN_R2__________________,
      __________________WORKMN_L3__________________,       __________________WORKMN_R3__________________
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
      KC_PGUP, KC_TAB,  KC_UP,   KC_ENT,  KC_PGDN, XXXXXXX, XXXXXXX,   XXXXXXX, KC_7, KC_8,   KC_9,    KC_ASTR,
      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, XXXXXXX, XXXXXXX,   XXXXXXX, KC_4, KC_5,   KC_6,    KC_SLSH,
      KC_ESC,  KC_BSPC, XXXXXXX, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, KC_1, KC_2,   KC_3,    KC_MINS,
      KC_LSFT, KC_LEAD, KC_CCCV, KC_MEH,  KC_BSPC,  KC_SPC, XXXXXXX,    KC_ENT, KC_0, KC_DOT, KC_COMM, LED_LEVEL
  ),

  /* Raise
  * ,-----------------------------------------------------------------------------------.
  * |      |   _  |   [  |   ]  |   ^  |      |      |   !  |   <  |   >  |   =  |      |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |   \  |   /  |   {  |   }  |   *  |      |      |   ?  |   (  |   )  |   -  |  :   |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |   #  |   $  |   |  |   ~  |   `  |      |      |   @  |   %  |   '  |   +  |  &   |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      | LEAD |      |      | BSPC |    SPACE    | held |      |      |      |      |
  * `-----------------------------------------------------------------------------------'
  */
  [_RAISE] = LAYOUT_planck_common(
      XXXXXXX, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC,    KC_EXLM, KC_LABK, KC_RABK, KC_EQL , XXXXXXX,
      KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,    KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_SCLN,
      KC_HASH, KC_DLR , KC_PIPE, KC_TILD, KC_GRV ,    KC_AT,   KC_PERC, KC_QUOT, KC_PLUS, KC_AMPR
  ),

  /* Adjust (Lower + Raise)
  * ,-----------------------------------------------------------------------------------.
  * |      | Debug|Reset |TermOn|TrmOff|      |      |MusMod|Mus On|MusOff|MidiOn|MidOff|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Mute | Vol- | Vol+ | Play | Skip |      |      |Voice-| HUE+ | HUE- | SAT+ | SAT- |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      | AudOn|AudOff|CGswap|CGnorm|      |      |Voice+|RGBTog|RGBMod|BRGHT+|BRGHT-|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      |      |      |      | held |             | held |      |      |      |      |
  * `-----------------------------------------------------------------------------------'
  */
  [_ADJUST] = LAYOUT_planck_common(
       XXXXXXX,       DEBUG,     RESET, TERM_ON, TERM_OFF,      MU_MOD, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,
      KC__MUTE, KC__VOLDOWN, KC__VOLUP, KC_MPLY,  KC_MNXT,      MUV_IN, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,
       XXXXXXX,       AU_ON,    AU_OFF, CG_SWAP,  CG_NORM,      MUV_DE, RGB_TOG, RGB_MOD, RGB_VAI, RGB_VAD
  )

};

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

void dip_switch_update_keymap(uint8_t index, bool active) {
    switch (index) {
        case 0: {
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
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

#ifdef AUDIO_ENABLE
void matrix_scan_keymap(void) {
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
}
#endif


#ifdef KEYBOARD_planck_ez
layer_state_t layer_state_set_keymap(layer_state_t state) {
    planck_ez_left_led_off();
    planck_ez_right_led_off();
    switch (get_highest_layer(state)) {
        case _LOWER:
            planck_ez_left_led_on();
            break;
        case _RAISE:
            planck_ez_right_led_on();
            break;
        case _ADJUST:
            planck_ez_right_led_on();
            planck_ez_left_led_on();
            break;
        default:
            break;
    }
    return state;
}
#endif

bool music_mask_keymap(uint16_t keycode) {
  switch (keycode) {
    case _RAISE:
    case _LOWER:
      return false;
    default:
      return true;
  }
}
