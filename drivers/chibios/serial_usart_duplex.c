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

#include <stdatomic.h>

#if !defined(USE_GPIOV1)
// The default PAL alternate modes are used to signal that the pins are used for USART
#    if !defined(SERIAL_USART_TX_PAL_MODE)
#        define SERIAL_USART_TX_PAL_MODE 7
#    endif
#    if !defined(SERIAL_USART_RX_PAL_MODE)
#        define SERIAL_USART_RX_PAL_MODE 7
#    endif
#endif

#if !defined(SERIAL_USART_DRIVER)
#    define SERIAL_USART_DRIVER UARTD1
#endif

#if !defined(SERIAL_USART_TX_PIN)
#    define SERIAL_USART_TX_PIN A9
#endif

#if !defined(SERIAL_USART_RX_PIN)
#    define SERIAL_USART_RX_PIN A10
#endif

#define SIGNAL_HANDSHAKE_RECEIVED 0x1

void        handle_transactions_slave(uint8_t sstd_index);
static void receive_transaction_handshake(UARTDriver* uartp, uint16_t received_handshake);

/*
 * UART driver configuration structure. We use the blocking DMA enabled API and
 * the rxchar callback to receive handshake tokens but only on the slave halve.
 */
// clang-format off
static UARTConfig uart_config = {
    .txend1_cb = NULL,
    .txend2_cb = NULL,
    .rxend_cb = NULL,
    .rxchar_cb = NULL,
    .rxerr_cb = NULL,
    .timeout_cb = NULL,
    .speed = (SERIAL_USART_SPEED),
    .cr1 = (SERIAL_USART_CR1),
    .cr2 = (SERIAL_USART_CR2),
    .cr3 = (SERIAL_USART_CR3)
};
// clang-format on

static SSTD_t*              Transaction_table      = NULL;
static uint8_t              Transaction_table_size = 0;
static atomic_uint_least8_t handshake              = 0xFF;
static thread_reference_t   tp_target              = NULL;

/*
 * This callback is invoked when a character is received but the application
 * was not ready to receive it, the character is passed as parameter.
 * Receive transaction table index from initiator, which doubles as basic handshake token. */
static void receive_transaction_handshake(UARTDriver* uartp, uint16_t received_handshake) {
    /* Check if received handshake is not a valid transaction id.
     * Please note that we can still catch a seemingly valid handshake
     * i.e. a byte from a ongoing transfer which is in the allowed range.
     * So this check mainly prevents any obviously wrong handshakes and
     * subsequent wakeups of the receiving thread, which is a costly operation. */
    if (received_handshake > Transaction_table_size) {
        return;
    }

    handshake = (uint8_t)received_handshake;
    chSysLockFromISR();
    /* Wakeup receiving thread to start a transaction. */
    chEvtSignalI(tp_target, (eventmask_t)SIGNAL_HANDSHAKE_RECEIVED);
    chSysUnlockFromISR();
}

__attribute__((weak)) void usart_init(void) {
#if defined(USE_GPIOV1)
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetLineMode(SERIAL_USART_RX_PIN, PAL_MODE_INPUT);
#else
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_TX_PAL_MODE) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(SERIAL_USART_RX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_RX_PAL_MODE) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
#endif
}

/*
 * This thread runs on the slave half and reacts to transactions initiated from the master.
 */
static THD_WORKING_AREA(waSlaveThread, 1024);
static THD_FUNCTION(SlaveThread, arg) {
    (void)arg;
    chRegSetThreadName("slave_usart_tx_rx");

    while (true) {
        /* We sleep as long as there is no handshake waiting for us. */
        chEvtWaitAny((eventmask_t)SIGNAL_HANDSHAKE_RECEIVED);
        handle_transactions_slave(handshake);
    }
}

void soft_serial_target_init(SSTD_t* const sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;
    usart_init();

#if defined(USART_REMAP)
    USART_REMAP;
#endif

    tp_target = chThdCreateStatic(waSlaveThread, sizeof(waSlaveThread), HIGHPRIO, SlaveThread, NULL);

    // Start receiving handshake tokens on slave halve
    uart_config.rxchar_cb = receive_transaction_handshake;
    uartStart(&SERIAL_USART_DRIVER, &uart_config);
}

/**
 * @brief React to transactions started by the master.
 * This version uses duplex send and receive usart pheriphals and DMA backed transfers.
 */
