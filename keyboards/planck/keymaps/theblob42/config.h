#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(NO_SOUND)

    // if you want to reenable the startup sound
    // #define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

// enable basic MIDI features
#define MIDI_BASIC

// only two taps to toggle layer via TT(...)
#define TAPPING_TOGGLE 2
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

// time (in ms) before a one shot key is released
#define ONESHOT_TIMEOUT 3000

// set the default unicode input mode to linux
#define UNICODE_SELECTED_MODES UC_LNX

// make the mouse cursor move smooothly
#define MOUSEKEY_INTERVAL 16 // for a 60hz monitor
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 100
#define MOUSEKEY_MAX_SPEED 5
#define MOUSEKEY_WHEEL_DELAY 20
