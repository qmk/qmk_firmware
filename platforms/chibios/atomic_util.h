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
#pragma once

#include <ch.h>

static __inline__ uint8_t __interrupt_disable__(void) {
    chSysLock();

    return 1;
}

static __inline__ void __interrupt_enable__(const uint8_t *__s) {
    chSysUnlock();

    __asm__ volatile("" ::: "memory");
    (void)__s;
}

static __inline__ syssts_t __interrupt_lock__(void) {
    return chSysGetStatusAndLockX();
}

static __inline__ void __interrupt_unlock__(const syssts_t *__s) {
    chSysRestoreStatusX(*__s);

    __asm__ volatile("" ::: "memory");
}

#define ATOMIC_BLOCK(type) for (type, __ToDo = 1; __ToDo; __ToDo = 0)
#define ATOMIC_FORCEON uint8_t status_save __attribute__((__cleanup__(__interrupt_enable__))) = __interrupt_disable__()
#define ATOMIC_RESTORESTATE syssts_t status_save __attribute__((__cleanup__(__interrupt_unlock__))) = __interrupt_lock__()

#define ATOMIC_BLOCK_RESTORESTATE ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
#define ATOMIC_BLOCK_FORCEON ATOMIC_BLOCK(ATOMIC_FORCEON)
