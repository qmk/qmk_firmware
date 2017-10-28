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

#ifndef KEYBOARDS_ERGODOX_INFINITY_ANIMATIONS_H_
#define KEYBOARDS_ERGODOX_INFINITY_ANIMATIONS_H_

#include "visualizer.h"

// You can use these default animations, but of course you can also write your own custom ones instead
extern keyframe_animation_t default_startup_animation;
extern keyframe_animation_t default_suspend_animation;

// An animation for testing and demonstrating the led support, should probably not be used for real world
// cases
extern keyframe_animation_t led_test_animation;

#endif /* KEYBOARDS_ERGODOX_INFINITY_ANIMATIONS_H_ */
