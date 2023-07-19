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

#include <string.h>
#include <stddef.h>

#include "crc.h"
#include "debug.h"
#include "matrix.h"
#include "host.h"
#include "action_util.h"
#include "sync_timer.h"
#include "wait.h"
#include "transactions.h"
#include "transport.h"
#include "transaction_id_define.h"
#include "split_util.h"
#include "synchronization_util.h"

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif
#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif
#ifdef LED_MATRIX_ENABLE
#    include "led_matrix.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif
#ifdef OLED_ENABLE
#    include "oled_driver.h"
#endif
#ifdef ST7565_ENABLE
#    include "st7565.h"
#endif
#ifdef ENCODER_ENABLE
#    include "encoder.h"
#endif
#ifdef HAPTIC_ENABLE
#    include "haptic.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
#    include "pointing_device.h"
#endif
#ifdef OS_DETECTION_ENABLE
#    include "os_detection.h"
#endif
#ifdef WPM_ENABLE
#    include "wpm.h"
#endif

#define SYNC_TIMER_OFFSET 2

#ifndef FORCED_SYNC_THROTTLE_MS
#    define FORCED_SYNC_THROTTLE_MS 100
#endif // FORCED_SYNC_THROTTLE_MS

#define sizeof_member(type, member) sizeof(((type *)NULL)->member)

#define trans_initiator2target_initializer_cb(member, cb) \
    { sizeof_member(split_shared_memory_t, member), offsetof(split_shared_memory_t, member), 0, 0, cb }
#define trans_initiator2target_initializer(member) trans_initiator2target_initializer_cb(member, NULL)

#define trans_target2initiator_initializer_cb(member, cb) \
    { 0, 0, sizeof_member(split_shared_memory_t, member), offsetof(split_shared_memory_t, member), cb }
#define trans_target2initiator_initializer(member) trans_target2initiator_initializer_cb(member, NULL)

#define transport_write(id, data, length) transport_execute_transaction(id, data, length, NULL, 0)
#define transport_read(id, data, length) transport_execute_transaction(id, NULL, 0, data, length)

#if defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)
// Forward-declare the RPC callback handlers
void slave_rpc_info_callback(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);
void slave_rpc_exec_callback(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);
#endif // defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)

////////////////////////////////////////////////////
// Helpers

static bool transaction_handler_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[], const char *prefix, bool (*handler)(matrix_row_t master_matrix[], matrix_row_t slave_matrix[])) {
    int num_retries = is_transport_connected() ? 10 : 1;
    for (int iter = 1; iter <= num_retries; ++iter) {
        if (iter > 1) {
            for (int i = 0; i < iter * iter; ++i) {
                wait_us(10);
            }
        }
        bool this_okay = true;
        this_okay      = handler(master_matrix, slave_matrix);
        if (this_okay) return true;
    }
    dprintf("Failed to execute %s\n", prefix);
    return false;
}

#define TRANSACTION_HANDLER_MASTER(prefix)                                                                              \
    do {                                                                                                                \
        if (!transaction_handler_master(master_matrix, slave_matrix, #prefix, &prefix##_handlers_master)) return false; \
    } while (0)

/**
 * @brief Constructs a transaction handler that doesn't acquire a lock to the
 * split shared memory. Therefore the locking and unlocking has to be done
 * manually inside the handler. Use this macro only if the handler is
 * non-deterministic in runtime and thus needs a manual lock unlock
 * implementation to hold the lock for the shortest possible time.
 */
#define TRANSACTION_HANDLER_SLAVE(prefix)                     \
    do {                                                      \
        prefix##_handlers_slave(master_matrix, slave_matrix); \
    } while (0)

/**
 * @brief Constructs a transaction handler that automatically acquires a lock to
 * safely access the split shared memory and releases the lock again after
 * processing the handler. Use this macro if the handler is fast and
 * deterministic in runtime and thus holds the lock only for a very short time.
 * If not fallback to manually locking and unlocking inside the handler.
 */
#define TRANSACTION_HANDLER_SLAVE_AUTOLOCK(prefix)            \
    do {                                                      \
        split_shared_memory_lock();                           \
        prefix##_handlers_slave(master_matrix, slave_matrix); \
        split_shared_memory_unlock();                         \
    } while (0)

inline static bool read_if_checksum_mismatch(int8_t trans_id_checksum, int8_t trans_id_retrieve, uint32_t *last_update, void *destination, const void *equiv_shmem, size_t length) {
    uint8_t curr_checksum;
    bool    okay = transport_read(trans_id_checksum, &curr_checksum, sizeof(curr_checksum));
    if (okay && (timer_elapsed32(*last_update) >= FORCED_SYNC_THROTTLE_MS || curr_checksum != crc8(equiv_shmem, length))) {
        okay &= transport_read(trans_id_retrieve, destination, length);
        okay &= curr_checksum == crc8(equiv_shmem, length);
        if (okay) {
            *last_update = timer_read32();
        }
    } else {
        memcpy(destination, equiv_shmem, length);
    }
    return okay;
}

inline static bool send_if_condition(int8_t trans_id, uint32_t *last_update, bool condition, void *source, size_t length) {
    bool okay = true;
    if (timer_elapsed32(*last_update) >= FORCED_SYNC_THROTTLE_MS || condition) {
        okay &= transport_write(trans_id, source, length);
        if (okay) {
            *last_update = timer_read32();
        }
    }
    return okay;
}

inline static bool send_if_data_mismatch(int8_t trans_id, uint32_t *last_update, void *source, const void *equiv_shmem, size_t length) {
    // Just run a memcmp to compare the source and equivalent shmem location
    return send_if_condition(trans_id, last_update, (memcmp(source, equiv_shmem, length) != 0), source, length);
}

////////////////////////////////////////////////////
// Slave matrix

static bool slave_matrix_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t     last_update                    = 0;
    static matrix_row_t last_matrix[(MATRIX_ROWS) / 2] = {0}; // last successfully-read matrix, so we can replicate if there are checksum errors
    matrix_row_t        temp_matrix[(MATRIX_ROWS) / 2];       // holding area while we test whether or not checksum is correct

    bool okay = read_if_checksum_mismatch(GET_SLAVE_MATRIX_CHECKSUM, GET_SLAVE_MATRIX_DATA, &last_update, temp_matrix, split_shmem->smatrix.matrix, sizeof(split_shmem->smatrix.matrix));
    if (okay) {
        // Checksum matches the received data, save as the last matrix state
        memcpy(last_matrix, temp_matrix, sizeof(temp_matrix));
    }
    // Copy out the last-known-good matrix state to the slave matrix
    memcpy(slave_matrix, last_matrix, sizeof(last_matrix));
    return okay;
}

static void slave_matrix_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    memcpy(split_shmem->smatrix.matrix, slave_matrix, sizeof(split_shmem->smatrix.matrix));
    split_shmem->smatrix.checksum = crc8(split_shmem->smatrix.matrix, sizeof(split_shmem->smatrix.matrix));
}

