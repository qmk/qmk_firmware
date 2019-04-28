#include "tap_dances.h"


//define diablo macro timer variables
diablo_timer_t diablo_timer[4];

uint8_t diablo_times[] = { 0, 0, 1, 3, 5, 10, 30 };

// has the correct number of seconds elapsed (as defined by diablo_times)
bool check_dtimer(uint8_t dtimer) { return (timer_elapsed(diablo_timer[dtimer].key_time) < (diablo_timer[dtimer].timer * 1000)) ? false : true; };

// Cycle through the times for the macro, starting at 0, for disabled.
// Max of six values, so don't exceed
void diablo_tapdance_master(qk_tap_dance_state_t *state, void *user_data) {
    int index = (int)user_data;
    if (state->count >= 7) {
        diablo_timer[index].key_time = diablo_times[0];
        reset_tap_dance(state);
    }  else {
        diablo_timer[index].key_time = diablo_times[state->count];
    }
}

// One funtion to rule them all!!
#define ACTION_TAP_DANCE_DIABLO(arg) {  \
    .fn = { NULL, (void *)diablo_tapdance_master, NULL }, \
    .user_data = (void *)arg,  \
  }

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // tap once to disable, and more to enable timed micros
    [TD_D3_1] = ACTION_TAP_DANCE_DIABLO(0),
    [TD_D3_2] = ACTION_TAP_DANCE_DIABLO(1),
    [TD_D3_3] = ACTION_TAP_DANCE_DIABLO(2),
    [TD_D3_4] = ACTION_TAP_DANCE_DIABLO(3),
};

// Sends the key press to system, but only if on the Diablo layer
void send_diablo_keystroke(uint8_t diablo_key) {
    if (IS_LAYER_ON(_DIABLO)) {
        switch (diablo_key) {
        case 0:
            tap_code(KC_1); break;
        case 1:
            tap_code(KC_2); break;
        case 2:
            tap_code(KC_3); break;
        case 3:
            tap_code(KC_4); break;
        }
    }
}

// Checks each of the 4 timers/keys to see if enough time has elapsed
// Runs the "send string" command if enough time has passed, and resets the timer.
void run_diablo_macro_check(void) {
    uint8_t dtime;
    for (dtime = 0; dtime < 4; dtime++) {
        if (check_dtimer(dtime) && diablo_timer[dtime].key_time) {
        diablo_timer[dtime].timer = timer_read();
        send_diablo_keystroke(dtime);
        }
    }
}
