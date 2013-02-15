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
#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include <stdint.h>
#include "action.h"


/*
 * Layer stack
 */
#define LAYER_STACK_SIZE 8
typedef struct {
    uint8_t layer:4;
    uint8_t next:3;
    bool    used;
} layer_item_t;


void layer_stack_clear(void);
bool layer_stack_push(uint8_t layer);
bool layer_stack_pop(void);
bool layer_stack_remove(uint8_t layer);
bool layer_stack_remove_then_push(uint8_t layer);
bool layer_stack_remove_or_push(uint8_t layer);
void layer_stack_debug(void);
action_t layer_stack_get_action(key_t key);

#endif

