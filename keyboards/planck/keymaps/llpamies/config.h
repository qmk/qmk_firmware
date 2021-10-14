#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)
#endif

// Combos.
#undef COMBO_COUNT // I set COMBO_LEN in keymap.c
#define COMBO_TERM 30

// Hold and tap config.
#define TAPPING_TERM 200
//#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
