/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "serial_usart.h"

#ifndef USE_GPIOV1
// The default PAL alternate modes are used to signal that the pins are used for USART
#    ifndef SERIAL_USART_TX_PAL_MODE
#        define SERIAL_USART_TX_PAL_MODE 7
#    endif
#endif

#ifndef SERIAL_USART_DRIVER
#    define SERIAL_USART_DRIVER SD1
#endif

#ifdef SOFT_SERIAL_PIN
#    define SERIAL_USART_TX_PIN SOFT_SERIAL_PIN
#endif

static inline msg_t sdWriteHalfDuplex(SerialDriver* driver, uint8_t* data, uint8_t size) {
    msg_t ret = sdWrite(driver, data, size);

    // Half duplex requires us to read back the data we just wrote - just throw it away
    uint8_t dump[size];
    sdRead(driver, dump, size);

    return ret;
}
#undef sdWrite
#define sdWrite sdWriteHalfDuplex

static inline msg_t sdWriteTimeoutHalfDuplex(SerialDriver* driver, uint8_t* data, uint8_t size, uint32_t timeout) {
    msg_t ret = sdWriteTimeout(driver, data, size, timeout);

    // Half duplex requires us to read back the data we just wrote - just throw it away
    uint8_t dump[size];
    sdReadTimeout(driver, dump, size, timeout);

    return ret;
}
#undef sdWriteTimeout
#define sdWriteTimeout sdWriteTimeoutHalfDuplex

static inline void sdClear(SerialDriver* driver) {
    while (sdGetTimeout(driver, TIME_IMMEDIATE) != MSG_TIMEOUT) {
        // Do nothing with the data
    }
}

static SerialConfig sdcfg = {
    (SERIAL_USART_SPEED),  // speed - mandatory
    (SERIAL_USART_CR1),    // CR1
    (SERIAL_USART_CR2),    // CR2
    (SERIAL_USART_CR3)     // CR3
};

void handle_soft_serial_slave(void);

/*
 * This thread runs on the slave and responds to transactions initiated
 * by the master
 */
static THD_WORKING_AREA(waSlaveThread, 2048);
static THD_FUNCTION(SlaveThread, arg) {
    (void)arg;
    chRegSetThreadName("slave_transport");

    while (true) {
        handle_soft_serial_slave();
    }
}

__attribute__((weak)) void usart_init(void) {
#if defined(USE_GPIOV1)
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
#else
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_TX_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
#endif

#if defined(USART_REMAP)
    USART_REMAP;
#endif
}

void usart_master_init(void) {
    usart_init();

    sdcfg.cr3 |= USART_CR3_HDSEL;
    sdStart(&SERIAL_USART_DRIVER, &sdcfg);
}

void usart_slave_init(void) {
    usart_init();

    sdcfg.cr3 |= USART_CR3_HDSEL;
    sdStart(&SERIAL_USART_DRIVER, &sdcfg);

    // Start transport thread
    chThdCreateStatic(waSlaveThread, sizeof(waSlaveThread), HIGHPRIO, SlaveThread, NULL);
}

static SSTD_t* Transaction_table      = NULL;
static uint8_t Transaction_table_size = 0;

void soft_serial_initiator_init(SSTD_t* sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;

    usart_master_init();
}

void soft_serial_target_init(SSTD_t* sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;

    usart_slave_init();
}

void handle_soft_serial_slave(void) {
    uint8_t sstd_index = sdGet(&SERIAL_USART_DRIVER);  // first chunk is always transaction id
    SSTD_t* trans      = &Transaction_table[sstd_index];

    // Always write back the sstd_index as part of a basic handshake
    sstd_index ^= HANDSHAKE_MAGIC;
    sdWrite(&SERIAL_USART_DRIVER, &sstd_index, sizeof(sstd_index));

    if (trans->initiator2target_buffer_size) {
        sdRead(&SERIAL_USART_DRIVER, trans->initiator2target_buffer, trans->initiator2target_buffer_size);
    }

    if (trans->target2initiator_buffer_size) {
        sdWrite(&SERIAL_USART_DRIVER, trans->target2initiator_buffer, trans->target2initiator_buffer_size);
    }

    if (trans->status) {
        *trans->status = TRANSACTION_ACCEPTED;
    }
}

/////////
//  start transaction by initiator
//
// int  soft_serial_transaction(int sstd_index)
//
// Returns:
//    TRANSACTION_END
//    TRANSACTION_NO_RESPONSE
//    TRANSACTION_DATA_ERROR
#ifndef SERIAL_USE_MULTI_TRANSACTION
int soft_serial_transaction(void) {
    uint8_t sstd_index = 0;
#else
int soft_serial_transaction(int index) {
    uint8_t sstd_index = index;
#endif

    if (sstd_index > Transaction_table_size) return TRANSACTION_TYPE_ERROR;
    SSTD_t* trans = &Transaction_table[sstd_index];
    msg_t   res   = 0;

    sdClear(&SERIAL_USART_DRIVER);

    // First chunk is always transaction id
    sdWriteTimeout(&SERIAL_USART_DRIVER, &sstd_index, sizeof(sstd_index), TIME_MS2I(SERIAL_USART_TIMEOUT));

    uint8_t sstd_index_shake = 0xFF;

    // Which we always read back first so that we can error out correctly
    //   - due to the half duplex limitations on return codes, we always have to read *something*
    //   - without the read, write only transactions *always* succeed, even during the boot process where the slave is not ready
    res = sdReadTimeout(&SERIAL_USART_DRIVER, &sstd_index_shake, sizeof(sstd_index_shake), TIME_MS2I(SERIAL_USART_TIMEOUT));
    if (res < 0 || (sstd_index_shake != (sstd_index ^ HANDSHAKE_MAGIC))) {
        dprintf("serial::usart_shake NO_RESPONSE\n");
        return TRANSACTION_NO_RESPONSE;
    }

    if (trans->initiator2target_buffer_size) {
        res = sdWriteTimeout(&SERIAL_USART_DRIVER, trans->initiator2target_buffer, trans->initiator2target_buffer_size, TIME_MS2I(SERIAL_USART_TIMEOUT));
        if (res < 0) {
            dprintf("serial::usart_transmit NO_RESPONSE\n");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    if (trans->target2initiator_buffer_size) {
        res = sdReadTimeout(&SERIAL_USART_DRIVER, trans->target2initiator_buffer, trans->target2initiator_buffer_size, TIME_MS2I(SERIAL_USART_TIMEOUT));
        if (res < 0) {
            dprintf("serial::usart_receive NO_RESPONSE\n");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    return TRANSACTION_END;
}
