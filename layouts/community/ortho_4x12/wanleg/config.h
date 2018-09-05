#ifndef CONFIG_USER_H
#define CONFIG_USER_H

//QMK DFU settings (ProMicro boards with QMK bootloader)
// set top left key as bootloader mode escape key on Lets Split rev2
#if defined(KEYBOARD_lets_split_rev2)
#define QMK_LED B0
#define QMK_ESC_OUTPUT F6 // usually COL
#define QMK_ESC_INPUT D7 // usually ROW
#define USE_SERIAL
#undef USE_I2C
#define EE_HANDS
#endif

// set top left key as bootloader mode escape key on 4x4 48key layout
#if defined(KEYBOARD_4x4)
#define QMK_LED B0
#define QMK_ESC_OUTPUT C6 // usually COL
#define QMK_ESC_INPUT B2 // usually ROW

// use alternate settings for 4x4 board using ProMicro instead of Micro
// usage: make 4x4:wanleg PM=yes
#if defined(PRO_MICRO_yes)
#define MATRIX_COLS 12
#define MATRIX_COL_PINS { C6, D7, E6, B4, B5, B6, B3, B1, F7, F6, F5, F4 }
#endif

#endif

#endif
