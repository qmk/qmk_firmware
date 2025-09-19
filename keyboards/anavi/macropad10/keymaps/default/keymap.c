// Copyright 2022 Leon Anavi
// SPDX-License-Identifier: GPL-2.0-or-later
//

#include QMK_KEYBOARD_H
#include "hardware/gpio.h"

#define LED_PIN 26

enum layer_names {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_mp10(
        KC_A,     KC_B,     KC_C,
        KC_D,     KC_E,     KC_F,
        BL_TOGG,  UG_NEXT,  UG_TOGG
    )
};

// ---- LED state ----
static uint8_t led_level = 0; // 0=off, 1=25%, 2=50%, 3=75%, 4=100%
static uint8_t pwm_counter = 0;

void custom_backlight_init(void) {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, true); // output
    gpio_put(LED_PIN, 0);
}

void matrix_init_user(void) {
    custom_backlight_init();
}

// ---- Software PWM ----
void matrix_scan_user(void) {
    if (led_level == 0) {
        gpio_put(LED_PIN, 0);
        return;
    }

    pwm_counter++;
    if (pwm_counter >= 100) pwm_counter = 0;

    uint8_t duty = led_level * 25; // 25,50,75,100
    gpio_put(LED_PIN, pwm_counter < duty ? 1 : 0);
}

// ---- Handle key events ----
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == BL_TOGG && record->event.pressed) {
        // cycle brightness
        led_level++;
        if (led_level > 4) {
            led_level = 0;
        }
        return false; // don’t send to host
    }
    return true;
}
