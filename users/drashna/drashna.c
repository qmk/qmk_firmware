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

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#include "secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familiar enough to know which is better or why...
PROGMEM const char secret[][64] = {
  "test1",
  "test2",
  "test3",
  "test4",
  "test5"
};
#endif


#ifdef FAUXCLICKY_ENABLE
float fauxclicky_pressed_note[2]  = MUSICAL_NOTE(_A6, 2);  // (_D4, 0.25);
float fauxclicky_released_note[2] = MUSICAL_NOTE(_A6, 2); // (_C4, 0.125);
#else // FAUXCLICKY_ENABLE
float fauxclicky_pressed[][2]             = SONG(S__NOTE(_A6)); // change to your tastes
float fauxclicky_released[][2]             = SONG(S__NOTE(_A6)); // change to your tastes
#endif // FAUXCLICKY_ENABLE

bool faux_click_enabled = false;
bool is_overwatch = false;
#ifdef RGBLIGHT_ENABLE
bool rgb_layer_change = true;
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

#endif // TAP_DANCE_ENABLE


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


// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  uint8_t default_layer = eeconfig_read_default_layer();

  rgblight_enable();

  if (true) {
    if (default_layer & (1UL << _COLEMAK)) {
      rgblight_sethsv_magenta();
    }
    else if (default_layer & (1UL << _DVORAK)) {
      rgblight_sethsv_green();
    }
    else if (default_layer & (1UL << _WORKMAN)) {
      rgblight_sethsv_goldenrod();
    }
    else {
      rgblight_sethsv_teal();
    }
  }
  else
  {
    rgblight_setrgb_red();
    rgblight_mode(5);
  }
#endif // RGBLIGHT_ENABLE

#if ( defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE) )
	set_unicode_input_mode(UC_WINC);
#endif //UNICODE_ENABLE

  matrix_init_keymap();
}
// No global matrix scan code, so just run keymap's matrix
// scan function
void matrix_scan_user(void) {
#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
  run_diablo_macro_check();
#endif // TAP_DANCE_ENABLE
  matrix_scan_keymap();
}

// This block is for all of the gaming macros, as they were all doing
// the same thing, but with differring text sent.
bool send_game_macro(const char *str, keyrecord_t *record, bool override) {
  if (!record->event.pressed || override) {
    clear_keyboard();
    register_code(is_overwatch ? KC_BSPC : KC_ENTER);
    unregister_code(is_overwatch ? KC_BSPC : KC_ENTER);
    wait_ms(50);
    send_string(str);
    register_code(KC_ENTER);
    unregister_code(KC_ENTER);
  }
  if (override) wait_ms(3000);
  return false;
}


// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
  xprintf("KL: row: %u, column: %u, pressed: %u\n", record->event.key.col, record->event.key.row, record->event.pressed);
#endif //CONSOLE_ENABLE

  // Run custom faux click code, but only if faux clicky is enabled
#ifdef AUDIO_ENABLE
  if ( (faux_click_enabled && keycode != KC_FXCL) || (!faux_click_enabled && keycode == KC_FXCL) ) {
    if (record->event.pressed) {
      stop_all_notes();
      PLAY_SONG(fauxclicky_pressed);
    } else {
      stop_all_notes();
      PLAY_SONG(fauxclicky_released);
    }
  }
#endif //AUDIO_ENABLE


  switch (keycode) {
  case KC_QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;
    break;
  case KC_COLEMAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_COLEMAK);
    }
    return false;
    break;
  case KC_DVORAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_DVORAK);
    }
    return false;
    break;
  case KC_WORKMAN:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_WORKMAN);
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


  case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
    if (!record->event.pressed) {
      SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP
#if  (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
                   ":dfu"
#elif defined(BOOTLOADER_HALFKAY)
                   ":teensy"
#elif defined(BOOTLOADER_CATERINA)
                   ":avrdude"
#endif // bootloader options
                   SS_TAP(X_ENTER));
    }
    return false;
    break;


  case KC_RESET: // Custom RESET code that sets RGBLights to RED
    if (!record->event.pressed) {
#ifdef RGBLIGHT_ENABLE
      rgblight_enable();
      rgblight_mode(1);
      rgblight_setrgb_red();
#endif // RGBLIGHT_ENABLE
      reset_keyboard();
    }
    return false;
    break;


  case EPRM: // Resets EEPROM
    if (record->event.pressed) {
      eeconfig_init();
    }
    return false;
    break;
  case VRSN: // Prints firmware version
    if (record->event.pressed) {
      SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
    }
    return false;
    break;


  case KC_SECRET_1 ... KC_SECRET_5: // Secrets!  Externally defined strings, not stored in repo
    if (!record->event.pressed) {
      clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
      send_string_P(secret[keycode - KC_SECRET_1]);
    }
    return false;
    break;


// These are a serious of gaming macros.
// Only enables for the viterbi, basically,
// to save on firmware space, since it's limited.
#if !(defined(KEYBOARD_orthodox_rev1) || defined(KEYBOARD_orthodox_rev3) || defined(KEYBOARD_ergodox_ez))
  case KC_OVERWATCH: // Toggle's if we hit "ENTER" or "BACKSPACE" to input macros
    if (record->event.pressed) { is_overwatch = !is_overwatch; }
