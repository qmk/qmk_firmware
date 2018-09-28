#include "audio.h"
#include "process_clicky.h"

#ifdef AUDIO_CLICKY

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
float clicky_rand = AUDIO_CLICKY_FREQ_RANDOMNESS;
float clicky_song[][2]  = {{AUDIO_CLICKY_FREQ_DEFAULT, 3}, {AUDIO_CLICKY_FREQ_DEFAULT, 1}}; // 3 and 1 --> durations

extern audio_config_t audio_config;

#ifndef NO_MUSIC_MODE
extern bool music_activated;
extern bool midi_activated;
#endif // !NO_MUSIC_MODE

void clicky_play(void) {
#ifndef NO_MUSIC_MODE
  if (music_activated || midi_activated) return;
#endif // !NO_MUSIC_MODE
  clicky_song[0][0] = 2.0f * clicky_freq * (1.0f + clicky_rand * ( ((float)rand()) / ((float)(RAND_MAX)) ) );
  clicky_song[1][0] = clicky_freq * (1.0f + clicky_rand * ( ((float)rand()) / ((float)(RAND_MAX)) ) );
  PLAY_SONG(clicky_song);
}

void clicky_freq_up(void) {
  float new_freq = clicky_freq * AUDIO_CLICKY_FREQ_FACTOR;
  if (new_freq < AUDIO_CLICKY_FREQ_MAX) {
    clicky_freq = new_freq;
  }
}

void clicky_freq_down(void) {
  float new_freq = clicky_freq / AUDIO_CLICKY_FREQ_FACTOR;
  if (new_freq > AUDIO_CLICKY_FREQ_MIN) {
    clicky_freq = new_freq;
  }
}

void clicky_freq_reset(void) {
  clicky_freq = AUDIO_CLICKY_FREQ_DEFAULT;
}

void clicky_toggle(void) {
  audio_config.clicky_enable ^= 1;
  eeconfig_update_audio(audio_config.raw);
}

void clicky_on(void) {
  audio_config.clicky_enable = 1;
  eeconfig_update_audio(audio_config.raw);
}

void clicky_off(void) {
  audio_config.clicky_enable = 0;
  eeconfig_update_audio(audio_config.raw);
}

bool is_clicky_on(void) {
      return (audio_config.clicky_enable != 0);
}

bool process_clicky(uint16_t keycode, keyrecord_t *record) {
    if (keycode == CLICKY_TOGGLE && record->event.pressed) { clicky_toggle(); }

    if (keycode == CLICKY_ENABLE && record->event.pressed) { clicky_on(); }
    if (keycode == CLICKY_DISABLE && record->event.pressed) { clicky_off(); }

    if (keycode == CLICKY_RESET && record->event.pressed) { clicky_freq_reset(); }

    if (keycode == CLICKY_UP && record->event.pressed) { clicky_freq_up(); }
    if (keycode == CLICKY_DOWN && record->event.pressed) { clicky_freq_down(); }


    if ( audio_config.clicky_enable ) {
      if (record->event.pressed) {
        clicky_play();;
      }
    }
    return true;
}

#endif //AUDIO_CLICKY
