#include "arkag.h"

/*
 Current Layout and Keeb:
 https://github.com/arkag/qmk_firmware/blob/master/keyboards/mechmini/v2/keymaps/arkag/keymap.c
*/

// Start: Written by konstantin: vomindoraan
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void send_unicode_hex_string(const char *str) {
  if (!str) { return; } // Saftey net
  while (*str) {
    // Find the next code point (token) in the string
    for (; *str == ' '; str++);
    size_t n = strcspn(str, " "); // Length of the current token
    char code_point[n+1];
    strncpy(code_point, str, n);
    code_point[n] = '\0'; // Make sure it's null-terminated

    // Normalize the code point: make all hex digits lowercase
    for (char *p = code_point; *p; p++) {
            *p = tolower(*p);
    }

    // Send the code point as a Unicode input string
    unicode_input_start();
    send_string(code_point);
    unicode_input_finish();
    str += n; // Move to the first ' ' (or '\0') after the current token
  }
}
// End: Written by konstantin: vomindoraan

// Start: Written by Chris Lewis
#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define TYPING_SPEED_MAX_VALUE 200
uint8_t typing_speed = 0;

void velocikey_accelerate() {
    if (typing_speed < TYPING_SPEED_MAX_VALUE) typing_speed += (TYPING_SPEED_MAX_VALUE / 50);
}

void velocikey_decelerate() {
  static uint16_t decay_timer = 0;

  if (timer_elapsed(decay_timer) > 500 || decay_timer == 0) {
    if (typing_speed > 0) typing_speed -= 1;
    //Decay a little faster at half of max speed
    if (typing_speed > TYPING_SPEED_MAX_VALUE / 2) typing_speed -= 1;
    //Decay even faster at 3/4 of max speed
    if (typing_speed > TYPING_SPEED_MAX_VALUE / 4 * 3) typing_speed -= 3;
    decay_timer = timer_read();
  }
}

uint8_t velocikey_match_speed(uint8_t minValue, uint8_t maxValue) {
  return MAX(minValue, maxValue - (maxValue - minValue) * ((float)typing_speed / TYPING_SPEED_MAX_VALUE));
}
// End: Written by Chris Lewis

uint8_t       current_os,
              mod_primary_mask,
              fade_interval,
              num_extra_flashes_off = 0;
Color         underglow,
              flash_color,
              saved_color,
              hsv_none      = {0,0,0};
flashState    flash_state   = no_flash;
fadeState     fade_state    = add_fade;
activityState state         = boot;

void set_color (Color new, bool update) {
  rgblight_sethsv_eeprom_helper(new.h, new.s, new.v, update);
}

void save_color(Color to_save) {
  saved_color = to_save;
}

void reset_color(void) {
  underglow = saved_color;
}

Color mod_color(Color current_color, bool should_add, uint8_t change_amount) {
  save_color(underglow);
  int addlim = 359 - change_amount;
  int sublim = change_amount;
  int leftovers;
  if (should_add) {
    if (current_color.h <= addlim) {
      current_color.h += change_amount;
    } else {
      leftovers = (359 + change_amount) % 359;
      current_color.h  = 0 + leftovers;
    }
  } else {
    if (current_color.h >= sublim) {
      current_color.h -= change_amount;
    } else {
      leftovers = change_amount - current_color.h;
      current_color.h  = 359 - leftovers;
    }
  }
  return current_color;
}

void check_state (void) {
  static uint16_t active_timer;
  if (!active_timer) {active_timer = timer_read();}
  static bool activated, deactivated, slept;
  switch (state) {
  case active:
    if (!activated) {
      if (slept) {rgblight_mode_noeeprom(1);}
      activated = true;
      deactivated = false;
      slept = false;
    }
    fade_interval = velocikey_match_speed(1, 25);
    if (timer_elapsed(active_timer) < INACTIVE_DELAY) {return;}
    active_timer = timer_read();
    state = inactive;
    return;

  case inactive:
    if (!deactivated) {
      deactivated = true;
      activated = false;
      slept = false;
    }
    velocikey_decelerate();
    fade_interval = velocikey_match_speed(1, 25);
    if (timer_elapsed(active_timer) < SLEEP_DELAY) {return;}
    state = sleeping;
    return;

  case sleeping:
    if (!slept) {
      rgblight_mode_noeeprom(4);
      slept = true;
      activated = false;
      deactivated = false;
    }
    return;

  case boot:
    return;
  }
}

