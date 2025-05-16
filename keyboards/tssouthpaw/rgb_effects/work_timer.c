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

// Bitpacked flags to save memory
typedef struct {
    uint8_t active: 1;
    uint8_t paused: 1;
    uint8_t lunch_break: 1;
    uint8_t mid_break: 1;
    uint8_t lunch_warning_shown: 1;
    uint8_t mid_break_warning_shown: 1;
    uint8_t end_warning_shown: 1;
    uint8_t pulse_active: 1;  // Flag to track if any pulse is currently active
} work_timer_flags_t;

// Simplified work timer state structure
typedef struct {
    work_timer_flags_t flags;
    work_timer_type_t timer_type;
    uint32_t start_time;         // When timer was started
    uint32_t end_time;           // When timer should end (calculated)
    uint32_t pause_time;         // When pause started (if paused)
    uint32_t break_start_time;   // When current break started
    uint32_t mid_break_time;     // When mid-break should occur
    uint32_t mid_break_duration; // How long the mid-break should last
    bool has_lunch_break;        // Whether this timer has a lunch break
} work_timer_t;

// Global work timer state with simplified initialization
static work_timer_t work_timer = {
    .flags = {0},
    .timer_type = TIMER_TYPE_8HR,
    .start_time = 0,
    .end_time = 0,
    .pause_time = 0,
    .break_start_time = 0,
    .mid_break_time = 0,
    .mid_break_duration = LUNCH_BREAK_DURATION,
    .has_lunch_break = true
};

// Predefined RGB colors for timer states
static const rgb_color_t WORK_TIMER_START_COLOR = {WORK_TIMER_START_R, WORK_TIMER_START_G, WORK_TIMER_START_B};
static const rgb_color_t WORK_TIMER_MID_COLOR = {WORK_TIMER_MID_R, WORK_TIMER_MID_G, WORK_TIMER_MID_B};
static const rgb_color_t WORK_TIMER_END_COLOR = {WORK_TIMER_END_R, WORK_TIMER_END_G, WORK_TIMER_END_B};
static const rgb_color_t WORK_TIMER_LUNCH_COLOR = {WORK_TIMER_LUNCH_R, WORK_TIMER_LUNCH_G, WORK_TIMER_LUNCH_B};
static const rgb_color_t WORK_TIMER_WARNING_COLOR = {WORK_TIMER_WARNING_R, WORK_TIMER_WARNING_G, WORK_TIMER_WARNING_B};

// Function prototypes for internal functions
static void configure_timer_for_type(work_timer_type_t timer_type);
static void display_progress_bar(uint8_t num_leds, float overall_progress, float brightness_factor);
static void save_work_timer_state(void);
static void load_work_timer_state(void);
static void update_pulse_active_state(void);

/**
 * Configure timer parameters based on timer type
 */
static void configure_timer_for_type(work_timer_type_t timer_type) {
    work_timer.timer_type = timer_type;
    
    switch (timer_type) {
        case TIMER_TYPE_30MIN:
            work_timer.mid_break_time = TIMER_30MIN_DURATION / 2;
            work_timer.mid_break_duration = MID_BREAK_30MIN_DURATION;
            work_timer.has_lunch_break = false;
            work_timer.end_time = work_timer.start_time + TIMER_30MIN_DURATION;
            break;
            
        case TIMER_TYPE_1HR:
            work_timer.mid_break_time = TIMER_1HR_DURATION / 2;
            work_timer.mid_break_duration = MID_BREAK_1HR_DURATION;
            work_timer.has_lunch_break = false;
            work_timer.end_time = work_timer.start_time + TIMER_1HR_DURATION;
            break;
            
        case TIMER_TYPE_4HR:
            work_timer.mid_break_time = TIMER_4HR_DURATION / 2;
            work_timer.mid_break_duration = MID_BREAK_4HR_DURATION;
            work_timer.has_lunch_break = false;
            work_timer.end_time = work_timer.start_time + TIMER_4HR_DURATION;
            break;
            
        case TIMER_TYPE_8HR:
            work_timer.mid_break_time = TIMER_8HR_DURATION / 2;
            work_timer.mid_break_duration = LUNCH_BREAK_DURATION;
            work_timer.has_lunch_break = true;
            work_timer.end_time = work_timer.start_time + TIMER_8HR_DURATION;
            break;
            
        case TIMER_TYPE_10HR:
            work_timer.mid_break_time = TIMER_10HR_DURATION / 2;
            work_timer.mid_break_duration = LUNCH_BREAK_DURATION;
            work_timer.has_lunch_break = true;
            work_timer.end_time = work_timer.start_time + TIMER_10HR_DURATION;
            break;
            
        default:
            // Default to 8HR if something goes wrong
            work_timer.mid_break_time = TIMER_8HR_DURATION / 2;
            work_timer.mid_break_duration = LUNCH_BREAK_DURATION;
            work_timer.has_lunch_break = true;
            work_timer.end_time = work_timer.start_time + TIMER_8HR_DURATION;
            break;
    }
}

