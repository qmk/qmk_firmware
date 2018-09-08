#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H

// required because lower/raise modifiers are redefined by colemak-dh
#define PREVENT_STUCK_MODIFIERS

// tap dance key press termination interval
#define TAPPING_TERM   250

// thumb key tap-shift() double tap: one shot shift (0) off (1) on
#define DT_SHIFT 1

#ifdef KEYBOARD_lets_split
#define USE_SERIAL
#define EE_HANDS
#endif

#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT

// number of backlight levels
#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 5

#endif
