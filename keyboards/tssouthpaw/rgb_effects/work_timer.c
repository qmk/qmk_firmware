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

#include "work_timer.h"
#include "quantum.h"
#include "rgb_effects/rgb_effects.h"
#include "timer.h"

// Simple work timer structure
typedef struct {
    // Basic state
    bool active;              // Is the timer running?
    bool paused;              // Is the timer paused?
    work_timer_type_t type;   // Timer type (30min, 1hr, etc.)
    
    // Time tracking
    uint32_t start_time;      // When this timer started
    uint32_t end_time;        // When this timer should end
    uint32_t pause_time;      // When timer was paused (if paused)
    uint32_t break_time;      // Break duration for this timer
    
    // Midpoint break tracking
    uint32_t mid_point;       // Time value at midpoint (when break starts)
    uint32_t mid_point_end;   // Time value when break ends
} work_timer_t;

// Global timer state
static work_timer_t timer = {0};

// Timer colors
static const rgb_color_t TIMER_START_COLOR = {WORK_TIMER_START_R, WORK_TIMER_START_G, WORK_TIMER_START_B};
static const rgb_color_t TIMER_MID_COLOR = {WORK_TIMER_MID_R, WORK_TIMER_MID_G, WORK_TIMER_MID_B};
static const rgb_color_t TIMER_END_COLOR = {WORK_TIMER_END_R, WORK_TIMER_END_G, WORK_TIMER_END_B};
static const rgb_color_t TIMER_BREAK_COLOR = {WORK_TIMER_LUNCH_R, WORK_TIMER_LUNCH_G, WORK_TIMER_LUNCH_B};

// Function declarations
static void save_timer_state(void);
static void load_timer_state(void);
static void display_progress_bar(uint8_t num_leds, float progress, float brightness);

/**
 * Configure a timer with the specified type
 */
static void configure_timer(work_timer_type_t type) {
    timer.type = type;
    
    // Set break duration based on timer type
    switch (type) {
        case TIMER_TYPE_30MIN:
            timer.break_time = MID_BREAK_30MIN_DURATION;
            break;
            
        case TIMER_TYPE_1HR:
            timer.break_time = MID_BREAK_1HR_DURATION;
            break;
            
        case TIMER_TYPE_4HR:
            timer.break_time = MID_BREAK_4HR_DURATION;
            break;
            
        case TIMER_TYPE_8HR:
            timer.break_time = LUNCH_BREAK_DURATION;
            break;
            
        case TIMER_TYPE_10HR:
            timer.break_time = LUNCH_BREAK_DURATION;
            break;
            
        default:
            timer.break_time = LUNCH_BREAK_DURATION;
            break;
    }
    
    // Calculate timer duration (excluding break)
    uint32_t work_duration = 0;
    switch (type) {
        case TIMER_TYPE_30MIN: work_duration = TIMER_30MIN_DURATION; break;
        case TIMER_TYPE_1HR:   work_duration = TIMER_1HR_DURATION;   break;
        case TIMER_TYPE_4HR:   work_duration = TIMER_4HR_DURATION;   break;
        case TIMER_TYPE_8HR:   work_duration = TIMER_8HR_DURATION;   break;
        case TIMER_TYPE_10HR:  work_duration = TIMER_10HR_DURATION;  break;
        default:               work_duration = TIMER_8HR_DURATION;   break;
    }
    
    // Calculate end time and midpoint
    timer.end_time = timer.start_time + work_duration;
    timer.mid_point = timer.start_time + (work_duration / 2);
    timer.mid_point_end = timer.mid_point + timer.break_time;
}

/**
 * Save timer state to EEPROM
 */
static void save_timer_state(void) {
    uint8_t buffer[24] = {0};
    
    // Basic state
    buffer[0] = timer.active ? 1 : 0;
    buffer[1] = timer.paused ? 1 : 0;
    buffer[2] = (uint8_t)timer.type;
    
    // Time values
    memcpy(&buffer[3], &timer.start_time, sizeof(uint32_t));
    memcpy(&buffer[7], &timer.end_time, sizeof(uint32_t));
    memcpy(&buffer[11], &timer.pause_time, sizeof(uint32_t));
    memcpy(&buffer[15], &timer.break_time, sizeof(uint32_t));
    memcpy(&buffer[19], &timer.mid_point, sizeof(uint32_t));
    
    // Write to EEPROM
    eeprom_update_block(buffer, (void *)EEPROM_WORK_TIMER_ACTIVE, sizeof(buffer));
}

