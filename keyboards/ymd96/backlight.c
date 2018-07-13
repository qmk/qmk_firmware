/**
 * Backlighting code for PS2AVRGB boards (ATMEGA32A)
 * Kenneth A. (github.com/krusli | krusli.me)
 */

#include "backlight.h"
#include "quantum.h"

#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "backlight_custom.h"
#include "breathing_custom.h"

// DEBUG
#include <stdlib.h>
#include <stdio.h>

// Port D: digital pins of the AVR chipset
#define NUMLOCK_PORT    (1 << 0)  // 0th pin of Port D (digital)
#define CAPSLOCK_PORT   (1 << 1)  // 1st pin
#define BACKLIGHT_PORT  (1 << 4)  // 4th pin
//#define SCROLLLOCK_PORT (1 << 6)  // 6th pin

#define TIMER_CLK_DIV64			  0x03	///< Timer clocked at F_CPU/64
#define TIMER1PRESCALE	TIMER_CLK_DIV64 ///< timer 1 prescaler default

#define TIMER_PRESCALE_MASK		0x07	///< Timer Prescaler Bit-Mask

#define PWM_MAX 0xFF
#define TIMER_TOP 255 // 8 bit PWM

extern backlight_config_t backlight_config;

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

  /* YMD96 does not have scroll lock led  
   if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
      DDRD  |= SCROLLLOCK_PORT;
      PORTD |= SCROLLLOCK_PORT;
    } else {
      DDRD  &= ~SCROLLLOCK_PORT;
      PORTD &= ~SCROLLLOCK_PORT;
    }*/
}

#ifdef BACKLIGHT_ENABLE

// sets up Timer 1 for 8-bit PWM
void timer1PWMSetup(void) { // NOTE ONLY CALL THIS ONCE
  // default 8 bit mode
  TCCR1A &= ~(1 << 1); // cbi(TCCR1A,PWM11); <- set PWM11 bit to HIGH
  TCCR1A |= (1 << 0);  // sbi(TCCR1A,PWM10); <- set PWM10 bit to LOW

  // clear output compare value A
  // outb(OCR1AH, 0);
  // outb(OCR1AL, 0);

  // clear output comparator registers for B
	OCR1BH = 0; // outb(OCR1BH, 0);
	OCR1BL = 0; // outb(OCR1BL, 0);
}

bool is_init = false;
void timer1Init(void) {
  // timer1SetPrescaler(TIMER1PRESCALE)
  // set to DIV/64
  (TCCR1B) = ((TCCR1B) & ~TIMER_PRESCALE_MASK) | TIMER1PRESCALE;

  // reset TCNT1
  TCNT1H = 0;  // outb(TCNT1H, 0);
	TCNT1L = 0;  // outb(TCNT1L, 0);

  // TOIE1: Timer Overflow Interrupt Enable (Timer 1);
	TIMSK |= _BV(TOIE1); // sbi(TIMSK, TOIE1);

  is_init = true;
}

void timer1UnInit(void) {
  // set prescaler back to NONE
  (TCCR1B) = ((TCCR1B) & ~TIMER_PRESCALE_MASK) | 0x00;  // TIMERRTC_CLK_STOP

  // disable timer overflow interrupt
  TIMSK &= ~_BV(TOIE1); // overflow bit?

  setPWM(0);

  is_init = false;
}


// handle TCNT1 overflow
//! Interrupt handler for tcnt1 overflow interrupt
ISR(TIMER1_OVF_vect, ISR_NOBLOCK)
{
	// sei();
  // handle breathing here
  #ifdef BACKLIGHT_BREATHING
  if (is_breathing()) {
    custom_breathing_handler();
  }
  #endif

  // TODO call user defined function
}

// enable timer 1 PWM
// timer1PWMBOn()
void timer1PWMBEnable(void) {
  // turn on channel B (OC1B) PWM output
  // set OC1B as non-inverted PWM
  TCCR1A |= _BV(COM1B1);
  TCCR1A &= ~_BV(COM1B0);
}

// disable timer 1 PWM
// timer1PWMBOff()
void timer1PWMBDisable(void) {
  TCCR1A &= ~_BV(COM1B1);
  TCCR1A &= ~_BV(COM1B0);
}

void enableBacklight(void) {
  DDRD  |= BACKLIGHT_PORT;  // set digital pin 4 as output
  PORTD |= BACKLIGHT_PORT;  // set digital pin 4 to high
}

void disableBacklight(void) {
  // DDRD  &= ~BACKLIGHT_PORT;  // set digital pin 4 as input
  PORTD &= ~BACKLIGHT_PORT;  // set digital pin 4 to low
}

void startPWM(void) {
  timer1Init();
  timer1PWMBEnable();
  enableBacklight();
}

void stopPWM(void) {
  timer1UnInit();
  disableBacklight();
  timer1PWMBDisable();
}

void b_led_init_ports(void) {
  /* turn backlight on/off depending on user preference */
  #if BACKLIGHT_ON_STATE == 0
    // DDRx register: sets the direction of Port D
    // DDRD  &= ~BACKLIGHT_PORT;  // set digital pin 4 as input
    PORTD &= ~BACKLIGHT_PORT;  // set digital pin 4 to low
  #else
    DDRD  |= BACKLIGHT_PORT;  // set digital pin 4 as output
    PORTD |= BACKLIGHT_PORT;  // set digital pin 4 to high
  #endif

  timer1PWMSetup();
  startPWM();

  #ifdef BACKLIGHT_BREATHING
  breathing_enable();
  #endif
}

void b_led_set(uint8_t level) {
  if (level > BACKLIGHT_LEVELS) {
    level = BACKLIGHT_LEVELS;
  }

  setPWM((int)(TIMER_TOP * (float) level / BACKLIGHT_LEVELS));
}

// called every matrix scan
void b_led_task(void) {
  // do nothing for now
}

void setPWM(uint16_t xValue) {
  if (xValue > TIMER_TOP) {
    xValue = TIMER_TOP;
  }
  OCR1B = xValue; // timer1PWMBSet(xValue);
}

#endif  // BACKLIGHT_ENABLE
