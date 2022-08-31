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

#include "giabalanaipico.h"

// the velocity difference from the velocity of the root note.
#define UNISON_VELOCITY_OFFSET 30

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
#       ifdef GIABARINAIPICO
        { NO_LED, NO_LED, 11,  10,  9,   8,   7,   NO_LED },
        { NO_LED, NO_LED, 12,  13,  14,  15,  16,  NO_LED },
        { NO_LED, NO_LED, 35,  34,  33,  32,  31,  NO_LED },
        { NO_LED, NO_LED, 36,  37,  38,  39,  40,  NO_LED },
        { NO_LED, NO_LED, 59,  58,  57,  56,  55,  NO_LED },

        { 0,      1,      2,   3,   4,   5,   6,   NO_LED },
        { 23,     22,     21,  20,  19,  18,  17,  NO_LED },
        { 24,     25,     26,  27,  28,  29,  30,  NO_LED },
        { 47,     46,     45,  44,  43,  42,  41,  NO_LED },
        { 48,     49,     50,  51,  52,  53,  54,  NO_LED },


        { 60,     61,     62,  63,  64,  65,  66,  NO_LED },
        { 84,     83,     82,  81,  80,  79,  78,  NO_LED },
        { 85,     86,     87,  88,  89,  90,  91,  NO_LED },
        { 110,    109,    108, 107, 106, 105, 104, NO_LED },
        { NO_LED, 111,    112, 113, 114, 115, 116, NO_LED },

        { NO_LED, NO_LED, 71,  70,  69,  68,  67,  NO_LED },
        { NO_LED, 72,     73,  74,  75,  76,  77,  NO_LED },
        { NO_LED, 97,     96,  95,  94,  93,  92,  NO_LED },
        { NO_LED, 98,     99, 100, 101, 102, 103,  NO_LED },
        { NO_LED, 122,    121, 120, 119, 118, 117, NO_LED }
    }, {
        {  88,  0 }, {  80,  0 }, {  72,  0 }, {  64,  0 }, {  56,  0 }, {  48,  0 }, {  40,  0 }, {  32,  0 }, {  24,  0 }, {  16,  0 }, {   8,  0 }, {   0,  0 },
        {   4, 16 }, {  12, 16 }, {  20, 16 }, {  28, 16 }, {  36, 16 }, {  44, 16 }, {  52, 16 }, {  60, 16 }, {  68, 16 }, {  76, 16 }, {  84, 16 }, {  92, 16 },
        {  96, 32 }, {  88, 32 }, {  80, 32 }, {  72, 32 }, {  64, 32 }, {  56, 32 }, {  48, 32 }, {  40, 32 }, {  32, 32 }, {  24, 32 }, {  16, 32 }, {   8, 32 },
        {  12, 48 }, {  20, 48 }, {  28, 48 }, {  36, 48 }, {  44, 48 }, {  52, 48 }, {  60, 48 }, {  68, 48 }, {  76, 48 }, {  84, 48 }, {  92, 48 }, { 100, 48 },
        { 104, 64 }, {  96, 64 }, {  88, 64 }, {  80, 64 }, {  72, 64 }, {  64, 64 }, {  56, 64 }, {  48, 64 }, {  40, 64 }, {  32, 64 }, {  24, 64 }, {  16, 64 },

        { 120,  0 }, { 128,  0 }, { 136,  0 }, { 144,  0 }, { 152,  0 }, { 160,  0 }, { 168,  0 }, { 176,  0 }, { 184,  0 }, { 192,  0 }, { 200,  0 }, { 208,  0 },
        { 212, 16 }, { 204, 16 }, { 196, 16 }, { 188, 16 }, { 180, 16 }, { 172, 16 }, { 164, 16 }, { 156, 16 }, { 148, 16 }, { 140, 16 }, { 132, 16 }, { 124, 16 }, { 116, 16 },
        { 120, 32 }, { 128, 32 }, { 136, 32 }, { 144, 32 }, { 152, 32 }, { 160, 32 }, { 168, 32 }, { 176, 32 }, { 184, 32 }, { 192, 32 }, { 200, 32 }, { 208, 32 },        { 224, 32 },
        { 212, 48 }, { 204, 48 }, { 196, 48 }, { 188, 48 }, { 180, 48 }, { 172, 48 }, { 164, 48 }, { 156, 48 }, { 148, 48 }, { 140, 48 }, { 132, 48 }, { 124, 48 }, { 116, 48 },
        { 120, 64 }, { 128, 64 }, { 136, 64 }, { 144, 64 }, { 152, 64 }, { 160, 64 }, { 168, 64 }, { 176, 64 }, { 184, 64 }, { 192, 64 }, { 200, 64 }, { 208, 64 }
    }, {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,

        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
#   else
        { NO_LED, NO_LED, 74,  73,  72,  71,  70,  NO_LED },
        { NO_LED, NO_LED, 75,  76,  77,  78,  79,  NO_LED },
        { NO_LED, NO_LED, 98,  97,  96,  95,  94,  NO_LED },
        { NO_LED, NO_LED, 99,  100, 101, 102, 103, NO_LED },
        { NO_LED, NO_LED, 122, 121, 120, 119, 118, NO_LED },

        { 63,     64,     65,  66,  67,  68,  69,  NO_LED },
        { 86,     85,     84,  83,  82,  81,  80,  NO_LED },
        { 87,     88,     89,  90,  91,  92,  93,  NO_LED },
        { 110,    109,    108, 107, 106, 105, 104, NO_LED },
        { 111,    112,    113, 114, 115, 116, 117, NO_LED },


        { 0,      1,      2,   3,   4,   5,   6,  NO_LED },
        { 24,     23,     22,  21,  20,  19,  18, NO_LED },
        { 25,     26,     27,  28,  29,  30,  31, NO_LED },
        { 50,     49,     48,  47,  46,  45,  44, NO_LED },
        { NO_LED, 51,     52,  53,  54,  55,  56, NO_LED },

        { NO_LED, NO_LED, 11,  10,  9,   8,   7,  NO_LED },
        { NO_LED, 12,     13,  14,  15,  16,  17, NO_LED },
        { NO_LED, 37,     36,  35,  34,  33,  32, NO_LED },
        { NO_LED, 38,     39,  40,  41,  42,  43, NO_LED },
        { NO_LED, 62,     61,  60,  59,  58,  57, NO_LED }
    }, {
        { 120,  0 }, { 128,  0 }, { 136,  0 }, { 144,  0 }, { 152,  0 }, { 160,  0 }, { 168,  0 }, { 176,  0 }, { 184,  0 }, { 192,  0 }, { 200,  0 }, { 208,  0 },
        { 212, 16 }, { 204, 16 }, { 196, 16 }, { 188, 16 }, { 180, 16 }, { 172, 16 }, { 164, 16 }, { 156, 16 }, { 148, 16 }, { 140, 16 }, { 132, 16 }, { 124, 16 }, { 116, 16 },
        { 120, 32 }, { 128, 32 }, { 136, 32 }, { 144, 32 }, { 152, 32 }, { 160, 32 }, { 168, 32 }, { 176, 32 }, { 184, 32 }, { 192, 32 }, { 200, 32 }, { 208, 32 },        { 224, 32 },
        { 212, 48 }, { 204, 48 }, { 196, 48 }, { 188, 48 }, { 180, 48 }, { 172, 48 }, { 164, 48 }, { 156, 48 }, { 148, 48 }, { 140, 48 }, { 132, 48 }, { 124, 48 }, { 116, 48 },
        { 120, 64 }, { 128, 64 }, { 136, 64 }, { 144, 64 }, { 152, 64 }, { 160, 64 }, { 168, 64 }, { 176, 64 }, { 184, 64 }, { 192, 64 }, { 200, 64 }, { 208, 64 },

        {  88,  0 }, {  80,  0 }, {  72,  0 }, {  64,  0 }, {  56,  0 }, {  48,  0 }, {  40,  0 }, {  32,  0 }, {  24,  0 }, {  16,  0 }, {   8,  0 }, {   0,  0 },
        {   4, 16 }, {  12, 16 }, {  20, 16 }, {  28, 16 }, {  36, 16 }, {  44, 16 }, {  52, 16 }, {  60, 16 }, {  68, 16 }, {  76, 16 }, {  84, 16 }, {  92, 16 },
        {  96, 32 }, {  88, 32 }, {  80, 32 }, {  72, 32 }, {  64, 32 }, {  56, 32 }, {  48, 32 }, {  40, 32 }, {  32, 32 }, {  24, 32 }, {  16, 32 }, {   8, 32 },
        {  12, 48 }, {  20, 48 }, {  28, 48 }, {  36, 48 }, {  44, 48 }, {  52, 48 }, {  60, 48 }, {  68, 48 }, {  76, 48 }, {  84, 48 }, {  92, 48 }, { 100, 48 },
        { 104, 64 }, {  96, 64 }, {  88, 64 }, {  80, 64 }, {  72, 64 }, {  64, 64 }, {  56, 64 }, {  48, 64 }, {  40, 64 }, {  32, 64 }, {  24, 64 }, {  16, 64 }
    }, {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,

        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
#   endif
};

#endif

void keyboard_pre_init_kb(void) {
    // https://beta.docs.qmk.fm/using-qmk/guides/custom_quantum_functions
    // https://beta.docs.qmk.fm/developing-qmk/c-development/internals_gpio_control
    // Set the handedness pin to low by default.
    // Left side keyboard will have an external wire shorted to 3.3V, to have HIGH state.
    setPinInputLow(SPLIT_HAND_PIN);
}

// void keyboard_post_init_kb(void) {
//     debug_enable = true;
//     debug_matrix = true;
//     debug_keyboard=true;
//     keyboard_post_init_user();
// }

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
