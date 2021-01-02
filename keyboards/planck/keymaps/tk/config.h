#pragma once

#define ENCODER_RESOLUTION 4    // dependent on rotary encoder

#define TAP_CODE_DELAY 10       // delay between key press and release on `tapcode(kc)`

#define TAPPING_TERM 200        // mod tap tap-window

// oneshot keys --

#define ONESHOT_TAP_TOGGLE 25   // taps to toggle a one-shot layer/key persistence

#define ONESHOT_TIMEOUT 500     // one-shot layer/key timeout

// dynamic macros --

// you can store HALF of this number of keypresses in both macros together
#define DYNAMIC_MACRO_SIZE 256

// mouse keys --

#define MK_3_SPEED

// mouse speeds

// cursor offset per movement
#define MK_C_OFFSET_1 4
#define MK_C_OFFSET_2 16

// time between cursor movements (ms)
#define MK_C_INTERVAL_1 16  // 16 ms = 60 Hz refresh rate
#define MK_C_INTERVAL_2 16

// scroll speeds

// scroll steps per scroll action
#define MK_W_OFFSET_1 1
#define MK_W_OFFSET_2 4

// time between scroll steps (ms)
#define MK_W_INTERVAL_1 16
#define MK_W_INTERVAL_2 16


// audio --

#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_RANDOMNESS 1

