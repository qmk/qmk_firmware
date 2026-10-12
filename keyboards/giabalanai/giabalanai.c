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

#include "giabalanai.h"

// the velocity difference from the velocity of the root note.
#define UNISON_VELOCITY_OFFSET 30

#ifdef RGBLIGHT_ENABLE
#    define NO_LED 255
/* Conversion map from keylocation (MATRIX_ROWS x2(split) x MATRIX_COLS) to led IDs.
  led IDs are the number starts "0" from upper left corner of left side,
  enumerated from left to right, from top to bottom.
  Then emumeration follows to the right side, starting from "60".

  Note that the conversion from physical LED serial alighment to
    the led IDs is done with RGBLIGHT_LED_MAP beforehand.                          */

#    ifdef GIABARINAIX2
const uint8_t PROGMEM convert_key_to_led[] =
{
    0,  12,  24,  36,  48,  11,  23,  35,  47,  59,
    1,  13,  25,  37,  49,  10,  22,  34,  46,  58,
    2,  14,  26,  38,  50,  9,   21,  33,  45,  57,
    3,  15,  27,  39,  51,  8,   20,  32,  44,  56,
    4,  16,  28,  40,  52,  7,   19,  31,  43,  55,
    5,  17,  29,  41,  53,  6,   18,  30,  42,  54,
  119, 107,  95,  83,  71, 108,  96,  84,  72,  60,
  118, 106,  94,  82,  70, 109,  97,  85,  73,  61,
  117, 105,  93,  81,  69, 110,  98,  86,  74,  62,
  116, 104,  92,  80,  68, 111,  99,  87,  75,  63,
  115, 103,  91,  79,  67, 112, 100,  88,  76,  64,
  114, 102,  90,  78,  66, 113, 101,  89,  77,  65
};

#    else
const uint8_t PROGMEM convert_key_to_led[] =
{
0,      12,    24,    36,    48,      11,    23,    35,     47,     59,
1,      13,    25,    37,    49,      10,    22,    34,     46,     58,
2,      14,    26,    38,    50,      9,     21,    33,     45,     57,
3,      15,    27,    39,    51,      8,     20,    32,     44,     56,
4,      16,    28,    40,    52,      7,     19,    31,     43,     55,
5,      17,    29,    41,    53,      6,     18,    30,     42,     54,

85,     86,    87,    88,    89,      90,    91,    NO_LED, NO_LED, NO_LED,
98,     99,    100,   101,   102,     103,   104,   NO_LED, NO_LED, NO_LED,
NO_LED, 111,   112,   113,   114,     115,   116,   NO_LED, NO_LED, NO_LED,
NO_LED, 97,    96,    95,    94,      93,    92,    NO_LED, NO_LED, NO_LED,
NO_LED, 110,   109,   108,   107,     106,   105,   NO_LED, NO_LED, NO_LED,
NO_LED, 122,   121,   120,   119,     118,   117,   NO_LED, NO_LED, NO_LED
};

/* Top 2 rows on the right side (LED:60-84) are
 duplicates of the bottom 2 rows (LED:85-122).
 LED:97 = Encoder,
 LED:110 don't have a duplicate on the top row,
 LED:72 is used when r20 is pressed (not a duplicate) */
const uint8_t PROGMEM convert_key_to_led2[] =
{
NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,

NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
60,     61,     62,     63,     64,       65,     66,     NO_LED, NO_LED, NO_LED,
72,     73,     74,     75,     76,       77,     78,     NO_LED, NO_LED, NO_LED,
NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,   NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,
NO_LED, NO_LED, 71,     70,     69,       68,     67,     NO_LED, NO_LED, NO_LED,
NO_LED, 84,     83,     82,     81,       80,     79,     NO_LED, NO_LED, NO_LED
};
#    endif
#endif  //  RGBLIGHT_ENABLE

