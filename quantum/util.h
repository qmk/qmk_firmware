// Copyright 2022 Stefan Kerkmann (KarlK90)
// Copyright 2011 Jun Wako <wakojun@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

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

#if !defined(ARRAY_SIZE)
/**
 * @brief Computes the number of elements of the given array at compile time.
 * This Macro can only be used for statically allocated arrays that have not
 * been decayed into a pointer.
 */
#    define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#endif
