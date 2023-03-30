/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/times.h>
#include <unistd.h>
#include "pico.h"

#include "hardware/regs/m0plus.h"
#include "hardware/regs/resets.h"
#include "hardware/structs/mpu.h"
#include "hardware/structs/scb.h"
#include "hardware/structs/padsbank0.h"

#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hardware/resets.h"

#include "pico/mutex.h"
#include "pico/time.h"

#if LIB_PICO_PRINTF_PICO
#include "pico/printf.h"
#else
#define weak_raw_printf printf
#define weak_raw_vprintf vprintf
#endif

#if PICO_ENTER_USB_BOOT_ON_EXIT
#include "pico/bootrom.h"
#endif

extern char __StackLimit; /* Set by linker.  */

uint32_t __attribute__((section(".ram_vector_table"))) ram_vector_table[48];

// this is called for each thread since they have their own MPU
void runtime_install_stack_guard(void *stack_bottom) {
    // this is called b4 runtime_init is complete, so beware printf or assert

    // make sure no one is using the MPU yet
    if (mpu_hw->ctrl) {
        // Note that it would be tempting to change this to a panic, but it happens so early, printing is not a good idea
        __breakpoint();
    }

    uintptr_t addr = (uintptr_t) stack_bottom;
    // the minimum we can protect is 32 bytes on a 32 byte boundary, so round up which will
    // just shorten the valid stack range a tad
    addr = (addr + 31u) & ~31u;

    // mask is 1 bit per 32 bytes of the 256 byte range... clear the bit for the segment we want
    uint32_t subregion_select = 0xffu ^ (1u << ((addr >> 5u) & 7u));
    mpu_hw->ctrl = 5; // enable mpu with background default map
    mpu_hw->rbar = (addr & (uint)~0xff) | M0PLUS_MPU_RBAR_VALID_BITS | 0;
    mpu_hw->rasr = 1 // enable region
                   | (0x7 << 1) // size 2^(7 + 1) = 256
                   | (subregion_select << 8)
                   | 0x10000000; // XN = disable instruction fetch; no other bits means no permissions
}

