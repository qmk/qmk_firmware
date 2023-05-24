/* Copyright 2017  Christopher Browne
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

#ifndef NO_DEBUG
#define NO_DEBUG
#endif
#ifndef NO_PRINT
#define NO_PRINT
#endif

#include "../../config.h"

#define LEADER_TIMEOUT 300

#ifndef KEYBOARD_planck_light
#define BACKLIGHT_BREATHING
#endif

/* cbbrowne user configuration */

#define randadd 53
#define randmul 181
#define randmod 167

/* Filler to make layering a bit clearer *
 * borrowed from basic keymap            */

#define _____   KC_NO
