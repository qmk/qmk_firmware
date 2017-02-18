#include "process_midi.h"

#if 0
bool midi_activated = false;
uint8_t midi_starting_note = 0x0C;
int midi_offset = 7;
#endif

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

#define MIDI_MAX_NOTES_ON 10

typedef struct {
    uint8_t note;
    uint8_t tone;
} midi_notes_on_array_entry_t;

typedef struct {
    uint8_t length;
    midi_notes_on_array_entry_t values[MIDI_MAX_NOTES_ON];
} midi_notes_on_array_t;

static midi_notes_on_array_t notes_on;

inline uint8_t compute_velocity(uint8_t setting)
{
    return (setting + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
}

void midi_init(void)
{
    midi_config.octave = MI_OCT_0 - MIDI_OCTAVE_MIN;
    midi_config.velocity = (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN);
    midi_config.channel = 0;
    notes_on.length = 0;
}

bool process_midi(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case MIDI_TONE_MIN ... MIDI_TONE_MAX:
        {
            uint8_t channel = midi_config.channel;
            uint8_t tone = keycode - MIDI_TONE_MIN;
            uint8_t velocity = compute_velocity(midi_config.velocity);
            if (record->event.pressed && notes_on.length < MIDI_MAX_NOTES_ON) {
                uint8_t note = 12 * midi_config.octave + tone;
                midi_send_noteon(&midi_device, channel, note, velocity);
                dprintf("midi noteon channel:%d note:%d velocity:%d\n", channel, note, velocity);
                notes_on.values[notes_on.length].note = note;
                notes_on.values[notes_on.length].tone = tone;
                notes_on.length++;
            }
            else {
                for (uint8_t i = 0; i < notes_on.length; i++) {
                    uint8_t note = notes_on.values[i].note;
                    if (tone == notes_on.values[i].tone) {
                        midi_send_noteoff(&midi_device, channel, note, velocity);
                        dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);

                        for (uint8_t j=i; j < notes_on.length - 1; j++)
                        {
                            notes_on.values[j] = notes_on.values[j + 1];
                        }

                        notes_on.length--;
                        break;
                    }
                }
            }
            return false;
        }
        case MIDI_OCTAVE_MIN ... MIDI_OCTAVE_MAX:
            if (record->event.pressed)
                midi_config.octave = keycode - MIDI_OCTAVE_MIN;
            return false;
        case MI_OCTD:
            if (record->event.pressed && midi_config.octave > 0)
                midi_config.octave--;
            return false;
        case MI_OCTU:
            if (record->event.pressed && midi_config.octave < (MIDI_OCTAVE_MAX - MIDI_OCTAVE_MIN))
                midi_config.octave++;
            return false;
        case MIDI_VELOCITY_MIN ... MIDI_VELOCITY_MAX:
            if (record->event.pressed)
                midi_config.velocity = keycode - MIDI_VELOCITY_MIN;
            return false;
        case MI_VELD:
            if (record->event.pressed && midi_config.velocity > 0)
                midi_config.velocity--;
            return false;
        case MI_VELU:
            if (record->event.pressed)
                midi_config.velocity++;
            return false;
        case MIDI_CHANNEL_MIN ... MIDI_CHANNEL_MAX:
            if (record->event.pressed)
                midi_config.channel = keycode - MIDI_CHANNEL_MIN;
            return false;
        case MI_CHD:
            if (record->event.pressed)
                midi_config.channel--;
            return false;
        case MI_CHU:
            if (record->event.pressed)
                midi_config.channel++;
            return false;
        case MI_SUS:
            //TODO
            return false;
    };

    return true;
}
