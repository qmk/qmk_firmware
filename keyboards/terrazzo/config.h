#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"


/* USB Device descriptor parameter */
#define VENDOR_ID       0x4d4d // MM
#define PRODUCT_ID      0x545a // TZ
#define DEVICE_VER      0x0002
#define MANUFACTURER    MsMustard
#define PRODUCT         Terrazzo
#define DESCRIPTION     40% Keyboard with LED Matrix

/* key matrix size */

// SWAP FOR PRO MICRO
// #define MATRIX_ROWS 8
#define MATRIX_ROWS 9
#define MATRIX_COLS 6

/* key matrix pins */

// SWAP FOR PRO MICRO
// #define MATRIX_ROW_PINS { D2, D7, E6, B4, B5, B6, B2, B3 }
#define MATRIX_ROW_PINS { D2, D7, E6, B4, B5, B6, B2, B3, F0 }
#define MATRIX_COL_PINS { D3, F4, F5, F6, F7, B1 }

#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

/* ROTARY ENCODERS */

/* 4 encoder positions are supported. With multiple
encoder support when using the extra pins of
Elite-C controller.

Use the following configuration guides for your
encoder layout. */

/* PRO MICRO CONFIGURATIONS */

/* If using a Pro Micro, only 1 encoder may be used,
and only in the top or bottom position.
Top and bottom encoders share the same net,
so there is only one configuration. */

/* TOP or BOTTOM */
// #define ENCODERS_PAD_A { C6 }
// #define ENCODERS_PAD_B { D4 }

/* ELITE-C ONLY CONFIGURATIONS */

/* TOP 3
   Default configuration */
#define ENCODERS_PAD_A { C6 , B7, C7 }
#define ENCODERS_PAD_B { D4 , D5, F1 }

/* BOTTOM 3 */
// #define ENCODERS_PAD_A { B7, C7, C6 }
// #define ENCODERS_PAD_B { D5, F1, D4 }

/* BOTTOM 2 */
// #define ENCODERS_PAD_A { C7, C6 }
// #define ENCODERS_PAD_B { F1, D4 }


#define ENCODER_RESOLUTION 2
#define BACKLIGHT_LEVELS 5

#ifdef LED_MATRIX_ENABLE

#define LED_DRIVER_ADDR_1 0x74 
#define LED_DRIVER_COUNT 1
#define LED_DRIVER_LED_COUNT 105
#define LED_MATRIX_ROWS 15
#define LED_MATRIX_COLS 7
#define LED_MATRIX_MAXIMUM_BRIGHTNESS 20
#define LED_DISABLE_WHEN_USB_SUSPENDED true

#endif
#endif

/* Terrazzo animations */

// #define DISABLE_TERRAZZO_EFFECT_STRIPES
// #define DISABLE_TERRAZZO_EFFECT_DINO
// #define DISABLE_TERRAZZO_EFFECT_OUTRUN
#define DISABLE_TERRAZZO_EFFECT_PAC_DUDE
#define DISABLE_TERRAZZO_EFFECT_HEART
// #define DISABLE_TERRAZZO_EFFECT_WPM_CHART
#define DISABLE_TERRAZZO_EFFECT_DOT
