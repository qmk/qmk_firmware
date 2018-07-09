#ifndef SIXSHOOTER_H
#define SIXSHOOTER_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
	K00, K01, K02, \
	K03, K04, K05 \
) { \
	{ K00, K01, K02, K03, K04, K05 }, \
}

inline void sixshooter_led_1_on(void)    { DDRB |=  (1<<6); PORTB |=  (1<<6); }
inline void sixshooter_led_2_on(void)    { DDRC |=  (1<<7); PORTC |=  (1<<7); }
inline void sixshooter_led_3_on(void)    { DDRD |=  (1<<0); PORTD |=  (1<<0); }
inline void sixshooter_led_4_on(void)    { DDRB |=  (1<<5); PORTB |=  (1<<5); }
inline void sixshooter_led_5_on(void)    { DDRD |=  (1<<7); PORTD |=  (1<<7); }
inline void sixshooter_led_6_on(void)    { DDRB |=  (1<<7); PORTB |=  (1<<7); }

inline void sixshooter_led_1_off(void)   { DDRB &= ~(1<<6); PORTB &= ~(1<<6); }
inline void sixshooter_led_2_off(void)   { DDRC &= ~(1<<7); PORTC &= ~(1<<7); }
inline void sixshooter_led_3_off(void)   { DDRD &= ~(1<<0); PORTD &= ~(1<<0); }
inline void sixshooter_led_4_off(void)   { DDRB &= ~(1<<5); PORTB &= ~(1<<5); }
inline void sixshooter_led_5_off(void)   { DDRD &= ~(1<<7); PORTD &= ~(1<<7); }
inline void sixshooter_led_6_off(void)   { DDRB &= ~(1<<7); PORTB &= ~(1<<7); }

inline void sixshooter_led_all_on(void) {
  sixshooter_led_1_on();
  sixshooter_led_2_on();
  sixshooter_led_3_on();
  sixshooter_led_4_on();
  sixshooter_led_5_on();
  sixshooter_led_6_on();
}
inline void sixshooter_led_all_off(void) {
  sixshooter_led_1_off();
  sixshooter_led_2_off();
  sixshooter_led_3_off();
  sixshooter_led_4_off();
  sixshooter_led_5_off();
  sixshooter_led_6_off();
}

#endif
