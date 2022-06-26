// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdbool.h>
#include "fnv.h"
#include "wear_leveling.h"
#include "wear_leveling_internal.h"

/*
    This wear leveling algorithm is adapted from algorithms from previous
    implementations in QMK, namely:
        - Artur F. (http://engsta.com/stm32-flash-memory-eeprom-emulator/)
        - Yiancar -- QMK's base implementation for STM32F303
        - Ilya Zhuravlev -- initial wear leveling algorithm
        - Don Kjer -- increased flash density algorithm
        - Nick Brassel (@tzarc) -- decoupled for use on other peripherals

    At this layer, it is assumed that any reads/writes from the backing store
    have a "reset state" after erasure of zero.
    It is up to the backing store to perform translation of values, such as
    taking the complement in order to deal with flash memory's reset value.

    Terminology:

        - Backing store: this is the storage area used by the wear leveling
            algorithm.

        - Backing size: this is the amount of storage provided by the backing
            store for use by the wear leveling algorithm.

        - Backing write size: this is the minimum number of bytes the backing
            store can write in a single operation.

        - Logical data: this is the externally-visible "emulated EEPROM" that
            external subsystems "see" when performing reads/writes.

        - Logical size: this is the amount of storage available for use
            externally. Effectively, the "size of the EEPROM".

        - Write log: this is a section of the backing store used to keep track
            of modifications without overwriting existing data. This log is
            "played back" on startup such that any subsequent reads are capable
            of returning the latest data.

        - Consolidated data: this is a section of the backing store reserved for
            use for the latest copy of logical data. This is only ever written
            when the write log is full -- the latest values for the logical data
            are written here and the write log is cleared.

    Configurables:

        - BACKING_STORE_WRITE_SIZE: The number of bytes requires for a write
            operation. This is defined by the capabilities of the backing store.

        - WEAR_LEVELING_BACKING_SIZE: The number of bytes provided by the
            backing store for use by the wear leveling algorithm.  This is
            defined by the capabilities of the backing store. This value must
            also be at least twice the size of the logical size, as well as a
            multiple of the logical size.

        - WEAR_LEVELING_LOGICAL_SIZE: The number of bytes externally visible
            to other subsystems performing reads/writes. This must be a multiple
            of the write size.

    General algorithm:

        During initialization:
            * The contents of the consolidated data section are read into cache.
            * The contents of the write log are "played back" and update the
                cache accordingly.

        During reads:
            * Logical data is served from the cache.

        During writes:
            * The cache is updated with the new data.
            * A new write log entry is appended to the log.
            * If the log's full, data is consolidated and the write log cleared.

    Write log structure:

        The first 8 bytes of the write log are a FNV1a_64 hash of the contents
        of the consolidated data area, in an attempt to detect and guard against
        any data corruption.

        The write log follows the hash:

        Given that the algorithm needs to cater for 2-, 4-, and 8-byte writes,
        a variable-length write log entry is used such that the minimal amount
        of storage is used based off the backing store write size.

        Firstly, an empty log entry is expected to be all zeros. If the backing
        store uses 0xFF for cleared bytes, it should return the complement, such
        that this wear-leveling algorithm "receives" zeros.

        For multi-byte writes, up to 8 bytes will be used for each log entry,
        depending on the size of backing store writes:

        ╔ Multi-byte Log Entry (2, 4-byte) ═╗
        ║00XXXYYY║YYYYYYYY║YYYYYYYY║AAAAAAAA║
        ║  └┬┘└┬┘║└──┬───┘║└──┬───┘║└──┬───┘║
        ║  LenAdd║ Address║ Address║Value[0]║
        ╚════════╩════════╩════════╩════════╝
        ╔ Multi-byte Log Entry (2-byte) ══════════════════════╗
        ║00XXXYYY║YYYYYYYY║YYYYYYYY║AAAAAAAA║BBBBBBBB║CCCCCCCC║
        ║  └┬┘└┬┘║└──┬───┘║└──┬───┘║└──┬───┘║└──┬───┘║└──┬───┘║
        ║  LenAdd║ Address║ Address║Value[0]║Value[1]║Value[2]║
        ╚════════╩════════╩════════╩════════╩════════╩════════╝
        ╔ Multi-byte Log Entry (2, 4, 8-byte) ══════════════════════════════════╗
        ║00XXXYYY║YYYYYYYY║YYYYYYYY║AAAAAAAA║BBBBBBBB║CCCCCCCC║DDDDDDDD║EEEEEEEE║
        ║  └┬┘└┬┘║└──┬───┘║└──┬───┘║└──┬───┘║└──┬───┘║└──┬───┘║└──┬───┘║└──┬───┘║
        ║  LenAdd║ Address║ Address║Value[0]║Value[1]║Value[2]║Value[3]║Value[4]║
        ╚════════╩════════╩════════╩════════╩════════╩════════╩════════╩════════╝

        19 bits are used for the address, which allows for a max logical size of
        512kB. Up to 5 bytes can be included in a single log entry.

        For 2-byte backing store writes, the last two bytes are optional
            depending on the length of data to be written. Accordingly, either 3
            or 4 backing store write operations will occur.
        For 4-byte backing store writes, either one or two write operations
            occur, depending on the length.
        For 8-byte backing store writes, one write operation occur.

    2-byte backing store optimizations:

        For single byte writes, addresses between 0...63 are encoded in a single
        backing store write operation. 4- and 8-byte backing stores do not have
        this optimization as it does not minimize the number of bytes written.

        ╔ Byte-Entry ════╗
        ║01XXXXXXYYYYYYYY║
        ║  └─┬──┘└──┬───┘║
        ║ Address Value  ║
        ╚════════════════╝
        0 <= Address < 0x40 (64)

        A second optimization takes into account uint16_t writes of 0 or 1,
        specifically catering for KC_NO and KC_TRANSPARENT in the dynamic keymap
        subsystem. This is valid only for the first 16kB of logical data --
        addresses outside this range will use the multi-byte encoding above.

        ╔ U16-Encoded 0 ═╗
        ║100XXXXXXXXXXXXX║
        ║  │└─────┬─────┘║
        ║  │Address >> 1 ║
        ║  └── Value: 0  ║
        ╚════════════════╝
        0 <= Address <= 0x3FFE (16382)

        ╔ U16-Encoded 1 ═╗
        ║101XXXXXXXXXXXXX║
        ║  │└─────┬─────┘║
        ║  │Address >> 1 ║
        ║  └── Value: 1  ║
        ╚════════════════╝
        0 <= Address <= 0x3FFE (16382) */

