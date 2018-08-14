#ifndef SPLIT_KEYBOARD_UTIL_H
#define SPLIT_KEYBOARD_UTIL_H

#include <stdbool.h>
#include "eeconfig.h"

#define SLAVE_I2C_ADDRESS           0x32

extern volatile bool isLeftHand;

// slave version of matrix scan, defined in matrix.c
void matrix_slave_scan(void);

void split_keyboard_setup(void);
bool has_usb(void);
void keyboard_slave_loop(void);

#ifdef SSD1306OLED
void matrix_master_OLED_init(void);
#endif


#endif
