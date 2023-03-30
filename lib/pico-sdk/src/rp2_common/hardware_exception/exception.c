/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/exception.h"
#include "hardware/regs/m0plus.h"
#include "hardware/structs/scb.h"
#include "hardware/sync.h"
#include "pico/assert.h"

#ifndef exception_is_compile_time_default
static bool exception_is_compile_time_default(exception_handler_t handler) {
    extern char __default_isrs_start;
    extern char __default_isrs_end;
    return ((uintptr_t)handler) >= (uintptr_t)&__default_isrs_start &&
            ((uintptr_t)handler) < (uintptr_t)&__default_isrs_end;
}
#endif

static inline exception_handler_t *get_vtable(void) {
    return (exception_handler_t *) scb_hw->vtor;
}

static void set_raw_exception_handler_and_restore_interrupts(enum exception_number num, exception_handler_t handler, uint32_t save) {
    // update vtable (vtable_handler may be same or updated depending on cases, but we do it anyway for compactness)
    get_vtable()[16 + num] = handler;
    __dmb();
    restore_interrupts(save);
}

static inline void check_exception_param(__unused enum exception_number num) {
    invalid_params_if(EXCEPTION, num < NMI_EXCEPTION || num >=0);
}

exception_handler_t exception_get_vtable_handler(enum exception_number num) {
    check_exception_param(num);
    return get_vtable()[16 + num];
}

exception_handler_t exception_set_exclusive_handler(enum exception_number num, exception_handler_t handler) {
    check_exception_param(num);
#if !PICO_NO_RAM_VECTOR_TABLE
    uint32_t save = save_and_disable_interrupts();
    exception_handler_t current = exception_get_vtable_handler(num);
    hard_assert(handler == current || exception_is_compile_time_default(current));
    set_raw_exception_handler_and_restore_interrupts(num, handler, save);
#else
    panic_unsupported();
#endif
    return current;
}

void exception_restore_handler(enum exception_number num, exception_handler_t original_handler) {
    hard_assert(exception_is_compile_time_default(original_handler));
#if !PICO_NO_RAM_VECTOR_TABLE
    uint32_t save = save_and_disable_interrupts();
    set_raw_exception_handler_and_restore_interrupts(num, original_handler, save);
#else
    panic_unsupported();
#endif
}