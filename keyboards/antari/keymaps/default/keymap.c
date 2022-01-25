/* Copyright 2022 Sandipratama <https://github.com/nendezkombet>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "encoder.h"
#include "analog.h"
#include "midi.h"

extern MidiDevice midi_device;

int16_t pot_oldVal = 0;
int16_t pot_val    = 0;
int16_t pot_ccVal  = 0;
#define POT_TOLERANCE 12

void matrix_init_user(void) {
#ifdef POT_ENABLE
    analogReference(ADC_REF_POWER);
#endif
}


void matrix_scan_user(void) {
#ifdef POT_ENABLE
    pot_val   = (analogReadPin(SLIDER_PIN));
    pot_ccVal = pot_val / 8;
    if (abs(pot_val - pot_oldVal) > POT_TOLERANCE) {
       pot_oldVal = pot_val;
        midi_send_cc(&midi_device, 1, 0x30, pot_ccVal);
    }
#endif
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		TO(1), KC_B, KC_C, KC_D,
		KC_E, KC_F, KC_G, KC_H,
		KC_I, KC_J, KC_K, KC_L,
		KC_M, KC_N, KC_O, KC_P
	),
	[1] = LAYOUT(
		TO(2), KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	[2] = LAYOUT(
		TO(3), KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
	[3] = LAYOUT(
		TO(0), RGB_TOG, RGB_MOD, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
	),
};



bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
	    }
	}
    return true;
}

#ifdef AUDIO_ENABLE
float my_song1[][2]    = SONG(MUSIC_ON_SOUND);		
float my_song2[][2]    = SONG(VOICE_CHANGE_SOUND);
float my_song3[][2]    = SONG(GUITAR_SOUND);
float my_song4[][2]    = SONG(VIOLIN_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:
            #ifdef AUDIO_ENABLE
		_delay_ms(100);
          PLAY_SONG(my_song1);

        #endif
	break;
        case 1:
            #ifdef AUDIO_ENABLE
		_delay_ms(100);
          PLAY_SONG(my_song2);

        #endif
	break;
        case 2:
            #ifdef AUDIO_ENABLE
		_delay_ms(100);
          PLAY_SONG(my_song3);

        #endif
	break;
	case 3:
            #ifdef AUDIO_ENABLE
		_delay_ms(100);
          PLAY_SONG(my_song4);

        #endif
	break;
    }
    return state;
}


//qmk compile -kb antari -km default