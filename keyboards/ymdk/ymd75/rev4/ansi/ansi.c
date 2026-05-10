// Copyright 2021 Mike Tsao
// Copyright 2026 sodevel<steffen.o.dev@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_kb(void)
{
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_kb(void)
{
    rgb_matrix_set_suspend_state(false);
}
void rgb_matrix_indicators_kb(void) {
    if (host_keyboard_led_state().caps_lock) {  // Capslock = RED
        //rgb_matrix_set_color(44, 200, 0, 0);
        rgb_matrix_set_color(46, 200, 0, 0);

    }
    //if (host_keyboard_led_state().scroll_lock) {  // Capslock = RED
      //  rgb_matrix_set_color(15, 200, 0, 0);

   // }
}

#endif  // #ifdef RGB_MATRIX_ENABLE
