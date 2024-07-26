// Copyright 2022 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "micro.h"

#if defined(RGB_MATRIX_ENABLE)
// clang-format off
led_config_t g_led_config = { {
    { NO_LED, 10, 11, NO_LED },
    {      9 , 8,  7, 6 },
    {      2,  3,  4, 5 },
    { NO_LED,  1,  0, NO_LED }
  }, {
                  { 122,  64 }, { 103,  64 },
    {  84,  45 }, { 103,  45 }, { 133,  45 }, { 152,  45 },
    { 152,  26 }, { 122,  26 }, { 103,  26 }, { 84,  26 },
                  { 103,   7 }, { 122,   7 }
  },
  {
       4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4,
       4, 4
  }
};
// clang-format on
#endif

#if defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code_delay(KC_WH_U, 10);
        } else {
            tap_code_delay(KC_WH_D, 10);
        }
    }
    return true;
}
#endif

void work_louder_micro_led_1_on(void) {
    gpio_set_pin_output(WORK_LOUDER_LED_PIN_1);
    gpio_write_pin(WORK_LOUDER_LED_PIN_1, true);
}
void work_louder_micro_led_2_on(void) {
    gpio_set_pin_output(WORK_LOUDER_LED_PIN_2);
    gpio_write_pin(WORK_LOUDER_LED_PIN_2, true);
}
void work_louder_micro_led_3_on(void) {
    gpio_set_pin_output(WORK_LOUDER_LED_PIN_3);
    gpio_write_pin(WORK_LOUDER_LED_PIN_3, true);
}

void work_louder_micro_led_1_off(void) {
    gpio_set_pin_input(WORK_LOUDER_LED_PIN_1);
    gpio_write_pin(WORK_LOUDER_LED_PIN_1, false);
}
void work_louder_micro_led_2_off(void) {
    gpio_set_pin_input(WORK_LOUDER_LED_PIN_2);
    gpio_write_pin(WORK_LOUDER_LED_PIN_2, false);
}
void work_louder_micro_led_3_off(void) {
    gpio_set_pin_input(WORK_LOUDER_LED_PIN_3);
    gpio_write_pin(WORK_LOUDER_LED_PIN_3, false);
}

void work_louder_micro_led_all_on(void) {
    work_louder_micro_led_1_on();
    work_louder_micro_led_2_on();
    work_louder_micro_led_3_on();
}

void work_louder_micro_led_all_off(void) {
    work_louder_micro_led_1_off();
    work_louder_micro_led_2_off();
    work_louder_micro_led_3_off();
}

void work_louder_micro_led_1_set(uint8_t n) {
#if WORK_LOUDER_LED_PIN_1 == B6
    OCR1B = n;
#else
    n ? work_louder_micro_led_1_on() : work_louder_micro_led_1_off();
#endif
}
void work_louder_micro_led_2_set(uint8_t n) {
#if WORK_LOUDER_LED_PIN_2 == B7
    OCR1C = n;
#else
    n ? work_louder_micro_led_2_on() : work_louder_micro_led_2_off();
#endif
}
void work_louder_micro_led_3_set(uint8_t n) {
#if WORK_LOUDER_LED_PIN_3 == B5
    OCR1A = n;
#else
    n ? work_louder_micro_led_3_on() : work_louder_micro_led_3_off();
#endif
}

void work_louder_micro_led_all_set(uint8_t n) {
    work_louder_micro_led_1_set(n);
    work_louder_micro_led_2_set(n);
    work_louder_micro_led_3_set(n);
}

void keyboard_post_init_kb(void) {
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM

    keyboard_post_init_user();
}

void work_louder_led_init_animation(void) {
    work_louder_micro_led_all_off();

    wait_ms(500);
    work_louder_micro_led_1_on();
    wait_ms(100);
    work_louder_micro_led_2_on();
    wait_ms(100);
    work_louder_micro_led_3_on();
    wait_ms(100);
    work_louder_micro_led_1_off();
    wait_ms(100);
    work_louder_micro_led_2_off();
    wait_ms(100);
    work_louder_micro_led_3_off();
    wait_ms(200);
}


void suspend_power_down_kb(void) {
    suspend_power_down_user();
    work_louder_micro_led_all_off();
}

void suspend_wakeup_init_kb(void) {
    work_louder_led_init_animation();
    suspend_wakeup_init_user();
}
