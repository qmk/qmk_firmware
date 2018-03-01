#ifndef USERSPACE
#define USERSPACE

#define TAPPING_TOGGLE 2

#ifdef AUDIO_ENABLE
    #define WORKMAN_SOUND \
        E__NOTE(_GS7),    \
        ED_NOTE(_E7),     \
        S__NOTE(_REST),   \
        E__NOTE(_A6),     \
        S__NOTE(_REST),   \
        ED_NOTE(_GS6),
#endif

#endif
