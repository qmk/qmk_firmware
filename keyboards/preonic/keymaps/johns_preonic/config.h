#pragma once


#define TAPPING_TERM 200

/* #define MK_3_SPEED */
#define MK_MOMENTARY_ACCEL
#define MOUSEKEY_MAX_SPEED         8



#undef MUSICAL_NOTE
#define MUSICAL_NOTE(note, duration) {((NOTE##note) * 1.3348398541700344), duration}

#define CUSTOM_STARTUP \
    QD_NOTE(_A6),  \
    QD_NOTE(_C7),  \
    QD_NOTE(_A7),  \
    QD_NOTE(_F7),  \
    QD_NOTE(_G7),  \
    HD_NOTE(_C8),

#undef MUSICAL_NOTE
#define MUSICAL_NOTE(note, duration) {(NOTE##note), duration}

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(CUSTOM_STARTUP)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND), \
                                  SONG(WORKMAN_SOUND), \
                                  SONG(PREONIC_SOUND), \
                                  SONG(GUITAR_SOUND), \
                                  SONG(UNICODE_WINDOWS), \
                                  SONG(UNICODE_LINUX) \
                                }
#endif

#define MUSIC_MASK (keycode != KC_NO)


#define MIDI_BASIC


