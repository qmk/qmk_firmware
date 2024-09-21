// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

static PWMConfig pwmCFG = {
    .frequency = 0xFFFF,
    .period    = 256,
};

void prime_setleds(rgb_led_t *start_led, uint16_t num_leds) {
    if (start_led[0].r == 0) {
        pwmDisableChannel(&RGB_PWM_DRIVER, RGB_RED_PWM_CHANNEL - 1);
    } else {
        uint32_t duty = ((uint32_t)0xFFFF * start_led[0].r) / 0xFF;
        pwmEnableChannel(&RGB_PWM_DRIVER, RGB_RED_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&RGB_PWM_DRIVER, 0xFFFF, duty));
    }
    if (start_led[0].g == 0) {
        pwmDisableChannel(&RGB_PWM_DRIVER, RGB_GREEN_PWM_CHANNEL - 1);
    } else {
        uint32_t duty = ((uint32_t)0xFFFF * start_led[0].g) / 0xFF;
        pwmEnableChannel(&RGB_PWM_DRIVER, RGB_GREEN_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&RGB_PWM_DRIVER, 0xFFFF, duty));
    }
    if (start_led[0].b == 0) {
        pwmDisableChannel(&RGB_PWM_DRIVER, RGB_BLUE_PWM_CHANNEL - 1);
    } else {
        uint32_t duty = ((uint32_t)0xFFFF * start_led[0].b) / 0xFF;
        pwmEnableChannel(&RGB_PWM_DRIVER, RGB_BLUE_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&RGB_PWM_DRIVER, 0xFFFF, duty));
    }
}

void prime_initleds(void) {
    palSetPadMode(PAL_PORT(RGB_RED_PIN), PAL_PAD(RGB_RED_PIN), PAL_MODE_ALTERNATE_PUSHPULL);
    palSetPadMode(PAL_PORT(RGB_GREEN_PIN), PAL_PAD(RGB_GREEN_PIN), PAL_MODE_ALTERNATE_PUSHPULL);
    palSetPadMode(PAL_PORT(RGB_BLUE_PIN), PAL_PAD(RGB_BLUE_PIN), PAL_MODE_ALTERNATE_PUSHPULL);
    pwmCFG.channels[RGB_RED_PWM_CHANNEL - 1].mode   = PWM_OUTPUT_ACTIVE_HIGH;
    pwmCFG.channels[RGB_GREEN_PWM_CHANNEL - 1].mode = PWM_OUTPUT_ACTIVE_HIGH;
    pwmCFG.channels[RGB_BLUE_PWM_CHANNEL - 1].mode  = PWM_OUTPUT_ACTIVE_HIGH;
    pwmStart(&RGB_PWM_DRIVER, &pwmCFG);
}

const rgblight_driver_t rgblight_driver = {
    .init    = prime_initleds,
    .setleds = prime_setleds,
};
