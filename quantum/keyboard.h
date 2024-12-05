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

#include "timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/* key matrix position */
typedef struct {
    uint8_t col;
    uint8_t row;
} keypos_t;

typedef enum keyevent_type_t { TICK_EVENT = 0, KEY_EVENT = 1, ENCODER_CW_EVENT = 2, ENCODER_CCW_EVENT = 3, COMBO_EVENT = 4, DIP_SWITCH_ON_EVENT = 5, DIP_SWITCH_OFF_EVENT = 6 } keyevent_type_t;

/* key event */
typedef struct {
    keypos_t        key;
    uint16_t        time;
    keyevent_type_t type;
    bool            pressed;
} keyevent_t;

/* equivalent test of keypos_t */
#define KEYEQ(keya, keyb) ((keya).row == (keyb).row && (keya).col == (keyb).col)

/* special keypos_t entries */
#define KEYLOC_ENCODER_CW 253
#define KEYLOC_ENCODER_CCW 252
#define KEYLOC_DIP_SWITCH_ON 251
#define KEYLOC_DIP_SWITCH_OFF 250

static inline bool IS_NOEVENT(const keyevent_t event) {
    return event.type == TICK_EVENT;
}
static inline bool IS_EVENT(const keyevent_t event) {
    return event.type != TICK_EVENT;
}
static inline bool IS_KEYEVENT(const keyevent_t event) {
    return event.type == KEY_EVENT;
}
static inline bool IS_COMBOEVENT(const keyevent_t event) {
    return event.type == COMBO_EVENT;
}
static inline bool IS_ENCODEREVENT(const keyevent_t event) {
    return event.type == ENCODER_CW_EVENT || event.type == ENCODER_CCW_EVENT;
}
static inline bool IS_DIPSWITCHEVENT(const keyevent_t event) {
    return event.type == DIP_SWITCH_ON_EVENT || event.type == DIP_SWITCH_OFF_EVENT;
}

/* Common keypos_t object factory */
#define MAKE_KEYPOS(row_num, col_num) ((keypos_t){.row = (row_num), .col = (col_num)})

/* Common keyevent_t object factory */
#define MAKE_EVENT(row_num, col_num, press, event_type) ((keyevent_t){.key = MAKE_KEYPOS((row_num), (col_num)), .pressed = (press), .time = timer_read(), .type = (event_type)})

/**
 * @brief Constructs a key event for a pressed or released key.
 */
#define MAKE_KEYEVENT(row_num, col_num, press) MAKE_EVENT((row_num), (col_num), (press), KEY_EVENT)

/**
 * @brief Constructs a combo event.
 */
#define MAKE_COMBOEVENT(press) MAKE_EVENT(0, 0, (press), COMBO_EVENT)

/**
 * @brief Constructs a internal tick event that is used to drive the internal QMK state machine.
 */
#define MAKE_TICK_EVENT MAKE_EVENT(0, 0, false, TICK_EVENT)

#ifdef ENCODER_MAP_ENABLE
/* Encoder events */
#    define MAKE_ENCODER_CW_EVENT(enc_id, press) MAKE_EVENT(KEYLOC_ENCODER_CW, (enc_id), (press), ENCODER_CW_EVENT)
#    define MAKE_ENCODER_CCW_EVENT(enc_id, press) MAKE_EVENT(KEYLOC_ENCODER_CCW, (enc_id), (press), ENCODER_CCW_EVENT)
#endif // ENCODER_MAP_ENABLE

#ifdef DIP_SWITCH_MAP_ENABLE
/* Dip Switch events */
#    define MAKE_DIPSWITCH_ON_EVENT(switch_id, press) MAKE_EVENT(KEYLOC_DIP_SWITCH_ON, (switch_id), (press), DIP_SWITCH_ON_EVENT)
#    define MAKE_DIPSWITCH_OFF_EVENT(switch_id, press) MAKE_EVENT(KEYLOC_DIP_SWITCH_OFF, (switch_id), (press), DIP_SWITCH_OFF_EVENT)
#endif // DIP_SWITCH_MAP_ENABLE

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

uint32_t last_input_activity_time(void);    // Timestamp of the last matrix or encoder or pointing device activity
uint32_t last_input_activity_elapsed(void); // Number of milliseconds since the last matrix or encoder or pointing device activity

uint32_t last_matrix_activity_time(void);    // Timestamp of the last matrix activity
uint32_t last_matrix_activity_elapsed(void); // Number of milliseconds since the last matrix activity

uint32_t last_encoder_activity_time(void);    // Timestamp of the last encoder activity
uint32_t last_encoder_activity_elapsed(void); // Number of milliseconds since the last encoder activity

uint32_t last_pointing_device_activity_time(void);    // Timestamp of the last pointing device activity
uint32_t last_pointing_device_activity_elapsed(void); // Number of milliseconds since the last  pointing device activity

void set_activity_timestamps(uint32_t matrix_timestamp, uint32_t encoder_timestamp, uint32_t pointing_device_timestamp); // Set the timestamps of the last matrix and encoder activity

uint32_t get_matrix_scan_rate(void);

#ifdef __cplusplus
}
#endif
