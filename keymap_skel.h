#ifndef KEYMAP_SKEL_H
#define KEYMAP_SKEL_H 1

#include <stdint.h>
#include <stdbool.h>
#include "usb_keycodes.h"


uint8_t keymap_get_keycode(int row, int col);
uint8_t keymap_get_keycodel(int layer, int row, int col);
int keymap_get_layer(void);
int keymap_set_layer(int layer);

/* process Fn keys. This.should be called every scan. */
void keymap_fn_proc(int fn_bits);

#endif
