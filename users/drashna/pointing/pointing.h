/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "drashna.h"

report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report);
void           matrix_scan_pointing(void);
bool           process_record_pointing(uint16_t keycode, keyrecord_t* record);
layer_state_t  layer_state_set_pointing(layer_state_t state);
extern bool    tap_toggling, enable_acceleration;