// clang-format off
#define TRANSACTIONS_SLAVE_MATRIX_MASTER() TRANSACTION_HANDLER_MASTER(slave_matrix)
#define TRANSACTIONS_SLAVE_MATRIX_SLAVE() TRANSACTION_HANDLER_SLAVE_AUTOLOCK(slave_matrix)
#define TRANSACTIONS_SLAVE_MATRIX_REGISTRATIONS \
    [GET_SLAVE_MATRIX_CHECKSUM] = trans_target2initiator_initializer(smatrix.checksum), \
    [GET_SLAVE_MATRIX_DATA]     = trans_target2initiator_initializer(smatrix.matrix),
// clang-format on

////////////////////////////////////////////////////
// Master matrix

#ifdef SPLIT_TRANSPORT_MIRROR

static bool master_matrix_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_update = 0;
    return send_if_data_mismatch(PUT_MASTER_MATRIX, &last_update, master_matrix, split_shmem->mmatrix.matrix, sizeof(split_shmem->mmatrix.matrix));
}

static void master_matrix_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    // Always copy to the master matrix
    memcpy(master_matrix, split_shmem->mmatrix.matrix, sizeof(split_shmem->mmatrix.matrix));
}

#    define TRANSACTIONS_MASTER_MATRIX_MASTER() TRANSACTION_HANDLER_MASTER(master_matrix)
#    define TRANSACTIONS_MASTER_MATRIX_SLAVE() TRANSACTION_HANDLER_SLAVE_AUTOLOCK(master_matrix)
#    define TRANSACTIONS_MASTER_MATRIX_REGISTRATIONS [PUT_MASTER_MATRIX] = trans_initiator2target_initializer(mmatrix.matrix),

#else // SPLIT_TRANSPORT_MIRROR

#    define TRANSACTIONS_MASTER_MATRIX_MASTER()
#    define TRANSACTIONS_MASTER_MATRIX_SLAVE()
#    define TRANSACTIONS_MASTER_MATRIX_REGISTRATIONS

#endif // SPLIT_TRANSPORT_MIRROR

////////////////////////////////////////////////////
// Encoders

#ifdef ENCODER_ENABLE

static bool encoder_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_update = 0;
    uint8_t         temp_state[NUM_ENCODERS_MAX_PER_SIDE];

    bool okay = read_if_checksum_mismatch(GET_ENCODERS_CHECKSUM, GET_ENCODERS_DATA, &last_update, temp_state, split_shmem->encoders.state, sizeof(temp_state));
    if (okay) encoder_update_raw(temp_state);
    return okay;
}

static void encoder_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    uint8_t encoder_state[NUM_ENCODERS_MAX_PER_SIDE];
    encoder_state_raw(encoder_state);
    // Always prepare the encoder state for read.
    memcpy(split_shmem->encoders.state, encoder_state, sizeof(encoder_state));
    // Now update the checksum given that the encoders has been written to
    split_shmem->encoders.checksum = crc8(encoder_state, sizeof(encoder_state));
}

// clang-format off
#    define TRANSACTIONS_ENCODERS_MASTER() TRANSACTION_HANDLER_MASTER(encoder)
#    define TRANSACTIONS_ENCODERS_SLAVE() TRANSACTION_HANDLER_SLAVE_AUTOLOCK(encoder)
#    define TRANSACTIONS_ENCODERS_REGISTRATIONS \
    [GET_ENCODERS_CHECKSUM] = trans_target2initiator_initializer(encoders.checksum), \
    [GET_ENCODERS_DATA]     = trans_target2initiator_initializer(encoders.state),
// clang-format on

#else // ENCODER_ENABLE

#    define TRANSACTIONS_ENCODERS_MASTER()
#    define TRANSACTIONS_ENCODERS_SLAVE()
#    define TRANSACTIONS_ENCODERS_REGISTRATIONS

#endif // ENCODER_ENABLE

////////////////////////////////////////////////////
// Sync timer

#ifndef DISABLE_SYNC_TIMER

static bool sync_timer_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_update = 0;

    bool okay = true;
    if (timer_elapsed32(last_update) >= FORCED_SYNC_THROTTLE_MS) {
        uint32_t sync_timer = sync_timer_read32() + SYNC_TIMER_OFFSET;
        okay &= transport_write(PUT_SYNC_TIMER, &sync_timer, sizeof(sync_timer));
        if (okay) {
            last_update = timer_read32();
        }
    }
    return okay;
}

static void sync_timer_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_sync_timer = 0;
    if (last_sync_timer != split_shmem->sync_timer) {
        last_sync_timer = split_shmem->sync_timer;
        sync_timer_update(last_sync_timer);
    }
}