/**
 * Save the work timer state to EEPROM
 */
static void save_work_timer_state(void) {
    // Create a buffer to store all our data
    uint8_t buffer[24] = {0}; // Increased from 21 to 24 bytes to have enough space
    
    // Set the active flag
    buffer[0] = work_timer.flags.active;
    
    // Only save time info if timer is active
    if (work_timer.flags.active) {
        // Save start time (4 bytes)
        memcpy(&buffer[1], &work_timer.start_time, sizeof(uint32_t));
        
        // Save end time (4 bytes)
        memcpy(&buffer[5], &work_timer.end_time, sizeof(uint32_t));
        
        // Save timer type (1 byte)
        buffer[9] = (uint8_t)work_timer.timer_type;
        
        // Save pause state and time (5 bytes)
        buffer[10] = work_timer.flags.paused;
        memcpy(&buffer[11], &work_timer.pause_time, sizeof(uint32_t));
        
        // Save break state (1 byte)
        buffer[15] = (work_timer.flags.lunch_break ? 1 : 0) | 
                    (work_timer.flags.mid_break ? 2 : 0);
        
        // Save break start time (4 bytes)
        memcpy(&buffer[16], &work_timer.break_start_time, sizeof(uint32_t));
        
        // Save mid-break time (4 bytes) - fixed buffer position
        memcpy(&buffer[20], &work_timer.mid_break_time, sizeof(uint32_t));
    }
    
    // Write all data at once to EEPROM
    eeprom_update_block(buffer, (void *)EEPROM_WORK_TIMER_ACTIVE, sizeof(buffer));
}

/**
 * Load the work timer state from EEPROM
 */
static void load_work_timer_state(void) {
    // Create a buffer to read all our data
    uint8_t buffer[24] = {0}; // Increased from 21 to 24 bytes to match save function
    
    // Read all data at once from EEPROM
    eeprom_read_block(buffer, (const void *)EEPROM_WORK_TIMER_ACTIVE, sizeof(buffer));
    
    // Get the active flag
    work_timer.flags.active = buffer[0];
    
    // Only process the rest if timer was active
    if (work_timer.flags.active) {
        // Load timer type
        work_timer_type_t saved_type = (work_timer_type_t)buffer[9];
        
        // Get start time (4 bytes)
        memcpy(&work_timer.start_time, &buffer[1], sizeof(uint32_t));
        
        // Get end time (4 bytes)
        memcpy(&work_timer.end_time, &buffer[5], sizeof(uint32_t));
        
        // Get pause state and time (5 bytes)
        work_timer.flags.paused = buffer[10];
        memcpy(&work_timer.pause_time, &buffer[11], sizeof(uint32_t));
        
        // Get break state (1 byte)
        uint8_t break_state = buffer[15];
        work_timer.flags.lunch_break = (break_state & 1) > 0;
        work_timer.flags.mid_break = (break_state & 2) > 0;
        
        // Get break start time (4 bytes)
        memcpy(&work_timer.break_start_time, &buffer[16], sizeof(uint32_t));
        
        // Get mid-break time (4 bytes) - fixed buffer position
        memcpy(&work_timer.mid_break_time, &buffer[20], sizeof(uint32_t));
        
        // Apply configuration for this timer type (durations, etc.)
        configure_timer_for_type(saved_type);
        
        // If currently in a break, we need to adjust for time passed since poweroff
        if (work_timer.flags.lunch_break || work_timer.flags.mid_break) {
            uint32_t current_time = timer_read32();
            uint32_t time_off = current_time - work_timer.break_start_time;
            
            // If we've been powered off longer than the break duration, end the break
            if (time_off > work_timer.mid_break_duration) {
                work_timer.flags.lunch_break = 0;
                work_timer.flags.mid_break = 0;
            }
        }
        
        // Validate timer values
        uint32_t current_time = timer_read32();
        
        // If end time is in the past, timer is done
        if (work_timer.end_time <= current_time && !work_timer.flags.paused) {
            work_timer.flags.active = 0;
            save_work_timer_state();
        }
        
        // Check for end warning state (within 5 minutes of end)
        if (!work_timer.flags.paused && 
            current_time >= (work_timer.end_time - BREAK_WARNING_TIME)) {
            work_timer.flags.end_warning_shown = 1;
        }
        
        // Update pulse active state
        update_pulse_active_state();
    }
}

