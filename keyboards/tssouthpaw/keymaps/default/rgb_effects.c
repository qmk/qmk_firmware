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

 #include QMK_KEYBOARD_H
 #include "rgb_effects.h"
 
 /**
  * RGB Color structure for cleaner color definitions
  */
 typedef struct {
     uint8_t r;
     uint8_t g;
     uint8_t b;
 } rgb_color_t;
 
 /**
  * Color definitions for RGB effects
  */
 static const rgb_color_t CAPS_LOCK_COLOR = {255, 60, 0};  // Orange for Caps Lock
 static const rgb_color_t NUM_LOCK_COLOR = {255, 60, 0};   // Orange for Num Lock
 static const rgb_color_t ESC_RIPPLE_COLOR = {255, 0, 0};  // Red for ESC ripple effect
 static const rgb_color_t MIC_MUTE_COLOR = {255, 0, 0};    // Red for Mic Mute
 static const rgb_color_t ARROW_KEYS_COLOR = {0, 0, 255};  // Blue for arrow keys
 
 /**
  * State tracking structure for LED effects
  */
 typedef struct {
     bool active;
     uint8_t prev_rgb_mode;
 } led_state_t;
 
 /**
  * State variables for LED indicators
  */
 static led_state_t caps_lock_state = {false, 0};
 static led_state_t num_lock_state = {false, 0};
 static led_state_t mic_mute_state = {false, 0};
 
 /**
  * ESC ripple effect state variables
  */
 static struct {
     bool active;
     uint8_t step;
     uint16_t timer;
     bool expanding;
 } ripple_state = {false, 0, 0, true};
 
 /**
  * ESC ripple effect LED configuration
  */
 #define MAX_RIPPLE_LAYERS 6
 #define MAX_LEDS_PER_LAYER 10
 
 // LED indices for each ripple layer
 // 255 is used as a placeholder for unused indices
 static const uint8_t esc_splash_ripple[MAX_RIPPLE_LAYERS][MAX_LEDS_PER_LAYER] = {
     {0, 255, 255, 255, 255, 255, 255, 255, 255, 255},        // Center LED only
     {1, 19, 255, 255, 255, 255, 255, 255, 255, 255},         // First ring
     {38, 39, 6, 7, 15, 255, 255, 255, 255, 255},             // Second ring
     {42, 43, 25, 48, 49, 255, 255, 255, 255, 255},           // Third ring
     {80, 81, 67, 68, 75, 76, 255, 255, 255, 255},            // Fourth ring
     {102, 103, 71, 36, 18, 93, 100, 255, 255, 255}           // Fifth ring
 };
 
 // Number of actual LEDs in each ripple layer for more efficient processing
 static const uint8_t leds_per_layer[MAX_RIPPLE_LAYERS] = {1, 2, 5, 5, 6, 7};
 
 /**
  * Arrow key LED configuration
  */
 static const uint8_t arrow_key_leds[] = {78, 94, 95, 96};
 #define ARROW_KEY_COUNT (sizeof(arrow_key_leds) / sizeof(arrow_key_leds[0]))
 
 /**
  * Apply a pulsing effect to a specific LED
  * 
  * @param led_index The index of the LED to apply the effect to
  * @param color The base RGB color to use
  */
 static void apply_pulse_effect(uint8_t led_index, rgb_color_t color) {
     // Create a pulsing effect by varying brightness based on timer
     uint8_t brightness = abs((timer_read() / 2) % 510 - 255);
     rgb_matrix_set_color(led_index,
                          (color.r * brightness) / 255,
                          (color.g * brightness) / 255,
                          (color.b * brightness) / 255);
 }
 
 /**
  * Handle the state change for an indicator LED
  * 
  * @param active Whether the indicator should be active
  * @param state Pointer to the LED state structure to update
  */
 static void update_indicator_state(bool active, led_state_t *state) {
     if (active) {
         if (!state->active) {
             state->prev_rgb_mode = rgb_matrix_get_mode();
             state->active = true;
         }
     } else if (state->active) {
         state->active = false;
         rgb_matrix_mode_noeeprom(state->prev_rgb_mode);
     }
 }
 
 /**
  * Handle Caps Lock indicator lighting
  */
 void handle_caps_lock_rgb(void) {
     bool caps_active = host_keyboard_led_state().caps_lock;
     update_indicator_state(caps_active, &caps_lock_state);
     
     if (caps_lock_state.active) {
         apply_pulse_effect(CAPS_LOCK_LED, CAPS_LOCK_COLOR);
     }
 }
 
 /**
  * Handle Num Lock indicator lighting
  * Note: Active when Num Lock is OFF (inverse logic)
  */
 void handle_num_lock_rgb(void) {
     bool num_lock_inactive = !host_keyboard_led_state().num_lock;
     update_indicator_state(num_lock_inactive, &num_lock_state);
     
     if (num_lock_state.active) {
         apply_pulse_effect(NUM_LOCK_LED, NUM_LOCK_COLOR);
     }
 }
 
 /**
  * Toggle the Mic Mute effect state
  */
 void toggle_mic_mute_effect(void) {
     if (!mic_mute_state.active) {
         mic_mute_state.prev_rgb_mode = rgb_matrix_get_mode();
         mic_mute_state.active = true;
     } else {
         mic_mute_state.active = false;
         rgb_matrix_mode_noeeprom(mic_mute_state.prev_rgb_mode);
     }
 }
 
 /**
  * Handle Mic Mute indicator lighting
  */
 void handle_mic_mute_rgb(void) {
     if (mic_mute_state.active) {
         apply_pulse_effect(MIC_MUTE_LED, MIC_MUTE_COLOR);
     }
 }
 
 /**
  * Start the ESC ripple effect
  */
 void start_esc_ripple_effect(void) {
     ripple_state.active = true;
     ripple_state.step = 0;
     ripple_state.timer = timer_read();
     ripple_state.expanding = true;
 }
 
 /**
  * Stop the ESC ripple effect
  */
 void stop_esc_ripple_effect(void) {
     ripple_state.active = false;
 }
 
 /**
  * Handle the ESC ripple effect animation
  */
 void handle_esc_ripple_effect(void) {
     if (!ripple_state.active) return;
 
     // Update ripple step based on timer (every 15ms)
     if (timer_elapsed(ripple_state.timer) > 15) {
         ripple_state.timer = timer_read();
         
         // Update step based on direction
         if (ripple_state.expanding) {
             ripple_state.step++;
             if (ripple_state.step >= MAX_RIPPLE_LAYERS - 1) {
                 ripple_state.step = MAX_RIPPLE_LAYERS - 1;
                 ripple_state.expanding = false;
             }
         } else {
             if (ripple_state.step > 0) {
                 ripple_state.step--;
             } else {
                 ripple_state.expanding = true;
             }
         }
     }
 
     // Turn off all ripple LEDs first
     for (uint8_t layer = 0; layer < MAX_RIPPLE_LAYERS; layer++) {
         for (uint8_t i = 0; i < leds_per_layer[layer]; i++) {
             uint8_t led_index = esc_splash_ripple[layer][i];
             if (led_index != 255) { // Skip placeholder values
                 rgb_matrix_set_color(led_index, 0, 0, 0);
             }
         }
     }
     
     // Set active layer LEDs
     uint8_t current_layer = ripple_state.step;
     for (uint8_t i = 0; i < leds_per_layer[current_layer]; i++) {
         uint8_t led_index = esc_splash_ripple[current_layer][i];
         if (led_index != 255) { // Skip placeholder values
             rgb_matrix_set_color(led_index, 
                                 ESC_RIPPLE_COLOR.r,
                                 ESC_RIPPLE_COLOR.g,
                                 ESC_RIPPLE_COLOR.b);
         }
     }
 }
 
 /**
  * Handle arrow key highlighting
  */
 static void handle_arrow_keys(void) {
     // Only override arrows in SOLID_COLOR mode
     if (rgb_matrix_get_mode() == RGB_MATRIX_SOLID_COLOR) {
         uint8_t val = rgb_matrix_get_val();  // current brightness (0–255)
         
         for (uint8_t i = 0; i < ARROW_KEY_COUNT; i++) {
             rgb_matrix_set_color(arrow_key_leds[i], 
                                 ARROW_KEYS_COLOR.r * val / 255,
                                 ARROW_KEYS_COLOR.g * val / 255,
                                 ARROW_KEYS_COLOR.b * val / 255);
         }
     }
 }
 
 /**
 * Work Timer state variables
 */
