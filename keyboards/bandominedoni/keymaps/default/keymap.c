/* Copyright 2021 3araht
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
#include "version.h"

static uint8_t midi_sub_ch = DEFAULT_SUB_CH_NUMBER;       //  By default, DEFAULT_SUB_CH_NUMBER is used for sub ch.

//  By default( when use_alt_ch_gr == false), DEFAULT ch group (DEFAULT_MAIN_CH_NUMBER for entirely, or right side when separated, DEFAULT_SUB_CH_NUMBER for left side) is used.
//  When false, ALT ch group (ALT_MAIN_CH_NUMBER for entirely, or right side when separated, ALT_SUB_CH_NUMBER for left side) is used.
static bool use_alt_ch_gr = false;

// Defines names for use in layer keycodes and the keymap
enum layer_names {
#ifndef PEDAL_NORMALLY_CLOSED
    _OPEN,
#endif
    _CLOSE,
#ifdef PEDAL_NORMALLY_CLOSED
    _OPEN,
#endif
    _FN
};

static uint8_t my_tone_status[MY_TONE_COUNT];

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_OPEN] = LAYOUT(
                  MY_Gs1, MY_As1, MY_Cs2, MY_F2, MY_Gs3,
       MY_E1, MY_A1, MY_G2, MY_Ds2, MY_F3, MY_As2, MY_F1,
         MY_D2, MY_A2, MY_C3, MY_E3, MY_C2, MY_G1, TG_SWAP,
       MY_E2, MY_Gs2, MY_B2, MY_D3, MY_Fs3, MY_Cs3, MY_Fs1,
     MY_D1, MY_B1, MY_G3, MY_A3, MY_Ds3, MY_Fs2, MY_Ds1, MY_C1,

     MO_SWAP,    MI_B5, MI_Gs5, MI_G5, MI_F5,     FN_MUTE,
         MI_Cs3, MI_A5, MI_Fs5, MI_E5, MI_Ds5,
        MI_C3, MI_D3, MI_G3, MI_As4, MI_C5, MI_D5,
     TG_SWAP, MI_B2, MI_E3, MI_Cs4, MI_Fs3, MI_A3, MI_C4, MI_E4,
       MI_A2, MI_F3, MI_As3, MI_Gs3, MI_B3, MI_D4, MI_Gs4, MI_B4,
     MI_Gs2, MI_As2, MI_Ds3, MI_F4, MI_Ds4, MI_Fs4, MI_A4, MI_Cs5, MI_G4
    ),

    [_CLOSE] = LAYOUT(
                  MY_Gs1, MY_As1, MY_Ds2, MY_Ds3, MY_G3,
       MY_D1, MY_D2, MY_As2, MY_C3, MY_Cs2, MY_C2, MY_Fs1,
         MY_G1, MY_G2, MY_B2, MY_D3, MY_F3, MY_Fs2, TG_SWAP,
       MY_A1, MY_E2, MY_A2, MY_Cs3, MY_E3, MY_Gs2, MY_B1,
     MY_E1, MI_E2, MY_Fs3, MY_Gs3, MY_B3, MY_F2, MY_Cs1, MY_F1,

     MO_SWAP,    MI_A5, MI_Gs5, MI_Fs5, MI_F5,     FN_MUTE,
         MI_C3, MI_G5, MI_As4, MI_C5, MI_Ds5,
        MI_D3, MI_Cs3, MI_Gs3, MI_As3, MI_C4, MI_D5,
     TG_SWAP, MI_B2, MI_Fs3, MI_Fs4, MI_G3, MI_B3, MI_D4, MI_G4,
       MI_A2, MI_F3, MI_E3, MI_A3, MI_Cs4, MY_E4, MI_A4, MI_Cs5,
     MI_Gs2, MI_As2, MI_Ds3, MI_F4, MI_E4, MI_Gs4, MI_B4, MI_E5, MI_Ds4
    ),

    [_FN] = LAYOUT(
                   DF_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

     _______,        MI_OCTD, MI_OCTU, MI_VELD, MI_VELU,         _______,
                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                TGLCHGR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, VERSION,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_OPEN]     = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_CLOSE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN]       = { ENCODER_CCW_CW(_______, _______) },
};
#endif

void keyboard_post_init_user(void) {
    for (uint8_t i = 0; i < MY_TONE_COUNT; i++) {
        my_tone_status[i] = MIDI_INVALID_NOTE;
    }
    //  Set octave to 0
    midi_config.octave = QK_MIDI_OCTAVE_0 - MIDI_OCTAVE_MIN;

    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " " QMK_GIT_HASH " | " QMK_BUILDDATE);
            }
            break;

        case TGLCHGR:
            if (record->event.pressed) {
                use_alt_ch_gr = !use_alt_ch_gr;
                if (use_alt_ch_gr) {
                    midi_sub_ch = ALT_SUB_CH_NUMBER;
                } else {  //  default
                    midi_sub_ch = DEFAULT_SUB_CH_NUMBER;
                }
            }
            break;

        case  MY_TONE_MIN ... MY_TONE_MAX:  // MY tone
            // uprintf("keycode=%u, MY_C3=%u, MY_Db2 =%u, MY_MIN = %u, MY_MAX = %u\n", keycode, MY_C3, MY_Db2, MY_TONE_MIN, MY_TONE_MAX);
            //  DO NOT THROW BELOW into 'if (record->event.pressed) {}' STATEMENT SINCE IT IS USED IN THE FUNCTION BELOW.
            my_process_midi4single_note(midi_sub_ch, keycode, record, my_tone_status);
            break;
    }
    return true;
}
