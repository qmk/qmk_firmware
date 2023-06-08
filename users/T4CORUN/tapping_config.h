#pragma once

/*
https://docs.qmk.fm/#/tap_hold
https://docs.qmk.fm/#/one_shot_keys

*/


//Clear variables we plan to use that might be set elsewhere
#undef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#undef TAPPING_TERM
#undef TAPPING_TERM_PER_KEY
#undef QUICK_TAP_TERM
#undef QUICK_TAP_TERM_PER_KEY

#undef ONESHOT_TAP_TOGGLE
#undef ONESHOT_TIMEOUT


//Set common configuration for all keyboards
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY

#define QUICK_TAP_TERM 120
#define QUICK_TAP_TERM_PER_KEY

#if defined(ONESHOT_ENABLE)
#   define ONESHOT_TAP_TOGGLE 3
#   define ONESHOT_TIMEOUT 3000
#else
#   define NO_ACTION_ONESHOT
#endif //ONESHOT_ENABLE