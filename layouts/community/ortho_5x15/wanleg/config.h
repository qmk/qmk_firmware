#pragma once

// set top left key as bootloader mode escape key on 5x5 75key layout
#if defined(KEYBOARD_5x5) && !defined(PRO_MICRO)
#define QMK_LED B0
#define QMK_ESC_OUTPUT D7 // usually COL
#define QMK_ESC_INPUT B2 // usually ROW
#endif