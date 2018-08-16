#pragma once

//QMK DFU settings (ProMicro boards)
// set top left key as bootloader mode escape key on Gherkin
#if defined(KEYBOARD_gherkin)
#define QMK_LED B0
#define QMK_ESC_OUTPUT B4 // usually COL
#define QMK_ESC_INPUT F7 // usually ROW
#endif
