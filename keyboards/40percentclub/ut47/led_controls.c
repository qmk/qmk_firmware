// Copyright 2018 Carlos Filoteo
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "uart.h"

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        if (led_state.caps_lock) {
            // output low
            gpio_set_pin_output(B0);
            gpio_write_pin_low(B0);
            gpio_set_pin_output(D5);
            gpio_write_pin_low(D5);
        } else {
            // Hi-Z
            gpio_set_pin_input(B0);
            gpio_set_pin_input(D5);
        }
    }
    return false;
}

void keyboard_post_init_kb(void) {
    uart_init(9600);

    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uart_write((record->event.key.row * 16) + record->event.key.col);

        switch (keycode) {
            case LED_TOG:
                uart_write(0x64);
                return false;
            case LED_CHG:
                uart_write(0x65);
                return false;
        }
    }
    return process_record_user(keycode, record);
}
