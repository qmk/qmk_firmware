#ifndef TEENSY_H
#define TEENSY_H 1

// for Teensy/Teensy++ 2.0
#define DEBUG_LED 1
#define DEBUG_LED_CONFIG    (DDRD |= (1<<6))
#define DEBUG_LED_ON        (PORTD |= (1<<6))
#define DEBUG_LED_OFF       (PORTD &= ~(1<<6))

#endif