static struct {
    bool active;
    uint32_t start_time;
    uint32_t elapsed_time;
    bool lunch_break;
    bool lunch_warning_shown;
    bool end_warning_shown;
    bool paused;
    uint32_t pause_time;
} work_timer_state = {false, 0, 0, false, false, false, false, 0};

/**
 * Work Timer color gradient from green to red
 */
static const rgb_color_t WORK_TIMER_START_COLOR = {0, 255, 0};    // Green
static const rgb_color_t WORK_TIMER_MID_COLOR = {255, 255, 0};    // Yellow
static const rgb_color_t WORK_TIMER_END_COLOR = {255, 0, 0};      // Red
static const rgb_color_t WORK_TIMER_LUNCH_COLOR = {0, 0, 255};    // Blue
static const rgb_color_t WORK_TIMER_WARNING_COLOR = {255, 0, 0};  // Red

/**
 * Calculate color gradient between two colors based on progress (0.0 - 1.0)
 */
static rgb_color_t calculate_gradient_color(rgb_color_t start, rgb_color_t end, float progress) {
    rgb_color_t result;
    result.r = start.r + (int)((float)(end.r - start.r) * progress);
    result.g = start.g + (int)((float)(end.g - start.g) * progress);
    result.b = start.b + (int)((float)(end.b - start.b) * progress);
    return result;
}

