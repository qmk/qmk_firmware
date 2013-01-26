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
    uint8_t col;
    uint8_t row;
} keypos_t;

typedef union {
    uint16_t raw;
    keypos_t pos;
} key_t;

typedef struct {
    key_t    key;
    bool     pressed;
    uint16_t time;
} keyevent_t;

#define KEYEQ(keya, keyb)       ((keya).raw == (keyb).raw)
#define IS_NOEVENT(event)       ((event).key.pos.row == 255 && (event).key.pos.col == 255)
#define NOEVENT                 (keyevent_t){           \
    .key.pos = (keypos_t){ .row = 255, .col = 255 },    \
    .pressed = false,                                   \
    .time = 0                                           \
}
#define TICK                    (keyevent_t){           \
    .key.pos = (keypos_t){ .row = 255, .col = 255 },    \
    .pressed = false,                                   \
    .time = timer_read()                                \
}


extern uint8_t current_layer;
extern uint8_t default_layer;

void keyboard_init(void);
void keyboard_task(void);
void keyboard_set_leds(uint8_t leds);

#ifdef __cplusplus
}
#endif

#endif
