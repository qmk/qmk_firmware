// Copyright 2024 QMK
// Copyright 2024 Thomas Preisner
// SPDX-License-Identifier: GPL-2.0-or-later

#include "serial_fdcan.h"
#include "serial_protocol.h"
#include "synchronization_util.h"
#include "chibios_config.h" // TODO

// TODO: decide on a proper way to define which fdcan-instance to use for
//       actual communication (FDCAN1 needs to be set for changing CKDIV_PDIV)
// TODO: limit to STM32G4xx?
#if defined(MCU_STM32)
static QMKCANConfig can_config = {
    .NBTP = FDCAN_NBTP,
    .DBTP = 0,
    // TODO: maybe reenable automatic retransmission
    .CCCR = FDCAN_CCCR_DAR | FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE,
    .TEST = 0,
    // TODO: set this field in a smart way (contains number of filters, etc)
    .RXGFC = 0,
};
#else
#    error MCU Family not supported
#endif

#if !defined(STM32_CAN_USE_FDCAN1)
#    error STM32_CAN_USE_FDCAN1 must be set to allow for driver configuration
#endif
static QMKCANDriver* can_config_device = &CAND1;
#if STM32_CAN_USE_FDCAN2
static QMKCANDriver* can_driver = &CAND2;
#elif STM32_CAN_USE_FDCAN3
static QMKCANDriver* can_driver = &CAND3;
#else
static QMKCANDriver* can_driver = &CAND1;
#endif

// TODO: use 64 bytes -> implement handling for DLC > 8
#define FDCAN_MAX_MSGSIZE 8
#define min(a, b) a < b ? a : b;

#define SERIAL_FDCAN_TIMEOUT 20

#if HAL_USE_CAN

static inline void fdcan_init(void) {
    static bool is_initialized = false;
    if (!is_initialized) {
        is_initialized = true;

        palSetPadMode(PAL_PORT(FDCAN_TX_PIN), PAL_PAD(FDCAN_TX_PIN), PAL_MODE_ALTERNATE(FDCAN_TX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        palSetPadMode(PAL_PORT(FDCAN_RX_PIN), PAL_PAD(FDCAN_RX_PIN), PAL_MODE_ALTERNATE(FDCAN_RX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);

        // configure ckdiv via fdcan1
        canStart(can_config_device, &can_config);
        canStop(can_config_device);

        canStart(can_driver, &can_config);
    }
}

static inline bool fdcan_receive(uint8_t* destination, const size_t size, sysinterval_t timeout) {
    // read length, then receive and merge transaction data packages
    CANRxFrame crf = {0};
    for (uint16_t p = 0; p * FDCAN_MAX_MSGSIZE < size; ++p) {
        msg_t res = canReceiveTimeout(can_driver, CAN_ANY_MAILBOX, &crf, timeout);
        if (res != MSG_OK) {
            return false;
        }

        uint16_t plen = min(FDCAN_MAX_MSGSIZE, size - p * FDCAN_MAX_MSGSIZE);
        if (plen != crf.DLC) {
            // most likely message order got screwed up somehow..
            // XXX: is this the right way to handle this?
            return false;
        }
        for (uint16_t i = 0; i < plen; ++i) {
            destination[i + p * FDCAN_MAX_MSGSIZE] = crf.data8[i];
        }
    }
    return true;
}
inline void serial_transport_driver_clear(void) {
    canStop(can_driver);
    canStart(can_driver, &can_config);
}

void serial_transport_driver_slave_init(void) {
    fdcan_init();
}

void serial_transport_driver_master_init(void) {
    fdcan_init();
}

inline bool serial_transport_receive(uint8_t* destination, const size_t size) {
    return fdcan_receive(destination, size, TIME_MS2I(SERIAL_FDCAN_TIMEOUT));
}

inline bool serial_transport_receive_blocking(uint8_t* destination, const size_t size) {
    return fdcan_receive(destination, size, TIME_INFINITE);
}

inline bool serial_transport_send(const uint8_t* source, const size_t size) {
    // append length and split up transaction data into smaller packages
    CANTxFrame ctf = {0};
    // TODO: actually make use of standard identifiers to allow for more than 2 "halves"
    if (is_keyboard_master()) {
        ctf.std.SID = 1;
    } else {
        ctf.std.SID = 2;
    }
    ctf.common.XTD = 0;
    ctf.FDF        = 1;

    for (uint16_t p = 0; p * FDCAN_MAX_MSGSIZE < size; ++p) {
        uint16_t sent = p * FDCAN_MAX_MSGSIZE;
        ctf.DLC       = min(FDCAN_MAX_MSGSIZE, size - sent);
        for (uint16_t i = 0; i < ctf.DLC; ++i) {
            ctf.data8[i] = source[i + sent];
        }

        msg_t res = canTransmitTimeout(can_driver, CAN_ANY_MAILBOX, &ctf, TIME_MS2I(SERIAL_FDCAN_TIMEOUT));
        if (res != MSG_OK) {
            return false;
        }
    }
    return true;
}
#endif
