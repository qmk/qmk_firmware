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

#include "yellowbrickroad.h"

// the velocity difference from the velocity of the root note.
#define UNISON_VELOCITY_OFFSET 30

#ifdef RGB_MATRIX_ENABLE
#    define NO_LED 255

led_config_t g_led_config = {
    {
        { 0,      1,      2,      3,      4,      5,      6,      7      },
        { 8,      9,      10,     11,     12,     13,     14,     15     },
        { 16,     17,     18,     19,     20,     21,     22,     23     },
        { 24,     25,     26,     27,     28,     29,     30,     31     },
        { 32,     33,     34,     35,     36,     37,     38,     39     },
        { 40,     41,     42,     43,     44,     45,     46,     47     },
        { 48,     49,     50,     51,     52,     53,     54,     55     }
    }, {
        { 0,  0 },
        { 4,  0 },  { 8,   0 }, { 12,  0 }, { 16,  0 }, { 20,  0 }, { 24,  0 }, { 28,  0 }, { 32,  0 }, { 36,  0 }, { 40,  0 },
        { 44, 0 },  { 48,  0 }, { 52,  0 }, { 56,  0 }, { 60,  0 }, { 64,  0 }, { 68,  0 }, { 72,  0 }, { 76,  0 }, { 80,  0 },
        { 84,  0 }, { 88, 0 },  { 92,  0 }, { 96,  0 }, { 100, 0 }, { 104, 0 }, { 108, 0 }, { 112, 0 }, { 116, 0 }, { 120, 0 },
        { 124, 0 }, { 128, 0 }, { 132, 0 }, { 136, 0 }, { 140, 0 }, { 144, 0 }, { 148, 0 }, { 152, 0 }, { 156, 0 }, { 160, 0 },
        { 164, 0 }, { 168, 0 }, { 172, 0 }, { 176, 0 }, { 180, 0 }, { 188, 0 }, { 192, 0 }, { 196, 0 }, { 200, 0 }, { 204, 0 },
        { 208, 0 }, { 212, 0 }, { 216, 0 },
        { 220, 0 },
        { 224, 0 },
    }, {
        4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4,
        4,
        4,
    }
};

// C indicator
const uint8_t led_c_indicator[3][12][MAXCINDICATORLED] = {
    {   // chromatic scale
        {       1,     13,     25,     37,     49, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {       2,     14,     26,     38,     50, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {       3,     15,     27,     39,     51, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {       4,     16,     28,     40,     52, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {       5,     17,     29,     41,     53, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {       6,     18,     30,     42, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {       7,     19,     31,     43, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {       8,     20,     32,     44, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {       9,     21,     33,     45, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {      10,     22,     34,     46, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {      11,     23,     35,     47, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {      12,     24,     36,     48, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
    },
    {   // heptatonic scale
        {       1,     8,      15,     22,     29,     36,     43,     50, NO_LED, NO_LED, NO_LED },
        {       2,     9,      16,     23,     30,     37,     44,     51, NO_LED, NO_LED, NO_LED },
        {       3,     10,     17,     24,     31,     38,     45,     52, NO_LED, NO_LED, NO_LED },
        {       4,     11,     18,     25,     32,     39,     46,     53, NO_LED, NO_LED, NO_LED },
        {       5,     12,     19,     26,     33,     40,     47, NO_LED, NO_LED, NO_LED, NO_LED },
        {       6,     13,     20,     27,     34,     41,     48, NO_LED, NO_LED, NO_LED, NO_LED },
        {       7,     14,     21,     28,     35,     42,     49, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
    },
    {   // pentatonic scale
        {       1,      6,     11,     16,     21,     26,     31,     36,     41,     46,     51 },
        {       2,      7,     12,     17,     22,     27,     32,     37,     42,     47,     52 },
        {       3,      8,     13,     18,     23,     28,     33,     38,     43,     48,     53 },
        {       4,      9,     14,     19,     24,     29,     34,     39,     44,     49, NO_LED },
        {       5,     10,     15,     20,     25,     30,     35,     40,     45,     50, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
    }
};
#endif  //  RGB_MATRIX_ENABLE


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

uint8_t shift_led_indicator_left(uint8_t scale_indicator_col, uint8_t upperlimit){
    if (scale_indicator_col > 0) {
        scale_indicator_col--;
    } else {
        scale_indicator_col = upperlimit;
    }
    return scale_indicator_col;
}

uint8_t shift_led_indicator_right(uint8_t scale_indicator_col, uint8_t upperlimit){
    if (scale_indicator_col < upperlimit) {
        scale_indicator_col++;
    } else {
        scale_indicator_col = 0;
    }
    return scale_indicator_col;
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
