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
#include "tap_dances.h"
#include "rgb_stuff.h"

userspace_config_t userspace_config;
#if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
  #define DRASHNA_UNICODE_MODE UC_WIN
#else
  // set to 2 for UC_WIN, set to 4 for UC_WINC
  #define DRASHNA_UNICODE_MODE 2
#endif

uint16_t copy_paste_timer;
//  Helper Functions


// This block is for all of the gaming macros, as they were all doing
// the same thing, but with differring text sent.
bool send_game_macro(const char *str, keyrecord_t *record, bool override) {
  if (!record->event.pressed || override) {
    uint16_t keycode;
    if (userspace_config.is_overwatch) {
      keycode = KC_BSPC;
    } else {
      keycode = KC_ENTER;
    }
    clear_keyboard();
    tap_code(keycode);
    wait_ms(50);
    send_string_with_delay(str, MACRO_TIMER);
    wait_ms(50);
    tap_code(KC_ENTER);
  }
  if (override) wait_ms(3000);
  return false;
}

bool mod_key_press_timer (uint16_t code, uint16_t mod_code, bool pressed) {
  static uint16_t this_timer;
  if(pressed) {
      this_timer= timer_read();
  } else {
      if (timer_elapsed(this_timer) < TAPPING_TERM){
          register_code(code);
          unregister_code(code);
      } else {
          register_code(mod_code);
          register_code(code);
          unregister_code(code);
          unregister_code(mod_code);
      }
  }
  return false;
}

bool mod_key_press (uint16_t code, uint16_t mod_code, bool pressed, uint16_t this_timer) {
  if(pressed) {
      this_timer= timer_read();
  } else {
      if (timer_elapsed(this_timer) < TAPPING_TERM){
          register_code(code);
          unregister_code(code);
      } else {
          register_code(mod_code);
          register_code(code);
          unregister_code(code);
          unregister_code(mod_code);
      }
  }
  return false;
}

void bootmagic_lite(void) {
  matrix_scan();
  #if defined(DEBOUNCING_DELAY) && DEBOUNCING_DELAY > 0
    wait_ms(DEBOUNCING_DELAY * 2);
  #elif defined(DEBOUNCE) && DEBOUNCE > 0
    wait_ms(DEBOUNCE * 2);
  #else
    wait_ms(30);
  #endif
  matrix_scan();
   if (matrix_get_row(BOOTMAGIC_LITE_ROW) & (1 << BOOTMAGIC_LITE_COLUMN)) {
    bootloader_jump();
  }
}

// Add reconfigurable functions here, for keymap customization
// This allows for a global, userspace functions, and continued
// customization of the keymap.  Use _keymap instead of _user
// functions in the keymaps
__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void startup_keymap(void) {}

__attribute__ ((weak))
void shutdown_keymap(void) {}

__attribute__ ((weak))
void suspend_power_down_keymap(void) {}

__attribute__ ((weak))
void suspend_wakeup_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}


__attribute__ ((weak))
uint32_t layer_state_set_keymap (uint32_t state) {
  return state;
}

__attribute__ ((weak))
uint32_t default_layer_state_set_keymap (uint32_t state) {
  return state;
}

__attribute__ ((weak))
void led_set_keymap(uint8_t usb_led) {}

__attribute__ ((weak))
void eeconfig_init_keymap(void) {}

// Call user matrix init, set default RGB colors and then
// call the keymap's init function
void matrix_init_user(void) {
  #if !defined(BOOTMAGIC_LITE) && !defined(BOOTMAGIC_ENABLE)
    bootmagic_lite();
  #endif

  userspace_config.raw = eeconfig_read_user();

  #ifdef BOOTLOADER_CATERINA
    DDRD &= ~(1<<5);
    PORTD &= ~(1<<5);

    DDRB &= ~(1<<0);
    PORTB &= ~(1<<0);
  #endif

  #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(DRASHNA_UNICODE_MODE);
    get_unicode_input_mode();
  #endif //UNICODE_ENABLE
  matrix_init_keymap();
  #ifdef RGBLIGHT_ENABLE
    matrix_init_rgb();
  #endif //RGBLIGHT_ENABLE
}

void startup_user (void) {
  // #ifdef RGBLIGHT_ENABLE
  //   matrix_init_rgb();
  // #endif //RGBLIGHT_ENABLE
  startup_keymap();
}

void shutdown_user (void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(1);
  rgblight_setrgb_red();
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
  rgb_led led;
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    led = g_rgb_leds[i];
    if (led.matrix_co.raw < 0xFF) {
      rgb_matrix_set_color( i, 0xFF, 0x00, 0x00 );
    }
  }
#endif //RGB_MATRIX_ENABLE
  shutdown_keymap();
}

void suspend_power_down_user(void) {
    suspend_power_down_keymap();
}

void suspend_wakeup_init_user(void) {
  suspend_wakeup_init_keymap();
}


// No global matrix scan code, so just run keymap's matrix
// scan function
void matrix_scan_user(void) {
  static bool has_ran_yet;
  if (!has_ran_yet) {
    has_ran_yet = true;
    startup_user();
  }

#ifdef TAP_DANCE_ENABLE  // Run Diablo 3 macro checking code.
  run_diablo_macro_check();
#endif // TAP_DANCE_ENABLE

#ifdef RGBLIGHT_ENABLE
  matrix_scan_rgb();
#endif // RGBLIGHT_ENABLE

  matrix_scan_keymap();
}




// Defines actions tor my global custom keycodes. Defined in drashna.h file
// Then runs the _keymap's record handier if not processed here
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
  #if defined(KEYBOARD_ergodox_ez) || defined(KEYBOARD_iris_rev2)
    xprintf("KL: col: %u, row: %u, pressed: %u\n", record->event.key.row, record->event.key.col, record->event.pressed);
  #else
    xprintf("KL: col: %u, row: %u, pressed: %u\n", record->event.key.col, record->event.key.row, record->event.pressed);
  #endif
