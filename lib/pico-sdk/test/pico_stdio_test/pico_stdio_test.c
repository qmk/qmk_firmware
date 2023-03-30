/**
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/test.h"

PICOTEST_MODULE_NAME("pico_stdio_test", "pico_stdio test harness");

static volatile bool deadlock_test_done;
static void deadlock_test_core1(void) {
    busy_wait_ms(250);
    for(int i=0;i<1000;i++) {
        if (deadlock_test_done) break;
        printf("Hello from core 1 - %d\n", i);
        busy_wait_ms(23);
    }
}

static volatile bool deadlock_test_irq_called;

static int64_t deadlock_test_alarm(alarm_id_t id, void *param) {
    static int foo;
    printf("Here is a printf from the IRQ %d\n", ++foo);
    deadlock_test_irq_called = true;
    return 100;
}

int main() {
    stdio_init_all();

    for(int i=0;i<10;i++) {
        printf("Hello %d\n", i);
    }
    printf("pico_stdio_test begins\n");
    PICOTEST_START();

    // Check default config has valid data in it
    PICOTEST_START_SECTION("STDIO deadlock test");
    multicore_launch_core1(deadlock_test_core1);
    alarm_id_t alarm_id = add_alarm_in_ms(500, deadlock_test_alarm, NULL, false);
    PICOTEST_CHECK(getchar_timeout_us(2000000) < 0, "someone pressed a key!");

    deadlock_test_done = true;
    cancel_alarm(alarm_id);

    sleep_ms(100);
    PICOTEST_CHECK(deadlock_test_irq_called, "deadlock_test_irq was not called");
    PICOTEST_END_SECTION();

    PICOTEST_END_TEST();
}

