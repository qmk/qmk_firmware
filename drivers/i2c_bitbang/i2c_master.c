/* Copyright 2021 Andrei Purdea (portions)
 * Copyright (C) 2019 Elia Ritterbusch (portions)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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

/* This library follows the convention of the AVR i2c_master library.
 * As a result addresses are expected to be already shifted (addr << 1).
 */

#include "i2c_master.h"
#include "timer.h"
#include "gpio.h"
#include "wait.h"
#include <stdbool.h>

#ifndef I2C_BITBANG_SDA_PIN
#    error "You must set I2C_BITBANG_SDA_PIN in config.h, in order to user the i2c bitbang driver"
/* Define it to something, to avoid follow-up error messages from the compiler */
#    define I2C_BITBANG_SDA_PIN 0
#endif

#ifndef I2C_BITBANG_SCL_PIN
#    error "You must set I2C_BITBANG_SCL_PIN in config.h, in order to user the i2c bitbang driver"
/* Define it to something, to avoid follow-up error messages from the compiler */
#    define I2C_BITBANG_SCL_PIN 0
#endif

#ifndef I2C_BITBANG_ENABLE_INTERNAL_PULLUPS
#    ifdef PAL_MODE_OUTPUT_OPENDRAIN
#        define INITIALISE_PIN(pin) palSetLineMode((pin), PAL_MODE_OUTPUT_OPENDRAIN)
#        define WRITE_PIN(pin, value) writePin((pin), (value))
#        define READ_PIN(pin) readPin(pin)
#    else
#        define INITIALISE_PIN(pin) setPinInput(pin)
#        define WRITE_PIN(pin, value)   \
            do {                        \
                if (value) {            \
                    setPinInput(pin);   \
                } else {                \
                    writePin((pin), 0); \
                    setPinOutput(pin);  \
                }                       \
            } while (0)
#        define READ_PIN(pin) readPin(pin)
#    endif
#else
#    if defined(PAL_STM32_MODE_OUTPUT) && defined(PAL_STM32_OTYPE_OPENDRAIN) && defined(PAL_STM32_PUPDR_PULLUP)
#        define INITIALISE_PIN(pin) palSetLineMode((pin), PAL_STM32_MODE_OUTPUT | PAL_STM32_OTYPE_OPENDRAIN | PAL_STM32_PUPDR_PULLUP)
#        define WRITE_PIN(pin, value) writePin((pin), (value))
#        define READ_PIN(pin) readPin(pin)
#    else
#        ifdef __AVR__
#            error "It's not possible to instantly switch between driving a strong 0, and input with weak pull-up enabled on AVR."
#        else
#            error "If i2c bitbang with internal pull-ups enabled is possible on this MCU, it has not yet been implemented."
#        endif
#    endif
#endif

#define I2C_BITBANG_RECOVERY_CLOCKS 9

#ifndef I2C_BITBANG_FREQUENCY_KHZ
#    if defined(I2C_BITBANG_STANDARD_MODE)
#        define I2C_BITBANG_FREQUENCY_KHZ 100
#    else
#        define I2C_BITBANG_FREQUENCY_KHZ 400
#    endif
#endif

#if (I2C_BITBANG_FREQUENCY_KHZ <= 100) && !defined(I2C_BITBANG_STANDARD_MODE)
#    define I2C_BITBANG_STANDARD_MODE
#endif

#define I2C_BITBANG_CLOCK_PERIOD_NS ((1000000 + I2C_BITBANG_FREQUENCY_KHZ - 1) / (I2C_BITBANG_FREQUENCY_KHZ))

#ifdef I2C_BITBANG_STANDARD_MODE
#    define T_HOLD_TIME_START_NS 4000
#    define T_SETUP_TIME_START_NS 4700
#    define T_SCL_CLOCK_LOW_PERIOD_NS 4700
#    define T_SCL_CLOCK_HIGH_PERIOD_NS 4000
#    define T_ACK_VALID_TIME_NS 3450
#    define T_DATA_VALID_TIME_NS 3450
#    define T_SETUP_TIME_STOP_NS 4000
#    define T_BUS_FREE_TIME 4700
#else
/* Fast mode: */
#    define T_HOLD_TIME_START_NS 600
#    define T_SETUP_TIME_START_NS 600
#    define T_SCL_CLOCK_LOW_PERIOD_NS 1300
#    define T_SCL_CLOCK_HIGH_PERIOD_NS 600
#    define T_ACK_VALID_TIME_NS 900
#    define T_DATA_VALID_TIME_NS 900
#    define T_SETUP_TIME_STOP_NS 600
#    define T_BUS_FREE_TIME 1300
#endif

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define T_SCL_CLOCK_ACTUAL_HIGH_PERIOD_NS (MAX(I2C_BITBANG_CLOCK_PERIOD_NS - T_SCL_CLOCK_LOW_PERIOD_NS, T_SCL_CLOCK_HIGH_PERIOD_NS))

