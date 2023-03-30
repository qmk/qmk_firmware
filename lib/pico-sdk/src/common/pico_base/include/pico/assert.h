/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_ASSERT_H
#define _PICO_ASSERT_H

#include <stdbool.h>

#ifdef __cplusplus

#include <cassert>

extern "C" {
#else
#include <assert.h>
#endif

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLE_ALL, Global assert enable, type=bool, default=0, group=pico_base
// PICO_CONFIG: PARAM_ASSERTIONS_DISABLE_ALL, Global assert disable, type=bool, default=0, group=pico_base

#ifndef PARAM_ASSERTIONS_ENABLE_ALL
#define PARAM_ASSERTIONS_ENABLE_ALL 0
#endif

#ifndef PARAM_ASSERTIONS_DISABLE_ALL
#define PARAM_ASSERTIONS_DISABLE_ALL 0
#endif

#define PARAM_ASSERTIONS_ENABLED(x) ((PARAM_ASSERTIONS_ENABLED_ ## x || PARAM_ASSERTIONS_ENABLE_ALL) && !PARAM_ASSERTIONS_DISABLE_ALL)

#define invalid_params_if(x, test) ({if (PARAM_ASSERTIONS_ENABLED(x)) assert(!(test));})
#define valid_params_if(x, test) ({if (PARAM_ASSERTIONS_ENABLED(x)) assert(test);})
#define hard_assert_if(x, test) ({if (PARAM_ASSERTIONS_ENABLED(x)) hard_assert(!(test));})

#ifdef NDEBUG
extern void hard_assertion_failure(void);
static inline void hard_assert(bool condition, ...) {
    if (!condition)
        hard_assertion_failure();
}
#else
#define hard_assert assert
#endif

#ifdef __cplusplus
}
#endif
#endif
