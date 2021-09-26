#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define PRODUCT_ID 0
#define VENDOR_ID 0
#define DEVICE_VER 0

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

// Define the handedness
#define MASTER_LEFT

// Pin for the serial connection
#define SOFT_SERIAL_PIN D0

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define SPLIT_USB_TIMEOUT_POLL 10

// Define the trackball
#define PMW_3360

#define ENCODERS_PAD_A { B6 }
#define ENCODERS_PAD_B { C7 }
#define ENCODERS_PAD_A_RIGHT { B6 }
#define ENCODERS_PAD_B_RIGHT { B2 }
#define ENCODER_RESOLUTIONS { 4, 4 }

#define RGB_DI_PIN D3

#define RGBLED_NUM 10

//#define RGBLIGHT_ANIMATIONS
//#define RGBLIGHT_MODE_RAINBOW_MOOD
//#define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL

#define RGBLIGHT_LAYERS

#define RGBSTRIP_CURRENT_LIMIT 400
#define RGBSTRIP_MAX_CURRENT_PER_LIGHT 60

/* optical sensor settings */
#define SCROLL_DIVIDER 12
#define CPI_1 600

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
