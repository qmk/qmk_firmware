#include "arkag.h"
#include "eeprom.h"

/*
 Current Layout and Keeb:
 https://github.com/arkag/qmk_firmware/blob/master/keyboards/mechmini/v2/keymaps/arkag/keymap.c
*/

#include <stdbool.h>

// Start: Written by Chris Lewis
#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define TYPING_SPEED_MAX_VALUE 200
uint8_t typing_speed = 0;

void velocikey_accelerate(void) {
    if (typing_speed < TYPING_SPEED_MAX_VALUE) typing_speed += (TYPING_SPEED_MAX_VALUE / 50);
}

void velocikey_decelerate(void) {
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

static int shift_int = 0;
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
bool          aesthetic     = false,
              shifty        = false;

float song_ussr[][2]     = SONG(USSR_ANTHEM);

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
  int addlim = HUE_MAX - change_amount;
  int sublim = change_amount;
  int leftovers;
  if (should_add) {
    if (current_color.h <= addlim) {
      current_color.h += change_amount;
    } else {
      leftovers = (HUE_MAX + change_amount) % HUE_MAX;
      current_color.h  = 0 + leftovers;
    }
  } else {
    if (current_color.h >= sublim) {
      current_color.h -= change_amount;
    } else {
      leftovers = change_amount - current_color.h;
      current_color.h  = HUE_MAX - leftovers;
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
    }
    velocikey_decelerate();
    fade_interval = velocikey_match_speed(1, 25);
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
    if (underglow.h == HUE_MAX) {
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
    set_unicode_input_mode(UNICODE_MODE_MACOS);
    underglow = (Color){ 213, 255, 255 };
    break;
  case OS_WIN:
    set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
    underglow = (Color){ 128, 255, 255 };
    break;
  case OS_NIX:
    set_unicode_input_mode(UNICODE_MODE_LINUX);
    underglow = (Color){ 43, 255, 255 };
    break;
  default:
    underglow = (Color){ 0, 0, 255 };
  }
  set_color(underglow, update);
  flash_color           = underglow;
  flash_state           = flash_off;
  state                 = boot;
  num_extra_flashes_off = 1;
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

// register Meh if Win or Hyper if other
// KC_MEH/HYPR registers both sides, causes issues with some apps
// I'll do it myself, then
void meh_hyper(bool press) {
  if (current_os == OS_WIN) {
    (press) ? register_mods(L_BIT_MEH) : unregister_mods(L_BIT_MEH);
  } else {
    (press) ? register_mods(L_BIT_HYPR) : unregister_mods(L_BIT_HYPR);
  }
}

void multi_tap(uint8_t num_of_chars, uint16_t keycode, bool use_shift) {
  if (use_shift) {
    register_code(KC_LSFT);
  }
  for (int i = 0; i < num_of_chars; i++) {
    tap_code(keycode);
  }
  if (use_shift) {
    unregister_code(KC_LSFT);
  }
}

void pair_surround_type(uint8_t num_of_chars, uint16_t keycode, bool use_shift) {
  for (int i = 0; i < num_of_chars; i++) {
    (use_shift) ? register_mods(MOD_BIT( KC_LSFT)) : NULL;  
    tap_code(keycode);
    tap_code((keycode == KC_LCBR) ? KC_RCBR : (keycode == KC_LBRC) ? KC_RBRC : (keycode == KC_LPRN) ? KC_RPRN : KC_NO);
    (use_shift) ? unregister_mods(MOD_BIT( KC_LSFT)) : NULL;
    tap_code(KC_LEFT);
  }
}

void surround_type(uint8_t num_of_chars, uint16_t keycode, bool use_shift) {
  for (int i = 0; i < num_of_chars; i++) {
    (use_shift) ? register_mods(MOD_BIT( KC_LSFT)) : NULL;
    tap_code(keycode);
    (use_shift) ? unregister_mods(MOD_BIT( KC_LSFT)) : NULL;
  }
  multi_tap(num_of_chars / 2, KC_LEFT, false);
}

void long_keystroke(size_t num_of_keys, uint16_t keys[]) {
  for (int i = 0; i < num_of_keys-1; i++) {
    register_code(keys[i]);
  }
  tap_code(keys[num_of_keys-1]);
  for (int i = 0; i < num_of_keys-1; i++) {
    unregister_code(keys[i]);
  }
}

void pri_mod_keystroke(uint16_t key) {
  pri_mod(true);
  tap_code(key);
  pri_mod(false);
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
        long_keystroke(2, (uint16_t[]){KC_LGUI, KC_PAUSE});
      } else {
        return;
      }
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
    SEQ_THREE_KEYS(KC_C, KC_A, KC_D) {
      if (current_os == OS_WIN) {
        long_keystroke(3, (uint16_t[]){KC_LCTL, KC_LALT, KC_DEL});
      } else {
      }
    }
    SEQ_THREE_KEYS(KC_C, KC_A, KC_E) {
      if (current_os == OS_WIN) {
        long_keystroke(3, (uint16_t[]){KC_LCTL, KC_LALT, KC_END});
      } else {
      }
    }
    // end OS functions

    // begin format functions
    SEQ_ONE_KEY(KC_B) {
      surround_type(2, KC_8, true);
    }
    SEQ_ONE_KEY(KC_I) {
      surround_type(2, KC_MINS, true);
    }
    SEQ_ONE_KEY(KC_U) {
      surround_type(4, KC_MINS, true);
    }
    SEQ_ONE_KEY(KC_S) {
      surround_type(4, KC_GRAVE, true);
    }
    SEQ_ONE_KEY(KC_C) {
      register_unicode(0x00E7); // ç
    }
    SEQ_TWO_KEYS(KC_A, KC_V) {
      surround_type(2, KC_QUOT, true);
      pair_surround_type(2, KC_LCBR, true);
      surround_type(2, KC_SPC, false);
    }
    SEQ_TWO_KEYS(KC_M, KC_L) {
      pair_surround_type(1, KC_LBRC, false);
      SEND_STRING("LINK_NAME");
      tap_code(KC_RGHT);
      pair_surround_type(1, KC_LPRN, true);
      pri_mod_keystroke(KC_V);
    }
    SEQ_TWO_KEYS(KC_C, KC_C) {
      surround_type(2, KC_GRAVE, false);
    }
    SEQ_THREE_KEYS(KC_C, KC_C, KC_C) {
      surround_type(6, KC_GRAVE, false);
    }
    SEQ_ONE_KEY(KC_E) {
      register_unicode(0x00E8); // è
    }
    SEQ_TWO_KEYS(KC_E, KC_E) {
      register_unicode(0x00E9); // é
    }
    // end format functions

    // start fancy functions
    SEQ_TWO_KEYS(KC_V, KC_P) {
      SEND_STRING("ggvG}x:set paste\ni");
      pri_mod_keystroke(KC_V);
    }
    SEQ_THREE_KEYS(KC_C, KC_C, KC_ENT) {
      surround_type(6, KC_GRAVE, false);
      pri_mod_keystroke(KC_V);
      multi_tap(3, KC_RGHT, false);
      tap_code(KC_ENTER);
    }
    SEQ_THREE_KEYS(KC_T, KC_C, KC_ENT) {
      multi_tap(3, KC_GRAVE, false);
      pri_mod_keystroke(KC_V);
      multi_tap(2, KC_ENTER, false);
    }
    // end fancy functions

    // start typing functions
    SEQ_TWO_KEYS(KC_T, KC_M) {
      register_unicode(0x2122); // ™
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(".\\Administrator");
    }
    SEQ_THREE_KEYS(KC_D, KC_D, KC_D) {
      SEND_STRING(".\\Administrator");
      tap_code(KC_TAB);
      pri_mod_keystroke(KC_V);
      tap_code(KC_ENTER);
    }
    SEQ_THREE_KEYS(KC_L, KC_O, KC_D) {
      send_unicode_string("ಠ__ಠ");
    }
    SEQ_THREE_KEYS(KC_M, KC_A, KC_P) {
      SEND_STRING("https://github.com/qmk/qmk_firmware/tree/master/users/arkag");
    }
    SEQ_TWO_KEYS(KC_F, KC_F) {
      send_unicode_string("(╯‵Д′)╯彡┻━┻");
    }
    SEQ_THREE_KEYS(KC_F, KC_F, KC_F) {
      send_unicode_string("┬─┬ノ( º _ º ノ)");
    }
    SEQ_THREE_KEYS(KC_L, KC_O, KC_L) {
      send_unicode_string("( ͡° ͜ʖ ͡°)");
    }
    SEQ_THREE_KEYS(KC_S, KC_S, KC_S) {
      send_unicode_string("¯\\_(ツ)_/¯");
    }
    // end typing functions

  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (aesthetic) {
    switch (keycode) {
    case KC_A ... KC_0:
    case KC_SPACE ... KC_SLASH:
      if (record->event.pressed) {
        state = active;
        velocikey_accelerate();
        tap_code(keycode);
        tap_code(KC_SPACE);
      }
      return false;

    case KC_BACKSPACE:
      if (record->event.pressed) {
        state = active;
        velocikey_accelerate();
        tap_code(keycode);
        tap_code(keycode);
      }
      return false;
    default: // Do nothing
      break;
    }
  }

  if (shifty) {
    switch (keycode) {
    case KC_A ... KC_Z:
      if (record->event.pressed) {
        shift_int += (rand() % 5);
        int shift = ((shift_int % 2) == 1) ? true : false;
        state = active;
        velocikey_accelerate();
        (shift) ? register_code(KC_LSFT) : NULL;
        tap_code(keycode);
        (shift) ? unregister_code(KC_LSFT) : NULL;
      }
      return false;
    case KC_SPC:
      if (record->event.pressed) {
        state = active;
        velocikey_accelerate();
        tap_code(keycode);
      }
      return false;
    default: // Do nothing
      break;
    }
  }

  switch (keycode) {
  #ifdef AUDIO_ENABLE
        case M_USSR:
            PLAY_SONG(song_ussr);
            return false;
  #endif

  case M_OS:
    if (record->event.pressed){
      set_os((current_os+1) % _OS_COUNT, true);
    }
    return false;

  case M_DASH:
    if (record->event.pressed){
      register_unicode(0x2014); // —
    }
    return false;
  case M_LMHYP:
  case M_EHYPR:
    (keycode = M_LMHYP) ? (record->event.pressed) ? layer_on(_ARROW) : layer_off(_ARROW) : NULL;
    meh_hyper(record->event.pressed);
    return false;

  case M_SFTY:
    if(record->event.pressed){
      num_extra_flashes_off = (shifty) ?  1 : 0;
      shifty = !shifty;
      flash_color = underglow;
      flash_state = flash_off;
      return false;
    }

  case M_AEST:
    if(record->event.pressed){
      num_extra_flashes_off = (aesthetic) ? 1 : 0;
      aesthetic = !aesthetic;
      flash_color = underglow;
      flash_state = flash_off;
      return false;
    }

  default:
    if (record->event.pressed) {
      state = active;
      velocikey_accelerate();
    }
    return true;
  }
}
