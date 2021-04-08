#pragma once

#ifdef AUDIO_ENABLE
#  define DEFAULT_LAYER_SONGS \
     { SONG(QWERTY_SOUND), SONG(COLEMAK_SOUND), SONG(DVORAK_SOUND), SONG(PLOVER_SOUND) }
#  define AUDIO_CLICKY
#  define STARTUP_SONG SONG(RICK_ROLL)
#  define GOODBYE_SONG SONG(SONIC_RING)
#  define AUDIO_CLICKY_FREQ_RANDOMNESS 1.5f
#  ifndef __arm__
#    undef  NOTE_REST
#    define NOTE_REST 1.00f
#  endif // !__arm__
#  define UNICODE_SONG_MAC SONG(RICK_ROLL)
#  define UNICODE_SONG_LNX SONG(RICK_ROLL)
#  define UNICODE_SONG_WIN SONG(RICK_ROLL)
#  define UNICODE_SONG_BSD SONG(RICK_ROLL)
#  define UNICODE_SONG_WINC SONG(RICK_ROLL)
#endif // !AUDIO_ENABLE

#ifdef RGBLIGHT_ENABLE
#  define RGBLIGHT_SLEEP
#  undef  RGBLIGHT_ANIMATIONS
#  define RGBLIGHT_HUE_STEP 16
#  define RGBLIGHT_SAT_STEP 16
#  define RGBLIGHT_VAL_STEP 16
#  define RGBLIGHT_LIMIT_VAL 255
#  define RGBLIGHT_EFFECT_BREATHING
#  define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#  define RGBLIGHT_EFFECT_KNIGHT
//#  define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
//#  define RGBLIGHT_EFFECT_SNAKE
//#  define RGBLIGHT_EFFECT_SNAKE_LENGTH 2
#endif // !RGBLIGHT_ENABLE

#ifndef ONESHOT_TAP_TOGGLE
#  define ONESHOT_TAP_TOGGLE 2
#endif // !ONESHOT_TAP_TOGGLE

#ifndef ONESHOT_TIMEOUT
#  define ONESHOT_TIMEOUT 3000
#endif// !ONESHOT_TIMEOUT

#ifndef QMK_KEYS_PER_SCAN
#  define QMK_KEYS_PER_SCAN 4
#endif // !QMK_KEYS_PER_SCAN

#if defined(LEADER_ENABLE)
#  define LEADER_PER_KEY_TIMING
#  define LEADER_TIMEOUT 250
#endif // !LEADER_ENABLE 

#if defined(COMBO_ENABLE)
#  define COMBO_COUNT 4
#  define COMBO_TERM 150
#endif // !COMBO_ENABLE 

#if defined(NKRO_ENABLE)
#  define FORCE_NKRO
#endif // !NKRO_ENABLE

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD
//#define TAPPING_FORCE_HOLD
//#define RETRO_TAPPING

#ifndef TAPPING_TOGGLE
#  define TAPPING_TOGGLE  1
#endif

#ifdef TAPPING_TERM
#  undef TAPPING_TERM
#endif // !TAPPING_TERM
#if defined(KEYBOARD_handwired_kuchosauronad0_planckenstein)
#  define TAPPING_TERM 185
#elif defined(KEYBOARD_c39)
#  define TAPPING_TERM 200
#else
#  define TAPPING_TERM 180
#endif


#define TAP_CODE_DELAY 5

#define MACRO_TIMER 5 

