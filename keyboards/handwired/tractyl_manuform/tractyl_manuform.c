/* Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
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

#include "tractyl_manuform.h"
#include "transactions.h"
#include <string.h>

#ifndef TRACKBALL_DPI_OPTIONS
#    define TRACKBALL_DPI_OPTIONS \
        { 1200, 1600, 2400 }
#    ifndef TRACKBALL_DPI_DEFAULT
#        define TRACKBALL_DPI_DEFAULT 1
#    endif
#endif
#ifndef TRACKBALL_DPI_DEFAULT
#    define TRACKBALL_DPI_DEFAULT 0
#endif

keyboard_config_t keyboard_config;
kb_config_data_t  kb_config_data;
uint16_t          dpi_array[] = TRACKBALL_DPI_OPTIONS;
#define DPI_OPTION_SIZE (sizeof(dpi_array) / sizeof(uint16_t))

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

#ifdef POINTING_DEVICE_ENABLE
    if (keycode == DPI_CONFIG && record->event.pressed) {
        if ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT) {
            keyboard_config.dpi_config = (keyboard_config.dpi_config - 1) % DPI_OPTION_SIZE;
        } else {
            keyboard_config.dpi_config = (keyboard_config.dpi_config + 1) % DPI_OPTION_SIZE;
        }
        eeconfig_update_kb(keyboard_config.raw);
        kb_config_data.device_cpi = dpi_array[keyboard_config.dpi_config];
        pointing_device_set_cpi(kb_config_data.device_cpi);
    }
#endif

/* If Mousekeys is disabled, then use handle the mouse button
 * keycodes.  This makes things simpler, and allows usage of
 * the keycodes in a consistent manner.  But only do this if
 * Mousekeys is not enable, so it's not handled twice.
 */
#ifndef MOUSEKEY_ENABLE
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        report_mouse_t currentReport = pointing_device_get_report();
        currentReport.buttons        = pointing_device_handle_buttons(currentReport.buttons, record->event.pressed, keycode - KC_MS_BTN1);
        pointing_device_set_report(currentReport);
        pointing_device_send();
    }
#endif

    return true;
}
__attribute__((weak)) void keyboard_pre_init_sub(void) {}
void                       keyboard_pre_init_kb(void) {
    // debug_enable  = true;
    // debug_matrix  = true;
    // debug_mouse   = true;
    // debug_encoder = true;

    // This is the debug LED.
#if defined(DEBUG_LED_PIN)
    setPinOutput(DEBUG_LED_PIN);
    writePin(DEBUG_LED_PIN, !debug_enable);
#endif

    memset(&kb_config_data, 0, sizeof(kb_config_data));

    keyboard_pre_init_sub();
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    transaction_register_rpc(RPC_ID_KB_CONFIG_SYNC, kb_config_sync_handler);

    keyboard_post_init_user();
}

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init_kb(void) {
    kb_config_data.device_cpi = dpi_array[keyboard_config.dpi_config];
    pointing_device_set_cpi(kb_config_data.device_cpi);
    pointing_device_init_user();
}

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    if (is_keyboard_master()) {
        mouse_report = pointing_device_task_user(mouse_report);
    }
    return mouse_report;
}
#endif

void eeconfig_init_kb(void) {
    keyboard_config.dpi_config = TRACKBALL_DPI_DEFAULT;
#ifdef POINTING_DEVICE_ENABLE
    kb_config_data.device_cpi = dpi_array[keyboard_config.dpi_config];
    pointing_device_set_cpi(kb_config_data.device_cpi);
#endif
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}

__attribute__((weak)) void matrix_init_sub_kb(void) {}
void                       matrix_init_kb(void) {
    // is safe to just read DPI setting since matrix init
    // comes before pointing device init.
    keyboard_config.raw = eeconfig_read_kb();
    if (keyboard_config.dpi_config > DPI_OPTION_SIZE) {
        eeconfig_init_kb();
    }
    matrix_init_sub_kb();
    matrix_init_user();
}

__attribute__((weak)) void matrix_scan_sub_kb(void) {}
void                       matrix_scan_kb(void) {
    matrix_scan_sub_kb();
    matrix_scan_user();
}

void housekeeping_task_kb(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static kb_config_data_t last_kb_config;
        static uint32_t         last_sync  = 0;
        bool                    needs_sync = false;

        // Check if the state values are different
        if (memcmp(&kb_config_data, &last_kb_config, sizeof(kb_config_data))) {
            needs_sync = true;
            memcpy(&last_kb_config, &kb_config_data, sizeof(kb_config_data));
        }
        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync) > 500) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_KB_CONFIG_SYNC, sizeof(kb_config_data), &kb_config_data)) {
                last_sync = timer_read32();
            }
        }
    }
    // no need for user function, is called already
}

void kb_config_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(kb_config_data)) {
        memcpy(&kb_config_data, initiator2target_buffer, sizeof(kb_config_data));
    }
}

#ifdef POINTING_DEVICE_ENABLE
void matrix_power_up(void) { pointing_device_task(); }
#endif
