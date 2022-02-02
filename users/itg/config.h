
#pragma once
#ifdef AUDIO_ENABLE
  #include "audio.h"
  #define STARTUP_SONG SONG(ZELDA_TREASURE)
  #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                SONG(PLANCK_SOUND) \
                              }
#endif
