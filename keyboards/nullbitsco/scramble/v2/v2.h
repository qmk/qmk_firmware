// Copyright 2022 Jay Greco
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "scramble.h"
#include <hal.h>

enum led_mode {
    LED_OFF = 0,
    LED_DIM,
    LED_ON,
    NUM_LED_MODE
};

enum rgb_idx {
    RED = 0,
    GREEN,
    BLUE,
    NUM_RGB_IDX
};

typedef struct pwm_led_t {
    uint32_t pin[3];
    PWMDriver* driver[3];
    uint8_t channel[3];
    uint8_t mode;
    uint8_t init_complete;
} pwm_led_t;

#define PWM_PAL_MODE (PAL_MODE_ALTERNATE_PWM | PAL_RP_PAD_DRIVE12 | PAL_RP_GPIO_OE)
#define PWM_PWM_COUNTER_FREQUENCY 1000000
#define PWM_PWM_PERIOD PWM_PWM_COUNTER_FREQUENCY / 1000

// RP2040 adds HW PWM control!
// PWM values are in percent, 0-100
void
    set_scramble_LED(uint8_t mode),
    set_scramble_LED_rgb_pwm(uint8_t r_pwm, uint8_t g_pwm, uint8_t b_pwm),
    set_scramble_LED_r_pwm(uint8_t pwm),
    set_scramble_LED_g_pwm(uint8_t pwm),
    set_scramble_LED_b_pwm(uint8_t pwm);
    