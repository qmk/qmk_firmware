#pragma once

#ifdef AUDIO_ENABLE
    #define AUDIO_INIT_DELAY 150       // Enables delay during startup song to accomidate for USB startup issues
    #define STARTUP_SONG SONG(ZELDA_SECRET)
#endif

#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10
