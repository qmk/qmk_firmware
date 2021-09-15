#pragma once

#define VIAL_KEYBOARD_UID {0x44, 0x25, 0x2A, 0x83, 0x83, 0x13, 0x46, 0xEE}
#define VIAL_UNLOCK_COMBO_ROWS { 2, 7 }
#define VIAL_UNLOCK_COMBO_COLS { 2, 0 }

#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL

#define VIAL_COMBO_ENTRIES 4

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS
