/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

// ======== DEPRECATED DEFINES - DO NOT USE ========
#ifdef BOOTMAGIC_LITE_ROW
#    define BOOTMAGIC_ROW BOOTMAGIC_LITE_ROW
#endif
#ifdef BOOTMAGIC_LITE_COLUMN
#    define BOOTMAGIC_COLUMN BOOTMAGIC_LITE_COLUMN
#endif
#ifdef BOOTMAGIC_LITE_ROW_RIGHT
#    define BOOTMAGIC_ROW_RIGHT BOOTMAGIC_LITE_ROW_RIGHT
#endif
#ifdef BOOTMAGIC_LITE_COLUMN_RIGHT
#    define BOOTMAGIC_COLUMN_RIGHT BOOTMAGIC_LITE_COLUMN_RIGHT
#endif
// ========

#ifndef BOOTMAGIC_COLUMN
#    define BOOTMAGIC_COLUMN 0
#endif
#ifndef BOOTMAGIC_ROW
#    define BOOTMAGIC_ROW 0
#endif

void bootmagic(void);
