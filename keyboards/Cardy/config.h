#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6090
#define DEVICE_VER      0x0002
#define MANUFACTURER    RD_team
#define PRODUCT         Cardy
#define DESCRIPTION     RD_team 2020

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 2

/* key matrix pins */
#define MATRIX_ROW_PINS { B0,F6 }
#define MATRIX_COL_PINS { B3, B2}
#define UNUSED_PINS

/* key matrix Encoders */

#define ENCODERS_PAD_A { D6, C7 }
#define ENCODERS_PAD_B { D7, C6 }
#define ENCODER_RESOLUTION 4

/* key matrix Encoder switch */
#define DIP_SWITCH_PINS { D4,B7 }


/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

//OLED
#define OLED_FONT_WIDTH 6
#define OLED_FONT_HEIGHT 11