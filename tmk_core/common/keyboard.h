/*
Copyright 2011,2012,2013 Jun Wako <wakojun@gmail.com>

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

/* key matrix position */
typedef struct {
    uint8_t col;
    uint8_t row;
} keypos_t;

/* key event */
typedef struct {
    keypos_t key;
    bool     pressed;
    uint16_t time;
} keyevent_t;

/* equivalent test of keypos_t */
#define KEYEQ(keya, keyb) ((keya).row == (keyb).row && (keya).col == (keyb).col)

/* Rules for No Event:
 * 1) (time == 0) to handle (keyevent_t){} as empty event
 * 2) Matrix(255, 255) to make TICK event available
 */
static inline bool IS_NOEVENT(keyevent_t event) { return event.time == 0 || (event.key.row == 255 && event.key.col == 255); }
static inline bool IS_PRESSED(keyevent_t event) { return (!IS_NOEVENT(event) && event.pressed); }
static inline bool IS_RELEASED(keyevent_t event) { return (!IS_NOEVENT(event) && !event.pressed); }

/* Tick event */
#define TICK \
    (keyevent_t) { .key = (keypos_t){.row = 255, .col = 255}, .pressed = false, .time = (timer_read() | 1) }

/* it runs once at early stage of startup before keyboard_init. */
void keyboard_setup(void);
/* it runs once after initializing host side protocol, debug and MCU peripherals. */
void keyboard_init(void);
/* it runs repeatedly in main loop */
void keyboard_task(void);
/* it runs when host LED status is updated */
void keyboard_set_leds(uint8_t leds);
/* it runs whenever code has to behave differently on a slave */
bool is_keyboard_master(void);

void keyboard_pre_init_kb(void);
void keyboard_pre_init_user(void);
void keyboard_post_init_kb(void);
void keyboard_post_init_user(void);

#ifdef __cplusplus
}
#endif

#endif
