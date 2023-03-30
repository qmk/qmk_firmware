/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "hardware/watchdog.h"
#include "hardware/structs/watchdog.h"
#include "hardware/structs/psm.h"

/// \tag::watchdog_start_tick[]
void watchdog_start_tick(uint cycles) {
    // Important: This function also provides a tick reference to the timer
    watchdog_hw->tick = cycles | WATCHDOG_TICK_ENABLE_BITS;
}
/// \end::watchdog_start_tick[]

// Value to load when updating the watchdog

// tag::watchdog_update[]
static uint32_t load_value;

void watchdog_update(void) {
    watchdog_hw->load = load_value;
}
// end::watchdog_update[]

uint32_t watchdog_get_count(void) {
    return (watchdog_hw->ctrl & WATCHDOG_CTRL_TIME_BITS) / 2 ;
}

// tag::watchdog_enable[]
// Helper function used by both watchdog_enable and watchdog_reboot
void _watchdog_enable(uint32_t delay_ms, bool pause_on_debug) {
    hw_clear_bits(&watchdog_hw->ctrl, WATCHDOG_CTRL_ENABLE_BITS);

    // Reset everything apart from ROSC and XOSC
    hw_set_bits(&psm_hw->wdsel, PSM_WDSEL_BITS & ~(PSM_WDSEL_ROSC_BITS | PSM_WDSEL_XOSC_BITS));

    uint32_t dbg_bits = WATCHDOG_CTRL_PAUSE_DBG0_BITS |
                        WATCHDOG_CTRL_PAUSE_DBG1_BITS |
                        WATCHDOG_CTRL_PAUSE_JTAG_BITS;

    if (pause_on_debug) {
        hw_set_bits(&watchdog_hw->ctrl, dbg_bits);
    } else {
        hw_clear_bits(&watchdog_hw->ctrl, dbg_bits);
    }

    if (!delay_ms) {
        hw_set_bits(&watchdog_hw->ctrl, WATCHDOG_CTRL_TRIGGER_BITS);
    } else {
        // Note, we have x2 here as the watchdog HW currently decrements twice per tick
        load_value = delay_ms * 1000 * 2;

        if (load_value > 0xffffffu)
            load_value = 0xffffffu;

        watchdog_update();

        hw_set_bits(&watchdog_hw->ctrl, WATCHDOG_CTRL_ENABLE_BITS);
    }
}
// end::watchdog_enable[]

#define WATCHDOG_NON_REBOOT_MAGIC 0x6ab73121

void watchdog_enable(uint32_t delay_ms, bool pause_on_debug) {
    // update scratch[4] to distinguish from magic used for reboot to specific address, or 0 used to reboot
    // into regular flash path
    watchdog_hw->scratch[4] = WATCHDOG_NON_REBOOT_MAGIC;
    _watchdog_enable(delay_ms, pause_on_debug);
}

void watchdog_reboot(uint32_t pc, uint32_t sp, uint32_t delay_ms) {
    check_hw_layout(watchdog_hw_t, scratch[7], WATCHDOG_SCRATCH7_OFFSET);

    // Clear enable before setting up scratch registers
    hw_clear_bits(&watchdog_hw->ctrl, WATCHDOG_CTRL_ENABLE_BITS);

    if (pc) {
        pc |= 1u; // thumb mode
        watchdog_hw->scratch[4] = 0xb007c0d3;
        watchdog_hw->scratch[5] = pc ^ -0xb007c0d3;
        watchdog_hw->scratch[6] = sp;
        watchdog_hw->scratch[7] = pc;
//        printf("rebooting %08x/%08x in %dms...\n", (uint) pc, (uint) sp, (uint) delay_ms);
    } else {
        watchdog_hw->scratch[4] = 0;
//        printf("rebooting (regular)) in %dms...\n", (uint) delay_ms);
    }

    // Don't pause watchdog for debug
    _watchdog_enable(delay_ms, 0);
}

bool watchdog_caused_reboot(void) {
    // If any reason bits are set this is true
    return watchdog_hw->reason;
}

bool watchdog_enable_caused_reboot(void) {
    return watchdog_hw->reason && watchdog_hw->scratch[4] == WATCHDOG_NON_REBOOT_MAGIC;
}