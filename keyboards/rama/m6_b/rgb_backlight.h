/* Copyright 2018 Jason Williams (Wilba)
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

#if RGB_BACKLIGHT_ENABLED
#else
#error rgb_backlight.h included when RGB_BACKLIGHT_ENABLED == 0
#endif // RGB_BACKLIGHT_ENABLED

#include <stdint.h>
#include <stdbool.h>

#include "quantum/color.h"

void backlight_init_drivers(void);
void backlight_update_pwm_buffers(void);
void backlight_timer_init(void);
void backlight_timer_enable(void);
void backlight_timer_disable(void);
void backlight_set_suspend_state(bool state);

