#pragma once

//QMK DFU settings (ProMicro boards)
// set top left key as bootloader mode escape key on Gherkin
#if defined(KEYBOARD_40percentclub_gherkin) && !defined(FLIP) 
#define QMK_LED B0
#define QMK_ESC_OUTPUT B4 // usually COL
#define QMK_ESC_INPUT F7 // usually ROW
#endif

//change gherkin orientation (i.e. move USB port from right side to left side)
#if defined(KEYBOARD_40percentclub_gherkin) && defined(FLIP) 
//need to fix QMKdfu setting:
#define QMK_ESC_OUTPUT B6 // usually COL
#define QMK_ESC_INPUT D0 // usually ROW
#define QMK_LED B0

//need to undefine standard 4x4 array before defining alternate ProMicro array
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
//standard config:
//#define MATRIX_ROW_PINS { F7, B1, B3, B2, B6 }
//#define MATRIX_COL_PINS { B4, E6, D7, C6, D4, D0 }
#define MATRIX_ROW_PINS { B6, B2, B3, B1, F7 }
#define MATRIX_COL_PINS { D0, D4, C6, D7, E6, B4 }
#endif