#ifndef I2C_BITBANG_WAIT_NS
#    ifdef PROTOCOL_CHIBIOS
#        if (PORT_SUPPORTS_RT == FALSE) || !defined(STM32_SYSCLK)
#            warning "chSysPolledDelayX method not supported on this platform, using inaccurate delay method. Bitbang i2c will work but will be much slower."
#            define I2C_BITBANG_WAIT_NS(time) wait_us(((time) + 999) / 1000)
#        else
#            define I2C_BITBANG_WAIT_NS(time) chSysPolledDelayX(((STM32_SYSCLK + 999999) / 1000000 * (time) + 999) / 1000)
#            define TIMEOUT_START_TIME_TYPE rtcnt_t
#            define TIMEOUT_GET_COUNTER chSysGetRealtimeCounterX
#            define TIMEOUT_HAS_IT_TIMED_OUT(initcounter, timeout_ms) (((rtcnt_t)(chSysGetRealtimeCounterX() - (initcounter))) >= MS2RTC(STM32_SYSCLK, timeout_ms))
#            define USE_SYSCLOCK_TIMER_FOR_CYCLE_LENGTH
#            define SCL_PERIOD_IN_SYSCLK_CYCLES ((STM32_SYSCLK + (I2C_BITBANG_FREQUENCY_KHZ * 1000) - 1) / (I2C_BITBANG_FREQUENCY_KHZ * 1000))
#        endif
#    else
#        ifdef __AVR__
#            ifndef F_CPU
#                define F_CPU 16000000
#            endif
#            define NS_TO_AVR_CYCLES(time) (((time)*1000ULL + (1000000000000ULL / F_CPU) - 1) / (1000000000000ULL / F_CPU))
#            define I2C_BITBANG_WAIT_NS(time) __builtin_avr_delay_cycles(NS_TO_AVR_CYCLES(time))
#        else
#            warning "Using inaccurate delay method. Bitbang i2c will work but will be much slower."
#            define I2C_BITBANG_WAIT_NS(time) wait_us(((time) + 999) / 1000)
#        endif
#    endif
#endif

#ifndef TIMEOUT_START_TIME_TYPE
#    define TIMEOUT_START_TIME_TYPE uint16_t
#    define TIMEOUT_GET_COUNTER timer_read
#    define TIMEOUT_HAS_IT_TIMED_OUT(initcounter, timeout_ms) (((uint16_t)(timer_read() - initcounter)) >= timeout_ms)
#endif

#define I2C_BITBANG_HARDCODED_TIMEOUT_ON_STOP_MS 20

#ifdef __AVR__
// The following is included to make the if (ARCH == ARCH_...) statements work:
#    include <LUFA/Common/Common.h>

#    define I2C_BITBANG_SDA_OUT_IO _SFR_IO_ADDR(DDRx_ADDRESS(I2C_BITBANG_SDA_PIN))
#    define I2C_BITBANG_SCL_OUT_IO _SFR_IO_ADDR(DDRx_ADDRESS(I2C_BITBANG_SCL_PIN))
#    define I2C_BITBANG_SDA_IN_IO _SFR_IO_ADDR(PINx_ADDRESS(I2C_BITBANG_SDA_PIN))
#    define I2C_BITBANG_SCL_IN_IO _SFR_IO_ADDR(PINx_ADDRESS(I2C_BITBANG_SCL_PIN))
#    define I2C_BITBANG_SDA_BIT (I2C_BITBANG_SDA_PIN & 0xf)
#    define I2C_BITBANG_SCL_BIT (I2C_BITBANG_SCL_PIN & 0xf)

/* The following instructions are 2 cycles each: */
#    if (ARCH == ARCH_AVR8)
#        define WRITE_PIN_SDA_1 "cbi %[sda_out_io_addr], %[sda_bit_num]"
#        define WRITE_PIN_SDA_0 "sbi %[sda_out_io_addr], %[sda_bit_num]"
#        define WRITE_PIN_SCL_1 "cbi %[scl_out_io_addr], %[scl_bit_num]"
#        define WRITE_PIN_SCL_0 "sbi %[scl_out_io_addr], %[scl_bit_num]"
#    elif (ARCH == ARCH_XMEGA)
/* Only 1 cycle on XMEGA */
#        define WRITE_PIN_SDA_1 "cbi %[sda_out_io_addr], %[sda_bit_num]\n\tnop"
#        define WRITE_PIN_SDA_0 "sbi %[sda_out_io_addr], %[sda_bit_num]\n\tnop"
#        define WRITE_PIN_SCL_1 "cbi %[scl_out_io_addr], %[scl_bit_num]\n\tnop"
#        define WRITE_PIN_SCL_0 "sbi %[scl_out_io_addr], %[scl_bit_num]\n\tnop"
#    else
#        error "Unknow arch"
#    endif

/* 1 cycle if not skipping. 2 cycles if skipping 1-word instruction, 3 cycles if skipping 2-word instruction */
#    define SKIP_IF_SCL_IS_0 "sbic %[scl_in_io_addr], %[scl_bit_num]"
/* 2 cycles: */
#    define READ_SCL_TO_T_FLAG "in r0, %[scl_in_io_addr]\n\tbst r0, %[scl_bit_num]"
#    define READ_SDA_PINREG_TO(register) "in " register ", %[sda_in_io_addr]"
#    define SDA_REGISTER_TO_T_FLAG(register) "bst " register ", %[sda_bit_num]"
#    define READ_SDA_TO_T_FLAG "in r0, %[sda_in_io_addr]\n\tbst r0, %[sda_bit_num]"

// clang-format off
#    define I2C_GPIO_CONSTRAINTS [sda_out_io_addr] "I" (I2C_BITBANG_SDA_OUT_IO), \
                                 [scl_out_io_addr] "I" (I2C_BITBANG_SCL_OUT_IO), \
                                 [sda_in_io_addr] "I" (I2C_BITBANG_SDA_IN_IO), \
                                 [scl_in_io_addr] "I" (I2C_BITBANG_SCL_IN_IO), \
                                 [sda_bit_num] "I" (I2C_BITBANG_SDA_BIT), \
                                 [scl_bit_num] "I" (I2C_BITBANG_SCL_BIT)
// clang-format on

#    define T_SCL_CLOCK_LOW_PERIOD_CYCLES NS_TO_AVR_CYCLES(T_SCL_CLOCK_LOW_PERIOD_NS)
#    define T_SCL_CLOCK_HIGH_PERIOD_CYCLES NS_TO_AVR_CYCLES(T_SCL_CLOCK_HIGH_PERIOD_NS)
#    define T_SCL_CLOCK_PERIOD_CYCLES ((F_CPU + (1000UL * I2C_BITBANG_FREQUENCY_KHZ) - 1) / (1000UL * I2C_BITBANG_FREQUENCY_KHZ))
#    define T_SCL_CLOCK_PADDING_CYCLES (T_SCL_CLOCK_PERIOD_CYCLES - T_SCL_CLOCK_LOW_PERIOD_CYCLES - T_SCL_CLOCK_HIGH_PERIOD_CYCLES)