/**
 * Display progress bar with gradient colors
 */
static void display_progress_bar(uint8_t num_leds, float overall_progress, float brightness_factor) {
    // Calculate hour segments and LED positions
    float hours_per_led = 1.0f / (float)num_leds;
    
    // Determine how many LEDs should be fully lit
    uint8_t leds_lit = (uint8_t)(overall_progress / hours_per_led);
    if (leds_lit > num_leds) leds_lit = num_leds;
    
    // Calculate progress within the current LED
    float current_led_progress = (overall_progress - (leds_lit * hours_per_led)) / hours_per_led;
    
    // Set colors for each LED in the progress bar
    for (uint8_t i = 0; i < num_leds; i++) {
        rgb_color_t color = {0, 0, 0}; // Default to off
        
        if (i < leds_lit) {
            // Fully lit LED - calculate gradient color based on position
            float led_position = (float)i / (float)(num_leds - 1);
            
            // Adjust transition points - more green-to-orange (first 80% of bar), 
            // and less orange-to-red (last 20% of bar)
            if (led_position < 0.3f) {
                // Scale to 0.0 - 1.0 for green-to-orange part (now 80% of the bar)
                float adjusted_progress = led_position / 0.3f;
                color = calculate_gradient_color(WORK_TIMER_START_COLOR, WORK_TIMER_MID_COLOR, adjusted_progress);
            }
            else {
                float adjusted_progress = (led_position - 0.3f) / 0.7f; // Scale to 0.0 - 1.0 for last 20%
                color = calculate_gradient_color(WORK_TIMER_MID_COLOR, WORK_TIMER_END_COLOR, adjusted_progress);
            }
            
            // Apply overall RGB brightness factor
            color.r = (uint8_t)((float)color.r * brightness_factor);
            color.g = (uint8_t)((float)color.g * brightness_factor);
            color.b = (uint8_t)((float)color.b * brightness_factor);
        }
        else if (i == leds_lit && current_led_progress > 0.0f) {
            // Current LED - partially lit based on progress
            float led_position = (float)i / (float)(num_leds - 1);
            
            rgb_color_t full_color;
            // Adjust transition points - more green-to-orange, less orange-to-red
            if (led_position < 0.3f) {
                // Scale to 0.0 - 1.0 for green-to-orange part
                float adjusted_progress = led_position / 0.3f;
                full_color = calculate_gradient_color(WORK_TIMER_START_COLOR, WORK_TIMER_MID_COLOR, adjusted_progress);
            }
            // Last 30% is orange-to-red gradient
            else {
                float adjusted_progress = (led_position - 0.3f) / 0.7f; // Scale to 0.0 - 1.0 for last 20%
                full_color = calculate_gradient_color(WORK_TIMER_MID_COLOR, WORK_TIMER_END_COLOR, adjusted_progress);
            }
            
            // Dim the color based on progress within this LED and overall brightness
            color.r = (uint8_t)((float)full_color.r * current_led_progress * brightness_factor);
            color.g = (uint8_t)((float)full_color.g * current_led_progress * brightness_factor);
            color.b = (uint8_t)((float)full_color.b * current_led_progress * brightness_factor);
        }
        
        // Set the LED color
        rgb_matrix_set_color(WORK_TIMER_LED_START + i, color.r, color.g, color.b);
    }
}

/**
 * Update the pulse active state
 * This determines if any pulse effect is currently active
 */
