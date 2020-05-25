#pragma once

// Expect to get errors if you comment a feature out and leave it in your keymap.

#ifdef USE_BABLPASTE
//define BabblePaste maps
// Windows.
#define MAC_MODE   0
#define MS_MODE 1
//aka gnome+KDE
//#define LINUX_MODE 2
//#define EMACS_MODE 3
#define VI_MODE 3
// Readline and tmux
#define READMUX_MODE 2
//#define WORDSTAR_MODE 5
#endif

// Uncomment if you need more free flash space

// This removes everything but cursor movement
//#define BABL_MOVEMENTONLY
// and this just removes browser shortcuts
//#define BABL_NOBROWSER

// place overrides here
#define RGBLED_NUM 3
#define RGBLIGHT_LIMIT_VAL 200
#ifdef RGBLIGHT_ENABLE
#define RGBLIGHT_COLOR_LAYER_0 0x00, 0xFF, 0x00
#define RGBLIGHT_COLOR_LAYER_1 0x00, 0x00, 0xFF 
#define RGBLIGHT_COLOR_LAYER_2 0xFF, 0x00, 0x00 
#define RGBLIGHT_COLOR_LAYER_3 0x00, 0xFF, 0xFF 
#define RGBLIGHT_COLOR_LAYER_4 0xFF, 0xFF, 0x00 
#define RGBLIGHT_COLOR_LAYER_5 0x00, 0xFF, 0xFF 
#define RGBLIGHT_ANIMATIONS
#define RGB_LIGHT_EFFECT_BREATHE_MAX 200
#define RGBLIGHT_RAINBOW_SWIRL_RANGE 127
#endif // rgblight

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY
#define RETRO_TAPPING
//#define PERMISSIVE_HOLD
