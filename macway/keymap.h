#ifndef KEYMAP_H
#define KEYMAP_H 1

#include <stdint.h>
#include <stdbool.h>
#include "usb_keycodes.h"


#define MATRIX_ROWS 9
#define MATRIX_COLS 8


extern int current_layer;
extern bool key_sent;


int get_layer(void);
uint8_t get_keycode(int layer, int row, int col);

#endif
