/* Copyright 2022 Julian Turner
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

#pragma once

#ifdef OLED_ENABLE
bool            process_record_oled(uint16_t keycode, keyrecord_t *record);
oled_rotation_t oled_init_user(oled_rotation_t rotation);
void            render_layer_symbol(void);
void            render_layer_name(void);
void            render_mod_state(uint8_t modifiers);
void            render_status(void);
bool            oled_task_user(void);
#endif