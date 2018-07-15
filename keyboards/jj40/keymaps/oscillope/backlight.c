/**
 * Backlighting code for PS2AVRGB boards (ATMEGA32A)
 * Kenneth A. (github.com/krusli | krusli.me)
 */

#include "quantum.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>

// Port D: digital pins of the AVR chipset
#define NUMLOCK_PORT    (1 << 1)  // 1st pin of Port D (digital)
#define CAPSLOCK_PORT   (1 << 2)  // 2nd pin
#define BACKLIGHT_PORT  (1 << 4)  // 4th pin
#define SCROLLLOCK_PORT (1 << 6)  // 6th pin

/**
 * References
 * Port Registers: https://www.arduino.cc/en/Reference/PortManipulation
 * TCCR1A: https://electronics.stackexchange.com/questions/92350/what-is-the-difference-between-tccr1a-and-tccr1b
 * Timers: http://www.avrbeginners.net/architecture/timers/timers.html
 * 16-bit timer setup: http://sculland.com/ATmega168/Interrupts-And-Timers/16-Bit-Timer-Setup/
 * PS2AVRGB firmware: https://github.com/showjean/ps2avrU/tree/master/firmware
 */

// @Override
// turn LEDs on and off depending on USB caps/num/scroll lock states.
void led_set_user(uint8_t usb_led) {
/* It appears that these cause the v1 JJ40 PCB to hang.
 * I haven't looked into why, but I don't have any LEDs on my board anyway. */
#if 0
    if (usb_led & (1 << USB_LED_NUM_LOCK)) {
      // turn on
      DDRD  |= NUMLOCK_PORT;
      PORTD |= NUMLOCK_PORT;
    } else {
      // turn off
      DDRD  &= ~NUMLOCK_PORT;
      PORTD &= ~NUMLOCK_PORT;
    }

    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
      DDRD  |= CAPSLOCK_PORT;
      PORTD |= CAPSLOCK_PORT;
    } else {
      DDRD  &= ~CAPSLOCK_PORT;
      PORTD &= ~CAPSLOCK_PORT;
    }

    if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
      DDRD  |= SCROLLLOCK_PORT;
      PORTD |= SCROLLLOCK_PORT;
    } else {
      DDRD  &= ~SCROLLLOCK_PORT;
      PORTD &= ~SCROLLLOCK_PORT;
    }
#endif
}

