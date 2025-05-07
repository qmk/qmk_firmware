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
 
 // Work timer state structure
 typedef struct {
     work_timer_flags_t flags;
     work_timer_type_t timer_type;
     uint32_t start_time;
     uint32_t elapsed_time;    // Work time (excluding breaks)
     uint32_t pause_time;
     uint32_t break_start_time; // When current break started
     uint32_t total_break_time; // Total accumulated break time
     uint32_t timer_duration;   // Total work time duration (excludes breaks)
     uint32_t mid_break_start;  // When in workday the break occurs
     uint32_t mid_break_duration;
     bool has_lunch_break;
 } work_timer_t;
 
 // Global work timer state
 static work_timer_t work_timer = {
     .flags = {0},
     .timer_type = TIMER_TYPE_8HR,
     .start_time = 0,
     .elapsed_time = 0,
     .pause_time = 0,
     .break_start_time = 0,
     .total_break_time = 0,
     .timer_duration = TIMER_8HR_DURATION,
     .mid_break_start = TIMER_8HR_DURATION / 2, // Default halfway point
     .mid_break_duration = LUNCH_BREAK_DURATION,
     .has_lunch_break = true
 };
 
 // Predefined RGB colors for timer states
 static const rgb_color_t WORK_TIMER_START_COLOR = {WORK_TIMER_START_R, WORK_TIMER_START_G, WORK_TIMER_START_B};
 static const rgb_color_t WORK_TIMER_MID_COLOR = {WORK_TIMER_MID_R, WORK_TIMER_MID_G, WORK_TIMER_MID_B};
 static const rgb_color_t WORK_TIMER_END_COLOR = {WORK_TIMER_END_R, WORK_TIMER_END_G, WORK_TIMER_END_B};
 static const rgb_color_t WORK_TIMER_LUNCH_COLOR = {WORK_TIMER_LUNCH_R, WORK_TIMER_LUNCH_G, WORK_TIMER_LUNCH_B};
 static const rgb_color_t WORK_TIMER_WARNING_COLOR = {WORK_TIMER_WARNING_R, WORK_TIMER_WARNING_G, WORK_TIMER_WARNING_B};
 static const rgb_color_t WORK_TIMER_BREAK_WARNING_COLOR = {WORK_TIMER_WARNING_R, WORK_TIMER_WARNING_G, WORK_TIMER_WARNING_B};
 
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
             work_timer.timer_duration = TIMER_30MIN_DURATION;
             work_timer.mid_break_start = TIMER_30MIN_DURATION / 2;
             work_timer.mid_break_duration = MID_BREAK_30MIN_DURATION;
             work_timer.has_lunch_break = false;
             break;
             
         case TIMER_TYPE_1HR:
             work_timer.timer_duration = TIMER_1HR_DURATION;
             work_timer.mid_break_start = TIMER_1HR_DURATION / 2;
             work_timer.mid_break_duration = MID_BREAK_1HR_DURATION;
             work_timer.has_lunch_break = false;
             break;
             
         case TIMER_TYPE_4HR:
             work_timer.timer_duration = TIMER_4HR_DURATION;
             work_timer.mid_break_start = TIMER_4HR_DURATION / 2;
             work_timer.mid_break_duration = MID_BREAK_4HR_DURATION;
             work_timer.has_lunch_break = false;
             break;
             
         case TIMER_TYPE_8HR:
             work_timer.timer_duration = TIMER_8HR_DURATION;
             work_timer.mid_break_start = TIMER_8HR_DURATION / 2;
             work_timer.mid_break_duration = LUNCH_BREAK_DURATION;
             work_timer.has_lunch_break = true;
             break;
             
         case TIMER_TYPE_10HR:
             work_timer.timer_duration = TIMER_10HR_DURATION;
             work_timer.mid_break_start = TIMER_10HR_DURATION / 2;
             work_timer.mid_break_duration = LUNCH_BREAK_DURATION;
             work_timer.has_lunch_break = true;
             break;
             
         default:
             // Default to 8HR if something goes wrong
             work_timer.timer_duration = TIMER_8HR_DURATION;
             work_timer.mid_break_start = TIMER_8HR_DURATION / 2;
             work_timer.mid_break_duration = LUNCH_BREAK_DURATION;
             work_timer.has_lunch_break = true;
             break;
     }
 }
 
 /**
  * Save the work timer state to EEPROM
  * Modern QMK using block-based EEPROM operations for RP2040
  */
 static void save_work_timer_state(void) {
     // Create a buffer to store all our data
     uint8_t buffer[19] = {0}; // 19 bytes total
     
     // Set the active flag
     buffer[0] = work_timer.flags.active;
     
     // Only save time info if timer is active
     if (work_timer.flags.active) {
         // Save start time (4 bytes)
         memcpy(&buffer[1], &work_timer.start_time, sizeof(uint32_t));
         
         // Save elapsed time (4 bytes)
         memcpy(&buffer[5], &work_timer.elapsed_time, sizeof(uint32_t));
         
         // Save total break time (4 bytes)
         memcpy(&buffer[9], &work_timer.total_break_time, sizeof(uint32_t));
         
         // Save timer type (1 byte)
         buffer[13] = (uint8_t)work_timer.timer_type;
         
         // Save break state (1 byte)
         buffer[14] = (work_timer.flags.lunch_break ? 1 : 0) | 
                      (work_timer.flags.mid_break ? 2 : 0);
         
         // Save break start time (4 bytes)
         memcpy(&buffer[15], &work_timer.break_start_time, sizeof(uint32_t));
     }
     
     // Write all data at once to EEPROM
     eeprom_update_block(buffer, (void *)EEPROM_WORK_TIMER_ACTIVE, sizeof(buffer));
 }
 
 /**
  * Load the work timer state from EEPROM
  * Modern QMK using block-based EEPROM operations for RP2040
  */
 static void load_work_timer_state(void) {
     // Create a buffer to read all our data
     uint8_t buffer[19] = {0}; // 19 bytes total
     
     // Read all data at once from EEPROM
     eeprom_read_block(buffer, (const void *)EEPROM_WORK_TIMER_ACTIVE, sizeof(buffer));
     
     // Get the active flag
     work_timer.flags.active = buffer[0];
     
     // Only process the rest if timer was active
     if (work_timer.flags.active) {
         // Load timer type
         work_timer_type_t saved_type = (work_timer_type_t)buffer[13];
         
         // Apply configuration for this timer type
         configure_timer_for_type(saved_type);
         
         // Get start time (4 bytes)
         memcpy(&work_timer.start_time, &buffer[1], sizeof(uint32_t));
         
         // Get the elapsed work time (4 bytes)
         memcpy(&work_timer.elapsed_time, &buffer[5], sizeof(uint32_t));
         
         // Get the total break time (4 bytes)
         memcpy(&work_timer.total_break_time, &buffer[9], sizeof(uint32_t));
         
         // Get break state (1 byte)
         uint8_t break_state = buffer[14];
         work_timer.flags.lunch_break = (break_state & 1) > 0;
         work_timer.flags.mid_break = (break_state & 2) > 0;
         
         // Get break start time (4 bytes)
         memcpy(&work_timer.break_start_time, &buffer[15], sizeof(uint32_t));
         
         // If in a break, adjust break_start_time to account for time powered off
         if (work_timer.flags.lunch_break || work_timer.flags.mid_break) {
             uint32_t current_time = timer_read32();
             uint32_t time_off = current_time - work_timer.break_start_time;
             
             // If we've been off for less than the break duration, continue the break
             if (work_timer.flags.lunch_break && 
                 time_off < work_timer.mid_break_duration) {
                 // Stay in lunch break, adjust break_start_time
                 work_timer.break_start_time = current_time - time_off;
             } 
             else if (work_timer.flags.mid_break && 
                      time_off < work_timer.mid_break_duration) {
                 // Stay in mid-break, adjust break_start_time
                 work_timer.break_start_time = current_time - time_off;
             }
             else {
                 // Break would have ended while powered off
                 work_timer.flags.lunch_break = 0;
                 work_timer.flags.mid_break = 0;
                 
                 // Add the remaining break time to total_break_time
                 // This is approximate but better than nothing
                 if (time_off < work_timer.mid_break_duration) {
                     work_timer.total_break_time += work_timer.mid_break_duration;
                 }
             }
         }
         
         // Calculate elapsed wall time (including time powered off)
         uint32_t current_time = timer_read32();
         uint32_t wall_time_elapsed = current_time - work_timer.start_time;
         
         // Adjust start time to account for time powered off, preserving elapsed_time
         work_timer.start_time = current_time - wall_time_elapsed;
         
         // Validate time values - if unreasonable, reset
         if (work_timer.elapsed_time > work_timer.timer_duration) {
             work_timer.flags.active = 0;
             save_work_timer_state();
         }
         
         // Check for end warning state
         if (work_timer.elapsed_time >= (work_timer.timer_duration - BREAK_WARNING_TIME)) {
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
  * This determines if the keyboard should wake from sleep for timer notification
  */
 static void update_pulse_active_state(void) {
     if (!work_timer.flags.active || work_timer.flags.paused) {
         work_timer.flags.pulse_active = false;
         return;
     }
     
     // Check if any pulse condition is active
     bool lunch_warning = false;
     bool lunch_end_warning = false;
     bool mid_point_warning = false;
     bool end_warning = false;
     
     // For timers with lunch breaks
     if (work_timer.has_lunch_break) {
         // Lunch break warning (before lunch)
         lunch_warning = !work_timer.flags.lunch_break && 
                        (work_timer.elapsed_time >= (work_timer.mid_break_start - BREAK_WARNING_TIME) && 
                         work_timer.elapsed_time < work_timer.mid_break_start);
         
         // Lunch end warning (before end of lunch)
         lunch_end_warning = work_timer.flags.lunch_break && 
                            (timer_elapsed32(work_timer.break_start_time) >= (work_timer.mid_break_duration - BREAK_WARNING_TIME));
     } else {
         // Mid-point break warning for shorter timers
         mid_point_warning = !work_timer.flags.mid_break && 
                           (work_timer.elapsed_time >= (work_timer.mid_break_start - BREAK_WARNING_TIME) && 
                            work_timer.elapsed_time < work_timer.mid_break_start);
     }
     
     // End timer warning (5 minutes before end)
     end_warning = (work_timer.elapsed_time >= (work_timer.timer_duration - BREAK_WARNING_TIME) && 
                   work_timer.elapsed_time < work_timer.timer_duration);
     
     // Set pulse active if any of these conditions are true
     bool new_pulse_active = (
         work_timer.flags.mid_break ||           // Mid-point break pulse
         work_timer.flags.lunch_break ||         // Lunch break
         work_timer.flags.end_warning_shown ||   // End warning
         lunch_warning ||                        // Pre-lunch warning
         lunch_end_warning ||                    // End of lunch warning
         mid_point_warning ||                    // Mid-point warning for shorter timers
         end_warning                             // End warning for all timers
     );
     
     // Force a wakeup signal if transitioning from inactive to active pulse
     if (!work_timer.flags.pulse_active && new_pulse_active) {
         // Explicitly wake up keyboard by toggling suspend state
         rgb_matrix_set_suspend_state(false);
         
         // Force appropriate brightness for notifications
         uint8_t val = rgb_matrix_get_val();
         if (val < RGB_MATRIX_MINIMUM_BRIGHTNESS) {
             rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), RGB_MATRIX_MINIMUM_BRIGHTNESS);
         }
     }
     
     work_timer.flags.pulse_active = new_pulse_active;
 }
 
 /**
  * Toggle the work timer on/off
  */
 void toggle_work_timer(void) {
     if (work_timer.flags.active) {
         // If timer is active, stop it
         work_timer.flags.active = 0;
         work_timer.flags.pulse_active = 0;  // Clear pulse active flag
         save_work_timer_state();
     } else {
         // If timer is inactive, just activate it with current settings
         // This assumes the timer type and duration are already set
         work_timer.flags.active = 1;
         work_timer.flags.paused = 0;
         work_timer.flags.lunch_break = 0;
         work_timer.flags.mid_break = 0;
         work_timer.flags.lunch_warning_shown = 0;
         work_timer.flags.mid_break_warning_shown = 0;
         work_timer.flags.end_warning_shown = 0;
         work_timer.flags.pulse_active = 0;
         
         work_timer.start_time = timer_read32();
         work_timer.elapsed_time = 0;
         work_timer.pause_time = 0;
         work_timer.break_start_time = 0;
         work_timer.total_break_time = 0;
         
         save_work_timer_state();
     }
     
     // Ensure timer visual updates immediately after toggle
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
     // Configure timer parameters based on type
     configure_timer_for_type(timer_type);
     
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
     work_timer.elapsed_time = 0;
     work_timer.pause_time = 0;
     work_timer.break_start_time = 0;
     work_timer.total_break_time = 0;
     
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
         // Resume the timer, adjust start time to account for pause duration
         uint32_t pause_duration = timer_read32() - work_timer.pause_time;
         work_timer.start_time += pause_duration;
         
         // If in a break, adjust break start time too
         if (work_timer.flags.lunch_break || work_timer.flags.mid_break) {
             work_timer.break_start_time += pause_duration;
         }
         
         work_timer.flags.paused = 0;
         save_work_timer_state();
     }
     
     // Update pulse state after changing pause status
     update_pulse_active_state();
 }
 
 /**
  * Update the work timer state
  */
 void update_work_timer(void) {
     if (!work_timer.flags.active || work_timer.flags.paused) return;
     
     // Calculate wall time (real-world time) elapsed since start
     uint32_t wall_time_elapsed = timer_read32() - work_timer.start_time;
     
     // Current wall time
     uint32_t current_time = timer_read32();
     
     // Process different timer states based on timer type
     if (work_timer.has_lunch_break) {
         // For timers with lunch breaks (8HR and 10HR)
         
         // Handle lunch break state transitions
         if (!work_timer.flags.lunch_break) {
             // Check if it's time to start lunch
             if (!work_timer.flags.lunch_warning_shown && 
                 work_timer.elapsed_time >= (work_timer.mid_break_start - BREAK_WARNING_TIME) && 
                 work_timer.elapsed_time < work_timer.mid_break_start) {
                 // Pre-lunch warning (red pulse before lunch)
                 work_timer.flags.lunch_warning_shown = 1;
             } 
             else if (work_timer.elapsed_time >= work_timer.mid_break_start) {
                 // Start lunch break
                 work_timer.flags.lunch_break = 1;
                 work_timer.break_start_time = current_time;
                 work_timer.flags.lunch_warning_shown = 0; // Reset for lunch end warning
                 
                 // Save state when entering lunch break
                 save_work_timer_state();
             }
         } 
         else {
             // Currently in lunch break
             uint32_t break_elapsed = timer_elapsed32(work_timer.break_start_time);
             
             // Check for lunch end warning
             if (!work_timer.flags.lunch_warning_shown && 
                 break_elapsed >= (work_timer.mid_break_duration - BREAK_WARNING_TIME)) {
                 // Pre-end warning (red pulse before end of lunch)
                 work_timer.flags.lunch_warning_shown = 1;
             }
             
             // FIX: Emergency safety - force end lunch if it's been active way too long
             // This addresses the stuck lunch mode issue
             if (break_elapsed >= (work_timer.mid_break_duration * 2)) {
                 // Break has been active for twice as long as it should be - force exit
                 work_timer.flags.lunch_break = 0;
                 work_timer.flags.lunch_warning_shown = 0;
                 work_timer.total_break_time += work_timer.mid_break_duration; // Use exact duration instead
                 save_work_timer_state();
             }
             // Normal lunch break end check
             else if (break_elapsed >= work_timer.mid_break_duration) {
                 // End lunch break
                 work_timer.flags.lunch_break = 0;
                 work_timer.flags.lunch_warning_shown = 0; // FIX: Reset the warning flag
                 
                 // Add the break time to total_break_time - use the exact duration
                 // FIX: Use the exact lunch break duration instead of elapsed time
                 work_timer.total_break_time += work_timer.mid_break_duration;
                 
                 // Save state when exiting lunch break
                 save_work_timer_state();
             }
         }
     } 
     else {
         // For shorter timers without lunch breaks (30MIN, 1HR, 4HR)
         
         // Handle mid-break state transitions
         if (!work_timer.flags.mid_break) {
             // Check if it's time to start mid-break
             if (!work_timer.flags.mid_break_warning_shown && 
                 work_timer.elapsed_time >= (work_timer.mid_break_start - BREAK_WARNING_TIME) && 
                 work_timer.elapsed_time < work_timer.mid_break_start) {
                 // Mid-break warning
                 work_timer.flags.mid_break_warning_shown = 1;
             } 
             else if (work_timer.elapsed_time >= work_timer.mid_break_start) {
                 // Start mid-break
                 work_timer.flags.mid_break = 1;
                 work_timer.break_start_time = current_time;
                 save_work_timer_state();
             }
         } 
         else {
             // Currently in mid-break
             uint32_t break_elapsed = timer_elapsed32(work_timer.break_start_time);
             
             // FIX: Emergency safety - force end mid-break if it's been active way too long
             if (break_elapsed >= (work_timer.mid_break_duration * 2)) {
                 // Break has been active for twice as long as it should be - force exit
                 work_timer.flags.mid_break = 0;
                 work_timer.flags.mid_break_warning_shown = 0;
                 work_timer.total_break_time += work_timer.mid_break_duration;
                 save_work_timer_state();
             }
             // Normal mid-break end check
             else if (break_elapsed >= work_timer.mid_break_duration) {
                 // End mid-break
                 work_timer.flags.mid_break = 0;
                 work_timer.flags.mid_break_warning_shown = 0; // FIX: Reset warning flag
                 
                 // Add the break time to total_break_time
                 work_timer.total_break_time += work_timer.mid_break_duration;
                 save_work_timer_state();
             }
         }
     }
     
     // Calculate true work time (excluding breaks)
     if (work_timer.flags.lunch_break || work_timer.flags.mid_break) {
         // Currently in a break, so work time is wall time minus total breaks 
         // minus current break elapsed time
         uint32_t current_break_elapsed = timer_elapsed32(work_timer.break_start_time);
         work_timer.elapsed_time = wall_time_elapsed - work_timer.total_break_time - current_break_elapsed;
     } else {
         // Not in a break, so work time is wall time minus total breaks
         work_timer.elapsed_time = wall_time_elapsed - work_timer.total_break_time;
     }
     
     // Check for end of day warning (5 min before end)
     if (!work_timer.flags.end_warning_shown && 
         work_timer.elapsed_time >= (work_timer.timer_duration - BREAK_WARNING_TIME)) {
         work_timer.flags.end_warning_shown = 1;
     }
     
     // Auto-stop after timer duration
     if (work_timer.elapsed_time >= work_timer.timer_duration) {
         work_timer.flags.active = 0;
         save_work_timer_state();
     }
     
     // Update the pulse active state for wakeup
     update_pulse_active_state();
 }
 
