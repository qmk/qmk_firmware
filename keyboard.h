#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>


void keyboard_init(void);
void keyboard_proc(void);
void keyboard_set_leds(uint8_t leds);

#endif
