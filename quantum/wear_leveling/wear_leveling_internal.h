// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifdef __cplusplus
#    define _Static_assert static_assert
#endif

#include <stdint.h>
#include <string.h>

#if BACKING_STORE_WRITE_SIZE == 2
typedef uint16_t backing_store_int_t;
#elif BACKING_STORE_WRITE_SIZE == 4
typedef uint32_t backing_store_int_t;
#elif BACKING_STORE_WRITE_SIZE == 8
typedef uint64_t backing_store_int_t;
#else
#    error Invalid BACKING_STORE_WRITE_SIZE, needs to be 2/4/8.
#endif

#ifndef WEAR_LEVELING_BACKING_SIZE
#    error WEAR_LEVELING_BACKING_SIZE was not set.
#endif

#ifndef WEAR_LEVELING_LOGICAL_SIZE
#    error WEAR_LEVELING_LOGICAL_SIZE was not set.
#endif

#ifdef WEAR_LEVELING_DEBUG_OUTPUT
#    include <debug.h>
#    define bs_dprintf(...) dprintf("Backing store: " __VA_ARGS__)
#    define wl_dprintf(...) dprintf("Wear leveling: " __VA_ARGS__)
#    define wl_dump(address, value, length)             \
        do {                                            \
            dprintf("[0x%04X]: ", (int)(address));      \
            const uint8_t* p = (const uint8_t*)(value); \
            for (int i = 0; i < (length); ++i) {        \
                dprintf(" %02X", (int)p[i]);            \
            }                                           \
            dprintf("\n");                              \
        } while (0)
#else
#    define wl_dprintf(...) \
        do {                \
        } while (0)
#    define bs_dprintf(...) \
        do {                \
        } while (0)
#    define wl_dump(...) \
        do {             \
        } while (0)
#endif // WEAR_LEVELING_DEBUG_OUTPUT

#ifdef WEAR_LEVELING_ASSERTS
#    include <assert.h>
#    define wl_assert(...) assert(__VA_ARGS__)
#else
#    define wl_assert(...) \
        do {               \
        } while (0)
#endif // WEAR_LEVELING_ASSERTS

// Compile-time validation of configurable options
_Static_assert(WEAR_LEVELING_BACKING_SIZE >= (WEAR_LEVELING_LOGICAL_SIZE * 2), "Total backing size must be at least twice the size of the logical size");
_Static_assert(WEAR_LEVELING_LOGICAL_SIZE % BACKING_STORE_WRITE_SIZE == 0, "Logical size must be a multiple of write size");
_Static_assert(WEAR_LEVELING_BACKING_SIZE % WEAR_LEVELING_LOGICAL_SIZE == 0, "Backing size must be a multiple of logical size");

// Backing Store API, to be implemented elsewhere by flash driver etc.
bool backing_store_init(void);
bool backing_store_unlock(void);
bool backing_store_erase(void);
bool backing_store_write(uint32_t address, backing_store_int_t value);
bool backing_store_write_bulk(uint32_t address, backing_store_int_t* values, size_t item_count); // weak implementation already provided, optimized implementation can be implemented by driver
bool backing_store_lock(void);
bool backing_store_read(uint32_t address, backing_store_int_t* value);
bool backing_store_read_bulk(uint32_t address, backing_store_int_t* values, size_t item_count); // weak implementation already provided, optimized implementation can be implemented by driver

/**
 * Helper type used to contain a write log entry.
 */
typedef union write_log_entry_t {
    uint64_t raw64;
    uint32_t raw32[2];
    uint16_t raw16[4];
    uint8_t  raw8[8];
} write_log_entry_t;

_Static_assert(sizeof(write_log_entry_t) == 8, "Wear leveling write log entry size was not 8");

/**
 * Log entry type discriminator.
 */
enum {
    // 0x00 -- Multi-byte storage type
    LOG_ENTRY_TYPE_MULTIBYTE,

    // 0x01 -- 2-byte backing store write optimization: address < 64
    LOG_ENTRY_TYPE_OPTIMIZED_64,

    // 0x02 -- 2-byte backing store write optimization: word-encoded 0/1 values
    LOG_ENTRY_TYPE_WORD_01,

