/**
 * Backlighting code for PS2AVRGB boards (ATMEGA32A)
 * Kenneth A. (github.com/krusli | krusli.me)
 */

#ifndef BACKLIGHT_CUSTOM_H
#define BACKLIGHT_CUSTOM_H

#include <avr/pgmspace.h>
void b_led_init_ports(void);
void b_led_set(uint8_t level);
void b_led_task(void);
void setPWM(uint16_t xValue);

#endif  // BACKLIGHT_CUSTOM_H