/**
 * Load timer state from EEPROM
 */
static void load_timer_state(void) {
    uint8_t buffer[24] = {0};
    
    // Read from EEPROM
    eeprom_read_block(buffer, (const void *)EEPROM_WORK_TIMER_ACTIVE, sizeof(buffer));
    
    // Basic state
    timer.active = buffer[0] ? true : false;
    timer.paused = buffer[1] ? true : false;
    timer.type = (work_timer_type_t)buffer[2];
    
    // Time values
    memcpy(&timer.start_time, &buffer[3], sizeof(uint32_t));
    memcpy(&timer.end_time, &buffer[7], sizeof(uint32_t));
    memcpy(&timer.pause_time, &buffer[11], sizeof(uint32_t));
    memcpy(&timer.break_time, &buffer[15], sizeof(uint32_t));
    memcpy(&timer.mid_point, &buffer[19], sizeof(uint32_t));
    
    // Calculate mid_point_end from loaded values
    if (timer.active) {
        timer.mid_point_end = timer.mid_point + timer.break_time;
        
        // Verify timer is still valid
        if (!timer.paused) {
            uint32_t current_time = timer_read32();
            if (current_time > timer.end_time) {
                timer.active = false;
                save_timer_state();
            }
        }
    }
}

/**
 * Display progress bar with gradient colors
 */
static void display_progress_bar(uint8_t num_leds, float progress, float brightness) {
    // Progress is a value from 0.0 to 1.0
    float hours_per_led = 1.0f / (float)num_leds;
    
    // Determine how many LEDs should be lit
    uint8_t leds_lit = (uint8_t)(progress / hours_per_led);
    if (leds_lit > num_leds) leds_lit = num_leds;
    
    // Calculate progress for the partially-lit LED
    float current_led_progress = (progress - (leds_lit * hours_per_led)) / hours_per_led;
    
    // Set colors for each LED in the progress bar
    for (uint8_t i = 0; i < num_leds; i++) {
        rgb_color_t color = {0, 0, 0}; // Default to off
        
        if (i < leds_lit) {
            // Fully lit LED - calculate gradient color based on position
            float position = (float)i / (float)(num_leds - 1);
            
            // Use green to orange gradient for most of bar, orange to red at end
            if (position < 0.7f) {
                // First 70% is green to orange
                float adj_progress = position / 0.7f;
                color = calculate_gradient_color(TIMER_START_COLOR, TIMER_MID_COLOR, adj_progress);
            } else {
                // Last 30% is orange to red
                float adj_progress = (position - 0.7f) / 0.3f;
                color = calculate_gradient_color(TIMER_MID_COLOR, TIMER_END_COLOR, adj_progress);
            }
            
            // Apply brightness
            color.r = (uint8_t)((float)color.r * brightness);
            color.g = (uint8_t)((float)color.g * brightness);
            color.b = (uint8_t)((float)color.b * brightness);
        }
        else if (i == leds_lit && current_led_progress > 0.0f) {
            // Partially lit LED
            float position = (float)i / (float)(num_leds - 1);
            rgb_color_t full_color;
            
            if (position < 0.7f) {
                float adj_progress = position / 0.7f;
                full_color = calculate_gradient_color(TIMER_START_COLOR, TIMER_MID_COLOR, adj_progress);
            } else {
                float adj_progress = (position - 0.7f) / 0.3f;
                full_color = calculate_gradient_color(TIMER_MID_COLOR, TIMER_END_COLOR, adj_progress);
            }
            
            // Dim by progress and brightness
            color.r = (uint8_t)((float)full_color.r * current_led_progress * brightness);
            color.g = (uint8_t)((float)full_color.g * current_led_progress * brightness);
            color.b = (uint8_t)((float)full_color.b * current_led_progress * brightness);
        }
        
        // Set the LED color
        rgb_matrix_set_color(WORK_TIMER_LED_START + i, color.r, color.g, color.b);
    }
}

/**
 * Initialize the work timer
 */
void work_timer_init(void) {
    load_timer_state();
}

/**
 * Toggle the work timer on/off
 */
