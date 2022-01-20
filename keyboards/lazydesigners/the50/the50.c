#include "the50.h"

void the50_led_on() {
  DDRB |= (1 << 7); PORTB &= ~(1 << 7);
}

void the50_led_off() {
  DDRB &= ~(1 << 7); PORTB &= ~(1 << 7);
}