#    define NOPS_0 ""
#    define NOPS_1 "nop"
#    define NOPS_2 "nop\n\tnop"
#    define NOPS_3 "nop\n\tnop\n\tnop"
#    if (ARCH == ARCH_AVR8)
#        define NOPS_4 "push r16\n\tpop r16"
#    elif (ARCH == ARCH_XMEGA)
#        define NOPS_4 "nop\n\tnop\n\tnop\n\tnop"
#    endif
#    define NOPS_5 NOPS_4 "\n\t" NOPS_1
#    define NOPS_6 NOPS_4 "\n\t" NOPS_2
#    define NOPS_7 NOPS_4 "\n\t" NOPS_3
#    define NOPS_8 NOPS_4 "\n\t" NOPS_4
#    define NOPS_9 NOPS_4 "\n\t" NOPS_4 "\n\t" NOPS_1

#    define AVR_DELAY_AMOUNT (T_SCL_CLOCK_LOW_PERIOD_CYCLES - 11)
#    define AVR_DELAY_NAME delay_scl_clock_low_period_minus_11
#    if ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 8) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 10)
#        include "define_avr_delay.inc"
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 "call delay_scl_clock_low_period_minus_11"
#    elif AVR_DELAY_AMOUNT == 9
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 NOPS_9
#    elif AVR_DELAY_AMOUNT == 8
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 NOPS_8
#    elif AVR_DELAY_AMOUNT == 7
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 NOPS_7
#    elif AVR_DELAY_AMOUNT == 6
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 NOPS_6
#    elif AVR_DELAY_AMOUNT == 5
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 NOPS_5
#    elif AVR_DELAY_AMOUNT == 4
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 NOPS_4
#    elif AVR_DELAY_AMOUNT == 3
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 NOPS_3
#    elif AVR_DELAY_AMOUNT == 2
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 NOPS_2
#    elif AVR_DELAY_AMOUNT == 1
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 NOPS_1
#    else
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11 NOPS_0
#    endif
#    undef AVR_DELAY_AMOUNT
#    undef AVR_DELAY_NAME

#    define AVR_DELAY_AMOUNT (T_SCL_CLOCK_LOW_PERIOD_CYCLES - 5)
#    define AVR_DELAY_NAME delay_scl_clock_low_period_minus_5
#    if ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 8) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 10)
#        include "define_avr_delay.inc"
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 "call delay_scl_clock_low_period_minus_5"
#    elif AVR_DELAY_AMOUNT == 9
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 NOPS_9
#    elif AVR_DELAY_AMOUNT == 8
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 NOPS_8
#    elif AVR_DELAY_AMOUNT == 7
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 NOPS_7
#    elif AVR_DELAY_AMOUNT == 6
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 NOPS_6
#    elif AVR_DELAY_AMOUNT == 5
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 NOPS_5
#    elif AVR_DELAY_AMOUNT == 4
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 NOPS_4
#    elif AVR_DELAY_AMOUNT == 3
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 NOPS_3
#    elif AVR_DELAY_AMOUNT == 2
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 NOPS_2
#    elif AVR_DELAY_AMOUNT == 1
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 NOPS_1
#    else
#        define DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5 NOPS_0
#    endif
#    undef AVR_DELAY_AMOUNT
#    undef AVR_DELAY_NAME

#    define AVR_DELAY_AMOUNT (T_SCL_CLOCK_HIGH_PERIOD_CYCLES - 3)
#    define AVR_DELAY_NAME delay_scl_clock_high_period_minus_3
#    if ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 8) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 10)
#        include "define_avr_delay.inc"
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 "call delay_scl_clock_high_period_minus_3"
#    elif AVR_DELAY_AMOUNT == 9
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 NOPS_9
#    elif AVR_DELAY_AMOUNT == 8
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 NOPS_8
#    elif AVR_DELAY_AMOUNT == 7
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 NOPS_7
#    elif AVR_DELAY_AMOUNT == 6
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 NOPS_6
#    elif AVR_DELAY_AMOUNT == 5
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 NOPS_5
#    elif AVR_DELAY_AMOUNT == 4
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 NOPS_4
#    elif AVR_DELAY_AMOUNT == 3
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 NOPS_3
#    elif AVR_DELAY_AMOUNT == 2
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 NOPS_2
#    elif AVR_DELAY_AMOUNT == 1
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 NOPS_1
#    else
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3 NOPS_0
#    endif
#    undef AVR_DELAY_AMOUNT
#    undef AVR_DELAY_NAME

#    define AVR_DELAY_AMOUNT (T_SCL_CLOCK_HIGH_PERIOD_CYCLES - 6)
#    define AVR_DELAY_NAME delay_scl_clock_high_period_minus_6
#    if ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 8) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 10)
#        include "define_avr_delay.inc"
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 "call delay_scl_clock_high_period_minus_6"
#    elif AVR_DELAY_AMOUNT == 9
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 NOPS_9
#    elif AVR_DELAY_AMOUNT == 8
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 NOPS_8
#    elif AVR_DELAY_AMOUNT == 7
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 NOPS_7
#    elif AVR_DELAY_AMOUNT == 6
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 NOPS_6
#    elif AVR_DELAY_AMOUNT == 5
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 NOPS_5
#    elif AVR_DELAY_AMOUNT == 4
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 NOPS_4
#    elif AVR_DELAY_AMOUNT == 3
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 NOPS_3
#    elif AVR_DELAY_AMOUNT == 2
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 NOPS_2
#    elif AVR_DELAY_AMOUNT == 1
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 NOPS_1
#    else
#        define DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6 NOPS_0
#    endif
#    undef AVR_DELAY_AMOUNT
#    undef AVR_DELAY_NAME

