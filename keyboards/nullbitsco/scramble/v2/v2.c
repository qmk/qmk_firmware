// Copyright 2022 Jay Greco
// SPDX-License-Identifier: GPL-2.0-or-later

#include "v2.h"

// SCRAMBLE PWM LED config
pwm_led_t scramble_rgb = {
    {GP18, GP19, GP20},
    {&PWMD1, &PWMD1, &PWMD2},
    {0, 1, 0},
    PWM_OUTPUT_ACTIVE_LOW,
    0
};

// Internal PWM init 
// only runs once per PWM LED
void _init_pwm(pwm_led_t* led) {
    if (!led->init_complete) {
        for (int i=0; i<NUM_RGB_IDX; i++) {
            palSetPadMode(PAL_PORT(led->pin[i]), PAL_PAD(led->pin[i]), PWM_PAL_MODE);

            static PWMConfig pwmCFG = {
                .frequency = PWM_PWM_COUNTER_FREQUENCY,
                .period    = PWM_PWM_PERIOD,
            };

            // Channels are always configured as active low
            // If active high is needed, pwm is inverted in _set_led_pwm()
            pwmCFG.channels[0].mode = PWM_OUTPUT_ACTIVE_LOW;
            pwmCFG.channels[1].mode = PWM_OUTPUT_ACTIVE_LOW;
            pwmStart(led->driver[i], &pwmCFG);

            // Start LEDs in the OFF state 
            uint8_t pwm = led->mode == PWM_OUTPUT_ACTIVE_HIGH ? 100 : 0;
            pwmEnableChannel(led->driver[i], led->channel[i], PWM_FRACTION_TO_WIDTH(led->driver[i], 99, pwm));
        }
        
        led->init_complete = 1;
    }
}

// Internal generic PWM setter
void _set_led_pwm(uint8_t pwm, pwm_led_t* led, uint8_t channel) {
    if (pwm > 100) pwm = 100;
    if (led->mode == PWM_OUTPUT_ACTIVE_HIGH) pwm = (100 - pwm);

    _init_pwm(led);
    pwmEnableChannel(led->driver[channel], led->channel[channel], PWM_FRACTION_TO_WIDTH(led->driver[channel], 99, pwm));
}

// SCRAMBLE
void set_scramble_LED(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            set_scramble_LED_rgb_pwm(65, 100, 95);
        break;

        case LED_DIM:
            set_scramble_LED_rgb_pwm(3, 9, 3);
        break;

        default: //LED_OFF
            set_scramble_LED_rgb_pwm(0, 0, 0);
        break;
    }
}

void set_scramble_LED_rgb_pwm(uint8_t r_pwm, uint8_t g_pwm, uint8_t b_pwm) {
    _set_led_pwm(r_pwm, &scramble_rgb, RED);
    _set_led_pwm(g_pwm, &scramble_rgb, GREEN);
    _set_led_pwm(b_pwm, &scramble_rgb, BLUE);
}

void set_scramble_LED_r_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &scramble_rgb, RED);
}

void set_scramble_LED_g_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &scramble_rgb, GREEN);
}

void set_scramble_LED_b_pwm(uint8_t pwm) {
    _set_led_pwm(pwm, &scramble_rgb, BLUE);
}
