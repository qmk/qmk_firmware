#pragma once

#include "quantum.h"

#define LAYOUT( \
    k00, k01, k02, \
    k10, k11, k12 \
) { \
    { k00, k01, k02 }, \
    { k10, k11, k12 } \
}

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
