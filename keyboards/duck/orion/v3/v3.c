/* Copyright 2019 MechMerlin <mechmerlin@gmail.com>
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
#include "indicator_leds.h"

// Alphas              PB1
// Navigation Cluster: PB2
// Number Row, Mods:   PB3
// Function Row:       PE6

// Other than using RGB or LED matrix, QMK cannot turn on specific zones
// of backlight LEDs. Unfortunately, Duck PCBs do not follow this design
// and instead use multiple pins connected to each of these zones. QMK is
// only able to control them ALL with the current default mechanisms. 

// Locking indicator LEDs
// The Duck Orion V3 has 3 locking indicator LEDs and are located to the right
// of the Escape key. 
bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        gpio_write_pin(B0, !led_state.caps_lock);
        gpio_write_pin(B4, !led_state.num_lock);
        gpio_write_pin(D7, !led_state.scroll_lock);
    }
    return true;
}
