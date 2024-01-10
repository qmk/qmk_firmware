/* Copyright 2022 @ Keychron (https://www.keychron.com)
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

#include "stdint.h"
#include "action.h"

#ifdef LEMOKEY_CALLBACK_ENABLE
typedef bool (*keychron_cb)(void);
typedef bool (*keychron_record_process_cb)(uint16_t keycode, keyrecord_t *record);


bool process_record_keychron(uint16_t keycode, keyrecord_t *record);

void register_keychron_task(keychron_cb cb, bool priority);
void register_record_process(keychron_record_process_cb cb, bool priority);
#if defined(LED_MATRIX_ENABLE) ||  defined(RGB_MATRIX_ENABLE)
void register_led_indicator_task(keychron_cb cb, bool priority);
#endif

#else
bool keychron_task_kb(void);
bool process_record_keychron_kb(uint16_t keycode, keyrecord_t *record);

#endif
void keychron_task(void);

