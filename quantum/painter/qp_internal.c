// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter Core API: device registration

enum {
    // Work out how many devices we're actually going to be instantiating
    // NOTE: We intentionally do not include surfaces here, despite them conforming to the same API.
    QP_NUM_DEVICES = (ILI9163_NUM_DEVICES)   // ILI9163
                     + (ILI9341_NUM_DEVICES) // ILI9341
                     + (ILI9486_NUM_DEVICES) // ILI9486
                     + (ILI9488_NUM_DEVICES) // ILI9488
                     + (ST7789_NUM_DEVICES)  // ST7789
                     + (ST7735_NUM_DEVICES)  // ST7735
                     + (GC9A01_NUM_DEVICES)  // GC9A01
                     + (SSD1351_NUM_DEVICES) // SSD1351
                     + (SH1106_NUM_DEVICES)  // SH1106
};

static painter_device_t qp_devices[QP_NUM_DEVICES] = {NULL};

bool qp_internal_register_device(painter_device_t driver) {
    for (uint8_t i = 0; i < QP_NUM_DEVICES; i++) {
        if (qp_devices[i] == NULL) {
            qp_devices[i] = driver;
            return true;
        }
    }

    // We should never get here -- someone has screwed up their device counts during config
    qp_dprintf("qp_internal_register_device: no more space for devices!\n");
    return false;
}

#if (QUANTUM_PAINTER_DISPLAY_TIMEOUT) > 0
static void qp_internal_display_timeout_task(void) {
    // Handle power on/off state
    static bool display_on                  = true;
    bool        should_change_display_state = false;
    bool        target_display_state        = false;
    if (last_input_activity_elapsed() < (QUANTUM_PAINTER_DISPLAY_TIMEOUT)) {
        should_change_display_state = display_on == false;
        target_display_state        = true;
    } else {
        should_change_display_state = display_on == true;
        target_display_state        = false;
    }

    if (should_change_display_state) {
        for (uint8_t i = 0; i < QP_NUM_DEVICES; i++) {
            if (qp_devices[i] != NULL) {
                qp_power(qp_devices[i], target_display_state);
            }
        }

        display_on = target_display_state;
    }
}
#endif // (QUANTUM_PAINTER_DISPLAY_TIMEOUT) > 0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter Core API: qp_internal_task

_Static_assert((QUANTUM_PAINTER_TASK_THROTTLE) > 0 && (QUANTUM_PAINTER_TASK_THROTTLE) < 1000, "QUANTUM_PAINTER_TASK_THROTTLE must be between 1 and 999");

void qp_internal_task(void) {
    // Perform throttling of the internal processing of Quantum Painter
    static uint32_t last_tick = 0;
    uint32_t        now       = timer_read32();
    if (TIMER_DIFF_32(now, last_tick) < (QUANTUM_PAINTER_TASK_THROTTLE)) {
        return;
    }
    last_tick = now;

#if (QUANTUM_PAINTER_DISPLAY_TIMEOUT) > 0
    qp_internal_display_timeout_task();
#endif // (QUANTUM_PAINTER_DISPLAY_TIMEOUT) > 0

    // Handle animations
    void qp_internal_animation_tick(void);
    qp_internal_animation_tick();

#ifdef QUANTUM_PAINTER_LVGL_INTEGRATION_ENABLE
    // Run LVGL ticks
    void qp_lvgl_internal_tick(void);
    qp_lvgl_internal_tick();
#endif

    // Flush (render) dirty regions to corresponding displays
#if !defined(QUANTUM_PAINTER_DEBUG_ENABLE_FLUSH_TASK_OUTPUT)
    bool old_debug_state = debug_enable;
    debug_enable         = false;
#endif // defined(QUANTUM_PAINTER_DEBUG_ENABLE_FLUSH_TASK_OUTPUT)
    for (uint8_t i = 0; i < QP_NUM_DEVICES; i++) {
        if (qp_devices[i] != NULL) {
            qp_flush(qp_devices[i]);
        }
    }
#if !defined(QUANTUM_PAINTER_DEBUG_ENABLE_FLUSH_TASK_OUTPUT)
    debug_enable = old_debug_state;
#endif // defined(QUANTUM_PAINTER_DEBUG_ENABLE_FLUSH_TASK_OUTPUT)
}
