/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/multicore.h"
#include "hardware/sync.h"
#include "hardware/irq.h"
#include "hardware/structs/scb.h"
#include "hardware/structs/sio.h"
#include "hardware/regs/psm.h"
#include "hardware/claim.h"
#if PICO_USE_STACK_GUARDS
#include "pico/runtime.h"
#endif

static inline void multicore_fifo_push_blocking_inline(uint32_t data) {
    // We wait for the fifo to have some space
    while (!multicore_fifo_wready())
        tight_loop_contents();

    sio_hw->fifo_wr = data;

    // Fire off an event to the other core
    __sev();
}

void multicore_fifo_push_blocking(uint32_t data) {
    multicore_fifo_push_blocking_inline(data);
}

bool multicore_fifo_push_timeout_us(uint32_t data, uint64_t timeout_us) {
    absolute_time_t end_time = make_timeout_time_us(timeout_us);
    // We wait for the fifo to have some space
    while (!multicore_fifo_wready()) {
        tight_loop_contents();
        if (time_reached(end_time)) return false;
    }

    sio_hw->fifo_wr = data;

    // Fire off an event to the other core
    __sev();
    return true;
}

static inline uint32_t multicore_fifo_pop_blocking_inline(void) {
    // If nothing there yet, we wait for an event first,
    // to try and avoid too much busy waiting
    while (!multicore_fifo_rvalid())
        __wfe();

    return sio_hw->fifo_rd;
}

uint32_t multicore_fifo_pop_blocking() {
    return multicore_fifo_pop_blocking_inline();
}

bool multicore_fifo_pop_timeout_us(uint64_t timeout_us, uint32_t *out) {
    absolute_time_t end_time = make_timeout_time_us(timeout_us);
    // If nothing there yet, we wait for an event first,
    // to try and avoid too much busy waiting
    while (!multicore_fifo_rvalid()) {
        __wfe();
        if (time_reached(end_time)) return false;
    }

    *out = sio_hw->fifo_rd;
    return true;
}

// Default stack for core1 ... if multicore_launch_core1 is not included then .stack1 section will be garbage collected
static uint32_t __attribute__((section(".stack1"))) core1_stack[PICO_CORE1_STACK_SIZE / sizeof(uint32_t)];

static void __attribute__ ((naked)) core1_trampoline(void) {
    __asm("pop {r0, r1, pc}");
}

int core1_wrapper(int (*entry)(void), void *stack_base) {
#if PICO_USE_STACK_GUARDS
    // install core1 stack guard
    runtime_install_stack_guard(stack_base);
#else
    __unused void *ignore = stack_base;
#endif
    irq_init_priorities();
    return (*entry)();
}

void multicore_reset_core1() {
    // Use atomic aliases just in case core 1 is also manipulating some PSM state
    io_rw_32 *power_off = (io_rw_32 *) (PSM_BASE + PSM_FRCE_OFF_OFFSET);
    io_rw_32 *power_off_set = hw_set_alias(power_off);
    io_rw_32 *power_off_clr = hw_clear_alias(power_off);

    // Hard-reset core 1.
    // Reading back confirms the core 1 reset is in the correct state, but also
    // forces APB IO bridges to fence on any internal store buffering
    *power_off_set = PSM_FRCE_OFF_PROC1_BITS;
    while (!(*power_off & PSM_FRCE_OFF_PROC1_BITS)) tight_loop_contents();

    // Bring core 1 back out of reset. It will drain its own mailbox FIFO, then push
    // a 0 to our mailbox to tell us it has done this.
    *power_off_clr = PSM_FRCE_OFF_PROC1_BITS;
}

void multicore_launch_core1_with_stack(void (*entry)(void), uint32_t *stack_bottom, size_t stack_size_bytes) {
    assert(!(stack_size_bytes & 3u));
    uint32_t *stack_ptr = stack_bottom + stack_size_bytes / sizeof(uint32_t);
    // push 2 values onto top of stack for core1_trampoline
    stack_ptr -= 3;
    stack_ptr[0] = (uintptr_t) entry;
    stack_ptr[1] = (uintptr_t) stack_bottom;
    stack_ptr[2] = (uintptr_t) core1_wrapper;
#if PICO_VTABLE_PER_CORE
#warning PICO_VTABLE_PER_CORE==1 is not currently supported in pico_multicore
    panic_unsupported();
#endif
    multicore_launch_core1_raw(core1_trampoline, stack_ptr, scb_hw->vtor);
}

void multicore_launch_core1(void (*entry)(void)) {
    extern uint32_t __StackOneBottom;
    uint32_t *stack_limit = (uint32_t *) &__StackOneBottom;
    // hack to reference core1_stack although that pointer is wrong.... core1_stack should always be <= stack_limit, if not boom!
    uint32_t *stack = core1_stack <= stack_limit ? stack_limit : (uint32_t *) -1;
    multicore_launch_core1_with_stack(entry, stack, sizeof(core1_stack));
}

