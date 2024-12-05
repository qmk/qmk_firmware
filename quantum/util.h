// Copyright 2022 Stefan Kerkmann (KarlK90)
// Copyright 2011 Jun Wako <wakojun@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "bits.h"
#include "bitwise.h"

// convert to string
#define STR(s) XSTR(s)
#define XSTR(s) #s

#if !defined(MIN)
#    define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

#if !defined(MAX)
#    define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif

#if !defined(CEILING)
/**
 * @brief Computes the rounded up result of a division of two integers at
 * compile time.
 */
#    define CEILING(dividend, divisor) (((dividend) + (divisor)-1) / (divisor))
#endif

#if !defined(IS_ARRAY)
/**
 * @brief Returns true if the value is an array, false if it's a pointer.
 *
 * This macro is ill-formed for scalars, which is OK for its intended use in
 * ARRAY_SIZE.
 */
#    define IS_ARRAY(value) (!__builtin_types_compatible_p(typeof((value)), typeof(&(value)[0])))
#endif

#if !defined(ARRAY_SIZE)
/**
 * @brief Computes the number of elements of the given array at compile time.
 *
 * This Macro can only be used for statically allocated arrays that have not
 * been decayed into a pointer. This is detected at compile time, though the
 * error message for scalar values is poor.
 */
#    define ARRAY_SIZE(array) (__builtin_choose_expr(IS_ARRAY((array)), sizeof((array)) / sizeof((array)[0]), (void)0))
#endif

#if !defined(PACKED)
#    define PACKED __attribute__((__packed__))
#endif

#if __has_include("_util.h")
#    include "_util.h" /* Include the platform's _util.h */
#endif
