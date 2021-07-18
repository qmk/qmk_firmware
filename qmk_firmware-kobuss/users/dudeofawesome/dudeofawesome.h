#ifndef USERSPACE
#define USERSPACE

#ifdef TAPPING_TOGGLE
#undef TAPPING_TOGGLE
#endif
#define TAPPING_TOGGLE 2

#ifdef AUDIO_ENABLE
    #ifdef WORKMAN_SOUND
        #undef WORKMAN_SOUND
    #endif

    #define WORKMAN_SOUND \
        E__NOTE(_GS7),    \
        ED_NOTE(_E7),     \
        S__NOTE(_REST),   \
        E__NOTE(_A6),     \
        S__NOTE(_REST),   \
        ED_NOTE(_GS6),

    #define NUMPAD_ON_SOUND \
        E__NOTE(_C6),       \
        ED_NOTE(_BF5),      \
        S__NOTE(_C6),       \
        ED_NOTE(_BF5),
#endif

#endif
