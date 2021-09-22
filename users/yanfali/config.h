#pragma once

#ifdef KEYBOARD_evyd13_plain60

#define AUDIO_PIN B7
#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(GUITAR_SOUND)
#endif

#endif

#ifdef KEYBOARD_xd84

#undef RGBLED_NUM
#define RGBLED_NUM 20

#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL

#endif