void inline handle_transactions_slave(uint8_t sstd_index) {
    size_t  buffer_size = 0;
    msg_t   msg         = 0;
    SSTD_t* trans       = &Transaction_table[sstd_index];

    /* Send back the handshake which is XORed as a simple checksum,
     to signal that the slave is ready to receive possible transaction buffers  */
    sstd_index ^= HANDSHAKE_MAGIC;
    buffer_size = (size_t)sizeof(sstd_index);
    msg         = uartSendTimeout(&SERIAL_USART_DRIVER, &buffer_size, &sstd_index, TIME_MS2I(SERIAL_USART_TIMEOUT));

    if (msg != MSG_OK) {
        if (trans->status) {
            *trans->status = TRANSACTION_NO_RESPONSE;
        }
        return;
    }

    /* Receive transaction buffer from the master. If this transaction requires it.*/
    buffer_size = (size_t)trans->initiator2target_buffer_size;
    if (buffer_size) {
        msg = uartReceiveTimeout(&SERIAL_USART_DRIVER, &buffer_size, trans->initiator2target_buffer, TIME_MS2I(SERIAL_USART_TIMEOUT));
        if (msg != MSG_OK) {
            if (trans->status) {
                *trans->status = TRANSACTION_NO_RESPONSE;
            }
            return;
        }
    }

    /* Send transaction buffer to the master. If this transaction requires it. */
    buffer_size = (size_t)trans->target2initiator_buffer_size;
    if (buffer_size) {
        msg = uartSendFullTimeout(&SERIAL_USART_DRIVER, &buffer_size, trans->target2initiator_buffer, TIME_MS2I(SERIAL_USART_TIMEOUT));
        if (msg != MSG_OK) {
            if (trans->status) {
                *trans->status = TRANSACTION_NO_RESPONSE;
            }
            return;
        }
    }

    if (trans->status) {
        *trans->status = TRANSACTION_ACCEPTED;
    }
}

void soft_serial_initiator_init(SSTD_t* const sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;
    usart_init();

#if defined(SERIAL_USART_PIN_SWAP)
    uart_config.cr2 |= USART_CR2_SWAP;  // master has swapped TX/RX pins
#endif

#if defined(USART_REMAP)
    USART_REMAP;
#endif

    uartStart(&SERIAL_USART_DRIVER, &uart_config);
}

/**
 * @brief Start transaction from the master to the slave.
 * This version uses duplex send and receive usart pheriphals and DMA backed transfers.
 *
 * @param index Transaction Table index of the transaction to start.
 * @return int TRANSACTION_NO_RESPONSE in case of Timeout.
 *             TRANSACTION_TYPE_ERROR in case of invalid transaction index.
 *             TRANSACTION_END in case of success.
 */
#if !defined(SERIAL_USE_MULTI_TRANSACTION)
int soft_serial_transaction(void) {
    uint8_t sstd_index = 0;
#else
int soft_serial_transaction(int index) {
    uint8_t sstd_index = index;
#endif

    if (sstd_index > Transaction_table_size) {
        return TRANSACTION_TYPE_ERROR;
    }

    SSTD_t* const trans       = &Transaction_table[sstd_index];
    msg_t         msg         = 0;
    size_t        buffer_size = (size_t)sizeof(sstd_index);

    /* Send transaction table index to the slave, which doubles as basic handshake token. */
    uartSendFullTimeout(&SERIAL_USART_DRIVER, &buffer_size, &sstd_index, TIME_MS2I(SERIAL_USART_TIMEOUT));

    uint8_t sstd_index_shake = 0xFF;
    buffer_size              = (size_t)sizeof(sstd_index_shake);

    /* Receive the handshake token from the slave. The token was XORed by the slave as a simple checksum.
     If the tokens match, the master will start to send and receive possible transaction buffers. */
    msg = uartReceiveTimeout(&SERIAL_USART_DRIVER, &buffer_size, &sstd_index_shake, TIME_MS2I(SERIAL_USART_TIMEOUT));
    if (msg != MSG_OK || (sstd_index_shake != (sstd_index ^ HANDSHAKE_MAGIC))) {
        dprintln("USART: Handshake Failed");
        return TRANSACTION_NO_RESPONSE;
    }

    /* Send transaction buffer to the slave. If this transaction requires it. */
    buffer_size = (size_t)trans->initiator2target_buffer_size;
    if (buffer_size) {
        msg = uartSendFullTimeout(&SERIAL_USART_DRIVER, &buffer_size, trans->initiator2target_buffer, TIME_MS2I(SERIAL_USART_TIMEOUT));
        if (msg != MSG_OK) {
            dprintln("USART: Send Failed");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    /* Receive transaction buffer from the slave. If this transaction requires it. */
    buffer_size = (size_t)trans->target2initiator_buffer_size;
    if (buffer_size) {
        msg = uartReceiveTimeout(&SERIAL_USART_DRIVER, &buffer_size, trans->target2initiator_buffer, TIME_MS2I(SERIAL_USART_TIMEOUT));
        if (msg != MSG_OK) {
            dprintln("USART: Receive Failed");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    return TRANSACTION_END;
}