static void update_pulse_active_state(void) {
    if (!work_timer.flags.active || work_timer.flags.paused) {
        work_timer.flags.pulse_active = false;
        return;
    }
    
    uint32_t current_time = timer_read32();
    
    // Check if any pulse condition is active
    bool lunch_warning = false;
    bool lunch_end_warning = false;
    bool mid_point_warning = false;
    bool end_warning = false;
    
    // Mid-break (lunch) timing logic
    if (work_timer.has_lunch_break) {
        // Time until mid-break (lunch)
        uint32_t time_to_mid_break = 0;
        if (current_time < work_timer.mid_break_time) {
            time_to_mid_break = work_timer.mid_break_time - current_time;
        }
        
        // Lunch break warning (before lunch)
        lunch_warning = !work_timer.flags.lunch_break && 
                       (time_to_mid_break > 0 && time_to_mid_break < BREAK_WARNING_TIME);
        
        // Lunch end warning (before end of lunch)
        lunch_end_warning = work_timer.flags.lunch_break && 
                          (timer_elapsed32(work_timer.break_start_time) >= 
                           (work_timer.mid_break_duration - BREAK_WARNING_TIME));
    } 
    else {
        // Simple mid-break logic
        uint32_t time_to_mid_break = 0;
        if (current_time < work_timer.mid_break_time) {
            time_to_mid_break = work_timer.mid_break_time - current_time;
        }
        
        // Mid-point break warning for shorter timers
        mid_point_warning = !work_timer.flags.mid_break && 
                          (time_to_mid_break > 0 && time_to_mid_break < BREAK_WARNING_TIME);
    }
    
    // End timer warning (5 minutes before end)
    end_warning = (current_time >= (work_timer.end_time - BREAK_WARNING_TIME) && 
                  current_time < work_timer.end_time);
    
    // Set pulse active if any of these conditions are true
    work_timer.flags.pulse_active = (
        work_timer.flags.mid_break ||           // Mid-point break pulse
        work_timer.flags.lunch_break ||         // Lunch break
        work_timer.flags.end_warning_shown ||   // End warning
        lunch_warning ||                        // Pre-lunch warning
        lunch_end_warning ||                    // End of lunch warning
        mid_point_warning ||                    // Mid-point warning for shorter timers
        end_warning                             // End warning for all timers
    );
}

/**
 * Toggle the work timer on/off
 */
void toggle_work_timer(void) {
    if (work_timer.flags.active) {
        // If timer is active, stop it and reset all state flags
        work_timer.flags.active = 0;
        work_timer.flags.paused = 0;
        work_timer.flags.lunch_break = 0;
        work_timer.flags.mid_break = 0;
        work_timer.flags.lunch_warning_shown = 0;
        work_timer.flags.mid_break_warning_shown = 0;
        work_timer.flags.end_warning_shown = 0;
        work_timer.flags.pulse_active = 0;
        
        // Save clean state to EEPROM
        save_work_timer_state();
        
        // Force immediate RGB refresh
        rgb_matrix_mode_noeeprom(rgb_matrix_get_mode());
    } else {
        // If timer is inactive, start a new timer
        work_timer.flags.active = 1;
        work_timer.flags.paused = 0;
        work_timer.flags.lunch_break = 0;
        work_timer.flags.mid_break = 0;
        work_timer.flags.lunch_warning_shown = 0;
        work_timer.flags.mid_break_warning_shown = 0;
        work_timer.flags.end_warning_shown = 0;
        work_timer.flags.pulse_active = 0;
        
        // Set timer start and calculate end time
        work_timer.start_time = timer_read32();
        work_timer.break_start_time = 0;
        
        // Set up mid-break time based on current time
        uint32_t duration = 0;
        switch (work_timer.timer_type) {
            case TIMER_TYPE_30MIN: duration = TIMER_30MIN_DURATION; break;
            case TIMER_TYPE_1HR:   duration = TIMER_1HR_DURATION; break;
            case TIMER_TYPE_4HR:   duration = TIMER_4HR_DURATION; break;
            case TIMER_TYPE_8HR:   duration = TIMER_8HR_DURATION; break;
            case TIMER_TYPE_10HR:  duration = TIMER_10HR_DURATION; break;
            default:               duration = TIMER_8HR_DURATION; break;
        }
        
        // Set mid-break time (halfway through timer)
        work_timer.mid_break_time = work_timer.start_time + (duration / 2);
        
        // Set end time
        work_timer.end_time = work_timer.start_time + duration;
        
        save_work_timer_state();
    }
    
    update_pulse_active_state();
}

