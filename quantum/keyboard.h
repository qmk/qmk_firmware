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

#pragma once

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

/* special keypos_t entries */
#define KEYLOC_TICK 255
#define KEYLOC_COMBO 254
#define KEYLOC_ENCODER_CW 253
#define KEYLOC_ENCODER_CCW 252

/* Rules for No Event:
 * 1) (time == 0) to handle (keyevent_t){} as empty event
 * 2) Matrix(255, 255) to make TICK event available
 */
static inline bool IS_NOEVENT(keyevent_t event) {
    return event.time == 0 || (event.key.row == KEYLOC_TICK && event.key.col == KEYLOC_TICK);
}
static inline bool IS_KEYEVENT(keyevent_t event) {
    return event.key.row < MATRIX_ROWS && event.key.col < MATRIX_COLS;
}
static inline bool IS_COMBOEVENT(keyevent_t event) {
    return event.key.row == KEYLOC_COMBO;
}
static inline bool IS_ENCODEREVENT(keyevent_t event) {
    return event.key.row == KEYLOC_ENCODER_CW || event.key.row == KEYLOC_ENCODER_CCW;
}
static inline bool IS_PRESSED(keyevent_t event) {
    return !IS_NOEVENT(event) && event.pressed;
}
static inline bool IS_RELEASED(keyevent_t event) {
    return !IS_NOEVENT(event) && !event.pressed;
}

/* Common keyevent object factory */
#define MAKE_KEYPOS(row_num, col_num) ((keypos_t){.row = (row_num), .col = (col_num)})
#define MAKE_KEYEVENT(row_num, col_num, press) ((keyevent_t){.key = MAKE_KEYPOS((row_num), (col_num)), .pressed = (press), .time = (timer_read() | 1)})

/* Tick event */
#define TICK_EVENT MAKE_KEYEVENT(KEYLOC_TICK, KEYLOC_TICK, false)

#ifdef ENCODER_MAP_ENABLE
/* Encoder events */
#    define ENCODER_CW_EVENT(enc_id, press) MAKE_KEYEVENT(KEYLOC_ENCODER_CW, (enc_id), (press))
#    define ENCODER_CCW_EVENT(enc_id, press) MAKE_KEYEVENT(KEYLOC_ENCODER_CCW, (enc_id), (press))
#endif // ENCODER_MAP_ENABLE

/* it runs once at early stage of startup before keyboard_init. */
void keyboard_setup(void);
/* it runs once after initializing host side protocol, debug and MCU peripherals. */
void keyboard_init(void);
/* it runs repeatedly in main loop */
void keyboard_task(void);
/* it runs whenever code has to behave differently on a slave */
bool is_keyboard_master(void);
/* it runs whenever code has to behave differently on left vs right split */
bool is_keyboard_left(void);

void keyboard_pre_init_kb(void);
void keyboard_pre_init_user(void);
void keyboard_post_init_kb(void);
void keyboard_post_init_user(void);

void housekeeping_task(void);      // To be executed by the main loop in each backend TMK protocol
void housekeeping_task_kb(void);   // To be overridden by keyboard-level code
void housekeeping_task_user(void); // To be overridden by user/keymap-level code

uint32_t last_input_activity_time(void);    // Timestamp of the last matrix or encoder activity
uint32_t last_input_activity_elapsed(void); // Number of milliseconds since the last matrix or encoder activity

uint32_t last_matrix_activity_time(void);    // Timestamp of the last matrix activity
uint32_t last_matrix_activity_elapsed(void); // Number of milliseconds since the last matrix activity

uint32_t last_encoder_activity_time(void);    // Timestamp of the last encoder activity
uint32_t last_encoder_activity_elapsed(void); // Number of milliseconds since the last encoder activity

uint32_t get_matrix_scan_rate(void);

#ifdef __cplusplus
}
#endif
