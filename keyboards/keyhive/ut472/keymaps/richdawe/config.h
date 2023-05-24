/* Copyright 2018 Carlos Filoteo
 * Copyright 2021-2023 Richard Dawe
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

#include "config_common.h"
#include <stdio.h>

// place overrides here

// Purple
#define RGBLIGHT_DEFAULT_HUE 	MIN(240, UINT8_MAX)
#define RGBLIGHT_DEFAULT_SAT 	MIN(215, UINT8_MAX)
#define RGBLIGHT_DEFAULT_VAL 	MIN(95, RGBLIGHT_LIMIT_VAL)

// Note: reddish purple: H: 248 S: 215 V: 95
