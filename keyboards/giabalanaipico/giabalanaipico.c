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

#include "giabalanaipico.h"

// the velocity difference from the velocity of the root note.
#define UNISON_VELOCITY_OFFSET 30

void keyboard_pre_init_kb(void) {
    // https://beta.docs.qmk.fm/using-qmk/guides/custom_quantum_functions
    // https://beta.docs.qmk.fm/developing-qmk/c-development/internals_gpio_control
    // Set the handedness pin to low by default.
    // Left side keyboard will have an external wire shorted to 3.3V, to have HIGH state.
    setPinInputLow(SPLIT_HAND_PIN);

    keyboard_pre_init_user();
}

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