void fade_rgb (void) {
  static uint16_t fade_timer;
  if (state == boot) {return;}
  if (!fade_timer) {fade_timer = timer_read();}
  if (timer_elapsed(fade_timer) < fade_interval) {return;}
  switch (fade_state) {
  case add_fade:
    if (underglow.h == 359) {
      fade_state = sub_fade;
      return;
    }
    underglow.h = underglow.h + 1;
    break;

  case sub_fade:
    if (underglow.h == 0) {
      fade_state = add_fade;
      return;
    }
    underglow.h = underglow.h - 1;
    break;
  }
  fade_timer = timer_read();
  if (flash_state == no_flash) {
    set_color(underglow, false);
  }
}

void flash_rgb (void) {
  static uint16_t flash_timer;
  switch(flash_state) {
  case no_flash:
    return;

  case flash_off:
    if (!flash_timer) {flash_timer = timer_read();}
    if (timer_elapsed(flash_timer) >= LED_FLASH_DELAY) {
      set_color(hsv_none, false);
      flash_timer = timer_read();
      flash_state = flash_on;
    }
    return;

  case flash_on:
    if (timer_elapsed(flash_timer) >= LED_FLASH_DELAY) {
      set_color(flash_color, false);
      flash_timer = timer_read();
      if (num_extra_flashes_off > 0) {
        flash_state = flash_off;
        num_extra_flashes_off--;
      } else {
        set_color(underglow, false);
        flash_state = no_flash;
      }
    }
    return;
  }
}

void set_os (uint8_t os, bool update) {
  current_os = os;
  if (update) {
    eeprom_update_byte(EECONFIG_USERSPACE, current_os);
  }
  switch (os) {
  case OS_MAC:
    set_unicode_input_mode(UC_OSX);
    underglow = (Color){ 300, 255, 255 };
    mod_primary_mask = MOD_GUI_MASK;
    break;
  case OS_WIN:
    set_unicode_input_mode(UC_WINC);
    underglow = (Color){ 180, 255, 255 };
    mod_primary_mask = MOD_CTL_MASK;
    break;
  case OS_NIX:
    set_unicode_input_mode(UC_LNX);
    underglow = (Color){ 60, 255, 255 };
    mod_primary_mask = MOD_CTL_MASK;
    break;
  default:
    underglow = (Color){ 0, 0, 255 };
    mod_primary_mask = MOD_CTL_MASK;
  }
  set_color(underglow, update);
  flash_color           = underglow;
  flash_state           = flash_off;
  state                 = boot;
  num_extra_flashes_off = 1;
}

void tap_key(uint8_t keycode) {
  register_code(keycode);
  unregister_code(keycode);
}

// register GUI if Mac or Ctrl if other
void pri_mod(bool press) {
  if (press) {
    if (current_os == OS_MAC) {
      register_code(KC_LGUI);
    } else {
      register_code(KC_LCTL);
    }
  } else {
    if (current_os == OS_MAC) {
      unregister_code(KC_LGUI);
    } else {
      unregister_code(KC_LCTL);
    }
  }
}

// register Ctrl if Mac or GUI if other
void sec_mod(bool press) {
  if (press) {
    if (current_os == OS_MAC) {
      register_code(KC_LCTL);
    } else {
      register_code(KC_LGUI);
    }
  } else {
    if (current_os == OS_MAC) {
      unregister_code(KC_LCTL);
    } else {
      unregister_code(KC_LGUI);
    }
  }
}

