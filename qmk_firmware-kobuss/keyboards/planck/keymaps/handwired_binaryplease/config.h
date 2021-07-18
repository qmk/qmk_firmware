#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* USB Device descriptor parameter */



#undef VENDOR_ID
#undef PRODUCT_ID
#undef MANUFACTURER
#undef PRODUCT
#undef DESCRIPTION
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#undef UNUSED_PINS
#undef BACKLIGHT_PIN
#undef BACKLIGHT_LEVELS



#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define MANUFACTURER    binaryplease
#define PRODUCT         Teensy_Planck
#define DESCRIPTION     A compact ortholinear keyboard using a teensy 2.0

#define MATRIX_ROW_PINS { D3, D2, D1, D0 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, B6, B5, B4, D7, D6, D4 }
#define UNUSED_PINS

#define BACKLIGHT_PIN B7

/* number of backlight levels */
#define BACKLIGHT_LEVELS 0


#endif