#    if (ARCH == ARCH_AVR8)
#        define AVR_DELAY_AMOUNT (T_SCL_CLOCK_PADDING_CYCLES - 3)
#    elif (ARCH == ARCH_XMEGA)
#        define AVR_DELAY_AMOUNT (T_SCL_CLOCK_PADDING_CYCLES - 4)
#    endif
#    define AVR_DELAY_NAME delay_scl_clock_padding_period_minus_3_or_4
#    if ((!defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 8) || ((defined(__AVR_3_BYTE_PC__)) && AVR_DELAY_AMOUNT >= 10)
#        include "define_avr_delay.inc"
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 "call delay_scl_clock_padding_period_minus_3_or_4"
#    elif AVR_DELAY_AMOUNT == 9
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 NOPS_9
#    elif AVR_DELAY_AMOUNT == 8
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 NOPS_8
#    elif AVR_DELAY_AMOUNT == 7
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 NOPS_7
#    elif AVR_DELAY_AMOUNT == 6
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 NOPS_6
#    elif AVR_DELAY_AMOUNT == 5
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 NOPS_5
#    elif AVR_DELAY_AMOUNT == 4
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 NOPS_4
#    elif AVR_DELAY_AMOUNT == 3
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 NOPS_3
#    elif AVR_DELAY_AMOUNT == 2
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 NOPS_2
#    elif AVR_DELAY_AMOUNT == 1
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 NOPS_1
#    else
#        define DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 NOPS_0
#    endif
#    undef AVR_DELAY_AMOUNT
#    undef AVR_DELAY_NAME

#endif

bool started       = false;
bool has_been_used = false;

static i2c_status_t i2c_try_to_recover_potentially_locked_up_bus(uint16_t timeout) {
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
    for (int i = 0; i < I2C_BITBANG_RECOVERY_CLOCKS; i++) {
        WRITE_PIN(I2C_BITBANG_SCL_PIN, 1);
        while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
            /* wait for clock stretching */
            if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
                return I2C_STATUS_TIMEOUT;
            }
        }
        I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_ACTUAL_HIGH_PERIOD_NS);
        WRITE_PIN(I2C_BITBANG_SCL_PIN, 0);
        I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_LOW_PERIOD_NS);
        if (READ_PIN(I2C_BITBANG_SDA_PIN)) {
            break;
        }
    }
    WRITE_PIN(I2C_BITBANG_SDA_PIN, 0); /* preparing for stop bit */
    I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_LOW_PERIOD_NS);
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 1);
    while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
        /* wait for clock stretching */
        if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
            return I2C_STATUS_TIMEOUT;
        }
    }
    I2C_BITBANG_WAIT_NS(T_SETUP_TIME_STOP_NS);
    WRITE_PIN(I2C_BITBANG_SDA_PIN, 1); /* stop condition final */
    I2C_BITBANG_WAIT_NS(T_BUS_FREE_TIME);
    started = false;
    return I2C_STATUS_SUCCESS;
}

void i2c_init(void) {
    INITIALISE_PIN(I2C_BITBANG_SDA_PIN);
    INITIALISE_PIN(I2C_BITBANG_SCL_PIN);
    started       = false;
    has_been_used = false;
}

inline static i2c_status_t i2c_write_raw(uint8_t databyte, uint16_t timeout, TIMEOUT_START_TIME_TYPE init_timeout_counter) __attribute__((always_inline));

static i2c_status_t i2c_write_raw(uint8_t databyte, uint16_t timeout, TIMEOUT_START_TIME_TYPE init_timeout_counter) {
#ifdef __AVR__
    uint8_t bits_left = 8;
    uint8_t ack       = 1;
restart_in_case_of_clock_stretch:
    // clang-format off
    asm goto (
            WRITE_PIN_SCL_0                             "\n\t" /* 2 cycles */
            NOPS_3                                      "\n\t" /* 3 cycles - to equalize paths */
        "1:"                                            "\n\t"
            "rol %[databyte]"                           "\n\t" /* 1 cycle */
            "brcs 2f"                                   "\n\t" /* 1 cycle if condition is false, 2 if true */
            WRITE_PIN_SDA_0                             "\n\t" /* 2 cycles */
            "rjmp 3f"                                   "\n\t" /* 2 cycles */
        "2:"                                            "\n\t"
            WRITE_PIN_SDA_1                             "\n\t" /* 2 cycles */
            "nop"                                       "\n\t" /* 1 cycle to equalize paths */
        "3:"                                            "\n\t"
            DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11         "\n\t"
            WRITE_PIN_SCL_1                             "\n\t" /* 2 cycles */
            DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 "\n\t" /* delay depends on arch (avr8 is -3, xmega is -4) */
            SKIP_IF_SCL_IS_0                            "\n\t" /* when not skipping: 1 cycle on avr8, 2 cycles on xmega. We don't care when skipping. */
            "rjmp 4f"                                   "\n\t" /* 2 cycles */
            "st %a[bits_left_pointer], %[bits_left]"    "\n\t" /* on this branch we don't care if the performance degrades. */
            "st %a[databyte_pointer], %[databyte]"      "\n\t"
            "jmp %l[maybe_timeout]"                     "\n\t"
        "4:"                                            "\n\t"
            "nop"                                       "\n\t" /* 1 cycle */
            DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3         "\n\t"
            WRITE_PIN_SCL_0                             "\n\t" /* 2 cycles */
            "dec %[bits_left]"                          "\n\t" /* 1 cycle */
            "brne 1b"                                   "\n\t" /* 2 cycles when jumping, 1 cycle when not */
            WRITE_PIN_SDA_1                             "\n\t" /* 2 cycles, release SDA for ACK */
            NOPS_5                                      "\n\t" /* 5 cycles */
            DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11         "\n\t"
            WRITE_PIN_SCL_1                             "\n\t" /* 2 cycles */
            DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 "\n\t" /* delay depends on arch (avr8 is -3, xmega is -4) */
            SKIP_IF_SCL_IS_0                            "\n\t" /* when not skipping: 1 cycle on avr8, 2 cycles on xmega. We don't care when skipping. */
            "rjmp 5f"                                   "\n\t" /* 2 cycles */
            "jmp %l[maybe_timeout_on_ack_bit]"          "\n\t" /* on this branch we don't care if the performance degrades. */
        "5:"                                            "\n\t"
            READ_SDA_PINREG_TO("r0")                    "\n\t" /* 1 cycle */
            DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3         "\n\t"
            WRITE_PIN_SCL_0                             "\n\t" /* 2 cycles */
            SDA_REGISTER_TO_T_FLAG("r0")                "\n\t"
            "eor r0, r0"                                "\n\t"
            "bld r0, 1"                                 "\n\t"
            "st %a[databyte_pointer], r0"               "\n\t" // reuse databyte as output operand
    :
    : [bits_left] "r" (bits_left),
      [databyte] "r" (databyte),
      [bits_left_pointer] "e" (&bits_left),
      [databyte_pointer] "e" (&databyte),
      I2C_GPIO_CONSTRAINTS
    : "memory", "0", "1"
    : maybe_timeout, maybe_timeout_on_ack_bit );
    // clang-format on
    ack = databyte;
    goto after_maybe_timeout;
maybe_timeout:
    while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
        /* wait for clock stretching */
        if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
            return I2C_STATUS_TIMEOUT;
        }
    }

    __builtin_avr_delay_cycles(T_SCL_CLOCK_HIGH_PERIOD_CYCLES + T_SCL_CLOCK_PADDING_CYCLES);
    bits_left--;
    if (bits_left != 0) {
        goto restart_in_case_of_clock_stretch;
    }
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 0);
    WRITE_PIN(I2C_BITBANG_SDA_PIN, 1); /* release the SDA pin to get ACK/NACK */
    __builtin_avr_delay_cycles(T_SCL_CLOCK_LOW_PERIOD_CYCLES);
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 1);
    __builtin_avr_delay_cycles(T_SCL_CLOCK_PADDING_CYCLES);
