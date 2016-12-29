#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* enable/disable LEDs based on layout */
#undef USE_SPLIT_BACKSPACE
#define USE_SPLIT_BACKSPACE 0

#undef USE_SPLIT_LEFT_SHIFT
#define USE_SPLIT_LEFT_SHIFT 0

#undef USE_SPLIT_RIGHT_SHIFT
#define USE_SPLIT_RIGHT_SHIFT 0

#undef USE_7U_SPACEBAR
#define USE_7U_SPACEBAR 0

#undef USE_ISO_ENTER
#define USE_ISO_ENTER 0

// RGB underglow stuff.
#define RGBLIGHT_ANIMATIONS
#define RGB_DI_PIN B0          // The pin your RGB strip is wired to
#define RGBLIGHT_ANIMATIONS    // Require for fancier stuff (not compatible with audio)
#define RGBLED_NUM 16          // Number of LEDs
#define RGBLIGHT_HUE_STEP 5    // How much each press of rgb_hue changes hue
#define RGBLIGHT_SAT_STEP 10   // How much each press of rgb_sat changes sat
#define RGBLIGHT_VAL_STEP 10   // How much each press of rgb_val changes val

#endif //CONFIG_USER_H 
