#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    atset
#define PRODUCT         rotary

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1
#define MATRIX_ROW_PINS { B2 }
#define MATRIX_COL_PINS { B4 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/*#define RGB_DI_PIN F4
#define DRIVER_LED_TOTAL 6
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES*/

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5
#define VIAL_KEYBOARD_UID {0x6F, 0xD2, 0x03, 0xC4, 0x16, 0xAF, 0x61, 0x27}
#define VIAL_UNLOCK_COMBO_ROWS { 1, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

#define ENCODERS_PAD_A { D7 }
#define ENCODERS_PAD_B { E6 }
