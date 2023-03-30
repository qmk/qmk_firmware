/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <inttypes.h>
#include "pico/stdlib.h"
#include "pico/bit_ops.h"
#include <stdlib.h>

void test_builtin_bitops() {
    int32_t x = 0;
    for (uint32_t i = 0; i < 10000; i++) {
        uint32_t vals32[] = {
                i,
                1u << (i & 31u),
                i * 12355821u,
        };
        uint64_t vals64[] = {
                i,
                1ull << (i & 63u),
                i * 12345678123125ull,
        };
        for(int j=0; j<count_of(vals32); j++) {
            x += __builtin_popcount(vals32[j]);
            x += __builtin_popcountl(vals32[j]);
            x += (int32_t)__rev(vals32[j]);
#if !PICO_ON_DEVICE
            // the following functions are undefined on host mode, but on RP2040 we return 32
            if (vals32[j]) {
                x += __builtin_clz(vals32[j]);
                x += __builtin_ctz(vals32[j]);
            } else {
                x += 64;
            }
#else
            x += __builtin_clz(vals32[j]);
            x += __builtin_ctz(vals32[j]);
            // check l variants are the same
            if (__builtin_clz(vals32[j]) != __builtin_clzl(vals32[j])) x += 17;
            if (__builtin_ctz(vals32[j]) != __builtin_ctzl(vals32[j])) x += 23;
#endif
        }
        for(int j=0; j<count_of(vals64); j++) {
            x += __builtin_popcountll(vals64[j]);
            x += (int32_t)__revll(vals64[j]);
#if !PICO_ON_DEVICE
            // the following functions are undefined on host mode, but on RP2040 we return 64
            if (!vals64[j]) {
                x += 128;
                continue;
            }
#endif
            x += __builtin_clzll(vals64[j]);
            x += __builtin_ctzll(vals64[j]);
        }
    }
    printf("Count is %d\n", (int)x);
    int32_t expected = 1475508680;
    if (x != expected) {
        printf("FAILED (expected count %d\n", (int) expected);
        exit(1);
    }
}

int main() {
    setup_default_uart();

    puts("Hellox, world!");
    printf("Hello world %d\n", 2);
#if PICO_NO_HARDWARE
    puts("This is native");
#endif
#if PICO_NO_FLASH
    puts("This is no flash");
#endif

    for (int i = 0; i < 64; i++) {
        uint32_t x = 1 << i;
        uint64_t xl = 1ull << i;
//        printf("%d %u %u %u %u \n", i, (uint)(x%10u), (uint)(x%16u), (uint)(xl %10u), (uint)(xl%16u));
        printf("%08x %08x %016llx %016llx\n", (uint) x, (uint) __rev(x), (unsigned long long) xl,
               (unsigned long long) __revll(xl));
    }

    test_builtin_bitops();

    for (int i = 0; i < 8; i++) {
        sleep_ms(500);
        printf( "%" PRIu64 "\n", to_us_since_boot(get_absolute_time()));
    }
    absolute_time_t until = delayed_by_us(get_absolute_time(), 500000);
    printf("\n");
    for (int i = 0; i < 8; i++) {
        sleep_until(until);
        printf("%" PRIu64 "\n", to_us_since_boot(get_absolute_time()));
        until = delayed_by_us(until, 500000);
    }
    puts("DONE");
}
