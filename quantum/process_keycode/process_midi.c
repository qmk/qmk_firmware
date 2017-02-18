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

#if 0
typedef struct {
    uint64_t low;
    uint64_t high;
} uint128_t;

#if 0
static void right_shift_uint128_t(uint128_t* val, uint8_t shift)
{
    uint64_t high_mask = ~0 >> (64 - shift);
    uint64_t high_bits = (val->high & high_mask) << (64 - shift);
    val->high = val->high >> shift;
    val->low = (val->low >> shift) | high_bits;
}
#endif

static uint64_t left_shift_uint64_t(uint64_t val, uint8_t shift)
{
    dprintf("left_shift_uint64_t(val, %c) ...\n", val, shift);
    while (shift > 16u) {
        dprintf("  left_shift_uint64_t: val=?, shift=%c\n", val, shift);
        val <<= 16;
        shift -= 16;
    }
    dprintf("  left_shift_uint64_t: val=?, shift=%c\n", val, shift);
    val <<= shift;
    return val;
}

static void set_bit_uint128_t(uint128_t* val, uint8_t shift)
{
    uint64_t x = 1u;

    if (shift < 64)
    {
        x = left_shift_uint64_t(x, shift);
        dprintf("x: %d\n", x);
        dprintf("set_bit_uint128_t (%d): 0x%016X%016X\n", shift, 0, x);
        val->low = val->low | left_shift_uint64_t(1u, shift);
    }
    else
    {
        x = left_shift_uint64_t(x, shift - 64);
        dprintf("set_bit_uint128_t (%d): 0x%016X%016X\n", shift, x, 0);
        val->high = val->high | left_shift_uint64_t(1u, shift - 64);
    }
}

static void clear_bit_uint128_t(uint128_t* val, uint8_t shift)
{
    if (shift < 64)
    {
        val->low = val->low & ~left_shift_uint64_t(1u, shift);
    }
    else
    {
        val->high = val->high & ~left_shift_uint64_t(1u, shift - 64);
    }
}

static bool is_bit_set_uint128_t(const uint128_t* val, uint8_t shift)
{
    if (shift < 64)
    {
        return !!(val->low & (1u << shift));
    }
    else
    {
        return !!(val->high & (1u << (shift - 64)));
    }
}

uint128_t note_status = { 0, 0 };
#endif


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
