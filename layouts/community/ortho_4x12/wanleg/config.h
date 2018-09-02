#ifndef CONFIG_USER_H
#define CONFIG_USER_H

//QMK DFU settings (ProMicro boards)
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
#endif

#endif
