#if AUDIO_ENABLE
#    if __has_include("copyright.h")
#        include "copyright.h"
#    endif

#    define LOWER_SOUND S__NOTE(_EF5), W__NOTE(_REST), Q__NOTE(_E4)
#    define NUMPAD_SOUND S__NOTE(_DF5), S__NOTE(_REST), S__NOTE(_C6)
#    define RAISE_SOUND S__NOTE(_E4), W__NOTE(_REST), Q__NOTE(_EF5)

#    define AUDIO_ON_SONG SONG(ZELDA_PUZZLE)
#    define LAYER_FUNCROW_ON_SONG SONG(COLEMAK_SOUND)
#    define LAYER_FUNCROW_OFF_SONG SONG(QWERTY_SOUND)
#    define LAYER_NMPAD_SONG SONG(NUMPAD_SOUND)
#    define LAYER_LOWER_SONG SONG(LOWER_SOUND)
#    define LAYER_RAISE_SONG SONG(RAISE_SOUND)
#else
//   No-op version of PLAY_SONG instead of many checks for AUDIO_ENABLED
#    ifndef PLAY_SONG
#        define PLAY_SONG(ARG)  // ARG
#    endif
#endif