    LOG_ENTRY_TYPES
};

_Static_assert(LOG_ENTRY_TYPES <= (1 << 2), "Too many log entry types to fit into 2 bits of storage");

#define BITMASK_FOR_BITCOUNT(n) ((1 << (n)) - 1)

#define LOG_ENTRY_GET_TYPE(entry) (((entry).raw8[0] >> 6) & BITMASK_FOR_BITCOUNT(2))

#define LOG_ENTRY_MULTIBYTE_MAX_BYTES 5
#define LOG_ENTRY_MULTIBYTE_GET_ADDRESS(entry) (((((uint32_t)((entry).raw8[0])) & BITMASK_FOR_BITCOUNT(3)) << 16) | (((uint32_t)((entry).raw8[1])) << 8) | (entry).raw8[2])
#define LOG_ENTRY_MULTIBYTE_GET_LENGTH(entry) ((uint8_t)(((entry).raw8[0] >> 3) & BITMASK_FOR_BITCOUNT(3)))
#define LOG_ENTRY_MAKE_MULTIBYTE(address, length)                                                       \
    (write_log_entry_t) {                                                                               \
        .raw8 = {                                                                                       \
            [0] = (((((uint8_t)LOG_ENTRY_TYPE_MULTIBYTE) & BITMASK_FOR_BITCOUNT(2)) << 6) /* type */    \
                   | ((((uint8_t)(length)) & BITMASK_FOR_BITCOUNT(3)) << 3)               /* length */  \
                   | ((((uint8_t)((address) >> 16))) & BITMASK_FOR_BITCOUNT(3))           /* address */ \
                   ),                                                                                   \
            [1] = (((uint8_t)((address) >> 8)) & BITMASK_FOR_BITCOUNT(8)), /* address */                \
            [2] = (((uint8_t)(address)) & BITMASK_FOR_BITCOUNT(8)),        /* address */                \
        }                                                                                               \
    }

#define LOG_ENTRY_OPTIMIZED_64_GET_ADDRESS(entry) ((uint32_t)((entry).raw8[0] & BITMASK_FOR_BITCOUNT(6)))
#define LOG_ENTRY_OPTIMIZED_64_GET_VALUE(entry) ((entry).raw8[1])
#define LOG_ENTRY_MAKE_OPTIMIZED_64(address, value)                                                        \
    (write_log_entry_t) {                                                                                  \
        .raw8 = {                                                                                          \
            [0] = (((((uint8_t)LOG_ENTRY_TYPE_OPTIMIZED_64) & BITMASK_FOR_BITCOUNT(2)) << 6) /* type */    \
                   | ((((uint8_t)(address))) & BITMASK_FOR_BITCOUNT(6))                      /* address */ \
                   ),                                                                                      \
            [1] = ((uint8_t)(value)), /* value */                                                          \
        }                                                                                                  \
    }

#define LOG_ENTRY_WORD_01_GET_ADDRESS(entry) ((((uint32_t)(((entry).raw8[0]) & BITMASK_FOR_BITCOUNT(5))) << 9) | (((uint32_t)((entry).raw8[1])) << 1))
#define LOG_ENTRY_WORD_01_GET_VALUE(entry) ((uint8_t)((entry).raw8[0] >> 5) & BITMASK_FOR_BITCOUNT(1))
#define LOG_ENTRY_MAKE_WORD_01(address, value)                                                        \
    (write_log_entry_t) {                                                                             \
        .raw8 = {                                                                                     \
            [0] = (((((uint8_t)LOG_ENTRY_TYPE_WORD_01) & BITMASK_FOR_BITCOUNT(2)) << 6) /* type */    \
                   | (((((uint8_t)((value) ? 1 : 0))) & BITMASK_FOR_BITCOUNT(1)) << 5)  /* value */   \
                   | ((((uint8_t)((address) >> 9))) & BITMASK_FOR_BITCOUNT(5))          /* address */ \
                   ),                                                                                 \
            [1] = (uint8_t)((address) >> 1), /* address */                                            \
        }                                                                                             \
    }
