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
  * RGB Effect types enumeration
  * For potential future extension of effect types
  */
 typedef enum {
     RGB_EFFECT_NONE,
     RGB_EFFECT_BREATHING,
     RGB_EFFECT_RAINBOW,
     RGB_EFFECT_CUSTOM
 } rgb_effect_type_t;
  
 /**
  * RGB Color structure for cleaner color definitions
  */
 typedef struct {
     uint8_t r;
     uint8_t g;
     uint8_t b;
 } rgb_color_t;
  
 /**
  * Function declarations for handling RGB effects
  */
  
 // Handle LED indicators for keyboard state
 void handle_caps_lock_rgb(void);
 void handle_num_lock_rgb(void);
 void handle_mic_mute_rgb(void);
  
 // Ripple effect functions
 void handle_esc_ripple_effect(void);
 void start_esc_ripple_effect(void);
 void stop_esc_ripple_effect(void);
  
 // Microphone mute effect toggle
 void toggle_mic_mute_effect(void);
  
 /**
  * Utility functions for RGB effects
  */
  
 // Gets the keyboard's current RGB mode
 static inline uint8_t get_current_rgb_mode(void) {
     return rgb_matrix_get_mode();
 }
  
 // Sets an LED to a specific RGB color
 static inline void set_led_color(uint8_t led_index, uint8_t r, uint8_t g, uint8_t b) {
     rgb_matrix_set_color(led_index, r, g, b);
 }
  
 // Calculate color gradient between two colors based on progress (0.0 - 1.0)
 static inline rgb_color_t calculate_gradient_color(rgb_color_t start, rgb_color_t end, float progress) {
     rgb_color_t result;
     result.r = start.r + (int)((float)(end.r - start.r) * progress);
     result.g = start.g + (int)((float)(end.g - start.g) * progress);
     result.b = start.b + (int)((float)(end.b - start.b) * progress);
     return result;
 }