#include "audio.h"
#include "process_audio.h"

#ifndef VOICE_CHANGE_SONG
    #define VOICE_CHANGE_SONG SONG(VOICE_CHANGE_SOUND)
#endif
float voice_change_song[][2] = VOICE_CHANGE_SONG;

#ifndef PITCH_STANDARD_A
    #define PITCH_STANDARD_A 440.0f
#endif

#ifdef AUDIO_CLICKY
#ifdef AUDIO_CLICKY_ON
bool clicky_enable = true;
#else
bool clicky_enable = false;
#endif
#ifndef AUDIO_CLICKY_FREQ_DEFAULT
#define AUDIO_CLICKY_FREQ_DEFAULT 440.0f
#endif
#ifndef AUDIO_CLICKY_FREQ_MIN
#define AUDIO_CLICKY_FREQ_MIN 65.0f
#endif
#ifndef AUDIO_CLICKY_FREQ_MAX
#define AUDIO_CLICKY_FREQ_MAX 1500.0f
#endif
#ifndef AUDIO_CLICKY_FREQ_FACTOR
#define AUDIO_CLICKY_FREQ_FACTOR 1.18921f
#endif
#ifndef AUDIO_CLICKY_FREQ_RANDOMNESS
#define AUDIO_CLICKY_FREQ_RANDOMNESS 0.05f
#endif

float clicky_freq = AUDIO_CLICKY_FREQ_DEFAULT;
float clicky_song[][2]  = {{AUDIO_CLICKY_FREQ_DEFAULT, 3}, {AUDIO_CLICKY_FREQ_DEFAULT, 1}}; // 3 and 1 --> durations

#ifndef NO_MUSIC_MODE
extern bool music_activated;
extern bool midi_activated;
#endif

void clicky_play(void) {
#ifndef NO_MUSIC_MODE
  if (music_activated || midi_activated) return;
#endif
  clicky_song[0][0] = 2.0f * clicky_freq * (1.0f + AUDIO_CLICKY_FREQ_RANDOMNESS * ( ((float)rand()) / ((float)(RAND_MAX)) ) );
  clicky_song[1][0] = clicky_freq * (1.0f + AUDIO_CLICKY_FREQ_RANDOMNESS * ( ((float)rand()) / ((float)(RAND_MAX)) ) );
  PLAY_SONG(clicky_song);
}
#endif

static float compute_freq_for_midi_note(uint8_t note)
{
    // https://en.wikipedia.org/wiki/MIDI_tuning_standard
    return pow(2.0, (note - 69) / 12.0) * PITCH_STANDARD_A;
}

bool process_audio(uint16_t keycode, keyrecord_t *record) {

    if (keycode == AU_ON && record->event.pressed) {
      audio_on();
      return false;
    }

    if (keycode == AU_OFF && record->event.pressed) {
      audio_off();
      return false;
    }

    if (keycode == AU_TOG && record->event.pressed) {
        if (is_audio_on()) {
            audio_off();
        } else {
            audio_on();
        }
        return false;
    }

    if (keycode == MUV_IN && record->event.pressed) {
        voice_iterate();
        PLAY_SONG(voice_change_song);
        return false;
    }

    if (keycode == MUV_DE && record->event.pressed) {
        voice_deiterate();
        PLAY_SONG(voice_change_song);
        return false;
    }

#ifdef AUDIO_CLICKY
    if (keycode == CLICKY_TOGGLE && record->event.pressed) { clicky_enable = !clicky_enable; }

    if (keycode == CLICKY_RESET && record->event.pressed) { clicky_freq = AUDIO_CLICKY_FREQ_DEFAULT; }

    if (keycode == CLICKY_UP && record->event.pressed) {
      float new_freq = clicky_freq * AUDIO_CLICKY_FREQ_FACTOR;
      if (new_freq < AUDIO_CLICKY_FREQ_MAX) {
        clicky_freq = new_freq;
      }
    }
    if (keycode == CLICKY_TOGGLE && record->event.pressed) {
      float new_freq = clicky_freq / AUDIO_CLICKY_FREQ_FACTOR;
      if (new_freq > AUDIO_CLICKY_FREQ_MIN) {
        clicky_freq = new_freq;
      }
      }


    if ( (clicky_enable && keycode != CLICKY_TOGGLE) || (!clicky_enable && keycode == CLICKY_TOGGLE) ) {
      if (record->event.pressed) {
        stop_all_notes();
        clicky_play();;
      }
    }
#endif // AUDIO_CLICKY

    return true;
}

void process_audio_noteon(uint8_t note) {
    play_note(compute_freq_for_midi_note(note), 0xF);
}

void process_audio_noteoff(uint8_t note) {
    stop_note(compute_freq_for_midi_note(note));
}

void process_audio_all_notes_off(void) {
    stop_all_notes();
}

__attribute__ ((weak))
void audio_on_user() {}
