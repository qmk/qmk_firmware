


#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xBB01
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0002
#define MANUFACTURER Hanachi
#define PRODUCT Willow64
#define DESCRIPTION Willow64 ergo keyboard

#define MATRIX_ROWS 10
#define MATRIX_COLS 8

#define MATRIX_ROW_PINS { D4, C6, D7, E6, B4}
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6}
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW

#define MASTER_LEFT
#define SOFT_SERIAL_PIN D2
#define USE_SERIAL
#define SELECT_SOFT_SERIAL_SPEED 1
#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define RGBLED_SPLIT {29, 35}
#define RGB_DI_PIN D3
#define RGBLED_NUM 64
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 100 /* The maximum brightness level */
#define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_ANIMATIONS

