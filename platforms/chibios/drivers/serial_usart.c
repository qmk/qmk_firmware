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

#if defined(SERIAL_USART_CONFIG)
static SerialConfig serial_config = SERIAL_USART_CONFIG;
#else
static SerialConfig serial_config = {
    .speed = (SERIAL_USART_SPEED), /* speed - mandatory */
    .cr1   = (SERIAL_USART_CR1),
    .cr2   = (SERIAL_USART_CR2),
#    if !defined(SERIAL_USART_FULL_DUPLEX)
    .cr3   = ((SERIAL_USART_CR3) | USART_CR3_HDSEL) /* activate half-duplex mode */
#    else
    .cr3 = (SERIAL_USART_CR3)
#    endif
};
#endif

static SerialDriver* serial_driver = &SERIAL_USART_DRIVER;

static inline bool react_to_transactions(void);
static inline bool __attribute__((nonnull)) receive(uint8_t* destination, const size_t size);
static inline bool __attribute__((nonnull)) send(const uint8_t* source, const size_t size);
static inline int  initiate_transaction(uint8_t sstd_index);
static inline void usart_clear(void);

/**
 * @brief Clear the receive input queue.
 */
static inline void usart_clear(void) {
    osalSysLock();
    bool volatile queue_not_empty = !iqIsEmptyI(&serial_driver->iqueue);
    osalSysUnlock();

    while (queue_not_empty) {
        osalSysLock();
        /* Hard reset the input queue. */
        iqResetI(&serial_driver->iqueue);
        osalSysUnlock();
        /* Allow pending interrupts to preempt.
         * Do not merge the lock/unlock blocks into one
         * or the code will not work properly.
         * The empty read adds a tiny amount of delay. */
        (void)queue_not_empty;
        osalSysLock();
        queue_not_empty = !iqIsEmptyI(&serial_driver->iqueue);
        osalSysUnlock();
    }
}

/**
 * @brief Blocking send of buffer with timeout.
 *
 * @return true Send success.
 * @return false Send failed.
 */
static inline bool send(const uint8_t* source, const size_t size) {
    bool success = (size_t)sdWriteTimeout(serial_driver, source, size, TIME_MS2I(SERIAL_USART_TIMEOUT)) == size;

#if !defined(SERIAL_USART_FULL_DUPLEX)
    if (success) {
        /* Half duplex fills the input queue with the data we wrote - just throw it away.
           Under the right circumstances (e.g. bad cables paired with high baud rates)
           less bytes can be present in the input queue, therefore a timeout is needed. */
        uint8_t dump[size];
        return receive(dump, size);
    }
#endif

    return success;
}

/**
 * @brief  Blocking receive of size * bytes with timeout.
 *
 * @return true Receive success.
 * @return false Receive failed.
 */
static inline bool receive(uint8_t* destination, const size_t size) {
    bool success = (size_t)sdReadTimeout(serial_driver, destination, size, TIME_MS2I(SERIAL_USART_TIMEOUT)) == size;
    return success;
}

#if !defined(SERIAL_USART_FULL_DUPLEX)

/**
 * @brief Initiate pins for USART peripheral. Half-duplex configuration.
 */
__attribute__((weak)) void usart_init(void) {
#    if defined(MCU_STM32)
#        if defined(USE_GPIOV1)
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
#        else
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_TX_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
#        endif

#        if defined(USART_REMAP)
    USART_REMAP;
#        endif
#    else
#        pragma message "usart_init: MCU Familiy not supported by default, please supply your own init code by implementing usart_init() in your keyboard files."
#    endif
}

#else

/**
 * @brief Initiate pins for USART peripheral. Full-duplex configuration.
 */
__attribute__((weak)) void usart_init(void) {
#    if defined(MCU_STM32)
#        if defined(USE_GPIOV1)
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetLineMode(SERIAL_USART_RX_PIN, PAL_MODE_INPUT);
#        else
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_TX_PAL_MODE) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(SERIAL_USART_RX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_RX_PAL_MODE) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
#        endif

#        if defined(USART_REMAP)
    USART_REMAP;
#        endif
#    else
#        pragma message "usart_init: MCU Familiy not supported by default, please supply your own init code by implementing usart_init() in your keyboard files."
#    endif
}

#endif

/**
 * @brief Overridable master specific initializations.
 */
__attribute__((weak, nonnull)) void usart_master_init(SerialDriver** driver) {
    (void)driver;
    usart_init();
}

/**
 * @brief Overridable slave specific initializations.
 */
__attribute__((weak, nonnull)) void usart_slave_init(SerialDriver** driver) {
    (void)driver;
    usart_init();
}

/**
 * @brief This thread runs on the slave and responds to transactions initiated
 * by the master.
 */
static THD_WORKING_AREA(waSlaveThread, 1024);
static THD_FUNCTION(SlaveThread, arg) {
    (void)arg;
    chRegSetThreadName("usart_tx_rx");

    while (true) {
        if (!react_to_transactions()) {
            /* Clear the receive queue, to start with a clean slate.
             * Parts of failed transactions or spurious bytes could still be in it. */
            usart_clear();
        }
    }
}