#ifdef AUDIO_ENABLE

    #undef  TEMPO_DEFAULT       // set a custom tempo
    #define TEMPO_DEFAULT 255   // smaller is faster; max = 255

    #define T__NOTE(note) MUSICAL_NOTE(note, 2) // 32nd-note
    #define TD_NOTE(note) MUSICAL_NOTE(note, 3) // 48th-note
    #define X__NOTE(note) MUSICAL_NOTE(note, 1) // 64th-note

    #define NOTE_A5SEMI         905.79f
    #define NOTE_AS5SEMI        959.65f
    #define NOTE_B5SEMI         1016.71f

    // Mario songs

    #define MARIO_FIREBALL      T__NOTE(_G4), T__NOTE(_G5), T__NOTE(_G6), T__NOTE(_G7)

    #define MARIO_KICK          S__NOTE(_AS5), E__NOTE(_REST), S__NOTE(_F6)

    #define MARIO_COIN          E__NOTE(_B6), H__NOTE(_E7), QD_NOTE(_E7)


    #define MARIO_ONEUP         ED_NOTE(_E7), ED_NOTE(_G7), ED_NOTE(_E8), \
                                ED_NOTE(_C8), ED_NOTE(_D8), H__NOTE(_G8)

    #define MARIO_STOMP         T__NOTE(_A5), X__NOTE(_AS5), X__NOTE(_B5),  X__NOTE(_C6), X__NOTE(_CS6), T__NOTE(_REST),\
                                T__NOTE(_F6), X__NOTE(_G6),  X__NOTE(_GS6), X__NOTE(_A6), X__NOTE(_AS6)

    #define MARIO_BUMP          X__NOTE(_G4),  X__NOTE(_FS4), X__NOTE(_F4),  X__NOTE(_E4), \
                                X__NOTE(_DS4), X__NOTE(_D4),  X__NOTE(_CS4), X__NOTE(_C4), \
                                X__NOTE(_CS4), X__NOTE(_D4),  X__NOTE(_DS4), X__NOTE(_E4)

    #define MARIO_CAVE_1        E__NOTE(_C5),  E__NOTE(_REST), E__NOTE(_C5),  E__NOTE(_REST), \
                                E__NOTE(_A4),  E__NOTE(_REST), E__NOTE(_A4),  E__NOTE(_REST), \
                                E__NOTE(_AS4), E__NOTE(_REST), E__NOTE(_AS4), E__NOTE(_REST)

    #define MARIO_CAVE_2        E__NOTE(_F4),  E__NOTE(_REST), E__NOTE(_F4),  E__NOTE(_REST), \
                                E__NOTE(_D4),  E__NOTE(_REST), E__NOTE(_D4),  E__NOTE(_REST), \
                                E__NOTE(_DS4), E__NOTE(_REST), E__NOTE(_DS4), E__NOTE(_REST)

    #define MARIO_POWERUP_BLOCK SD_NOTE(_C5),  T__NOTE(_G5),  T__NOTE(_GS5), \
                                SD_NOTE(_CS5), T__NOTE(_GS5), T__NOTE(_A5),  \
                                SD_NOTE(_D5),  T__NOTE(_A5),  T__NOTE(_AS5), \
                                SD_NOTE(_DS5), T__NOTE(_AS5), T__NOTE(_B5)

    #define MARIO_POWERUP       S__NOTE(_C6),  T__NOTE(_G5),  T__NOTE(_C6),  T__NOTE(_E6),  \
                                T__NOTE(_G6),  T__NOTE(_C7),  T__NOTE(_G6),  S__NOTE(_GS5), \
                                T__NOTE(_C6),  T__NOTE(_DS6), T__NOTE(_GS6), T__NOTE(_DS6), \
                                T__NOTE(_GS6), T__NOTE(_C7),  T__NOTE(_DS7), T__NOTE(_GS7), \
                                T__NOTE(_DS7), S__NOTE(_AS5), T__NOTE(_D6),  T__NOTE(_F6),  \
                                T__NOTE(_AS6), T__NOTE(_F6),  T__NOTE(_AS6), T__NOTE(_D7),  \
                                T__NOTE(_F7),  T__NOTE(_AS7), T__NOTE(_F7)


    #define MARIO_PIPE          X__NOTE(_E7), X__NOTE(_A6), X__NOTE(_D6), X__NOTE(_G5), \
                                X__NOTE(_E7), X__NOTE(_A6), X__NOTE(_D6), X__NOTE(_G5), T__NOTE(_AS3), T__NOTE(_AS2), \
                                T__NOTE(_REST), \
                                X__NOTE(_E7), X__NOTE(_A6), X__NOTE(_D6), X__NOTE(_G5), \
                                X__NOTE(_E7), X__NOTE(_A6), X__NOTE(_D6), X__NOTE(_G5), T__NOTE(_AS3), T__NOTE(_AS2), \
                                T__NOTE(_REST), \
                                X__NOTE(_E7), X__NOTE(_A6), X__NOTE(_D6), X__NOTE(_G5), \
                                X__NOTE(_E7), X__NOTE(_A6), X__NOTE(_D6), X__NOTE(_G5), T__NOTE(_AS3), T__NOTE(_AS2)

                                // todo - fix
    #define MARIO_DEATH         TD_NOTE(_AS5), T__NOTE(_A5SEMI), TD_NOTE(_B5), T__NOTE(_AS5SEMI), \
                                TD_NOTE(_C6), T__NOTE(_B5SEMI), X__NOTE(_GS5), TD_NOTE(_G5)

                                // todo - fix
    #define MARIO_JUMP_SMALL    T__NOTE(_A6), \
                                TD_NOTE(_A5), X__NOTE(_AS5), X__NOTE(_B5),                \
                                X__NOTE(_C6), X__NOTE(_CS6), X__NOTE(_D6), X__NOTE(_DS6), \
                                X__NOTE(_E6),                X__NOTE(_F6), X__NOTE(_FS6), \
                                X__NOTE(_G6), X__NOTE(_GS6), X__NOTE(_A6), X__NOTE(_AS6), \
                                T__NOTE(_B6)

    #define MARIO_JUMP_BIG      // todo

    #define MARIO_GAMEOVER      // todo

    #define MARIO_VINE          // todo

    #undef  MARIO_THEME
    #define MARIO_THEME         E__NOTE(_E5),   E__NOTE(_REST), Q__NOTE(_E5),   \
                                Q__NOTE(_REST), Q__NOTE(_E5),   Q__NOTE(_REST), \
                                Q__NOTE(_C5),   Q__NOTE(_E5),   Q__NOTE(_REST), \
                                H__NOTE(_G5),   S__NOTE(_REST), H__NOTE(_REST), HD_NOTE(_G4)

    // real songs

    #define PINK_PANTHER        Q__NOTE(_CS5), QD_NOTE(_D5), Q__NOTE(_REST), Q__NOTE(_DS5), W__NOTE(_E5)

    #define STILL_DRE           ED_NOTE(_CS6), E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_CS6), E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_CS6), E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_CS6), E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_CS6), E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_CS6), E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_CS6), E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_CS6), E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_C6),  E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_C6),  E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_C6),  E__NOTE(_F6), ED_NOTE(_AS6),  \
                                ED_NOTE(_C6),  E__NOTE(_F6), ED_NOTE(_GS6),  \
                                ED_NOTE(_C6),  E__NOTE(_F6), ED_NOTE(_GS6),  \
                                ED_NOTE(_C6),  E__NOTE(_F6), ED_NOTE(_GS6),  \
                                ED_NOTE(_C6),  E__NOTE(_F6), ED_NOTE(_GS6),  \
                                ED_NOTE(_C6),  E__NOTE(_F6), ED_NOTE(_GS6),

    // override default songs

    #define STARTUP_SONG        SONG(PINK_PANTHER)
    #define GOODBYE_SONG        SONG(MARIO_DEATH)

#endif