/**
 * Storage area for the wear-leveling cache.
 */
static struct __attribute__((__aligned__(BACKING_STORE_WRITE_SIZE))) {
    __attribute__((__aligned__(BACKING_STORE_WRITE_SIZE))) uint8_t cache[(WEAR_LEVELING_LOGICAL_SIZE)];
    uint32_t                                                       write_address;
    bool                                                           unlocked;
} wear_leveling;

/**
 * Locking helper: status
 */
typedef enum backing_store_lock_status_t { STATUS_FAILURE = 0, STATUS_SUCCESS, STATUS_UNCHANGED } backing_store_lock_status_t;

/**
 * Locking helper: unlock
 */
static inline backing_store_lock_status_t wear_leveling_unlock(void) {
    if (wear_leveling.unlocked) {
        return STATUS_UNCHANGED;
    }
    if (!backing_store_unlock()) {
        return STATUS_FAILURE;
    }
    wear_leveling.unlocked = true;
    return STATUS_SUCCESS;
}

/**
 * Locking helper: lock
 */
static inline backing_store_lock_status_t wear_leveling_lock(void) {
    if (!wear_leveling.unlocked) {
        return STATUS_UNCHANGED;
    }
    if (!backing_store_lock()) {
        return STATUS_FAILURE;
    }
    wear_leveling.unlocked = false;
    return STATUS_SUCCESS;
}

/**
 * Resets the cache, ensuring the write address is correctly initialised.
 */
static void wear_leveling_clear_cache(void) {
    memset(wear_leveling.cache, 0, (WEAR_LEVELING_LOGICAL_SIZE));
    wear_leveling.write_address = (WEAR_LEVELING_LOGICAL_SIZE) + 8; // +8 is due to the FNV1a_64 of the consolidated buffer
}

/**
 * Reads the consolidated data from the backing store into the cache.
 * Does not consider the write log.
 */
