#pragma once

#include "config_common.h"

#define VENDOR_ID 0x0000
#define PRODUCT_ID 0x0001
#define DEVICE_VER 0x0001
#define MANUFACTURER mangoiv
#define PRODUCT draculad
#define DESCRIPTION a < 40 - key input device

#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS {D4, C6, D7, E6}
#define MATRIX_COL_PINS {F4, F5,F6, F7, B1}

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5


#define USE_SERIAL
#define SOFT_SERIAL_PIN D2

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 30000
#endif

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLED_NUM 10
#define RGBLIGHT_SPLIT
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_SLEEP
#endif

#define ENCODERS_PAD_A {B2 , B4}
#define ENCODERS_PAD_B {B6 , B5}

#define ENCODER_RESOLUTIONS { 4, 4, 4, 1}
#define UNUSED_PINS

#define EE_HANDS