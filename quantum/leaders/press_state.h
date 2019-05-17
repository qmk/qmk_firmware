/* Copyright 2017 Alex Olkhovskiy
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
#ifndef PRESS_STATE_H
#define PRESS_STATE_H


#define LD_PRESS_MAX 16
#include "keyboard.h"

#include "keycode.h"
#include "util.h"

typedef struct {
  keypos_t key;
  uint16_t keycode;
  bool ignore;
  uint16_t sentinels;
  uint8_t pos;
} press_t;

void init_press_state(void);
uint16_t press_state_get(void);
uint8_t find_press(keypos_t key);
bool press_state_remove_by_idx(uint8_t idx);
void press_state_put(press_t press);
press_t press_state_get_press(uint8_t idx);
press_t* presses_get(void);

#endif
