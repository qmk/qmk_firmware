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

#ifdef MIDI_ENABLE
#include "midi.h"

#ifdef MIDI_BASIC

void process_midi_basic_noteon(uint8_t note) 
{
    midi_send_noteon(&midi_device, 0, note, 128);
}

void process_midi_basic_noteoff(uint8_t note)
{
    midi_send_noteoff(&midi_device, 0, note, 0);
}

void process_midi_all_notes_off(void)
{
    midi_send_cc(&midi_device, 0, 0x7B, 0);
}

#endif // MIDI_BASIC

#ifdef MIDI_ADVANCED

#include "timer.h"

static uint8_t tone_status[MIDI_TONE_COUNT];

static uint8_t midi_modulation;
static int8_t midi_modulation_step;
static uint16_t midi_modulation_timer;

inline uint8_t compute_velocity(uint8_t setting)
{
    return (setting + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
}

void midi_init(void)
{
    midi_config.octave = MI_OCT_2 - MIDI_OCTAVE_MIN;
    midi_config.transpose = 0;
    midi_config.velocity = (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN);
    midi_config.channel = 0;
    midi_config.modulation_interval = 8;

    for (uint8_t i = 0; i < MIDI_TONE_COUNT; i++)
    {
        tone_status[i] = MIDI_INVALID_NOTE;
    }

    midi_modulation = 0;
    midi_modulation_step = 0;
    midi_modulation_timer = 0;
}

void midi_task(void)
{
    if (timer_elapsed(midi_modulation_timer) < midi_config.modulation_interval)
        return;
    midi_modulation_timer = timer_read();

    if (midi_modulation_step != 0)
    {
        dprintf("midi modulation %d\n", midi_modulation);
        midi_send_cc(&midi_device, midi_config.channel, 0x1, midi_modulation);

        if (midi_modulation_step < 0 && midi_modulation < -midi_modulation_step) {
            midi_modulation = 0;
            midi_modulation_step = 0;
            return;
        }

        midi_modulation += midi_modulation_step;

        if (midi_modulation > 127)
            midi_modulation = 127;
    }
}

uint8_t midi_compute_note(uint16_t keycode)
{
    return 12 * midi_config.octave + (keycode - MIDI_TONE_MIN) + midi_config.transpose;
}

bool process_midi(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case MIDI_TONE_MIN ... MIDI_TONE_MAX:
        {
            uint8_t channel = midi_config.channel;
            uint8_t tone = keycode - MIDI_TONE_MIN;
            uint8_t velocity = compute_velocity(midi_config.velocity);
            if (record->event.pressed) {
                uint8_t note = midi_compute_note(keycode);
                midi_send_noteon(&midi_device, channel, note, velocity);
                dprintf("midi noteon channel:%d note:%d velocity:%d\n", channel, note, velocity);
                tone_status[tone] = note;
            }
            else {
                uint8_t note = tone_status[tone];
                if (note != MIDI_INVALID_NOTE)
                {
                    midi_send_noteoff(&midi_device, channel, note, velocity);
                    dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
                }
                tone_status[tone] = MIDI_INVALID_NOTE;
            }
            return false;
        }
        case MIDI_OCTAVE_MIN ... MIDI_OCTAVE_MAX:
            if (record->event.pressed) {
                midi_config.octave = keycode - MIDI_OCTAVE_MIN;
                dprintf("midi octave %d\n", midi_config.octave);
            }
            return false;
        case MI_OCTD:
            if (record->event.pressed && midi_config.octave > 0) {
                midi_config.octave--;
                dprintf("midi octave %d\n", midi_config.octave);
            }
            return false;
        case MI_OCTU:
            if (record->event.pressed && midi_config.octave < (MIDI_OCTAVE_MAX - MIDI_OCTAVE_MIN)) {
                midi_config.octave++;
                dprintf("midi octave %d\n", midi_config.octave);
            }
            return false;
        case MIDI_TRANSPOSE_MIN ... MIDI_TRANSPOSE_MAX:
            if (record->event.pressed) {
                midi_config.transpose = keycode - MI_TRNS_0;
                dprintf("midi transpose %d\n", midi_config.transpose);
            }
            return false;
        case MI_TRNSD:
            if (record->event.pressed && midi_config.transpose > (MIDI_TRANSPOSE_MIN - MI_TRNS_0)) {
                midi_config.transpose--;
                dprintf("midi transpose %d\n", midi_config.transpose);
            }
            return false;
        case MI_TRNSU:
            if (record->event.pressed && midi_config.transpose < (MIDI_TRANSPOSE_MAX - MI_TRNS_0)) {
                const bool positive = midi_config.transpose > 0;
                midi_config.transpose++;
                if (positive && midi_config.transpose < 0)
                    midi_config.transpose--;
                dprintf("midi transpose %d\n", midi_config.transpose);
            }
            return false;
        case MIDI_VELOCITY_MIN ... MIDI_VELOCITY_MAX:
            if (record->event.pressed) {
                midi_config.velocity = keycode - MIDI_VELOCITY_MIN;
                dprintf("midi velocity %d\n", midi_config.velocity);
            }
            return false;
        case MI_VELD:
            if (record->event.pressed && midi_config.velocity > 0) {
                midi_config.velocity--;
                dprintf("midi velocity %d\n", midi_config.velocity);
            }
            return false;
        case MI_VELU:
            if (record->event.pressed) {
                midi_config.velocity++;
                dprintf("midi velocity %d\n", midi_config.velocity);
            }
            return false;
        case MIDI_CHANNEL_MIN ... MIDI_CHANNEL_MAX:
            if (record->event.pressed) {
                midi_config.channel = keycode - MIDI_CHANNEL_MIN;
                dprintf("midi channel %d\n", midi_config.channel);
            }
            return false;
        case MI_CHD:
            if (record->event.pressed) {
                midi_config.channel--;
                dprintf("midi channel %d\n", midi_config.channel);
            }
            return false;
        case MI_CHU:
            if (record->event.pressed) {
                midi_config.channel++;
                dprintf("midi channel %d\n", midi_config.channel);
            }
            return false;
        case MI_ALLOFF:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 0x7B, 0);
                dprintf("midi all notes off\n");
            }
            return false;
        case MI_SUS:
            midi_send_cc(&midi_device, midi_config.channel, 0x40, record->event.pressed ? 127 : 0);
            dprintf("midi sustain %d\n", record->event.pressed);
            return false;
        case MI_PORT:
            midi_send_cc(&midi_device, midi_config.channel, 0x41, record->event.pressed ? 127 : 0);
            dprintf("midi portamento %d\n", record->event.pressed);
            return false;
        case MI_SOST:
            midi_send_cc(&midi_device, midi_config.channel, 0x42, record->event.pressed ? 127 : 0);
            dprintf("midi sostenuto %d\n", record->event.pressed);
            return false;
        case MI_SOFT:
            midi_send_cc(&midi_device, midi_config.channel, 0x43, record->event.pressed ? 127 : 0);
            dprintf("midi soft %d\n", record->event.pressed);
            return false;
        case MI_LEG:
            midi_send_cc(&midi_device, midi_config.channel, 0x43, record->event.pressed ? 127 : 0);
            dprintf("midi legato %d\n", record->event.pressed);
            return false;
        case MI_MOD:
            midi_modulation_step = record->event.pressed ? 1 : -1;
            return false;
        case MI_MODSD:
            if (record->event.pressed) {
                midi_config.modulation_interval++;
                // prevent overflow
                if (midi_config.modulation_interval == 0)
                    midi_config.modulation_interval--;
                dprintf("midi modulation interval %d\n", midi_config.modulation_interval);
            }
            return false;
        case MI_MODSU:
            if (record->event.pressed && midi_config.modulation_interval > 0) {
                midi_config.modulation_interval--;
                dprintf("midi modulation interval %d\n", midi_config.modulation_interval);
            }
            return false;
    };

    return true;
}

#endif // MIDI_ADVANCED

#endif // MIDI_ENABLE
