/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <stdio.h>
#include "pico.h"
#include "pico/malloc.h"

#if PICO_USE_MALLOC_MUTEX
#include "pico/mutex.h"
auto_init_mutex(malloc_mutex);
#endif

extern void *__real_malloc(size_t size);
extern void *__real_calloc(size_t count, size_t size);
extern void *__real_realloc(void *mem, size_t size);
extern void __real_free(void *mem);

extern char __StackLimit; /* Set by linker.  */

static inline void check_alloc(__unused void *mem, __unused uint size) {
#if PICO_MALLOC_PANIC
    if (!mem || (((char *)mem) + size) > &__StackLimit) {
        panic("Out of memory");
    }
#endif
}

void *__wrap_malloc(size_t size) {
#if PICO_USE_MALLOC_MUTEX
    mutex_enter_blocking(&malloc_mutex);
#endif
    void *rc = __real_malloc(size);
#if PICO_USE_MALLOC_MUTEX
    mutex_exit(&malloc_mutex);
#endif
#if PICO_DEBUG_MALLOC
    if (!rc || ((uint8_t *)rc) + size > (uint8_t*)PICO_DEBUG_MALLOC_LOW_WATER) {
        printf("malloc %d %p->%p\n", (uint) size, rc, ((uint8_t *) rc) + size);
    }
#endif
    check_alloc(rc, size);
    return rc;
}

void *__wrap_calloc(size_t count, size_t size) {
#if PICO_USE_MALLOC_MUTEX
    mutex_enter_blocking(&malloc_mutex);
#endif
    void *rc = __real_calloc(count, size);
#if PICO_USE_MALLOC_MUTEX
    mutex_exit(&malloc_mutex);
#endif
#if PICO_DEBUG_MALLOC
    if (!rc || ((uint8_t *)rc) + size > (uint8_t*)PICO_DEBUG_MALLOC_LOW_WATER) {
        printf("calloc %d %p->%p\n", (uint) (count * size), rc, ((uint8_t *) rc) + size);
    }
#endif
    check_alloc(rc, size);
    return rc;
}

void *__wrap_realloc(void *mem, size_t size) {
#if PICO_USE_MALLOC_MUTEX
    mutex_enter_blocking(&malloc_mutex);
#endif
    void *rc = __real_realloc(mem, size);
#if PICO_USE_MALLOC_MUTEX
    mutex_exit(&malloc_mutex);
#endif
#if PICO_DEBUG_MALLOC
    if (!rc || ((uint8_t *)rc) + size > (uint8_t*)PICO_DEBUG_MALLOC_LOW_WATER) {
        printf("realloc %p %d->%p\n", mem, (uint) size, rc);
    }
#endif
    check_alloc(rc, size);
    return rc;
}

void __wrap_free(void *mem) {
#if PICO_USE_MALLOC_MUTEX
    mutex_enter_blocking(&malloc_mutex);
#endif
    __real_free(mem);
#if PICO_USE_MALLOC_MUTEX
    mutex_exit(&malloc_mutex);
#endif
}
