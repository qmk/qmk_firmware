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

#ifndef USERSPACE
#define USERSPACE

#include QMK_KEYBOARD_H

enum xtonhasvim_keycodes {
  VIM_START = SAFE_RANGE,  // bookend for vim states
  VIM_A,
  VIM_B,
  VIM_C,
  VIM_CI,
  VIM_D,
  VIM_DI,
  VIM_E,
  VIM_H,
  VIM_G,
  VIM_I,
  VIM_J,
  VIM_K,
  VIM_L,
  VIM_O,
  VIM_P,
  VIM_S,
  VIM_U,
  VIM_V,
  VIM_VS, // visual-line
  VIM_VI,
  VIM_W,
  VIM_X,
  VIM_Y,
  VIM_PERIOD, // to support indent/outdent
  VIM_COMMA,  // and toggle comments
  VIM_SHIFT, // avoid side-effect of supporting real shift.
  VIM_ESC, // bookend
  VIM_SAFE_RANGE // start other keycodes here.
};

bool process_record_vimlayer(uint16_t keycode, keyrecord_t *record);

// NOTE: Define this in keymap.c to return vim layer
extern uint8_t vim_cmd_layer(void);

extern uint16_t vstate;


#endif
