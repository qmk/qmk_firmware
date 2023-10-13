#pragma once

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef AUDIO_ENABLE
  #define AUDIO_PIN B5
  #define STARTUP_SONG SONG(ONE_UP_SOUND)
  #define NO_MUSIC_MODE
#endif

#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 12
