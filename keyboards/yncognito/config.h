#pragma once

#include "config_common.h"

#define VENDOR_ID       0x7979
#define PRODUCT_ID      0x6604
#define DEVICE_VER      0x0001
#define MANUFACTURER    Yncognito
#define PRODUCT         SL8
#define DESCRIPTION     8 key macro with knob


#define MATRIX_ROWS 2
#define MATRIX_COLS 5


#define MATRIX_ROW_PINS { B4, D7 }
#define MATRIX_COL_PINS { B0, B1, B2, B3, D5 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { B5}
#define ENCODERS_PAD_B { B6}
#define ENCODER_RESOLUTION 4

#define RGB_DI_PIN E6
#define DRIVER_LED_TOTAL 8
#define RGB_MATRIX_KEYPRESSES 
#define RGB_MATRIX_KEYRELEASES 
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0 
#define RGB_DISABLE_WHEN_USB_SUSPENDED false 
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255 
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL