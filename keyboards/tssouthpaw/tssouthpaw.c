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

 #include "tssouthpaw.h"
 #include "rgb_effects/rgb_effects.h"
 #include "rgb_effects/work_timer.h"
 
 /**
  * Keyboard initialization
  * Called once at startup
  */
 void keyboard_post_init_kb(void) {
     // Initialize RGB lighting effects
     rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
     rgb_matrix_sethsv_noeeprom(HSV_GREEN);  // Set default color to green
     
     // Enable N-Key Rollover
     keymap_config.nkro = true;
     
     // Load saved work timer state from EEPROM if applicable
     work_timer_init();
     
     // Continue with any user-level initialization
     keyboard_post_init_user();
 }
 
 /**
  * Power management function - Called when system is going to sleep
  */
 void suspend_power_down_kb(void) {
     // If timer pulse is active, ensure RGB matrix remains active
     if (is_timer_pulse_active()) {
         // Ensure RGB matrix has reasonable brightness for notifications
         uint8_t val = rgb_matrix_get_val();
         if (val < RGB_MATRIX_MINIMUM_BRIGHTNESS) {
             rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), RGB_MATRIX_MINIMUM_BRIGHTNESS);
         }
         
         // Return early to skip deep sleep routines
         return;
     }
     
     // Only disable RGB effects when no timer pulse is active
     rgb_matrix_set_suspend_state(true);
     suspend_power_down_user();
 }
  
 /**
  * Power management function - Called when system is waking from sleep
  */
 void suspend_wakeup_init_kb(void) {
     // Re-enable RGB effects when computer wakes up
     rgb_matrix_set_suspend_state(false);
     
     // Make sure the timer pulse state is properly reflected
     // This ensures the timer visuals are immediately visible
     if (is_timer_pulse_active()) {
         // Ensure RGB matrix effect is enabled with proper brightness
         uint8_t val = rgb_matrix_get_val();
         if (val < RGB_MATRIX_MINIMUM_BRIGHTNESS) {
             rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), RGB_MATRIX_MINIMUM_BRIGHTNESS);
         }
     }
     
     suspend_wakeup_init_user();
 }
 
 /**
  * Regular task hook to ensure timer updates even during suspend
  */
 void housekeeping_task_user(void) {
     // Update work timer even during suspend
     if (is_timer_pulse_active()) {
         update_work_timer();
         handle_work_timer();
     }
 }
  
 // Default implementations for weak functions
 __attribute__((weak)) void keyboard_post_init_user(void) {}
 __attribute__((weak)) void suspend_power_down_user(void) {}
 __attribute__((weak)) void suspend_wakeup_init_user(void) {}
