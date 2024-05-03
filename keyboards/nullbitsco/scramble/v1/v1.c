// Copyright 2022 Jay Greco
// SPDX-License-Identifier: GPL-2.0-or-later

#include "v1.h"

void set_scramble_LED(uint8_t mode) {
    switch(mode) {
        case LED_ON:
            gpio_set_pin_output(PIN_LED);
            gpio_write_pin(PIN_LED, GPIO_STATE_HIGH);
        break;

        case LED_DIM:
            gpio_set_pin_input(PIN_LED);
        break;

        case LED_OFF:
            gpio_set_pin_output(PIN_LED);
            gpio_write_pin(PIN_LED, GPIO_STATE_LOW);
        break;

        default:
        break;
    }
}
