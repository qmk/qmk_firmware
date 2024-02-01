#pragma once

#include "quantum.h"

/* DO60 LEDs
 *   GPIO pads
 *   0 F7 not connected
 *   1 F6 not connected
 *   2 F5 RGB PWM Underglow
 *   3 F4 Backlight LED
 *   B2 Capslock LED
 *   B0 not connected
 */

/*
inline void do60_caps_led_on(void)    { DDRB |=  (1<<2); PORTB &= ~(1<<2); }
inline void do60_bl_led_on(void)    	{ DDRF |=  (1<<4); PORTF &= ~(1<<4); }

inline void do60_caps_led_off(void)   { DDRB &= ~(1<<2); PORTB &= ~(1<<2); }
inline void do60_bl_led_off(void)   	{ DDRF &= ~(1<<4); PORTF &= ~(1<<4); }
*/

inline void setdefaultrgb(void){ rgblight_sethsv(100,100,100); }
