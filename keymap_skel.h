#ifndef KEYMAP_SKEL_H
#define KEYMAP_SKEL_H 1

#include <stdint.h>
#include <stdbool.h>
#include "usb_keycodes.h"


/* keycode in specific layer */
uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col);

/* layer to move during press Fn key */
uint8_t keymap_fn_layer(uint8_t fn_bits);

/* keycode to send when release Fn key without using */
uint8_t keymap_fn_keycode(uint8_t fn_bits);

/* whether special key combination */
bool keymap_is_special_mode(uint8_t fn_bits);

#endif
