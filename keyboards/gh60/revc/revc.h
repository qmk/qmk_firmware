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
static inline void gh60_caps_led_on(void)      { setPinOutput(B2); writePinLow(B2); }
static inline void gh60_poker_leds_on(void)    { setPinOutput(F4); writePinLow(F4); }
static inline void gh60_fn_led_on(void)        { setPinOutput(F5); writePinLow(F5); }
static inline void gh60_esc_led_on(void)       { setPinOutput(F6); writePinLow(F6); }
static inline void gh60_wasd_leds_on(void)     { setPinOutput(F7); writePinLow(F7); }

static inline void gh60_caps_led_off(void)     { setPinInput(B2); }
static inline void gh60_poker_leds_off(void)   { setPinInput(F4); }
static inline void gh60_fn_led_off(void)       { setPinInput(F5); }
static inline void gh60_esc_led_off(void)      { setPinInput(F6); }
static inline void gh60_wasd_leds_off(void)    { setPinInput(F7); }
