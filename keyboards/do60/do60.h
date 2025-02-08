#pragma once

#include "quantum.h"

#define DO60_CAPS_LOCK_LED_PIN B2
#define DO60_BACKLIGHT_PIN F4

/* DO60 LEDs
 *   GPIO pads
 *   0 F7 not connected
 *   1 F6 not connected
 *   2 F5 RGB PWM Underglow
 *   3 F4 Backlight LED
 *   B2 Capslock LED
 *   B0 not connected
 */

/*
inline void do60_caps_led_on(void) {
    gpio_set_pin_output(DO60_CAPS_LOCK_LED_PIN);
    gpio_write_pin_low(DO60_CAPS_LOCK_LED_PIN);
}
inline void do60_bl_led_on(void) {
    gpio_set_pin_output(DO60_BACKLIGHT_PIN);
    gpio_write_pin_low(DO60_BACKLIGHT_PIN);
}

inline void do60_caps_led_off(void) {
    gpio_set_pin_input(DO60_CAPS_LOCK_LED_PIN);
}
inline void do60_bl_led_off(void) {
    gpio_set_pin_input(DO60_BACKLIGHT_PIN);
}
*/

inline void setdefaultrgb(void){ rgblight_sethsv(100,100,100); }
