#pragma once
#include "quantum.h"

/* port,pin assignments for LED indicators */
#define led_red   F5
#ifdef MITOSIS_DATAGROK_I2CHACK
#define led_green D4
#else
#define led_green D1
#endif
#define led_blue  F4
#define led_tx    D5
#define led_rx    B0

/* led_init_pin(name): sets the pin for the named LED to output mode */
#define _led_init_pin(pin) setPinOutput(pin)
#define led_init_pin(name) _led_init_pin(led_ ## name)

/* led(name, state): sets the named LED to state, where state is on or off */
#define _led_off(pin) writePinHigh(pin)
#define _led_on(pin) writePinLow(pin)
#define led(name, state) _led_ ## state (led_ ## name)

/* convenience macros to set the RGB LED to a specific color */
#define set_led_off     led(red, off); led(green, off); led(blue, off)
#define set_led_red     led(red, on);  led(green, off); led(blue, off)
#define set_led_blue    led(red, off); led(green, off); led(blue, on)
#define set_led_green   led(red, off); led(green, on);  led(blue, off)
#define set_led_yellow  led(red, on);  led(green, on);  led(blue, off)
#define set_led_magenta led(red, on);  led(green, off); led(blue, on)
#define set_led_cyan    led(red, off); led(green, on);  led(blue, on)
#define set_led_white   led(red, on);  led(green, on);  led(blue, on)

/*
  This a shortcut to help you visually see your layout.
  The first section contains all of the arguments
  The second converts the arguments into a two-dimensional array
*/
#define LAYOUT( \
  k00, k01, k02, k03, k04,      k05, k06, k07, k08, k09, \
  k10, k11, k12, k13, k14,      k15, k16, k17, k18, k19, \
  k20, k21, k22, k23, k24,      k25, k26, k27, k28, k29, \
       k31, k32, k33, k34,      k35, k36, k37, k38, \
       k41, k42, k43, k44,      k45, k46, k47, k48  \
) \
  {                                                           \
    { k00,   k01, k02, k03, k04, k05, k06, k07, k08, k09   }, \
    { k10,   k11, k12, k13, k14, k15, k16, k17, k18, k19   }, \
    { k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29   }, \
    { KC_NO, k31, k32, k33, k34, k35, k36, k37, k38, KC_NO }, \
    { KC_NO, k41, k42, k43, k44, k45, k46, k47, k48, KC_NO }  \
  }
