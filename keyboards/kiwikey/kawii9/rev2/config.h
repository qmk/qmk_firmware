#pragma once

#ifdef OLED_ENABLE
// OLED Screen definitions
#define OLED_DISPLAY_128X64
#define OLED_TIMEOUT 20000
#define OLED_BRIGHTNESS 255
//#define OLED_FADE_OUT
#define OLED_FONT_H "keyboards/kiwikey/kawii9/rev2/lib/glcdfont.c"
#endif

#ifdef RGB_MATRIX_ENABLE
// RGB Matrix definitions
#define RGB_DI_PIN B7
#define RGB_MATRIX_LED_COUNT 18
#define RGB_MATRIX_VAL_STEP 12
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 240
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
// RGB Matrix Animation modes. Explicitly enabled.
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINDROPS
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
// Set default RGB Matrix mode
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_UP_DOWN
#endif

//#define WPM_UNFILTERED
