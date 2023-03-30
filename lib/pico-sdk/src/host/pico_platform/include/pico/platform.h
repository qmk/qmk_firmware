/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_PLATFORM_H
#define _PICO_PLATFORM_H

#include "hardware/platform_defs.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __unix__

#include <sys/cdefs.h>

#endif

#ifdef __cplusplus
extern "C" {
#endif

#define __not_in_flash(group)
#define __not_in_flash_func(func) func
#define __no_inline_not_in_flash_func(func) func
#define __in_flash(group)
#define __scratch_x(group)
#define __scratch_y(group)

#ifndef _MSC_VER
#define __packed __attribute__((packed))
#define __packed_aligned __packed __attribute((aligned))
#else
// MSVC requires #pragma pack which isn't compatible with a single attribute style define
#define __packed
#define __packed_aligned
#endif

#define __time_critical_func(x) x
#define __after_data(group)

//int running_on_fpga() { return false; }
extern void tight_loop_contents();

#ifndef __STRING
#define __STRING(x) #x
#endif

#ifndef _MSC_VER
#ifndef __noreturn
#define __noreturn __attribute((noreturn))
#endif

#ifndef __unused
#define __unused __attribute__((unused))
#endif

#ifndef __noinline
#define __noinline __attribute__((noinline))
#endif

#ifndef __aligned
#define __aligned(x) __attribute__((aligned(x)))
#endif

#define PICO_WEAK_FUNCTION_DEF(x) _Pragma(__STRING(weak x))
#define PICO_WEAK_FUNCTION_IMPL_NAME(x) x

#else
#ifndef __noreturn
#define __noreturn __declspec(noreturn)
#endif

#ifndef __unused
#define __unused
#endif

#ifndef __noinline
#define __noinline __declspec(noinline)
#endif

#ifndef __aligned
#define __aligned(x) __declspec(align(x))
#endif

#ifndef __CONCAT
#define __CONCAT(x,y) x ## y
#endif

#define __thread __declspec( thread )

#define PICO_WEAK_FUNCTION_DEF(x) __pragma(comment(linker, __STRING(/alternatename:_##x=_##x##__weak)));
#define PICO_WEAK_FUNCTION_IMPL_NAME(x) x ## __weak

static __noreturn void __builtin_unreachable() {
}

#include <intrin.h>
#define __builtin_clz __lzcnt
#endif

#ifndef count_of
#define count_of(a) (sizeof(a)/sizeof((a)[0]))
#endif

#ifndef MAX
#define MAX(a, b) ((a)>(b)?(a):(b))
#endif

#ifndef MIN
#define MIN(a, b) ((b)>(a)?(a):(b))
#endif

// abort in our case
void __noreturn __breakpoint();

void __noreturn panic_unsupported();

void __noreturn panic(const char *fmt, ...);

// arggggghhhh there is a weak function called sem_init used by SDL
#define sem_init sem_init_alternative

extern uint32_t host_safe_hw_ptr_impl(uintptr_t x);
// return a 32 bit handle for a raw ptr; DMA chaining for example embeds pointers in 32 bit values
// which of course does not work if we're running the code natively on a 64 bit platforms. Therefore
// we provide this macro which allows that code to provide a 64->32 bit mapping in host mode
#define host_safe_hw_ptr(x) host_safe_hw_ptr_impl((uintptr_t)(x))
void *decode_host_safe_hw_ptr(uint32_t ptr);

#define __fast_mul(a,b) ((a)*(b))

typedef unsigned int uint;

static inline int32_t __mul_instruction(int32_t a,int32_t b)
{
    return a*b;
}

static inline void __compiler_memory_barrier(void) {
}

uint get_core_num();

static inline uint __get_current_exception(void) {
    return 0;
}
#ifdef __cplusplus
}
#endif
#endif
