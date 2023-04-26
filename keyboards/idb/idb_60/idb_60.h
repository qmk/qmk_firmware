#pragma once

#include "quantum.h"

void _idb_60_caps_led_on(void);
void _idb_60_fn_led_on(void);
void _idb_60_caps_led_off(void);
void _idb_60_fn_led_off(void);

#define _idb_60_esc_led_on() _idb_60_fn_led_on()
#define _idb_60_esc_led_off() _idb_60_fn_led_off()
