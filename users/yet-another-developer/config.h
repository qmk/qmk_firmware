#pragma once


/* Set Polling rate to 1000Hz */
#define USB_POLLING_INTERVAL_MS 1


#ifndef ONESHOT_TAP_TOGGLE
#    define ONESHOT_TAP_TOGGLE 2
#endif  // !ONESHOT_TAP_TOGGLE

#ifndef ONESHOT_TIMEOUT
#    define ONESHOT_TIMEOUT 3000
#endif  // !ONESHOT_TIMEOUT

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define IGNORE_MOD_TAP_INTERRUPT
#undef PERMISSIVE_HOLD

#ifdef TAPPING_TERM
#  undef TAPPING_TERM
#endif  // !TAPPING_TERM

#if defined(KEYBOARD_ergodash)
#    define TAPPING_TERM 190
#else
#    define TAPPING_TERM 175
#endif

 #define TAP_CODE_DELAY 5 //DEFAULT: 100

 #define MACRO_TIMER 5

