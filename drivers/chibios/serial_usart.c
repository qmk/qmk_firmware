#include "quantum.h"
#include "serial.h"
#include "printf.h"

#include "ch.h"
#include "hal.h"

#ifndef USE_GPIOV1
// The default PAL alternate modes are used to signal that the pins are used for USART
#    ifndef SERIAL_USART_TX_PAL_MODE
#        define SERIAL_USART_TX_PAL_MODE 7
#    endif
#endif

#ifndef SERIAL_USART_DRIVER
#    define SERIAL_USART_DRIVER SD1
#endif

#ifndef SELECT_SOFT_SERIAL_SPEED
#    define SELECT_SOFT_SERIAL_SPEED 1
#endif

#ifdef SERIAL_USART_SPEED
// Allow advanced users to directly set SERIAL_USART_SPEED
#elif SELECT_SOFT_SERIAL_SPEED == 0
#    define SERIAL_USART_SPEED 230400
#elif SELECT_SOFT_SERIAL_SPEED == 1
#    define SERIAL_USART_SPEED 115200
#elif SELECT_SOFT_SERIAL_SPEED == 2
#    define SERIAL_USART_SPEED 57600
#elif SELECT_SOFT_SERIAL_SPEED == 3
#    define SERIAL_USART_SPEED 38400
#elif SELECT_SOFT_SERIAL_SPEED == 4
#    define SERIAL_USART_SPEED 19200
#elif SELECT_SOFT_SERIAL_SPEED == 5
#    define SERIAL_USART_SPEED 14400
#else
#    error invalid SELECT_SOFT_SERIAL_SPEED value
#endif

#ifndef SERIAL_USART_CR1
#    define SERIAL_USART_CR1 (USART_CR1_PCE | USART_CR1_PS | USART_CR1_M0)  // parity enable, odd parity, 9 bit length
#endif

#ifndef SERIAL_USART_CR2
#    define SERIAL_USART_CR2 (USART_CR2_STOP_1)  // 2 stop bits
#endif

#ifndef SERIAL_USART_CR3
#    define SERIAL_USART_CR3 0
#endif

#define TIMEOUT 100
#define HANDSHAKE_MAGIC 7

static inline void sdClear(SerialDriver* driver) {
    while (sdGetTimeout(driver, TIME_IMMEDIATE) != MSG_TIMEOUT) {
        // Do nothing with the data
    }
}

static inline msg_t sdWriteTimeoutHalfDuplex(SerialDriver* driver, uint8_t* data, uint8_t size, uint32_t timeout) {
    msg_t ret = sdWriteTimeout(driver, data, size, timeout);

    // Half duplex requires us to read back the data we just wrote - just throw it away
    uint8_t dump[size];
    sdReadTimeout(driver, dump, size, timeout);

    return ret;
}

static inline msg_t sdWriteHalfDuplex(SerialDriver* driver, uint8_t* data, uint8_t size) {
    msg_t ret = sdWrite(driver, data, size);

    // Half duplex requires us to read back the data we just wrote - just throw it away
    uint8_t dump[size];
    sdRead(driver, dump, size);

    return ret;
}

static const SerialConfig sdcfg = {
    (SERIAL_USART_SPEED),                 // speed - mandatory
    (SERIAL_USART_CR1),                   // CR1
    (SERIAL_USART_CR2),                   // CR2
    (SERIAL_USART_CR3) | USART_CR3_HDSEL  // CR3
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

void usart_init(void) {
    sdStart(&SERIAL_USART_DRIVER, &sdcfg);

#if defined(USE_GPIOV1)
    palSetPadMode(PAL_PORT(SOFT_SERIAL_PIN), PAL_PAD(SOFT_SERIAL_PIN), PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
#else
    palSetPadMode(PAL_PORT(SOFT_SERIAL_PIN), PAL_PAD(SOFT_SERIAL_PIN), PAL_MODE_ALTERNATE(SERIAL_USART_TX_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
#endif
}

void usart_slave_init(void) {
    usart_init();

    // Start transport thread
    chThdCreateStatic(waSlaveThread, sizeof(waSlaveThread), HIGHPRIO, SlaveThread, NULL);
}

static SSTD_t* Transaction_table      = NULL;
static uint8_t Transaction_table_size = 0;

void soft_serial_initiator_init(SSTD_t* sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;

    usart_init();
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
    sdWriteHalfDuplex(&SERIAL_USART_DRIVER, &sstd_index, sizeof(sstd_index));

    if (trans->initiator2target_buffer_size) {
        sdRead(&SERIAL_USART_DRIVER, trans->initiator2target_buffer, trans->initiator2target_buffer_size);
    }

    if (trans->target2initiator_buffer_size) {
        sdWriteHalfDuplex(&SERIAL_USART_DRIVER, trans->target2initiator_buffer, trans->target2initiator_buffer_size);
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
    sdWriteTimeoutHalfDuplex(&SERIAL_USART_DRIVER, &sstd_index, sizeof(sstd_index), TIME_MS2I(TIMEOUT));

    uint8_t sstd_index_shake = 0xFF;

    // Which we always read back first so that we can error out correctly
    //   - due to the half duplex limitations on return codes, we always have to read *something*
    //   - without the read, write only transactions *always* succeed, even during the boot process where the slave is not ready
    res = sdReadTimeout(&SERIAL_USART_DRIVER, &sstd_index_shake, sizeof(sstd_index_shake), TIME_MS2I(TIMEOUT));
    if (res < 0 || (sstd_index_shake != (sstd_index ^ HANDSHAKE_MAGIC))) {
        dprintf("serial::usart_shake NO_RESPONSE\n");
        return TRANSACTION_NO_RESPONSE;
    }

    if (trans->initiator2target_buffer_size) {
        res = sdWriteTimeoutHalfDuplex(&SERIAL_USART_DRIVER, trans->initiator2target_buffer, trans->initiator2target_buffer_size, TIME_MS2I(TIMEOUT));
        if (res < 0) {
            dprintf("serial::usart_transmit NO_RESPONSE\n");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    if (trans->target2initiator_buffer_size) {
        res = sdReadTimeout(&SERIAL_USART_DRIVER, trans->target2initiator_buffer, trans->target2initiator_buffer_size, TIME_MS2I(TIMEOUT));
        if (res < 0) {
            dprintf("serial::usart_receive NO_RESPONSE\n");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    return TRANSACTION_END;
}