/**
 * @brief Slave specific initializations.
 */
void soft_serial_target_init(void) {
    usart_slave_init(&serial_driver);

    sdStart(serial_driver, &serial_config);

    /* Start transport thread. */
    chThdCreateStatic(waSlaveThread, sizeof(waSlaveThread), HIGHPRIO, SlaveThread, NULL);
}

/**
 * @brief React to transactions started by the master.
 */
static inline bool react_to_transactions(void) {
    /* Wait until there is a transaction for us. */
    uint8_t sstd_index = (uint8_t)sdGet(serial_driver);

    /* Sanity check that we are actually responding to a valid transaction. */
    if (sstd_index >= NUM_TOTAL_TRANSACTIONS) {
        return false;
    }

    split_transaction_desc_t* trans = &split_transaction_table[sstd_index];

    /* Send back the handshake which is XORed as a simple checksum,
     to signal that the slave is ready to receive possible transaction buffers  */
    sstd_index ^= HANDSHAKE_MAGIC;
    if (!send(&sstd_index, sizeof(sstd_index))) {
        *trans->status = TRANSACTION_DATA_ERROR;
        return false;
    }

    /* Receive transaction buffer from the master. If this transaction requires it.*/
    if (trans->initiator2target_buffer_size) {
        if (!receive(split_trans_initiator2target_buffer(trans), trans->initiator2target_buffer_size)) {
            *trans->status = TRANSACTION_DATA_ERROR;
            return false;
        }
    }

    /* Allow any slave processing to occur. */
    if (trans->slave_callback) {
        trans->slave_callback(trans->initiator2target_buffer_size, split_trans_initiator2target_buffer(trans), trans->initiator2target_buffer_size, split_trans_target2initiator_buffer(trans));
    }

    /* Send transaction buffer to the master. If this transaction requires it. */
    if (trans->target2initiator_buffer_size) {
        if (!send(split_trans_target2initiator_buffer(trans), trans->target2initiator_buffer_size)) {
            *trans->status = TRANSACTION_DATA_ERROR;
            return false;
        }
    }

    *trans->status = TRANSACTION_ACCEPTED;
    return true;
}

/**
 * @brief Master specific initializations.
 */
void soft_serial_initiator_init(void) {
    usart_master_init(&serial_driver);

#if defined(MCU_STM32) && defined(SERIAL_USART_PIN_SWAP)
    serial_config.cr2 |= USART_CR2_SWAP;  // master has swapped TX/RX pins
#endif

    sdStart(serial_driver, &serial_config);
}

/**
 * @brief Start transaction from the master half to the slave half.
 *
 * @param index Transaction Table index of the transaction to start.
 * @return int TRANSACTION_NO_RESPONSE in case of Timeout.
 *             TRANSACTION_TYPE_ERROR in case of invalid transaction index.
 *             TRANSACTION_END in case of success.
 */
int soft_serial_transaction(int index) {
    /* Clear the receive queue, to start with a clean slate.
     * Parts of failed transactions or spurious bytes could still be in it. */
    usart_clear();
    return initiate_transaction((uint8_t)index);
}

/**
 * @brief Initiate transaction to slave half.
 */
static inline int initiate_transaction(uint8_t sstd_index) {
    /* Sanity check that we are actually starting a valid transaction. */
    if (sstd_index >= NUM_TOTAL_TRANSACTIONS) {
        dprintln("USART: Illegal transaction Id.");
        return TRANSACTION_TYPE_ERROR;
    }

    split_transaction_desc_t* trans = &split_transaction_table[sstd_index];

    /* Transaction is not registered. Abort. */
    if (!trans->status) {
        dprintln("USART: Transaction not registered.");
        return TRANSACTION_TYPE_ERROR;
    }

    /* Send transaction table index to the slave, which doubles as basic handshake token. */
    if (!send(&sstd_index, sizeof(sstd_index))) {
        dprintln("USART: Send Handshake failed.");
        return TRANSACTION_TYPE_ERROR;
    }

    uint8_t sstd_index_shake = 0xFF;

    /* Which we always read back first so that we can error out correctly.
     *   - due to the half duplex limitations on return codes, we always have to read *something*.
     *   - without the read, write only transactions *always* succeed, even during the boot process where the slave is not ready.
     */
    if (!receive(&sstd_index_shake, sizeof(sstd_index_shake)) || (sstd_index_shake != (sstd_index ^ HANDSHAKE_MAGIC))) {
        dprintln("USART: Handshake failed.");
        return TRANSACTION_NO_RESPONSE;
    }

    /* Send transaction buffer to the slave. If this transaction requires it. */
    if (trans->initiator2target_buffer_size) {
        if (!send(split_trans_initiator2target_buffer(trans), trans->initiator2target_buffer_size)) {
            dprintln("USART: Send failed.");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    /* Receive transaction buffer from the slave. If this transaction requires it. */
    if (trans->target2initiator_buffer_size) {
        if (!receive(split_trans_target2initiator_buffer(trans), trans->target2initiator_buffer_size)) {
            dprintln("USART: Receive failed.");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    return TRANSACTION_END;
}
