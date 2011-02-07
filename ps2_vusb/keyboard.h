#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>
#include "host.h"


void keyboard_set_led(uint8_t led);
void keyboard_send(void);
bool keyboard_has_key(void);
void keyboard_add_mod(uint8_t mod);
void keyboard_add_key(uint8_t key);
void keyboard_add_code(uint8_t code);
void keyboard_swap_report(void);
void keyboard_clear_report(void);
report_keyboard_t *keyboard_report(void);
report_keyboard_t *keyboard_report_prev(void);

#endif


