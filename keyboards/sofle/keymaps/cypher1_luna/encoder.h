 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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

//Setting up what encoder rotation does. If your encoder can be pressed as a button, that function can be set in Via.
#ifndef CYPHER1_ENCODER_H_
#define CYPHER1_ENCODER_H_

#include QMK_KEYBOARD_H
#ifdef ENCODER_ENABLE

#include "state.h"

#define BOOL_SIZE 2
#define NUM_ENCODERS 2

const uint16_t encoder_table[NUM_ENCODERS][BOOL_SIZE][BOOL_SIZE] = {
  /*left  (index==0)*/ {
    /*unshifted*/{ /* counter-clockwise */  KC_VOLD, /* clockwise */ KC_VOLU  },
    /*  shifted*/{ /* counter-clockwise */ KC_MNXT,  /* clockwise */ KC_MPRV  }
  },
  /*right (index==1)*/ {
    /*unshifted*/{ /* counter-clockwise */ KC_UP,    /* clockwise */ KC_DOWN  },
    /*  shifted*/{ /* counter-clockwise */ KC_LEFT,  /* clockwise */ KC_RIGHT }
  }
};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index < NUM_ENCODERS) {
    tap_code(encoder_table[index][shift_held][clockwise]);
  }
  return true;
}

#endif
#endif // CYPHER1_ENCODER_H_