#    define TRANSACTIONS_SYNC_TIMER_MASTER() TRANSACTION_HANDLER_MASTER(sync_timer)
#    define TRANSACTIONS_SYNC_TIMER_SLAVE() TRANSACTION_HANDLER_SLAVE_AUTOLOCK(sync_timer)
#    define TRANSACTIONS_SYNC_TIMER_REGISTRATIONS [PUT_SYNC_TIMER] = trans_initiator2target_initializer(sync_timer),

#else // DISABLE_SYNC_TIMER

#    define TRANSACTIONS_SYNC_TIMER_MASTER()
#    define TRANSACTIONS_SYNC_TIMER_SLAVE()
#    define TRANSACTIONS_SYNC_TIMER_REGISTRATIONS

#endif // DISABLE_SYNC_TIMER

////////////////////////////////////////////////////
// Layer state

#if !defined(NO_ACTION_LAYER) && defined(SPLIT_LAYER_STATE_ENABLE)

static bool layer_state_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_layer_state_update         = 0;
    static uint32_t last_default_layer_state_update = 0;

    bool okay = send_if_condition(PUT_LAYER_STATE, &last_layer_state_update, (layer_state != split_shmem->layers.layer_state), &layer_state, sizeof(layer_state));
    if (okay) {
        okay &= send_if_condition(PUT_DEFAULT_LAYER_STATE, &last_default_layer_state_update, (default_layer_state != split_shmem->layers.default_layer_state), &default_layer_state, sizeof(default_layer_state));
    }
    return okay;
}

static void layer_state_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    layer_state         = split_shmem->layers.layer_state;
    default_layer_state = split_shmem->layers.default_layer_state;
}

// clang-format off
#    define TRANSACTIONS_LAYER_STATE_MASTER() TRANSACTION_HANDLER_MASTER(layer_state)
#    define TRANSACTIONS_LAYER_STATE_SLAVE() TRANSACTION_HANDLER_SLAVE_AUTOLOCK(layer_state)
#    define TRANSACTIONS_LAYER_STATE_REGISTRATIONS \
    [PUT_LAYER_STATE]         = trans_initiator2target_initializer(layers.layer_state), \
    [PUT_DEFAULT_LAYER_STATE] = trans_initiator2target_initializer(layers.default_layer_state),
// clang-format on

#else // !defined(NO_ACTION_LAYER) && defined(SPLIT_LAYER_STATE_ENABLE)

#    define TRANSACTIONS_LAYER_STATE_MASTER()
#    define TRANSACTIONS_LAYER_STATE_SLAVE()
#    define TRANSACTIONS_LAYER_STATE_REGISTRATIONS

#endif // !defined(NO_ACTION_LAYER) && defined(SPLIT_LAYER_STATE_ENABLE)

////////////////////////////////////////////////////
// LED state

#ifdef SPLIT_LED_STATE_ENABLE

static bool led_state_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_update = 0;
    uint8_t         led_state   = host_keyboard_leds();
    return send_if_data_mismatch(PUT_LED_STATE, &last_update, &led_state, &split_shmem->led_state, sizeof(led_state));
}

static void led_state_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    void set_split_host_keyboard_leds(uint8_t led_state);
    set_split_host_keyboard_leds(split_shmem->led_state);
}

#    define TRANSACTIONS_LED_STATE_MASTER() TRANSACTION_HANDLER_MASTER(led_state)
#    define TRANSACTIONS_LED_STATE_SLAVE() TRANSACTION_HANDLER_SLAVE_AUTOLOCK(led_state)
#    define TRANSACTIONS_LED_STATE_REGISTRATIONS [PUT_LED_STATE] = trans_initiator2target_initializer(led_state),

#else // SPLIT_LED_STATE_ENABLE

#    define TRANSACTIONS_LED_STATE_MASTER()
#    define TRANSACTIONS_LED_STATE_SLAVE()
#    define TRANSACTIONS_LED_STATE_REGISTRATIONS

#endif // SPLIT_LED_STATE_ENABLE

////////////////////////////////////////////////////
// Mods

#ifdef SPLIT_MODS_ENABLE

static bool mods_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t   last_update    = 0;
    bool              mods_need_sync = timer_elapsed32(last_update) >= FORCED_SYNC_THROTTLE_MS;
    split_mods_sync_t new_mods;
    new_mods.real_mods = get_mods();
    if (!mods_need_sync && new_mods.real_mods != split_shmem->mods.real_mods) {
        mods_need_sync = true;
    }

    new_mods.weak_mods = get_weak_mods();
    if (!mods_need_sync && new_mods.weak_mods != split_shmem->mods.weak_mods) {
        mods_need_sync = true;
    }

#    ifndef NO_ACTION_ONESHOT
    new_mods.oneshot_mods = get_oneshot_mods();
    if (!mods_need_sync && new_mods.oneshot_mods != split_shmem->mods.oneshot_mods) {
        mods_need_sync = true;
    }
#    endif // NO_ACTION_ONESHOT

    bool okay = true;
    if (mods_need_sync) {
        okay &= transport_write(PUT_MODS, &new_mods, sizeof(new_mods));
        if (okay) {
            last_update = timer_read32();
        }
    }

    return okay;
}

static void mods_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    split_shared_memory_lock();
    split_mods_sync_t mods;
    memcpy(&mods, &split_shmem->mods, sizeof(split_mods_sync_t));
    split_shared_memory_unlock();

    set_mods(mods.real_mods);
    set_weak_mods(mods.weak_mods);
#    ifndef NO_ACTION_ONESHOT
    set_oneshot_mods(mods.oneshot_mods);
#    endif
}

#    define TRANSACTIONS_MODS_MASTER() TRANSACTION_HANDLER_MASTER(mods)
#    define TRANSACTIONS_MODS_SLAVE() TRANSACTION_HANDLER_SLAVE(mods)
#    define TRANSACTIONS_MODS_REGISTRATIONS [PUT_MODS] = trans_initiator2target_initializer(mods),

#else // SPLIT_MODS_ENABLE

#    define TRANSACTIONS_MODS_MASTER()
#    define TRANSACTIONS_MODS_SLAVE()
#    define TRANSACTIONS_MODS_REGISTRATIONS

