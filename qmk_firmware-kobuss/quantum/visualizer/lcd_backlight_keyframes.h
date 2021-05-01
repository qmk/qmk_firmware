/* Copyright 2017 Fred Sundvik
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

#include "visualizer.h"

// Animates the LCD backlight color between the current color and the target color (of the state)
bool lcd_backlight_keyframe_animate_color(keyframe_animation_t* animation, visualizer_state_t* state);
// Sets the backlight color to the target color
bool lcd_backlight_keyframe_set_color(keyframe_animation_t* animation, visualizer_state_t* state);

bool lcd_backlight_keyframe_disable(keyframe_animation_t* animation, visualizer_state_t* state);
bool lcd_backlight_keyframe_enable(keyframe_animation_t* animation, visualizer_state_t* state);
