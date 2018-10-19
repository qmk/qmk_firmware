#pragma once

//QMK DFU settings (ProMicro boards)
// set top left key as bootloader mode escape key on Gherkin
#if defined(KEYBOARD_5x5)
#define QMK_LED B0
#define QMK_ESC_OUTPUT D7 // usually COL
#define QMK_ESC_INPUT B2 // usually ROW
#endif
