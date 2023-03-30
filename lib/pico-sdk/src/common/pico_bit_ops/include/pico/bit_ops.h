/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_BIT_OPS_H
#define _PICO_BIT_OPS_H

#include "pico.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file bit_ops.h
*  \defgroup pico_bit_ops pico_bit_ops
*
* Optimized bit manipulation functions.
* Additionally provides  replacement implementations of the compiler built-ins __builtin_popcount, __builtin_clz
* and __bulitin_ctz
*/

/*! \brief Reverse the bits in a 32 bit word
 *  \ingroup pico_bit_ops
 *
 * \param bits 32 bit input
 * \return the 32 input bits reversed
 */
uint32_t __rev(uint32_t bits);

/*! \brief Reverse the bits in a 64 bit double word
 *  \ingroup pico_bit_ops
 *
 * \param bits 64 bit input
 * \return the 64 input bits reversed
 */
uint64_t __revll(uint64_t bits);

#ifdef __cplusplus
}
#endif

#endif
