/* Copyright 2017 REPLACE_WITH_YOUR_NAME
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "woodpad.h"
#include "drashna.h"

 // Each layer gets a name for readability, which is then used in the keymap matrix below.
 // The underscores don't mean anything - you can have a layer called STUFF or any other name.
 // Layer names don't all need to be of the same length, obviously, and you can also skip them
 // entirely and just use numbers.

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


//define layer change stuff for underglow indicator
bool skip_leds = false;


#ifdef TAP_DANCE_ENABLE
//define diablo macro timer variables
static uint16_t diablo_timer[4];
static uint8_t diablo_times[] = { 0, 1, 3, 5, 10, 30 };
static uint8_t diablo_key_time[4];


bool check_dtimer(uint8_t dtimer) {
  // has the correct number of seconds elapsed (as defined by diablo_times)
  return (timer_elapsed(diablo_timer[dtimer]) < (diablo_key_time[dtimer] * 1000)) ? false : true;
};
#endif



#ifdef TAP_DANCE_ENABLE
enum {
  TD_DIABLO_1 = 0,
  TD_DIABLO_2,
  TD_DIABLO_3,
  TD_DIABLO_4
};


// Cycle through the times for the macro, starting at 0, for disabled.
// Max of six values, so don't exceed
void diablo_tapdance_master(qk_tap_dance_state_t *state, void *user_data, uint8_t diablo_key) {
  if (state->count >= 7) {
    diablo_key_time[diablo_key] = diablo_times[0];
    reset_tap_dance(state);
  }
  else {
    diablo_key_time[diablo_key] = diablo_times[state->count - 1];
  }
}


// Would rather have one function for all of this, but no idea how to do that...
void diablo_tapdance1(qk_tap_dance_state_t *state, void *user_data) {
  diablo_tapdance_master(state, user_data, 0);
}

void diablo_tapdance2(qk_tap_dance_state_t *state, void *user_data) {
  diablo_tapdance_master(state, user_data, 1);
}

void diablo_tapdance3(qk_tap_dance_state_t *state, void *user_data) {
  diablo_tapdance_master(state, user_data, 2);
}

void diablo_tapdance4(qk_tap_dance_state_t *state, void *user_data) {
  diablo_tapdance_master(state, user_data, 3);
}



//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  // tap once to disable, and more to enable timed micros
  [TD_DIABLO_1] = ACTION_TAP_DANCE_FN(diablo_tapdance1),
  [TD_DIABLO_2] = ACTION_TAP_DANCE_FN(diablo_tapdance2),
  [TD_DIABLO_3] = ACTION_TAP_DANCE_FN(diablo_tapdance3),
  [TD_DIABLO_4] = ACTION_TAP_DANCE_FN(diablo_tapdance4),

};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_NUMLOCK] = KEYMAP( /* Base */
    TG(_NAV), TG(_DIABLO), TG(_MACROS), KC_PSLS,\
    KC_P7,  KC_P8, KC_P9, KC_PAST,   \
    KC_P4,  KC_P5, KC_P6, KC_PMNS,   \
    KC_P1,  KC_P2, KC_P3, KC_PPLS,   \
    LT(_MEDIA,KC_P0), KC_PDOT, KC_COLN, KC_PENT   \
),
[_NAV] = KEYMAP( /* Base */
    _______, _______, _______, _______,\
    KC_HOME,  KC_UP, KC_PGUP, _______,   \
    KC_LEFT,  XXXXXXX, KC_RIGHT, _______,   \
    KC_END,  KC_DOWN, KC_PGDN, _______,   \
    KC_INS, KC_DEL, _______, _______   \
),
#ifdef TAP_DANCE_ENABLE
[_DIABLO] = KEYMAP( /* Base */
    KC_ESC, _______, _______, _______,\
    KC_S, KC_F, KC_I, KC_M,   \
    KC_1, KC_2, KC_3, KC_4, \
    TD(TD_DIABLO_1), TD(TD_DIABLO_2), TD(TD_DIABLO_3), TD(TD_DIABLO_4), \
    _______, KC_DIABLO_CLEAR, KC_Q, SFT_T(KC_SPACE)  \
),
#else
[_DIABLO] = KEYMAP( /* Base */
    KC_ESC, _______, _______, _______,\
    KC_S, KC_F, KC_I, KC_M,   \
    KC_1, KC_2, KC_3, KC_4, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, KC_DIABLO_CLEAR, KC_Q, SFT_T(KC_SPACE)  \
),

#endif

[_MACROS] = KEYMAP( /* Base */
    KC_OVERWATCH, _______, _______, XXXXXXX,\
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   \
    XXXXXXX, XXXXXXX, XXXXXXX, KC_JUSTGAME,   \
    KC_SYMM,  KC_DOOMFIST, KC_TORB, KC_GOODGAME,   \
    KC_SALT,  KC_MORESALT, KC_SALTHARD, KC_GLHF   \
),
[_MEDIA] = KEYMAP( /* Base */
    KC_RESET, KC_MUTE, KC_VOLD, KC_VOLU,\
    KC_MAKE, _______, RGB_HUI, RGB_HUD,   \
    KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT,   \
    RGB_TOG, RGB_MOD, RGB_SAI, RGB_VAI,   \
    _______, _______, RGB_SAD, RGB_VAD   \
),

};


void numlock_led_on(void) {
  PORTF |= (1 << 7);
}

void numlock_led_off(void) {
  PORTF &= ~(1 << 7);
}


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
#ifdef TAP_DANCE_ENABLE
  case KC_DIABLO_CLEAR:  // reset all Diable timers, disabling them
    if (record->event.pressed) {
      uint8_t dtime;

      for (dtime = 0; dtime < 4; dtime++) {
        diablo_key_time[dtime] = diablo_times[0];
      }
    }
    return false;
    break;
#endif
  }
  return true;
}

#ifdef TAP_DANCE_ENABLE

// Sends the key press to system, but only if on the Diablo layer
void send_diablo_keystroke(uint8_t diablo_key) {
  if (biton32(layer_state) == _DIABLO) {
    switch (diablo_key) {
    case 0:
      SEND_STRING("1");
      break;
    case 1:
      SEND_STRING("2");
      break;
    case 2:
      SEND_STRING("3");
      break;
    case 3:
      SEND_STRING("4");
      break;
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
#endif
void matrix_init_keymap(void) {
  // set Numlock LED to output and low
  DDRF |= (1 << 7);
  PORTF &= ~(1 << 7);


  if (!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))) {
    register_code(KC_NUMLOCK);
    unregister_code(KC_NUMLOCK);
  }
}

void matrix_scan_keymap(void) {
  numlock_led_off();
  if (is_overwatch && biton32(layer_state) == _MACROS) {
    numlock_led_on();
  }

  // Run Diablo 3 macro checking code.
#ifdef TAP_DANCE_ENABLE
  run_diablo_macro_check();
#endif
}

