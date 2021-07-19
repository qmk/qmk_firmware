#pragma once
#define ENCODER_DIRECTION_FLIP

#ifdef ENCODER_RESOLUTION
    #undef ENCODER_RESOLUTION
    #define ENCODER_RESOLUTION 4
#endif
#define TAPPING_TERM_PER_KEY
#ifdef TAPPING_TERM
    #undef TAPPING_TERM
    #define TAPPING_TERM 200
#endif
#ifdef MANUFACTURER
    #undef MANUFACTURER
    #define MANUFACTURER Flare576
#endif
