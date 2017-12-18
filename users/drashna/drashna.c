/*
Copyright 2017 Christopher Courtney <drashna@live.com> @drashna

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

#include "drashna.h"
#include "version.h"

#if (__has_include("secrets.h"))
#include "secrets.h"
#else
PROGMEM const char secret[][64] = {
  "test1",
  "test2",
  "test3",
  "test4",
  "test5"
};
#endif

#ifdef TAP_DANCE_ENABLE
//define diablo macro timer variables
static uint16_t diablo_timer[4];
static uint8_t diablo_times[] = { 0, 1, 3, 5, 10, 30 };
static uint8_t diablo_key_time[4];


bool check_dtimer(uint8_t dtimer) {
  // has the correct number of seconds elapsed (as defined by diablo_times)
  return (timer_elapsed(diablo_timer[dtimer]) < (diablo_key_time[dtimer] * 1000)) ? false : true;
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
  [TD_D3_1] = ACTION_TAP_DANCE_FN(diablo_tapdance1),
  [TD_D3_2] = ACTION_TAP_DANCE_FN(diablo_tapdance2),
  [TD_D3_3] = ACTION_TAP_DANCE_FN(diablo_tapdance3),
  [TD_D3_4] = ACTION_TAP_DANCE_FN(diablo_tapdance4),

};
#endif

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]       = SONG(QWERTY_SOUND);
float tone_dvorak[][2]       = SONG(DVORAK_SOUND);
float tone_colemak[][2]      = SONG(COLEMAK_SOUND);
float tone_workman[][2]      = SONG(PLOVER_SOUND);
float tone_hackstartup[][2]  = SONG(ONE_UP_SOUND);
#endif


// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

bool is_overwatch = false;
#ifdef RGBLIGHT_ENABLE
bool rgb_layer_change = true;
#endif




// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();

  rgblight_enable();

  if (true) {
    if (default_layer & (1UL << _COLEMAK)) {
      rgblight_set_magenta;
    }
    else if (default_layer & (1UL << _DVORAK)) {
      rgblight_set_green;
    }
    else if (default_layer & (1UL << _WORKMAN)) {
      rgblight_set_purple;
    }
    else {
      rgblight_set_teal;
    }
  }
  else
  {
    rgblight_set_red;
    rgblight_mode(5);
  }
#endif
#ifdef AUDIO_ENABLE
//  _delay_ms(21); // gets rid of tick
//  stop_all_notes();
//  PLAY_SONG(tone_hackstartup);
#endif
  matrix_init_keymap();
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
// No global matrix scan code, so just run keymap's matix
// scan function
void matrix_scan_user(void) {
#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
  run_diablo_macro_check();
#endif
  matrix_scan_keymap();
}

void led_set_user(uint8_t usb_led) {
  led_set_keymap(usb_led);
}



void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's recod handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
#ifdef CONSOLE_ENABLE
  xprintf("KL: row: %u, column: %u, pressed: %u\n", record->event.key.col, record->event.key.row, record->event.pressed);
#endif

  switch (keycode) {
  case KC_QWERTY:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_qwerty);
#endif
      persistent_default_layer_set(1UL << _QWERTY);
    }
    return false;
    break;
  case KC_COLEMAK:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_colemak);
#endif
      persistent_default_layer_set(1UL << _COLEMAK);
    }
    return false;
    break;
  case KC_DVORAK:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_dvorak);
#endif
      persistent_default_layer_set(1UL << _DVORAK);
    }
    return false;
    break;
  case KC_WORKMAN:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_workman);
#endif
      persistent_default_layer_set(1UL << _WORKMAN);
    }
    return false;
    break;
  case LOWER:
    if (record->event.pressed) {
      layer_on(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    else {
      layer_off(_LOWER);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;
  case RAISE:
    if (record->event.pressed) {
      layer_on(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    else {
      layer_off(_RAISE);
      update_tri_layer(_LOWER, _RAISE, _ADJUST);
    }
    return false;
    break;
  case ADJUST:
    if (record->event.pressed) {
      layer_on(_ADJUST);
    }
    else {
      layer_off(_ADJUST);
    }
    return false;
    break;
#if !(defined(KEYBOARD_orthodox_rev1) || defined(KEYBOARD_ergodox_ez))
  case KC_OVERWATCH:
    if (record->event.pressed) {
      is_overwatch = !is_overwatch;
    }
#ifdef RGBLIGHT_ENABLE
    is_overwatch ? rgblight_mode(17) : rgblight_mode(18);
#endif
    return false;
    break;
  case KC_SALT:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("Salt, salt, salt...");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_MORESALT:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("Please sir, can I have some more salt?!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_SALTHARD:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("Your salt only makes me harder, and even more aggressive!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_GOODGAME:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("Good game, everyone!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_GLHF:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("Good luck, have fun!!!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_SYMM:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("Left click to win!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_JUSTGAME:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("It may be a game, but if you don't want to actually try, please go play AI, so that people that actually want to take the game seriously and \"get good\" have a place to do so without trolls like you throwing games.");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_TORB:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("That was positively riveting!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_AIM:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("That aim is absolutely amazing. It's almost like you're a machine!" SS_TAP(X_ENTER));
      _delay_ms(3000);
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      SEND_STRING("Wait! That aim is TOO good!  You're clearly using an aim hack! CHEATER!" SS_TAP(X_ENTER));
    }
    return false;
    break;
  case KC_C9:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("OMG!!!  C9!!!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
  case KC_GGEZ:
    if (!record->event.pressed) {
      register_code(is_overwatch ? KC_BSPC : KC_ENTER);
      unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
      _delay_ms(50);
      SEND_STRING("That was a fantastic game, though it was a bit easy. Try harder next time!");
      register_code(KC_ENTER);
      unregister_code(KC_ENTER);
    }
    return false;
    break;
#endif
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
  case KC_MAKE:
    if (!record->event.pressed) {
      SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP
#if  (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
       ":dfu"
#elif defined(BOOTLOADER_HALFKAY)
      ":teensy"
//#elif defined(BOOTLOADER_CATERINA)
//       ":avrdude"
#endif
#ifdef RGBLIGHT_ENABLE
        " RGBLIGHT_ENABLE=yes"
#else
        " RGBLIGHT_ENABLE=no"
#endif
#ifdef AUDIO_ENABLE
        " AUDIO_ENABLE=yes"
#else
        " AUDIO_ENABLE=no"
#endif
#ifdef FAUXCLICKY_ENABLE
        " FAUXCLICKY_ENABLE=yes"
#else
        " FAUXCLICKY_ENABLE=no" 
#endif
        SS_TAP(X_ENTER));
    }
    return false;
    break;
  case KC_RESET:
    if (!record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
      rgblight_enable();
      rgblight_mode(1);
      rgblight_setrgb(0xff, 0x00, 0x00);
#endif
      reset_keyboard();
    }
    return false;
    break;
  case EPRM:
    if (record->event.pressed) {
      eeconfig_init();
    }
    return false;
    break;
  case VRSN:
    if (record->event.pressed) {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
    }
    return false;
    break;
  case KC_SECRET_1 ... KC_SECRET_5:
    if (!record->event.pressed) {
      send_string_P(secret[keycode - KC_SECRET_1]);
    }
    return false;
    break;
  case KC_RGB_T:  // Because I want the option to go back to normal RGB mode rather than always layer indication
#ifdef RGBLIGHT_ENABLE
    if (record->event.pressed) {
      rgb_layer_change = !rgb_layer_change;
    }
#endif
    return false;
    break;
#ifdef RGBLIGHT_ENABLE
  case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // quantum_keycodes.h L400 for definitions
    if (record->event.pressed) { //This disrables layer indication, as it's assumed that if you're changing this ... you want that disabled
      rgb_layer_change = false;
    }
    return true;
    break;
#endif
  }
  return process_record_keymap(keycode, record);
}

// Runs state check and changes underglow color and animation
// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();
  if (rgb_layer_change) {
    switch (biton32(state)) {
    case _NAV:
      rgblight_set_blue;
      rgblight_mode(1);
      break;
    case _SYMB:
      rgblight_set_blue;
      rgblight_mode(2);
      break;
    case _MOUS:
      rgblight_set_yellow;
      rgblight_mode(1);
      break;
    case _MACROS:
      rgblight_set_orange;
      is_overwatch ? rgblight_mode(17) : rgblight_mode(18);
      break;
    case _MEDIA:
      rgblight_set_green;
      rgblight_mode(22);
      break;
    case _GAMEPAD:
      rgblight_set_orange;
      rgblight_mode(17);
      break;
    case _DIABLO:
      rgblight_set_red;
      rgblight_mode(5);
      break;
    case _RAISE:
      rgblight_set_yellow;
      rgblight_mode(5);
      break;
    case _LOWER:
      rgblight_set_orange;
      rgblight_mode(5);
      break;
    case _ADJUST:
      rgblight_set_red;
      rgblight_mode(23);
      break;
    case _COVECUBE:
      rgblight_set_green;
      rgblight_mode(2);
      break;
    default:
      if (default_layer & (1UL << _COLEMAK)) {
        rgblight_set_magenta;
      }
      else if (default_layer & (1UL << _DVORAK)) {
        rgblight_set_green;
      }
      else if (default_layer & (1UL << _WORKMAN)) {
        rgblight_set_purple;
      }
      else {
        rgblight_set_teal;
      }
      rgblight_mode(1);
      break;
    }
  }
#endif
  return layer_state_set_keymap (state);
}


