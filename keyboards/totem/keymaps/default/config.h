#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/
#define MASTER_LEFT

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#define TAPPING_TERM 200
#define QUICK_TAP_TERM TAPPING_TERM
#define PERMISSIVE_HOLD_PER_KEY

// Neutralize long hold of Alt and GUI keys
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_RIGHT_CTRL

// Auto Shift
#define NO_AUTO_SHIFT_ALPHA
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_NO_SETUP

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
