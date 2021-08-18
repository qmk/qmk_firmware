#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 165
#define TAPPING_FORCE_HOLD_PER_KEY

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 5000

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION