// Copyright 2011 Jun Wako <wakojun@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "led.h"
#include "adb.h"

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        adb_host_kbd_led(~led_state.raw);
    }
    return res;
}
