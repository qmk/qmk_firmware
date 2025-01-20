#ifndef HELPERS_H
#define HELPERS_H

#include "quantum.h"

bool is_shift_pressed(void);
bool is_ctrl_pressed(void);
bool is_alt_pressed(void);
bool is_key_press(uint16_t keycode, const keyrecord_t *record);

#endif
