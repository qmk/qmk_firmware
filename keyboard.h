#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>
#include "host.h"


/* keyboard Modifiers in boot protocol report */
#define BIT_LCTRL   (1<<0)
#define BIT_LSHIFT  (1<<1)
#define BIT_LALT    (1<<2)
#define BIT_LGUI    (1<<3)
#define BIT_RCTRL   (1<<4)
#define BIT_RSHIFT  (1<<5)
#define BIT_RALT    (1<<6)
#define BIT_RGUI    (1<<7)
#define BIT_LCTL BIT_LCTRL
#define BIT_RCTL BIT_RCTRL
#define BIT_LSFT BIT_LSHIFT
#define BIT_RSFT BIT_RSHIFT


extern report_keyboard_t *keyboard_report;
extern report_keyboard_t *keyboard_report_prev;

void keyboard_set_led(uint8_t led);
void keyboard_send(void);

void keyboard_add_key(uint8_t key);
void keyboard_add_mod_bit(uint8_t mod);
void keyboard_set_mods(uint8_t mods);
void keyboard_add_code(uint8_t code);
void keyboard_swap_report(void);
void keyboard_clear_report(void);

uint8_t keyboard_has_anykey(void);
uint8_t *keyboard_get_keys(void);
uint8_t keyboard_get_mods(void);

#endif


