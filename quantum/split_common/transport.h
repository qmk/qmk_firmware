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
#include "action_layer.h"
#include "matrix.h"

#ifndef RPC_M2S_BUFFER_SIZE
#    define RPC_M2S_BUFFER_SIZE 32
#endif  // RPC_M2S_BUFFER_SIZE

#ifndef RPC_S2M_BUFFER_SIZE
#    define RPC_S2M_BUFFER_SIZE 32
#endif  // RPC_S2M_BUFFER_SIZE

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

#if !defined(NO_ACTION_LAYER) && defined(SPLIT_LAYER_STATE_ENABLE)
typedef struct _split_layers_sync_t {
    layer_state_t layer_state;
    layer_state_t default_layer_state;
} split_layers_sync_t;
#endif  // !defined(NO_ACTION_LAYER) && defined(SPLIT_LAYER_STATE_ENABLE)

#if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
#    include "led_matrix.h"

typedef struct _led_matrix_sync_t {
    led_eeconfig_t led_matrix;
    bool           led_suspend_state;
} led_matrix_sync_t;
#endif  // defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)

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

#if defined(POINTING_DEVICE_ENABLE) && defined(SPLIT_POINTING_ENABLE)
#    include "pointing_device.h"
typedef struct _split_slave_pointing_sync_t {
    uint8_t        checksum;
    report_mouse_t report;
    uint16_t       cpi;
} split_slave_pointing_sync_t;
#endif  // defined(POINTING_DEVICE_ENABLE) && defined(SPLIT_POINTING_ENABLE)

#if defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)
typedef struct _rpc_sync_info_t {
    int8_t  transaction_id;
    uint8_t m2s_length;
    uint8_t s2m_length;
} rpc_sync_info_t;
#endif  // defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)

typedef struct _split_shared_memory_t {
#ifdef USE_I2C
    int8_t transaction_id;
#endif  // USE_I2C

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

#if !defined(NO_ACTION_LAYER) && defined(SPLIT_LAYER_STATE_ENABLE)
    split_layers_sync_t layers;
#endif  // !defined(NO_ACTION_LAYER) && defined(SPLIT_LAYER_STATE_ENABLE)

#ifdef SPLIT_LED_STATE_ENABLE
    uint8_t led_state;
#endif  // SPLIT_LED_STATE_ENABLE

#ifdef SPLIT_MODS_ENABLE
    split_mods_sync_t mods;
#endif  // SPLIT_MODS_ENABLE

#ifdef BACKLIGHT_ENABLE
    uint8_t backlight_level;
#endif  // BACKLIGHT_ENABLE

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    rgblight_syncinfo_t rgblight_sync;
#endif  // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

#if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)
    led_matrix_sync_t led_matrix_sync;
#endif  // defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)
    rgb_matrix_sync_t rgb_matrix_sync;
#endif  // defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)

#if defined(WPM_ENABLE) && defined(SPLIT_WPM_ENABLE)
    uint8_t current_wpm;
#endif  // defined(WPM_ENABLE) && defined(SPLIT_WPM_ENABLE)

#if defined(OLED_ENABLE) && defined(SPLIT_OLED_ENABLE)
    uint8_t current_oled_state;
#endif  // defined(OLED_ENABLE) && defined(SPLIT_OLED_ENABLE)

#if defined(ST7565_ENABLE) && defined(SPLIT_ST7565_ENABLE)
    uint8_t current_st7565_state;
#endif  // ST7565_ENABLE(OLED_ENABLE) && defined(SPLIT_ST7565_ENABLE)

#if defined(POINTING_DEVICE_ENABLE) && defined(SPLIT_POINTING_ENABLE)
    split_slave_pointing_sync_t pointing;
#endif  // defined(POINTING_DEVICE_ENABLE) && defined(SPLIT_POINTING_ENABLE)

#if defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)
    rpc_sync_info_t rpc_info;
    uint8_t         rpc_m2s_buffer[RPC_M2S_BUFFER_SIZE];
    uint8_t         rpc_s2m_buffer[RPC_S2M_BUFFER_SIZE];
#endif  // defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)
} split_shared_memory_t;

extern split_shared_memory_t *const split_shmem;
