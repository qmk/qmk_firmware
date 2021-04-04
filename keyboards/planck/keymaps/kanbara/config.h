#pragma once

#ifdef AUDIO_ENABLE
    #ifdef TEMPO_DEFAULT
        #undef TEMPO_DEFAULT
        #define TEMPO_DEFAULT 80
    #endif

    #define STARTUP_SONG SONG(MAJOR_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND), \
                                  SONG(WORKMAN_SOUND) \
                                }
#endif
