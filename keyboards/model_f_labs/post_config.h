/* Copyright 2020 Purdea Andrei
 * Copyright 2021 Matthew J Wolf
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

// This file should be included at the end of each keyboard-specific config.h

#pragma once

#ifndef MATRIX_CAPSENSE_ROWS
#    ifdef MATRIX_EXTRA_DIRECT_ROWS
#        define MATRIX_CAPSENSE_ROWS (MATRIX_ROWS - MATRIX_EXTRA_DIRECT_ROWS)
#        ifndef MATRIX_EXTRA_DIRECT_COLS
#            define MATRIX_EXTRA_DIRECT_COLS MATRIX_COLS
#        endif
#    else
#        define MATRIX_CAPSENSE_ROWS MATRIX_ROWS
#    endif
#endif

#ifndef CAPSENSE_CAL_INIT_REPS
#    define CAPSENSE_CAL_INIT_REPS 16
#endif
#ifndef CAPSENSE_CAL_EACHKEY_REPS
#    define CAPSENSE_CAL_EACHKEY_REPS 16
#endif

// Testing Options

#ifndef CAPSENSE_KEYBOARD_SETTLE_TIME_US
#    error "Please define CAPSENSE_KEYBOARD_SETTLE_TIME_US in config.h"
#endif
#ifndef CAPSENSE_DAC_SETTLE_TIME_US
#    error "Please define CAPSENSE_DAC_SETTLE_TIME_US in config.h"
#endif
#ifndef CAPSENSE_HARDCODED_SAMPLE_TIME
#    error "Please define CAPSENSE_HARDCODED_SAMPLE_TIME in config.h"
#endif

#ifndef CAPSENSE_CAL_ENABLED
#    error "Please define CAPSENSE_CAL_ENABLED as 1/0 in config.h"
#endif
#ifndef CAPSENSE_CAL_DEBUG
#    error "Please define CAPSENSE_CAL_DEBUG as 1/0 in config.h"
#endif
#ifndef CAPSENSE_CAL_BINS
#    error "Please define CAPSENSE_CAL_BINS in config.h"
#endif
#ifndef CAPSENSE_CAL_THRESHOLD_OFFSET
#    error "Please define CAPSENSE_CAL_THRESHOLD_OFFSET in config.h"
#endif
