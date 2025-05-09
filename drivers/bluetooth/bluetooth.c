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

#include "bluetooth.h"

#if defined(BLUETOOTH_BLUEFRUIT_LE)
#    include "bluefruit_le.h"
#elif defined(BLUETOOTH_RN42)
#    include "rn42.h"
#endif

void bluetooth_init(void) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_init();
#elif defined(BLUETOOTH_RN42)
    rn42_init();
#endif
}

void bluetooth_task(void) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_task();
#endif
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_send_keyboard(report);
#elif defined(BLUETOOTH_RN42)
    rn42_send_keyboard(report);
#endif
}

void bluetooth_send_mouse(report_mouse_t *report) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_send_mouse(report);
#elif defined(BLUETOOTH_RN42)
    rn42_send_mouse(report);
#endif
}

void bluetooth_send_consumer(uint16_t usage) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_send_consumer(usage);
#elif defined(BLUETOOTH_RN42)
    rn42_send_consumer(usage);
#endif
}