#endif //KEYLOGGER_ENABLE

  switch (keycode) {
  case KC_QWERTY:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_QWERTY);
    }
    break;
  case KC_COLEMAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_COLEMAK);
    }
    break;
  case KC_DVORAK:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_DVORAK);
    }
    break;
  case KC_WORKMAN:
    if (record->event.pressed) {
      set_single_persistent_default_layer(_WORKMAN);
    }
    break;


  case KC_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
    if (!record->event.pressed) {
      uint8_t temp_mod = get_mods();
      uint8_t temp_osm = get_oneshot_mods();
      clear_mods(); clear_oneshot_mods();
      send_string_with_delay_P(PSTR("make " QMK_KEYBOARD ":" QMK_KEYMAP), 10);
      if (temp_mod & MODS_SHIFT_MASK || temp_osm & MODS_SHIFT_MASK) {
        #if defined(__ARM__)
          send_string_with_delay_P(PSTR(":dfu-util"), 10);
        #elif defined(BOOTLOADER_DFU)
          send_string_with_delay_P(PSTR(":dfu"), 10);
        #elif defined(BOOTLOADER_HALFKAY)
          send_string_with_delay_P(PSTR(":teensy"), 10);
        #elif defined(BOOTLOADER_CATERINA)
          send_string_with_delay_P(PSTR(":avrdude"), 10);
        #endif // bootloader options
      }
      #if defined(KEYBOARD_viterbi)
        send_string_with_delay_P(PSTR(":dfu"), 10);
      #endif
      if (temp_mod & MODS_CTRL_MASK || temp_osm & MODS_CTRL_MASK) { send_string_with_delay_P(PSTR(" -j8 --output-sync"), 10); }
      send_string_with_delay_P(PSTR(SS_TAP(X_ENTER)), 10);
      set_mods(temp_mod);
    }
    break;

  case VRSN: // Prints firmware version
    if (record->event.pressed) {
      send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), MACRO_TIMER);
    }
    break;

// These are a serious of gaming macros.
// Only enables for the viterbi, basically,
// to save on firmware space, since it's limited.
#ifdef MACROS_ENABLED
  case KC_OVERWATCH: // Toggle's if we hit "ENTER" or "BACKSPACE" to input macros
    if (record->event.pressed) { userspace_config.is_overwatch ^= 1; eeconfig_update_user(userspace_config.raw); }
#ifdef RGBLIGHT_ENABLE
    userspace_config.is_overwatch ? rgblight_mode_noeeprom(17) : rgblight_mode_noeeprom(18);
#endif //RGBLIGHT_ENABLE
    break;
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
#endif // MACROS_ENABLED


  case KC_DIABLO_CLEAR:  // reset all Diablo timers, disabling them
#ifdef TAP_DANCE_ENABLE
    if (record->event.pressed) {
      uint8_t dtime;
      for (dtime = 0; dtime < 4; dtime++) {
        diablo_key_time[dtime] = diablo_times[0];
      }
    }
#endif // TAP_DANCE_ENABLE
    break;


  case KC_CCCV:                                    // One key copy/paste
    if(record->event.pressed){
      copy_paste_timer = timer_read();
    } else {
      if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {   // Hold, copy
        register_code(KC_LCTL);
        tap_code(KC_C);
        unregister_code(KC_LCTL);
      } else {                                // Tap, paste
        register_code(KC_LCTL);
        tap_code(KC_V);
        unregister_code(KC_LCTL);
      }
    }
    break;
#ifdef UNICODE_ENABLE
  case UC_FLIP: // (ノಠ痊ಠ)ノ彡┻━┻
    if (record->event.pressed) {
      send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
    }
    break;
  case UC_TABL: // ┬─┬ノ( º _ ºノ)
    if (record->event.pressed) {
      send_unicode_hex_string("252C 2500 252C 30CE 0028 0020 00BA 0020 005F 0020 00BA 30CE 0029");
    }
    break;
  case UC_SHRG: // ¯\_(ツ)_/¯
    if (record->event.pressed) {
      send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
    }
    break;
  case UC_DISA: // ಠ_ಠ
    if (record->event.pressed) {
      send_unicode_hex_string("0CA0 005F 0CA0");
    }
    break;
#endif
  }
  return process_record_keymap(keycode, record) &&
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    process_record_user_rgb(keycode, record) &&
#endif // RGBLIGHT_ENABLE
    process_record_secrets(keycode, record);
}



// Runs state check and changes underglow color and animation
// on layer change, no matter where the change was initiated
// Then runs keymap's layer change check
uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
#ifdef RGBLIGHT_ENABLE
  state = layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
  return layer_state_set_keymap (state);
}


uint32_t default_layer_state_set_user(uint32_t state) {
  state = default_layer_state_set_keymap(state);
#ifdef RGBLIGHT_ENABLE
  state = default_layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
  return state;
}


// Any custom LED code goes here.
// So far, I only have keyboard specific code,
// So nothing goes here.
void led_set_user(uint8_t usb_led) {
  led_set_keymap(usb_led);
}

void eeconfig_init_user(void) {
  userspace_config.raw = 0;
  userspace_config.rgb_layer_change = true;
  eeconfig_update_user(userspace_config.raw);
  #if (defined(UNICODE_ENABLE) || defined(UNICODEMAP_ENABLE) || defined(UCIS_ENABLE))
    set_unicode_input_mode(DRASHNA_UNICODE_MODE);
    get_unicode_input_mode();
  #else
    eeprom_update_byte(EECONFIG_UNICODEMODE, DRASHNA_UNICODE_MODE);
  #endif
}
