// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "c1.h"
#include "ch.h"
#include "hal.h"

static virtual_timer_t vt;

// Main process for core1
static THD_WORKING_AREA(wa_c1_main_task_wrapper, 2048);
static THD_FUNCTION(c1_main_task_wrapper, arg) {
    while (1) {
        c1_main_task();
        chThdSleepMicroseconds(125);
    }
}

// Entry point of core1
void c1_main(void) {
    chSysWaitSystemState(ch_sys_running);
    chInstanceObjectInit(&ch1, &ch_core1_cfg);
    chSysUnlock();

    // USB host stack uses PIO and DMA
    hal_lld_peripheral_unreset(RESETS_ALLREG_PIO0);
    hal_lld_peripheral_unreset(RESETS_ALLREG_PIO1);
    hal_lld_peripheral_unreset(RESETS_ALLREG_DMA);

    // Initialize USB host stack
    c1_usbh();

    // Start main task
    chThdCreateStatic(wa_c1_main_task_wrapper, sizeof(wa_c1_main_task_wrapper), NORMALPRIO + 1, c1_main_task_wrapper, NULL);
}

// 1ms repeat timer for USB frame
void        sof_timer(void *);
static void timer_cb(virtual_timer_t *_vt, void *_) {
    // Start USB frame
    sof_timer(NULL);
}

// Start 1ms timer
void c1_start_timer(void) {
    chVTObjectInit(&vt);
    chVTSetContinuous(&vt, TIME_MS2I(1), timer_cb, NULL);
}