/**
 * Toggle the work timer on/off
 */
void toggle_work_timer(void) {
    if (!work_timer_state.active) {
        // Start the timer
        work_timer_state.active = true;
        work_timer_state.start_time = timer_read32();
        work_timer_state.elapsed_time = 0;
        work_timer_state.lunch_break = false;
        work_timer_state.lunch_warning_shown = false;
        work_timer_state.end_warning_shown = false;
        work_timer_state.paused = false;
        work_timer_state.pause_time = 0;
    } else {
        // Stop the timer
        work_timer_state.active = false;
    }
}

/**
 * Pause or resume the work timer
 */
void toggle_pause_work_timer(void) {
    if (!work_timer_state.active) return;
    
    if (!work_timer_state.paused) {
        // Pause the timer
        work_timer_state.paused = true;
        work_timer_state.pause_time = timer_read32();
    } else {
        // Resume the timer, adjust start time to account for pause duration
        uint32_t pause_duration = timer_read32() - work_timer_state.pause_time;
        work_timer_state.start_time += pause_duration;
        work_timer_state.paused = false;
    }
}

/**
 * Update the work timer state
 */
void update_work_timer(void) {
    if (!work_timer_state.active || work_timer_state.paused) return;
    
    // Calculate elapsed time
    work_timer_state.elapsed_time = timer_read32() - work_timer_state.start_time;
    
    // Check for lunch break
    if (work_timer_state.elapsed_time >= LUNCH_BREAK_START && 
        work_timer_state.elapsed_time < (LUNCH_BREAK_START + LUNCH_BREAK_DURATION)) {
        work_timer_state.lunch_break = true;
        
        // Check for lunch break warning (5 min before end)
        if (!work_timer_state.lunch_warning_shown && 
            work_timer_state.elapsed_time >= (LUNCH_BREAK_START + LUNCH_BREAK_DURATION - BREAK_WARNING_TIME)) {
            work_timer_state.lunch_warning_shown = true;
        }
    } else {
        work_timer_state.lunch_break = false;
    }
    
    // Check for end of day warning (5 min before end)
    if (!work_timer_state.end_warning_shown && 
        work_timer_state.elapsed_time >= (WORK_TIMER_DURATION - BREAK_WARNING_TIME)) {
        work_timer_state.end_warning_shown = true;
    }
    
    // Auto-stop after 8 hours
    if (work_timer_state.elapsed_time >= WORK_TIMER_DURATION) {
        work_timer_state.active = false;
    }
}

/**
 * Handle the work timer visualization on LEDs
 */