void toggle_work_timer(void) {
    if (timer.active) {
        // Turn off timer
        timer.active = false;
        timer.paused = false;
        
        save_timer_state();
        
        // Force RGB refresh
        rgb_matrix_mode_noeeprom(rgb_matrix_get_mode());
    } else {
        // Start a new timer
        timer.active = true;
        timer.paused = false;
        timer.start_time = timer_read32();
        timer.pause_time = 0;
        
        // Configure for current timer type
        configure_timer(timer.type);
        save_timer_state();
    }
}

/**
 * Start a specific timer type
 */
void start_timer(work_timer_type_t type) {
    // Start fresh
    timer.active = true;
    timer.paused = false;
    timer.start_time = timer_read32();
    timer.pause_time = 0;
    
    // Configure based on type
    configure_timer(type);
    save_timer_state();
}

/**
 * Pause or resume the timer
 */
void toggle_pause_work_timer(void) {
    if (!timer.active) return;
    
    if (timer.paused) {
        // Resume - calculate time paused and adjust timers
        uint32_t current_time = timer_read32();
        uint32_t pause_duration = current_time - timer.pause_time;
        
        // Extend all time points by pause duration
        timer.end_time += pause_duration;
        timer.mid_point += pause_duration;
        timer.mid_point_end += pause_duration;
        
        timer.paused = false;
    } else {
        // Pause
        timer.pause_time = timer_read32();
        timer.paused = true;
    }
    
    save_timer_state();
}

/**
 * Check if the blue pulse effect should be active
 */
bool is_timer_pulse_active(void) {
    if (!timer.active || timer.paused) return false;
    
    uint32_t current_time = timer_read32();
    
    // Only return true when we're in the mid-point break window
    return (current_time >= timer.mid_point && current_time < timer.mid_point_end);
}

/**
 * Update timer state
 */
void update_work_timer(void) {
    if (!timer.active || timer.paused) return;
    
    uint32_t current_time = timer_read32();
    
    // Check if timer has ended
    if (current_time >= timer.end_time) {
        timer.active = false;
        save_timer_state();
        rgb_matrix_mode_noeeprom(rgb_matrix_get_mode());
    }
}

/**
 * Handle work timer visualization
 */
void handle_work_timer(void) {
    static bool was_active = false;
    
    if (!timer.active) {
        if (was_active) {
            rgb_matrix_mode_noeeprom(rgb_matrix_get_mode());
            was_active = false;
        }
        return;
    }
    
    was_active = true;
    
    // Get current time and brightness
    uint32_t current_time = timer_read32();
    uint8_t rgb_brightness = rgb_matrix_get_val();
    float brightness_factor = (float)rgb_brightness / 255.0f;
    
    // Number of LEDs in the progress bar
    const uint8_t num_leds = WORK_TIMER_LED_END - WORK_TIMER_LED_START + 1;
    
    // Calculate progress based on active timer duration
    float progress;
    if (timer.paused) {
        // When paused, use pause time for progress calculation
        progress = (float)(timer.pause_time - timer.start_time) / 
                  (float)(timer.end_time - timer.start_time);
    } else {
        // When active, use current time for progress calculation
        progress = (float)(current_time - timer.start_time) / 
                  (float)(timer.end_time - timer.start_time);
    }
    
    // Clamp progress to valid range
    if (progress > 1.0f) progress = 1.0f;
    if (progress < 0.0f) progress = 0.0f;
    
    // Check if we're in the break window (midpoint of the timer)
    if (!timer.paused && current_time >= timer.mid_point && current_time < timer.mid_point_end) {
        // In break time - show blue pulse
        rgb_color_t color = TIMER_BREAK_COLOR;
        
        // Slow pulse for break time
        uint8_t break_pulse = timer_read() / 10;
        float break_intensity = (float)(abs(break_pulse % 510 - 255)) / 255.0f;
        
        // Apply blue pulse to all LEDs in progress bar
        for (uint8_t i = 0; i < num_leds; i++) {
            rgb_matrix_set_color(WORK_TIMER_LED_START + i,
                              (uint8_t)((float)color.r * break_intensity * brightness_factor),
                              (uint8_t)((float)color.g * break_intensity * brightness_factor),
                              (uint8_t)((float)color.b * break_intensity * brightness_factor));
        }
    } else {
        // Normal progress display
        display_progress_bar(num_leds, progress, brightness_factor);
    }
}

/**
 * Periodic timer task
 */
void work_timer_task(void) {
    update_work_timer();
}