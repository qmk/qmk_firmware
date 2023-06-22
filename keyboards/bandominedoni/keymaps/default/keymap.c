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
    VERSION = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_OPEN] = LAYOUT(
                  MI_Gs1, MI_As1, MI_Cs2, MI_F2, MI_Gs3,
       MI_E1, MI_A1, MI_G2, MI_Ds2, MI_F3, MI_As2, MI_F1,
         MI_D2, MI_A2, MI_C3, MI_E3, MI_C2, MI_G1, TG_SWAP,
       MI_E2, MI_Gs2, MI_B2, MI_D3, MI_Fs3, MI_Cs3, MI_Fs1,
     MI_D1, MI_B1, MI_G3, MI_A3, MI_Ds3, MI_Fs2, MI_Ds1, MI_C1,

     MO_SWAP,    MI_B5, MI_Gs5, MI_G5, MI_F5,     FN_MUTE,
         MI_Cs3, MI_A5, MI_Fs5, MI_E5, MI_Ds5,
        MI_C3, MI_D3, MI_G3, MI_As4, MI_C5, MI_D5,
     TG_SWAP, MI_B2, MI_E3, MI_Cs4, MI_Fs3, MI_A3, MI_C4, MI_E4,
       MI_A2, MI_F3, MI_As3, MI_Gs3, MI_B3, MI_D4, MI_Gs4, MI_B4,
     MI_Gs2, MI_As2, MI_Ds3, MI_F4, MI_Ds4, MI_Fs4, MI_A4, MI_Cs5, MI_G4
    ),

    [_CLOSE] = LAYOUT(
                  MI_Gs1, MI_As1, MI_Ds2, MI_Ds3, MI_G3,
       MI_D1, MI_D2, MI_As2, MI_C3, MI_Cs2, MI_C2, MI_Fs1,
         MI_G1, MI_G2, MI_B2, MI_D3, MI_F3, MI_Fs2, TG_SWAP,
       MI_A1, MI_E2, MI_A2, MI_Cs3, MI_E3, MI_Gs2, MI_B1,
     MI_E1, MI_E2, MI_Fs3, MI_Gs3, MI_B3, MI_F2, MI_Cs1, MI_F1,

     MO_SWAP,    MI_A5, MI_Gs5, MI_Fs5, MI_F5,     FN_MUTE,
         MI_C3, MI_G5, MI_As4, MI_C5, MI_Ds5,
        MI_D3, MI_Cs3, MI_Gs3, MI_As3, MI_C4, MI_D5,
     TG_SWAP, MI_B2, MI_Fs3, MI_Fs4, MI_G3, MI_B3, MI_D4, MI_G4,
       MI_A2, MI_F3, MI_E3, MI_A3, MI_Cs4, MI_E4, MI_A4, MI_Cs5,
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
                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, VERSION,
     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_OPEN]     = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_CLOSE]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN]       = { ENCODER_CCW_CW(_______, _______) },
};
#endif

void keyboard_post_init_user(void) {
    //  Set octave to 0
    midi_config.octave = QK_MIDI_OCTAVE_0 - MIDI_OCTAVE_MIN;

    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING(QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            break;
    }
    return true;
}