void handle_work_timer(void) {
    if (!work_timer_state.active) return;
    
    // Number of LEDs in the progress bar
    const uint8_t num_leds = WORK_TIMER_LED_END - WORK_TIMER_LED_START + 1;
    
    // Calculate overall progress (0.0 - 1.0)
    float overall_progress = (float)work_timer_state.elapsed_time / (float)WORK_TIMER_DURATION;
    if (overall_progress > 1.0f) overall_progress = 1.0f;
    
    // Lunch break or end warning - flash all LEDs
    if ((work_timer_state.lunch_break && (timer_read() % 500) < 250) || 
        (work_timer_state.end_warning_shown && (timer_read() % 500) < 250)) {
        
        rgb_color_t flash_color;
        if (work_timer_state.lunch_break) {
            // Flash blue during lunch break
            flash_color = WORK_TIMER_LUNCH_COLOR;
        } else {
            // Flash red for end warning
            flash_color = WORK_TIMER_WARNING_COLOR;
        }
        
        // Apply flash color to all progress bar LEDs
        for (uint8_t i = 0; i < num_leds; i++) {
            rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                flash_color.r,
                                flash_color.g,
                                flash_color.b);
        }
    } else {
        // Normal progress bar display
        // Calculate hour segments and LED positions
        float hours_per_led = 8.0f / (float)num_leds;
        float hours_elapsed = overall_progress * 8.0f;
        
        // Determine how many LEDs should be fully lit
        uint8_t leds_lit = (uint8_t)(hours_elapsed / hours_per_led);
        if (leds_lit > num_leds) leds_lit = num_leds;
        
        // Calculate progress within the current LED
        float current_led_progress = (hours_elapsed - (leds_lit * hours_per_led)) / hours_per_led;
        
        // Set colors for each LED in the progress bar
        for (uint8_t i = 0; i < num_leds; i++) {
            rgb_color_t color;
            
            if (i < leds_lit) {
                // Fully lit LED - calculate gradient color based on position
                float led_position = (float)i / (float)(num_leds - 1);
                
                // First half uses green to yellow gradient
                if (led_position < 0.5f) {
                    float half_progress = led_position * 2.0f; // Scale to 0.0 - 1.0 for first half
                    color = calculate_gradient_color(WORK_TIMER_START_COLOR, WORK_TIMER_MID_COLOR, half_progress);
                }
                // Second half uses yellow to red gradient
                else {
                    float half_progress = (led_position - 0.5f) * 2.0f; // Scale to 0.0 - 1.0 for second half
                    color = calculate_gradient_color(WORK_TIMER_MID_COLOR, WORK_TIMER_END_COLOR, half_progress);
                }
            }
            else if (i == leds_lit) {
                // Current LED - partially lit based on progress
                float led_position = (float)i / (float)(num_leds - 1);
                
                rgb_color_t full_color;
                // First half uses green to yellow gradient
                if (led_position < 0.5f) {
                    float half_progress = led_position * 2.0f; // Scale to 0.0 - 1.0 for first half
                    full_color = calculate_gradient_color(WORK_TIMER_START_COLOR, WORK_TIMER_MID_COLOR, half_progress);
                }
                // Second half uses yellow to red gradient
                else {
                    float half_progress = (led_position - 0.5f) * 2.0f; // Scale to 0.0 - 1.0 for second half
                    full_color = calculate_gradient_color(WORK_TIMER_MID_COLOR, WORK_TIMER_END_COLOR, half_progress);
                }
                
                // Dim the color based on progress within this LED
                color.r = full_color.r * current_led_progress;
                color.g = full_color.g * current_led_progress;
                color.b = full_color.b * current_led_progress;
            }
            else {
                // Unlit LED
                color.r = 0;
                color.g = 0;
                color.b = 0;
            }
            
            // Set the LED color
            rgb_matrix_set_color(WORK_TIMER_LED_START + i, color.r, color.g, color.b);
        }
    }
}
 /**
  * Combined overlay for arrow-keys + reactive handlers
  */
 bool rgb_matrix_indicators_user(void) {
    // Apply arrow key highlighting
    handle_arrow_keys();
    
    // Run all reactive handlers
    handle_caps_lock_rgb();
    handle_num_lock_rgb();
    handle_mic_mute_rgb();
    handle_esc_ripple_effect();
    
    // Handle work timer (new addition)
    update_work_timer();
    handle_work_timer();

    return true;  // continue with the normal effect pipeline
}