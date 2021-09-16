#pragma once

// Expect to get errors if you comment a feature out and leave it in your keymap.

#ifdef USE_BABLPASTE
//define BabblePaste maps
// Windows.
#define MAC_MODE   0
#define MS_MODE 1
#define LINUX_MODE 2
#define READMUX_MODE 3
#endif

// Uncomment if you need more free flash space

// This removes everything but cursor movement
//#define BABL_MOVEMENTONLY
// and this just removes browser shortcuts
//#define BABL_NOBROWSER

#ifdef RGBLIGHT_ENABLE
// place overrides here
#define RGBLED_NUM 3
#define RGBLIGHT_LIMIT_VAL 128
#define LED_IS_GRB

// Which LED shows OS?
#define LED_BABL_OS 0

//#define RGBLIGHT_ANIMATIONS
///#define RGB_LIGHT_EFFECT_BREATHE_MAX 200
//#define RGBLIGHT_RAINBOW_SWIRL_RANGE 127
#endif // rgblight