maybe_timeout_on_ack_bit:
    while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
        /* wait for clock stretching */
        if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
            return I2C_STATUS_TIMEOUT;
        }
    }
    ack = READ_PIN(I2C_BITBANG_SDA_PIN);
    __builtin_avr_delay_cycles(T_SCL_CLOCK_HIGH_PERIOD_CYCLES);
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 0);
after_maybe_timeout:
#else
#    ifdef USE_SYSCLOCK_TIMER_FOR_CYCLE_LENGTH
    TIMEOUT_START_TIME_TYPE init_cycle_counter = TIMEOUT_GET_COUNTER();
#    endif
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 0);
    for (int8_t i = 1; i <= 8; i++) {
        WRITE_PIN(I2C_BITBANG_SDA_PIN, ((databyte >> (8 - i)) & 1));
        I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_LOW_PERIOD_NS);
        WRITE_PIN(I2C_BITBANG_SCL_PIN, 1);
        while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
            /* wait for clock stretching */
            if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
                return I2C_STATUS_TIMEOUT;
            }
        }
#    ifdef USE_SYSCLOCK_TIMER_FOR_CYCLE_LENGTH
        I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_HIGH_PERIOD_NS);
        while (((TIMEOUT_START_TIME_TYPE)(TIMEOUT_GET_COUNTER() - init_cycle_counter)) < (SCL_PERIOD_IN_SYSCLK_CYCLES - 3)) {
            /* note: -3 is not architecture-specific, it comes from a fact that there's at least 3 distinct operations
             * that are not counted: substraction with underflow, comparison, and reading of a new counter value
             */
            /* wait for SCL cycle length to fill up */
        }
        init_cycle_counter = TIMEOUT_GET_COUNTER();
#    else
        I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_ACTUAL_HIGH_PERIOD_NS);
#    endif
        WRITE_PIN(I2C_BITBANG_SCL_PIN, 0);
    }
    WRITE_PIN(I2C_BITBANG_SDA_PIN, 1); /* release the SDA pin to get ACK/NACK */
    I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_LOW_PERIOD_NS);
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 1);
    while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
        /* wait for clock stretching */
        if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
            return I2C_STATUS_TIMEOUT;
        }
    }
    uint8_t ack = READ_PIN(I2C_BITBANG_SDA_PIN);
#    ifdef USE_SYSCLOCK_TIMER_FOR_CYCLE_LENGTH
    I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_HIGH_PERIOD_NS);
    while (((TIMEOUT_START_TIME_TYPE)(TIMEOUT_GET_COUNTER() - init_cycle_counter)) < (SCL_PERIOD_IN_SYSCLK_CYCLES - 2)) {
        /* note: -2 is not architecture-specific, it comes from a fact that there's at least 2 distinct operations
         * that are not counted: substraction with underflow, and comparison
         */
        /* wait for SCL cycle length to fill up */
    }
#    else
    I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_ACTUAL_HIGH_PERIOD_NS);
#    endif
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 0);
#endif
    started = true;
    if (ack != 0) return I2C_STATUS_ERROR;
    return I2C_STATUS_SUCCESS;
}

inline static i2c_status_t i2c_only_start_condition_raw(TIMEOUT_START_TIME_TYPE init_timeout_counter, uint16_t timeout) __attribute__((always_inline));

