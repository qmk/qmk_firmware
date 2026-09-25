/* Copyright (C) 2022 jonylee@hfd
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

#ifndef BLED_H
#define BLED_H

#include "quantum.h"

#define BLED_MAX_BRIGHTNESS 100
#define BLED_BRIGHTNESS_STEP 25

typedef enum {
    BLED_MODE_FLOW,
    BLED_MODE_BREATHING,
    BLED_MODE_SOLID,
    BLED_MODE_OFF,
    BLED_MODE_COUNT,
    BLED_MODE_CYCLE,
    BLED_MODE_CYCLE1,
} bled_mode_t;

typedef enum {
    COLOR_RAINBOW,
    COLOR_RED,
    COLOR_ORIANGE,
    COLOR_YELLOW,
    COLOR_GREEN,
    COLOR_CYAN,
    COLOR_BLUE,
    COLOR_PURPLE,
    COLOR_WHITE,
    COLOR_COUNT,
} bled_color_preset_t;

void bled_task(void);
void bled_init(void);
void bled_eeconfig_init(void);
void bled_charging_indicate(void);
void bled_charged_indicate(void);

#endif // BLED_H
