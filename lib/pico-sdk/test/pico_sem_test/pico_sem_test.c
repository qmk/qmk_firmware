/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "pico/sem.h"
#include "pico/test.h"
#include "pico/stdio.h"

PICOTEST_MODULE_NAME("SEM", "semaphore test");

int main() {
    semaphore_t sem;

    stdio_init_all();
    sem_init(&sem, 1, 1);

    PICOTEST_START();

    PICOTEST_START_SECTION("sem_try_acquire");
        PICOTEST_CHECK(sem_try_acquire(&sem), "available permit not acquired");
        PICOTEST_CHECK(!sem_try_acquire(&sem), "success with no permits");
    PICOTEST_END_SECTION();

    PICOTEST_END_TEST();
}
