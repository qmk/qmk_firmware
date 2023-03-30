/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/claim.h"

uint32_t hw_claim_lock() {
    return spin_lock_blocking(spin_lock_instance(PICO_SPINLOCK_ID_HARDWARE_CLAIM));
}

void hw_claim_unlock(uint32_t save) {
    spin_unlock(spin_lock_instance(PICO_SPINLOCK_ID_HARDWARE_CLAIM), save);
}

inline bool hw_is_claimed(const uint8_t *bits, uint bit_index) {
    return (bits[bit_index >> 3u] & (1u << (bit_index & 7u)));
}

void hw_claim_or_assert(uint8_t *bits, uint bit_index, const char *message) {
    uint32_t save = hw_claim_lock();
    if (hw_is_claimed(bits, bit_index)) {
        panic(message, bit_index);
    } else {
        bits[bit_index >> 3u] |= (uint8_t)(1u << (bit_index & 7u));
    }
    hw_claim_unlock(save);
}

int hw_claim_unused_from_range(uint8_t *bits, bool required, uint bit_lsb, uint bit_msb, const char *message) {
    // don't bother check lsb / msb order as if wrong, then it'll fail anyway
    uint32_t save = hw_claim_lock();
    int found_bit = -1;
    for(uint bit=bit_lsb; bit <= bit_msb; bit++) {
        if (!hw_is_claimed(bits, bit)) {
            bits[bit >> 3u] |= (uint8_t)(1u << (bit & 7u));
            found_bit = (int)bit;
            break;
        }
    }
    hw_claim_unlock(save);
    if (found_bit < 0 && required) {
        panic(message);
    }
    return found_bit;
}

void hw_claim_clear(uint8_t *bits, uint bit_index) {
    uint32_t save = hw_claim_lock();
    assert(hw_is_claimed(bits, bit_index));
    bits[bit_index >> 3u] &= (uint8_t) ~(1u << (bit_index & 7u));
    hw_claim_unlock(save);
}


