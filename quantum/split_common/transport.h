/* Copyright 2021 QMK
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

#pragma once

#include "stdint.h"
#include "stdbool.h"

#include "progmem.h"
#include "matrix.h"

void transport_master_init(void);
void transport_slave_init(void);

// returns false if valid data not received from slave
bool transport_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]);
void transport_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]);

bool transport_execute_transaction(int8_t id, const void *initiator2target_buf, uint16_t initiator2target_length, void *target2initiator_buf, uint16_t target2initiator_length);

#ifdef ENCODER_ENABLE
#    include "encoder.h"
#    define NUMBER_OF_ENCODERS (sizeof((pin_t[])ENCODERS_PAD_A) / sizeof(pin_t))
#endif  // ENCODER_ENABLE

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif  // BACKLIGHT_ENABLE

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif  // RGBLIGHT_ENABLE

typedef struct _split_slave_matrix_sync_t {
    uint8_t      checksum;
    matrix_row_t matrix[(MATRIX_ROWS) / 2];
} split_slave_matrix_sync_t;

#ifdef SPLIT_TRANSPORT_MIRROR
typedef struct _split_master_matrix_sync_t {
    matrix_row_t matrix[(MATRIX_ROWS) / 2];
} split_master_matrix_sync_t;
#endif  // SPLIT_TRANSPORT_MIRROR

#ifdef ENCODER_ENABLE
typedef struct _split_slave_encoder_sync_t {
    uint8_t checksum;
    uint8_t state[NUMBER_OF_ENCODERS];
} split_slave_encoder_sync_t;
#endif  // ENCODER_ENABLE

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
#    include "rgb_matrix.h"

typedef struct _rgb_matrix_sync_t {
    rgb_config_t rgb_matrix;
    bool         rgb_suspend_state;
} rgb_matrix_sync_t;
#endif  // defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)

#ifdef SPLIT_MODS_ENABLE
typedef struct _split_mods_sync_t {
    uint8_t real_mods;
    uint8_t weak_mods;
#    ifndef NO_ACTION_ONESHOT
    uint8_t oneshot_mods;
#    endif  // NO_ACTION_ONESHOT
} split_mods_sync_t;
#endif  // SPLIT_MODS_ENABLE

typedef struct _split_shared_memory_t {
    split_slave_matrix_sync_t smatrix;

#ifdef SPLIT_TRANSPORT_MIRROR
    split_master_matrix_sync_t mmatrix;
#endif  // SPLIT_TRANSPORT_MIRROR

#ifdef ENCODER_ENABLE
    split_slave_encoder_sync_t encoders;
#endif  // ENCODER_ENABLE

#ifndef DISABLE_SYNC_TIMER
    uint32_t sync_timer;
#endif  // DISABLE_SYNC_TIMER

#ifndef DISABLE_SYNC_LAYER_STATE
    uint32_t layer_state;
#endif  // DISABLE_SYNC_LAYER_STATE

#ifndef DISABLE_SYNC_LED_STATE
    uint8_t led_state;
#endif  // DISABLE_SYNC_LED_STATE

#ifdef SPLIT_MODS_ENABLE
    split_mods_sync_t mods;
#endif  // SPLIT_MODS_ENABLE

#ifdef BACKLIGHT_ENABLE
    uint8_t backlight_level;
#endif  // BACKLIGHT_ENABLE

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    rgblight_syncinfo_t rgblight_sync;
#endif  // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    rgb_matrix_sync_t rgb_matrix_sync;
#endif  // defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)

#ifdef WPM_ENABLE
    uint8_t current_wpm;
#endif  // WPM_ENABLE
} split_shared_memory_t;

extern split_shared_memory_t *const split_shmem;