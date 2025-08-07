#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>

#define HOTDOX_BOARD_LED_PIN B7
#define HOTDOX_RIGHT_LED_1_PIN B5
#define HOTDOX_RIGHT_LED_2_PIN B6
#define HOTDOX_RIGHT_LED_3_PIN B4

void init_ergodox(void);

inline void ergodox_board_led_on(void) {
    gpio_set_pin_output(HOTDOX_BOARD_LED_PIN);
    gpio_write_pin_high(HOTDOX_BOARD_LED_PIN);
}
inline void ergodox_right_led_1_on(void) {
    gpio_set_pin_output(HOTDOX_RIGHT_LED_1_PIN);
    gpio_write_pin_low(HOTDOX_RIGHT_LED_1_PIN);
}
inline void ergodox_right_led_2_on(void) {
    gpio_set_pin_output(HOTDOX_RIGHT_LED_2_PIN);
    gpio_write_pin_low(HOTDOX_RIGHT_LED_2_PIN);
}
inline void ergodox_right_led_3_on(void) {
    gpio_set_pin_output(HOTDOX_RIGHT_LED_3_PIN);
    gpio_write_pin_low(HOTDOX_RIGHT_LED_3_PIN);
}

inline void ergodox_board_led_off(void) {
    gpio_set_pin_output(HOTDOX_BOARD_LED_PIN);
    gpio_write_pin_low(HOTDOX_BOARD_LED_PIN);
}
inline void ergodox_right_led_1_off(void) {
    gpio_set_pin_output(HOTDOX_RIGHT_LED_1_PIN);
    gpio_write_pin_high(HOTDOX_RIGHT_LED_1_PIN);
}
inline void ergodox_right_led_2_off(void) {
    gpio_set_pin_output(HOTDOX_RIGHT_LED_2_PIN);
    gpio_write_pin_high(HOTDOX_RIGHT_LED_2_PIN);
}
inline void ergodox_right_led_3_off(void) {
    gpio_set_pin_output(HOTDOX_RIGHT_LED_3_PIN);
    gpio_write_pin_high(HOTDOX_RIGHT_LED_3_PIN);
}

inline void ergodox_right_led_on(uint8_t l) {
    switch (l) {
         case 1:
             ergodox_right_led_1_on();
             break;
         case 2:
             ergodox_right_led_2_on();
             break;
         case 3:
             ergodox_right_led_3_on();
             break;
         default:
             break;
        }
}

inline void ergodox_right_led_off(uint8_t l) {
    switch (l) {
         case 1:
             ergodox_right_led_1_off();
             break;
         case 2:
             ergodox_right_led_2_off();
             break;
         case 3:
             ergodox_right_led_3_off();
             break;
         default:
             break;
        }
}

inline void ergodox_led_all_on(void) {
    ergodox_board_led_on();
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
}

inline void ergodox_led_all_off(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
}

inline void ergodox_right_led_1_set(uint8_t n)          {}
inline void ergodox_right_led_2_set(uint8_t n)          {}
inline void ergodox_right_led_3_set(uint8_t n)          {}
inline void ergodox_right_led_set(uint8_t l, uint8_t n) {}
inline void ergodox_led_all_set(uint8_t n)              {}

void ergodox_blink_all_leds(void);
