/** @file oled.h
 *  @brief oled header that includes function prototypes and external variables.
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
 *
 * @author Mario Corona (mariocc@comunidad.unam.mx) 2021
 *
 */
#pragma once

#include <stdio.h>
#include "mcrown.h"

#ifdef OLED_VERTICAL
#define KEYLOG_LEN (48)
#else
#define KEYLOG_LEN (19)
#endif

#define KEYLOG_EOL_LEN (KEYLOG_LEN+1)

extern void add_keylog(uint16_t keycode);
extern void update_log(void);