/**
 * Initialize the work timer - load state from EEPROM
 */
void work_timer_init(void) {
    load_work_timer_state();
}

/**
 * Start a specific timer type
 */
void start_timer(work_timer_type_t timer_type) {
    // Reset timer state
    work_timer.flags.active = 1;
    work_timer.flags.paused = 0;
    work_timer.flags.lunch_break = 0;
    work_timer.flags.mid_break = 0;
    work_timer.flags.lunch_warning_shown = 0;
    work_timer.flags.mid_break_warning_shown = 0;
    work_timer.flags.end_warning_shown = 0;
    work_timer.flags.pulse_active = 0;
    
    work_timer.start_time = timer_read32();
    work_timer.break_start_time = 0;
    
    // Configure timer parameters based on type
    work_timer.timer_type = timer_type;
    configure_timer_for_type(timer_type);
    
    save_work_timer_state();
    
    // Update pulse state immediately after starting timer
    update_pulse_active_state();
}

/**
 * Pause or resume the work timer
 */
void toggle_pause_work_timer(void) {
    if (!work_timer.flags.active) return;
    
    if (!work_timer.flags.paused) {
        // Pause the timer
        work_timer.flags.paused = 1;
        work_timer.pause_time = timer_read32();
        save_work_timer_state();
    } else {
        // Resume the timer - extend all time values by pause duration
        uint32_t current_time = timer_read32();
        uint32_t pause_duration = current_time - work_timer.pause_time;
        
        // Extend end time by pause duration
        work_timer.end_time += pause_duration;
        
        // If mid-break hasn't happened yet, extend that too
        if (current_time < work_timer.mid_break_time) {
            work_timer.mid_break_time += pause_duration;
        }
        
        // If in a break, adjust break start time too
        if (work_timer.flags.lunch_break || work_timer.flags.mid_break) {
            work_timer.break_start_time += pause_duration;
        }
        
        work_timer.flags.paused = 0;
        save_work_timer_state();
    }
    
    update_pulse_active_state();
}

/**
 * Update the work timer state
 */
void update_work_timer(void) {
    if (!work_timer.flags.active || work_timer.flags.paused) return;
    
    uint32_t current_time = timer_read32();
    
    // Process different timer states based on timer type
    if (work_timer.has_lunch_break) {
        // Handle lunch break state transitions
        if (!work_timer.flags.lunch_break) {
            // Check if it's time to start lunch
            if (!work_timer.flags.lunch_warning_shown && 
                current_time >= (work_timer.mid_break_time - BREAK_WARNING_TIME) && 
                current_time < work_timer.mid_break_time) {
                // Pre-lunch warning
                work_timer.flags.lunch_warning_shown = 1;
            } 
            else if (current_time >= work_timer.mid_break_time) {
                // Start lunch break
                work_timer.flags.lunch_break = 1;
                work_timer.break_start_time = current_time;
                work_timer.flags.lunch_warning_shown = 0; // Reset for lunch end warning
                
                // Don't need to extend end time yet - will do that when break ends
                save_work_timer_state();
            }
        } 
        else {
            // Currently in lunch break
            uint32_t break_elapsed = timer_elapsed32(work_timer.break_start_time);
            
            // Check for lunch end warning
            if (!work_timer.flags.lunch_warning_shown && 
                break_elapsed >= (work_timer.mid_break_duration - BREAK_WARNING_TIME)) {
                // Pre-end warning
                work_timer.flags.lunch_warning_shown = 1;
            }
            
            // End lunch break after duration (plus grace period)
            if (break_elapsed >= (work_timer.mid_break_duration + 5000)) {
                // End lunch break
                work_timer.flags.lunch_break = 0;
                work_timer.flags.lunch_warning_shown = 0;
                
                // Extend end time by break duration
                work_timer.end_time += break_elapsed;
                
                save_work_timer_state();
            }
        }
    } 
    else {
        // Handle mid-break state transitions for shorter timers
        if (!work_timer.flags.mid_break) {
            // Check if it's time to start mid-break
            if (!work_timer.flags.mid_break_warning_shown && 
                current_time >= (work_timer.mid_break_time - BREAK_WARNING_TIME) && 
                current_time < work_timer.mid_break_time) {
                // Mid-break warning
                work_timer.flags.mid_break_warning_shown = 1;
            } 
            else if (current_time >= work_timer.mid_break_time) {
                // Start mid-break
                work_timer.flags.mid_break = 1;
                work_timer.break_start_time = current_time;
                work_timer.flags.mid_break_warning_shown = 0;
                save_work_timer_state();
            }
        } 
        else {
            // Currently in mid-break
            uint32_t break_elapsed = timer_elapsed32(work_timer.break_start_time);
            
            // End mid-break after duration (plus grace period)
            if (break_elapsed >= (work_timer.mid_break_duration + 5000)) {
                // End mid-break
                work_timer.flags.mid_break = 0;
                work_timer.flags.mid_break_warning_shown = 0;
                
                // Extend end time by break duration
                work_timer.end_time += break_elapsed;
                
                save_work_timer_state();
            }
        }
    }
    
    // Check for end of day warning
    if (!work_timer.flags.end_warning_shown && 
        current_time >= (work_timer.end_time - BREAK_WARNING_TIME)) {
        work_timer.flags.end_warning_shown = 1;
    }
    
    // Auto-stop after timer ends
    if (current_time >= work_timer.end_time) {
        work_timer.flags.active = 0;
        work_timer.flags.lunch_break = 0;
        work_timer.flags.mid_break = 0;
        save_work_timer_state();
    }
    
    update_pulse_active_state();
}