static wear_leveling_status_t wear_leveling_read_consolidated(void) {
    wl_dprintf("Reading consolidated data\n");

    wear_leveling_status_t status = WEAR_LEVELING_SUCCESS;
    for (int address = 0; address < (WEAR_LEVELING_LOGICAL_SIZE); address += (BACKING_STORE_WRITE_SIZE)) {
        backing_store_int_t *const loc = (backing_store_int_t *)&wear_leveling.cache[address];
        backing_store_int_t        temp;
        bool                       ok = backing_store_read(address, &temp);
        if (!ok) {
            wl_dprintf("Failed to read from backing store\n");
            status = WEAR_LEVELING_FAILED;
            break;
        }
        *loc = temp;
    }

    // Verify the FNV1a_64 result
    if (status != WEAR_LEVELING_FAILED) {
        uint64_t          expected = fnv_64a_buf(wear_leveling.cache, (WEAR_LEVELING_LOGICAL_SIZE), FNV1A_64_INIT);
        write_log_entry_t entry;
#if BACKING_STORE_WRITE_SIZE == 2
        backing_store_read((WEAR_LEVELING_LOGICAL_SIZE) + 0, &entry.raw16[0]);
        backing_store_read((WEAR_LEVELING_LOGICAL_SIZE) + 2, &entry.raw16[1]);
        backing_store_read((WEAR_LEVELING_LOGICAL_SIZE) + 4, &entry.raw16[2]);
        backing_store_read((WEAR_LEVELING_LOGICAL_SIZE) + 6, &entry.raw16[3]);
#elif BACKING_STORE_WRITE_SIZE == 4
        backing_store_read((WEAR_LEVELING_LOGICAL_SIZE) + 0, &entry.raw32[0]);
        backing_store_read((WEAR_LEVELING_LOGICAL_SIZE) + 4, &entry.raw32[1]);
#elif BACKING_STORE_WRITE_SIZE == 8
        backing_store_read((WEAR_LEVELING_LOGICAL_SIZE) + 0, &entry.raw64);
#endif
        // If we have a mismatch, clear the cache but do not flag a failure,
        // which will cater for the completely clean MCU case.
        if (entry.raw64 != expected) {
            wear_leveling_clear_cache();
        }
    }

    // If we failed for any reason, then clear the cache
    if (status == WEAR_LEVELING_FAILED) {
        wear_leveling_clear_cache();
    }

    return status;
}

/**
 * Writes the current cache to consolidated data at the beginning of the backing store.
 * Does not clear the write log.
 */
static wear_leveling_status_t wear_leveling_write_consolidated(void) {
    wl_dprintf("Writing consolidated data\n");

    wear_leveling_status_t      status      = WEAR_LEVELING_CONSOLIDATED;
    backing_store_lock_status_t lock_status = wear_leveling_unlock();
    for (int address = 0; address < (WEAR_LEVELING_LOGICAL_SIZE); address += (BACKING_STORE_WRITE_SIZE)) {
        const backing_store_int_t value = *(backing_store_int_t *)&wear_leveling.cache[address];
        backing_store_int_t       temp;
        bool                      ok = backing_store_read(address, &temp);
        if (!ok) {
            wl_dprintf("Failed to read from backing store\n");
            status = WEAR_LEVELING_FAILED;
            break;
        }
        if (temp != value) {
            ok = backing_store_write(address, value);
            if (!ok) {
                wl_dprintf("Failed to write to backing store\n");
                status = WEAR_LEVELING_FAILED;
                break;
            }
        }
    }

    if (status != WEAR_LEVELING_FAILED) {
        // Write out the FNV1a_64 result of the consolidated data
        write_log_entry_t entry;
        entry.raw64 = fnv_64a_buf(wear_leveling.cache, (WEAR_LEVELING_LOGICAL_SIZE), FNV1A_64_INIT);
        do {
#if BACKING_STORE_WRITE_SIZE == 2
            if (!backing_store_write((WEAR_LEVELING_LOGICAL_SIZE) + 0, entry.raw16[0])) {
                status = WEAR_LEVELING_FAILED;
                break;
            }
            if (!backing_store_write((WEAR_LEVELING_LOGICAL_SIZE) + 2, entry.raw16[1])) {
                status = WEAR_LEVELING_FAILED;
                break;
            }
            if (!backing_store_write((WEAR_LEVELING_LOGICAL_SIZE) + 4, entry.raw16[2])) {
                status = WEAR_LEVELING_FAILED;
                break;
            }
            if (!backing_store_write((WEAR_LEVELING_LOGICAL_SIZE) + 6, entry.raw16[3])) {
                status = WEAR_LEVELING_FAILED;
                break;
            }
#elif BACKING_STORE_WRITE_SIZE == 4
            if (!backing_store_write((WEAR_LEVELING_LOGICAL_SIZE) + 0, entry.raw32[0])) {
                status = WEAR_LEVELING_FAILED;
                break;
            }
            if (!backing_store_write((WEAR_LEVELING_LOGICAL_SIZE) + 4, entry.raw32[1])) {
                status = WEAR_LEVELING_FAILED;
                break;
            }
#elif BACKING_STORE_WRITE_SIZE == 8
            if (!backing_store_write((WEAR_LEVELING_LOGICAL_SIZE) + 0, entry.raw64)) {
                status = WEAR_LEVELING_FAILED;
                break;
            }
#endif
        } while (0);
    }

    if (lock_status == STATUS_SUCCESS) {
        wear_leveling_lock();
    }
    return status;
}

