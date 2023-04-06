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

//  define which MIDI ch to use.
//  Note that (actual MIDI ch# - 1) -> 0 .. 15 is used for coding.
//  ch1
#define DEFAULT_SUB_CH_NUMBER  0
//  ch2
#define ALT_SUB_CH_NUMBER      1
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

enum custom_keycodes {
    VERSION = SAFE_RANGE,
    TGLCHGR,  //  ToGgLe CH GRoup

   // MY tone to distinguish the notes to avoid sustain effect, etc.
    MY_TONE_MIN,

    MY_C = MY_TONE_MIN,
    MY_Cs,
    MY_Db = MY_Cs,
    MY_D,
    MY_Ds,
    MY_Eb = MY_Ds,
    MY_E,
    MY_F,
    MY_Fs,
    MY_Gb = MY_Fs,
    MY_G,
    MY_Gs,
    MY_Ab = MY_Gs,
    MY_A,
    MY_As,
    MY_Bb = MY_As,
    MY_B,

    MY_C1,
    MY_Cs1,
    MY_Db1 = MY_Cs1,
    MY_D1,
    MY_Ds1,
    MY_Eb1 = MY_Ds1,
    MY_E1,
    MY_F1,
    MY_Fs1,
    MY_Gb1 = MY_Fs1,
    MY_G1,
    MY_Gs1,
    MY_Ab1 = MY_Gs1,
    MY_A1,
    MY_As1,
    MY_Bb1 = MY_As1,
    MY_B1,

    MY_C2,
    MY_Cs2,
    MY_Db2 = MY_Cs2,
    MY_D2,
    MY_Ds2,
    MY_Eb2 = MY_Ds2,
    MY_E2,
    MY_F2,
    MY_Fs2,
    MY_Gb2 = MY_Fs2,
    MY_G2,
    MY_Gs2,
    MY_Ab2 = MY_Gs2,
    MY_A2,
    MY_As2,
    MY_Bb2 = MY_As2,
    MY_B2,

    MY_C3,
    MY_Cs3,
    MY_Db3 = MY_Cs3,
    MY_D3,
    MY_Ds3,
    MY_Eb3 = MY_Ds3,
    MY_E3,
    MY_F3,
    MY_Fs3,
    MY_Gb3 = MY_Fs3,
    MY_G3,
    MY_Gs3,
    MY_Ab3 = MY_Gs3,
    MY_A3,
    MY_As3,
    MY_Bb3 = MY_As3,
    MY_B3,

    MY_C4,
    MY_Cs4,
    MY_Db4 = MY_Cs4,
    MY_D4,
    MY_Ds4,
    MY_Eb4 = MY_Ds4,
    MY_E4,
    MY_F4,
    MY_Fs4,
    MY_Gb4 = MY_Fs4,
    MY_G4,
    MY_Gs4,
    MY_Ab4 = MY_Gs4,
    MY_A4,
    MY_As4,
    MY_Bb4 = MY_As4,
    MY_B4,

    MY_C5,
    MY_Cs5,
    MY_Db5 = MY_Cs5,
    MY_D5,
    MY_Ds5,
    MY_Eb5 = MY_Ds5,
    MY_E5,
    MY_F5,
    MY_Fs5,
    MY_Gb5 = MY_Fs5,
    MY_G5,
    MY_Gs5,
    MY_Ab5 = MY_Gs5,
    MY_A5,
    MY_As5,
    MY_Bb5 = MY_As5,
    MY_B5,

    MY_C6,
    MY_TONE_MAX = MY_C6
};

#define MY_TONE_COUNT (MY_TONE_MAX - MY_TONE_MIN + 1)
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

void my_process_midi4single_note(uint8_t channel, uint16_t keycode, keyrecord_t *record, uint8_t *my_tone_status) {
    uint8_t  mytone    = keycode - MY_TONE_MIN;
    uint16_t mykeycode = mytone + MIDI_TONE_MIN;
    // uint16_t mykeycode = keycode - MY_TONE_MIN;
    // uint8_t  mytone    = mykeycode - MIDI_TONE_MIN;
    uint8_t  velocity  = midi_config.velocity;
    // uprintf("keycode=%u,mykeycode=%u,mytone =%u,velo = %u\n", keycode, mykeycode, mytone, velocity);
    if (record->event.pressed) {
        if (my_tone_status[mytone] == MIDI_INVALID_NOTE) {
            uint8_t note = midi_compute_note(mykeycode);
            midi_send_noteon(&midi_device, channel, note, velocity);
            dprintf("midi noteon channel:%d note:%d mytone:%d velocity:%d\n", channel, note, mytone, velocity);
            // uprintf("midi noteon channel:%d note:%d mytone:%d velocity:%d\n", channel, note, mytone, velocity);
            my_tone_status[mytone] = note;  // store root_note status.
        }
    } else {
        uint8_t note = my_tone_status[mytone];
        if (note != MIDI_INVALID_NOTE) {
            midi_send_noteoff(&midi_device, channel, note, velocity);
            dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
            // uprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
        }
        my_tone_status[mytone] = MIDI_INVALID_NOTE;
    }
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
