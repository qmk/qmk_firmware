#include "process_midi.h"

typedef union {
  uint16_t raw;
  struct {
    uint8_t octave   :4;
    uint8_t velocity :4;
    uint8_t channel  :4;
  };
} midi_config_t;

midi_config_t midi_config;

#define MIDI_INVALID_NOTE 0xFF

#define MIDI_TONE_COUNT (MIDI_TONE_MAX - MIDI_TONE_MIN + 1)
static uint8_t tone_status[MIDI_TONE_COUNT];

inline uint8_t compute_velocity(uint8_t setting)
{
    return (setting + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
}

void midi_init(void)
{
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;
    midi_config.velocity = (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN);
    midi_config.channel = 0;
    #ifdef MIDI_USE_NOTE_ON_ARRAY
    notes_on.length = 0;
    #else
    for (uint8_t i = 0; i < MIDI_TONE_COUNT; i++)
    {
        tone_status[i] = MIDI_INVALID_NOTE;
    }
    #endif
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
                uint8_t note = 12 * midi_config.octave + tone;
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
        case MI_OFF:
            if (record->event.pressed) {
                midi_send_cc(&midi_device, midi_config.channel, 0x7B, 0);
                dprintf("midi off\n");
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
    };

    return true;
}
