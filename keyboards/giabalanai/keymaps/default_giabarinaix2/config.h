#pragma once

#define GIABARINAIX2
#ifdef GIABARINAIX2
#    undef MATRIX_ROW_PINS_RIGHT
#    undef MATRIX_COL_PINS_RIGHT

#    ifdef RGBLIGHT_ENABLE
#        undef RGBLED_NUM
#        define RGBLED_NUM 120
#        undef RGBLIGHT_LED_MAP
#        define RGBLIGHT_LED_MAP { \
           108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, \
           107, 106, 105, 104, 103, 102, 101, 100, 99,  98,  97,  96, \
           84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95, \
           83,  82,  81,  80,  79,  78,  77,  76,  75,  74,  73,  72, \
           60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71, \
           \
           11,  10,  9,   8,   7,   6,   5,   4,   3,   2,   1,   0,  \
           12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23, \
           35,  34,  33,  32,  31,  30,  29,  28,  27,  26,  25,  24, \
           36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47, \
           59,  58,  57,  56,  55,  54,  53,  52,  51,  50,  49,  48  \
           }
#    endif
#endif
