// Copyright 2021 QMK
// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include "serial_usart.h"
#include "serial_protocol.h"
#include "synchronization_util.h"
#include "chibios_config.h"

#if defined(SERIAL_USART_CONFIG)
static QMKSerialConfig serial_config = SERIAL_USART_CONFIG;
#elif defined(MCU_STM32) /* STM32 MCUs */
static QMKSerialConfig serial_config = {
#    if HAL_USE_SERIAL
    .speed = (SERIAL_USART_SPEED),
#    else
    .baud = (SERIAL_USART_SPEED),
#    endif
    .cr1   = (SERIAL_USART_CR1),
    .cr2   = (SERIAL_USART_CR2),
#    if !defined(SERIAL_USART_FULL_DUPLEX)
    .cr3   = ((SERIAL_USART_CR3) | USART_CR3_HDSEL) /* activate half-duplex mode */
#    else
    .cr3  = (SERIAL_USART_CR3)
#    endif
};
#elif defined(MCU_RP) /* Raspberry Pi MCUs */
/* USART in 8E2 config with RX and TX FIFOs enabled. */
// clang-format off
static QMKSerialConfig serial_config = {
    .baud = (SERIAL_USART_SPEED),
    .UARTLCR_H = UART_UARTLCR_H_WLEN_8BITS | UART_UARTLCR_H_PEN | UART_UARTLCR_H_STP2 | UART_UARTLCR_H_FEN,
    .UARTCR = 0U,
    .UARTIFLS = UART_UARTIFLS_RXIFLSEL_1_8F | UART_UARTIFLS_TXIFLSEL_1_8E,
    .UARTDMACR = 0U
};
// clang-format on
#else
#    error MCU Familiy not supported by default, supply your own serial_config by defining SERIAL_USART_CONFIG in your keyboard files.
#endif

static QMKSerialDriver* serial_driver = (QMKSerialDriver*)&SERIAL_USART_DRIVER;

#if HAL_USE_SERIAL

/**
 * @brief SERIAL Driver startup routine.
 */
static inline void usart_driver_start(void) {
    sdStart(serial_driver, &serial_config);
}

inline void serial_transport_driver_clear(void) {
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

/**
 * @brief SIO Driver startup routine.
 */
static inline void usart_driver_start(void) {
    sioStart(serial_driver, &serial_config);
}

inline void serial_transport_driver_clear(void) {
    if (sioHasRXErrorsX(serial_driver)) {
        sioGetAndClearErrors(serial_driver);
    }
    osalSysLock();
    while (!sioIsRXEmptyX(serial_driver)) {
        (void)sioGetX(serial_driver);
    }
    osalSysUnlock();
}

#else

#    error Either the SERIAL or SIO driver has to be activated to use the usart driver for split keyboards.

#endif

inline bool serial_transport_send(const uint8_t* source, const size_t size) {
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
            if (unlikely(!serial_transport_receive(dump, 64))) {
                return false;
            }
            bytes_left -= 64;
        }

        return serial_transport_receive(dump, bytes_left);
#    else
        /* The SIO driver directly accesses the hardware FIFOs of the USART
         * peripheral. As these are limited in depth, the RX FIFO might have
         * been overflowed by a large transaction that we just send. Therefore
         * we attempt to read back all the data we send or until the FIFO runs
         * empty in case it overflowed and data was truncated. */
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

inline bool serial_transport_receive(uint8_t* destination, const size_t size) {
    bool success = (size_t)chnReadTimeout(serial_driver, destination, size, TIME_MS2I(SERIAL_USART_TIMEOUT)) == size;
    return success;
}

inline bool serial_transport_receive_blocking(uint8_t* destination, const size_t size) {
    bool success = (size_t)chnRead(serial_driver, destination, size) == size;
    return success;
}

#if !defined(SERIAL_USART_FULL_DUPLEX)

/**
 * @brief Initiate pins for USART peripheral. Half-duplex configuration.
 */
__attribute__((weak)) void usart_init(void) {
#    if defined(MCU_STM32) /* STM32 MCUs */
#        if defined(USE_GPIOV1)
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE_OPENDRAIN);
#        else
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_TX_PAL_MODE) | PAL_OUTPUT_TYPE_OPENDRAIN);
#        endif

#        if defined(USART_REMAP)
    USART_REMAP;
#        endif
#    elif defined(MCU_RP) /* Raspberry Pi MCUs */
#        error Half-duplex with the SIO driver is not supported due to hardware limitations on the RP2040, switch to the PIO driver which has half-duplex support.
#    else
#        pragma message "usart_init: MCU Familiy not supported by default, please supply your own init code by implementing usart_init() in your keyboard files."
#    endif
}

#else

/**
 * @brief Initiate pins for USART peripheral. Full-duplex configuration.
 */
__attribute__((weak)) void usart_init(void) {
#    if defined(MCU_STM32) /* STM32 MCUs */
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
#    elif defined(MCU_RP) /* Raspberry Pi MCUs */
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE_UART);
    palSetLineMode(SERIAL_USART_RX_PIN, PAL_MODE_ALTERNATE_UART);
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

void serial_transport_driver_slave_init(void) {
    usart_slave_init(&serial_driver);
    usart_driver_start();
}

void serial_transport_driver_master_init(void) {
    usart_master_init(&serial_driver);

#if defined(MCU_STM32) && defined(SERIAL_USART_PIN_SWAP)
    serial_config.cr2 |= USART_CR2_SWAP; // master has swapped TX/RX pins
#endif

    usart_driver_start();
}
