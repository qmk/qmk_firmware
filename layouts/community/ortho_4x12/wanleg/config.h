#pragma once

#if defined(KEYBOARD_jj40)
#undef BACKLIGHT_BREATHING
#undef BACKLIGHT_LEVELS
#undef BREATHING_PERIOD
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3
#define BREATHING_PERIOD 15
#endif

//QMK DFU settings (ProMicro boards with QMK bootloader)
// set top left key as bootloader mode escape key on Lets Split rev2
#if defined(KEYBOARD_lets_split_rev2)
#define QMK_LED B0
#define QMK_ESC_OUTPUT F6 // usually COL
#define QMK_ESC_INPUT D7 // usually ROW
#undef USE_I2C
#define EE_HANDS
#endif

// set top left key as bootloader mode escape key on Nori
#if defined(KEYBOARD_40percentclub_nori)
#define QMK_LED B0
#define QMK_ESC_OUTPUT F4 // usually COL
#define QMK_ESC_INPUT D3 // usually ROW
#endif

// set top left key as bootloader mode escape key on 4x4 48key layout
#if defined(KEYBOARD_40percentclub_4x4) && !defined(PRO_MICRO)
#define QMK_LED B0
#define QMK_ESC_OUTPUT C6 // usually COL
#define QMK_ESC_INPUT B2 // usually ROW
#endif

// use alternate settings for 4x4 board using ProMicro instead of Micro
// usage: make 4x4:wanleg PM=yes
#if defined(KEYBOARD_40percentclub_4x4) && defined(PRO_MICRO)
#define QMK_ESC_OUTPUT F4 // usually COL
#define QMK_ESC_INPUT D1 // usually ROW
#define QMK_LED B0

//need to undefine standard 4x4 array before defining alternate ProMicro array
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#define MATRIX_ROW_PINS { D1, D0, D4, C6 }
//last 4 elements of the column array are not broken out on a ProMicro (included only to preserve array structure)
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2, B6, B5, B4, E6, D7, F0, B7, D6, F1 }
#endif
