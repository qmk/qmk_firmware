#ifndef KEYMAP_H
#define KEYMAP_H 1

#include <stdint.h>
#include "usbkeycodes.h"

uint8_t get_keycode(uint8_t row, uint8_t col);

#define MATRIX_ROWS 9
#define MATRIX_COLS 8

#endif