#endif // SPLIT_MODS_ENABLE

////////////////////////////////////////////////////
// Backlight

#ifdef BACKLIGHT_ENABLE

static bool backlight_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_update = 0;
    uint8_t         level       = is_backlight_enabled() ? get_backlight_level() : 0;
    return send_if_condition(PUT_BACKLIGHT, &last_update, (level != split_shmem->backlight_level), &level, sizeof(level));
}

static void backlight_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    split_shared_memory_lock();
    uint8_t backlight_level = split_shmem->backlight_level;
    split_shared_memory_unlock();

    backlight_level_noeeprom(backlight_level);
}

#    define TRANSACTIONS_BACKLIGHT_MASTER() TRANSACTION_HANDLER_MASTER(backlight)
#    define TRANSACTIONS_BACKLIGHT_SLAVE() TRANSACTION_HANDLER_SLAVE(backlight)
#    define TRANSACTIONS_BACKLIGHT_REGISTRATIONS [PUT_BACKLIGHT] = trans_initiator2target_initializer(backlight_level),

#else // BACKLIGHT_ENABLE

#    define TRANSACTIONS_BACKLIGHT_MASTER()
#    define TRANSACTIONS_BACKLIGHT_SLAVE()
#    define TRANSACTIONS_BACKLIGHT_REGISTRATIONS

#endif // BACKLIGHT_ENABLE

////////////////////////////////////////////////////
// RGBLIGHT

#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

static bool rgblight_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t     last_update = 0;
    rgblight_syncinfo_t rgblight_sync;
    rgblight_get_syncinfo(&rgblight_sync);
    if (send_if_condition(PUT_RGBLIGHT, &last_update, (rgblight_sync.status.change_flags != 0), &rgblight_sync, sizeof(rgblight_sync))) {
        rgblight_clear_change_flags();
    } else {
        return false;
    }
    return true;
}

static void rgblight_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    split_shared_memory_lock();
    // Update the RGB with the new data
    rgblight_syncinfo_t rgblight_sync;
    memcpy(&rgblight_sync, &split_shmem->rgblight_sync, sizeof(rgblight_syncinfo_t));
    split_shmem->rgblight_sync.status.change_flags = 0;
    split_shared_memory_unlock();

    if (rgblight_sync.status.change_flags != 0) {
        rgblight_update_sync(&rgblight_sync, false);
    }
}

#    define TRANSACTIONS_RGBLIGHT_MASTER() TRANSACTION_HANDLER_MASTER(rgblight)
#    define TRANSACTIONS_RGBLIGHT_SLAVE() TRANSACTION_HANDLER_SLAVE(rgblight)
#    define TRANSACTIONS_RGBLIGHT_REGISTRATIONS [PUT_RGBLIGHT] = trans_initiator2target_initializer(rgblight_sync),

#else // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

#    define TRANSACTIONS_RGBLIGHT_MASTER()
#    define TRANSACTIONS_RGBLIGHT_SLAVE()
#    define TRANSACTIONS_RGBLIGHT_REGISTRATIONS

#endif // defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

////////////////////////////////////////////////////
// LED Matrix

#if defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)

static bool led_matrix_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t   last_update = 0;
    led_matrix_sync_t led_matrix_sync;
    memcpy(&led_matrix_sync.led_matrix, &led_matrix_eeconfig, sizeof(led_eeconfig_t));
    led_matrix_sync.led_suspend_state = led_matrix_get_suspend_state();
    return send_if_data_mismatch(PUT_LED_MATRIX, &last_update, &led_matrix_sync, &split_shmem->led_matrix_sync, sizeof(led_matrix_sync));
}

static void led_matrix_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    split_shared_memory_lock();
    memcpy(&led_matrix_eeconfig, &split_shmem->led_matrix_sync.led_matrix, sizeof(led_eeconfig_t));
    bool led_suspend_state = split_shmem->led_matrix_sync.led_suspend_state;
    split_shared_memory_unlock();

    led_matrix_set_suspend_state(led_suspend_state);
}

#    define TRANSACTIONS_LED_MATRIX_MASTER() TRANSACTION_HANDLER_MASTER(led_matrix)
#    define TRANSACTIONS_LED_MATRIX_SLAVE() TRANSACTION_HANDLER_SLAVE(led_matrix)
#    define TRANSACTIONS_LED_MATRIX_REGISTRATIONS [PUT_LED_MATRIX] = trans_initiator2target_initializer(led_matrix_sync),

#else // defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)

#    define TRANSACTIONS_LED_MATRIX_MASTER()
#    define TRANSACTIONS_LED_MATRIX_SLAVE()
#    define TRANSACTIONS_LED_MATRIX_REGISTRATIONS

#endif // defined(LED_MATRIX_ENABLE) && defined(LED_MATRIX_SPLIT)

////////////////////////////////////////////////////
// RGB Matrix

#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)

static bool rgb_matrix_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t   last_update = 0;
    rgb_matrix_sync_t rgb_matrix_sync;
    memcpy(&rgb_matrix_sync.rgb_matrix, &rgb_matrix_config, sizeof(rgb_config_t));
    rgb_matrix_sync.rgb_suspend_state = rgb_matrix_get_suspend_state();
    return send_if_data_mismatch(PUT_RGB_MATRIX, &last_update, &rgb_matrix_sync, &split_shmem->rgb_matrix_sync, sizeof(rgb_matrix_sync));
}

static void rgb_matrix_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    split_shared_memory_lock();
    memcpy(&rgb_matrix_config, &split_shmem->rgb_matrix_sync.rgb_matrix, sizeof(rgb_config_t));
    bool rgb_suspend_state = split_shmem->rgb_matrix_sync.rgb_suspend_state;
    split_shared_memory_unlock();

    rgb_matrix_set_suspend_state(rgb_suspend_state);
}

