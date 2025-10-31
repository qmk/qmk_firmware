#pragma once

#include "quantum.h"

#define XD60_CAPS_LOCK_LED_PIN B2
#define XD60_BACKLIGHT_PIN F5

/* XD60 LEDs
 *   GPIO pads
 *   0 F7 not connected
 *   1 F6 RGB PWM Underglow
 *   2 F5 Backlight LED
 *   3 F4 not connected
 *   B2 Capslock LED
 *   B0 not connected
 */
inline void xd60_caps_led_on(void) {
    gpio_set_pin_output(XD60_CAPS_LOCK_LED_PIN);
    gpio_write_pin_low(XD60_CAPS_LOCK_LED_PIN);
}
inline void xd60_bl_led_on(void) {
    gpio_set_pin_output(XD60_BACKLIGHT_PIN);
    gpio_write_pin_low(XD60_BACKLIGHT_PIN);
}

inline void xd60_caps_led_off(void) {
    gpio_set_pin_input(XD60_CAPS_LOCK_LED_PIN);
}
inline void xd60_bl_led_off(void) {
    gpio_set_pin_input(XD60_BACKLIGHT_PIN);
}
