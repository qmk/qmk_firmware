/* SPDX-License-Identifier: GPL-2.0 */

#pragma once

#include <stdint.h>

/* Remove these once we transitioned to C23 across all platfroms */
#define UINT32_WIDTH 32
#define UINT64_WIDTH 64

/**
 *  @brief Mask for the little endian nth bit (0-31) in a 32-bit integer.
 */
#define BIT32(n) (UINT32_C(1) << (n))

/**
 * @brief Mask for the little endian nth bit (0-63) in a 64-bit integer.
 */
#define BIT64(n) (UINT64_C(1) << (n))

/**
 * @brief Create a contiguous 32-bit wide bitmask starting at bit position @l
 * and ending at position @h. The range is inclusive, meaning GENMASK32(20, 10)
 * gives us the 32-bit mask 0x001ffc00.
 */
#define GENMASK32(h, l) (((~UINT32_C(0)) - (UINT32_C(1) << (l)) + 1) & (~UINT32_C(0) >> (UINT32_WIDTH - 1 - (h))))

/**
 * @brief Create a contiguous 64-bit wide bitmask starting at bit position @l
 * and ending at position @h. The range is inclusive, meaning GENMASK64(39, 21)
 * gives us the 64-bit mask 0x000000ffffe00000.
 */
#define GENMASK64(h, l) (((~UINT64_C(0)) - (UINT64_C(1) << (l)) + 1) & (~UINT64_C(0) >> (UINT64_WIDTH - 1 - (h))))
