/* mbed Microcontroller Library - stackheap
 * Copyright (C) 2009-2015 ARM Limited. All rights reserved.
 *
 * Setup a fixed single stack/heap memory model,
 *  between the top of the RW/ZI region and the stackpointer
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <rt_misc.h>
#include <stdint.h>

extern char Image$$RW_IRAM1$$ZI$$Limit[];

extern __value_in_regs struct __initial_stackheap __user_setup_stackheap(uint32_t R0, uint32_t R1, uint32_t R2, uint32_t R3) {
    uint32_t zi_limit = (uint32_t)Image$$RW_IRAM1$$ZI$$Limit;
    uint32_t sp_limit = __current_sp();

    zi_limit = (zi_limit + 7) & ~0x7;    // ensure zi_limit is 8-byte aligned

    struct __initial_stackheap r;
    r.heap_base = zi_limit;
    r.heap_limit = sp_limit;
    return r;
}

#ifdef __cplusplus
}
#endif
