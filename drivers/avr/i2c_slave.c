/*  Copyright (C) 2019 Elia Ritterbusch
 +
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
/* Library made by: g4lvanix
 * GitHub repository: https://github.com/g4lvanix/I2C-slave-lib
 */

#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#include "i2c_slave.h"

#ifdef SPLIT_COMMON_TRANSACTIONS
#    include "transactions.h"
#endif  // SPLIT_COMMON_TRANSACTIONS

volatile uint8_t i2c_slave_reg[I2C_SLAVE_REG_COUNT];

static volatile uint8_t buffer_address;
static volatile bool    slave_has_register_set = false;

#if defined(USE_I2C) && defined(SPLIT_COMMON_TRANSACTIONS)
static volatile uint8_t received_transaction_id;
#endif  // defined(USE_I2C) && defined(SPLIT_COMMON_TRANSACTIONS)

void i2c_slave_init(uint8_t address) {
    // load address into TWI address register
    TWAR = address;
    // set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
    TWCR = (1 << TWIE) | (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
}

void i2c_slave_stop(void) {
    // clear acknowledge and enable bits
    TWCR &= ~((1 << TWEA) | (1 << TWEN));
}

ISR(TWI_vect) {
    uint8_t ack = 1;

    switch (TW_STATUS) {
        case TW_SR_SLA_ACK:
            // The device is now a slave receiver
            slave_has_register_set = false;
            break;

        case TW_SR_DATA_ACK:
            // This device is a slave receiver and has received data
            // First byte is the location then the bytes will be writen in buffer with auto-increment
            if (!slave_has_register_set) {
                buffer_address = TWDR;

#if defined(USE_I2C) && defined(SPLIT_COMMON_TRANSACTIONS)
                // Work out which transaction we're executing
                received_transaction_id = NUM_TOTAL_TRANSACTIONS;
                for (int i = 0; i < NUM_TOTAL_TRANSACTIONS; ++i) {
                    split_transaction_desc_t *trans = &split_transaction_table[i];
                    if (buffer_address == trans->initiator2target_offset || buffer_address == trans->target2initiator_offset) {
                        received_transaction_id = i;
                        break;
                    }
                }
#endif  // defined(USE_I2C) && defined(SPLIT_COMMON_TRANSACTIONS)

                if (buffer_address >= I2C_SLAVE_REG_COUNT) {  // address out of bounds dont ack
                    ack            = 0;
                    buffer_address = 0;
                }
                slave_has_register_set = true;  // address has been received now fill in buffer
            } else {
                i2c_slave_reg[buffer_address] = TWDR;
                buffer_address++;

#if defined(USE_I2C) && defined(SPLIT_COMMON_TRANSACTIONS)
                // If we're intending to execute a transaction callback, do so, as we've received the transaction ID
                if (received_transaction_id == I2C_EXECUTE_CALLBACK) {
                    split_transaction_desc_t *trans = &split_transaction_table[split_shmem->transaction_id];
                    if (trans->slave_callback) {
                        trans->slave_callback(trans->initiator2target_buffer_size, split_trans_initiator2target_buffer(trans), trans->target2initiator_buffer_size, split_trans_target2initiator_buffer(trans));
                    }
                }
#endif  // defined(USE_I2C) && defined(SPLIT_COMMON_TRANSACTIONS)
            }
            break;

        case TW_ST_SLA_ACK:
        case TW_ST_DATA_ACK:
            // This device is a slave transmitter and master has requested data
            TWDR = i2c_slave_reg[buffer_address];
            buffer_address++;
            break;

        case TW_BUS_ERROR:
            // We got an error, reset i2c
            TWCR = 0;
        default:
            break;
    }

    // Reset i2c state machine to be ready for next interrupt
    TWCR |= (1 << TWIE) | (1 << TWINT) | (ack << TWEA) | (1 << TWEN);
}
