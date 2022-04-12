#pragma once

/* Set Polling rate to 1000Hz */
#define USB_POLLING_INTERVAL_MS 1

#ifndef ONESHOT_TAP_TOGGLE
    #define ONESHOT_TAP_TOGGLE 2
#endif  // !ONESHOT_TAP_TOGGLE

#ifndef ONESHOT_TIMEOUT
    #define ONESHOT_TIMEOUT 2000
#endif  // !ONESHOT_TIMEOUT

#ifndef QMK_KEYS_PER_SCAN
  #define QMK_KEYS_PER_SCAN 4
#endif // !QMK_KEYS_PER_SCAN

#if defined(LEADER_ENABLE)
  #define LEADER_PER_KEY_TIMING
  #define LEADER_TIMEOUT 250
#endif // !LEADER_ENABLE

#if defined(COMBO_ENABLE)
  #define COMBO_COUNT 4
  #define COMBO_TERM 150
#endif // !COMBO_ENABLE

#if defined(NKRO_ENABLE)
  #define FORCE_NKRO
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
  #define TAPPING_TOGGLE  1
#endif

#ifdef TAPPING_TERM
#  undef TAPPING_TERM
#endif  // !TAPPING_TERM
#if defined(KEYBOARD_ergodash)
    #define TAPPING_TERM 240
#else
    #define TAPPING_TERM 200
#endif

#define TAP_CODE_DELAY 5 //DEFAULT: 100

#define MACRO_TIMER 5
