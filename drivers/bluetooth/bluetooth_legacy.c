/*
 * Copyright 2022
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

/** DEPRECATED: Provided for backward compatibility */

#include <stddef.h>
#include "bluetooth.h"
#include "bluetooth_legacy.h"

__attribute__((weak)) void bluetooth_init(void) {
    bluetooth_driver.init();
}

__attribute__((weak)) void bluetooth_task(void) {
    if (NULL != (*bluetooth_driver.task)) {
        bluetooth_driver.task();
    }
}

__attribute__((weak)) void bluetooth_send_keyboard(report_keyboard_t *report) {
    bluetooth_driver.send_keyboard(report);
}

#ifdef NKRO_ENABLE
__attribute__((weak)) void bluetooth_send_nkro(report_keyboard_t *report) {
    if (NULL != (*bluetooth_driver.send_nkro)) {
        bluetooth_driver.send_nkro(report);
    }
}
#endif

__attribute__((weak)) void bluetooth_send_mouse(report_mouse_t *report) {
    bluetooth_driver.send_mouse(report);
}

__attribute__((weak)) void bluetooth_send_consumer(uint16_t usage) {
    bluetooth_driver.send_consumer(usage);
}

__attribute__((weak)) void bluetooth_send_system(uint16_t usage) {
    if (NULL != (*bluetooth_driver.send_system)) {
        bluetooth_driver.send_system(usage);
    }
}
