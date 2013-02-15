/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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
#ifndef LAYER_SWITCH_H
#define LAYER_SWITCH_H

#include <stdint.h>
#include "keyboard.h"
#include "action.h"


/* base layer to fall back */
extern uint8_t default_layer;

/* layer status */
extern uint16_t layer_switch_stat;

/* return layer status */
uint16_t layer_switch_get_stat(void);
/* return current active layer */
uint8_t layer_switch_get_layer(void);

/* switch off all layers */
void layer_switch_clear(void);
/* set layer status */
void layer_switch_set(uint16_t stat);
/* move to layer */
void layer_switch_move(uint8_t layer);
/* switch on layer */
void layer_switch_on(uint8_t layer);
/* switch off layer */
void layer_switch_off(uint8_t layer);
/* switch state of layer */
void layer_switch_invert(uint8_t layer);

/* bitwise operation against layer status */
void layer_switch_or(uint16_t stat);
void layer_switch_and(uint16_t stat);
void layer_switch_xor(uint16_t stat);

void layer_switch_debug(void);

/* return action depending on current layer status */
action_t layer_switch_get_action(key_t key);

#endif