#ifdef RGBLIGHT_ENABLE
    is_overwatch ? rgblight_mode(17) : rgblight_mode(18);
#endif //RGBLIGHT_ENABLE
    return false; break;
  case KC_SALT:
    return send_game_macro("Salt, salt, salt...", record, false);
  case KC_MORESALT:
    return  send_game_macro("Please sir, can I have some more salt?!", record, false);
  case KC_SALTHARD:
    return send_game_macro("Your salt only makes me harder, and even more aggressive!", record, false);
  case KC_GOODGAME:
    return send_game_macro("Good game, everyone!", record, false);
  case KC_GLHF:
    return send_game_macro("Good luck, have fun!!!", record, false);
  case KC_SYMM:
    return send_game_macro("Left click to win!", record, false);
  case KC_JUSTGAME:
    return send_game_macro("It may be a game, but if you don't want to actually try, please go play AI, so that people that actually want to take the game seriously and \"get good\" have a place to do so without trolls like you throwing games.", record, false);
  case KC_TORB:
    return send_game_macro("That was positively riveting!", record, false);
  case KC_AIM:
    send_game_macro("That aim is absolutely amazing. It's almost like you're a machine!", record, true);
    return send_game_macro("Wait! That aim is TOO good!  You're clearly using an aim hack! CHEATER!", record, false);
  case KC_C9:
    return send_game_macro("OMG!!!  C9!!!", record, false);
  case KC_GGEZ:
    return send_game_macro("That was a fantastic game, though it was a bit easy. Try harder next time!", record, false);
#endif // !(defined(KEYBOARD_orthodox_rev1) || defined(KEYBOARD_orthodox_rev3) || defined(KEYBOARD_ergodox_ez))


#ifdef TAP_DANCE_ENABLE
  case KC_DIABLO_CLEAR:  // reset all Diablo timers, disabling them
    if (record->event.pressed) {
      uint8_t dtime;
      for (dtime = 0; dtime < 4; dtime++) {
        diablo_key_time[dtime] = diablo_times[0];
      }
    }
    return false; break;
#endif // TAP_DANCE_ENABLE


  case KC_FXCL:
    if (!record->event.pressed) { // Toggles the custom faux click code
      faux_click_enabled = !faux_click_enabled;
    }
    return false; break;
  case KC_RGB_T:  // This allows me to use underglow as layer indication, or as normal
#ifdef RGBLIGHT_ENABLE
    if (record->event.pressed) {
      rgb_layer_change = !rgb_layer_change;
      if (rgb_layer_change) {
        layer_state_set(layer_state); // This is needed to immediately set the layer color (looks better)
      }
    }
#endif // RGBLIGHT_ENABLE
    return false; break;
#ifdef RGBLIGHT_ENABLE
  case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT: // quantum_keycodes.h L400 for definitions
    if (record->event.pressed) { //This disables layer indication, as it's assumed that if you're changing this ... you want that disabled
      rgb_layer_change = false;
    }
    return true; break;
#endif // RGBLIGHT_ENABLE
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
      rgblight_sethsv_blue();
      rgblight_mode(1);
      break;
    case _SYMB:
      rgblight_sethsv_blue();
      rgblight_mode(2);
      break;
    case _MOUS:
      rgblight_sethsv_yellow();
      rgblight_mode(1);
      break;
    case _MACROS:
      rgblight_sethsv_orange();
      is_overwatch ? rgblight_mode(17) : rgblight_mode(18);
      break;
    case _MEDIA:
      rgblight_sethsv_chartreuse();
      rgblight_mode(22);
      break;
    case _GAMEPAD:
      rgblight_sethsv_orange();
      rgblight_mode(17);
      break;
    case _DIABLO:
      rgblight_sethsv_red();
      rgblight_mode(5);
      break;
    case _RAISE:
      rgblight_sethsv_yellow();
      rgblight_mode(5);
      break;
    case _LOWER:
      rgblight_sethsv_orange();
      rgblight_mode(5);
      break;
    case _ADJUST:
      rgblight_sethsv_red();
      rgblight_mode(23);
      break;
    case _COVECUBE:
      rgblight_sethsv_green();
      rgblight_mode(2);
      break;
    default: //  for any other layers, or the default layer
      if (default_layer & (1UL << _COLEMAK)) {
        rgblight_sethsv_magenta();
      }
      else if (default_layer & (1UL << _DVORAK)) {
        rgblight_sethsv_green();
      }
      else if (default_layer & (1UL << _WORKMAN)) {
        rgblight_sethsv_goldenrod();
      }
      else {
        rgblight_sethsv_teal();
      }
      if (biton32(state) == _MODS) { // If the non-OSM layer is enabled, then breathe
        rgblight_mode(2);
      } else {                       // otherwise, stay solid
        rgblight_mode(1);
      }
      break;
    }
  }
#endif // RGBLIGHT_ENABLE
  return layer_state_set_keymap (state);
}


// Any custom LED code goes here.
// So far, I only have keyboard specific code,
// So nothing goes here.
void led_set_user(uint8_t usb_led) {
  led_set_keymap(usb_led);
}
