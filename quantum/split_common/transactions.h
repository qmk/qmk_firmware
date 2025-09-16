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

#include <stdint.h>
#include <stdbool.h>

#include "matrix.h"
#include "transaction_id_define.h"
#include "transport.h"

typedef void (*slave_callback_t)(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);

// Split transaction Descriptor
typedef struct _split_transaction_desc_t {
    uint8_t          initiator2target_buffer_size;
    uint16_t         initiator2target_offset;
    uint8_t          target2initiator_buffer_size;
    uint16_t         target2initiator_offset;
    slave_callback_t slave_callback;
} split_transaction_desc_t;

// Forward declaration for the split transactions
extern split_transaction_desc_t split_transaction_table[NUM_TOTAL_TRANSACTIONS];

#define split_shmem_offset_ptr(offset) (((uint8_t *)split_shmem) + (offset))
#define split_trans_initiator2target_buffer(trans) (split_shmem_offset_ptr((trans)->initiator2target_offset))
#define split_trans_target2initiator_buffer(trans) (split_shmem_offset_ptr((trans)->target2initiator_offset))

// returns false if valid data not received from slave
bool transactions_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]);
void transactions_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]);

void transaction_register_rpc(int8_t transaction_id, slave_callback_t callback);

bool transaction_rpc_exec(int8_t transaction_id, uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);

#define transaction_rpc_send(transaction_id, initiator2target_buffer_size, initiator2target_buffer) transaction_rpc_exec(transaction_id, initiator2target_buffer_size, initiator2target_buffer, 0, NULL)
#define transaction_rpc_recv(transaction_id, target2initiator_buffer_size, target2initiator_buffer) transaction_rpc_exec(transaction_id, 0, NULL, target2initiator_buffer_size, target2initiator_buffer)
