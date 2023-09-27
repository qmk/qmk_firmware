/* Copyright 2022 3araht
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

// Long press: go to _FN , tap: MUTE
#define FN_MUTE LT(_FN, KC_MUTE)

// Used to set octave to QK_MIDI_OCTAVE_0
extern midi_config_t midi_config;

// Defines names for use in  keycodes and the keymap
enum _names {
    _BASE,
    _RESERVE01,
    _FN                  //  FN layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        FN_MUTE,
        MI_C1,  MI_Db1,  MI_D1,   MI_Eb1, MI_E1, MI_F1, MI_Fs1, MI_G1, MI_Ab1, MI_A1, MI_Bb1, MI_B1,
        MI_C2,  MI_Db2,  MI_D2,   MI_Eb2, MI_E2, MI_F2, MI_Fs2, MI_G2, MI_Ab2, MI_A2, MI_Bb2, MI_B2,
        MI_C3,  MI_Db3,  MI_D3,   MI_Eb3, MI_E3, MI_F3, MI_Fs3, MI_G3, MI_Ab3, MI_A3, MI_Bb3, MI_B3,
        MI_C4,  MI_Db4,  MI_D4,   MI_Eb4, MI_E4, MI_F4, MI_Fs4, MI_G4, MI_Ab4, MI_A4, MI_Bb4, MI_B4,
        MI_C5,  MI_Db5,  MI_D5,   MI_Eb5, MI_E5,
        MI_F5,
        MI_SUST
    ),

    [_RESERVE01] = LAYOUT(
        _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______,
        _______
    ),

    [_FN] = LAYOUT(
        _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,
        XXXXXXX,
        XXXXXXX
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE]        = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MI_TRSD, MI_TRSU) },
    [_RESERVE01]   = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______)  },
    [_FN]          = { ENCODER_CCW_CW(XXXXXXX, XXXXXXX), ENCODER_CCW_CW(MI_OCTD, MI_OCTU)  }
};
#endif


void my_init(void){
    //  Set octave to QK_MIDI_OCTAVE_0
    midi_config.octave = QK_MIDI_OCTAVE_0 - MIDI_OCTAVE_MIN;
    // avoid using 127 since it is used as a special number in some sound sources.
    midi_config.velocity = MIDI_INITIAL_VELOCITY;
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    midi_init();
    my_init();
}

void keyboard_post_init_user(void) {
    my_init();
};
