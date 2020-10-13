/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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

#include "pointing_devices.h"

void pointing_device_init(void) {
#ifdef THUMBSTICK_ENABLE
    thumbstick_init_user();
#endif
}

void pointing_device_task(void) {
#ifdef THUMBSTICK_ENABLE
    report_mouse_t report  = pointing_device_get_report();
    bool           changed = thumbstick_update(&report);
    pointing_device_set_report(report);
    pointing_device_send();
    if (changed) {
        thumbstick_update_user();
    }
#endif
}
