#include QMK_KEYBOARD_H

#include "gui_state.h"
#include "draw_helper.h"

uint32_t global_sleep_timer     = 0;
uint32_t global_waking_up_timer = 0;
uint32_t global_booting_timer   = 0;

static bool IsBooting(void) { return (timer_elapsed32(global_booting_timer) < BOOTING_TIME_TRESHOLD); }
static bool IsWakingUp(void) {
    // after key input after idle or booting  OR after complet booting
    return (timer_elapsed32(global_waking_up_timer) < WAKING_UP_TIME_TRESHOLD);
}
static bool IsIdle(void) { return (timer_elapsed32(global_sleep_timer) > IDLE_TIME_TRESHOLD && timer_elapsed32(global_sleep_timer) < HALTING_TIME_TRESHOLD); }
static bool IsSleep(void) { return (timer_elapsed32(global_sleep_timer) >= SLEEP_TIME_TRESHOLD); }
static bool IsHalting(void) { return (timer_elapsed32(global_sleep_timer) >= HALTING_TIME_TRESHOLD && timer_elapsed32(global_sleep_timer) < SLEEP_TIME_TRESHOLD);      }
//static bool IsUp(void) { return !(IsSleep() || IsIdle() || IsBooting() || IsWakingUp()); }

gui_state_t get_gui_state(void) {
    if (IsBooting()) return _BOOTING;
    if (IsWakingUp()) return _WAKINGUP;
    if (IsIdle()) return _IDLE;
   if (IsHalting()) return _HALTING;
    if (IsSleep()) return _SLEEP;
    //if (IsUp()) return _UP;

    return _UP;
}

void update_gui_state(void) {
    gui_state_t t = get_gui_state();
    if (t == _SLEEP) {
        // booting
        global_booting_timer = timer_read32();
    }

    if (t == _BOOTING) {
        // cancel booting
        global_booting_timer = 1000000;
    }

    if (t == _IDLE || t == _HALTING || t == _BOOTING ) {
        // waking up
        global_waking_up_timer = timer_read32();
    }

    // no sleep
    global_sleep_timer = timer_read32();
}

uint8_t get_glitch_probability(void){

return interpo_pourcent(IDLE_TIME_TRESHOLD, HALTING_TIME_TRESHOLD, timer_elapsed32(global_sleep_timer) );
}
