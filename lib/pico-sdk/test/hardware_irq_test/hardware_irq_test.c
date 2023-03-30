/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdarg.h>
#include "pico/stdlib.h"
#include "pico/test.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/dma.h"
#include "hardware/structs/scb.h"

PICOTEST_MODULE_NAME("IRQ", "IRQ Handler test");

extern void __unhandled_user_irq(void);

static bool remove_handler1_in_dma;
static bool remove_handler2_in_dma;
static bool remove_handler3_in_dma;
static dma_channel_config config;

#define MAX_FIRE_COUNT 4
static int fire_count;
static int fired[MAX_FIRE_COUNT];

static uint32_t dma_to = 0;
static uint32_t dma_from = 0xaaaa5555;

int record_fire(int which) {
    PICOTEST_CHECK(fire_count < MAX_FIRE_COUNT, "too many firings");
    fired[fire_count++] = which;
    return 0;
}

void __isr handler1(void) {
    record_fire(1);
    dma_channel_acknowledge_irq0(0);
    if (remove_handler1_in_dma) {
        irq_remove_handler(DMA_IRQ_0, handler1);
        remove_handler1_in_dma = false;
    }
}

void __isr handler2(void) {
    record_fire(2);
    dma_channel_acknowledge_irq0(0);
    if (remove_handler2_in_dma) {
        irq_remove_handler(DMA_IRQ_0, handler2);
        remove_handler2_in_dma = false;
    }
}

void __isr handler3(void) {
    record_fire(3);
    dma_channel_acknowledge_irq0(0);
    if (remove_handler3_in_dma) {
        irq_remove_handler(DMA_IRQ_0, handler3);
        remove_handler3_in_dma = false;
    }
}

static inline irq_handler_t *get_vtable(void) {
    return (irq_handler_t *) scb_hw->vtor;
}

int dma_check(int expected, ...) {
    if (expected == 0) {
        // doing the DMA if there are no IRQ handlers will cause a hard fault, so we just check we are pointing at the handler which does this.
        PICOTEST_CHECK_AND_ABORT(get_vtable()[16 + DMA_IRQ_0] == __unhandled_user_irq, "Expected there to be no IRQ handlers");
        return 0;
    }
    fire_count = 0;
    dma_channel_configure(0, &config, &dma_to, &dma_from, 1, true);
    sleep_ms(100);
    va_list args;
    va_start(args, expected);
    bool ok = expected == fire_count;
    for(int i=0;ok && i<expected;i++) {
        if (fired[i] != va_arg(args, int)) {
            ok = false;
            break;
        }
    }
    va_end(args);
    if (!ok) {
        PICOTEST_CHECK(ok, "DMA handlers were not called in the order expected");
        printf("  EXPECTED handlers: ");
        va_start(args, expected);
        for(int i=0;i<expected;i++) {
            if (i) printf(", ");
            printf("%d", va_arg(args, int));
        }
        printf("\n");
        va_end(args);
        printf("  CALLED handlers:   ");
        for(int i=0;i<fire_count;i++) {
            if (i) printf(", ");
            printf("%d", fired[i]);
        }
        printf("\n");
        return -1;
    }
    return 0;
}