static i2c_status_t i2c_only_start_condition_raw(TIMEOUT_START_TIME_TYPE init_timeout_counter, uint16_t timeout) {
    if (!has_been_used) {
        has_been_used    = true;
        i2c_status_t ret = i2c_try_to_recover_potentially_locked_up_bus(timeout);
        if (I2C_STATUS_SUCCESS != ret) {
            return ret;
        }
    }
    if (!started) {
        if ((READ_PIN(I2C_BITBANG_SCL_PIN) == 0) || (READ_PIN(I2C_BITBANG_SDA_PIN) == 0)) {
            return I2C_STATUS_ERROR;
        }
    } else {
        /* Restart condition */
        I2C_BITBANG_WAIT_NS(MAX(T_ACK_VALID_TIME_NS, T_SCL_CLOCK_LOW_PERIOD_NS));
        if ((READ_PIN(I2C_BITBANG_SCL_PIN) != 0) || (READ_PIN(I2C_BITBANG_SDA_PIN) == 0)) {
            return I2C_STATUS_ERROR;
        }
        /* SDA pin was expected to have been released before, so it should be high */
        WRITE_PIN(I2C_BITBANG_SCL_PIN, 1);
        while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
            /* wait for clock stretching */
            if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
                return I2C_STATUS_TIMEOUT;
            }
        }
        I2C_BITBANG_WAIT_NS(T_SETUP_TIME_START_NS);
    }
    /* start condition */
    WRITE_PIN(I2C_BITBANG_SDA_PIN, 0);
    I2C_BITBANG_WAIT_NS(T_HOLD_TIME_START_NS);
    return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_start(uint8_t address, uint16_t timeout) {
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
    i2c_status_t            ret                  = i2c_only_start_condition_raw(init_timeout_counter, timeout);
    if (ret != I2C_STATUS_SUCCESS) {
        return ret;
    }
    return i2c_write_raw(address, timeout, init_timeout_counter);
}

i2c_status_t i2c_write(uint8_t data, uint16_t timeout) {
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
    return i2c_write_raw(data, timeout, init_timeout_counter);
}

inline static int16_t i2c_read_acknack_raw(uint16_t timeout, uint8_t ack) __attribute__((always_inline));
static int16_t        i2c_read_acknack_raw(uint16_t timeout, uint8_t ack) {
    uint8_t                 data                 = 0;
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
#ifdef __AVR__
    uint8_t bits_left = 8;
read_restart_in_case_of_clock_stretch:
    // clang-format off
    asm goto (
        /* At the start we can assume SCL is already zero, casue there was always at least one raw write before reading,
         * that is, at least the i2c address has been transmitted */
            WRITE_PIN_SDA_1                             "\n\t" /* 2 cycles */
            NOPS_3                                      "\n\t" /* 3 nop cycles - to equalize paths */
                                                               /* (mostly not necessary, but we can't know what creative */
                                                               /*  optimizations future GCC comes up with, so this is safer) */
        "1:"                                            "\n\t"
            DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_5          "\n\t"
            WRITE_PIN_SCL_1                             "\n\t" /* 2 cycles */
            DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 "\n\t" /* delay depends on arch (avr8 is -3, xmega is -4) */
            SKIP_IF_SCL_IS_0                            "\n\t" /* when not skipping: 1 cycle on avr8, 2 cycles on xmega. We don't care when skipping. */
            "rjmp 2f"                                   "\n\t" /* 2 cycles */
            "st %a[bits_left_pointer], %[bits_left]"    "\n\t" /* on this branch we don't care if the performance degrades. */
            "st %a[databyte_pointer], %[databyte]"      "\n\t"
            "jmp %l[read_maybe_timeout]"                "\n\t"
        "2:"                                            "\n\t"
            "lsl %[databyte]"                           "\n\t" /* 1 cycle */
            READ_SDA_TO_T_FLAG                          "\n\t" /* 2 cycles */
            "bld %[databyte], 0"                        "\n\t" /* 1 cycle */
            DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_6         "\n\t"
            WRITE_PIN_SCL_0                             "\n\t" /* 2 cycles */
            "dec %[bits_left]"                          "\n\t" /* 1 cycle */
            "brne 1b"                                   "\n\t" /* 2 cycles when jumping, 1 cycle when not */
            "tst %[ack]"                                "\n\t" /* 1 cycle */
            "brne 3f"                                   "\n\t" /* 1 cycle if condition is false, 2 if true */
            WRITE_PIN_SDA_0                             "\n\t" /* 2 cycles */
            "rjmp 4f"                                   "\n\t" /* 2 cycles */
        "3:"                                            "\n\t"
            WRITE_PIN_SDA_1                             "\n\t" /* 2 cycles */
            "nop"                                       "\n\t" /* 1 cycle to equalize paths */
        "4:"                                            "\n\t"
            DELAY_SCL_CLOCK_LOW_PERIOD_MINUS_11         "\n\t"
            "nop"                                       "\n\t" /* 1 cycle just to re-use the low-11 delay specification above */
            WRITE_PIN_SCL_1                             "\n\t" /* 2 cycles */
            DELAY_SCL_CLOCK_PADDING_PERIOD_MINUS_3_OR_4 "\n\t" /* delay depends on arch (avr8 is -3, xmega is -4) */
            SKIP_IF_SCL_IS_0                            "\n\t" /* when not skipping: 1 cycle on avr8, 2 cycles on xmega. We don't care when skipping. */
            "rjmp 5f"                                   "\n\t" /* 2 cycles */
            "st %a[databyte_pointer], %[databyte]"      "\n\t" /* on this branch we don't care if the performance degrades. */
            "jmp %l[read_maybe_timeout_on_ack_bit]"     "\n\t"
        "5:"                                            "\n\t"
            DELAY_SCL_CLOCK_HIGH_PERIOD_MINUS_3         "\n\t"
            "nop"                                       "\n\t" /* 1 cycle just to re-use the high-3 delay specification above */
            WRITE_PIN_SCL_0                             "\n\t" /* 2 cycles */
            "st %a[databyte_pointer], %[databyte]"      "\n\t"
    :
    : [bits_left] "r" (bits_left),
      [databyte] "r" (data),
      [bits_left_pointer] "e" (&bits_left),
      [databyte_pointer] "e" (&data),
      [ack] "r" (ack),
      I2C_GPIO_CONSTRAINTS
    : "memory", "0", "1"
    : read_maybe_timeout, read_maybe_timeout_on_ack_bit );
    // clang-format on
    return data;
read_maybe_timeout:
    while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
        /* wait for clock stretching */
        if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
            return I2C_STATUS_TIMEOUT;
        }
    }
    data = (data << 1) | !!READ_PIN(I2C_BITBANG_SDA_PIN);
    __builtin_avr_delay_cycles(T_SCL_CLOCK_HIGH_PERIOD_CYCLES + T_SCL_CLOCK_PADDING_CYCLES);
    bits_left--;
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 0);
    if (bits_left != 0) {
        goto read_restart_in_case_of_clock_stretch;
    }
    WRITE_PIN(I2C_BITBANG_SDA_PIN, ack); /* release the SDA pin to get ACK/NACK */
    __builtin_avr_delay_cycles(T_SCL_CLOCK_LOW_PERIOD_CYCLES);
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 1);
    __builtin_avr_delay_cycles(T_SCL_CLOCK_PADDING_CYCLES);
