// Copyright 2024 Bernd Lehmann (@der-b)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "rev1.h"

void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(USB_LED1);
    gpio_set_pin_output(USB_LED2);
    gpio_set_pin_output(USB_LED3);

    gpio_set_pin_output(USB_SEL_0);
    gpio_set_pin_output(USB_SEL_1);

    // set default port
    gpio_write_pin_high(USB_SEL_0);
    gpio_write_pin_high(USB_SEL_1);

    gpio_write_pin_high(USB_LED3);
    gpio_write_pin_low(USB_LED2);
    gpio_write_pin_low(USB_LED1);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case USB1:
            gpio_write_pin_high(USB_SEL_0);
            gpio_write_pin_low(USB_SEL_1);
            gpio_write_pin_high(USB_LED1);
            gpio_write_pin_low(USB_LED2);
            gpio_write_pin_low(USB_LED3);
            return false;
        case USB2:
            gpio_write_pin_low(USB_SEL_0);
            gpio_write_pin_high(USB_SEL_1);
            gpio_write_pin_low(USB_LED1);
            gpio_write_pin_high(USB_LED2);
            gpio_write_pin_low(USB_LED3);
            return false;
        case USB3:
            gpio_write_pin_high(USB_SEL_0);
            gpio_write_pin_high(USB_SEL_1);
            gpio_write_pin_low(USB_LED1);
            gpio_write_pin_low(USB_LED2);
            gpio_write_pin_high(USB_LED3);
            return false;
    }
    return true;
}
