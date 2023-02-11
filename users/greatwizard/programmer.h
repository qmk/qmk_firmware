/* Copyright 2020 Guillaume Gérard
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
#include "greatwizard.h"

bool process_record_pg(uint16_t keycode, keyrecord_t *record);

#define QWERTYP QWERTY_PROGRAMMER
#define WORKMNP WORKMAN_PROGRAMMER
#define COLEMKP COLEMAK_PROGRAMMER
#define DVORAKP DVORAK_PROGRAMMER
#ifdef TAP_DANCE_LSFT_CAPS
#    define PG_LSCP TD(TD_PG_LSFT_CAPS)
#else
#    define PG_LSCP LM(_PROGRAMMER_SHIFTED, MOD_LSFT)
#endif
