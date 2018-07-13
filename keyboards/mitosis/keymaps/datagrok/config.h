#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// TODO: figure out which of these I can safely enable to reduce firmware size.
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT // can't; errors
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)
// #define STARTUP_SONG SONG(NO_SOUND)
#define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND),   \
                              SONG(COLEMAK_SOUND),  \
                              SONG(DVORAK_SOUND)    \
  }
#define AUDIO_VOICES
#define AUDIO_CLICKY
#define C6_AUDIO
#endif

#endif