#    define TRANSACTIONS_RGB_MATRIX_MASTER() TRANSACTION_HANDLER_MASTER(rgb_matrix)
#    define TRANSACTIONS_RGB_MATRIX_SLAVE() TRANSACTION_HANDLER_SLAVE(rgb_matrix)
#    define TRANSACTIONS_RGB_MATRIX_REGISTRATIONS [PUT_RGB_MATRIX] = trans_initiator2target_initializer(rgb_matrix_sync),

#else // defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)

#    define TRANSACTIONS_RGB_MATRIX_MASTER()
#    define TRANSACTIONS_RGB_MATRIX_SLAVE()
#    define TRANSACTIONS_RGB_MATRIX_REGISTRATIONS

#endif // defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_SPLIT)

////////////////////////////////////////////////////
// WPM

#if defined(WPM_ENABLE) && defined(SPLIT_WPM_ENABLE)

static bool wpm_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_update = 0;
    uint8_t         current_wpm = get_current_wpm();
    return send_if_condition(PUT_WPM, &last_update, (current_wpm != split_shmem->current_wpm), &current_wpm, sizeof(current_wpm));
}

static void wpm_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    set_current_wpm(split_shmem->current_wpm);
}

#    define TRANSACTIONS_WPM_MASTER() TRANSACTION_HANDLER_MASTER(wpm)
#    define TRANSACTIONS_WPM_SLAVE() TRANSACTION_HANDLER_SLAVE_AUTOLOCK(wpm)
#    define TRANSACTIONS_WPM_REGISTRATIONS [PUT_WPM] = trans_initiator2target_initializer(current_wpm),

#else // defined(WPM_ENABLE) && defined(SPLIT_WPM_ENABLE)

#    define TRANSACTIONS_WPM_MASTER()
#    define TRANSACTIONS_WPM_SLAVE()
#    define TRANSACTIONS_WPM_REGISTRATIONS

#endif // defined(WPM_ENABLE) && defined(SPLIT_WPM_ENABLE)

////////////////////////////////////////////////////
// OLED

#if defined(OLED_ENABLE) && defined(SPLIT_OLED_ENABLE)

static bool oled_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_update        = 0;
    bool            current_oled_state = is_oled_on();
    return send_if_condition(PUT_OLED, &last_update, (current_oled_state != split_shmem->current_oled_state), &current_oled_state, sizeof(current_oled_state));
}

static void oled_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    split_shared_memory_lock();
    uint8_t current_oled_state = split_shmem->current_oled_state;
    split_shared_memory_unlock();

    if (current_oled_state) {
        oled_on();
    } else {
        oled_off();
    }
}

#    define TRANSACTIONS_OLED_MASTER() TRANSACTION_HANDLER_MASTER(oled)
#    define TRANSACTIONS_OLED_SLAVE() TRANSACTION_HANDLER_SLAVE(oled)
#    define TRANSACTIONS_OLED_REGISTRATIONS [PUT_OLED] = trans_initiator2target_initializer(current_oled_state),

#else // defined(OLED_ENABLE) && defined(SPLIT_OLED_ENABLE)

#    define TRANSACTIONS_OLED_MASTER()
#    define TRANSACTIONS_OLED_SLAVE()
#    define TRANSACTIONS_OLED_REGISTRATIONS

#endif // defined(OLED_ENABLE) && defined(SPLIT_OLED_ENABLE)

////////////////////////////////////////////////////
// ST7565

#if defined(ST7565_ENABLE) && defined(SPLIT_ST7565_ENABLE)

static bool st7565_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_update          = 0;
    bool            current_st7565_state = st7565_is_on();
    return send_if_condition(PUT_ST7565, &last_update, (current_st7565_state != split_shmem->current_st7565_state), &current_st7565_state, sizeof(current_st7565_state));
}

static void st7565_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    split_shared_memory_lock();
    uint8_t current_st7565_state = split_shmem->current_st7565_state;
    split_shared_memory_unlock();

    if (current_st7565_state) {
        st7565_on();
    } else {
        st7565_off();
    }
}

#    define TRANSACTIONS_ST7565_MASTER() TRANSACTION_HANDLER_MASTER(st7565)
#    define TRANSACTIONS_ST7565_SLAVE() TRANSACTION_HANDLER_SLAVE(st7565)
#    define TRANSACTIONS_ST7565_REGISTRATIONS [PUT_ST7565] = trans_initiator2target_initializer(current_st7565_state),

#else // defined(ST7565_ENABLE) && defined(SPLIT_ST7565_ENABLE)

#    define TRANSACTIONS_ST7565_MASTER()
#    define TRANSACTIONS_ST7565_SLAVE()
#    define TRANSACTIONS_ST7565_REGISTRATIONS

#endif // defined(ST7565_ENABLE) && defined(SPLIT_ST7565_ENABLE)

////////////////////////////////////////////////////
// POINTING

#if defined(POINTING_DEVICE_ENABLE) && defined(SPLIT_POINTING_ENABLE)

static bool pointing_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
#    if defined(POINTING_DEVICE_LEFT)
    if (is_keyboard_left()) {
        return true;
    }
#    elif defined(POINTING_DEVICE_RIGHT)
    if (!is_keyboard_left()) {
        return true;
    }
#    endif
    static uint32_t last_update = 0;
    static uint16_t last_cpi    = 0;
    report_mouse_t  temp_state;
    uint16_t        temp_cpi;
    bool            okay = read_if_checksum_mismatch(GET_POINTING_CHECKSUM, GET_POINTING_DATA, &last_update, &temp_state, &split_shmem->pointing.report, sizeof(temp_state));
    if (okay) pointing_device_set_shared_report(temp_state);
    temp_cpi = pointing_device_get_shared_cpi();
    if (temp_cpi && last_cpi != temp_cpi) {
        split_shmem->pointing.cpi = temp_cpi;
        okay                      = transport_write(PUT_POINTING_CPI, &split_shmem->pointing.cpi, sizeof(split_shmem->pointing.cpi));
        if (okay) {
            last_cpi = temp_cpi;
        }
    }
    return okay;
}

