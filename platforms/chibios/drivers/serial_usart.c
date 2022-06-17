// Copyright 2021 QMK
// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include "serial_usart.h"
#include "synchronization_util.h"

#if defined(SERIAL_USART_CONFIG)
static QMKSerialConfig serial_config = SERIAL_USART_CONFIG;
#else
static QMKSerialConfig serial_config = {
#    if HAL_USE_SERIAL
    .speed = (SERIAL_USART_SPEED), /* baudrate - mandatory */
#    else
    .baud = (SERIAL_USART_SPEED), /* baudrate - mandatory */
#    endif
    .cr1   = (SERIAL_USART_CR1),
    .cr2   = (SERIAL_USART_CR2),
#    if !defined(SERIAL_USART_FULL_DUPLEX)
    .cr3   = ((SERIAL_USART_CR3) | USART_CR3_HDSEL) /* activate half-duplex mode */
#    else
    .cr3  = (SERIAL_USART_CR3)
#    endif
};
#endif

static QMKSerialDriver* serial_driver = (QMKSerialDriver*)&SERIAL_USART_DRIVER;

static inline bool react_to_transactions(void);
static inline bool __attribute__((nonnull)) receive(uint8_t* destination, const size_t size);
static inline bool __attribute__((nonnull)) receive_blocking(uint8_t* destination, const size_t size);
static inline bool __attribute__((nonnull)) send(const uint8_t* source, const size_t size);
static inline bool initiate_transaction(uint8_t sstd_index);
static inline void usart_clear(void);
static inline void usart_driver_start(void);

#if HAL_USE_SERIAL

/**
 * @brief SERIAL Driver startup routine.
 */
static inline void usart_driver_start(void) {
    sdStart(serial_driver, &serial_config);
}

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

#elif HAL_USE_SIO

void clear_rx_evt_cb(SIODriver* siop) {
    osalSysLockFromISR();
    /* If errors occured during transactions this callback is invoked. We just
     * clear the error sources and move on. We rely on the fact that we check
     * for the success of the transaction by comparing the received/send bytes
     * with the actual received/send bytes in the send/receive functions. */
    sioGetAndClearEventsI(serial_driver);
    osalSysUnlockFromISR();
}

static const SIOOperation serial_usart_operation = {.rx_cb = NULL, .rx_idle_cb = NULL, .tx_cb = NULL, .tx_end_cb = NULL, .rx_evt_cb = &clear_rx_evt_cb};

/**
 * @brief SIO Driver startup routine.
 */
static inline void usart_driver_start(void) {
    sioStart(serial_driver, &serial_config);
    sioStartOperation(serial_driver, &serial_usart_operation);
}

/**
 * @brief Clear the receive input queue, as some MCUs have built-in hardware FIFOs.
 */
static inline void usart_clear(void) {
    osalSysLock();
    while (!sioIsRXEmptyX(serial_driver)) {
        (void)sioGetX(serial_driver);
    }
    osalSysUnlock();
}

#else

#    error Either the SERIAL or SIO driver has to be activated to use the usart driver for split keyboards.

#endif

/**
 * @brief Blocking send of buffer with timeout.
 *
 * @return true Send success.
 * @return false Send failed.
 */
static inline bool send(const uint8_t* source, const size_t size) {
    bool success = (size_t)chnWriteTimeout(serial_driver, source, size, TIME_MS2I(SERIAL_USART_TIMEOUT)) == size;

#if !defined(SERIAL_USART_FULL_DUPLEX)
    /* Half duplex fills the input queue with the data we wrote - just throw it away. */
    if (likely(success)) {
        size_t bytes_left = size;
#    if HAL_USE_SERIAL
        /* The SERIAL driver uses large soft FIFOs that are filled from an IRQ
         * context, so there is a delay between receiving the data and it
         * becoming actually available, therefore we have to apply a timeout
         * mechanism. Under the right circumstances (e.g. bad cables paired with
         * high baud rates) less bytes can be present in the input queue as
         * well. */
        uint8_t dump[64];

        while (unlikely(bytes_left >= 64)) {
            if (unlikely(!receive(dump, 64))) {
                return false;
            }
            bytes_left -= 64;
        }

        return receive(dump, bytes_left);
#    else
        /* The SIO driver directly accesses the hardware FIFOs of the USART
         * peripheral. As these are limited in depth, the RX FIFO might have been
         * overflowed by a large that we just send. Therefore we attempt to read
         * back all the data we send or until the FIFO runs empty in case it
         * overflowed and data was truncated. */
        if (unlikely(sioSynchronizeTXEnd(serial_driver, TIME_MS2I(SERIAL_USART_TIMEOUT)) < MSG_OK)) {
            return false;
        }

        osalSysLock();
        while (bytes_left > 0 && !sioIsRXEmptyX(serial_driver)) {
            (void)sioGetX(serial_driver);
            bytes_left--;
        }
        osalSysUnlock();
#    endif
    }
#endif

    return success;
}

/**
 * @brief  Blocking receive of size * bytes with timeout.
 *
 * @return true Receive success.
 * @return false Receive failed, e.g. by timeout.
 */
static inline bool receive(uint8_t* destination, const size_t size) {
    bool success = (size_t)chnReadTimeout(serial_driver, destination, size, TIME_MS2I(SERIAL_USART_TIMEOUT)) == size;
    return success;
}

/**
 * @brief  Blocking receive of size * bytes.
 *
 * @return true Receive success.
 * @return false Receive failed.
 */
static inline bool receive_blocking(uint8_t* destination, const size_t size) {
    bool success = (size_t)chnRead(serial_driver, destination, size) == size;
    return success;
}

#if !defined(SERIAL_USART_FULL_DUPLEX)

