#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG    SONG(STARTUP_SOUND)
    #define GOODBYE_SONG    SONG(GOODBYE_SOUND)
    #define AUDIO_CLICKY
    #define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f
    #define MIDI_BASIC
    #define MUSIC_MASK keycode != KC_NO
#endif

// save me space!
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
