#pragma once

#include "quantum.h"
#include "led.h"

/* GH60 LEDs
 *   GPIO pads
 *   0 F7 WASD LEDs
 *   1 F6 ESC LED
 *   2 F5 FN LED
 *   3 F4 POKER Arrow LEDs
 *   B2 Capslock LED
 *   B0 not connected
 */
static inline void gh60_caps_led_on(void)      { gpio_set_pin_output(B2); gpio_write_pin_low(B2); }
static inline void gh60_poker_leds_on(void)    { gpio_set_pin_output(F4); gpio_write_pin_low(F4); }
static inline void gh60_fn_led_on(void)        { gpio_set_pin_output(F5); gpio_write_pin_low(F5); }
static inline void gh60_esc_led_on(void)       { gpio_set_pin_output(F6); gpio_write_pin_low(F6); }
static inline void gh60_wasd_leds_on(void)     { gpio_set_pin_output(F7); gpio_write_pin_low(F7); }

static inline void gh60_caps_led_off(void)     { gpio_set_pin_input(B2); }
static inline void gh60_poker_leds_off(void)   { gpio_set_pin_input(F4); }
static inline void gh60_fn_led_off(void)       { gpio_set_pin_input(F5); }
static inline void gh60_esc_led_off(void)      { gpio_set_pin_input(F6); }
static inline void gh60_wasd_leds_off(void)    { gpio_set_pin_input(F7); }
