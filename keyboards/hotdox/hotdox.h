#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>

void init_ergodox(void);

inline void ergodox_board_led_on(void)    { DDRB |= (1<<PB7); PORTB |= (1<<PB7);  }
inline void ergodox_right_led_1_on(void)  { DDRB |= (1<<PB5); PORTB &= ~(1<<PB5); }
inline void ergodox_right_led_2_on(void)  { DDRB |= (1<<PB6); PORTB &= ~(1<<PB6); }
inline void ergodox_right_led_3_on(void)  { DDRB |= (1<<PB4); PORTB &= ~(1<<PB4); }

inline void ergodox_board_led_off(void)   { DDRB |= (1<<PB7); PORTB &= ~(1<<PB7); }
inline void ergodox_right_led_1_off(void) { DDRB |= (1<<PB5); PORTB |= (1<<PB5);  }
inline void ergodox_right_led_2_off(void) { DDRB |= (1<<PB6); PORTB |= (1<<PB6);  }
inline void ergodox_right_led_3_off(void) { DDRB |= (1<<PB4); PORTB |= (1<<PB4);  }

inline void ergodox_right_led_on(uint8_t l) {
    switch (l) {
         case 1:
             ergodox_right_led_1_on();
             break;
         case 2:
             ergodox_right_led_2_on();
             break;
         case 3:
             ergodox_right_led_3_on();
             break;
         default:
             break;
        }
}

inline void ergodox_right_led_off(uint8_t l) {
    switch (l) {
         case 1:
             ergodox_right_led_1_off();
             break;
         case 2:
             ergodox_right_led_2_off();
             break;
         case 3:
             ergodox_right_led_3_off();
             break;
         default:
             break;
        }
}

inline void ergodox_led_all_on(void) {
    ergodox_board_led_on();
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
}

inline void ergodox_led_all_off(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

inline void ergodox_right_led_1_set(uint8_t n)          {}
inline void ergodox_right_led_2_set(uint8_t n)          {}
inline void ergodox_right_led_3_set(uint8_t n)          {}
inline void ergodox_right_led_set(uint8_t l, uint8_t n) {}
inline void ergodox_led_all_set(uint8_t n)              {}

void ergodox_blink_all_leds(void);
