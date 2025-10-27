#pragma once

#include "quantum.h"

#define SIXSHOOTER_LED_0_PIN B6
#define SIXSHOOTER_LED_1_PIN C7
#define SIXSHOOTER_LED_2_PIN D0
#define SIXSHOOTER_LED_3_PIN B5
#define SIXSHOOTER_LED_4_PIN D7
#define SIXSHOOTER_LED_5_PIN B7

inline void sixshooter_led_0_on(void) {
  gpio_set_pin_output(SIXSHOOTER_LED_0_PIN);
  gpio_write_pin_high(SIXSHOOTER_LED_0_PIN);
}
inline void sixshooter_led_1_on(void) {
  gpio_set_pin_output(SIXSHOOTER_LED_1_PIN);
  gpio_write_pin_high(SIXSHOOTER_LED_1_PIN);
}
inline void sixshooter_led_2_on(void) {
  gpio_set_pin_output(SIXSHOOTER_LED_2_PIN);
  gpio_write_pin_high(SIXSHOOTER_LED_2_PIN);
}
inline void sixshooter_led_3_on(void) {
  gpio_set_pin_output(SIXSHOOTER_LED_3_PIN);
  gpio_write_pin_high(SIXSHOOTER_LED_3_PIN);
}
inline void sixshooter_led_4_on(void) {
  gpio_set_pin_output(SIXSHOOTER_LED_4_PIN);
  gpio_write_pin_high(SIXSHOOTER_LED_4_PIN);
}
inline void sixshooter_led_5_on(void) {
  gpio_set_pin_output(SIXSHOOTER_LED_5_PIN);
  gpio_write_pin_high(SIXSHOOTER_LED_5_PIN);
}

inline void sixshooter_led_0_off(void) {
  gpio_set_pin_input(SIXSHOOTER_LED_0_PIN);
}
inline void sixshooter_led_1_off(void) {
  gpio_set_pin_input(SIXSHOOTER_LED_1_PIN);
}
inline void sixshooter_led_2_off(void) {
  gpio_set_pin_input(SIXSHOOTER_LED_2_PIN);
}
inline void sixshooter_led_3_off(void) {
  gpio_set_pin_input(SIXSHOOTER_LED_3_PIN);
}
inline void sixshooter_led_4_off(void) {
  gpio_set_pin_input(SIXSHOOTER_LED_4_PIN);
}
inline void sixshooter_led_5_off(void) {
  gpio_set_pin_input(SIXSHOOTER_LED_5_PIN);
}

inline void sixshooter_led_all_on(void) {
  sixshooter_led_0_on();
  sixshooter_led_1_on();
  sixshooter_led_2_on();
  sixshooter_led_3_on();
  sixshooter_led_4_on();
  sixshooter_led_5_on();
}
inline void sixshooter_led_all_off(void) {
  sixshooter_led_0_off();
  sixshooter_led_1_off();
  sixshooter_led_2_off();
  sixshooter_led_3_off();
  sixshooter_led_4_off();
  sixshooter_led_5_off();
}
