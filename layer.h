#ifndef LAYER_H
#define LAYER_H 1

#include <stdint.h>

uint8_t default_layer;
uint8_t current_layer;

/* return keycode for switch */
uint8_t layer_get_keycode(uint8_t row, uint8_t col);

/* process layer switching */
void layer_switching(uint8_t fn_bits);

#endif
