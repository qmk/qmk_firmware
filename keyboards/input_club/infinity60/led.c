/*
Copyright 2015 Jun Wako <wakojun@gmail.com>
Copyright 2017 jpetermans <tibcmhhm@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <hal.h>

#include "led.h"

#include "led_controller.h"

/* WARNING! This function needs to be callable from
 * both regular threads and ISRs, unlocked (during resume-from-sleep).
 * In particular, I2C functions (interrupt-driven) should NOT be called from here.
 */
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        msg_t msg;

        if (led_state.num_lock) {
            chSysUnconditionalLock();
            msg=(1 << 8) | TOGGLE_NUM_LOCK;
            chMBPostI(&led_mailbox, msg);
            chSysUnconditionalUnlock();
        } else {
            chSysUnconditionalLock();
            msg=(0 << 8) | TOGGLE_NUM_LOCK;
            chMBPostI(&led_mailbox, msg);
            chSysUnconditionalUnlock();
        }
        if (led_state.caps_lock) {
            chSysUnconditionalLock();
            msg=(1 << 8) | TOGGLE_CAPS_LOCK;
            chMBPostI(&led_mailbox, msg);
            chSysUnconditionalUnlock();
        } else {
            chSysUnconditionalLock();
            msg=(0 << 8) | TOGGLE_CAPS_LOCK;
            chMBPostI(&led_mailbox, msg);
            chSysUnconditionalUnlock();
        }
    }
    return false;
}
