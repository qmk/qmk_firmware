/* Copyright 2020 3araht
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

#pragma once

#include "quantum.h"

#define _________________QWERTY_L1_________________ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________COLEMAK_L1________________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________ KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________ KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________ KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________NUMBER_L__________________ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _________________NUMBER_R__________________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________FUNC__L___________________ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC__R___________________ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

#ifdef RGBLIGHT_ENABLE

extern const uint8_t PROGMEM convert_key_to_led[];
#    ifndef GIABARINAIX2
extern const uint8_t PROGMEM convert_key_to_led2[];
#    endif
#endif  //  RGBLIGHT_ENABLE

// #ifdef RGB_MATRIX_ENABLE
// extern const uint8_t PROGMEM convert_led_location2number[];
// #endif

extern MidiDevice midi_device;
void my_process_midi4Bass(uint8_t channel, keyrecord_t *record,
                          uint8_t *chord_status, uint8_t chord, uint16_t root_note, bool is_single_bass);

void my_process_midi4TriadChords(uint8_t channel, keyrecord_t *record,
                                 uint8_t *chord_status, uint8_t chord, uint16_t root_note,
                                 int8_t offset1, int8_t offset2, int8_t offset3);

void my_process_midi(uint8_t channel, uint16_t keycode, keyrecord_t *record, uint8_t *my_tone_status, int8_t offset, bool melody_unison_suppress);


#ifdef RGBLIGHT_ENABLE
void keylight_manager(keyrecord_t *record, uint8_t hue, uint8_t sat, uint8_t val, uint8_t keylocation);
#endif  // RGBLIGHT_ENABLE
