#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// RGB underglow stuff.
#define RGBLIGHT_ANIMATIONS
#define RGB_DI_PIN B0          // The pin your RGB strip is wired to
#define RGBLIGHT_ANIMATIONS    // Require for fancier stuff (not compatible with audio)
#define RGBLED_NUM 16          // Number of LEDs
#define RGBLIGHT_HUE_STEP 5    // How much each press of rgb_hue changes hue
#define RGBLIGHT_SAT_STEP 10   // How much each press of rgb_sat changes sat
#define RGBLIGHT_VAL_STEP 10   // How much each press of rgb_val changes val

// Current limiting.
#define USB_MAX_POWER_CONSUMPTION 900
#define RGBSTRIP_CURRENT_LIMIT 400        // Strip current limit in mA.
#define RGBSTRIP_MAX_CURRENT_PER_LIGHT 60 // mA per light when at max brightness.

#endif //CONFIG_USER_H 
