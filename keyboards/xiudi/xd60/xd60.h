#pragma once

#include "quantum.h"

/* XD60 LEDs
 *   GPIO pads
 *   0 F7 not connected
 *   1 F6 RGB PWM Underglow
 *   2 F5 Backlight LED
 *   3 F4 not connected
 *   B2 Capslock LED
 *   B0 not connected
 */
inline void xd60_caps_led_on(void)    { DDRB |=  (1<<2); PORTB &= ~(1<<2); }
inline void xd60_bl_led_on(void)      { DDRF |=  (1<<5); PORTF &= ~(1<<5); }

inline void xd60_caps_led_off(void)   { DDRB &= ~(1<<2); PORTB &= ~(1<<2); }
inline void xd60_bl_led_off(void)     { DDRF &= ~(1<<5); PORTF &= ~(1<<5); }
