#pragma once

#undef TAPPING_TERM
#define TAPPING_TERM 200

#define IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_FORCE_HOLD

#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_NO_SETUP

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64

// Thumb Combos
#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
  #define COMBO_COUNT 8
  #define COMBO_TERM 200
  #define EXTRA_SHORT_COMBOS
#endif

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4
