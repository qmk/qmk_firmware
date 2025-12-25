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

#include "quantum.h"
#include "rgb_effects/rgb_effects.h"

/**
 * Keyboard post-initialization
 *
 * Called once at startup to configure RGB matrix, enable N-Key Rollover,
 * and prepare the keyboard for operation.
 */
void keyboard_post_init_kb(void) {
    // Initialize RGB lighting effects
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_GREEN);  // Set default color to green

    // Enable N-Key Rollover
    keymap_config.nkro = true;

    // Enable RGB matrix
    rgb_matrix_set_suspend_state(false);

    // Continue with any user-level initialization
    keyboard_post_init_user();
}

/**
 * System suspend power down handler
 *
 * Called when the system is going to sleep. Disables RGB matrix
 * to reduce power consumption during system suspend.
 */
void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

/**
 * System suspend wakeup handler
 *
 * Called when the system is waking from sleep. Re-enables RGB matrix
 * to restore lighting effects.
 */
void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
