/* Copyright 2018 Jack Humbert <jack.humb@gmail.com>
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

#include "qwiic.h"

enum {
  JOYSTIIC_LEFT,
  JOYSTIIC_RIGHT,
  JOYSTIIC_UP,
  JOYSTIIC_DOWN,
  JOYSTIIC_PRESS
};

void joystiic_update_kb(uint16_t horizontal, uint16_t vertical, bool button);
void joystiic_update_user(uint16_t horizontal, uint16_t vertical, bool button);
void joystiic_trigger_kb(uint8_t trigger, bool active);
void joystiic_trigger_user(uint8_t trigger, bool active);

void joystiic_init(void);
void joystiic_task(void);
