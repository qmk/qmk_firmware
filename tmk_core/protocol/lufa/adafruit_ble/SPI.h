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

#pragma once

#include <stdlib.h>

#ifndef LSBFIRST
#    define LSBFIRST 0
#endif
#ifndef MSBFIRST
#    define MSBFIRST 1
#endif

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_MODE_MASK 0x0C     // CPOL = bit 3, CPHA = bit 2 on SPCR
#define SPI_CLOCK_MASK 0x03    // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01  // SPI2X = bit 0 on SPSR

// define SPI_AVR_EIMSK for AVR boards with external interrupt pins
#if defined(EIMSK)
#    define SPI_AVR_EIMSK EIMSK
#elif defined(GICR)
#    define SPI_AVR_EIMSK GICR
#elif defined(GIMSK)
#    define SPI_AVR_EIMSK GIMSK
#endif

class SPISettings {
   public:
    SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
        if (__builtin_constant_p(clock)) {
            init_AlwaysInline(clock, bitOrder, dataMode);
        } else {
            init_MightInline(clock, bitOrder, dataMode);
        }
    }
    SPISettings() { init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0); }

   private:
    void init_MightInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) { init_AlwaysInline(clock, bitOrder, dataMode); }
    void init_AlwaysInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) __attribute__((__always_inline__)) {
        // Clock settings are defined as follows. Note that this shows SPI2X
        // inverted, so the bits form increasing numbers. Also note that
        // fosc/64 appears twice
        // SPR1 SPR0 ~SPI2X Freq
        //   0    0     0   fosc/2
        //   0    0     1   fosc/4
        //   0    1     0   fosc/8
        //   0    1     1   fosc/16
        //   1    0     0   fosc/32
        //   1    0     1   fosc/64
        //   1    1     0   fosc/64
        //   1    1     1   fosc/128

        // We find the fastest clock that is less than or equal to the
        // given clock rate. The clock divider that results in clock_setting
        // is 2 ^^ (clock_div + 1). If nothing is slow enough, we'll use the
        // slowest (128 == 2 ^^ 7, so clock_div = 6).
        uint8_t clockDiv;

        // When the clock is known at compiletime, use this if-then-else
        // cascade, which the compiler knows how to completely optimize
        // away. When clock is not known, use a loop instead, which generates
        // shorter code.
        if (__builtin_constant_p(clock)) {
            if (clock >= F_CPU / 2) {
                clockDiv = 0;
            } else if (clock >= F_CPU / 4) {
                clockDiv = 1;
            } else if (clock >= F_CPU / 8) {
                clockDiv = 2;
            } else if (clock >= F_CPU / 16) {
                clockDiv = 3;
            } else if (clock >= F_CPU / 32) {
                clockDiv = 4;
            } else if (clock >= F_CPU / 64) {
                clockDiv = 5;
            } else {
                clockDiv = 6;
            }
        } else {
            uint32_t clockSetting = F_CPU / 2;
            clockDiv              = 0;
            while (clockDiv < 6 && clock < clockSetting) {
                clockSetting /= 2;
                clockDiv++;
            }
        }

        // Compensate for the duplicate fosc/64
        if (clockDiv == 6) clockDiv = 7;

        // Invert the SPI2X bit
        clockDiv ^= 0x1;

        // Pack into the SPISettings class
        spcr = _BV(SPE) | _BV(MSTR) | ((bitOrder == LSBFIRST) ? _BV(DORD) : 0) | (dataMode & SPI_MODE_MASK) | ((clockDiv >> 1) & SPI_CLOCK_MASK);
        spsr = clockDiv & SPI_2XCLOCK_MASK;
    }
    uint8_t spcr;
    uint8_t spsr;
    friend class SPIClass;
};

class SPIClass {
   public:
    // Initialize the SPI library
    static void begin();

    // Note: the usingInterrupt and notUsingInterrupt functions should
    // not to be called from ISR context or inside a transaction.
    // For details see:
    // https://github.com/arduino/Arduino/pull/2381
    // https://github.com/arduino/Arduino/pull/2449

    // Before using SPI.transfer() or asserting chip select pins,
    // this function is used to gain exclusive access to the SPI bus
    // and configure the correct settings.
    inline static void beginTransaction(SPISettings settings) {
        SPCR = settings.spcr;
        SPSR = settings.spsr;
    }

    // Write to the SPI bus (MOSI pin) and also receive (MISO pin)
    inline static uint8_t transfer(uint8_t data) {
        SPDR = data;
        /*
         * The following NOP introduces a small delay that can prevent the wait
         * loop form iterating when running at the maximum speed. This gives
         * about 10% more speed, even if it seems counter-intuitive. At lower
         * speeds it is unnoticed.
         */
        asm volatile("nop");
        while (!(SPSR & _BV(SPIF)))
            ;  // wait
        return SPDR;
    }
    inline static uint16_t transfer16(uint16_t data) {
        union {
            uint16_t val;
            struct {
                uint8_t lsb;
                uint8_t msb;
            };
        } in, out;
        in.val = data;
        if (!(SPCR & _BV(DORD))) {
            SPDR = in.msb;
            asm volatile("nop");  // See transfer(uint8_t) function
            while (!(SPSR & _BV(SPIF)))
                ;
            out.msb = SPDR;
            SPDR    = in.lsb;
            asm volatile("nop");
            while (!(SPSR & _BV(SPIF)))
                ;
            out.lsb = SPDR;
        } else {
            SPDR = in.lsb;
            asm volatile("nop");
            while (!(SPSR & _BV(SPIF)))
                ;
            out.lsb = SPDR;
            SPDR    = in.msb;
            asm volatile("nop");
            while (!(SPSR & _BV(SPIF)))
                ;
            out.msb = SPDR;
        }
        return out.val;
    }
    inline static void transfer(void *buf, size_t count) {
        if (count == 0) return;
        uint8_t *p = (uint8_t *)buf;
        SPDR       = *p;
        while (--count > 0) {
            uint8_t out = *(p + 1);
            while (!(SPSR & _BV(SPIF)))
                ;
            uint8_t in = SPDR;
            SPDR       = out;
            *p++       = in;
        }
        while (!(SPSR & _BV(SPIF)))
            ;
        *p = SPDR;
    }
    // After performing a group of transfers and releasing the chip select
    // signal, this function allows others to access the SPI bus
    inline static void endTransaction(void) {}

    // Disable the SPI bus
    static void end();

    // These undocumented functions should not be used.  SPI.transfer()
    // polls the hardware flag which is automatically cleared as the
    // AVR responds to SPI's interrupt
    inline static void attachInterrupt() { SPCR |= _BV(SPIE); }
    inline static void detachInterrupt() { SPCR &= ~_BV(SPIE); }

   private:
    static uint8_t initialized;
};

extern SPIClass SPI;
