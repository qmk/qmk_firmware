/*
Copyright 2025 Vincent Franco <me@vincentfranco.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CROSSES_CORE_H
#    define CROSSES_CORE_H

/*
 * Pointer Storage
 */
typedef union {
    uint32_t raw;
    struct {
        uint16_t mse_cpi : 16;
    } __attribute__((packed));
} global_user_config_t;

extern global_user_config_t global_user_config;

extern const uint16_t MIN_DEFAULT_DPI;
extern const uint16_t MAX_DEFAULT_DPI;

void write_config_to_eeprom(global_user_config_t* config);

uint16_t get_pointer_dpi(global_user_config_t* config);

void update_pointer_cpi(global_user_config_t* config);

void change_pointer_dpi(global_user_config_t* config, bool inc);

void debug_config_to_console(global_user_config_t* config);

void eeconfig_init_user(void);

void keyboard_post_init_user(void);

/*
 * Pointing Device Config
 */

extern bool set_scrolling;

extern float scroll_acc_h;
extern float scroll_acc_v;

#    if defined(POINTING_DEVICE_LEFT) || defined(POINTING_DEVICE_RIGHT)
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report);
#    endif // POINTING_DEVICE
           //
#    ifdef POINTING_DEVICE_COMBINED
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report);
#    endif // POINTINTG_DEVICE_COMBINED

layer_state_t layer_state_set_user(layer_state_t state);

#endif // CROSSES_CORE_H

#ifdef __cplusplus
}
#endif
