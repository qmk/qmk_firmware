#pragma once

/* Set Polling rate to 1000Hz */
#define USB_POLLING_INTERVAL_MS 1

#ifndef ONESHOT_TAP_TOGGLE
    #define ONESHOT_TAP_TOGGLE 2
#endif  // !ONESHOT_TAP_TOGGLE

#ifndef ONESHOT_TIMEOUT
    #define ONESHOT_TIMEOUT 2000
#endif  // !ONESHOT_TIMEOUT

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

#undef PERMISSIVE_HOLD
//#define QUICK_TAP_TERM 0
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
