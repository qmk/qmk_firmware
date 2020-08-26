#pragma once

#define ENCODER_RESOLUTION 4    // dependent on rotary encoder

#define TAP_CODE_DELAY 10       // delay between key press and release on `tapcode(kc)`

#define TAPPING_TERM 200        // tap dance tap-window

#define ONESHOT_TAP_TOGGLE 5    // taps to toggle a one-shot layer/key persistence

#ifdef AUDIO_ENABLE
    #undef  TEMPO_DEFAULT       // set a custom tempo
    #define TEMPO_DEFAULT 255   // smaller is faster; max = 255

    // Mario songs

    #undef  MARIO_THEME
    #define MARIO_THEME         E__NOTE(_E5),   E__NOTE(_REST), Q__NOTE(_E5),   \
                                Q__NOTE(_REST), Q__NOTE(_E5),   Q__NOTE(_REST), \
                                Q__NOTE(_C5),   Q__NOTE(_E5),   Q__NOTE(_REST), \
                                H__NOTE(_G5),   S__NOTE(_REST), H__NOTE(_REST), HD_NOTE(_G4)

    #define MARIO_CAVE_1        E__NOTE(_C5),  E__NOTE(_REST), E__NOTE(_C5),  E__NOTE(_REST), \
                                E__NOTE(_A4),  E__NOTE(_REST), E__NOTE(_A4),  E__NOTE(_REST), \
                                E__NOTE(_AS4), E__NOTE(_REST), E__NOTE(_AS4), E__NOTE(_REST),
    #define MARIO_CAVE_2        E__NOTE(_F4),  E__NOTE(_REST), E__NOTE(_F4),  E__NOTE(_REST), \
                                E__NOTE(_D4),  E__NOTE(_REST), E__NOTE(_D4),  E__NOTE(_REST), \
                                E__NOTE(_DS4), E__NOTE(_REST), E__NOTE(_DS4), E__NOTE(_REST)

    #define MARIO_ONEUP         ED_NOTE(_E7), ED_NOTE(_G7), ED_NOTE(_E8), \
                                ED_NOTE(_C8), ED_NOTE(_D8), H__NOTE(_G8)

    #define MARIO_COIN          E__NOTE(_B6), H__NOTE(_E7), QD_NOTE(_E7)

    #define MARIO_PIPE          // todo

    #define MARIO_GAMEOVER      // todo

    #define MARIO_POWERUP       // todo

    #define MARIO_DAMAGE        // todo

    // real songs

    #define STILL_DRE           QD_NOTE(_CS6), Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_CS6), Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_CS6), Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_CS6), Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_CS6), Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_CS6), Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_CS6), Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_CS6), Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_C6),  Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_C6),  Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_C6),  Q__NOTE(_F6), QD_NOTE(_AS6),  \
                                QD_NOTE(_C6),  Q__NOTE(_F6), QD_NOTE(_GS6),  \
                                QD_NOTE(_C6),  Q__NOTE(_F6), QD_NOTE(_GS6),  \
                                QD_NOTE(_C6),  Q__NOTE(_F6), QD_NOTE(_GS6),  \
                                QD_NOTE(_C6),  Q__NOTE(_F6), QD_NOTE(_GS6),  \
                                QD_NOTE(_C6),  Q__NOTE(_F6), QD_NOTE(_GS6),
    // sound effects

    #define COIN                E__NOTE(_A5), HD_NOTE(_E6)
    #define BUZZ                H__NOTE(_C3), H__NOTE(_C3)

    #define PICK_UP             H__NOTE(_C4), HD_NOTE(_G4)
    #define PUT_DOWN            H__NOTE(_G4), HD_NOTE(_C4)

    // override default songs
    #define STARTUP_SONG        SONG(MARIO_THEME)
    #define GOODBYE_SONG        SONG(STILL_DRE)
#endif