int main() {
    stdio_init_all();

    PICOTEST_START();
    config = dma_channel_get_default_config(0);
    dma_channel_set_irq0_enabled(0, true);
    irq_set_enabled(DMA_IRQ_0, true);

    // part I, just add/remove two handlers
    PICOTEST_START_SECTION("I: Add handler1 default priority");
        irq_add_shared_handler(DMA_IRQ_0, handler1, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        dma_check(1, 1);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("I: Add handler2 default priority");
        irq_add_shared_handler(DMA_IRQ_0, handler2, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        dma_check(2, 2, 1);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("I: Remove handler1");
        irq_remove_handler(DMA_IRQ_0, handler1);
        dma_check(1, 2);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("I: Remove handler2");
        irq_remove_handler(DMA_IRQ_0, handler2);
        dma_check(0);
    PICOTEST_END_SECTION();

    // part II, add/remove three handlers including one in the middle

    PICOTEST_START_SECTION("II: Add handler3 default priority");
        irq_add_shared_handler(DMA_IRQ_0, handler3, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        dma_check(1, 3);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("II: Add handler2 default priority");
        irq_add_shared_handler(DMA_IRQ_0, handler2, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        dma_check(2, 2, 3);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("II: Add handler1 default priority");
        irq_add_shared_handler(DMA_IRQ_0, handler1, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        dma_check(3, 1, 2, 3);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("II: Remove handler2");
        irq_remove_handler(DMA_IRQ_0, handler2);
        dma_check(2, 1, 3);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("II: Remove handler3");
        irq_remove_handler(DMA_IRQ_0, handler3);
        dma_check(1, 1);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("II: Remove handler1");
        irq_remove_handler(DMA_IRQ_0, handler1);
        dma_check(0);
    PICOTEST_END_SECTION();

    // part III, the same as part II, but removing the handlers during the IRQ

    PICOTEST_START_SECTION("III: Add handler3 default priority");
        irq_add_shared_handler(DMA_IRQ_0, handler3, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        dma_check(1, 3);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("III: Add handler2 default priority");
        irq_add_shared_handler(DMA_IRQ_0, handler2, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        dma_check(2, 2, 3);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("III: Add handler1 default priority");
        irq_add_shared_handler(DMA_IRQ_0, handler1, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        dma_check(3, 1, 2, 3);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("III: Remove handler2");
        remove_handler2_in_dma = true;
        // note that this is the defined behavior, that any handlers after the removed handler are not called. the
        // reasoning is that the same IRQ will immediately be re-entered, as we have missed clearing an interrupt (in whichever
        // handlers were not called), and we will call any remaining handlers then. Because each IRQ handler is clearing the same
        // interrupt handler in our case, this does not happen.
        dma_check(2, 1, 2);
        // but we call again to check
        dma_check(2, 1, 3);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("III: Remove handler3");
        remove_handler3_in_dma = true;
        // note that this is the defined behavior, that any handlers after the removed handler are not called. the
        // reasoning is that the same IRQ will immediately be re-entered, as we have missed clearing an interrupt (in whichever
        // handlers were not called), and we will call any remaining handlers then. Because each IRQ handler is clearing the same
        // interrupt handler in our case, this does not happen.
        dma_check(2, 1, 3);
        // but we call again to check
        dma_check(1, 1);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("III: Remove handler3");
        remove_handler1_in_dma = true;
        // note that this is the defined behavior, that any handlers after the removed handler are not called. the
        // reasoning is that the same IRQ will immediately be re-entered, as we have missed clearing an interrupt (in whichever
        // handlers were not called), and we will call any remaining handlers then. Because each IRQ handler is clearing the same
        // interrupt handler in our case, this does not happen.
        dma_check(1, 1);
        // but we call again to check
        dma_check(0);
    PICOTEST_END_SECTION();

    // part IV, checking priorities
    PICOTEST_START_SECTION("IV: Add handler1 high priority");
        irq_add_shared_handler(DMA_IRQ_0, handler1, PICO_SHARED_IRQ_HANDLER_HIGHEST_ORDER_PRIORITY);
        dma_check(1, 1);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("IV: Add handler2 normal priority");
        irq_add_shared_handler(DMA_IRQ_0, handler2, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        dma_check(2, 1, 2);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("IV: Add handler3 lowest priority");
        irq_add_shared_handler(DMA_IRQ_0, handler3, PICO_SHARED_IRQ_HANDLER_LOWEST_ORDER_PRIORITY);
        dma_check(3, 1, 2, 3);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("IV: Remove handler3");
        irq_remove_handler(DMA_IRQ_0, handler3);
        dma_check(2, 1, 2);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("IV: Add handler3 normal priority");
        irq_add_shared_handler(DMA_IRQ_0, handler3, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY);
        dma_check(3, 1, 3, 2);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("IV: Remove handler2");
        irq_remove_handler(DMA_IRQ_0, handler2);
        dma_check(2, 1, 3);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("IV: Add handler2 normal priority - 2");
        irq_add_shared_handler(DMA_IRQ_0, handler2, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY - 2);
        dma_check(3, 1, 3, 2);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("IV: Remove handler1");
        irq_remove_handler(DMA_IRQ_0, handler1);
        dma_check(2, 3, 2);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("IV: Add handler1 normal priority - 1");
        irq_add_shared_handler(DMA_IRQ_0, handler1, PICO_SHARED_IRQ_HANDLER_DEFAULT_ORDER_PRIORITY - 1);
        dma_check(3, 3, 1, 2);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("IV: Remove handler2 again");
        irq_remove_handler(DMA_IRQ_0, handler2);
        dma_check(2, 3, 1);

    PICOTEST_END_SECTION();
    PICOTEST_START_SECTION("IV: Remove handler3 again");
        irq_remove_handler(DMA_IRQ_0, handler3);
        dma_check(1, 1);
    PICOTEST_END_SECTION();

    PICOTEST_START_SECTION("IV: Remove handler1 again");
        irq_remove_handler(DMA_IRQ_0, handler1);
        dma_check(0);
    PICOTEST_END_SECTION();
    PICOTEST_END_TEST();
}

