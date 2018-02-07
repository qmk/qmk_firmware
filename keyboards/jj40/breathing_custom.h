/**
 * Breathing effect code for PS2AVRGB boards (ATMEGA32A)
 * Works in conjunction with `backlight.c`.
 *
 * Code adapted from `quantum.c` to register with the existing TIMER1 overflow
 * handler in `backlight.c` instead of setting up its own timer.
 * Kenneth A. (github.com/krusli | krusli.me)
 */

#ifdef BACKLIGHT_ENABLE
#ifdef BACKLIGHT_BREATHING

#include "backlight_custom.h"

#ifndef BREATHING_PERIOD
#define BREATHING_PERIOD 6
#endif

#define breathing_min() do {breathing_counter = 0;} while (0)
#define breathing_max() do {breathing_counter = breathing_period * 244 / 2;} while (0)

// TODO make this share code with quantum.c

#define BREATHING_NO_HALT  0
#define BREATHING_HALT_OFF 1
#define BREATHING_HALT_ON  2
#define BREATHING_STEPS 128

static uint8_t breathing_period = BREATHING_PERIOD;
static uint8_t breathing_halt = BREATHING_NO_HALT;
static uint16_t breathing_counter = 0;

static bool breathing = false;

bool is_breathing(void) {
  return breathing;
}

// See http://jared.geek.nz/2013/feb/linear-led-pwm
static uint16_t cie_lightness(uint16_t v) {
  if (v <= 5243) // if below 8% of max
    return v / 9; // same as dividing by 900%
  else {
    uint32_t y = (((uint32_t) v + 10486) << 8) / (10486 + 0xFFFFUL); // add 16% of max and compare
    // to get a useful result with integer division, we shift left in the expression above
    // and revert what we've done again after squaring.
    y = y * y * y >> 8;
    if (y > 0xFFFFUL) // prevent overflow
      return 0xFFFFU;
    else
      return (uint16_t) y;
  }
}

void breathing_enable(void) {
  breathing = true;
  breathing_counter = 0;
  breathing_halt = BREATHING_NO_HALT;
  // interrupt already registered
}

void breathing_pulse(void) {
  if (get_backlight_level() == 0)
    breathing_min();
  else
    breathing_max();
  breathing_halt = BREATHING_HALT_ON;
  // breathing_interrupt_enable();
  breathing = true;
}

void breathing_disable(void) {
  breathing = false;
  // backlight_set(get_backlight_level());
  b_led_set(get_backlight_level()); // custom implementation of backlight_set()
}

void breathing_self_disable(void)
{
  if (get_backlight_level() == 0)
    breathing_halt = BREATHING_HALT_OFF;
  else
    breathing_halt = BREATHING_HALT_ON;
}

void breathing_toggle(void) {
  if (is_breathing())
    breathing_disable();
  else
    breathing_enable();
}

void breathing_period_set(uint8_t value)
{
  if (!value)
    value = 1;
  breathing_period = value;
}

void breathing_period_default(void) {
  breathing_period_set(BREATHING_PERIOD);
}

void breathing_period_inc(void)
{
  breathing_period_set(breathing_period+1);
}

void breathing_period_dec(void)
{
  breathing_period_set(breathing_period-1);
}

/* To generate breathing curve in python:
 * from math import sin, pi; [int(sin(x/128.0*pi)**4*255) for x in range(128)]
 */
static const uint8_t breathing_table[BREATHING_STEPS] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 17, 20, 24, 28, 32, 36, 41, 46, 51, 57, 63, 70, 76, 83, 91, 98, 106, 113, 121, 129, 138, 146, 154, 162, 170, 178, 185, 193, 200, 207, 213, 220, 225, 231, 235, 240, 244, 247, 250, 252, 253, 254, 255, 254, 253, 252, 250, 247, 244, 240, 235, 231, 225, 220, 213, 207, 200, 193, 185, 178, 170, 162, 154, 146, 138, 129, 121, 113, 106, 98, 91, 83, 76, 70, 63, 57, 51, 46, 41, 36, 32, 28, 24, 20, 17, 15, 12, 10, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Use this before the cie_lightness function.
static inline uint16_t scale_backlight(uint16_t v) {
  return v / BACKLIGHT_LEVELS * get_backlight_level();
}

void custom_breathing_handler(void) {
  uint16_t interval = (uint16_t) breathing_period * 244 / BREATHING_STEPS;
  // resetting after one period to prevent ugly reset at overflow.
  breathing_counter = (breathing_counter + 1) % (breathing_period * 244);
  uint8_t index = breathing_counter / interval % BREATHING_STEPS;

  if (((breathing_halt == BREATHING_HALT_ON) && (index == BREATHING_STEPS / 2)) ||
      ((breathing_halt == BREATHING_HALT_OFF) && (index == BREATHING_STEPS - 1)))
  {
      // breathing_interrupt_disable();
  }

  setPWM(cie_lightness(scale_backlight((uint16_t) pgm_read_byte(&breathing_table[index]) * 0x0101U)));
}

#endif // BACKLIGHT_BREATHING
#endif  // BACKLIGHT_ENABLE
