/* Copyright 2019 Drashna Jael're (@drashna)
 * Copyright 2019 Sunjun Kim
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

#include <math.h>
#include "quantum.h"
#include <stdint.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <string.h>
#include <print.h>
#include <stdio.h>
#include "spi_master.h"
#include "pmw3600.h"
#include "analog.h"
#include "pointing_device.h"

// Sensor defs
#define OPT_ENC1 F0
#define OPT_ENC2 F4
#define OPT_ENC1_MUX 0
#define OPT_ENC2_MUX 4



#define LAYOUT(BL, BM, BR, B4, B5) \
    { {BL, BM, BR, B4, B5}, }