/**
 * Forces a write of the current cache.
 * Erases the backing store, including the write log.
 * During this operation, there is the potential for data loss if a power loss occurs.
 */
static wear_leveling_status_t wear_leveling_consolidate_force(void) {
    wl_dprintf("Erasing backing store\n");

    // Erase the backing store. Expectation is that any un-written values that are read back after this call come back as zero.
    bool ok = backing_store_erase();
    if (!ok) {
        wl_dprintf("Failed to erase backing store\n");
        return WEAR_LEVELING_FAILED;
    }

    // Write the cache to the first section of the backing store.
    wear_leveling_status_t status = wear_leveling_write_consolidated();
    if (status == WEAR_LEVELING_FAILED) {
        wl_dprintf("Failed to write consolidated data\n");
    }

    // Next write of the log occurs after the consolidated values at the start of the backing store.
    wear_leveling.write_address = (WEAR_LEVELING_LOGICAL_SIZE) + 8; // +8 due to the FNV1a_64 of the consolidated area

    return status;
}

/**
 * Potential write of the current cache to the backing store.
 * Skipped if the current write log position is not at the end of the backing store.
 * During this operation, there is the potential for data loss if a power loss occurs.
 *
 * @return true if consolidation occurred
 */
static wear_leveling_status_t wear_leveling_consolidate_if_needed(void) {
    if (wear_leveling.write_address >= (WEAR_LEVELING_BACKING_SIZE)) {
        return wear_leveling_consolidate_force();
    }

    return WEAR_LEVELING_SUCCESS;
}

/**
 * Appends the supplied fixed-width entry to the write log, optionally consolidating if the log is full.
 *
 * @return true if consolidation occurred
 */
static wear_leveling_status_t wear_leveling_append_raw(backing_store_int_t value) {
    bool ok = backing_store_write(wear_leveling.write_address, value);
    if (!ok) {
        wl_dprintf("Failed to write to backing store\n");
        return WEAR_LEVELING_FAILED;
    }
    wear_leveling.write_address += (BACKING_STORE_WRITE_SIZE);
    return wear_leveling_consolidate_if_needed();
}

/**
 * Handles writing multi_byte-encoded data to the backing store.
 *
 * @return true if consolidation occurred
 */
static wear_leveling_status_t wear_leveling_write_raw_multibyte(uint32_t address, const void *value, size_t length) {
    const uint8_t *   p   = value;
    write_log_entry_t log = LOG_ENTRY_MAKE_MULTIBYTE(address, length);
    for (size_t i = 0; i < length; ++i) {
        log.raw8[3 + i] = p[i];
    }

    // Write to the backing store. See the multi-byte log format in the documentation header at the top of the file.
    wear_leveling_status_t status;
#if BACKING_STORE_WRITE_SIZE == 2
    status = wear_leveling_append_raw(log.raw16[0]);
    if (status != WEAR_LEVELING_SUCCESS) {
        return status;
    }

    status = wear_leveling_append_raw(log.raw16[1]);
    if (status != WEAR_LEVELING_SUCCESS) {
        return status;
    }

    if (length > 1) {
        status = wear_leveling_append_raw(log.raw16[2]);
        if (status != WEAR_LEVELING_SUCCESS) {
            return status;
        }
    }

    if (length > 3) {
        status = wear_leveling_append_raw(log.raw16[3]);
        if (status != WEAR_LEVELING_SUCCESS) {
            return status;
        }
    }
#elif BACKING_STORE_WRITE_SIZE == 4
    status = wear_leveling_append_raw(log.raw32[0]);
    if (status != WEAR_LEVELING_SUCCESS) {
        return status;
    }

    if (length > 1) {
        status = wear_leveling_append_raw(log.raw32[1]);
        if (status != WEAR_LEVELING_SUCCESS) {
            return status;
        }
    }
#elif BACKING_STORE_WRITE_SIZE == 8
    status = wear_leveling_append_raw(log.raw64);
    if (status != WEAR_LEVELING_SUCCESS) {
        return status;
    }
#endif
    return status;
}

