/*
  Copyright 2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
#ifdef ENCODER_ENABLE
#include "encoders.h"
#include USERSPACE_H

encoder_action_t encoder_actions[] = {
#include "encoders.def"
};
uint8_t  NUM_ENCODER_ACTIONS = sizeof(encoder_actions) / sizeof(encoder_action_t);


bool encoder_update_user(uint8_t index, bool clockwise) {
  // do it twice, once for layer actions, once for non layer specific actions.
  if (!do_encoder_action(index, clockwise, true)){
    do_encoder_action(index, clockwise, false);
  }
  return false;
}

bool do_encoder_action(uint8_t index, bool clockwise, bool layer_actions) {
  uint8_t mods = get_mods();
  encoder_action_t *action;

  // look for a match.
  // on the layer, not on any layer.
  // with the mods, or no mods.
  for (int i = 0; i < NUM_ENCODER_ACTIONS; ++i) {
    action = &encoder_actions[i];

    // this encoder, or another.
    if (action->index != index)
              continue;

    // skip non layer specific actions and visa versa
    // two pass system, once for layers, again for
    // actions without layers.
    if (layer_actions){
      if (action->layer == LAYER_NONE ||
          action->layer != biton32(layer_state)){
        continue;
      }
    }else if (action->layer != LAYER_NONE)
      continue;

    // no mods, or these mods.
    if ((mods && (action->mods == MOD_NONE)) ||
        (mods && (mods != action->mods)))
    continue;

    // found one.
    if (clockwise) {
      if (action->clockwise != 0) {
        tap_code16(action->clockwise);
      } else if (action->cw_func != NULL) {
        action->cw_func();
      }
    } else {
      if (action->counter_clockwise != 0) {
        tap_code16(action->counter_clockwise);
      } else if (action->ccw_func != NULL) {
        action->ccw_func();
      }
    }
  }
  return false;
}

#endif
