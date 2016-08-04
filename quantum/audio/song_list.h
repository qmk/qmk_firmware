#include "musical_notes.h"

#ifndef SONG_LIST_H
#define SONG_LIST_H

#define ODE_TO_JOY                                          \
    Q__NOTE(_E4), Q__NOTE(_E4), Q__NOTE(_F4), Q__NOTE(_G4), \
    Q__NOTE(_G4), Q__NOTE(_F4), Q__NOTE(_E4), Q__NOTE(_D4), \
    Q__NOTE(_C4), Q__NOTE(_C4), Q__NOTE(_D4), Q__NOTE(_E4), \
    QD_NOTE(_E4), E__NOTE(_D4), H__NOTE(_D4),

#define ROCK_A_BYE_BABY                            \
    QD_NOTE(_B4), E__NOTE(_D4), Q__NOTE(_B5),      \
    H__NOTE(_A5), Q__NOTE(_G5),                    \
    QD_NOTE(_B4), E__NOTE(_D5), Q__NOTE(_G5),      \
    H__NOTE(_FS5),

#define CLOSE_ENCOUNTERS_5_NOTE  \
	Q__NOTE(_D5),                \
	Q__NOTE(_E5),                \
	Q__NOTE(_C5),                \
	Q__NOTE(_C4),                \
	Q__NOTE(_G4),

#define DOE_A_DEER              \
	QD_NOTE(_C4), E__NOTE(_D4), \
	QD_NOTE(_E4), E__NOTE(_C4), \
	Q__NOTE(_E4), Q__NOTE(_C4), \
	Q__NOTE(_E4),

/* Requires: PLAY_NOTE_ARRAY(..., ..., STACCATO); */
#define IN_LIKE_FLINT \
    E__NOTE(_AS4), E__NOTE(_AS4), QD_NOTE(_B4),  \
    E__NOTE(_AS4), E__NOTE(_B4),  QD_NOTE(_CS4), \
    E__NOTE(_B4),  E__NOTE(_CS4), QD_NOTE(_DS4), \
    E__NOTE(_CS4), E__NOTE(_B4),  QD_NOTE(_AS4), \
    E__NOTE(_AS4), E__NOTE(_AS4), QD_NOTE(_B4),

#define GOODBYE_SOUND \
    E__NOTE(_E7),     \
    E__NOTE(_A6),     \
    ED_NOTE(_E6),

#define STARTUP_SOUND  \
    ED_NOTE(_E7 ),     \
    E__NOTE(_CS7),     \
    E__NOTE(_E6 ),     \
    E__NOTE(_A6 ),     \
    M__NOTE(_CS7, 20),

#define QWERTY_SOUND \
    E__NOTE(_GS6 ),  \
    E__NOTE(_A6  ),  \
    S__NOTE(_REST),  \
    Q__NOTE(_E7  ),

#define COLEMAK_SOUND \
    E__NOTE(_GS6 ),   \
    E__NOTE(_A6  ),   \
    S__NOTE(_REST),   \
    ED_NOTE(_E7  ),   \
    S__NOTE(_REST),   \
    ED_NOTE(_GS7 ),

#define DVORAK_SOUND \
    E__NOTE(_GS6 ),  \
    E__NOTE(_A6  ),  \
    S__NOTE(_REST),  \
    E__NOTE(_E7  ),  \
    S__NOTE(_REST),  \
    E__NOTE(_FS7 ),  \
    S__NOTE(_REST),  \
    E__NOTE(_E7  ),

#define PLOVER_SOUND \
    E__NOTE(_GS6 ),  \
    E__NOTE(_A6  ),  \
    S__NOTE(_REST),  \
    ED_NOTE(_E7  ),  \
    S__NOTE(_REST),  \
    ED_NOTE(_A7  ),

#define PLOVER_GOODBYE_SOUND \
    E__NOTE(_GS6 ),  \
    E__NOTE(_A6  ),  \
    S__NOTE(_REST),  \
    ED_NOTE(_A7  ),  \
    S__NOTE(_REST),  \
    ED_NOTE(_E7  ),

#define MUSIC_SCALE_SOUND \
    E__NOTE(_A5 ),        \
    E__NOTE(_B5 ),        \
    E__NOTE(_CS6),        \
    E__NOTE(_D6 ),        \
    E__NOTE(_E6 ),        \
    E__NOTE(_FS6),        \
    E__NOTE(_GS6),        \
    E__NOTE(_A6 ),

#define CAPS_LOCK_ON_SOUND \
    E__NOTE(_A3),          \
    E__NOTE(_B3),

#define CAPS_LOCK_OFF_SOUND \
    E__NOTE(_B3),           \
    E__NOTE(_A3),

#define SCROLL_LOCK_ON_SOUND \
    E__NOTE(_D4),            \
    E__NOTE(_E4),

#define SCROLL_LOCK_OFF_SOUND \
    E__NOTE(_E4),             \
    E__NOTE(_D4),

#define NUM_LOCK_ON_SOUND \
    E__NOTE(_D5),         \
    E__NOTE(_E5),

#define NUM_LOCK_OFF_SOUND \
    E__NOTE(_E5),          \
    E__NOTE(_D5),

#endif
