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

/*
 * Pointing Device Config
 */

extern bool set_scrolling;

extern float scroll_acc_h;
extern float scroll_acc_v;
