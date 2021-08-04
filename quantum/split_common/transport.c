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
#include <debug.h>

#include "transactions.h"
#include "transport.h"
#include "transaction_id_define.h"
#include "atomic_util.h"

// Max number of consecutive failed communications (one per scan cycle) before the communication is seen as disconnected.
// Set to a negative value to disable the disconnection check altogether.
#ifndef SPLIT_MAX_CONNECTION_ERRORS
#    define SPLIT_MAX_CONNECTION_ERRORS 10
#endif  // SPLIT_MAX_CONNECTION_ERRORS

// How long (in milliseconds) to block all connection attempts after the communication has been flagged as disconnected.
// One communication attempt will be allowed everytime this amount of time has passed since the last attempt. If that attempt succeeds, the communication is seen as working again.
#ifndef SPLIT_CONNECTION_CHECK_TIMEOUT
#    define SPLIT_CONNECTION_CHECK_TIMEOUT 500
#endif  // SPLIT_CONNECTION_CHECK_TIMEOUT

static uint8_t connection_errors = 0;

#ifdef USE_I2C

#    ifndef SLAVE_I2C_TIMEOUT
#        define SLAVE_I2C_TIMEOUT 100
#    endif  // SLAVE_I2C_TIMEOUT

#    ifndef SLAVE_I2C_ADDRESS
#        define SLAVE_I2C_ADDRESS 0x32
#    endif

#    include "i2c_master.h"
#    include "i2c_slave.h"

// Ensure the I2C buffer has enough space
_Static_assert(sizeof(split_shared_memory_t) <= I2C_SLAVE_REG_COUNT, "split_shared_memory_t too large for I2C_SLAVE_REG_COUNT");

split_shared_memory_t *const split_shmem = (split_shared_memory_t *)i2c_slave_reg;

void transport_master_init(void) { i2c_init(); }
void transport_slave_init(void) { i2c_slave_init(SLAVE_I2C_ADDRESS); }

i2c_status_t transport_trigger_callback(int8_t id) {
    // If there's no callback, indicate that we were successful
    if (!split_transaction_table[id].slave_callback) {
        return I2C_STATUS_SUCCESS;
    }

    // Kick off the "callback executor", now that data has been written to the slave
    split_shmem->transaction_id     = id;
    split_transaction_desc_t *trans = &split_transaction_table[I2C_EXECUTE_CALLBACK];
    return i2c_writeReg(SLAVE_I2C_ADDRESS, trans->initiator2target_offset, split_trans_initiator2target_buffer(trans), trans->initiator2target_buffer_size, SLAVE_I2C_TIMEOUT);
}

bool transport_execute_transaction(int8_t id, const void *initiator2target_buf, uint16_t initiator2target_length, void *target2initiator_buf, uint16_t target2initiator_length) {
    i2c_status_t              status;
    split_transaction_desc_t *trans = &split_transaction_table[id];
    if (initiator2target_length > 0) {
        size_t len = trans->initiator2target_buffer_size < initiator2target_length ? trans->initiator2target_buffer_size : initiator2target_length;
        memcpy(split_trans_initiator2target_buffer(trans), initiator2target_buf, len);
        if ((status = i2c_writeReg(SLAVE_I2C_ADDRESS, trans->initiator2target_offset, split_trans_initiator2target_buffer(trans), len, SLAVE_I2C_TIMEOUT)) < 0) {
            return false;
        }
    }

    // If we need to execute a callback on the slave, do so
    if ((status = transport_trigger_callback(id)) < 0) {
        return false;
    }

    if (target2initiator_length > 0) {
        size_t len = trans->target2initiator_buffer_size < target2initiator_length ? trans->target2initiator_buffer_size : target2initiator_length;
        if ((status = i2c_readReg(SLAVE_I2C_ADDRESS, trans->target2initiator_offset, split_trans_target2initiator_buffer(trans), len, SLAVE_I2C_TIMEOUT)) < 0) {
            return false;
        }
        memcpy(target2initiator_buf, split_trans_target2initiator_buffer(trans), len);
    }

    return true;
}

#else  // USE_I2C

#    include "serial.h"

static split_shared_memory_t shared_memory;
split_shared_memory_t *const split_shmem = &shared_memory;

void transport_master_init(void) { soft_serial_initiator_init(); }
void transport_slave_init(void) { soft_serial_target_init(); }

bool transport_execute_transaction(int8_t id, const void *initiator2target_buf, uint16_t initiator2target_length, void *target2initiator_buf, uint16_t target2initiator_length) {
    split_transaction_desc_t *trans = &split_transaction_table[id];
    if (initiator2target_length > 0) {
        size_t len = trans->initiator2target_buffer_size < initiator2target_length ? trans->initiator2target_buffer_size : initiator2target_length;
        memcpy(split_trans_initiator2target_buffer(trans), initiator2target_buf, len);
    }

    if (soft_serial_transaction(id) != TRANSACTION_END) {
        return false;
    }

    if (target2initiator_length > 0) {
        size_t len = trans->target2initiator_buffer_size < target2initiator_length ? trans->target2initiator_buffer_size : target2initiator_length;
        memcpy(target2initiator_buf, split_trans_target2initiator_buffer(trans), len);
    }

    return true;
}

#endif  // USE_I2C

bool is_transport_connected(void) { return connection_errors < SPLIT_MAX_CONNECTION_ERRORS; }

bool transport_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
#if SPLIT_MAX_CONNECTION_ERRORS < 0
    return transactions_master(master_matrix, slave_matrix);
#else   // SPLIT_MAX_CONNECTION_ERRORS < 0
    // Throttle transaction attempts if target doesn't seem to be connected
    // Without this, a solo half becomes unusable due to constant read timeouts
    static uint16_t connection_check_timer = 0;
    if (!is_transport_connected() && timer_elapsed(connection_check_timer) < SPLIT_CONNECTION_CHECK_TIMEOUT) {
        return false;
    }

    if (!transactions_master(master_matrix, slave_matrix)) {
        if (connection_errors < UINT8_MAX) {
            connection_errors++;
        }
        if (!is_transport_connected()) {
            connection_check_timer = timer_read();
            dprintln("Target disconnected, throttling connection attempts");
        }
        return false;
    } else if (!is_transport_connected()) {
        dprintln("Target connected");
    }

    connection_errors = 0;
    return true;
#endif  // SPLIT_MAX_CONNECTION_ERRORS < 0
}

void transport_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) { transactions_slave(master_matrix, slave_matrix); }
