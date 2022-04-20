// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include <stdint.h>
#include <stdlib.h>

/**
 * @typedef Status returned from any wear-leveling API.
 */
typedef enum wear_leveling_status_t {
    WEAR_LEVELING_FAILED,      //< Invocation failed
    WEAR_LEVELING_SUCCESS,     //< Invocation succeeded
    WEAR_LEVELING_CONSOLIDATED //< Invocation succeded, consolidation occurred
} wear_leveling_status_t;

/**
 * Wear-leveling initialization
 *
 * @return Status of the request
 */
wear_leveling_status_t wear_leveling_init(void);

/**
 * Wear-leveling erasure.
 *
 * @return Status of the request
 */
wear_leveling_status_t wear_leveling_erase(void);

/**
 * Writes logical data into the backing store. Skips writes if there are no changes to values.
 *
 * @param address[in] the logical address to write data
 * @param value[in] pointer to the source buffer
 * @param length[in] length of the data
 * @return Status of the request
 */
wear_leveling_status_t wear_leveling_write(uint32_t address, const void* value, size_t length);

/**
 * Reads logical data from the cache.
 *
 * @param address[in] the logical address to read data
 * @param value[out] pointer to the destination buffer
 * @param length[in] length of the data
 * @return Status of the request
 */
wear_leveling_status_t wear_leveling_read(uint32_t address, void* value, size_t length);
