/**
 * Backlighting code for PS2AVRGB boards (ATMEGA32A)
 * By Kenneth (github.com/krusli | krusli.me)
 */

#include "backlight.h"
#include "quantum.h"
#include <avr/pgmspace.h>

// Port D: digital pins of the AVR chipset
#define NUMLOCK_PORT    (1 << 1)  // 1st pin of Port D (digital)
#define CAPSLOCK_PORT   (1 << 2)  // 2nd pin
#define BACKLIGHT_PORT  (1 << 4)  // 4th pin
#define SCROLLLOCK_PORT (1 << 6)  // 6th pin

#define BACKLIGHT_CUSTOM_DRIVER
#define BACKLIGHT_LEVELS 12 // downLevelMax

#define PWM_MAX 0xFF

extern backlight_config_t backlight_config;
/*
References
Port Registers: https://www.arduino.cc/en/Reference/PortManipulation
TCCR1A: https://electronics.stackexchange.com/questions/92350/what-is-the-difference-between-tccr1a-and-tccr1b
Timers: http://www.avrbeginners.net/architecture/timers/timers.html

TCCR: Timer/Counter Control Register - used to set timer mode, prescaler, other options
7      6       5       4       3       2       1       0
COM1A1 COM1A0                                  PWM11   PWM10
*/

// Function signatures
void setPWM(int xValue);
uint16_t getBrightness(uint16_t value);

// turn LEDs on and off depending on USB caps/num/scroll lock states.
void led_set_user(uint8_t usb_led) {
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
}

// @Override
void backlight_init_ports(void) {
  /* turn backlight on/off depending on user preference */
  #if BACKLIGHT_ON_STATE == 0
    // DDRx register: sets the direction of Port D
    DDRD  |= BACKLIGHT_PORT;  // set digital pin 4 as output
    PORTD |= BACKLIGHT_PORT;  // set digital pin 4 to high
  #else
    DDRD  &= ~BACKLIGHT_PORT;  // set digital pin 4 as input
    PORTD &= ~BACKLIGHT_PORT;  // set digital pin 4 to low
  #endif

  /* initialise timers */
    /* set prescaler on timer 1 */
    // set timer resolution to 8 bits
    TCCR1A &= ~(1 << 1);  // cbi(TCCR1A, PWM11);
    TCCR1A |= (1 << 0);   // sbi(TCCR1A, PWM10);

    // commented out in source/timer.c; enabled in AVR's original code
  	// clear output compare value A
    // outb(OCR1AH, 0);
    // outb(OCR1AL, 0);

  	// clear output compare value B
  	(OCR1BH) = 0;  // outb(OCR1BH, 0);
  	(OCR1BL) = 0;  // outb(OCR1BL, 0);
  /* END initialise timers */
}

// @Override
void backlight_set(uint8_t level) {
  if (level > BACKLIGHT_LEVELS) {
    level = BACKLIGHT_LEVELS;
  }

  if (level == 0) {
    // turn off LEDs
    DDRD  &= ~BACKLIGHT_PORT;  // set digital pin 4 as input
    PORTD &= ~BACKLIGHT_PORT;  // set digital pin 4 to low
  }

  uint16_t valueToSet = getBrightness(level);
  setPWM((int) valueToSet);
}

// @Override
// called every matrix scan
void backlight_task(void) {
  if (backlight_config.enable) {
    DDRD  |= BACKLIGHT_PORT;  // set digital pin 4 as output
    PORTD |= BACKLIGHT_PORT;  // set digital pin 4 to high
  } else {
    DDRD  &= ~BACKLIGHT_PORT;  // set digital pin 4 as input
    PORTD &= ~BACKLIGHT_PORT;  // set digital pin 4 to low
  }

  // update backlight: update/compare against PWM registers
}

/*
void backlight_toggle(void);  // update state, store in EEPROM (eeconfig_update_backlight)
void backlight_step(void);    // update state
void backlight_increase(void);  // also only updates state
void backlight_decrease(void);  // also only updates state
*/

void setPWM(int xValue){
    // if(_ledOff) return;  // TODO check backlight_config
    OCR1B = xValue; // timer1PWMBSet(xValue);
}

// NOTE originally static
uint16_t getBrightness(uint16_t value) {
  return value / BACKLIGHT_LEVELS * PWM_MAX;
}
