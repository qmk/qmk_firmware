/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "analog_matrix.h"
#include "action.h"

void profile_init(bool reset);
analog_matrix_profile_t *profile_get(uint8_t index);
analog_matrix_profile_t* profile_get_current(void);
uint8_t profile_get_current_index(void);
bool profile_select(uint8_t prof_idx, bool indication);
bool profile_get_raw_data(uint8_t prof_idx, uint16_t offset, uint8_t size, uint8_t *data);
bool profile_set_traval(uint8_t prof_idx, uint8_t mode, uint8_t act_pt, uint8_t sens, uint8_t rls_sens, bool global, uint32_t row[]);
bool profile_set_name(uint8_t prof_idx, uint8_t len, uint8_t *name);
bool profile_set_socd(uint8_t *data);
bool profile_reset(uint8_t prof_index);
bool profile_save(uint8_t prof_index);
bool profile_set_adv_mode(uint8_t *data);
void process_profile_select_combo(void);
bool process_record_profile(uint16_t keycode, keyrecord_t *record);

void profile_indication_enable(void);
void profile_indication_timer_check(void);
void profile_indication(void);
