/* Copyright 2025 TS Design Works LLC
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

// LED indices for indicator LEDs
#define CAPS_LOCK_LED  62  // LED index for Caps Lock indicator
#define NUM_LOCK_LED   2   // LED index for Num Lock indicator
#define MIC_MUTE_LED   3   // LED index for KC_MICMUTE

/**
 * RGB color structure
 *
 * Represents a 24-bit RGB color for cleaner color definitions and usage.
 */
typedef struct {
    uint8_t r;  ///< Red channel (0-255)
    uint8_t g;  ///< Green channel (0-255)
    uint8_t b;  ///< Blue channel (0-255)
} rgb_color_t;

/**
 * LED indicator functions
 */

/// Handle Caps Lock LED indicator effect
void handle_caps_lock_rgb(void);

/// Handle Num Lock LED indicator effect
void handle_num_lock_rgb(void);

/// Handle microphone mute LED indicator effect
void handle_mic_mute_rgb(void);

/**
 * ESC ripple effect functions
 */

/// Animate the ESC ripple effect
void handle_esc_ripple_effect(void);

/// Start the ESC ripple effect animation
void start_esc_ripple_effect(void);

/// Stop the ESC ripple effect animation
void stop_esc_ripple_effect(void);

/// Toggle the ESC ripple effect on/off
void toggle_esc_ripple_effect(void);

/// Check if ESC ripple effect is enabled
bool is_esc_ripple_enabled(void);

/**
 * Microphone mute effect functions
 */

/// Toggle microphone mute LED effect state
void toggle_mic_mute_effect(void);

/**
 * Utility functions for RGB effects
 */

/// Get the keyboard's current RGB animation mode
static inline uint8_t get_current_rgb_mode(void) {
    return rgb_matrix_get_mode();
}

/// Set a specific LED to the given RGB color
static inline void set_led_color(uint8_t led_index, uint8_t r, uint8_t g, uint8_t b) {
    rgb_matrix_set_color(led_index, r, g, b);
}