extern const pointing_device_driver_t pointing_device_driver;

static void pointing_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
#    if defined(POINTING_DEVICE_LEFT)
    if (!is_keyboard_left()) {
        return;
    }
#    elif defined(POINTING_DEVICE_RIGHT)
    if (is_keyboard_left()) {
        return;
    }
#    endif
#    if (POINTING_DEVICE_TASK_THROTTLE_MS > 0)
    static uint32_t last_exec = 0;
    if (timer_elapsed32(last_exec) < POINTING_DEVICE_TASK_THROTTLE_MS) {
        return;
    }
    last_exec = timer_read32();
#    endif

    uint16_t temp_cpi = !pointing_device_driver.get_cpi ? 0 : pointing_device_driver.get_cpi(); // check for NULL

    split_shared_memory_lock();
    split_slave_pointing_sync_t pointing;
    memcpy(&pointing, &split_shmem->pointing, sizeof(split_slave_pointing_sync_t));
    split_shared_memory_unlock();

    if (pointing.cpi && pointing.cpi != temp_cpi && pointing_device_driver.set_cpi) {
        pointing_device_driver.set_cpi(pointing.cpi);
    }

    pointing.report = pointing_device_driver.get_report((report_mouse_t){0});
    // Now update the checksum given that the pointing has been written to
    pointing.checksum = crc8(&pointing.report, sizeof(report_mouse_t));

    split_shared_memory_lock();
    memcpy(&split_shmem->pointing, &pointing, sizeof(split_slave_pointing_sync_t));
    split_shared_memory_unlock();
}

#    define TRANSACTIONS_POINTING_MASTER() TRANSACTION_HANDLER_MASTER(pointing)
#    define TRANSACTIONS_POINTING_SLAVE() TRANSACTION_HANDLER_SLAVE(pointing)
#    define TRANSACTIONS_POINTING_REGISTRATIONS [GET_POINTING_CHECKSUM] = trans_target2initiator_initializer(pointing.checksum), [GET_POINTING_DATA] = trans_target2initiator_initializer(pointing.report), [PUT_POINTING_CPI] = trans_initiator2target_initializer(pointing.cpi),

#else // defined(POINTING_DEVICE_ENABLE) && defined(SPLIT_POINTING_ENABLE)

#    define TRANSACTIONS_POINTING_MASTER()
#    define TRANSACTIONS_POINTING_SLAVE()
#    define TRANSACTIONS_POINTING_REGISTRATIONS

#endif // defined(POINTING_DEVICE_ENABLE) && defined(SPLIT_POINTING_ENABLE)

////////////////////////////////////////////////////
// WATCHDOG

#if defined(SPLIT_WATCHDOG_ENABLE)

static bool watchdog_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    bool okay = true;
    if (!split_watchdog_check()) {
        okay = transport_write(PUT_WATCHDOG, &okay, sizeof(okay));
        split_watchdog_update(okay);
    }
    return okay;
}

static void watchdog_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    split_watchdog_update(split_shmem->watchdog_pinged);
}

#    define TRANSACTIONS_WATCHDOG_MASTER() TRANSACTION_HANDLER_MASTER(watchdog)
#    define TRANSACTIONS_WATCHDOG_SLAVE() TRANSACTION_HANDLER_SLAVE_AUTOLOCK(watchdog)
#    define TRANSACTIONS_WATCHDOG_REGISTRATIONS [PUT_WATCHDOG] = trans_initiator2target_initializer(watchdog_pinged),

#else // defined(SPLIT_WATCHDOG_ENABLE)

#    define TRANSACTIONS_WATCHDOG_MASTER()
#    define TRANSACTIONS_WATCHDOG_SLAVE()
#    define TRANSACTIONS_WATCHDOG_REGISTRATIONS

#endif // defined(SPLIT_WATCHDOG_ENABLE)

#if defined(HAPTIC_ENABLE) && defined(SPLIT_HAPTIC_ENABLE)

uint8_t                split_haptic_play = 0xFF;
extern haptic_config_t haptic_config;

static bool haptic_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t           last_update = 0;
    split_slave_haptic_sync_t haptic_sync;

    memcpy(&haptic_sync.haptic_config, &haptic_config, sizeof(haptic_config_t));
    haptic_sync.haptic_play = split_haptic_play;

    bool okay = send_if_data_mismatch(PUT_HAPTIC, &last_update, &haptic_sync, &split_shmem->haptic_sync, sizeof(haptic_sync));

    split_haptic_play = 0xFF;

    return okay;
}

static void haptic_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    memcpy(&haptic_config, &split_shmem->haptic_sync.haptic_config, sizeof(haptic_config_t));

    if (split_shmem->haptic_sync.haptic_play != 0xFF) {
        haptic_set_mode(split_shmem->haptic_sync.haptic_play);
        haptic_play();
    }
}

// clang-format off
#    define TRANSACTIONS_HAPTIC_MASTER() TRANSACTION_HANDLER_MASTER(haptic)
#    define TRANSACTIONS_HAPTIC_SLAVE() TRANSACTION_HANDLER_SLAVE(haptic)
#    define TRANSACTIONS_HAPTIC_REGISTRATIONS [PUT_HAPTIC] = trans_initiator2target_initializer(haptic_sync),
// clang-format on

#else // defined(HAPTIC_ENABLE) && defined(SPLIT_HAPTIC_ENABLE)

#    define TRANSACTIONS_HAPTIC_MASTER()
#    define TRANSACTIONS_HAPTIC_SLAVE()
#    define TRANSACTIONS_HAPTIC_REGISTRATIONS

#endif // defined(HAPTIC_ENABLE) && defined(SPLIT_HAPTIC_ENABLE)

#if defined(SPLIT_ACTIVITY_ENABLE)

