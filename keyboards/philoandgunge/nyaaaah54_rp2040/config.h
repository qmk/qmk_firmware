#ifndef CONFIG_H
#define CONFIG_H

#define BACKLIGHT_PIN GP22
/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 6
#endif

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// #ifdef RGB_DI_PIN
// #define RGBLIGHT_ANIMATIONS
// #define RGBLED_NUM 0
// #define RGBLIGHT_HUE_STEP 8
// #define RGBLIGHT_SAT_STEP 8
// #define RGBLIGHT_VAL_STEP 8
// #endif

#endif