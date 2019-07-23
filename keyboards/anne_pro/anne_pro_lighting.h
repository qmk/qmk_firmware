/* Copyright 2019 Michiel Visser
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

#define APL_MODE_OFF 0
#define APL_MODE_RED 1
#define APL_MODE_YELLOW 2
#define APL_MODE_GREEN 3
#define APL_MODE_CYAN 4
#define APL_MODE_BLUE 5
#define APL_MODE_PURPLE 6
#define APL_MODE_PINK 7
#define APL_MODE_ORANGE 8
#define APL_MODE_WHITE 9
#define APL_MODE_FLAG_FANCE 10
#define APL_MODE_FLAG_ITALY 11
#define APL_MODE_FLAG_ARGENTINA 12
#define APL_MODE_BREATHING 13
#define APL_MODE_RAINBOW 14
#define APL_MODE_REACTIVE_FADE 15
#define APL_MODE_REACTIVE_HOLD 16
#define APL_MODE_REACTIVE_LINE 17
#define APL_MODE_RANDOM 18
#define APL_MODE_CUSTOM 128

void anne_pro_lighting_init(void);
void anne_pro_lighting_update(void);
void anne_pro_lighting_update_dynamic(keyrecord_t *record);
void anne_pro_lighting_update_timeout(keyrecord_t *record);
void anne_pro_lighting_toggle(void);
void anne_pro_lighting_on(void);
void anne_pro_lighting_off(void);
bool anne_pro_lighting_enabled(void);
void anne_pro_lighting_rate_next(void);
void anne_pro_lighting_brightness_next(void);
void anne_pro_lighting_mode_next(void);
void anne_pro_lighting_mode(uint8_t mode);
void anne_pro_lighting_mode_last(void);
void anne_pro_lighting_rate_brightness(uint8_t speed, uint8_t brightness);
void anne_pro_lighting_set_keys(uint8_t keys, uint8_t *payload);
