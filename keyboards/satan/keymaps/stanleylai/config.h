#include "../../config.h"

// USB Device descriptor parameter
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0003
#define MANUFACTURER    Custom
#define PRODUCT         GH60 rev.CHN
#define DESCRIPTION     QMK keyboard firmware for GH60 with WS2812 support

// Backlight configuration
#define BACKLIGHT_LEVELS 3

// Underlight configuration
#define RGB_DI_PIN E2
#define RGBLIGHT_TIMER
#define RGBLED_NUM 6        // Number of LEDs
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
