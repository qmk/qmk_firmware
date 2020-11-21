#pragma once
#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PREONIC_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)
    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(ZELDA_PUZZLE), \
                                  SONG(MARIO_THEME) \
                                }
#endif
#define MUSIC_MASK (keycode != KC_NO)
//#define AUDIO_CLICKY
#define TAP_CODE_DELAY 100
#define MIDI_BASIC
