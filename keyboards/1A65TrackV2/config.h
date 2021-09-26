#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define MANUFACTURER    Santy
#define PRODUCT         SplitBall
#define DESCRIPTION     65% Split with Trackball

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 9

#define MATRIX_ROW_PINS { F6, F7, F0, F1, B5 }
#define MATRIX_COL_PINS { B4, D5, F4, F5, D4, C6, D7, E6, D1 }

#define MATRIX_ROW_PINS_RIGHT { F6, F7, B1, B3, B5 } 
#define MATRIX_COL_PINS_RIGHT { B4, D2, F4, F5, D4, C6, D7, E6, D1 }

#define DIODE_DIRECTION COL2ROW
#define FORCE_NKRO
#define DEBOUNCE 5

#define MASTER_LEFT
#define SOFT_SERIAL_PIN D0

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10

// Define the trackball sensor
#define PMW_3360

#define ENCODERS_PAD_A { B6 }
#define ENCODERS_PAD_B { C7 }
#define ENCODERS_PAD_A_RIGHT { B6 }
#define ENCODERS_PAD_B_RIGHT { B2 }
#define ENCODER_RESOLUTIONS { 4, 4 }

#define RGBLIGHT_SPLIT 
#define RGBLED_SPLIT { 16, 16 }
#define RGBLIGHT_LIMIT_VAL 200
#define SPLIT_USB_DETECT

#define RGB_DI_PIN D3
#define RGBLED_NUM 32
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LAYERS
//#define RGBLIGHT_MAX_LAYERS 32

//#define RGBLIGHT_ANIMATIONS
//#define RGBLIGHT_MODE_RAINBOW_MOOD
//#define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL 

/* optical sensor settings */
#define SCROLL_DIVIDER 12
#define CPI_1 600

// Decrease firmware size
#define NO_ACTION_MACRO
#define NO_ACTION_ONESHOT