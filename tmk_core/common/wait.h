#pragma once

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ARMEL__) || defined(__ARMEB__)
#    ifndef __OPTIMIZE__
#        pragma message "Compiler optimizations disabled; wait_cpuclock() won't work as designed"
#    endif

#    define wait_cpuclock(x) wait_cpuclock_allnop(x)

#    define CLOCK_DELAY_NOP8 "nop\n\t nop\n\t nop\n\t nop\n\t   nop\n\t nop\n\t nop\n\t nop\n\t"

__attribute__((always_inline)) static inline void wait_cpuclock_allnop(unsigned int n) { /* n: 1..135 */
    /* The argument n must be a constant expression.
     * That way, compiler optimization will remove unnecessary code. */
    if (n < 1) {
        return;
    }
    if (n > 8) {
        unsigned int n8 = n / 8;
        n               = n - n8 * 8;
        switch (n8) {
            case 16:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 15:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 14:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 13:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 12:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 11:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 10:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 9:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 8:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 7:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 6:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 5:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 4:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 3:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 2:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 1:
                asm volatile(CLOCK_DELAY_NOP8::: "memory");
            case 0:
                break;
        }
    }
    switch (n) {
        case 8:
            asm volatile("nop" ::: "memory");
        case 7:
            asm volatile("nop" ::: "memory");
        case 6:
            asm volatile("nop" ::: "memory");
        case 5:
            asm volatile("nop" ::: "memory");
        case 4:
            asm volatile("nop" ::: "memory");
        case 3:
            asm volatile("nop" ::: "memory");
        case 2:
            asm volatile("nop" ::: "memory");
        case 1:
            asm volatile("nop" ::: "memory");
        case 0:
            break;
    }
}
#endif

#if defined(__AVR__)
#    include <util/delay.h>
#    define wait_ms(ms) _delay_ms(ms)
#    define wait_us(us) _delay_us(us)
#    define wait_cpuclock(x) __builtin_avr_delay_cycles(x)
#elif defined PROTOCOL_CHIBIOS
#    include <ch.h>
#    define wait_ms(ms)                     \
        do {                                \
            if (ms != 0) {                  \
                chThdSleepMilliseconds(ms); \
            } else {                        \
                chThdSleepMicroseconds(1);  \
            }                               \
        } while (0)
#    define wait_us(us)                     \
        do {                                \
            if (us != 0) {                  \
                chThdSleepMicroseconds(us); \
            } else {                        \
                chThdSleepMicroseconds(1);  \
            }                               \
        } while (0)
#elif defined PROTOCOL_ARM_ATSAM
#    include "clks.h"
#    define wait_ms(ms) CLK_delay_ms(ms)
#    define wait_us(us) CLK_delay_us(us)
#else  // Unit tests
void wait_ms(uint32_t ms);
#    define wait_us(us) wait_ms(us / 1000)
#endif

#ifdef __cplusplus
}
#endif