void surround_type(uint8_t num_of_chars, uint16_t keycode, bool use_shift) {
  if (use_shift) {
    register_code(KC_LSFT);
  }
  for (int i = 0; i < num_of_chars; i++) {
    tap_key(keycode);
  }
  if (use_shift) {
    unregister_code(KC_LSFT);
  }
  for (int i = 0; i < (num_of_chars/2); i++) {
    tap_key(KC_LEFT);
  }
}

void long_keystroke(size_t num_of_keys, uint16_t keys[]) {
  for (int i = 0; i < num_of_keys-1; i++) {
    register_code(keys[i]);
  }
  tap_key(keys[num_of_keys-1]);
  for (int i = 0; i < num_of_keys-1; i++) {
    unregister_code(keys[i]);
  }
}

void dance_grv (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_key(KC_GRV);
  } else if (state->count == 2) {
    surround_type(2, KC_GRAVE, false);
  } else {
    surround_type(6, KC_GRAVE, false);
  }
}

void dance_quot (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_key(KC_QUOT);
  } else if (state->count == 2) {
    surround_type(2, KC_QUOTE, false);
  } else if (state->count == 3) {
    surround_type(2, KC_QUOTE, true);
  }
}

void dance_strk (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    surround_type(4, KC_TILDE, true);
  } else if (state->count == 2) {
    if (current_os == OS_MAC) {
      long_keystroke(3, (uint16_t[]){KC_LGUI, KC_LSFT, KC_4});
    } else if (current_os == OS_WIN) {
      long_keystroke(3, (uint16_t[]){KC_LGUI, KC_LSFT, KC_S});
    } else {
      return;
    }
  }
}

void dance_3 (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_key(KC_3);
  } else if (state->count == 2) {
    send_unicode_hex_string("00E8");
  } else if (state->count == 3) {
    send_unicode_hex_string("00E9");
  }
}

void dance_c (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    tap_key(KC_C);
  } else if (state->count == 2) {
    send_unicode_hex_string("00E7");
  }
}

