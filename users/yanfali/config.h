#pragma once

#ifdef KEYBOARD_maartenwut_plain60

#define B7_AUDIO
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
