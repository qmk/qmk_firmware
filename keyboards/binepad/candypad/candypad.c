// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "candypad.h"

#ifdef OLED_ENABLE

// OLED functions
uint8_t  oled_mode              = OLED_SPLASH;
bool     oled_repaint_requested = false;
uint32_t oled_splash_timer      = 0;

void housekeeping_task_kb(void) {
    if (0 != oled_splash_timer) {
        if (timer_elapsed(oled_splash_timer) > OLED_SPLASH_TIMEOUT) {
            switch (oled_mode) {
                case OLED_SPLASH:
                default:
                    oled_mode         = OLED_DEFAULT;
                    oled_splash_timer = 0; // disable
                    break;
            }
            oled_repaint_requested = true;
        }
    }
}

void suspend_wakeup_init_kb(void) {
    oled_on();
    suspend_wakeup_init_user();
}

#endif // OLED_ENABLE
