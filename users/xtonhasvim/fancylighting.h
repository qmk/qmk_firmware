/* Copyright 2015-2017 Christon DeWan
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

#ifndef _fancy_lighting_h
#define _fancy_lighting_h
#ifdef RGBLIGHT_ENABLE

#include "xtonhasvim.h"


extern uint8_t user_rgb_mode;
extern LED_TYPE shadowed_led[];


#endif //RGBLIGHT_ENABLE
void start_firey_return(void);

enum xtonhasvim_rgbmodes {
  BREATH_FIRE = 1,
  FADE_BACK
};

#endif //_fancy_lighting_h
