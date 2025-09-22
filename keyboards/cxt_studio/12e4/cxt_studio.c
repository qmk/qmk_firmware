// Copyright 2023 Colin Kinloch (@ColinKinloch)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    switch (index) {
      case 0: {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
      }
      break;
      case 1: {
        if (clockwise) {
            rgb_matrix_increase_hue();
        } else {
            rgb_matrix_decrease_hue();
        }
      }
      break;
      case 2: {
        if (clockwise) {
            rgb_matrix_increase_val();
        } else {
            rgb_matrix_decrease_val();
        }
      }
      break;
      case 3: {
        if (clockwise) {
            rgb_matrix_step();
        } else {
            rgb_matrix_step_reverse();
        }
      }
      break;
    }
    return true;
}
#endif

led_config_t g_led_config = {
    {
        // Matrix to LED Index mapping
        {  3,  2,  1,  0 },   // Row 0
        {  4,  5,  6,  7 },   // Row 1
        { 11, 10,  9,  8 }    // Row 2
    },
    {
        // LED Physical Positions (x, y) — adjust spacing as needed
        // Top row (reversed)
        {255,   0},   // LED 0 (far right key on top row)
        {170,   0},   // LED 1
        { 85,   0},   // LED 2
        {  0,   0},   // LED 3 (far left key on top row)

        // Middle row (normal order)
        {  0,  85},   // LED 4
        { 85,  85},   // LED 5
        {170,  85},   // LED 6
        {255,  85},   // LED 7

        // Bottom row (reversed)
        {255, 170},   // LED 8
        {170, 170},   // LED 9
        { 85, 170},   // LED 10
        {  0, 170}    // LED 11
    },
    {
        // LED Flags — per-key lighting for all
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
    }
};