/**
 * Handles the actual writing of logical data into the write log section of the backing store.
 */
static wear_leveling_status_t wear_leveling_write_raw(uint32_t address, const void *value, size_t length) {
    const uint8_t *        p         = value;
    size_t                 remaining = length;
    wear_leveling_status_t status    = WEAR_LEVELING_SUCCESS;
    while (remaining > 0) {
#if BACKING_STORE_WRITE_SIZE == 2
        // Small-write optimizations - uint16_t, 0 or 1, address is even, address <16384:
        if (remaining >= 2 && address % 2 == 0 && address < 16384) {
            const uint16_t v = *(const uint16_t *)p;
            if (v == 0 || v == 1) {
                const write_log_entry_t log = LOG_ENTRY_MAKE_WORD_01(address, v);
                status                      = wear_leveling_append_raw(log.raw16[0]);
                if (status != WEAR_LEVELING_SUCCESS) {
                    // If consolidation occurred, then the cache has already been written to the consolidated area. No need to continue.
                    // If a failure occurred, pass it on.
                    return status;
                }

                remaining -= 2;
                address += 2;
                p += 2;
                continue;
            }
        }

        // Small-write optimizations - address<64:
        if (address < 64) {
            const write_log_entry_t log = LOG_ENTRY_MAKE_OPTIMIZED_64(address, *p);
            status                      = wear_leveling_append_raw(log.raw16[0]);
            if (status != WEAR_LEVELING_SUCCESS) {
                // If consolidation occurred, then the cache has already been written to the consolidated area. No need to continue.
                // If a failure occurred, pass it on.
                return status;
            }

            remaining--;
            address++;
            p++;
            continue;
        }
#endif // BACKING_STORE_WRITE_SIZE == 2
        const size_t this_length = remaining >= LOG_ENTRY_MULTIBYTE_MAX_BYTES ? LOG_ENTRY_MULTIBYTE_MAX_BYTES : remaining;
        status                   = wear_leveling_write_raw_multibyte(address, p, this_length);
        if (status != WEAR_LEVELING_SUCCESS) {
            // If consolidation occurred, then the cache has already been written to the consolidated area. No need to continue.
            // If a failure occurred, pass it on.
            return status;
        }
        remaining -= this_length;
        address += (uint32_t)this_length;
        p += this_length;
    }

    return status;
}

/**
 * "Replays" the write log from the backing store, updating the local cache with updated values.
 */
