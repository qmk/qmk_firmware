#pragma once

#define ENCODER_RESOLUTION 4    // dependent on rotary encoder

#define TAP_CODE_DELAY 10       // delay between key press and release on tapcode(kc)

#define TAPPING_TERM 200        // tap dance window

#define ONESHOT_TAP_TOGGLE 2

#ifdef AUDIO_ENABLE
    // define custom sounds
    #define ONEUP_SOUND         QD_NOTE(_E5), QD_NOTE(_G5), QD_NOTE(_E6), QD_NOTE(_C5), QD_NOTE(_D5), HD_NOTE(_G6)

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
                                QD_NOTE(_C6),  Q__NOTE(_F6), QD_NOTE(_GS6)

    #define COIN                E__NOTE(_A5), HD_NOTE(_E6)
    #define BUZZ                H__NOTE(_C3), H__NOTE(_C3)

    // layer sounds
    #define BK_ACTIVATE         COIN
    #define BK_DEACTIVATE       BUZZ

    // button sounds
    #define CAPS_ON_SOUND       H__NOTE(_A4), H__NOTE(_E5)
    #define CAPS_OFF_SOUND      H__NOTE(_E5), H__NOTE(_A4)
    #define SAVE_SOUND          ONEUP_SOUND
    #define COPY_SOUND          H__NOTE(_C4), H__NOTE(_G4)
    #define CUT_SOUND           E__NOTE(_C4), H__NOTE(_D4), HD_NOTE(_G4)
    #define PASTE_SOUND         H__NOTE(_G4), H__NOTE(_C4)
    #define UNDO_SOUND          NO_SOUND
    #define REDO_SOUND          NO_SOUND

    // override default songs
    #define STARTUP_SONG        SONG(PLANCK_SOUND)
    #define GOODBYE_SONG        SONG(STILL_DRE)
#endif
