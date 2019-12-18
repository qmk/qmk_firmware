#pragma once
#include "quantum.h"

/*
  port and pin assignments for LED indicators. if you modify your hardware to
  reroute some pins (for example, to allow use of the i2c pins) then you can
  override these assignments in your own keymap.
*/
#ifndef LED_PIN_RED
#    define LED_PIN_RED   F5
#endif
#ifndef LED_PIN_GREEN
#    define LED_PIN_GREEN D1
#endif
#ifndef LED_PIN_BLUE
#    define LED_PIN_BLUE  F4
#endif
#ifndef LED_PIN_TX
#    define LED_PIN_TX    D5
#endif
#ifndef LED_PIN_RX
#    define LED_PIN_RX    B0
#endif

/* LED_INIT_PIN(name): sets the pin for the named LED to output mode */
#define _LED_INIT_PIN(pin) setPinOutput(pin)
#define LED_INIT_PIN(name) _LED_INIT_PIN(LED_PIN_ ## name)

/* LED(name, state): sets the named LED to state, where state is on or off */
#define _LED_OFF(pin) writePinHigh(pin)
#define _LED_ON(pin) writePinLow(pin)
#define LED(name, state) _LED_ ## state (LED_PIN_ ## name)

/* convenience macros to set the RGB LED to a specific color */
#define set_led_off     LED(RED, OFF); LED(GREEN, OFF); LED(BLUE, OFF)
#define set_led_red     LED(RED, ON);  LED(GREEN, OFF); LED(BLUE, OFF)
#define set_led_blue    LED(RED, OFF); LED(GREEN, OFF); LED(BLUE, ON)
#define set_led_green   LED(RED, OFF); LED(GREEN, ON);  LED(BLUE, OFF)
#define set_led_yellow  LED(RED, ON);  LED(GREEN, ON);  LED(BLUE, OFF)
#define set_led_magenta LED(RED, ON);  LED(GREEN, OFF); LED(BLUE, ON)
#define set_led_cyan    LED(RED, OFF); LED(GREEN, ON);  LED(BLUE, ON)
#define set_led_white   LED(RED, ON);  LED(GREEN, ON);  LED(BLUE, ON)

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