/**
 * Check if any timer pulse is currently active
 * Used for easier state checking
 * 
 * @return true if any timer pulse effect is active, false otherwise
 */
bool is_timer_pulse_active(void) {
    // If timer is not active or is paused, no pulse is active
    if (!work_timer.flags.active || work_timer.flags.paused) {
        return false;
    }
    
    // Return the pulse_active flag directly from the work timer state
    return work_timer.flags.pulse_active;
}

/**
 * Handle the work timer visualization on LEDs
 */
void handle_work_timer(void) {
    static bool was_active = false;
    
    if (!work_timer.flags.active) {
        // If the timer was just deactivated, force RGB refresh
        if (was_active) {
            rgb_matrix_mode_noeeprom(rgb_matrix_get_mode());
            was_active = false;
        }
        return;
    }
    
    was_active = true;
    
    // Get current RGB matrix brightness
    uint8_t rgb_brightness = rgb_matrix_get_val();
    float brightness_factor = (float)rgb_brightness / 255.0f;
    
    // Number of LEDs in the progress bar
    const uint8_t num_leds = WORK_TIMER_LED_END - WORK_TIMER_LED_START + 1;
    
    // Calculate overall progress (0.0 - 1.0)
    uint32_t current_time = timer_read32();
    float overall_progress;
    
    // Simple progress calculation based on total time range
    if (work_timer.flags.paused) {
        // When paused, use the pause time for calculation
        overall_progress = (float)(work_timer.pause_time - work_timer.start_time) / 
                          (float)(work_timer.end_time - work_timer.start_time);
    } else {
        // Normal operation - current progress through timer
        overall_progress = (float)(current_time - work_timer.start_time) / 
                          (float)(work_timer.end_time - work_timer.start_time);
    }
    
    if (overall_progress > 1.0f) overall_progress = 1.0f;
    
    // Create pulsing effect
    uint8_t pulse_brightness = abs((timer_read() / 4) % 510 - 255);
    float pulse_ratio = (float)pulse_brightness / 255.0f;
    
    // Check for various timer states
    bool lunch_warning = false;
    bool lunch_end_warning = false;
    bool mid_break_warning = false;
    bool end_warning = false;
    
    // For timers with lunch breaks
    if (work_timer.has_lunch_break) {
        // Pre-lunch warning (red pulse)
        lunch_warning = !work_timer.flags.lunch_break && 
                      (current_time >= (work_timer.mid_break_time - BREAK_WARNING_TIME) && 
                       current_time < work_timer.mid_break_time);
        
        // Lunch-end warning (red pulse)
        lunch_end_warning = work_timer.flags.lunch_break && 
                          work_timer.break_start_time != 0 &&
                          (timer_elapsed32(work_timer.break_start_time) >= 
                           (work_timer.mid_break_duration - BREAK_WARNING_TIME));
        
        // End warning
        end_warning = current_time >= (work_timer.end_time - BREAK_WARNING_TIME) && 
                     current_time < work_timer.end_time;
        
        // Choose appropriate display based on current state
        if (lunch_warning || lunch_end_warning) {
            // Pre/Post lunch red warning pulse 
            rgb_color_t pulse_color = WORK_TIMER_WARNING_COLOR;
            
            // Apply pulsing effect to all progress bar LEDs
            for (uint8_t i = 0; i < num_leds; i++) {
                rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                   (uint8_t)((float)pulse_color.r * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.g * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.b * pulse_ratio * brightness_factor));
            }
        }
        else if (work_timer.flags.lunch_break && work_timer.break_start_time != 0) {
            // During lunch break - blue pulse
            rgb_color_t pulse_color = WORK_TIMER_LUNCH_COLOR;
            
            // Use a slower pulse for regular lunch break
            uint8_t lunch_pulse = abs((timer_read() / 10) % 510 - 255);
            float lunch_pulse_ratio = (float)lunch_pulse / 255.0f;
            
            // Apply lunch break color to all progress bar LEDs
            for (uint8_t i = 0; i < num_leds; i++) {
                rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                   (uint8_t)((float)pulse_color.r * lunch_pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.g * lunch_pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.b * lunch_pulse_ratio * brightness_factor));
            }
        }
        else if (work_timer.flags.end_warning_shown || end_warning) {
            // End of day warning - red pulse
            rgb_color_t pulse_color = WORK_TIMER_WARNING_COLOR;
            
            // Apply pulsing effect to all progress bar LEDs
            for (uint8_t i = 0; i < num_leds; i++) {
                rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                   (uint8_t)((float)pulse_color.r * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.g * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.b * pulse_ratio * brightness_factor));
            }
        } 
        else {
            // Normal progress bar display
            display_progress_bar(num_leds, overall_progress, brightness_factor);
        }
    } 
    // For timers without lunch breaks (30MIN, 1HR, 4HR)
    else {
        mid_break_warning = !work_timer.flags.mid_break && 
                         (current_time >= (work_timer.mid_break_time - BREAK_WARNING_TIME) && 
                          current_time < work_timer.mid_break_time);
        
        end_warning = current_time >= (work_timer.end_time - BREAK_WARNING_TIME) && 
                     current_time < work_timer.end_time;
        
        // Choose appropriate display based on current state
        if (mid_break_warning) {
            // Mid-break warning - red pulse
            rgb_color_t pulse_color = WORK_TIMER_WARNING_COLOR;
            
            // Apply pulsing effect to all progress bar LEDs
            for (uint8_t i = 0; i < num_leds; i++) {
                rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                   (uint8_t)((float)pulse_color.r * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.g * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.b * pulse_ratio * brightness_factor));
            }
        }
        // Mid-break active
        else if (work_timer.flags.mid_break && work_timer.break_start_time != 0) {
            // Mid-break active - blue pulse
            rgb_color_t pulse_color = WORK_TIMER_LUNCH_COLOR;
            
            // Use a faster pulse for mid-break reminder
            uint8_t mid_pulse = abs((timer_read() / 3) % 510 - 255);
            float mid_pulse_ratio = (float)mid_pulse / 255.0f;
            
            // Apply pulsing effect to all progress bar LEDs
            for (uint8_t i = 0; i < num_leds; i++) {
                rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                   (uint8_t)((float)pulse_color.r * mid_pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.g * mid_pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.b * mid_pulse_ratio * brightness_factor));
            }
        }
        else if (work_timer.flags.end_warning_shown || end_warning) {
            // End of timer warning - red pulse
            rgb_color_t pulse_color = WORK_TIMER_WARNING_COLOR;
            
            // Apply pulsing effect to all progress bar LEDs
            for (uint8_t i = 0; i < num_leds; i++) {
                rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                   (uint8_t)((float)pulse_color.r * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.g * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.b * pulse_ratio * brightness_factor));
            }
        } 
        else {
            // Normal progress bar display
            display_progress_bar(num_leds, overall_progress, brightness_factor);
        }
    }
}

/**
 * Work timer task - can be called periodically
 */
void work_timer_task(void) {
    // Update work timer state
    update_work_timer();
}