// Copyright 2022 Takuya Urakawa @hsgw (dm9records.com, 5z6p.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "lain.h"

keyboard_config_t lain_config;

static const pin_t leds[LED_NUM]       = LED_PINS;
bool               led_states[LED_NUM] = {0};

void lain_eeconfig_update_kb(void) { eeconfig_update_kb(lain_config.raw); }

void lain_set_led(uint8_t no, bool flag) {
    led_states[no] = flag;
    gpio_write_pin(leds[no], lain_config.led_enabled ? flag : false);
}

void lain_enable_leds(bool flag) {
    lain_config.led_enabled = flag;
    lain_eeconfig_update_kb();

    for (int i = 0; i < LED_NUM; i++) {
        gpio_write_pin(leds[i], lain_config.led_enabled ? led_states[i] : false);
    }
}

void lain_enable_leds_toggle(void) { lain_enable_leds(!lain_config.led_enabled); }

void led_init_ports(void) {
    for (uint8_t i = 0; i < LED_NUM; i++) {
        gpio_set_pin_output(leds[i]);
        lain_set_led(leds[i], 0);
    }
}

void eeconfig_init_kb(void) {
    // set default config
    lain_config.led_enabled = true;
    lain_eeconfig_update_kb();

    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    // read stored config
    lain_config.raw = eeconfig_read_kb();

    keyboard_post_init_user();
}
