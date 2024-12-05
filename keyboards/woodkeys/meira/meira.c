/* Copyright 2017 Cole Markham, WoodKeys.click
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
#include "meira.h"

void matrix_init_kb(void) {
#ifdef WATCHDOG_ENABLE
    // This is done after turning the layer LED red, if we're caught in a loop
    // we should get a flashing red light
    wdt_enable(WDTO_500MS);
#endif

    // put your keyboard start-up code here
    // runs once when the firmware starts up
    matrix_init_user();
}

void housekeeping_task_kb(void) {
#ifdef WATCHDOG_ENABLE
    wdt_reset();
#endif
}

bool shutdown_kb(bool jump_to_bootloader) {
#ifdef WATCHDOG_ENABLE
    // Unconditionally run so shutdown_user can't mess up watchdog
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif

    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
    return true;
}