/**
  * Check if any timer pulse is currently active
  * Used for wake-from-sleep functionality
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
    if (!work_timer.flags.active) return;
    
    // Get current RGB matrix brightness value (0-255)
    uint8_t rgb_brightness = rgb_matrix_get_val();
    float brightness_factor = (float)rgb_brightness / 255.0f;
    
    // Ensure minimum brightness during notifications
    // (RGB matrix must be awake for this to have an effect)
    if (work_timer.flags.pulse_active && rgb_brightness < RGB_MATRIX_MINIMUM_BRIGHTNESS) {
        rgb_brightness = RGB_MATRIX_MINIMUM_BRIGHTNESS;
        brightness_factor = (float)RGB_MATRIX_MINIMUM_BRIGHTNESS / 255.0f;
        // Don't permanently change the RGB settings, just adjust for calculations
    }
    
    // Number of LEDs in the progress bar
    const uint8_t num_leds = WORK_TIMER_LED_END - WORK_TIMER_LED_START + 1;
    
    // Calculate overall progress (0.0 - 1.0)
    float overall_progress = (float)work_timer.elapsed_time / (float)work_timer.timer_duration;
    if (overall_progress > 1.0f) overall_progress = 1.0f;
    
    // Create a pulsing effect by varying brightness based on timer
    uint8_t pulse_brightness = abs((timer_read() / 4) % 510 - 255);
    float pulse_ratio = (float)pulse_brightness / 255.0f;
    
    // Check for various timer states
    bool lunch_warning = false;
    bool lunch_end_warning = false;
    
    // For timers with lunch breaks (8HR and 10HR)
    if (work_timer.has_lunch_break) {
        // Pre-lunch warning (red pulse)
        lunch_warning = !work_timer.flags.lunch_break && 
                      (work_timer.elapsed_time >= (work_timer.mid_break_start - BREAK_WARNING_TIME) && 
                       work_timer.elapsed_time < work_timer.mid_break_start);
        
        // Lunch-end warning (red pulse)
        lunch_end_warning = work_timer.flags.lunch_break && 
                          (timer_elapsed32(work_timer.break_start_time) >= (work_timer.mid_break_duration - BREAK_WARNING_TIME));
                          
        // Choose appropriate display based on current state
        if (lunch_warning || lunch_end_warning) {
            // Pre/Post lunch red warning pulse 
            rgb_color_t pulse_color = WORK_TIMER_BREAK_WARNING_COLOR;
            
            // Apply pulsing effect to all progress bar LEDs
            for (uint8_t i = 0; i < num_leds; i++) {
                rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                   (uint8_t)((float)pulse_color.r * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.g * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.b * pulse_ratio * brightness_factor));
            }
        }
        else if (work_timer.flags.lunch_break) {
            // During lunch break - blue pulse
            rgb_color_t pulse_color = WORK_TIMER_LUNCH_COLOR;
            
            // Use a slower pulse for regular lunch break
            uint8_t lunch_pulse = abs((timer_read() / 10) % 510 - 255);
            float lunch_pulse_ratio = (float)lunch_pulse / 255.0f;
            
            // FIXED: Track how long the lunch break has been active
            uint32_t break_elapsed = timer_elapsed32(work_timer.break_start_time);
            
            // FIXED: Emergency safety - if lunch is stuck for more than 2x the duration, force exit
            if (break_elapsed > (work_timer.mid_break_duration * 2)) {
                work_timer.flags.lunch_break = 0;
                work_timer.total_break_time += work_timer.mid_break_duration;
                return; // Exit and let the next update handle normal display
            }
            
            // Apply lunch break color to all progress bar LEDs
            for (uint8_t i = 0; i < num_leds; i++) {
                rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                   (uint8_t)((float)pulse_color.r * lunch_pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.g * lunch_pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.b * lunch_pulse_ratio * brightness_factor));
            }
        }
        else if (work_timer.flags.end_warning_shown) {
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
        bool mid_break_warning = !work_timer.flags.mid_break && 
                              (work_timer.elapsed_time >= (work_timer.mid_break_start - BREAK_WARNING_TIME) && 
                               work_timer.elapsed_time < work_timer.mid_break_start);
        
        // Choose appropriate display based on current state
        if (mid_break_warning) {
            // Mid-break warning - red pulse
            rgb_color_t pulse_color = WORK_TIMER_BREAK_WARNING_COLOR;
            
            // Apply pulsing effect to all progress bar LEDs
            for (uint8_t i = 0; i < num_leds; i++) {
                rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                   (uint8_t)((float)pulse_color.r * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.g * pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.b * pulse_ratio * brightness_factor));
            }
        }
        else if (work_timer.flags.mid_break) {
            // Mid-break active - blue pulse
            rgb_color_t pulse_color = WORK_TIMER_LUNCH_COLOR;
            
            // Use a faster pulse for mid-break reminder
            uint8_t mid_pulse = abs((timer_read() / 3) % 510 - 255);
            float mid_pulse_ratio = (float)mid_pulse / 255.0f;
            
            // FIXED: Track how long the mid-break has been active
            uint32_t break_elapsed = timer_elapsed32(work_timer.break_start_time);
            
            // FIXED: Emergency safety - if mid-break is stuck for more than 2x the duration, force exit
            if (break_elapsed > (work_timer.mid_break_duration * 2)) {
                work_timer.flags.mid_break = 0;
                work_timer.total_break_time += work_timer.mid_break_duration;
                return; // Exit and let the next update handle normal display
            }
            
            // Apply pulsing effect to all progress bar LEDs
            for (uint8_t i = 0; i < num_leds; i++) {
                rgb_matrix_set_color(WORK_TIMER_LED_START + i, 
                                   (uint8_t)((float)pulse_color.r * mid_pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.g * mid_pulse_ratio * brightness_factor),
                                   (uint8_t)((float)pulse_color.b * mid_pulse_ratio * brightness_factor));
            }
        }
        else if (work_timer.flags.end_warning_shown) {
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