static wear_leveling_status_t wear_leveling_playback_log(void) {
    wl_dprintf("Playback write log\n");

    wear_leveling_status_t status          = WEAR_LEVELING_SUCCESS;
    bool                   cancel_playback = false;
    uint32_t               address         = (WEAR_LEVELING_LOGICAL_SIZE) + 8; // +8 due to the FNV1a_64 of the consolidated area
    while (!cancel_playback && address < (WEAR_LEVELING_BACKING_SIZE)) {
        backing_store_int_t value;
        bool                ok = backing_store_read(address, &value);
        if (!ok) {
            wl_dprintf("Failed to load from backing store, skipping playback of write log\n");
            cancel_playback = true;
            status          = WEAR_LEVELING_FAILED;
            break;
        }
        if (value == 0) {
            wl_dprintf("Found empty slot, no more log entries\n");
            cancel_playback = true;
            break;
        }

        // If we got a nonzero value, then we need to increment the address to ensure next write occurs at next location
        address += (BACKING_STORE_WRITE_SIZE);

        // Read from the write log
        write_log_entry_t log;
#if BACKING_STORE_WRITE_SIZE == 2
        log.raw16[0] = value;
#elif BACKING_STORE_WRITE_SIZE == 4
        log.raw32[0] = value;
#elif BACKING_STORE_WRITE_SIZE == 8
        log.raw64 = value;
#endif

        switch (LOG_ENTRY_GET_TYPE(log)) {
            case LOG_ENTRY_TYPE_MULTIBYTE: {
#if BACKING_STORE_WRITE_SIZE == 2
                ok = backing_store_read(address, &log.raw16[1]);
                if (!ok) {
                    wl_dprintf("Failed to load from backing store, skipping playback of write log\n");
                    cancel_playback = true;
                    status          = WEAR_LEVELING_FAILED;
                    break;
                }
                address += (BACKING_STORE_WRITE_SIZE);
#endif // BACKING_STORE_WRITE_SIZE == 2
                const uint32_t a = LOG_ENTRY_MULTIBYTE_GET_ADDRESS(log);
                const uint8_t  l = LOG_ENTRY_MULTIBYTE_GET_LENGTH(log);

                if (a + l > (WEAR_LEVELING_LOGICAL_SIZE)) {
                    cancel_playback = true;
                    status          = WEAR_LEVELING_FAILED;
                    break;
                }

#if BACKING_STORE_WRITE_SIZE == 2
                if (l > 1) {
                    ok = backing_store_read(address, &log.raw16[2]);
                    if (!ok) {
                        wl_dprintf("Failed to load from backing store, skipping playback of write log\n");
                        cancel_playback = true;
                        status          = WEAR_LEVELING_FAILED;
                        break;
                    }
                    address += (BACKING_STORE_WRITE_SIZE);
                }
                if (l > 3) {
                    ok = backing_store_read(address, &log.raw16[3]);
                    if (!ok) {
                        wl_dprintf("Failed to load from backing store, skipping playback of write log\n");
                        cancel_playback = true;
                        status          = WEAR_LEVELING_FAILED;
                        break;
                    }
                    address += (BACKING_STORE_WRITE_SIZE);
                }
#elif BACKING_STORE_WRITE_SIZE == 4
                if (l > 1) {
                    ok = backing_store_read(address, &log.raw32[1]);
                    if (!ok) {
                        wl_dprintf("Failed to load from backing store, skipping playback of write log\n");
                        cancel_playback = true;
                        status = WEAR_LEVELING_FAILED;
                        break;
                    }
                    address += (BACKING_STORE_WRITE_SIZE);
                }
#endif

                memcpy(&wear_leveling.cache[a], &log.raw8[3], l);
            } break;
#if BACKING_STORE_WRITE_SIZE == 2
            case LOG_ENTRY_TYPE_OPTIMIZED_64: {
                const uint32_t a = LOG_ENTRY_OPTIMIZED_64_GET_ADDRESS(log);
                const uint8_t  v = LOG_ENTRY_OPTIMIZED_64_GET_VALUE(log);

                if (a >= (WEAR_LEVELING_LOGICAL_SIZE)) {
                    cancel_playback = true;
                    status          = WEAR_LEVELING_FAILED;
                    break;
                }

                wear_leveling.cache[a] = v;
            } break;
            case LOG_ENTRY_TYPE_WORD_01: {
                const uint32_t a = LOG_ENTRY_WORD_01_GET_ADDRESS(log);
                const uint8_t  v = LOG_ENTRY_WORD_01_GET_VALUE(log);

                if (a + 1 >= (WEAR_LEVELING_LOGICAL_SIZE)) {
                    cancel_playback = true;
                    status          = WEAR_LEVELING_FAILED;
                    break;
                }

                wear_leveling.cache[a + 0] = v;
                wear_leveling.cache[a + 1] = 0;
            } break;
#endif // BACKING_STORE_WRITE_SIZE == 2
            default: {
                cancel_playback = true;
                status          = WEAR_LEVELING_FAILED;
            } break;
        }
    }

    // We've reached the end of the log, so we're at the new write location
    wear_leveling.write_address = address;

    if (status == WEAR_LEVELING_FAILED) {
        // If we had a failure during readback, assume we're corrupted -- force a consolidation with the data we already have
        status = wear_leveling_consolidate_force();
    } else {
        // Consolidate the cache + write log if required
        status = wear_leveling_consolidate_if_needed();
    }

    return status;
}

