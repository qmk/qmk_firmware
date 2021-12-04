/*
 * Copyright 2020 Richard Sutherland (rich@brickbots.com)
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

#define MAX_WPM_INIT 40
#define BURST_FENETRE 500

#ifndef BURST_RECORD_TIME
#    define BURST_RECORD_TIME 1000
#endif

#define LIMIT_MAX_WPM 150

#ifndef WPM_ESTIMATED_WORD_SIZE
#    define WPM_ESTIMATED_WORD_SIZE 5
#endif
#ifndef WPM_SMOOTHING
#    define WPM_SMOOTHING 0.0487
#endif

#define SIZE_SCOPE 26
#define SCOPE_Y_BOTTOM 127

void update_scope(uint16_t keycode);
void render_scope(gui_state_t t);

void reset_scope(void);
void decay_scope(void);
