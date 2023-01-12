/* Copyright 2022 @ lokher (https://www.keychron.com)
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

/******************************************************************************
 *
 *  Filename:      lpm.c
 *
 *  Description:   Contains low power mode implementation
 *
 ******************************************************************************/

#include "quantum.h"
#if defined(PROTOCOL_CHIBIOS)
#    include <usb_main.h>
#endif
#include "bluetooth.h"
#include "indicator.h"
#include "lpm.h"
#include "transport.h"
#include "battery.h"

extern matrix_row_t          matrix[MATRIX_ROWS];
extern bluetooth_transport_t bluetooth_transport;

static uint32_t     lpm_timer_buffer;
static bool         lpm_time_up               = false;
static matrix_row_t empty_matrix[MATRIX_ROWS] = {0};

void lpm_init(void) {
#ifdef USB_POWER_SENSE_PIN
#    if (USB_POWER_CONNECTED_LEVEL == 0)
    setPinInputHigh(USB_POWER_SENSE_PIN);
#    else
    setPinInputLow(USB_POWER_SENSE_PIN);
#    endif
#endif
    lpm_timer_reset();
}

inline void lpm_timer_reset(void) {
    lpm_time_up      = false;
    lpm_timer_buffer = sync_timer_read32();
}

void lpm_timer_stop(void) {
    lpm_time_up      = false;
    lpm_timer_buffer = 0;
}

static inline bool lpm_any_matrix_action(void) { return memcmp(matrix, empty_matrix, sizeof(empty_matrix)); }

/* Implement of entering low power mode and wakeup varies per mcu or platform */
__attribute__((weak)) void enter_power_mode(pm_t mode) {}

__attribute__((weak)) bool usb_power_connected(void) {
#ifdef USB_POWER_SENSE_PIN
    return readPin(USB_POWER_SENSE_PIN) == USB_POWER_CONNECTED_LEVEL;
#endif

    return true;
}

void lpm_task(void) {
    if (!lpm_time_up && sync_timer_elapsed32(lpm_timer_buffer) > RUN_MODE_PROCESS_TIME) {
        lpm_time_up      = true;
        lpm_timer_buffer = 0;
    }

    if (get_transport() == TRANSPORT_BLUETOOTH && lpm_time_up && !indicator_is_running()
#ifdef LED_MATRIX_ENABLE
        && led_matrix_is_driver_shutdown()
#endif
#ifdef RGB_MATRIX_ENABLE
        && rgb_matrix_is_driver_shutdown()
#endif
        && !lpm_any_matrix_action() && !battery_power_on_sample())

        enter_power_mode(LOW_POWER_MODE);
}