void runtime_init(void) {
    // Reset all peripherals to put system into a known state,
    // - except for QSPI pads and the XIP IO bank, as this is fatal if running from flash
    // - and the PLLs, as this is fatal if clock muxing has not been reset on this boot
    // - and USB, syscfg, as this disturbs USB-to-SWD on core 1
    reset_block(~(
            RESETS_RESET_IO_QSPI_BITS |
            RESETS_RESET_PADS_QSPI_BITS |
            RESETS_RESET_PLL_USB_BITS |
            RESETS_RESET_USBCTRL_BITS |
            RESETS_RESET_SYSCFG_BITS |
            RESETS_RESET_PLL_SYS_BITS
    ));

    // Remove reset from peripherals which are clocked only by clk_sys and
    // clk_ref. Other peripherals stay in reset until we've configured clocks.
    unreset_block_wait(RESETS_RESET_BITS & ~(
            RESETS_RESET_ADC_BITS |
            RESETS_RESET_RTC_BITS |
            RESETS_RESET_SPI0_BITS |
            RESETS_RESET_SPI1_BITS |
            RESETS_RESET_UART0_BITS |
            RESETS_RESET_UART1_BITS |
            RESETS_RESET_USBCTRL_BITS
    ));

    // pre-init runs really early since we need it even for memcpy and divide!
    // (basically anything in aeabi that uses bootrom)

    // Start and end points of the constructor list,
    // defined by the linker script.
    extern void (*__preinit_array_start)(void);
    extern void (*__preinit_array_end)(void);

    // Call each function in the list.
    // We have to take the address of the symbols, as __preinit_array_start *is*
    // the first function pointer, not the address of it.
    for (void (**p)(void) = &__preinit_array_start; p < &__preinit_array_end; ++p) {
        (*p)();
    }

    // After calling preinit we have enough runtime to do the exciting maths
    // in clocks_init
    clocks_init();

    // Peripheral clocks should now all be running
    unreset_block_wait(RESETS_RESET_BITS);

#if !PICO_IE_26_29_UNCHANGED_ON_RESET
    // after resetting BANK0 we should disable IE on 26-29
    hw_clear_alias(padsbank0_hw)->io[26] = hw_clear_alias(padsbank0_hw)->io[27] =
            hw_clear_alias(padsbank0_hw)->io[28] = hw_clear_alias(padsbank0_hw)->io[29] = PADS_BANK0_GPIO0_IE_BITS;
#endif

    // this is an array of either mutex_t or recursive_mutex_t (i.e. not necessarily the same size)
    // however each starts with a lock_core_t, and the spin_lock is initialized to address 1 for a recursive
    // spinlock and 0 for a regular one.

    static_assert(!(sizeof(mutex_t)&3), "");
    static_assert(!(sizeof(recursive_mutex_t)&3), "");
    static_assert(!offsetof(mutex_t, core), "");
    static_assert(!offsetof(recursive_mutex_t, core), "");
    extern lock_core_t __mutex_array_start;
    extern lock_core_t __mutex_array_end;

    for (lock_core_t *l = &__mutex_array_start; l < &__mutex_array_end; ) {
        if (l->spin_lock) {
            assert(1 == (uintptr_t)l->spin_lock); // indicator for a recursive mutex
            recursive_mutex_t *rm = (recursive_mutex_t *)l;
            recursive_mutex_init(rm);
            l = &rm[1].core; // next
        } else {
            mutex_t *m = (mutex_t *)l;
            mutex_init(m);
            l = &m[1].core; // next
        }
    }

#if !(PICO_NO_RAM_VECTOR_TABLE || PICO_NO_FLASH)
    __builtin_memcpy(ram_vector_table, (uint32_t *) scb_hw->vtor, sizeof(ram_vector_table));
    scb_hw->vtor = (uintptr_t) ram_vector_table;
#endif

#ifndef NDEBUG
    if (__get_current_exception()) {
        // crap; started in exception handler
        __asm ("bkpt #0");
    }
#endif

#if PICO_USE_STACK_GUARDS
    // install core0 stack guard
    extern char __StackBottom;
    runtime_install_stack_guard(&__StackBottom);
#endif

    spin_locks_reset();
    irq_init_priorities();
    alarm_pool_init_default();

    // Start and end points of the constructor list,
    // defined by the linker script.
    extern void (*__init_array_start)(void);
    extern void (*__init_array_end)(void);

    // Call each function in the list.
    // We have to take the address of the symbols, as __init_array_start *is*
    // the first function pointer, not the address of it.
    for (void (**p)(void) = &__init_array_start; p < &__init_array_end; ++p) {
        (*p)();
    }

}

void __attribute__((noreturn)) __attribute__((weak)) _exit(__unused int status) {
#if PICO_ENTER_USB_BOOT_ON_EXIT
    reset_usb_boot(0,0);
#else
    while (1) {
        __breakpoint();
    }
#endif
}

__attribute__((weak)) void *_sbrk(int incr) {
    extern char end; /* Set by linker.  */
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
        heap_end = &end;

    prev_heap_end = heap_end;
    char *next_heap_end = heap_end + incr;

    if (__builtin_expect(next_heap_end > (&__StackLimit), false)) {
#if PICO_USE_OPTIMISTIC_SBRK
        if (heap_end == &__StackLimit) {
//        errno = ENOMEM;
            return (char *) -1;
        }
        next_heap_end = &__StackLimit;
#else
        return (char *) -1;
#endif
    }

    heap_end = next_heap_end;
    return (void *) prev_heap_end;
}

static int64_t epoch_time_us_since_boot;

__attribute__((weak)) int _gettimeofday (struct timeval *__restrict tv, __unused void *__restrict tz) {
    if (tv) {
        int64_t us_since_epoch = ((int64_t)to_us_since_boot(get_absolute_time())) - epoch_time_us_since_boot;
        tv->tv_sec = (time_t)(us_since_epoch / 1000000);
        tv->tv_usec = (suseconds_t)(us_since_epoch % 1000000);
    }
    return 0;
}

