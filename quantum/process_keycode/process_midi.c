/* Copyright 2016 Jack Humbert
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
#include "process_midi.h"

#include <LUFA/Drivers/USB/USB.h>
#include "midi.h"
#include "qmk_midi.h"
#include "timer.h"
#include "debug.h"

#ifdef MIDI_BASIC

void process_midi_basic_noteon(uint8_t note) {
    midi_send_noteon(&midi_device, 0, note, 127);
}

void process_midi_basic_noteoff(uint8_t note) {
    midi_send_noteoff(&midi_device, 0, note, 0);
}

void process_midi_all_notes_off(void) {
    midi_send_cc(&midi_device, 0, 0x7B, 0);
}

#endif // MIDI_BASIC

#ifdef MIDI_ADVANCED
static uint8_t tone_status[2][MIDI_TONE_COUNT];

static uint8_t  midi_modulation;
static int8_t   midi_modulation_step;
static uint16_t midi_modulation_timer;
midi_config_t   midi_config;

inline uint8_t compute_velocity(uint8_t setting) {
    return setting * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN));
}

void midi_init(void) {
    midi_config.octave              = QK_MIDI_OCTAVE_2 - MIDI_OCTAVE_MIN;
    midi_config.transpose           = 0;
    midi_config.velocity            = 127;
    midi_config.channel             = 0;
    midi_config.modulation_interval = 8;

    for (uint8_t i = 0; i < MIDI_TONE_COUNT; i++) {
        tone_status[0][i] = MIDI_INVALID_NOTE;
        tone_status[1][i] = 0;
    }

    midi_modulation       = 0;
    midi_modulation_step  = 0;
    midi_modulation_timer = 0;
}

uint8_t midi_compute_note(uint16_t keycode) {
    return 12 * midi_config.octave + (keycode - MIDI_TONE_MIN) + midi_config.transpose;
}

bool process_midi(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MIDI_TONE_MIN ... MIDI_TONE_MAX: {
            uint8_t channel  = midi_config.channel;
            uint8_t tone     = keycode - MIDI_TONE_MIN;
            uint8_t velocity = midi_config.velocity;
            if (record->event.pressed) {
                uint8_t note = midi_compute_note(keycode);
                midi_send_noteon(&midi_device, channel, note, velocity);
                dprintf("midi noteon channel:%d note:%d velocity:%d\n", channel, note, velocity);
                tone_status[1][tone] += 1;
                if (tone_status[0][tone] == MIDI_INVALID_NOTE) {
                    tone_status[0][tone] = note;
                }
            } else {
                uint8_t note = tone_status[0][tone];
                tone_status[1][tone] -= 1;
                if (tone_status[1][tone] == 0) {
                    midi_send_noteoff(&midi_device, channel, note, velocity);
                    dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
                    tone_status[0][tone] = MIDI_INVALID_NOTE;
                }
            }
            return false;
        }
        case MIDI_OCTAVE_MIN ... MIDI_OCTAVE_MAX:
            if (record->event.pressed) {
                midi_config.octave = keycode - MIDI_OCTAVE_MIN;
                dprintf("midi octave %d\n", midi_config.octave);
            }
            return false;
        case QK_MIDI_OCTAVE_DOWN:
            if (record->event.pressed && midi_config.octave > 0) {
                midi_config.octave--;
                dprintf("midi octave %d\n", midi_config.octave);
            }
            return false;
        case QK_MIDI_OCTAVE_UP:
            if (record->event.pressed && midi_config.octave < (MIDI_OCTAVE_MAX - MIDI_OCTAVE_MIN)) {
                midi_config.octave++;
                dprintf("midi octave %d\n", midi_config.octave);
            }
            return false;
        case MIDI_TRANSPOSE_MIN ... MIDI_TRANSPOSE_MAX:
            if (record->event.pressed) {
                midi_config.transpose = keycode - QK_MIDI_TRANSPOSE_0;
                dprintf("midi transpose %d\n", midi_config.transpose);
            }
            return false;
        case QK_MIDI_TRANSPOSE_DOWN:
            if (record->event.pressed && midi_config.transpose > (MIDI_TRANSPOSE_MIN - QK_MIDI_TRANSPOSE_0)) {
                midi_config.transpose--;
                dprintf("midi transpose %d\n", midi_config.transpose);
            }
            return false;
        case QK_MIDI_TRANSPOSE_UP:
            if (record->event.pressed && midi_config.transpose < (MIDI_TRANSPOSE_MAX - QK_MIDI_TRANSPOSE_0)) {
                const bool positive = midi_config.transpose > 0;
                midi_config.transpose++;
                if (positive && midi_config.transpose < 0) midi_config.transpose--;
                dprintf("midi transpose %d\n", midi_config.transpose);
            }
            return false;
        case MIDI_VELOCITY_MIN ... MIDI_VELOCITY_MAX:
            if (record->event.pressed) {
                midi_config.velocity = compute_velocity(keycode - MIDI_VELOCITY_MIN);
                dprintf("midi velocity %d\n", midi_config.velocity);
            }
            return false;
        case QK_MIDI_VELOCITY_DOWN:
            if (record->event.pressed && midi_config.velocity > 0) {
                if (midi_config.velocity == 127) {
                    midi_config.velocity -= 10;
                } else if (midi_config.velocity > 12) {
                    midi_config.velocity -= 13;
                } else {
                    midi_config.velocity = 0;
                }

                dprintf("midi velocity %d\n", midi_config.velocity);
            }
            return false;
        case QK_MIDI_VELOCITY_UP:
            if (record->event.pressed && midi_config.velocity < 127) {
                if (midi_config.velocity < 115) {
                    midi_config.velocity += 13;
                } else {
                    midi_config.velocity = 127;
                }
                dprintf("midi velocity %d\n", midi_config.velocity);
            }
            return false;
        case MIDI_CHANNEL_MIN ... MIDI_CHANNEL_MAX:
            if (record->event.pressed) {
                midi_config.channel = keycode - MIDI_CHANNEL_MIN;
                dprintf("midi channel %d\n", midi_config.channel);
            }
            return false;
        case QK_MIDI_CHANNEL_DOWN:
            if (record->event.pressed) {
                midi_config.channel--;
                dprintf("midi channel %d\n", midi_config.channel);
            }
            return false;
        case QK_MIDI_CHANNEL_UP:
            if (record->event.pressed) {
                midi_config.channel++;
                dprintf("midi channel %d\n", midi_config.channel);
            }
            return false;
        case QK_MIDI_ALL_NOTES_OFF:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 0x7B, 0);
                dprintf("midi all notes off\n");
            }
            return false;
        case QK_MIDI_SUSTAIN:
            midi_send_cc(&midi_device, midi_config.channel, 0x40, record->event.pressed ? 127 : 0);
            dprintf("midi sustain %d\n", record->event.pressed);
            return false;
        case QK_MIDI_PORTAMENTO:
            midi_send_cc(&midi_device, midi_config.channel, 0x41, record->event.pressed ? 127 : 0);
            dprintf("midi portamento %d\n", record->event.pressed);
            return false;
        case QK_MIDI_SOSTENUTO:
            midi_send_cc(&midi_device, midi_config.channel, 0x42, record->event.pressed ? 127 : 0);
            dprintf("midi sostenuto %d\n", record->event.pressed);
            return false;
        case QK_MIDI_SOFT:
            midi_send_cc(&midi_device, midi_config.channel, 0x43, record->event.pressed ? 127 : 0);
            dprintf("midi soft %d\n", record->event.pressed);
            return false;
        case QK_MIDI_LEGATO:
            midi_send_cc(&midi_device, midi_config.channel, 0x44, record->event.pressed ? 127 : 0);
            dprintf("midi legato %d\n", record->event.pressed);
            return false;
        case QK_MIDI_MODULATION:
            midi_modulation_step = record->event.pressed ? 1 : -1;
            return false;
        case QK_MIDI_MODULATION_SPEED_DOWN:
            if (record->event.pressed) {
                midi_config.modulation_interval++;
                // prevent overflow
                if (midi_config.modulation_interval == 0) midi_config.modulation_interval--;
                dprintf("midi modulation interval %d\n", midi_config.modulation_interval);
            }
            return false;
        case QK_MIDI_MODULATION_SPEED_UP:
            if (record->event.pressed && midi_config.modulation_interval > 0) {
                midi_config.modulation_interval--;
                dprintf("midi modulation interval %d\n", midi_config.modulation_interval);
            }
            return false;
        case QK_MIDI_PITCH_BEND_DOWN:
            if (record->event.pressed) {
                midi_send_pitchbend(&midi_device, midi_config.channel, -0x2000);
                dprintf("midi pitchbend channel:%d amount:%d\n", midi_config.channel, -0x2000);
            } else {
                midi_send_pitchbend(&midi_device, midi_config.channel, 0);
                dprintf("midi pitchbend channel:%d amount:%d\n", midi_config.channel, 0);
            }
            return false;
        case QK_MIDI_PITCH_BEND_UP:
            if (record->event.pressed) {
                midi_send_pitchbend(&midi_device, midi_config.channel, 0x1fff);
                dprintf("midi pitchbend channel:%d amount:%d\n", midi_config.channel, 0x1fff);
            } else {
                midi_send_pitchbend(&midi_device, midi_config.channel, 0);
                dprintf("midi pitchbend channel:%d amount:%d\n", midi_config.channel, 0);
            }
            return false;
    };

    return true;
}

#endif // MIDI_ADVANCED

void midi_task(void) {
    midi_device_process(&midi_device);
#ifdef MIDI_ADVANCED
    if (timer_elapsed(midi_modulation_timer) < midi_config.modulation_interval) return;
    midi_modulation_timer = timer_read();

    if (midi_modulation_step != 0) {
        dprintf("midi modulation %d\n", midi_modulation);
        midi_send_cc(&midi_device, midi_config.channel, 0x1, midi_modulation);

        if (midi_modulation_step < 0 && midi_modulation < -midi_modulation_step) {
            midi_modulation      = 0;
            midi_modulation_step = 0;
            return;
        }

        midi_modulation += midi_modulation_step;

        if (midi_modulation > 127) midi_modulation = 127;
    }
#endif
}
