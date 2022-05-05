#pragma once
#ifndef NUM_GPIO_PORTS
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)
#    define NUM_GPIO_PORTS 5
#elif defined(__AVR_AT90USB162__) || defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#    define NUM_GPIO_PORTS 3
#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#    define NUM_GPIO_PORTS 6
#elif defined(__AVR_ATmega32A__)
#    define NUM_GPIO_PORTS 4
#elif defined(__AVR_ATtiny85__)
#    define NUM_GPIO_PORTS 1
#endif
#endif // NUM_GPIO_PORTS
