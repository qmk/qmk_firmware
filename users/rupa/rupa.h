/*
Copyright 2020 rupa <rupa@lrrr.us> @rupa

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include QMK_KEYBOARD_H
#include "version.h"
#include "process_records.h"
#include "unicode.h"
#include "wrappers.h"

enum userspace_layers {
    _QWERTY = 0,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE,
    BUGS,
    CATS,
    DANCE,
    DICE,
    DOMO,
    FART,
    FLIP,
    HUGS,
    JOY,
    KISS,
    LOD,
    MUSIC,
    RNDM,
    RUPA,
    SHRUG,
    TADA,
    U_FRACT,
    U_ITALI,
    U_MONOS,
    U_NORML,
    U_SANSI,
    U_SANSN,
    U_SCRPT,
    WAT,
    YUNO,
    ZALGO,
    ZZZZZ,
    NEXT_SAFE_RANGE
};

enum userspace_font_choices {
    F_FRACT = 0,
    F_ITALI,
    F_MONOS,
    F_NORML,
    F_SANSI,
    F_SANSN,
    F_SCRPT
};

typedef struct font_t {
    uint32_t upper_alpha;
    uint32_t lower_alpha;
    uint32_t zero_glyph;
} font_t;

const font_t* get_script_mode(void);
bool set_script_mode(int fc);
bool script_mode_translate(bool is_shifted, uint32_t keycode);
