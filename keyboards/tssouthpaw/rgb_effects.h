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

 #include QMK_KEYBOARD_H
 
 // LED indices for indicator LEDs
 #define CAPS_LOCK_LED   62   // LED index for Caps Lock indicator
 #define NUM_LOCK_LED    2    // LED index for Num Lock indicator
 #define MIC_MUTE_LED    3    // LED index for KC_MICMUTE
 
 /**
  * RGB Effect types enumeration
  * For potential future extension of effect types
  */
 typedef enum {
     EFFECT_NONE = 0,
     EFFECT_PULSE,
     EFFECT_RIPPLE,
     EFFECT_FLASH,
     EFFECT_SOLID
 } rgb_effect_type_t;

 /* Work Timer Definitions */
#define WORK_TIMER_LED_START   4    // F1 key LED
#define WORK_TIMER_LED_END     15   // F12 key LED
#define WORK_TIMER_DURATION    28800000   // 8 hours in milliseconds
#define LUNCH_BREAK_START      14400000   // 4 hours in milliseconds
#define LUNCH_BREAK_DURATION   3600000    // 1 hour in milliseconds
#define BREAK_WARNING_TIME     300000     // 5 minutes in milliseconds

// Work timer effect functions
void toggle_work_timer(void);
void update_work_timer(void);
void handle_work_timer(void);
 
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