/**
 * Backlighting code for PS2AVRGB boards (ATMEGA32A)
 * By Kenneth (github.com/krusli | krusli.me)
 */

#include "backlight.h"
#include "quantum.h"
#include <avr/pgmspace.h>

#include "backlight_custom.h"

// DEBUG
#include <stdlib.h>
#include <stdio.h>


// Port D: digital pins of the AVR chipset
#define NUMLOCK_PORT    (1 << 1)  // 1st pin of Port D (digital)
#define CAPSLOCK_PORT   (1 << 2)  // 2nd pin
#define BACKLIGHT_PORT  (1 << 4)  // 4th pin
#define SCROLLLOCK_PORT (1 << 6)  // 6th pin

#define TIMER_PRESCALE_MASK		0x07	///< Timer Prescaler Bit-Mask
#define TIMER_CLK_DIV64			  0x03	///< Timer clocked at F_CPU/64
#define TIMER1PRESCALE	TIMER_CLK_DIV64 ///< timer 1 prescaler default

#define PWM_MAX 0xFF
#define TIMER_TOP 255 // 8 bit PWM


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
// uint16_t getBrightness(uint16_t value);

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

// sets up Timer 1 for 8-bit PWM
void timer1PWMSetup(void) {
  // default 8bit mode
  TCCR1A &= ~(1 << 1); // cbi(TCCR1A,PWM11); <- set PWM11 bit to HIGH
  TCCR1A |= (1 << 0);  // sbi(TCCR1A,PWM10); <- set PWM10 bit to LOW

// unused
// clear output compare value A
//	outb(OCR1AH, 0);
//	outb(OCR1AL, 0);

  // clear output compare registers for B
	OCR1BH = 0; // outb(OCR1BH, 0);
	OCR1BL = 0; // outb(OCR1BL, 0);
}

void timer1Init(void) {
  // timer1SetPrescaler(TIMER1PRESCALE`)
  (TCCR1B) = ((TCCR1B) & ~TIMER_PRESCALE_MASK) | TIMER1PRESCALE;

  // reset TCNT1
  TCNT1H = 0;  // outb(TCNT1H, 0);
	TCNT1L = 0;  // outb(TCNT1L, 0);

  // enable TCNT1 overflow
	TIMSK |= TOIE1; // sbi(TIMSK, TOIE1);
}

void timer1Stop(void) {
  // set prescaler back to NONE
  (TCCR1B) = ((TCCR1B) & ~TIMER_PRESCALE_MASK) | 0x00;  // TIMERRTC_CLK_STOP

  // disable timer overflow interrupt
  TIMSK &= ~TOIE1; // overflow bit?

  setPWM(0);
}

// enable timer 1 PWM
void timer1PWMEnable(void) {
  // timer1PWMBOn()
  // turn on channel B (OC1B) PWM output
  // set OC1B as non-inverted PWM
  TCCR1A |= COM1B1;  // sbi(TCCR1A,COM1B1);
  TCCR1A &= ~COM1B0; // cbi(TCCR1A,COM1B0);
}

// disable timer 1 PWM
void timer1PWMBDisable(void) {
  /* timer1PWMBOff() */
  TCCR1A &= ~COM1B1;  // cbi(TCCR1A,COM1B1);
  TCCR1A &= ~COM1B0;  // cbi(TCCR1A,COM1B0);
}

//
void enableBacklight(void) {
  DDRD  |= BACKLIGHT_PORT;  // set digital pin 4 as output
  PORTD |= BACKLIGHT_PORT;  // set digital pin 4 to high
}

void disableBacklight(void) {
  // DDRD  &= ~BACKLIGHT_PORT;  // set digital pin 4 as input
  PORTD &= ~BACKLIGHT_PORT;  // set digital pin 4 to low
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

  /* initialise timers */
  timer1PWMInit();

  // only if USB
  timer1PWMBEnable();
  enableBacklight();
}

// @Override
void b_led_set(uint8_t level) {
  if (level > BACKLIGHT_LEVELS) {
    level = BACKLIGHT_LEVELS;
  }

  if (level == 0) {
    timer1PWMBDisable();
    // enabled in task()
  }
  else {
    timer1PWMBEnable();
    // enabled in task()
  }

  setPWM((int)(TIMER_TOP * (float) level / BACKLIGHT_LEVELS));
}


// @Override
// called every matrix scan
void b_led_task(void) {
  if (backlight_config.enable) {
    enableBacklight();
  } else {
    disableBacklight();
  }
}

void setPWM(int xValue) {
  char buffer[20];
  snprintf(buffer, 20, "%d\n", xValue);
  send_string(buffer);

  if (xValue > TIMER_TOP) {
    xValue = TIMER_TOP;
  }
  OCR1B = xValue; // timer1PWMBSet(xValue);
}
