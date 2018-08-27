#ifndef SIXSHOOTER_H
#define SIXSHOOTER_H

#include "quantum.h"

#define LAYOUT( \
	K00, K01, K02, \
	K03, K04, K05 \
) { \
	{ K00, K01, K02, K03, K04, K05 }, \
}


/*
 * Define keyboard specific keycodes for controlling on/off for all LEDs as they
 * are all on different pins with this PCB, rather than a single backlight pin
 */
enum keyboard_keycode {
  SS_LON = SAFE_RANGE,
  SS_LOFF,
  SAFE_RANGE_KB
};

inline void sixshooter_led_0_on(void)    { DDRB |=  (1<<6); PORTB |=  (1<<6); }
inline void sixshooter_led_1_on(void)    { DDRC |=  (1<<7); PORTC |=  (1<<7); }
inline void sixshooter_led_2_on(void)    { DDRD |=  (1<<0); PORTD |=  (1<<0); }
inline void sixshooter_led_3_on(void)    { DDRB |=  (1<<5); PORTB |=  (1<<5); }
inline void sixshooter_led_4_on(void)    { DDRD |=  (1<<7); PORTD |=  (1<<7); }
inline void sixshooter_led_5_on(void)    { DDRB |=  (1<<7); PORTB |=  (1<<7); }

inline void sixshooter_led_0_off(void)   { DDRB &= ~(1<<6); PORTB &= ~(1<<6); }
inline void sixshooter_led_1_off(void)   { DDRC &= ~(1<<7); PORTC &= ~(1<<7); }
inline void sixshooter_led_2_off(void)   { DDRD &= ~(1<<0); PORTD &= ~(1<<0); }
inline void sixshooter_led_3_off(void)   { DDRB &= ~(1<<5); PORTB &= ~(1<<5); }
inline void sixshooter_led_4_off(void)   { DDRD &= ~(1<<7); PORTD &= ~(1<<7); }
inline void sixshooter_led_5_off(void)   { DDRB &= ~(1<<7); PORTB &= ~(1<<7); }

inline void sixshooter_led_all_on(void) {
  sixshooter_led_0_on();
  sixshooter_led_1_on();
  sixshooter_led_2_on();
  sixshooter_led_3_on();
  sixshooter_led_4_on();
  sixshooter_led_5_on();
}
inline void sixshooter_led_all_off(void) {
  sixshooter_led_0_off();
  sixshooter_led_1_off();
  sixshooter_led_2_off();
  sixshooter_led_3_off();
  sixshooter_led_4_off();
  sixshooter_led_5_off();
}

#endif