static bool activity_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t             last_update = 0;
    split_slave_activity_sync_t activity_sync;
    activity_sync.matrix_timestamp          = last_matrix_activity_time();
    activity_sync.encoder_timestamp         = last_encoder_activity_time();
    activity_sync.pointing_device_timestamp = last_pointing_device_activity_time();
    return send_if_data_mismatch(PUT_ACTIVITY, &last_update, &activity_sync, &split_shmem->activity_sync, sizeof(activity_sync));
}

static void activity_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    set_activity_timestamps(split_shmem->activity_sync.matrix_timestamp, split_shmem->activity_sync.encoder_timestamp, split_shmem->activity_sync.pointing_device_timestamp);
}

// clang-format off
#    define TRANSACTIONS_ACTIVITY_MASTER() TRANSACTION_HANDLER_MASTER(activity)
#    define TRANSACTIONS_ACTIVITY_SLAVE() TRANSACTION_HANDLER_SLAVE_AUTOLOCK(activity)
#    define TRANSACTIONS_ACTIVITY_REGISTRATIONS [PUT_ACTIVITY] = trans_initiator2target_initializer(activity_sync),
// clang-format on

#else // defined(SPLIT_ACTIVITY_ENABLE)

#    define TRANSACTIONS_ACTIVITY_MASTER()
#    define TRANSACTIONS_ACTIVITY_SLAVE()
#    define TRANSACTIONS_ACTIVITY_REGISTRATIONS

#endif // defined(SPLIT_ACTIVITY_ENABLE)

////////////////////////////////////////////////////
// Detected OS

#if defined(OS_DETECTION_ENABLE) && defined(SPLIT_DETECTED_OS_ENABLE)

static bool detected_os_handlers_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    static uint32_t last_detected_os_update = 0;
    os_variant_t    detected_os             = detected_host_os();
    bool            okay                    = send_if_condition(PUT_DETECTED_OS, &last_detected_os_update, (detected_os != split_shmem->detected_os), &detected_os, sizeof(os_variant_t));
    return okay;
}

static void detected_os_handlers_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    slave_update_detected_host_os(split_shmem->detected_os);
}

#    define TRANSACTIONS_DETECTED_OS_MASTER() TRANSACTION_HANDLER_MASTER(detected_os)
#    define TRANSACTIONS_DETECTED_OS_SLAVE() TRANSACTION_HANDLER_SLAVE_AUTOLOCK(detected_os)
#    define TRANSACTIONS_DETECTED_OS_REGISTRATIONS [PUT_DETECTED_OS] = trans_initiator2target_initializer(detected_os),

#else // defined(OS_DETECTION_ENABLE) && defined(SPLIT_DETECTED_OS_ENABLE)

#    define TRANSACTIONS_DETECTED_OS_MASTER()
#    define TRANSACTIONS_DETECTED_OS_SLAVE()
#    define TRANSACTIONS_DETECTED_OS_REGISTRATIONS

#endif // defined(OS_DETECTION_ENABLE) && defined(SPLIT_DETECTED_OS_ENABLE)

////////////////////////////////////////////////////

split_transaction_desc_t split_transaction_table[NUM_TOTAL_TRANSACTIONS] = {
    // Set defaults
    [0 ...(NUM_TOTAL_TRANSACTIONS - 1)] = {0, 0, 0, 0, 0},

#ifdef USE_I2C
    [I2C_EXECUTE_CALLBACK] = trans_initiator2target_initializer(transaction_id),
#endif // USE_I2C

    // clang-format off
    TRANSACTIONS_SLAVE_MATRIX_REGISTRATIONS
    TRANSACTIONS_MASTER_MATRIX_REGISTRATIONS
    TRANSACTIONS_ENCODERS_REGISTRATIONS
    TRANSACTIONS_SYNC_TIMER_REGISTRATIONS
    TRANSACTIONS_LAYER_STATE_REGISTRATIONS
    TRANSACTIONS_LED_STATE_REGISTRATIONS
    TRANSACTIONS_MODS_REGISTRATIONS
    TRANSACTIONS_BACKLIGHT_REGISTRATIONS
    TRANSACTIONS_RGBLIGHT_REGISTRATIONS
    TRANSACTIONS_LED_MATRIX_REGISTRATIONS
    TRANSACTIONS_RGB_MATRIX_REGISTRATIONS
    TRANSACTIONS_WPM_REGISTRATIONS
    TRANSACTIONS_OLED_REGISTRATIONS
    TRANSACTIONS_ST7565_REGISTRATIONS
    TRANSACTIONS_POINTING_REGISTRATIONS
    TRANSACTIONS_WATCHDOG_REGISTRATIONS
    TRANSACTIONS_HAPTIC_REGISTRATIONS
    TRANSACTIONS_ACTIVITY_REGISTRATIONS
    TRANSACTIONS_DETECTED_OS_REGISTRATIONS
// clang-format on

#if defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)
        [PUT_RPC_INFO]  = trans_initiator2target_initializer_cb(rpc_info, slave_rpc_info_callback),
    [PUT_RPC_REQ_DATA]  = trans_initiator2target_initializer(rpc_m2s_buffer),
    [EXECUTE_RPC]       = trans_initiator2target_initializer_cb(rpc_info.payload.transaction_id, slave_rpc_exec_callback),
    [GET_RPC_RESP_DATA] = trans_target2initiator_initializer(rpc_s2m_buffer),
#endif // defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)
};

