// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qpwm_internal.h"

enum {
    // Work out how many PWM devices we're actually going to be instantiating
    QPWM_NUM_DEVICES = (INTEGRATED_PWM_NUM_DEVICES) + \
                       (SOFTWARE_PWM_NUM_DEVICES)
};

static pwm_device_t qpwm_devices[QPWM_NUM_DEVICES] = {NULL};

bool qpwm_internal_register_device(pwm_device_t driver) {
    for (uint8_t i = 0; i < QPWM_NUM_DEVICES; i++) {
        if(qpwm_devices[i] == NULL) {
            qpwm_devices[i] = driver;
            return true;
        }
    }

    // We should never get here -- someone has screwed up their device counts during config
    qpwm_dprintf("qpwm_internal_register_device: no more space for devices!\n");
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum PWM Core API: qpwm_internal_task

_Static_assert((QUANTUM_PWM_TASK_THROTTLE) >= 0 && (QUANTUM_PWM_TASK_THROTTLE) < 1000, "QUANTUM_PWM_TASK_THROTTLE must be between 0 and 999");

void qpwm_internal_task(void) {

    static uint32_t last_tick = 0;
    uint32_t now              = timer_read32();
    if (TIMER_DIFF_32(now, last_tick) < (QUANTUM_PWM_TASK_THROTTLE)) {
        return;
    }
    last_tick = now;
#ifdef QUANTUM_PWM_UPDATE_TASK
    // Run internal update task software-driven PWM
    qpwm_internal_update_tick();
#endif
}