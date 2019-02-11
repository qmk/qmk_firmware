#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(MARIO_MUSHROOM)
#endif

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4
// Mouse Parameters
#define MOUSEKEY_DELAY             300
#define MOUSEKEY_INTERVAL          50
#define MOUSEKEY_MAX_SPEED         8
#define MOUSEKEY_TIME_TO_MAX       20
