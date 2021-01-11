/**
 * Backlighting code for PS2AVRGB boards (ATMEGA32A)
 * Kenneth A. (github.com/krusli | krusli.me)
 */

#pragma once

#include <avr/pgmspace.h>
void b_led_init_ports(void);
void b_led_set(uint8_t level);
void b_led_task(void);
void setPWM(uint16_t xValue);