read_maybe_timeout_on_ack_bit:
    while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
        /* wait for clock stretching */
        if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
            return I2C_STATUS_TIMEOUT;
        }
    }
    __builtin_avr_delay_cycles(T_SCL_CLOCK_HIGH_PERIOD_CYCLES);
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 0);
    return data;
#else
    WRITE_PIN(I2C_BITBANG_SDA_PIN, 1); /* release the SDA pin so that the device can talk back */
#    ifdef USE_SYSCLOCK_TIMER_FOR_CYCLE_LENGTH
    TIMEOUT_START_TIME_TYPE init_cycle_counter = TIMEOUT_GET_COUNTER();
    /* Note: there is no write of the SCL pin after reading the counter here, but with
     * all other delays involving calling this function, and writing the SDA pin above,
     * the clock period constraint is not violated.
     */
#    endif
    for (int8_t i = 7; i >= 0; i--) {
        I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_LOW_PERIOD_NS);
        WRITE_PIN(I2C_BITBANG_SCL_PIN, 1);
        while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
            /* wait for clock stretching */
            if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
                return I2C_STATUS_TIMEOUT;
            }
        }
        data = (data << 1) | !!READ_PIN(I2C_BITBANG_SDA_PIN);
#    ifdef USE_SYSCLOCK_TIMER_FOR_CYCLE_LENGTH
        I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_HIGH_PERIOD_NS);
        while (((TIMEOUT_START_TIME_TYPE)(TIMEOUT_GET_COUNTER() - init_cycle_counter)) < (SCL_PERIOD_IN_SYSCLK_CYCLES - 3)) {
            /* note: -3 is not architecture-specific, it comes from a fact that there's at least 3 distinct operations
             * that are not counted: substraction with underflow, comparison, and reading of a new counter value
             */
            /* wait for SCL cycle length to fill up */
        }
        init_cycle_counter = TIMEOUT_GET_COUNTER();
#    else
        I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_ACTUAL_HIGH_PERIOD_NS);
#    endif
        WRITE_PIN(I2C_BITBANG_SCL_PIN, 0);
    }
    I2C_BITBANG_WAIT_NS(T_DATA_VALID_TIME_NS);
    /* Now the device must have released the SDA pin so we can respond with an ack/nack */
    if (READ_PIN(I2C_BITBANG_SDA_PIN) == 0) {
        return I2C_STATUS_ERROR;
    }
    WRITE_PIN(I2C_BITBANG_SDA_PIN, ack); /* set the desired ack value */
    I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_LOW_PERIOD_NS);
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 1);
    while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
        /* wait for clock stretching */
        if ((timeout != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, timeout)) {
            return I2C_STATUS_TIMEOUT;
        }
    }
#    ifdef USE_SYSCLOCK_TIMER_FOR_CYCLE_LENGTH
    I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_HIGH_PERIOD_NS);
    while (((TIMEOUT_START_TIME_TYPE)(TIMEOUT_GET_COUNTER() - init_cycle_counter)) < (SCL_PERIOD_IN_SYSCLK_CYCLES - 2)) {
        /* note: -2 is not architecture-specific, it comes from a fact that there's at least 2 distinct operations
         * that are not counted: substraction with underflow, and comparison
         */
        /* wait for SCL cycle length to fill up */
    }
#    else
    I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_ACTUAL_HIGH_PERIOD_NS);
#    endif
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 0);
    WRITE_PIN(I2C_BITBANG_SDA_PIN, 1); /* release the SDA pin */
    return data;
#endif
}

int16_t i2c_read_ack(uint16_t timeout) { return i2c_read_acknack_raw(timeout, 0); }

int16_t i2c_read_nack(uint16_t timeout) { return i2c_read_acknack_raw(timeout, 1); }

void i2c_stop(void) {
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
    WRITE_PIN(I2C_BITBANG_SDA_PIN, 0);
    I2C_BITBANG_WAIT_NS(T_SCL_CLOCK_LOW_PERIOD_NS);
    WRITE_PIN(I2C_BITBANG_SCL_PIN, 1);
    while (READ_PIN(I2C_BITBANG_SCL_PIN) == 0) {
        /* wait for clock stretching */
        if ((I2C_BITBANG_HARDCODED_TIMEOUT_ON_STOP_MS != I2C_TIMEOUT_INFINITE) && TIMEOUT_HAS_IT_TIMED_OUT(init_timeout_counter, I2C_BITBANG_HARDCODED_TIMEOUT_ON_STOP_MS)) {
            return;
        }
    }
    I2C_BITBANG_WAIT_NS(T_SETUP_TIME_STOP_NS);
    WRITE_PIN(I2C_BITBANG_SDA_PIN, 1);
    I2C_BITBANG_WAIT_NS(T_BUS_FREE_TIME);
    started = false;
}

i2c_status_t i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length, uint16_t timeout) {
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
    i2c_status_t            ret                  = i2c_only_start_condition_raw(init_timeout_counter, timeout);
    if (ret == I2C_STATUS_SUCCESS) {
        ret = i2c_write_raw(address | I2C_WRITE, timeout, init_timeout_counter);

        for (uint16_t i = 0; i < length && ret == I2C_STATUS_SUCCESS; i++) {
            init_timeout_counter = TIMEOUT_GET_COUNTER();
            ret                  = i2c_write_raw(data[i], timeout, init_timeout_counter);
        }
    }

    i2c_stop();
    return ret;
}

