// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include "gpio.h"
#include "wait.h"

// All this for ergodox led compatibility...
#ifdef CONVERT_TO_PROTON_C
#    define ERGODOX_BOARD_LED_ON_STATE 1
#else
#    define ERGODOX_BOARD_LED_ON_STATE 0
#endif
#define LED_BRIGHTNESS_LO 15
#define LED_BRIGHTNESS_HI 255
static inline void ergodox_right_led_1_off(void) { gpio_set_pin_output(LED_NUM_LOCK_PIN); gpio_write_pin(LED_NUM_LOCK_PIN, 0); }
static inline void ergodox_right_led_1_on(void) { gpio_set_pin_output(LED_NUM_LOCK_PIN); gpio_write_pin(LED_NUM_LOCK_PIN, 1); }
static inline void ergodox_right_led_2_off(void) { gpio_set_pin_output(LED_CAPS_LOCK_PIN); gpio_write_pin(LED_CAPS_LOCK_PIN, 0); }
static inline void ergodox_right_led_2_on(void) { gpio_set_pin_output(LED_CAPS_LOCK_PIN); gpio_write_pin(LED_CAPS_LOCK_PIN, 1); }
static inline void ergodox_right_led_3_off(void) { gpio_set_pin_output(LED_SCROLL_LOCK_PIN); gpio_write_pin(LED_SCROLL_LOCK_PIN, 0); }
static inline void ergodox_right_led_3_on(void) { gpio_set_pin_output(LED_SCROLL_LOCK_PIN); gpio_write_pin(LED_SCROLL_LOCK_PIN, 1); }
static inline void ergodox_right_led_on(uint8_t l) {
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
static inline void ergodox_right_led_off(uint8_t l) {
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
static inline void ergodox_board_led_off(void) { gpio_set_pin_output(D5); gpio_write_pin(D5, !ERGODOX_BOARD_LED_ON_STATE); }
static inline void ergodox_board_led_on(void) { gpio_set_pin_output(D5); gpio_write_pin(D5, ERGODOX_BOARD_LED_ON_STATE); }
static inline void ergodox_led_all_on(void) {
    ergodox_right_led_1_on();
    ergodox_right_led_2_on();
    ergodox_right_led_3_on();
    ergodox_board_led_on();
}
static inline void ergodox_led_all_off(void) {
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    ergodox_board_led_off();
}
static inline void ergodox_right_led_1_set(uint8_t n)          {}
static inline void ergodox_right_led_2_set(uint8_t n)          {}
static inline void ergodox_right_led_3_set(uint8_t n)          {}
static inline void ergodox_right_led_set(uint8_t l, uint8_t n) {}
static inline void ergodox_led_all_set(uint8_t n)              {}
static inline void ergodox_led_init(void) {}
static inline void ergodox_blink_all_leds(void) {
    ergodox_led_all_off();
    ergodox_board_led_on();
    wait_ms(50);
    ergodox_right_led_1_on();
    wait_ms(50);
    ergodox_right_led_2_on();
    wait_ms(50);
    ergodox_right_led_3_on();
    wait_ms(50);
    ergodox_right_led_1_off();
    wait_ms(50);
    ergodox_right_led_2_off();
    wait_ms(50);
    ergodox_right_led_3_off();
    wait_ms(50);
    ergodox_board_led_off();
    //ergodox_led_all_on();
    //wait_ms(333);
    ergodox_led_all_off();
}