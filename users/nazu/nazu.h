/* Copyright 2023 Tom Sennewald (@beelzebubi)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

/* Define layer names */
enum userspace_layers {
    _QWERTY = 0,    // QWERTY layout for WIN or UNIX
    _COLEMAK,       // Colemak lazout
    _COLEMAK_DH,    // Colemak DHS layout
    _FN1,           //
    _FN2,           //
    _MEDIA,         //
    _LOWER,         //
    _RAISE,         //
    _ADJUST,        //
};


/* Tap Dance definitions */
#ifdef TAP_DANCE_ENABLE
#   include "keyrecords/tap_dances.h"
#   include "keyrecords/tap_dances.c"
#endif

#ifdef OLED_ENABLE
/* status variables */
#    include "oled/oled_rocket.c"
#    include "oled/oled_luna.c"
// #    include "oled/oled_status.c"
#endif

#include "keyrecords/wrappers.h"
#include "keyrecords/process_records.h"
#include "keyrecords/process_records.c"
