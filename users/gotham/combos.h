/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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
#include "progmem.h"
#include "process_records.h"

enum combos {
    CMB_GRV,
    CMB_ESC,
    CMB_TAB,
    CMB_GUI,
    CMB_UNDO,
    CMB_REDO,
    CMB_BSLS,
    CMB_QUOT,
    CMB_EQL,
    CMB_MINS,
    CMB_UNDS,
};
