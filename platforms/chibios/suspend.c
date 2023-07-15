// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <ch.h>
#include <hal.h>

#include "matrix.h"
#include "action.h"
#include "action_util.h"
#include "mousekey.h"
#include "programmable_button.h"
#include "host.h"
#include "suspend.h"
#include "led.h"
#include "wait.h"

/** \brief suspend power down
 *
 * FIXME: needs doc
 */
void suspend_power_down(void) {
    suspend_power_down_quantum();
    // on AVR, this enables the watchdog for 15ms (max), and goes to
    // SLEEP_MODE_PWR_DOWN

    wait_ms(17);
}

/** \brief suspend wakeup condition
 *
 * run immediately after wakeup
 * FIXME: needs doc
 */
void suspend_wakeup_init(void) {
    // clear keyboard state
    clear_keyboard();

    suspend_wakeup_init_quantum();
}
