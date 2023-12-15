#pragma once
/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

typedef struct {
  uint16_t layer;
  uint16_t index;  // 0 or 1, left/right.
  uint16_t clockwise;
  uint16_t counter_clockwise;
  uint16_t mods;
  void (*cw_func)(void);
  void (*ccw_func)(void);
} encoder_action_t;
extern encoder_action_t encoder_actions[];
extern uint8_t         NUM_ENCODER_ACTIONS;

// haven't looked at the real values for index, but I know
// 0 and 1 are left and right on my kyria.
#define LEFT 0
#define RIGHT 1
#define LAYER_NONE -1
#define MOD_NONE 0x00

#define ENCODER_ACTION(LAYER, INDEX, CW_KC, CCW_KC, MOD)        \
  {LAYER, INDEX, CW_KC, CCW_KC, MOD, NULL, NULL},

#define ENCODER_FUNCTION(LAYER, INDEX, CW_FUNC, CCW_FUNC, MOD)  \
  {LAYER, INDEX, 0, 0, MOD, CW_FUNC, CCW_FUNC},

bool do_encoder_action(uint8_t index, bool clockwise, bool layer_actions);
