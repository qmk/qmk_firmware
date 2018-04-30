#include "audio.h"
#include "process_clicky.h"

#ifdef AUDIO_CLICKY

#ifdef AUDIO_CLICKY_ON
bool clicky_enable = true;
#else // AUDIO_CLICKY_ON
bool clicky_enable = false;
#endif // AUDIO_CLICKY_ON
#ifndef AUDIO_CLICKY_FREQ_DEFAULT
#define AUDIO_CLICKY_FREQ_DEFAULT 440.0f
#endif // !AUDIO_CLICKY_FREQ_DEFAULT
#ifndef AUDIO_CLICKY_FREQ_MIN
#define AUDIO_CLICKY_FREQ_MIN 65.0f
#endif // !AUDIO_CLICKY_FREQ_MIN
#ifndef AUDIO_CLICKY_FREQ_MAX
#define AUDIO_CLICKY_FREQ_MAX 1500.0f
#endif // !AUDIO_CLICKY_FREQ_MAX
#ifndef AUDIO_CLICKY_FREQ_FACTOR
#define AUDIO_CLICKY_FREQ_FACTOR 1.18921f
#endif // !AUDIO_CLICKY_FREQ_FACTOR
#ifndef AUDIO_CLICKY_FREQ_RANDOMNESS
#define AUDIO_CLICKY_FREQ_RANDOMNESS 0.05f
#endif // !AUDIO_CLICKY_FREQ_RANDOMNESS

float clicky_freq = AUDIO_CLICKY_FREQ_DEFAULT;
float clicky_song[][2]  = {{AUDIO_CLICKY_FREQ_DEFAULT, 3}, {AUDIO_CLICKY_FREQ_DEFAULT, 1}}; // 3 and 1 --> durations

#ifndef NO_MUSIC_MODE
extern bool music_activated;
extern bool midi_activated;
#endif // !NO_MUSIC_MODE

void clicky_play(void) {
#ifndef NO_MUSIC_MODE
  if (music_activated || midi_activated) return;
#endif // !NO_MUSIC_MODE
  clicky_song[0][0] = 2.0f * clicky_freq * (1.0f + AUDIO_CLICKY_FREQ_RANDOMNESS * ( ((float)rand()) / ((float)(RAND_MAX)) ) );
  clicky_song[1][0] = clicky_freq * (1.0f + AUDIO_CLICKY_FREQ_RANDOMNESS * ( ((float)rand()) / ((float)(RAND_MAX)) ) );
  PLAY_SONG(clicky_song);
}

bool process_clicky(uint16_t keycode, keyrecord_t *record) {
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


    if ( clicky_enable ) {
      if (record->event.pressed) {
        stop_all_notes();
        clicky_play();;
      }
    }
    return true;
}

#endif //AUDIO_CLICKY
