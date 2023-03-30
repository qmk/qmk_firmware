/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdio/driver.h"
#include "pico/stdio_semihosting.h"
#include "pico/binary_info.h"

static void stdio_semihosting_out_chars(const char *buf, int length) {
    // must be volatile or the buffer gets put in registers & optimized away
    volatile struct {
        // https://developer.arm.com/documentation/dui0375/g/What-is-Semihosting-/SYS-WRITE--0x05-
        // arguments, in order:
        // word 0 = file handle (1 = stdout)
        // word 1 = pointer to buffer
        // word 2 = length of buffer
        size_t fd;
        const char *buf;
        size_t len;
    } args;

    args.fd = 1;  // 1 = stdout
    args.buf = buf;
    args.len = length;

    __asm (
    // r1 must contain a pointer to the arguments
    "mov r1, %[args]\n"
    // semihosting call number 0x05 = SYS_WRITE
    "mov r0, #5\n"
    // make the semihosting call: https://developer.arm.com/documentation/dui0375/g/What-is-Semihosting-/The-semihosting-interface
    "bkpt 0xab\n"
    :
    : [args] "r" (&args)
    : "r0", "r1");
}

stdio_driver_t stdio_semihosting = {
        .out_chars = stdio_semihosting_out_chars,
#if PICO_STDIO_ENABLE_CRLF_SUPPORT
        .crlf_enabled = PICO_STDIO_SEMIHOSTING_DEFAULT_CRLF
#endif
};

void stdio_semihosting_init() {
#if !PICO_NO_BI_STDIO_SEMIHOSTING
    bi_decl_if_func_used(bi_program_feature("semihosting stdout"));
#endif
    stdio_set_driver_enabled(&stdio_semihosting, true);
}

