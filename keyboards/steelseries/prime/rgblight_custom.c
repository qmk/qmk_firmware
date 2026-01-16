// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <hal.h>
#include "chibios_config.h"
#include "gpio.h"
#include "color.h"
#include "rgblight_drivers.h"

static PWMConfig pwmCFG = {
    .frequency = 0xFFFF,
    .period    = 256,
};

rgb_t prime_leds[RGBLIGHT_LED_COUNT];

void init_custom(void) {
    palSetPadMode(PAL_PORT(RGB_RED_PIN), PAL_PAD(RGB_RED_PIN), PAL_MODE_ALTERNATE_PUSHPULL);
    palSetPadMode(PAL_PORT(RGB_GREEN_PIN), PAL_PAD(RGB_GREEN_PIN), PAL_MODE_ALTERNATE_PUSHPULL);
    palSetPadMode(PAL_PORT(RGB_BLUE_PIN), PAL_PAD(RGB_BLUE_PIN), PAL_MODE_ALTERNATE_PUSHPULL);
    pwmCFG.channels[RGB_RED_PWM_CHANNEL - 1].mode   = PWM_OUTPUT_ACTIVE_HIGH;
    pwmCFG.channels[RGB_GREEN_PWM_CHANNEL - 1].mode = PWM_OUTPUT_ACTIVE_HIGH;
    pwmCFG.channels[RGB_BLUE_PWM_CHANNEL - 1].mode  = PWM_OUTPUT_ACTIVE_HIGH;
    pwmStart(&RGB_PWM_DRIVER, &pwmCFG);
}

void set_color_custom(int index, uint8_t red, uint8_t green, uint8_t blue) {
    prime_leds[index].r = red;
    prime_leds[index].g = green;
    prime_leds[index].b = blue;
}

void set_color_all_custom(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        set_color_custom(i, red, green, blue);
    }
}

void flush_custom(void) {
    if (prime_leds[0].r == 0) {
        pwmDisableChannel(&RGB_PWM_DRIVER, RGB_RED_PWM_CHANNEL - 1);
    } else {
        uint32_t duty = ((uint32_t)0xFFFF * prime_leds[0].r) / 0xFF;
        pwmEnableChannel(&RGB_PWM_DRIVER, RGB_RED_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&RGB_PWM_DRIVER, 0xFFFF, duty));
    }
    if (prime_leds[0].g == 0) {
        pwmDisableChannel(&RGB_PWM_DRIVER, RGB_GREEN_PWM_CHANNEL - 1);
    } else {
        uint32_t duty = ((uint32_t)0xFFFF * prime_leds[0].g) / 0xFF;
        pwmEnableChannel(&RGB_PWM_DRIVER, RGB_GREEN_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&RGB_PWM_DRIVER, 0xFFFF, duty));
    }
    if (prime_leds[0].b == 0) {
        pwmDisableChannel(&RGB_PWM_DRIVER, RGB_BLUE_PWM_CHANNEL - 1);
    } else {
        uint32_t duty = ((uint32_t)0xFFFF * prime_leds[0].b) / 0xFF;
        pwmEnableChannel(&RGB_PWM_DRIVER, RGB_BLUE_PWM_CHANNEL - 1, PWM_FRACTION_TO_WIDTH(&RGB_PWM_DRIVER, 0xFFFF, duty));
    }
}

const rgblight_driver_t rgblight_driver = {
    .init          = init_custom,
    .set_color     = set_color_custom,
    .set_color_all = set_color_all_custom,
    .flush         = flush_custom,
};