void multicore_launch_core1_raw(void (*entry)(void), uint32_t *sp, uint32_t vector_table) {
    // Allow for the fact that the caller may have already enabled the FIFO IRQ for their
    // own purposes (expecting FIFO content after core 1 is launched). We must disable
    // the IRQ during the handshake, then restore afterwards.
    bool enabled = irq_is_enabled(SIO_IRQ_PROC0);
    irq_set_enabled(SIO_IRQ_PROC0, false);

    // Values to be sent in order over the FIFO from core 0 to core 1
    //
    // vector_table is value for VTOR register
    // sp is initial stack pointer (SP)
    // entry is the initial program counter (PC) (don't forget to set the thumb bit!)
    const uint32_t cmd_sequence[] =
            {0, 0, 1, (uintptr_t) vector_table, (uintptr_t) sp, (uintptr_t) entry};

    uint seq = 0;
    do {
        uint cmd = cmd_sequence[seq];
        // Always drain the READ FIFO (from core 1) before sending a 0
        if (!cmd) {
            multicore_fifo_drain();
            // Execute a SEV as core 1 may be waiting for FIFO space via WFE
            __sev();
        }
        multicore_fifo_push_blocking(cmd);
        uint32_t response = multicore_fifo_pop_blocking();
        // Move to next state on correct response (echo-d value) otherwise start over
        seq = cmd == response ? seq + 1 : 0;
    } while (seq < count_of(cmd_sequence));

    irq_set_enabled(SIO_IRQ_PROC0, enabled);
}

#define LOCKOUT_MAGIC_START 0x73a8831eu
#define LOCKOUT_MAGIC_END (~LOCKOUT_MAGIC_START)

static_assert(SIO_IRQ_PROC1 == SIO_IRQ_PROC0 + 1, "");

static mutex_t lockout_mutex;
static bool lockout_in_progress;

// note this method is in RAM because lockout is used when writing to flash
// it only makes inline calls
static void __isr __not_in_flash_func(multicore_lockout_handler)(void) {
    multicore_fifo_clear_irq();
    while (multicore_fifo_rvalid()) {
        if (sio_hw->fifo_rd == LOCKOUT_MAGIC_START) {
            uint32_t save = save_and_disable_interrupts();
            multicore_fifo_push_blocking_inline(LOCKOUT_MAGIC_START);
            while (multicore_fifo_pop_blocking_inline() != LOCKOUT_MAGIC_END) {
                tight_loop_contents(); // not tight but endless potentially
            }
            restore_interrupts(save);
            multicore_fifo_push_blocking_inline(LOCKOUT_MAGIC_END);
        }
    }
}

static void check_lockout_mutex_init(void) {
    // use known available lock - we only need it briefly
    uint32_t save = hw_claim_lock();
    if (!mutex_is_initialized(&lockout_mutex)) {
        mutex_init(&lockout_mutex);
    }
    hw_claim_unlock(save);
}

void multicore_lockout_victim_init() {
    check_lockout_mutex_init();
    uint core_num = get_core_num();
    irq_set_exclusive_handler(SIO_IRQ_PROC0 + core_num, multicore_lockout_handler);
    irq_set_enabled(SIO_IRQ_PROC0 + core_num, true);
}

static bool multicore_lockout_handshake(uint32_t magic, absolute_time_t until) {
    uint irq_num = SIO_IRQ_PROC0 + get_core_num();
    bool enabled = irq_is_enabled(irq_num);
    if (enabled) irq_set_enabled(irq_num, false);
    bool rc = false;
    do {
        int64_t next_timeout_us = absolute_time_diff_us(get_absolute_time(), until);
        if (next_timeout_us < 0) {
            break;
        }
        multicore_fifo_push_timeout_us(magic, (uint64_t)next_timeout_us);
        next_timeout_us = absolute_time_diff_us(get_absolute_time(), until);
        if (next_timeout_us < 0) {
            break;
        }
        uint32_t word = 0;
        if (!multicore_fifo_pop_timeout_us((uint64_t)next_timeout_us, &word)) {
            break;
        }
        if (word == magic) {
            rc = true;
        }
    } while (!rc);
    if (enabled) irq_set_enabled(irq_num, true);
    return rc;
}

static bool multicore_lockout_start_block_until(absolute_time_t until) {
    check_lockout_mutex_init();
    if (!mutex_enter_block_until(&lockout_mutex, until)) {
        return false;
    }
    hard_assert(!lockout_in_progress);
    bool rc = multicore_lockout_handshake(LOCKOUT_MAGIC_START, until);
    lockout_in_progress = rc;
    mutex_exit(&lockout_mutex);
    return rc;
}

bool multicore_lockout_start_timeout_us(uint64_t timeout_us) {
    return multicore_lockout_start_block_until(make_timeout_time_us(timeout_us));
}

void multicore_lockout_start_blocking() {
    multicore_lockout_start_block_until(at_the_end_of_time);
}

static bool multicore_lockout_end_block_until(absolute_time_t until) {
    assert(mutex_is_initialized(&lockout_mutex));
    if (!mutex_enter_block_until(&lockout_mutex, until)) {
        return false;
    }
    assert(lockout_in_progress);
    bool rc = multicore_lockout_handshake(LOCKOUT_MAGIC_END, until);
    if (rc) {
        lockout_in_progress = false;
    }
    mutex_exit(&lockout_mutex);
    return rc;
}

bool multicore_lockout_end_timeout_us(uint64_t timeout_us) {
    return multicore_lockout_end_block_until(make_timeout_time_us(timeout_us));
}

void multicore_lockout_end_blocking() {
    multicore_lockout_end_block_until(at_the_end_of_time);
}
