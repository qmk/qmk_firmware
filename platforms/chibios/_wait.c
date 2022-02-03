/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __OPTIMIZE__
#    pragma message "Compiler optimizations disabled; wait_cpuclock() won't work as designed"
#endif

#define CLOCK_DELAY_NOP8 "nop\n\t nop\n\t nop\n\t nop\n\t   nop\n\t nop\n\t nop\n\t nop\n\t"

__attribute__((always_inline)) static inline void wait_cpuclock(unsigned int n) { /* n: 1..135 */
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