void matrix_init_user(void) {
  current_os = eeprom_read_byte(EECONFIG_USERSPACE);
  set_os(current_os, false);
}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  check_state();
  flash_rgb();
  fade_rgb();
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // begin OS functions
    SEQ_TWO_KEYS(KC_P, KC_B) {
      if (current_os == OS_WIN) {
              SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_PAUSE) SS_UP(X_LGUI));
      } else {
      }
    }
    SEQ_THREE_KEYS(KC_C, KC_A, KC_D) {
      if (current_os == OS_WIN) {
              SEND_STRING(SS_DOWN(X_LCTRL) SS_DOWN(X_LALT) SS_TAP(X_DELETE) SS_UP(X_LALT) SS_UP(X_LCTRL));
      } else {
      }
    }
    SEQ_FOUR_KEYS(KC_C, KC_A, KC_L, KC_C) {
      if (current_os == OS_WIN) {
        SEND_STRING(SS_TAP(X_CALCULATOR));
      } else if (current_os == OS_MAC) {
        SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_SPACE) SS_UP(X_LGUI) "calculator" SS_TAP(X_ENTER));
      }
    }
    // end OS functions

    // begin format functions
    SEQ_ONE_KEY(KC_B) {
      surround_type(4, KC_8, true);
    }
    SEQ_ONE_KEY(KC_I) {
      surround_type(2, KC_8, true);
    }
    SEQ_ONE_KEY(KC_U) {
      surround_type(4, KC_MINS, true);
    }
    SEQ_ONE_KEY(KC_S) {
      surround_type(4, KC_GRAVE, true);
    }
    SEQ_TWO_KEYS(KC_S, KC_S) {
      if (current_os == OS_MAC) {
        long_keystroke(3, (uint16_t[]){KC_LGUI, KC_LSFT, KC_4});
      } else if (current_os == OS_WIN) {
        long_keystroke(3, (uint16_t[]){KC_LGUI, KC_LSFT, KC_S});
      } else {
        return;
      }
    }
    SEQ_ONE_KEY(KC_C) {
      surround_type(2, KC_GRAVE, false);
    }
    SEQ_TWO_KEYS(KC_C, KC_C) {
      surround_type(6, KC_GRAVE, false);
    }
    // end format functions

    // start fancy functions
    SEQ_THREE_KEYS(KC_C, KC_C, KC_C) {
      surround_type(6, KC_GRAVE, false);
      pri_mod(true);
      tap_key(KC_V);
      pri_mod(false);
      tap_key(KC_RGHT);
      tap_key(KC_RGHT);
      tap_key(KC_RGHT);
      tap_key(KC_ENTER);
    }
    // end fancy functions

    // start typing functions
    SEQ_TWO_KEYS(KC_T, KC_M) {
      // ™
      send_unicode_hex_string("2122");
    }
    SEQ_THREE_KEYS(KC_G, KC_G, KC_T) {
      SEND_STRING("@GrahamGoldenTech.com");
    }
    SEQ_THREE_KEYS(KC_L, KC_O, KC_D) {
      // ಠ__ಠ
      send_unicode_hex_string("0CA0 005F 005F 0CA0");
    }
    SEQ_FOUR_KEYS(KC_R, KC_E, KC_P, KC_O) {
      SEND_STRING("https://github.com/qmk/qmk_firmware/tree/master/users/arkag");
    }
    SEQ_FOUR_KEYS(KC_F, KC_L, KC_I, KC_P) {
      // (╯‵Д′)╯彡┻━┻
      send_unicode_hex_string("0028 256F 2035 0414 2032 0029 256F 5F61 253B 2501 253B");
    }
    SEQ_FIVE_KEYS(KC_U, KC_F, KC_L, KC_I, KC_P) {
      // ┬─┬ノ( º _ º ノ)
      send_unicode_hex_string("252C 2500 252C 30CE 0028 0020 00BA 0020 005F 0020 00BA 0020 30CE 0029");
    }
    SEQ_FIVE_KEYS(KC_L, KC_E, KC_N, KC_N, KC_Y) {
      // ( ͡° ͜ʖ ͡°)
      send_unicode_hex_string("0028 0020 0361 00B0 0020 035C 0296 0020 0361 00B0 0029");
    }
    SEQ_FIVE_KEYS(KC_S, KC_H, KC_R, KC_U, KC_G) {
      // ¯\_(ツ)_/¯
      send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
    }
    // end typing functions

  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case M_PMOD:
    if (record->event.pressed) {
      pri_mod(true);
    } else {
      pri_mod(false);
    }
    return false;

  case M_SMOD:
    if (record->event.pressed) {
      sec_mod(true);
    } else {
      sec_mod(false);
    }
    return false;

  case M_OS:
    if (record->event.pressed) {
      set_os((current_os+1) % _OS_COUNT, true);
    }
    return false;

  default:
    if (record->event.pressed) {
      state = active;
      velocikey_accelerate();
    }
    return true;
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_3_GRV_ACT]      = ACTION_TAP_DANCE_FN (dance_3),
  [TD_C_CED]          = ACTION_TAP_DANCE_FN (dance_c),
  [TD_GRV_3GRV]       = ACTION_TAP_DANCE_FN (dance_grv),
  [TD_SING_DOUB]      = ACTION_TAP_DANCE_FN (dance_quot),
  [TD_STRK_SHOT]      = ACTION_TAP_DANCE_FN (dance_strk),
  [TD_HYPH_UNDR]      = ACTION_TAP_DANCE_DOUBLE (KC_MINS, LSFT(KC_MINS)),
  [TD_BRCK_PARN_O]    = ACTION_TAP_DANCE_DOUBLE (KC_LBRC, LSFT(KC_9)),
  [TD_BRCK_PARN_C]    = ACTION_TAP_DANCE_DOUBLE (KC_RBRC, LSFT(KC_0)),
  [TD_LALT_RALT]      = ACTION_TAP_DANCE_DOUBLE (KC_LALT, KC_RALT),
};
