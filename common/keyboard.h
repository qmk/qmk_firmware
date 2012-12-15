/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t row;
    uint8_t col;
} keypos_t;

typedef struct {
    keypos_t key;
    bool     pressed;
} keyevent_t;

typedef struct {
    keyevent_t  event;
    uint8_t     code;
    uint8_t     mods;
    uint16_t    time;
} keyrecord_t;

#define KEYEQ(keya, keyb)     (keya.row == keyb.row && keya.col == keyb.col)

extern uint8_t current_layer;
extern uint8_t default_layer;

void keyboard_init(void);
void keyboard_task(void);
void keyboard_set_leds(uint8_t leds);

#ifdef __cplusplus
}
#endif

#endif
