// Copyright 2024 B. Le Roy
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "analog.h"

joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    [0] = JOYSTICK_AXIS_VIRTUAL,
    [1] = JOYSTICK_AXIS_VIRTUAL,
    [2] = JOYSTICK_AXIS_VIRTUAL,
    [3] = JOYSTICK_AXIS_VIRTUAL
};

void keyboard_post_init_kb(void) {
    gpio_set_pin_input_high(GP10); // Up1
    gpio_set_pin_input_high(GP11); // Down1
    gpio_set_pin_input_high(GP12); // Left1
    gpio_set_pin_input_high(GP13); // Right1
    gpio_set_pin_input_high(GP14); // Fire1
    gpio_set_pin_input_high(GP15);
    gpio_set_pin_input_high(GP16);
    gpio_set_pin_input_high(GP17);
    gpio_set_pin_input_high(GP18);
    gpio_set_pin_input_high(GP19);

    keyboard_post_init_user();
}

void set_button_state(int btn, bool state) {
    if (state) {
        unregister_joystick_button(btn);
    }
    else {
        register_joystick_button(btn);
    }
}

void housekeeping_task_kb(void) {
    set_button_state(0, gpio_read_pin(GP16));
    set_button_state(1, gpio_read_pin(GP18));
    set_button_state(2, gpio_read_pin(GP17));
    set_button_state(3, gpio_read_pin(GP15));
    set_button_state(4, gpio_read_pin(GP14));
    set_button_state(5, gpio_read_pin(GP19));
    bool up = !gpio_read_pin(10);
    bool down = !gpio_read_pin(11);
    bool left = !gpio_read_pin(12);
    bool right = !gpio_read_pin(13);
    if (up) {
        if (left) {
            joystick_set_hat(7);
        }
        else if (right) {
            joystick_set_hat(1);
        }
        else {
            joystick_set_hat(0);
        }
    }
    else if (down) {
        if (left) {
            joystick_set_hat(5);
        }
        else if (right) {
            joystick_set_hat(3);
        }
        else {
            joystick_set_hat(4);
        }
    }
    else if (left) {
        joystick_set_hat(6);
    }
    else if (right) {
        joystick_set_hat(2);
    }
    else {
        joystick_set_hat(-1);
    }
    int16_t analog = analogReadPin(GP26);
    joystick_set_axis(0, analog);
    analog = analogReadPin(GP27);
    joystick_set_axis(1, analog);
    analog = analogReadPin(GP28);
    joystick_set_axis(2, analog);
    analog = analogReadPin(GP29);
    joystick_set_axis(3, analog);
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_GREEN);
                }
            }
        }
    }

    return false;
}
