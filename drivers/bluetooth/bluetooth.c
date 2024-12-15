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
#elif defined(BLUETOOTH_BHQ)
#   include "action.h"
#   include "report.h"
#   include "bluetooth_bhq.h"
#endif

void bluetooth_init(void) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_init();
#elif defined(BLUETOOTH_RN42)
    rn42_init();
#elif defined(BLUETOOTH_BHQ)
    bluetooth_bhq_init();
#endif
}

void bluetooth_task(void) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_task();
#elif defined(BLUETOOTH_BHQ)
    bluetooth_bhq_task();
#endif
}

void bluetooth_send_keyboard(report_keyboard_t *report) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_send_keyboard(report);
#elif defined(BLUETOOTH_RN42)
    rn42_send_keyboard(report);
#elif defined(BLUETOOTH_BHQ)
    bluetooth_bhq_send_keyboard(report);
#endif
}

void bluetooth_send_mouse(report_mouse_t *report) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_send_mouse(report);
#elif defined(BLUETOOTH_RN42)
    rn42_send_mouse(report);
#elif defined(BLUETOOTH_BHQ)
    bluetooth_bhq_send_mouse(report);
#endif
}

void bluetooth_send_consumer(uint16_t usage) {
#if defined(BLUETOOTH_BLUEFRUIT_LE)
    bluefruit_le_send_consumer(usage);
#elif defined(BLUETOOTH_RN42)
    rn42_send_consumer(usage);
#elif defined(BLUETOOTH_BHQ)
    bluetooth_bhq_send_consumer(usage);
#endif
}


void bluetooth_send_system(uint16_t usage)
{
#if defined(BLUETOOTH_BHQ)
    bluetooth_bhq_send_system(usage);
#endif
}

void bluetooth_send_nkro(report_nkro_t *report) {
#if defined(BLUETOOTH_BHQ)
    bluetooth_bhq_send_nkro(report);
#endif
}

void bluetooth_send_hid_raw(uint8_t *data, uint8_t length) {
#if defined(BLUETOOTH_BHQ)
    bluetooth_bhq_send_hid_raw(data, length);
#endif
}

void bluetooth_set_keyboard_leds(uint8_t led_sta) {
#if defined(BLUETOOTH_BHQ)
    bluetooth_bhq_set_keyboard_leds(led_sta);
#endif
}
uint8_t bluetooth_get_keyboard_leds(void) {
#if defined(BLUETOOTH_BHQ)
    return bluetooth_bhq_get_keyboard_leds();
#endif
}
