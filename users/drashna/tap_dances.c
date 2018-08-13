#include "drashna.h"
#include "tap_dances.h"


//define diablo macro timer variables
uint16_t diablo_timer[4];
uint8_t diablo_times[] = { 0, 1, 3, 5, 10, 30 };
uint8_t diablo_key_time[4];

// has the correct number of seconds elapsed (as defined by diablo_times)
bool check_dtimer(uint8_t dtimer) { return (timer_elapsed(diablo_timer[dtimer]) < (diablo_key_time[dtimer] * 1000)) ? false : true; };

// Cycle through the times for the macro, starting at 0, for disabled.
// Max of six values, so don't exceed
void diablo_tapdance_master(qk_tap_dance_state_t *state, void *user_data, uint8_t diablo_key) {
  if (state->count >= 7) {
    diablo_key_time[diablo_key] = diablo_times[0];
    reset_tap_dance(state);
  }  else {
    diablo_key_time[diablo_key] = diablo_times[state->count - 1];
  }
}

// Would rather have one function for all of this, but no idea how to do that...
void diablo_tapdance1(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 0); }
void diablo_tapdance2(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 1); }
void diablo_tapdance3(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 2); }
void diablo_tapdance4(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 3); }

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // tap once to disable, and more to enable timed micros
  [TD_D3_1] = ACTION_TAP_DANCE_FN(diablo_tapdance1),
  [TD_D3_2] = ACTION_TAP_DANCE_FN(diablo_tapdance2),
  [TD_D3_3] = ACTION_TAP_DANCE_FN(diablo_tapdance3),
  [TD_D3_4] = ACTION_TAP_DANCE_FN(diablo_tapdance4),
};

// Sends the key press to system, but only if on the Diablo layer
void send_diablo_keystroke(uint8_t diablo_key) {
  if (biton32(layer_state) == _DIABLO) {
    switch (diablo_key) {
      case 0:
        tap(KC_1); break;
      case 1:
        tap(KC_2); break;
      case 2:
        tap(KC_3); break;
      case 3:
        tap(KC_4); break;
    }
  }
}

// Checks each of the 4 timers/keys to see if enough time has elapsed
// Runs the "send string" command if enough time has passed, and resets the timer.
void run_diablo_macro_check(void) {
  uint8_t dtime;
  for (dtime = 0; dtime < 4; dtime++) {
    if (check_dtimer(dtime) && diablo_key_time[dtime]) {
      diablo_timer[dtime] = timer_read();
      send_diablo_keystroke(dtime);
    }
  }
}