void my_process_midi4Bass(uint8_t channel, keyrecord_t *record,
                          uint8_t *chord_status, uint8_t chord, uint16_t root_note, bool is_single_bass) {
    uint8_t velocity = midi_config.velocity;
    if (record->event.pressed) {
        if (chord_status[chord] == MIDI_INVALID_NOTE) {
            uint8_t note = midi_compute_note(root_note);
            if (is_single_bass) {
                midi_send_noteon(&midi_device, channel, note, velocity);
            } else {
                midi_send_noteon(&midi_device, channel, note, velocity);
                midi_send_noteon(&midi_device, channel, note + 12, velocity);  // +1 Octave
            }
            dprintf("midi noteon channel:%d note:%d velocity:%d\n", channel, note, velocity);
            chord_status[chord] = note;  // store root_note status.
        }
    } else {
        uint8_t note = chord_status[chord];
        if (note != MIDI_INVALID_NOTE) {
            if (is_single_bass) {
                midi_send_noteoff(&midi_device, channel, note, velocity);
            } else {
                midi_send_noteoff(&midi_device, channel, note, velocity);
                midi_send_noteoff(&midi_device, channel, note + 12, velocity);  // +1 Octave
            }
            dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
        }
        chord_status[chord] = MIDI_INVALID_NOTE;
    }
}

void my_process_midi4TriadChords(uint8_t channel, keyrecord_t *record,
                                 uint8_t *chord_status, uint8_t chord, uint16_t root_note,
                                 int8_t offset1, int8_t offset2, int8_t offset3) {
    uint8_t velocity = midi_config.velocity;
    if (record->event.pressed) {
        if (chord_status[chord] == MIDI_INVALID_NOTE) {
            uint8_t note = midi_compute_note(root_note);
            midi_send_noteon(&midi_device, channel, note + offset1, velocity);
            midi_send_noteon(&midi_device, channel, note + offset2, velocity);
            midi_send_noteon(&midi_device, channel, note + offset3, velocity);
            dprintf("midi noteon channel:%d note:%d velocity:%d\n", channel, note, velocity);
            chord_status[chord] = note;  // store root_note status.
        }
    } else {
        uint8_t note = chord_status[chord];
        if (note != MIDI_INVALID_NOTE) {
            midi_send_noteoff(&midi_device, channel, note + offset1, velocity);
            midi_send_noteoff(&midi_device, channel, note + offset2, velocity);
            midi_send_noteoff(&midi_device, channel, note + offset3, velocity);
            dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
        }
    chord_status[chord] = MIDI_INVALID_NOTE;
    }
}

void my_process_midi(uint8_t channel, uint16_t keycode, keyrecord_t *record, uint8_t *my_tone_status, int8_t offset, bool melody_unison_suppress) {

    uint8_t tone     = keycode - MIDI_TONE_MIN;

    uint8_t melody_unison_velocity;
    if (melody_unison_suppress) {
        if (midi_config.velocity > UNISON_VELOCITY_OFFSET){
            melody_unison_velocity = midi_config.velocity - UNISON_VELOCITY_OFFSET;
        } else {
            melody_unison_velocity = 0;
        }
    } else {
        melody_unison_velocity = midi_config.velocity;
    }

    if (record->event.pressed) {
        if (my_tone_status[tone] == MIDI_INVALID_NOTE) {
            uint8_t note = midi_compute_note(keycode);
            midi_send_noteon(&midi_device, channel, note + offset, melody_unison_velocity);
            dprintf("midi noteon channel:%d note:%d tone:%d velocity:%d\n", channel, note, tone, melody_unison_velocity);
            my_tone_status[tone] = note;  // store root_note status.
        }
    } else {
        uint8_t note = my_tone_status[tone];
        if (note != MIDI_INVALID_NOTE) {
            midi_send_noteoff(&midi_device, channel, note + offset, melody_unison_velocity);
            dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, melody_unison_velocity);
        }
    my_tone_status[tone] = MIDI_INVALID_NOTE;
    }
}

#ifdef RGBLIGHT_ENABLE
void keylight_manager(keyrecord_t *record, uint8_t hue, uint8_t sat, uint8_t val, uint8_t keylocation) {
    if (keylocation == NO_LED) {
        return;  // do nothing.
#    ifdef CONSOLE_ENABLE
        uprintf("keylight_manager, NO_LED\n");
#    endif
    }

    if (record->event.pressed) {
        rgblight_sethsv_at(hue, sat, val, keylocation);
    } else {
        rgblight_sethsv_at(HSV_BLACK, keylocation);
    }
}

#endif  // RGBLIGHT_ENABLE

