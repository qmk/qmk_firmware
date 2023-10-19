// Copyright 2023 Conor Burns (@Conor-Burns)
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

uint32_t startup_time = 0;
bool spiral_done = false;
#define START_DELAY 10 // delay in milliseconds
#define EFFECT_SPEED 85 // n milliseconds

void keyboard_post_init_kb(void) {
    // Enable RGB current limiter and wait for a bit before allowing RGB to continue
    setPinOutput(RGB_ENABLE_PIN);
    writePinHigh(RGB_ENABLE_PIN);
    wait_ms(20);

    // Record the current time
    startup_time = timer_read32();

    // Offload to the user func
    keyboard_post_init_user();
}

// Startup effect
void my_spiral_effect(uint8_t start_led, uint8_t end_led, uint8_t effect_start) {

    // Calculate the current LED from the timer since the keyboard started
    uint32_t elapsed_time = timer_read32() - startup_time - START_DELAY;
    uint8_t total_leds = end_led - start_led + 1;
    uint8_t current_led = (effect_start + (elapsed_time / EFFECT_SPEED)) % total_leds;

    for (uint8_t i = start_led; i <= end_led; i++) {
        if (g_led_config.flags[i] == LED_FLAG_UNDERGLOW) {
            // Calculate relative position in the spiral
            uint8_t relative_position = (i + total_leds - start_led) % total_leds;

            if (!spiral_done && ((relative_position >= effect_start && relative_position <= current_led) ||
                                (current_led < effect_start && (relative_position <= current_led || relative_position >= effect_start)))) {
                rgb_matrix_set_color(i, 23, 124, 255); // turn on the LED
            }
            else if (!spiral_done) {
                rgb_matrix_set_color(i, 0, 0, 0); // turn off the LED
            }
        }
    }

    // check if the spiral effect has completed
    if (current_led == (effect_start - 1 + total_leds) % total_leds) {
        spiral_done = true;
    }
}

bool rgb_matrix_indicators_user(void) {
    uint8_t start_led = 8;
    uint8_t end_led = 30;
    uint8_t effect_start = 13;

    if (timer_read32() - startup_time < START_DELAY) {
        for (uint8_t i = start_led; i <= end_led; i++) {
            if (g_led_config.flags[i] == LED_FLAG_UNDERGLOW) {
                rgb_matrix_set_color(i, 0, 0, 0); // all LEDs off during delay
            }
        }
    } else {
        my_spiral_effect(start_led, end_led, effect_start);
    }
    return true;
}
