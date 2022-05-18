/* Copyright 2021 Joshua T.
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
#include QMK_KEYBOARD_H
#include "rj_keycodes.h"

#ifndef USER_SUPER_ALT_TAB_TIMEOUT
#    define USER_SUPER_ALT_TAB_TIMEOUT 500
#endif

void matrix_scan_super_alt_tab(void);

bool process_record_super_alt_tab(uint16_t keycode, const keyrecord_t *record);
