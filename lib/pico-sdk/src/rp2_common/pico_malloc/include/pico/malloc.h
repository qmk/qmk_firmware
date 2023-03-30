/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_MALLOC_H
#define _PICO_MALLOC_H

/** \file malloc.h
*  \defgroup pico_malloc pico_malloc
*
* Multi-core safety for malloc, calloc and free
*
* This library does not provide any additional functions
*/

// PICO_CONFIG: PICO_USE_MALLOC_MUTEX, Whether to protect malloc etc with a mutex, type=bool, default=1 with pico_multicore, 0 otherwise, group=pico_malloc
#if LIB_PICO_MULTICORE && !defined(PICO_USE_MALLOC_MUTEX)
#define PICO_USE_MALLOC_MUTEX 1
#endif

// PICO_CONFIG: PICO_MALLOC_PANIC, Enable/disable panic when an allocation failure occurs, type=bool, default=1, group=pico_malloc
#ifndef PICO_MALLOC_PANIC
#define PICO_MALLOC_PANIC 1
#endif

// PICO_CONFIG: PICO_DEBUG_MALLOC, Enable/disable debug printf from malloc, type=bool, default=0, group=pico_malloc
#ifndef PICO_DEBUG_MALLOC
#define PICO_DEBUG_MALLOC 0
#endif

// PICO_CONFIG: PICO_DEBUG_MALLOC_LOW_WATER, Define the lower bound for allocation addresses to be printed by PICO_DEBUG_MALLOC, min=0, default=0, group=pico_malloc
#ifndef PICO_DEBUG_MALLOC_LOW_WATER
#define PICO_DEBUG_MALLOC_LOW_WATER 0
#endif

#endif