/* Copyright 2019
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

#include "quantum.h"
#include "fonts/gfxfont.h"

#if defined(KEYBOARD_polykb_4x2)
#    include "4x2.h"
#elif defined(KEYBOARD_polykb_4x5)
#    include "4x5.h"
##elif defined(KEYBOARD_polykb_wave)
#    include "wave.h"
#endif

#define FULL_BRIGHT 49
#define FADE_TRANSITION_TIME 5000
#define FADE_OUT_TIME 60000

enum diplay_state {
    DISPLAYS_ON,
    DISPLAYS_ON_SET_CONTRAST,
    DISPLAYS_SET_CONTRAST,
    DISPLAYS_OFF
};

void select_all_displays(void);

void inc_brightness(void);

void dec_brightness(void);

void set_displays(enum diplay_state state, uint8_t contrast);

void request_disp_refresh(void);

bool display_wakeup(keyrecord_t* record);

void show_splash_screen(void);

void clear_all_displays(void);

void update_displays(void);

void set_displays_on(bool on);

bool displays_on(void);

void set_last_key(uint16_t keycode);
