#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H

/* Use I2C or Serial, not both */
#define USE_SERIAL
//#define USE_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// Enable tap dance
#define TAPPING_TERM 150
#define TAPPING_TOGGLE 2

// Fix the screw up of the main author
#undef NO_ACTION_TAPPING
// Enable Tapdance
#define NO_ACTION_FUNCTION

// Reduce size
#if !defined(NO_DEBUG) && !defined(CONSOLE_ENABLE)
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

//#define DISABLE_LEADER

#define RGBLIGHT_ANIMATIONS

#endif
