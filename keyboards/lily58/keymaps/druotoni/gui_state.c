// Copyright 2021 Nicolas Druoton (druotoni)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "gui_state.h"
#include "draw_helper.h"

// timer for the gui state
uint32_t global_sleep_timer     = 0;
uint32_t global_waking_up_timer = 0;
uint32_t global_booting_timer   = 0;

// timers test for states
#ifdef WITH_BOOT
static bool IsBooting(void) { return (timer_elapsed32(global_booting_timer) < BOOTING_TIME_TRESHOLD); }
#else
static bool IsBooting(void) { return false; }
#endif

// state test
static bool IsWakingUp(void) { return (timer_elapsed32(global_waking_up_timer) < WAKING_UP_TIME_TRESHOLD); }
static bool IsIdle(void) { return (timer_elapsed32(global_sleep_timer) > IDLE_TIME_TRESHOLD && timer_elapsed32(global_sleep_timer) < HALTING_TIME_TRESHOLD); }
static bool IsSleep(void) { return (timer_elapsed32(global_sleep_timer) >= SLEEP_TIME_TRESHOLD); }
static bool IsHalting(void) { return (timer_elapsed32(global_sleep_timer) >= HALTING_TIME_TRESHOLD && timer_elapsed32(global_sleep_timer) < SLEEP_TIME_TRESHOLD); }

gui_state_t get_gui_state(void) {
    // get gui states by testing timers
    if (IsBooting()) return _BOOTING;
    if (IsWakingUp()) return _WAKINGUP;
    if (IsIdle()) return _IDLE;
    if (IsHalting()) return _HALTING;
    if (IsSleep()) return _SLEEP;

    return _UP;
}

void update_gui_state(void) {
    // what to do when a key is pressed
    gui_state_t t = get_gui_state();

#ifdef WITH_BOOT
    if (t == _SLEEP) {
        // booting
        global_booting_timer = timer_read32();
    }

    if (t == _BOOTING) {
        // cancel booting
        global_booting_timer = 1000000;
    }
#else
    if (t == _SLEEP) {
        // waking up
        global_waking_up_timer = timer_read32();
    }
#endif

    if (t == _IDLE || t == _HALTING || t == _BOOTING) {
        // waking up
        global_waking_up_timer = timer_read32();
    }

    // no sleep
    global_sleep_timer = timer_read32();
}

uint8_t get_glitch_probability(void) {
    // more gliches could occur when halting time is near
    return interpo_pourcent(IDLE_TIME_TRESHOLD, HALTING_TIME_TRESHOLD, timer_elapsed32(global_sleep_timer));
}