/**
 * @brief Initiate pins for USART peripheral. Half-duplex configuration.
 */
__attribute__((weak)) void usart_init(void) {
#    if defined(MCU_STM32)
#        if defined(USE_GPIOV1)
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE_OPENDRAIN);
#        else
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_TX_PAL_MODE) | PAL_OUTPUT_TYPE_OPENDRAIN);
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
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE_PUSHPULL);
    palSetLineMode(SERIAL_USART_RX_PIN, PAL_MODE_INPUT);
#        else
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_TX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
    palSetLineMode(SERIAL_USART_RX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_RX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
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
__attribute__((weak, nonnull)) void usart_master_init(QMKSerialDriver** driver) {
    (void)driver;
    usart_init();
}

/**
 * @brief Overridable slave specific initializations.
 */
__attribute__((weak, nonnull)) void usart_slave_init(QMKSerialDriver** driver) {
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
        if (unlikely(!react_to_transactions())) {
            /* Clear the receive queue, to start with a clean slate.
             * Parts of failed transactions or spurious bytes could still be in it. */
            usart_clear();
        }
        split_shared_memory_unlock();
    }
}

/**
 * @brief Slave specific initializations.
 */
void soft_serial_target_init(void) {
    usart_slave_init(&serial_driver);

    usart_driver_start();

    /* Start transport thread. */
    chThdCreateStatic(waSlaveThread, sizeof(waSlaveThread), HIGHPRIO, SlaveThread, NULL);
}

/**
 * @brief React to transactions started by the master.
 */
static inline bool react_to_transactions(void) {
    /* Wait until there is a transaction for us. */
    uint8_t sstd_index = 0;
    receive_blocking(&sstd_index, sizeof(sstd_index));

    /* Sanity check that we are actually responding to a valid transaction. */
    if (unlikely(sstd_index >= NUM_TOTAL_TRANSACTIONS)) {
        return false;
    }

    split_shared_memory_lock();
    split_transaction_desc_t* trans = &split_transaction_table[sstd_index];

    /* Send back the handshake which is XORed as a simple checksum,
     to signal that the slave is ready to receive possible transaction buffers  */
    sstd_index ^= HANDSHAKE_MAGIC;
    if (unlikely(!send(&sstd_index, sizeof(sstd_index)))) {
        return false;
    }

    /* Receive transaction buffer from the master. If this transaction requires it.*/
    if (trans->initiator2target_buffer_size) {
        if (unlikely(!receive(split_trans_initiator2target_buffer(trans), trans->initiator2target_buffer_size))) {
            return false;
        }
    }

    /* Allow any slave processing to occur. */
    if (trans->slave_callback) {
        trans->slave_callback(trans->initiator2target_buffer_size, split_trans_initiator2target_buffer(trans), trans->initiator2target_buffer_size, split_trans_target2initiator_buffer(trans));
    }

    /* Send transaction buffer to the master. If this transaction requires it. */
    if (trans->target2initiator_buffer_size) {
        if (unlikely(!send(split_trans_target2initiator_buffer(trans), trans->target2initiator_buffer_size))) {
            return false;
        }
    }

    return true;
}

/**
 * @brief Master specific initializations.
 */
void soft_serial_initiator_init(void) {
    usart_master_init(&serial_driver);

#if defined(MCU_STM32) && defined(SERIAL_USART_PIN_SWAP)
    serial_config.cr2 |= USART_CR2_SWAP; // master has swapped TX/RX pins
#endif

    usart_driver_start();
}

/**
 * @brief Start transaction from the master half to the slave half.
 *
 * @param index Transaction Table index of the transaction to start.
 * @return bool Indicates success of transaction.
 */
bool soft_serial_transaction(int index) {
    /* Clear the receive queue, to start with a clean slate.
     * Parts of failed transactions or spurious bytes could still be in it. */
    usart_clear();

    split_shared_memory_lock();
    bool result = initiate_transaction((uint8_t)index);
    split_shared_memory_unlock();

    return result;
}

/**
 * @brief Initiate transaction to slave half.
 */
static inline bool initiate_transaction(uint8_t sstd_index) {
    /* Sanity check that we are actually starting a valid transaction. */
    if (unlikely(sstd_index >= NUM_TOTAL_TRANSACTIONS)) {
        dprintln("USART: Illegal transaction Id.");
        return false;
    }

    split_transaction_desc_t* trans = &split_transaction_table[sstd_index];

    /* Send transaction table index to the slave, which doubles as basic handshake token. */
    if (unlikely(!send(&sstd_index, sizeof(sstd_index)))) {
        dprintln("USART: Send Handshake failed.");
        return false;
    }

    uint8_t sstd_index_shake = 0xFF;

    /* Which we always read back first so that we can error out correctly.
     *   - due to the half duplex limitations on return codes, we always have to read *something*.
     *   - without the read, write only transactions *always* succeed, even during the boot process where the slave is not ready.
     */
    if (unlikely(!receive(&sstd_index_shake, sizeof(sstd_index_shake)) || (sstd_index_shake != (sstd_index ^ HANDSHAKE_MAGIC)))) {
        dprintln("USART: Handshake failed.");
        return false;
    }

    /* Send transaction buffer to the slave. If this transaction requires it. */
    if (trans->initiator2target_buffer_size) {
        if (unlikely(!send(split_trans_initiator2target_buffer(trans), trans->initiator2target_buffer_size))) {
            dprintln("USART: Send failed.");
            return false;
        }
    }

    /* Receive transaction buffer from the slave. If this transaction requires it. */
    if (trans->target2initiator_buffer_size) {
        if (unlikely(!receive(split_trans_target2initiator_buffer(trans), trans->target2initiator_buffer_size))) {
            dprintln("USART: Receive failed.");
            return false;
        }
    }

    return true;
}
