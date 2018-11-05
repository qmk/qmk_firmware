#pragma once

#define FORCE_NKRO

#define MOUSEKEY_DELAY              50
#define MOUSEKEY_INTERVAL           15
#define MOUSEKEY_MAX_SPEED          4
#define MOUSEKEY_TIME_TO_MAX        50
#define MOUSEKEY_WHEEL_MAX_SPEED    1
#define MOUSEKEY_WHEEL_TIME_TO_MAX  50

#define PERMISSIVE_HOLD
#define TAPPING_TERM    200
#define TAPPING_TOGGLE  2

#undef  IS_COMMAND
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RCTL)))
