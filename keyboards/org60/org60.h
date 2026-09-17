#pragma once

#include "quantum.h"
#include "led.h"

#define ORG60_CAPS_LOCK_LED_PIN B2
#define ORG60_BACKLIGHT_PIN F5

/* Org60 LEDs
 *   GPIO pads
 *   0 F7 not connected
 *   1 F6 RGB PWM Underglow
 *   2 F5 Backlight LED
 *   3 F4 not connected
 *   B2 Capslock LED
 *   B0 not connected
 */
inline void org60_caps_led_on(void) {
    gpio_set_pin_output(ORG60_CAPS_LOCK_LED_PIN);
    gpio_write_pin_low(ORG60_CAPS_LOCK_LED_PIN);
}
inline void org60_bl_led_on(void) {
    gpio_set_pin_output(ORG60_BACKLIGHT_PIN);
    gpio_write_pin_low(ORG60_BACKLIGHT_PIN);
}

inline void org60_caps_led_off(void) {
    gpio_set_pin_input(ORG60_CAPS_LOCK_LED_PIN);
}
inline void org60_bl_led_off(void) {
    gpio_set_pin_input(ORG60_BACKLIGHT_PIN);
}