__attribute((weak)) int settimeofday(__unused const struct timeval *tv, __unused const struct timezone *tz) {
    if (tv) {
        int64_t us_since_epoch = tv->tv_sec * 1000000 + tv->tv_usec;
        epoch_time_us_since_boot = (int64_t)to_us_since_boot(get_absolute_time()) - us_since_epoch;
    }
    return 0;
}

__attribute((weak)) int _times(struct tms *tms) {
#if CLOCKS_PER_SEC >= 1000000
    tms->tms_utime = (clock_t)(to_us_since_boot(get_absolute_time()) * (CLOCKS_PER_SEC / 1000000));
#else
    tms->tms_utime = (clock_t)(to_us_since_boot(get_absolute_time()) / (1000000 / CLOCKS_PER_SEC));
#endif
    tms->tms_stime = 0;
    tms->tms_cutime = 0;
    tms->tms_cstime = 0;
    return 0;
}

__attribute((weak)) pid_t _getpid(void) {
    return 0;
}

__attribute((weak)) int _kill(__unused pid_t pid, __unused int sig) {
    return -1;
}

// exit is not useful... no desire to pull in __call_exitprocs
void exit(int status) {
    _exit(status);
}

// incorrect warning from GCC 6
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsuggest-attribute=format"
void __assert_func(const char *file, int line, const char *func, const char *failedexpr) {
    weak_raw_printf("assertion \"%s\" failed: file \"%s\", line %d%s%s\n",
           failedexpr, file, line, func ? ", function: " : "",
           func ? func : "");

    _exit(1);
}

#pragma GCC diagnostic pop

void __attribute__((noreturn)) panic_unsupported() {
    panic("not supported");
}

// PICO_CONFIG: PICO_PANIC_FUNCTION, Name of a function to use in place of the stock panic function or empty string to simply breakpoint on panic, group=pico_runtime
// note the default is not "panic" it is undefined
#ifdef PICO_PANIC_FUNCTION
#define PICO_PANIC_FUNCTION_EMPTY (__CONCAT(PICO_PANIC_FUNCTION, 1) == 1)
#if !PICO_PANIC_FUNCTION_EMPTY
extern void __attribute__((noreturn)) __printflike(1, 0) PICO_PANIC_FUNCTION(__unused const char *fmt, ...);
#endif
// Use a forwarding method here as it is a little simpler than renaming the symbol as it is used from assembler
void __attribute__((naked, noreturn)) __printflike(1, 0) panic(__unused const char *fmt, ...) {
    // if you get an undefined reference here, you didn't define your PICO_PANIC_FUNCTION!
    __asm (
            "push {lr}\n"
#if !PICO_PANIC_FUNCTION_EMPTY
            "bl " __XSTRING(PICO_PANIC_FUNCTION) "\n"
#endif
            "bkpt #0\n"
            "1: b 1b\n" // loop for ever as we are no return
        :
        :
        :
    );
}
#else
// todo consider making this try harder to output if we panic early
//  right now, print mutex may be uninitialised (in which case it deadlocks - although after printing "PANIC")
//  more importantly there may be no stdout/UART initialized yet
// todo we may want to think about where we print panic messages to; writing to USB appears to work
//  though it doesn't seem like we can expect it to... fine for now
void __attribute__((noreturn)) __printflike(1, 0) panic(const char *fmt, ...) {
    puts("\n*** PANIC ***\n");
    if (fmt) {
#if LIB_PICO_PRINTF_NONE
        puts(fmt);
#else
        va_list args;
        va_start(args, fmt);
#if PICO_PRINTF_ALWAYS_INCLUDED
        vprintf(fmt, args);
#else
        weak_raw_vprintf(fmt, args);
#endif
        va_end(args);
        puts("\n");
#endif
    }

    _exit(1);
}
#endif

void hard_assertion_failure(void) {
    panic("Hard assert");
}
