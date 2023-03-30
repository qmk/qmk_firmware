/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_DIVIDER_H
#define _PICO_DIVIDER_H

#include "pico.h"
#include "hardware/divider.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup pico_divider pico_divider
 * Optimized 32 and 64 bit division functions accelerated by the RP2040 hardware divider.
 * Additionally provides integration with the C `/` and `%` operators
 */

/** \file pico/divider.h
* \brief High level APIs including combined quotient and remainder functions for 32 and 64 bit accelerated by the hardware divider
* \ingroup pico_divider
*
* These functions all call __aeabi_idiv0 or __aebi_ldiv0 on division by zero
* passing the largest applicably signed value
*
* Functions with unsafe in their name do not save/restore divider state, so are unsafe to call from interrupts. Unsafe functions are slightly faster.
*/

/**
 * \brief Integer divide of two signed 32-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return quotient
 */
int32_t div_s32s32(int32_t a, int32_t b);

/**
 * \brief Integer divide of two signed 32-bit values, with remainder
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \param [out] rem The remainder of dividend/divisor
 * \return Quotient result of dividend/divisor
 */
static inline int32_t divmod_s32s32_rem(int32_t a, int32_t b, int32_t *rem) {
    divmod_result_t r = hw_divider_divmod_s32(a, b);
    *rem = to_remainder_s32(r);
    return to_quotient_s32(r);
}

/**
 * \brief Integer divide of two signed 32-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return quotient in low word/r0, remainder in high word/r1
 */
divmod_result_t divmod_s32s32(int32_t a, int32_t b);

/**
 * \brief Integer divide of two unsigned 32-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return Quotient
 */
uint32_t div_u32u32(uint32_t a, uint32_t b);

/**
 * \brief Integer divide of two unsigned 32-bit values, with remainder
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \param [out] rem The remainder of dividend/divisor
 * \return Quotient result of dividend/divisor
 */
static inline uint32_t divmod_u32u32_rem(uint32_t a, uint32_t b, uint32_t *rem) {
    divmod_result_t r = hw_divider_divmod_u32(a, b);
    *rem = to_remainder_u32(r);
    return to_quotient_u32(r);
}

/**
 * \brief Integer divide of two unsigned 32-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return quotient in low word/r0, remainder in high word/r1
 */
divmod_result_t divmod_u32u32(uint32_t a, uint32_t b);

/**
 * \brief Integer divide of two signed 64-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return Quotient
 */
int64_t div_s64s64(int64_t a, int64_t b);

/**
 * \brief Integer divide of two signed 64-bit values, with remainder
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \param [out] rem The remainder of dividend/divisor
 * \return Quotient result of dividend/divisor
 */
int64_t divmod_s64s64_rem(int64_t a, int64_t b, int64_t *rem);

/**
 * \brief Integer divide of two signed 64-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return quotient in result (r0,r1), remainder in regs (r2, r3)
 */
int64_t divmod_s64s64(int64_t a, int64_t b);

/**
 * \brief Integer divide of two unsigned 64-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return Quotient
 */
uint64_t div_u64u64(uint64_t a, uint64_t b);

/**
 * \brief Integer divide of two unsigned 64-bit values, with remainder
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \param [out] rem The remainder of dividend/divisor
 * \return Quotient result of dividend/divisor
 */
uint64_t divmod_u64u64_rem(uint64_t a, uint64_t b, uint64_t *rem);


/**
 * \brief Integer divide of two signed 64-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return quotient in result (r0,r1), remainder in regs (r2, r3)
 */
uint64_t divmod_u64u64(uint64_t a, uint64_t b);

// -----------------------------------------------------------------------
// these "unsafe" functions are slightly faster, but do not save the divider state,
// so are not generally safe to be called from interrupts
// -----------------------------------------------------------------------

/**
 * \brief Unsafe integer divide of two signed 32-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return quotient
 *
 * Do not use in interrupts
 */
int32_t div_s32s32_unsafe(int32_t a, int32_t b);

/**
 * \brief Unsafe integer divide of two signed 32-bit values, with remainder
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \param [out] rem The remainder of dividend/divisor
 * \return Quotient result of dividend/divisor
 *
 * Do not use in interrupts
 */
int32_t divmod_s32s32_rem_unsafe(int32_t a, int32_t b, int32_t *rem);

/**
 * \brief Unsafe integer divide of two unsigned 32-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return quotient in low word/r0, remainder in high word/r1
 *
 * Do not use in interrupts
 */
int64_t divmod_s32s32_unsafe(int32_t a, int32_t b);

/**
 * \brief Unsafe integer divide of two unsigned 32-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return Quotient
 *
 * Do not use in interrupts
 */
uint32_t div_u32u32_unsafe(uint32_t a, uint32_t b);

/**
 * \brief Unsafe integer divide of two unsigned 32-bit values, with remainder
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \param [out] rem The remainder of dividend/divisor
 * \return Quotient result of dividend/divisor
 *
 * Do not use in interrupts
 */
uint32_t divmod_u32u32_rem_unsafe(uint32_t a, uint32_t b, uint32_t *rem);

/**
 * \brief Unsafe integer divide of two unsigned 32-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return quotient in low word/r0, remainder in high word/r1
 *
 * Do not use in interrupts
 */
uint64_t divmod_u32u32_unsafe(uint32_t a, uint32_t b);

/**
 * \brief Unsafe integer divide of two signed 64-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return Quotient
 *
 * Do not use in interrupts
 */
int64_t div_s64s64_unsafe(int64_t a, int64_t b);

/**
 * \brief Unsafe integer divide of two signed 64-bit values, with remainder
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \param [out] rem The remainder of dividend/divisor
 * \return Quotient result of dividend/divisor
 *
 * Do not use in interrupts
 */
int64_t divmod_s64s64_rem_unsafe(int64_t a, int64_t b, int64_t *rem);

/**
 * \brief Unsafe integer divide of two signed 64-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return quotient in result (r0,r1), remainder in regs (r2, r3)
 *
 * Do not use in interrupts
 */
int64_t divmod_s64s64_unsafe(int64_t a, int64_t b);

/**
 * \brief Unsafe integer divide of two unsigned 64-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return Quotient
 *
 * Do not use in interrupts
 */
uint64_t div_u64u64_unsafe(uint64_t a, uint64_t b);

/**
 * \brief Unsafe integer divide of two unsigned 64-bit values, with remainder
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \param [out] rem The remainder of dividend/divisor
 * \return Quotient result of dividend/divisor
 *
 * Do not use in interrupts
 */
uint64_t divmod_u64u64_rem_unsafe(uint64_t a, uint64_t b, uint64_t *rem);

/**
 * \brief Unsafe integer divide of two signed 64-bit values
 * \ingroup pico_divider
 *
 * \param a Dividend
 * \param b Divisor
 * \return quotient in result (r0,r1), remainder in regs (r2, r3)
 *
 * Do not use in interrupts
 */
uint64_t divmod_u64u64_unsafe(uint64_t a, uint64_t b);

#ifdef __cplusplus
}
#endif
#endif
