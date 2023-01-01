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

#pragma once

#include <stdint.h>
#include "keyboard.h"
#include "action.h"

#ifdef DYNAMIC_KEYMAP_ENABLE
#    ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#        define DYNAMIC_KEYMAP_LAYER_COUNT 4
#    endif
#    define MAX_LAYER DYNAMIC_KEYMAP_LAYER_COUNT
#    if DYNAMIC_KEYMAP_LAYER_COUNT <= 8
#        ifndef LAYER_STATE_8BIT
#            define LAYER_STATE_8BIT
#        endif
#    elif DYNAMIC_KEYMAP_LAYER_COUNT <= 16
#        ifndef LAYER_STATE_16BIT
#            define LAYER_STATE_16BIT
#        endif
#    else
#        ifndef LAYER_STATE_32BIT
#            define LAYER_STATE_32BIT
#        endif
#    endif
#endif

#if !defined(LAYER_STATE_8BIT) && !defined(LAYER_STATE_16BIT) && !defined(LAYER_STATE_32BIT)
#    define LAYER_STATE_16BIT
#endif

#if defined(LAYER_STATE_8BIT)
typedef uint8_t layer_state_t;
#    define MAX_LAYER_BITS 3
#    ifndef MAX_LAYER
#        define MAX_LAYER 8
#    endif
#    define get_highest_layer(state) biton(state)
#elif defined(LAYER_STATE_16BIT)
typedef uint16_t layer_state_t;
#    define MAX_LAYER_BITS 4
#    ifndef MAX_LAYER
#        define MAX_LAYER 16
#    endif
#    define get_highest_layer(state) biton16(state)
#elif defined(LAYER_STATE_32BIT)
typedef uint32_t layer_state_t;
#    define MAX_LAYER_BITS 5
#    ifndef MAX_LAYER
#        define MAX_LAYER 32
#    endif
#    define get_highest_layer(state) biton32(state)
#else
#    error Layer Mask size not specified.  HOW?!
#endif

/*
 * Default Layer
 */
extern layer_state_t default_layer_state;
void                 default_layer_debug(void);
void                 default_layer_set(layer_state_t state);

__attribute__((weak)) layer_state_t default_layer_state_set_kb(layer_state_t state);
__attribute__((weak)) layer_state_t default_layer_state_set_user(layer_state_t state);

#ifndef NO_ACTION_LAYER
/* bitwise operation */
void default_layer_or(layer_state_t state);
void default_layer_and(layer_state_t state);
void default_layer_xor(layer_state_t state);
#else
#    define default_layer_or(state)
#    define default_layer_and(state)
#    define default_layer_xor(state)
#endif

/*
 * Keymap Layer
 */
#ifndef NO_ACTION_LAYER
extern layer_state_t layer_state;

void layer_state_set(layer_state_t state);
bool layer_state_is(uint8_t layer);
bool layer_state_cmp(layer_state_t layer1, uint8_t layer2);

void layer_debug(void);
void layer_clear(void);
void layer_move(uint8_t layer);
void layer_on(uint8_t layer);
void layer_off(uint8_t layer);
void layer_invert(uint8_t layer);
/* bitwise operation */
void          layer_or(layer_state_t state);
void          layer_and(layer_state_t state);
void          layer_xor(layer_state_t state);
layer_state_t layer_state_set_user(layer_state_t state);
layer_state_t layer_state_set_kb(layer_state_t state);
#else
#    define layer_state 0

#    define layer_state_set(layer)
#    define layer_state_is(layer) (layer == 0)
#    define layer_state_cmp(state, layer) (state == 0 ? layer == 0 : (state & (layer_state_t)1 << layer) != 0)

#    define layer_debug()
#    define layer_clear()
#    define layer_move(layer) (void)layer
#    define layer_on(layer) (void)layer
#    define layer_off(layer) (void)layer
#    define layer_invert(layer) (void)layer
#    define layer_or(state) (void)state
#    define layer_and(state) (void)state
#    define layer_xor(state) (void)state
#    define layer_state_set_kb(state) (void)state
#    define layer_state_set_user(state) (void)state
#endif

/* pressed actions cache */
#if !defined(NO_ACTION_LAYER) && !defined(STRICT_LAYER_RELEASE)

void    update_source_layers_cache(keypos_t key, uint8_t layer);
uint8_t read_source_layers_cache(keypos_t key);
#endif
action_t store_or_get_action(bool pressed, keypos_t key);

/* return the topmost non-transparent layer currently associated with key */
uint8_t layer_switch_get_layer(keypos_t key);

/* return action depending on current layer status */
action_t layer_switch_get_action(keypos_t key);
