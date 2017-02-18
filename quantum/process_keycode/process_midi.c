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

#define MIDI_USE_NOTE_ON_ARRAY

#ifdef MIDI_USE_NOTE_ON_ARRAY

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

#else

#define MIDI_TONE_COUNT (MIDI_TONE_MAX - MIDI_TONE_MIN + 1)
static uint8_t tone_status[MIDI_TONE_COUNT];

#endif



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
            #ifdef MIDI_USE_NOTE_ON_ARRAY
            if (record->event.pressed && notes_on.length < MIDI_MAX_NOTES_ON) {
            #else
            if (record->event.pressed) {
            #endif
                uint8_t note = 12 * midi_config.octave + tone;
                midi_send_noteon(&midi_device, channel, note, velocity);
                dprintf("midi noteon channel:%d note:%d velocity:%d\n", channel, note, velocity);

                #ifdef MIDI_USE_NOTE_ON_ARRAY
                
                notes_on.values[notes_on.length].note = note;
                notes_on.values[notes_on.length].tone = tone;
                notes_on.length++;
                
                #else

                tone_status[tone] = note;

                #endif
            }
            else {
                
                #ifdef MIDI_USE_NOTE_ON_ARRAY

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

                #else

                uint8_t note = tone_status[tone];
                if (note != MIDI_INVALID_NOTE)
                {
                    midi_send_noteoff(&midi_device, channel, note, velocity);
                    dprintf("midi noteoff channel:%d note:%d velocity:%d\n", channel, note, velocity);
                }
                tone_status[tone] = MIDI_INVALID_NOTE;

                #endif
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

#if 0
    if (keycode == MI_ON && record->event.pressed) {
      midi_activated = true;
#ifdef AUDIO_ENABLE
      music_scale_user();
#endif
      return false;
    }

    if (keycode == MI_OFF && record->event.pressed) {
      midi_activated = false;
      midi_send_cc(&midi_device, 0, 0x7B, 0);
      return false;
    }

    if (midi_activated) {
      if (record->event.key.col == (MATRIX_COLS - 1) && record->event.key.row == (MATRIX_ROWS - 1)) {
          if (record->event.pressed) {
              midi_starting_note++; // Change key
              midi_send_cc(&midi_device, 0, 0x7B, 0);
          }
          return false;
      }
      if (record->event.key.col == (MATRIX_COLS - 2) && record->event.key.row == (MATRIX_ROWS - 1)) {
          if (record->event.pressed) {
              midi_starting_note--; // Change key
              midi_send_cc(&midi_device, 0, 0x7B, 0);
          }
          return false;
      }
      if (record->event.key.col == (MATRIX_COLS - 3) && record->event.key.row == (MATRIX_ROWS - 1) && record->event.pressed) {
          midi_offset++; // Change scale
          midi_send_cc(&midi_device, 0, 0x7B, 0);
          return false;
      }
      if (record->event.key.col == (MATRIX_COLS - 4) && record->event.key.row == (MATRIX_ROWS - 1) && record->event.pressed) {
          midi_offset--; // Change scale
          midi_send_cc(&midi_device, 0, 0x7B, 0);
          return false;
      }
      // basic
      // uint8_t note = (midi_starting_note + SCALE[record->event.key.col + midi_offset])+12*(MATRIX_ROWS - record->event.key.row);
      // advanced
      // uint8_t note = (midi_starting_note + record->event.key.col + midi_offset)+12*(MATRIX_ROWS - record->event.key.row);
      // guitar
      uint8_t note = (midi_starting_note + record->event.key.col + midi_offset)+5*(MATRIX_ROWS - record->event.key.row);
      // violin
      // uint8_t note = (midi_starting_note + record->event.key.col + midi_offset)+7*(MATRIX_ROWS - record->event.key.row);

      if (record->event.pressed) {
        // midi_send_noteon(&midi_device, record->event.key.row, midi_starting_note + SCALE[record->event.key.col], 127);
        midi_send_noteon(&midi_device, 0, note, 127);
      } else {
        // midi_send_noteoff(&midi_device, record->event.key.row, midi_starting_note + SCALE[record->event.key.col], 127);
        midi_send_noteoff(&midi_device, 0, note, 127);
      }

      if (keycode < 0xFF) // ignores all normal keycodes, but lets RAISE, LOWER, etc through
        return false;
    }
#endif
    return true;
}
