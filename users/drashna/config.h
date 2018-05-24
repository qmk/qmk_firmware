#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H


#ifdef AUDIO_ENABLE
<<<<<<< HEAD
#define STARTUP_SONG SONG(IMPERIAL_MARCH)
=======
#define AUDIO_CLICKY
#define STARTUP_SONG SONG(E1M1_DOOM)
>>>>>>> 73ddb764ccbe47662ba4604a18818f003abd8d36
#define GOODBYE_SONG  SONG(SONIC_RING)
#define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND), \
                                  SONG(PLOVER_SOUND) \
                                }
#endif

#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_SLEEP
#endif // RGBLIGHT_ENABLE



#ifndef ONESHOT_TAP_TOGGLE
#define ONESHOT_TAP_TOGGLE 2
#endif // !ONESHOT_TAP_TOGGLE

#ifndef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 3000
#endif// !ONESHOT_TIMEOUT

#ifndef QMK_KEYS_PER_SCAN
#define QMK_KEYS_PER_SCAN 4
#endif // !QMK_KEYS_PER_SCAN



// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD
#undef PREVENT_STUCK_MODIFIERS
#define TAPPING_FORCE_HOLD
//#define RETRO_TAPPING

#ifndef TAPPING_TOGGLE
#define TAPPING_TOGGLE  1
#endif

#ifdef TAPPING_TERM
#undef TAPPING_TERM
<<<<<<< HEAD
#endif
#define TAPPING_TERM 150
=======
#endif // TAPPING_TERM
#define TAPPING_TERM 200
>>>>>>> 73ddb764ccbe47662ba4604a18818f003abd8d36


// Disable action_get_macro and fn_actions, since we don't use these
// and it saves on space in the firmware.
<<<<<<< HEAD
=======
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
>>>>>>> 73ddb764ccbe47662ba4604a18818f003abd8d36
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION



#endif // !USERSPACE_CONFIG_H

