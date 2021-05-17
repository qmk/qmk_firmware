#pragma once

/* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TAP_TOGGLE 7
/* Time (in ms) before the one shot key is released */
#define ONESHOT_TIMEOUT 5000

/* Audio */
#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
#endif
