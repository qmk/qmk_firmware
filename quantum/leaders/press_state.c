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
#include "leaders/press_state.h"

uint16_t press_state;
press_t presses[LD_PRESS_MAX];
press_t* presses_get() {
  return presses;
}

void init_press_state(void) {
  press_state = 0UL;
}

uint16_t press_state_get(void) {
  return press_state;
}

void press_state_put(press_t press) {
  for (int8_t i = 0; i < LD_PRESS_MAX; i ++) {
    if (press_state & (1U << i)) {
      continue;
    }
    press_state |= (1U << i);
    presses[i] = press;
    return;
  }
  return;
}

uint8_t find_press(keypos_t key) {
  if (press_state == 0) {return LD_PRESS_MAX;}
  uint8_t l = biton16(press_state);
  for (int8_t i = 0; i <= l; i++) {
    if (press_state & (1U << i)) {
      if (KEYEQ(presses[i].key, key)) {
        return i;
      }
    }
  }
  return LD_PRESS_MAX;
}

press_t press_state_get_press(uint8_t idx) {
  return presses[idx];
}
bool press_state_remove_by_idx(uint8_t idx) {
  if (idx == LD_PRESS_MAX) {return false;}
  press_state &= ~(1U << idx);
  return true;
}
