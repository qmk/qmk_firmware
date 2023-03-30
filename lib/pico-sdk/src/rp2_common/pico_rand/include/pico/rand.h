/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_RAND_H
#define _PICO_RAND_H

#include "pico.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file pico/rand.h
 *  \defgroup pico_rand pico_rand
 *
 * Random Number Generator API
 *
 * This module generates random numbers at runtime utilizing a number of possible entropy
 * sources and uses those sources to modify the state of a 128-bit 'Pseudo
 * Random Number Generator' implemented in software.
 *
 * The random numbers (32 to 128 bit) to be supplied are read from the PRNG which is used
 * to help provide a large number space.
 *
 * The following (multiple) sources of entropy are available (of varying quality), each enabled by a #define:
 *
 *  - The Ring Oscillator (ROSC) (\ref PICO_RAND_ENTROPY_SRC_ROSC == 1):
 *    \ref PICO_RAND_ROSC_BIT_SAMPLE_COUNT bits are gathered from the ring oscillator "random bit" and mixed in each
 *    time. This should not be used if the ROSC is off, or the processor is running from
 *    the ROSC.
 *    \note the maximum throughput of ROSC bit sampling is controlled by PICO_RAND_MIN_ROSC_BIT_SAMPLE_TIME_US which defaults
 *    to 10us, i.e. 100,000 bits per second.
 *  - Time (\ref PICO_RAND_ENTROPY_SRC_TIME == 1): The 64-bit microsecond timer is mixed in each time.
 *  - Bus Performance Counter (\ref PICO_RAND_ENTROPY_SRC_BUS_PERF_COUNTER == 1): One of the bus fabric's performance
 *    counters is mixed in each time.
 *
 * \note All entropy sources are hashed before application to the PRNG state machine.
 *
 * \note The \em first time a random number is requested, the 128-bit PRNG state
 * must be seeded. Multiple entropy sources are also available for the seeding operation:
 *
 *  - The Ring Oscillator (ROSC) (\ref PICO_RAND_SEED_ENTROPY_SRC_ROSC == 1):
 *    64 bits are gathered from the ring oscillator "random bit" and mixed into the seed.
 *  - Time (\ref PICO_RAND_SEED_ENTROPY_SRC_TIME == 1): The 64-bit microsecond timer is mixed into the seed.
 *  - Board Identifier (PICO_RAND_SEED_ENTROPY_SRC_BOARD_ID == 1): The board id via \ref pico_get_unique_board_id
 *    is mixed into the seed.
 *  - RAM hash (\ref PICO_RAND_SEED_ENTROPY_SRC_RAM_HASH (\ref PICO_RAND_SEED_ENTROPY_SRC_RAM_HASH): The hashed contents of a
 *    subset of RAM are mixed in. Initial RAM contents are undefined on power up, so provide a reasonable source of entropy.
 *    By default the last 1K of RAM (which usually contains the core 0 stack) is hashed, which may also provide for differences
 *    after each warm reset.
 *
 * With default settings, the seed generation takes approximately 1 millisecond while
 * subsequent random numbers generally take between 10 and 20 microseconds to generate.
 *
 * pico_rand methods may be safely called from either core or from an IRQ, but be careful in the latter case as
 * the calls may block for a number of microseconds waiting on more entropy.
 */

// ---------------
// ENTROPY SOURCES
// ---------------

// PICO_CONFIG: PICO_RAND_ENTROPY_SRC_ROSC, Enable/disable use of ROSC as an entropy source, type=bool, default=1, group=pico_rand
#ifndef PICO_RAND_ENTROPY_SRC_ROSC
#define PICO_RAND_ENTROPY_SRC_ROSC 1
#endif

// PICO_CONFIG: PICO_RAND_ENTROPY_SRC_TIME, Enable/disable use of hardware timestamp as an entropy source, type=bool, default=1, group=pico_rand
#ifndef PICO_RAND_ENTROPY_SRC_TIME
#define PICO_RAND_ENTROPY_SRC_TIME 1
#endif

// PICO_CONFIG: PICO_RAND_ENTROPY_SRC_BUS_PERF_COUNTER, Enable/disable use of a bus performance counter as an entropy source, type=bool, default=1, group=pico_rand
#ifndef PICO_RAND_ENTROPY_SRC_BUS_PERF_COUNTER
#define PICO_RAND_ENTROPY_SRC_BUS_PERF_COUNTER 1
#endif

// --------------------
// SEED ENTROPY SOURCES
// --------------------

// PICO_CONFIG: PICO_RAND_SEED_ENTROPY_SRC_ROSC, Enable/disable use of ROSC as an entropy source for the random seed, type=bool, default=1, group=pico_rand
#ifndef PICO_RAND_SEED_ENTROPY_SRC_ROSC
#define PICO_RAND_SEED_ENTROPY_SRC_ROSC PICO_RAND_ENTROPY_SRC_ROSC
#endif

// PICO_CONFIG: PICO_RAND_SEED_ENTROPY_SRC_TIME, Enable/disable use of hardware timestamp as an entropy source for the random seed, type=bool, default=1, group=pico_rand
#ifndef PICO_RAND_SEED_ENTROPY_SRC_TIME
#define PICO_RAND_SEED_ENTROPY_SRC_TIME PICO_RAND_ENTROPY_SRC_TIME
#endif

// PICO_CONFIG: PICO_RAND_SEED_ENTROPY_SRC_BOARD_ID, Enable/disable use of board id as part of the random seed, type=bool, default=1, group=pico_rand
#ifndef PICO_RAND_SEED_ENTROPY_SRC_BOARD_ID
#define PICO_RAND_SEED_ENTROPY_SRC_BOARD_ID 1
#endif

// PICO_CONFIG: PICO_RAND_SEED_ENTROPY_SRC_RAM_HASH, Enable/disable use of a RAM hash as an entropy source for the random seed, type=bool, default=1, group=pico_rand
#ifndef PICO_RAND_SEED_ENTROPY_SRC_RAM_HASH
#define PICO_RAND_SEED_ENTROPY_SRC_RAM_HASH 1
#endif

// ---------------------------------
// PICO_RAND_ENTROPY_SRC_ROSC CONFIG
// ---------------------------------

// PICO_CONFIG: PICO_RAND_ROSC_BIT_SAMPLE_COUNT, Number of samples to take of the ROSC random bit per random number generation , min=1, max=64, default=1, group=pico_rand
#ifndef PICO_RAND_ROSC_BIT_SAMPLE_COUNT
#define PICO_RAND_ROSC_BIT_SAMPLE_COUNT 1
#endif

// PICO_CONFIG: PICO_RAND_MIN_ROSC_BIT_SAMPLE_TIME_US, Define a default minimum time between sampling the ROSC random bit, min=5, max=20, default=10, group=pico_rand
#ifndef PICO_RAND_MIN_ROSC_BIT_SAMPLE_TIME_US
// (Arbitrary / tested) minimum time between sampling the ROSC random bit
#define PICO_RAND_MIN_ROSC_BIT_SAMPLE_TIME_US 10u
#endif

// ---------------------------------------------
// PICO_RAND_ENTROPY_SRC_BUS_PERF_COUNTER CONFIG
// ---------------------------------------------

// PICO_CONFIG: PICO_RAND_BUS_PERF_COUNTER_INDEX, Bus performance counter index to use for sourcing entropy, min=0, max=3, group=pico_rand
// this is deliberately undefined by default, meaning the code will pick that appears unused
//#define PICO_RAND_BUS_PERF_COUNTER_INDEX 0

// PICO_CONFIG: PICO_RAND_BUS_PERF_COUNTER_EVENT, Bus performance counter event to use for sourcing entropy, default=arbiter_sram5_perf_event_access, group=pico_rand
#ifndef PICO_RAND_BUS_PERF_COUNTER_EVENT
#define PICO_RAND_BUS_PERF_COUNTER_EVENT arbiter_sram5_perf_event_access
#endif

// ------------------------------------------
// PICO_RAND_SEED_ENTROPY_SRC_RAM_HASH CONFIG
// ------------------------------------------

// PICO_CONFIG: PICO_RAND_RAM_HASH_END, end of address in RAM (non-inclusive) to hash during pico_rand seed initialization, default=SRAM_END, group=pico_rand
#ifndef PICO_RAND_RAM_HASH_END
#define PICO_RAND_RAM_HASH_END     SRAM_END
#endif
// PICO_CONFIG: PICO_RAND_RAM_HASH_START, start of address in RAM (inclusive) to hash during pico_rand seed initialization, default=PICO_RAND_RAM_HASH_END-1024, group=pico_rand
#ifndef PICO_RAND_RAM_HASH_START
#define PICO_RAND_RAM_HASH_START   (PICO_RAND_RAM_HASH_END - 1024u)
#endif

// We provide a maximum of 128 bits entropy in one go
typedef struct rng_128 {
    uint64_t r[2];
} rng_128_t;

/*! \brief Get 128-bit random number
 *  \ingroup pico_rand
 *
 * This method may be safely called from either core or from an IRQ, but be careful in the latter case as
 * the call may block for a number of microseconds waiting on more entropy.
 *
 * \param rand128 Pointer to storage to accept a 128-bit random number
 */
void get_rand_128(rng_128_t *rand128);

/*! \brief Get 64-bit random number
 *  \ingroup pico_rand
 *
 * This method may be safely called from either core or from an IRQ, but be careful in the latter case as
 * the call may block for a number of microseconds waiting on more entropy.
 *
 * \return 64-bit random number
 */
uint64_t get_rand_64(void);

/*! \brief Get 32-bit random number
 *  \ingroup pico_rand
 *
 * This method may be safely called from either core or from an IRQ, but be careful in the latter case as
 * the call may block for a number of microseconds waiting on more entropy.
 *
 * \return 32-bit random number
 */
uint32_t get_rand_32(void);

#ifdef __cplusplus
}
#endif

#endif
