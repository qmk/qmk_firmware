#pragma once

/* Enable/disable LEDs based on layout. */
#undef RGB_BACKLIGHT_USE_SPLIT_BACKSPACE
#define RGB_BACKLIGHT_USE_SPLIT_BACKSPACE 0

#undef RGB_BACKLIGHT_USE_SPLIT_LEFT_SHIFT
#define RGB_BACKLIGHT_USE_SPLIT_LEFT_SHIFT 0

#undef RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT
#define RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT 0

#undef RGB_BACKLIGHT_USE_7U_SPACEBAR
#define RGB_BACKLIGHT_USE_7U_SPACEBAR 0

#undef RGB_BACKLIGHT_USE_ISO_ENTER
#define RGB_BACKLIGHT_USE_ISO_ENTER 0

#undef RGB_BACKLIGHT_DISABLE_HHKB_BLOCKER_LEDS
#define RGB_BACKLIGHT_DISABLE_HHKB_BLOCKER_LEDS 0

// Set up RGB underglow.
#define RGB_DI_PIN B0          // The pin your RGB strip is wired to
#define RGBLIGHT_ANIMATIONS    // Require for fancier stuff (not compatible with audio)
#define RGBLED_NUM 35          // Number of LEDs
#define RGBLIGHT_HUE_STEP 5    // How much each press of rgb_hue changes hue
#define RGBLIGHT_SAT_STEP 10   // How much each press of rgb_sat changes sat
#define RGBLIGHT_VAL_STEP 10   // How much each press of rgb_val changes val

// Enable current limiting for RGB underglow.
#define RGBSTRIP_CURRENT_LIMIT 1300    // Strip current limit in mA. (USB amperage - 500mA for keyboard)
#define RGBSTRIP_MAX_CURRENT_PER_LIGHT 40 // mA per light when at max brightness.

// Scale brightnes according to BRIGHTNESS_CORRECTION_TABLE in quantum/rgblight.c.
// This allows to mitigate uneven brightness from LED underglow strips.
// #define LED_BRIGHTNESS_CORRECTION

// Prevent modifiers on layer 1 from persisting after we let go
#define PREVENT_STUCK_MODIFIERS

