#ifndef ARROW_PAD_H
#define ARROW_PAD_H

#include "matrix.h"
#include "keymap_common.h"
#ifdef BACKLIGHT_ENABLE
	#include "backlight.h"
#endif
#include <avr/io.h>
#include <stddef.h>

void matrix_init_user(void);
void matrix_scan_user(void);
bool process_action_user(keyrecord_t *record);
void led_set_user(uint8_t usb_led);
void backlight_init_ports(void);

#endif
