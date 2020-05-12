/*
 * Copyright (c) 2020 by Joshua Rubin
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * Copyright (c) 2014 by Matthijs Kooijman <matthijs@stdin.nl> (SPISettings AVR)
 * Copyright (c) 2014 by Andrew J. Kroll <xxxajk@gmail.com> (atomicity fixes)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "quantum.h"
#include "SPI.h"

SPIClass SPI;

uint8_t SPIClass::initialized = 0;

#if defined(__AVR_ATmega16U2__) || defined(__AVR_ATmega32U2__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega32U4__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB647__) || defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB1287__)
#    define SPI_SS_PIN B0
#    define SPI_SCK_PIN B1
#    define SPI_MOSI_PIN B2
#    define SPI_MISO_PIN B3
#elif defined(__AVR_ATmega32A__)
#    define SPI_SS_PIN B4
#    define SPI_SCK_PIN B7
#    define SPI_MOSI_PIN B5
#    define SPI_MISO_PIN B6
#elif defined(__AVR_ATmega328P__)
#    define SPI_SS_PIN B2
#    define SPI_SCK_PIN B5
#    define SPI_MOSI_PIN B3
#    define SPI_MISO_PIN B4
#endif

void SPIClass::begin() {
    uint8_t sreg = SREG;
    cli();  // Protect from a scheduler and prevent transactionBegin
    if (!initialized) {
        writePinHigh(SPI_SS_PIN);

        // When the SPI_SS_PIN pin is set as OUTPUT, it can be used as
        // a general purpose output port (it doesn't influence
        // SPI operations).
        setPinOutput(SPI_SS_PIN);

        // Warning: if the SPI_SS_PIN pin ever becomes a LOW INPUT then SPI
        // automatically switches to Slave, so the data direction of
        // the SPI_SS_PIN pin MUST be kept as OUTPUT.
        SPCR |= _BV(MSTR);
        SPCR |= _BV(SPE);

        // Set direction register for SPI_SCK_PIN and SPI_MOSI_PIN pin.
        // MISO pin automatically overrides to INPUT.
        // By doing this AFTER enabling SPI, we avoid accidentally
        // clocking in a single bit since the lines go directly
        // from "input" to SPI control.
        // http://code.google.com/p/arduino/issues/detail?id=888
        setPinOutput(SPI_SCK_PIN);
        setPinOutput(SPI_MOSI_PIN);
    }
    initialized++;  // reference count
    SREG = sreg;
}

void SPIClass::end() {
    uint8_t sreg = SREG;
    cli();  // Protect from a scheduler and prevent transactionBegin
    // Decrease the reference counter
    if (initialized) initialized--;
    // If there are no more references disable SPI
    if (!initialized) {
        SPCR &= ~_BV(SPE);
    }
    SREG = sreg;
}
