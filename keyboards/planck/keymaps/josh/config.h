#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(ZELDA_PUZZLE)
#endif

#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 15
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 10

#include "../../config.h"

#endif
