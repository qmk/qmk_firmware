#pragma once

#define MASTER_RIGHT// EE_HANDS MASTER_RIGHT

// these should work better for homerow modifiers
#define TAPPING_TERM 350
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD

#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 300

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 10000
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
#endif

#ifdef ENCODER_ENABLE
  // EC11K encoders have a different resolution than other EC11 encoders.
  // When using the default resolution of 4, if you notice your encoder skipping
  // every other tick, lower the resolution to 2.
  #define ENCODER_RESOLUTION 2
  // Also, flip direction
  #define ENCODER_DIRECTION_FLIP
#endif