bool transactions_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    TRANSACTIONS_SLAVE_MATRIX_MASTER();
    TRANSACTIONS_MASTER_MATRIX_MASTER();
    TRANSACTIONS_ENCODERS_MASTER();
    TRANSACTIONS_SYNC_TIMER_MASTER();
    TRANSACTIONS_LAYER_STATE_MASTER();
    TRANSACTIONS_LED_STATE_MASTER();
    TRANSACTIONS_MODS_MASTER();
    TRANSACTIONS_BACKLIGHT_MASTER();
    TRANSACTIONS_RGBLIGHT_MASTER();
    TRANSACTIONS_LED_MATRIX_MASTER();
    TRANSACTIONS_RGB_MATRIX_MASTER();
    TRANSACTIONS_WPM_MASTER();
    TRANSACTIONS_OLED_MASTER();
    TRANSACTIONS_ST7565_MASTER();
    TRANSACTIONS_POINTING_MASTER();
    TRANSACTIONS_WATCHDOG_MASTER();
    TRANSACTIONS_HAPTIC_MASTER();
    TRANSACTIONS_ACTIVITY_MASTER();
    TRANSACTIONS_DETECTED_OS_MASTER();
    return true;
}

void transactions_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    TRANSACTIONS_SLAVE_MATRIX_SLAVE();
    TRANSACTIONS_MASTER_MATRIX_SLAVE();
    TRANSACTIONS_ENCODERS_SLAVE();
    TRANSACTIONS_SYNC_TIMER_SLAVE();
    TRANSACTIONS_LAYER_STATE_SLAVE();
    TRANSACTIONS_LED_STATE_SLAVE();
    TRANSACTIONS_MODS_SLAVE();
    TRANSACTIONS_BACKLIGHT_SLAVE();
    TRANSACTIONS_RGBLIGHT_SLAVE();
    TRANSACTIONS_LED_MATRIX_SLAVE();
    TRANSACTIONS_RGB_MATRIX_SLAVE();
    TRANSACTIONS_WPM_SLAVE();
    TRANSACTIONS_OLED_SLAVE();
    TRANSACTIONS_ST7565_SLAVE();
    TRANSACTIONS_POINTING_SLAVE();
    TRANSACTIONS_WATCHDOG_SLAVE();
    TRANSACTIONS_HAPTIC_SLAVE();
    TRANSACTIONS_ACTIVITY_SLAVE();
    TRANSACTIONS_DETECTED_OS_SLAVE();
}

#if defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)

void transaction_register_rpc(int8_t transaction_id, slave_callback_t callback) {
    // Prevent invoking RPC on QMK core sync data
    if (transaction_id <= GET_RPC_RESP_DATA) return;

    // Set the callback
    split_transaction_table[transaction_id].slave_callback          = callback;
    split_transaction_table[transaction_id].initiator2target_offset = offsetof(split_shared_memory_t, rpc_m2s_buffer);
    split_transaction_table[transaction_id].target2initiator_offset = offsetof(split_shared_memory_t, rpc_s2m_buffer);
}

bool transaction_rpc_exec(int8_t transaction_id, uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    // Prevent transaction attempts while transport is disconnected
    if (!is_transport_connected()) {
        return false;
    }
    // Prevent invoking RPC on QMK core sync data
    if (transaction_id <= GET_RPC_RESP_DATA) return false;
    // Prevent sizing issues
    if (initiator2target_buffer_size > RPC_M2S_BUFFER_SIZE) return false;
    if (target2initiator_buffer_size > RPC_S2M_BUFFER_SIZE) return false;

    // Prepare the metadata block
    rpc_sync_info_t info = {.payload = {.transaction_id = transaction_id, .m2s_length = initiator2target_buffer_size, .s2m_length = target2initiator_buffer_size}};
    info.checksum        = crc8(&info.payload, sizeof(info.payload));

    // Make sure the local side knows that we're not sending the full block of data
    split_transaction_table[PUT_RPC_REQ_DATA].initiator2target_buffer_size  = initiator2target_buffer_size;
    split_transaction_table[GET_RPC_RESP_DATA].target2initiator_buffer_size = target2initiator_buffer_size;

    // Run through the sequence:
    // * set the transaction ID and lengths
    // * send the request data
    // * execute RPC callback
    // * retrieve the response data
    if (!transport_write(PUT_RPC_INFO, &info, sizeof(info))) {
        return false;
    }
    if (!transport_write(PUT_RPC_REQ_DATA, initiator2target_buffer, initiator2target_buffer_size)) {
        return false;
    }
    if (!transport_write(EXECUTE_RPC, &transaction_id, sizeof(transaction_id))) {
        return false;
    }
    if (!transport_read(GET_RPC_RESP_DATA, target2initiator_buffer, target2initiator_buffer_size)) {
        return false;
    }
    return true;
}

void slave_rpc_info_callback(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    // The RPC info block contains the intended transaction ID, as well as the sizes for both inbound and outbound data.
    // Ignore the args -- the `split_shmem` already has the info, we just need to act upon it.
    // We must keep the `split_transaction_table` non-const, so that it is able to be modified at runtime.

    split_transaction_table[PUT_RPC_REQ_DATA].initiator2target_buffer_size  = split_shmem->rpc_info.payload.m2s_length;
    split_transaction_table[GET_RPC_RESP_DATA].target2initiator_buffer_size = split_shmem->rpc_info.payload.s2m_length;
}

void slave_rpc_exec_callback(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    // We can assume that the buffer lengths are correctly set, now, given that sequentially the rpc_info callback was already executed.
    // Go through the rpc_info and execute _that_ transaction's callback, with the scratch buffers as inputs.
    // As a safety precaution we check that the received payload matches its checksum first.
    if (crc8(&split_shmem->rpc_info.payload, sizeof(split_shmem->rpc_info.payload)) != split_shmem->rpc_info.checksum) {
        return;
    }

    int8_t transaction_id = split_shmem->rpc_info.payload.transaction_id;
    if (transaction_id < NUM_TOTAL_TRANSACTIONS) {
        split_transaction_desc_t *trans = &split_transaction_table[transaction_id];
        if (trans->slave_callback) {
            trans->slave_callback(split_shmem->rpc_info.payload.m2s_length, split_shmem->rpc_m2s_buffer, split_shmem->rpc_info.payload.s2m_length, split_shmem->rpc_s2m_buffer);
        }
    }
}

#endif // defined(SPLIT_TRANSACTION_IDS_KB) || defined(SPLIT_TRANSACTION_IDS_USER)