/**
 * Wear-leveling initialization
 */
wear_leveling_status_t wear_leveling_init(void) {
    wl_dprintf("Init\n");

    // Reset the cache
    wear_leveling_clear_cache();

    // Initialise the backing store
    if (!backing_store_init()) {
        // If it failed, clear the cache and return with failure
        wear_leveling_clear_cache();
        return WEAR_LEVELING_FAILED;
    }

    // Read the previous consolidated values, then replay the existing write log so that the cache has the "live" values
    wear_leveling_status_t status = wear_leveling_read_consolidated();
    if (status == WEAR_LEVELING_FAILED) {
        // If it failed, clear the cache and return with failure
        wear_leveling_clear_cache();
        return status;
    }

    status = wear_leveling_playback_log();
    if (status == WEAR_LEVELING_FAILED) {
        // If it failed, clear the cache and return with failure
        wear_leveling_clear_cache();
        return status;
    }

    return status;
}

/**
 * Wear-leveling erase.
 * Post-condition: any reads from the backing store directly after an erase operation must come back as zero.
 */
wear_leveling_status_t wear_leveling_erase(void) {
    wl_dprintf("Erase\n");

    // Unlock the backing store
    backing_store_lock_status_t lock_status = wear_leveling_unlock();
    if (lock_status == STATUS_FAILURE) {
        wear_leveling_lock();
        return WEAR_LEVELING_FAILED;
    }

    // Perform the erase
    bool ret = backing_store_erase();
    wear_leveling_clear_cache();

    // Lock the backing store if we acquired the lock successfully
    if (lock_status == STATUS_SUCCESS) {
        ret &= (wear_leveling_lock() != STATUS_FAILURE);
    }

    return ret ? WEAR_LEVELING_SUCCESS : WEAR_LEVELING_FAILED;
}

/**
 * Writes logical data into the backing store. Skips writes if there are no changes to values.
 */
wear_leveling_status_t wear_leveling_write(const uint32_t address, const void *value, size_t length) {
    wl_assert(address + length <= (WEAR_LEVELING_LOGICAL_SIZE));
    if (address + length > (WEAR_LEVELING_LOGICAL_SIZE)) {
        return WEAR_LEVELING_FAILED;
    }

    wl_dprintf("Write ");
    wl_dump(address, value, length);

    // Skip write if there's no change compared to the current cached value
    if (memcmp(value, &wear_leveling.cache[address], length) == 0) {
        return true;
    }

    // Update the cache before writing to the backing store -- if we hit the end of the backing store during writes to the log then we'll force a consolidation in-line
    memcpy(&wear_leveling.cache[address], value, length);

    // Unlock the backing store
    backing_store_lock_status_t lock_status = wear_leveling_unlock();
    if (lock_status == STATUS_FAILURE) {
        wear_leveling_lock();
        return WEAR_LEVELING_FAILED;
    }

    // Perform the actual write
    wear_leveling_status_t status = wear_leveling_write_raw(address, value, length);
    switch (status) {
        case WEAR_LEVELING_CONSOLIDATED:
        case WEAR_LEVELING_FAILED:
            // If the write triggered consolidation, or the write failed, then nothing else needs to occur.
            break;

        case WEAR_LEVELING_SUCCESS:
            // Consolidate the cache + write log if required
            status = wear_leveling_consolidate_if_needed();
            break;

        default:
            // Unsure how we'd get here...
            status = WEAR_LEVELING_FAILED;
            break;
    }

    if (lock_status == STATUS_SUCCESS) {
        if (wear_leveling_lock() == STATUS_FAILURE) {
            status = WEAR_LEVELING_FAILED;
        }
    }

    return status;
}

/**
 * Reads logical data from the cache.
 */
wear_leveling_status_t wear_leveling_read(const uint32_t address, void *value, size_t length) {
    wl_assert(address + length <= (WEAR_LEVELING_LOGICAL_SIZE));
    if (address + length > (WEAR_LEVELING_LOGICAL_SIZE)) {
        return WEAR_LEVELING_FAILED;
    }

    // Only need to copy from the cache
    memcpy(value, &wear_leveling.cache[address], length);

    wl_dprintf("Read  ");
    wl_dump(address, value, length);
    return WEAR_LEVELING_SUCCESS;
}
