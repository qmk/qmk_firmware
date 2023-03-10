#pragma once

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
/* #define LOCKING_SUPPORT_ENABLE */

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define NO_ACTION_ONESHOT
#define TAPPING_TOGGLE 3

/*#define RGB_DI_PIN F4*/
#ifdef RGB_DI_PIN
#define RGBLED_NUM 1
#define RGBLIGHT_HUE_STEP 1
#define RGBLIGHT_SAT_STEP 1
#define RGBLIGHT_VAL_STEP 1
#endif