i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length, uint16_t timeout) {
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
    i2c_status_t            ret                  = i2c_only_start_condition_raw(init_timeout_counter, timeout);
    if (ret == I2C_STATUS_SUCCESS) {
        ret = i2c_write_raw(address | I2C_READ, timeout, init_timeout_counter);

        for (uint16_t i = 0; i < length && ret >= 0; i++) {
            ret = i2c_read_acknack_raw(timeout, i == (length - 1));
            if (ret >= 0) {
                data[i] = ret;
            }
        }
    }
    i2c_stop();

    return (ret < 0) ? ret : I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout) {
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
    i2c_status_t            ret                  = i2c_only_start_condition_raw(init_timeout_counter, timeout);
    if (ret == I2C_STATUS_SUCCESS) {
        ret = i2c_write_raw(devaddr | I2C_WRITE, timeout, init_timeout_counter);
        if (ret == I2C_STATUS_SUCCESS) {
            init_timeout_counter = TIMEOUT_GET_COUNTER();
            ret                  = i2c_write_raw(regaddr, timeout, init_timeout_counter);
            for (uint16_t i = 0; i < length && ret == I2C_STATUS_SUCCESS; i++) {
                init_timeout_counter = TIMEOUT_GET_COUNTER();
                ret                  = i2c_write_raw(data[i], timeout, init_timeout_counter);
            }
        }
    }

    i2c_stop();
    return ret;
}

i2c_status_t i2c_writeReg16(uint8_t devaddr, uint16_t regaddr, const uint8_t* data, uint16_t length, uint16_t timeout) {
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
    i2c_status_t            ret                  = i2c_only_start_condition_raw(init_timeout_counter, timeout);
    if (ret == I2C_STATUS_SUCCESS) {
        ret = i2c_write_raw(devaddr | I2C_WRITE, timeout, init_timeout_counter);
        if (ret == I2C_STATUS_SUCCESS) {
            init_timeout_counter = TIMEOUT_GET_COUNTER();
            ret                  = i2c_write_raw(regaddr >> 8, timeout, init_timeout_counter);
            if (ret == I2C_STATUS_SUCCESS) {
                init_timeout_counter = TIMEOUT_GET_COUNTER();
                ret                  = i2c_write_raw(regaddr & 0xff, timeout, init_timeout_counter);
                for (uint16_t i = 0; i < length && ret == I2C_STATUS_SUCCESS; i++) {
                    init_timeout_counter = TIMEOUT_GET_COUNTER();
                    ret                  = i2c_write_raw(data[i], timeout, init_timeout_counter);
                }
            }
        }
    }

    i2c_stop();
    return ret;
}

i2c_status_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) {
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
    i2c_status_t            ret                  = i2c_only_start_condition_raw(init_timeout_counter, timeout);
    if (ret != I2C_STATUS_SUCCESS) {
        goto error;
    }
    ret = i2c_write_raw(devaddr | I2C_WRITE, timeout, init_timeout_counter);
    if (ret != I2C_STATUS_SUCCESS) {
        goto error;
    }
    init_timeout_counter = TIMEOUT_GET_COUNTER();
    ret                  = i2c_write_raw(regaddr, timeout, init_timeout_counter);
    if (ret != I2C_STATUS_SUCCESS) {
        goto error;
    }
    init_timeout_counter = TIMEOUT_GET_COUNTER();
    ret                  = i2c_only_start_condition_raw(init_timeout_counter, timeout);
    if (ret != I2C_STATUS_SUCCESS) {
        goto error;
    }
    ret = i2c_write_raw(devaddr | I2C_READ, timeout, init_timeout_counter);

    for (uint16_t i = 0; i < length && ret >= 0; i++) {
        ret = i2c_read_acknack_raw(timeout, i == (length - 1));
        if (ret >= 0) {
            data[i] = ret;
        }
    }

error:
    i2c_stop();

    return (ret < 0) ? ret : I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_readReg16(uint8_t devaddr, uint16_t regaddr, uint8_t* data, uint16_t length, uint16_t timeout) {
    TIMEOUT_START_TIME_TYPE init_timeout_counter = TIMEOUT_GET_COUNTER();
    i2c_status_t            ret                  = i2c_only_start_condition_raw(init_timeout_counter, timeout);
    if (ret != I2C_STATUS_SUCCESS) {
        goto error;
    }
    ret = i2c_write_raw(devaddr | I2C_WRITE, timeout, init_timeout_counter);
    if (ret != I2C_STATUS_SUCCESS) {
        goto error;
    }
    init_timeout_counter = TIMEOUT_GET_COUNTER();
    ret                  = i2c_write_raw(regaddr >> 8, timeout, init_timeout_counter);
    if (ret != I2C_STATUS_SUCCESS) {
        goto error;
    }
    init_timeout_counter = TIMEOUT_GET_COUNTER();
    ret                  = i2c_write_raw(regaddr & 0xFF, timeout, init_timeout_counter);
    if (ret != I2C_STATUS_SUCCESS) {
        goto error;
    }
    init_timeout_counter = TIMEOUT_GET_COUNTER();
    ret                  = i2c_only_start_condition_raw(init_timeout_counter, timeout);
    if (ret != I2C_STATUS_SUCCESS) {
        goto error;
    }
    ret = i2c_write_raw(devaddr | I2C_READ, timeout, init_timeout_counter);
    for (uint16_t i = 0; i < length && ret >= 0; i++) {
        ret = i2c_read_acknack_raw(timeout, i == (length - 1));
        if (ret >= 0) {
            data[i] = ret;
        }
    }

error:
    i2c_stop();

    return (ret < 0) ? ret : I2C_STATUS_SUCCESS;
}
