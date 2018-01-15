/* Copyright 2016-2017 Jack Humbert
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

#include "quantum.h"
#ifdef PROTOCOL_LUFA
#include "outputselect.h"
#endif

#ifndef TAPPING_TERM
#define TAPPING_TERM 200
#endif

#ifndef BREATHING_PERIOD
#define BREATHING_PERIOD 6
#endif

#include "backlight.h"
extern backlight_config_t backlight_config;

#ifdef FAUXCLICKY_ENABLE
#include "fauxclicky.h"
#endif

#ifdef AUDIO_ENABLE
  #ifndef GOODBYE_SONG
    #define GOODBYE_SONG SONG(GOODBYE_SOUND)
  #endif
  #ifndef AG_NORM_SONG
    #define AG_NORM_SONG SONG(AG_NORM_SOUND)
  #endif
  #ifndef AG_SWAP_SONG
    #define AG_SWAP_SONG SONG(AG_SWAP_SOUND)
  #endif
  float goodbye_song[][2] = GOODBYE_SONG;
  float ag_norm_song[][2] = AG_NORM_SONG;
  float ag_swap_song[][2] = AG_SWAP_SONG;
  #ifdef DEFAULT_LAYER_SONGS
    float default_layer_songs[][16][2] = DEFAULT_LAYER_SONGS;
  #endif
#endif

static void do_code16 (uint16_t code, void (*f) (uint8_t)) {
  switch (code) {
  case QK_MODS ... QK_MODS_MAX:
    break;
  default:
    return;
  }

  if (code & QK_LCTL)
    f(KC_LCTL);
  if (code & QK_LSFT)
    f(KC_LSFT);
  if (code & QK_LALT)
    f(KC_LALT);
  if (code & QK_LGUI)
    f(KC_LGUI);

  if (code < QK_RMODS_MIN) return;

  if (code & QK_RCTL)
    f(KC_RCTL);
  if (code & QK_RSFT)
    f(KC_RSFT);
  if (code & QK_RALT)
    f(KC_RALT);
  if (code & QK_RGUI)
    f(KC_RGUI);
}

static inline void qk_register_weak_mods(uint8_t kc) {
    add_weak_mods(MOD_BIT(kc));
    send_keyboard_report();
}

static inline void qk_unregister_weak_mods(uint8_t kc) {
    del_weak_mods(MOD_BIT(kc));
    send_keyboard_report();
}

static inline void qk_register_mods(uint8_t kc) {
    add_weak_mods(MOD_BIT(kc));
    send_keyboard_report();
}

static inline void qk_unregister_mods(uint8_t kc) {
    del_weak_mods(MOD_BIT(kc));
    send_keyboard_report();
}

void register_code16 (uint16_t code) {
  if (IS_MOD(code) || code == KC_NO) {
      do_code16 (code, qk_register_mods);
  } else {
      do_code16 (code, qk_register_weak_mods);
  }
  register_code (code);
}

void unregister_code16 (uint16_t code) {
  unregister_code (code);
  if (IS_MOD(code) || code == KC_NO) {
      do_code16 (code, qk_unregister_mods);
  } else {
      do_code16 (code, qk_unregister_weak_mods);
  }
}

__attribute__ ((weak))
bool process_action_kb(keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}

__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void reset_keyboard(void) {
  clear_keyboard();
#if defined(MIDI_ENABLE) && defined(MIDI_BASIC)
  process_midi_all_notes_off();
#endif  
#if defined(AUDIO_ENABLE)
  music_all_notes_off();
  uint16_t timer_start = timer_read();
  PLAY_SONG(goodbye_song);
  shutdown_user();
  while(timer_elapsed(timer_start) < 250) 
    wait_ms(1);
  stop_all_notes();
#else
  wait_ms(250);
#endif
// this is also done later in bootloader.c - not sure if it's neccesary here
#ifdef BOOTLOADER_CATERINA
  *(uint16_t *)0x0800 = 0x7777; // these two are a-star-specific
#endif
  bootloader_jump();
}

// Shift / paren setup

#ifndef LSPO_KEY
  #define LSPO_KEY KC_9
#endif
#ifndef RSPC_KEY
  #define RSPC_KEY KC_0
#endif

// Shift / Enter setup
#ifndef SFTENT_KEY
  #define SFTENT_KEY KC_ENT
#endif

static bool shift_interrupted[2] = {0, 0};
static uint16_t scs_timer[2] = {0, 0};

/* true if the last press of GRAVE_ESC was shifted (i.e. GUI or SHIFT were pressed), false otherwise.
 * Used to ensure that the correct keycode is released if the key is released.
 */
static bool grave_esc_was_shifted = false;

bool process_record_quantum(keyrecord_t *record) {

  /* This gets the keycode from the key pressed */
  keypos_t key = record->event.key;
  uint16_t keycode;

  #if !defined(NO_ACTION_LAYER) && defined(PREVENT_STUCK_MODIFIERS)
    /* TODO: Use store_or_get_action() or a similar function. */
    if (!disable_action_cache) {
      uint8_t layer;

      if (record->event.pressed) {
        layer = layer_switch_get_layer(key);
        update_source_layers_cache(key, layer);
      } else {
        layer = read_source_layers_cache(key);
      }
      keycode = keymap_key_to_keycode(layer, key);
    } else
  #endif
    keycode = keymap_key_to_keycode(layer_switch_get_layer(key), key);

    // This is how you use actions here
    // if (keycode == KC_LEAD) {
    //   action_t action;
    //   action.code = ACTION_DEFAULT_LAYER_SET(0);
    //   process_action(record, action);
    //   return false;
    // }

  if (!(
  #if defined(KEY_LOCK_ENABLE)
    // Must run first to be able to mask key_up events.
    process_key_lock(&keycode, record) &&
  #endif
    process_record_kb(keycode, record) &&
  #if defined(MIDI_ENABLE) && defined(MIDI_ADVANCED)
    process_midi(keycode, record) &&
  #endif
  #ifdef AUDIO_ENABLE
    process_audio(keycode, record) &&
  #endif
  #ifdef STENO_ENABLE
    process_steno(keycode, record) &&
  #endif
  #if defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_BASIC))
    process_music(keycode, record) &&
  #endif
  #ifdef TAP_DANCE_ENABLE
    process_tap_dance(keycode, record) &&
  #endif
  #ifndef DISABLE_LEADER
    process_leader(keycode, record) &&
  #endif
  #ifndef DISABLE_CHORDING
    process_chording(keycode, record) &&
  #endif
  #ifdef COMBO_ENABLE
    process_combo(keycode, record) &&
  #endif
  #ifdef UNICODE_ENABLE
    process_unicode(keycode, record) &&
  #endif
  #ifdef UCIS_ENABLE
    process_ucis(keycode, record) &&
  #endif
  #ifdef PRINTING_ENABLE
    process_printer(keycode, record) &&
  #endif
  #ifdef AUTO_SHIFT_ENABLE
    process_auto_shift(keycode, record) &&
  #endif
  #ifdef UNICODEMAP_ENABLE
    process_unicode_map(keycode, record) &&
  #endif
  #ifdef TERMINAL_ENABLE
    process_terminal(keycode, record) &&
  #endif
      true)) {
    return false;
  }

  // Shift / paren setup

  switch(keycode) {
    case RESET:
      if (record->event.pressed) {
        reset_keyboard();
      }
    return false;
    case DEBUG:
      if (record->event.pressed) {
          debug_enable = true;
          print("DEBUG: enabled.\n");
      }
    return false;
  #ifdef FAUXCLICKY_ENABLE
  case FC_TOG:
    if (record->event.pressed) {
      FAUXCLICKY_TOGGLE;
    }
    return false;
  case FC_ON:
    if (record->event.pressed) {
      FAUXCLICKY_ON;
    }
    return false;
  case FC_OFF:
    if (record->event.pressed) {
      FAUXCLICKY_OFF;
    }
    return false;
  #endif
  #ifdef RGBLIGHT_ENABLE
  case RGB_TOG:
    if (record->event.pressed) {
      rgblight_toggle();
    }
    return false;
  case RGB_MODE_FORWARD:
    if (record->event.pressed) {
      uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
      if(shifted) {
        rgblight_step_reverse();
      }
      else {
        rgblight_step();
      }
    }
    return false;
  case RGB_MODE_REVERSE:
    if (record->event.pressed) {
      uint8_t shifted = get_mods() & (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT));
      if(shifted) {
        rgblight_step();
      }
      else {
        rgblight_step_reverse();
      }
    }
    return false;
  case RGB_HUI:
    if (record->event.pressed) {
      rgblight_increase_hue();
    }
    return false;
  case RGB_HUD:
    if (record->event.pressed) {
      rgblight_decrease_hue();
    }
    return false;
  case RGB_SAI:
    if (record->event.pressed) {
      rgblight_increase_sat();
    }
    return false;
  case RGB_SAD:
    if (record->event.pressed) {
      rgblight_decrease_sat();
    }
    return false;
  case RGB_VAI:
    if (record->event.pressed) {
      rgblight_increase_val();
    }
    return false;
  case RGB_VAD:
    if (record->event.pressed) {
      rgblight_decrease_val();
    }
    return false;
  case RGB_MODE_PLAIN:
    if (record->event.pressed) {
      rgblight_mode(1);
    }
    return false;
  case RGB_MODE_BREATHE:
    if (record->event.pressed) {
      if ((2 <= rgblight_get_mode()) && (rgblight_get_mode() < 5)) {
        rgblight_step();
      } else {
        rgblight_mode(2);
      }
    }
    return false;
  case RGB_MODE_RAINBOW:
    if (record->event.pressed) {
      if ((6 <= rgblight_get_mode()) && (rgblight_get_mode() < 8)) {
        rgblight_step();
      } else {
        rgblight_mode(6);
      }
    }
    return false;
  case RGB_MODE_SWIRL:
    if (record->event.pressed) {
      if ((9 <= rgblight_get_mode()) && (rgblight_get_mode() < 14)) {
        rgblight_step();
      } else {
        rgblight_mode(9);
      }
    }
    return false;
  case RGB_MODE_SNAKE:
    if (record->event.pressed) {
      if ((15 <= rgblight_get_mode()) && (rgblight_get_mode() < 20)) {
        rgblight_step();
      } else {
        rgblight_mode(15);
      }
    }
    return false;
  case RGB_MODE_KNIGHT:
    if (record->event.pressed) {
      if ((21 <= rgblight_get_mode()) && (rgblight_get_mode() < 23)) {
        rgblight_step();
      } else {
        rgblight_mode(21);
      }
    }
    return false;
  case RGB_MODE_XMAS:
    if (record->event.pressed) {
      rgblight_mode(24);
    }
    return false;
  case RGB_MODE_GRADIENT:
    if (record->event.pressed) {
      if ((25 <= rgblight_get_mode()) && (rgblight_get_mode() < 34)) {
        rgblight_step();
      } else {
        rgblight_mode(25);
      }
    }
    return false;
  #endif
    #ifdef PROTOCOL_LUFA
    case OUT_AUTO:
      if (record->event.pressed) {
        set_output(OUTPUT_AUTO);
      }
      return false;
    case OUT_USB:
      if (record->event.pressed) {
        set_output(OUTPUT_USB);
      }
      return false;
    #ifdef BLUETOOTH_ENABLE
    case OUT_BT:
      if (record->event.pressed) {
        set_output(OUTPUT_BLUETOOTH);
      }
      return false;
    #endif
    #endif
    case MAGIC_SWAP_CONTROL_CAPSLOCK ... MAGIC_TOGGLE_NKRO:
      if (record->event.pressed) {
        // MAGIC actions (BOOTMAGIC without the boot)
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        /* keymap config */
        keymap_config.raw = eeconfig_read_keymap();
        switch (keycode)
        {
          case MAGIC_SWAP_CONTROL_CAPSLOCK:
            keymap_config.swap_control_capslock = true;
            break;
          case MAGIC_CAPSLOCK_TO_CONTROL:
            keymap_config.capslock_to_control = true;
            break;
          case MAGIC_SWAP_LALT_LGUI:
            keymap_config.swap_lalt_lgui = true;
            break;
          case MAGIC_SWAP_RALT_RGUI:
            keymap_config.swap_ralt_rgui = true;
            break;
          case MAGIC_NO_GUI:
            keymap_config.no_gui = true;
            break;
          case MAGIC_SWAP_GRAVE_ESC:
            keymap_config.swap_grave_esc = true;
            break;
          case MAGIC_SWAP_BACKSLASH_BACKSPACE:
            keymap_config.swap_backslash_backspace = true;
            break;
          case MAGIC_HOST_NKRO:
            keymap_config.nkro = true;
            break;
          case MAGIC_SWAP_ALT_GUI:
            keymap_config.swap_lalt_lgui = true;
            keymap_config.swap_ralt_rgui = true;
            #ifdef AUDIO_ENABLE
              PLAY_SONG(ag_swap_song);
            #endif
            break;
          case MAGIC_UNSWAP_CONTROL_CAPSLOCK:
            keymap_config.swap_control_capslock = false;
            break;
          case MAGIC_UNCAPSLOCK_TO_CONTROL:
            keymap_config.capslock_to_control = false;
            break;
          case MAGIC_UNSWAP_LALT_LGUI:
            keymap_config.swap_lalt_lgui = false;
            break;
          case MAGIC_UNSWAP_RALT_RGUI:
            keymap_config.swap_ralt_rgui = false;
            break;
          case MAGIC_UNNO_GUI:
            keymap_config.no_gui = false;
            break;
          case MAGIC_UNSWAP_GRAVE_ESC:
            keymap_config.swap_grave_esc = false;
            break;
          case MAGIC_UNSWAP_BACKSLASH_BACKSPACE:
            keymap_config.swap_backslash_backspace = false;
            break;
          case MAGIC_UNHOST_NKRO:
            keymap_config.nkro = false;
            break;
          case MAGIC_UNSWAP_ALT_GUI:
            keymap_config.swap_lalt_lgui = false;
            keymap_config.swap_ralt_rgui = false;
            #ifdef AUDIO_ENABLE
              PLAY_SONG(ag_norm_song);
            #endif
            break;
          case MAGIC_TOGGLE_NKRO:
            keymap_config.nkro = !keymap_config.nkro;
            break;
          default:
            break;
        }
        eeconfig_update_keymap(keymap_config.raw);
        clear_keyboard(); // clear to prevent stuck keys

        return false;
      }
      break;
    case KC_LSPO: {
      if (record->event.pressed) {
        shift_interrupted[0] = false;
        scs_timer[0] = timer_read ();
        register_mods(MOD_BIT(KC_LSFT));
      }
      else {
        #ifdef DISABLE_SPACE_CADET_ROLLOVER
          if (get_mods() & MOD_BIT(KC_RSFT)) {
            shift_interrupted[0] = true;
            shift_interrupted[1] = true;
          }
        #endif
        if (!shift_interrupted[0] && timer_elapsed(scs_timer[0]) < TAPPING_TERM) {
          register_code(LSPO_KEY);
          unregister_code(LSPO_KEY);
        }
        unregister_mods(MOD_BIT(KC_LSFT));
      }
      return false;
    }

    case KC_RSPC: {
      if (record->event.pressed) {
        shift_interrupted[1] = false;
        scs_timer[1] = timer_read ();
        register_mods(MOD_BIT(KC_RSFT));
      }
      else {
        #ifdef DISABLE_SPACE_CADET_ROLLOVER
          if (get_mods() & MOD_BIT(KC_LSFT)) {
            shift_interrupted[0] = true;
            shift_interrupted[1] = true;
          }
        #endif
        if (!shift_interrupted[1] && timer_elapsed(scs_timer[1]) < TAPPING_TERM) {
          register_code(RSPC_KEY);
          unregister_code(RSPC_KEY);
        }
        unregister_mods(MOD_BIT(KC_RSFT));
      }
      return false;
    }

    case KC_SFTENT: {
      if (record->event.pressed) {
        shift_interrupted[1] = false;
        scs_timer[1] = timer_read ();
        register_mods(MOD_BIT(KC_RSFT));
      }
      else if (!shift_interrupted[1] && timer_elapsed(scs_timer[1]) < TAPPING_TERM) {
        unregister_mods(MOD_BIT(KC_RSFT));
        register_code(SFTENT_KEY);
        unregister_code(SFTENT_KEY);
      }
      else {
        unregister_mods(MOD_BIT(KC_RSFT));
      }
      return false;
    }

    case GRAVE_ESC: {
      uint8_t shifted = get_mods() & ((MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT)
                                      |MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)));

#ifdef GRAVE_ESC_ALT_OVERRIDE
      // if ALT is pressed, ESC is always sent
      // this is handy for the cmd+opt+esc shortcut on macOS, among other things.
      if (get_mods() & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) {
        shifted = 0;
      }
#endif

#ifdef GRAVE_ESC_CTRL_OVERRIDE
      // if CTRL is pressed, ESC is always sent
      // this is handy for the ctrl+shift+esc shortcut on windows, among other things.
      if (get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))) {
        shifted = 0;
      }
#endif

#ifdef GRAVE_ESC_GUI_OVERRIDE
      // if GUI is pressed, ESC is always sent
      if (get_mods() & (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))) {
        shifted = 0;
      }
#endif

#ifdef GRAVE_ESC_SHIFT_OVERRIDE
      // if SHIFT is pressed, ESC is always sent
      if (get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) {
        shifted = 0;
      }
#endif

      if (record->event.pressed) {
        grave_esc_was_shifted = shifted;
        add_key(shifted ? KC_GRAVE : KC_ESCAPE);
      }
      else {
        del_key(grave_esc_was_shifted ? KC_GRAVE : KC_ESCAPE);
      }

      send_keyboard_report();
      return false;
    }

#if defined(BACKLIGHT_ENABLE) && defined(BACKLIGHT_BREATHING)
    case BL_BRTG: {
      if (record->event.pressed)
        breathing_toggle();
      return false;
    }
#endif

    default: {
      shift_interrupted[0] = true;
      shift_interrupted[1] = true;
      break;
    }
  }

  return process_action_kb(record);
}

__attribute__ ((weak))
const bool ascii_to_shift_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 1, 0, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 0
};

__attribute__ ((weak))
const uint8_t ascii_to_keycode_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    KC_BSPC, KC_TAB, KC_ENT, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, KC_ESC, 0, 0, 0, 0,
    KC_SPC, KC_1, KC_QUOT, KC_3, KC_4, KC_5, KC_7, KC_QUOT,
    KC_9, KC_0, KC_8, KC_EQL, KC_COMM, KC_MINS, KC_DOT, KC_SLSH,
    KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
    KC_8, KC_9, KC_SCLN, KC_SCLN, KC_COMM, KC_EQL, KC_DOT, KC_SLSH,
    KC_2, KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,
    KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O,
    KC_P, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_V, KC_W,
    KC_X, KC_Y, KC_Z, KC_LBRC, KC_BSLS, KC_RBRC, KC_6, KC_MINS,
    KC_GRV, KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G,
    KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O,
    KC_P, KC_Q, KC_R, KC_S, KC_T, KC_U, KC_V, KC_W,
    KC_X, KC_Y, KC_Z, KC_LBRC, KC_BSLS, KC_RBRC, KC_GRV, KC_DEL
};

void send_string(const char *str) {
  send_string_with_delay(str, 0);
}

void send_string_P(const char *str) {
  send_string_with_delay_P(str, 0);
}

void send_string_with_delay(const char *str, uint8_t interval) {
    while (1) {
        char ascii_code = *str;
        if (!ascii_code) break;
        if (ascii_code == 1) {
          // tap
          uint8_t keycode = *(++str);
          register_code(keycode);
          unregister_code(keycode);
        } else if (ascii_code == 2) {
          // down
          uint8_t keycode = *(++str);
          register_code(keycode);
        } else if (ascii_code == 3) {
          // up
          uint8_t keycode = *(++str);
          unregister_code(keycode);
        } else {
          send_char(ascii_code);
        }
        ++str;
        // interval
        { uint8_t ms = interval; while (ms--) wait_ms(1); }
    }
}

void send_string_with_delay_P(const char *str, uint8_t interval) {
    while (1) {
        char ascii_code = pgm_read_byte(str);
        if (!ascii_code) break;
        if (ascii_code == 1) {
          // tap
          uint8_t keycode = pgm_read_byte(++str);
          register_code(keycode);
          unregister_code(keycode);
        } else if (ascii_code == 2) {
          // down
          uint8_t keycode = pgm_read_byte(++str);
          register_code(keycode);
        } else if (ascii_code == 3) {
          // up
          uint8_t keycode = pgm_read_byte(++str);
          unregister_code(keycode);
        } else {
          send_char(ascii_code);
        }
        ++str;
        // interval
        { uint8_t ms = interval; while (ms--) wait_ms(1); }
    }
}

void send_char(char ascii_code) {
  uint8_t keycode;
  keycode = pgm_read_byte(&ascii_to_keycode_lut[(uint8_t)ascii_code]);
  if (pgm_read_byte(&ascii_to_shift_lut[(uint8_t)ascii_code])) {
      register_code(KC_LSFT);
      register_code(keycode);
      unregister_code(keycode);
      unregister_code(KC_LSFT);
  } else {
      register_code(keycode);
      unregister_code(keycode);
  }
}

void set_single_persistent_default_layer(uint8_t default_layer) {
  #if defined(AUDIO_ENABLE) && defined(DEFAULT_LAYER_SONGS)
    PLAY_SONG(default_layer_songs[default_layer]);
  #endif
  eeconfig_update_default_layer(1U<<default_layer);
  default_layer_set(1U<<default_layer);
}

void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void tap_random_base64(void) {
  #if defined(__AVR_ATmega32U4__)
    uint8_t key = (TCNT0 + TCNT1 + TCNT3 + TCNT4) % 64;
  #else
    uint8_t key = rand() % 64;
  #endif
  switch (key) {
    case 0 ... 25:
      register_code(KC_LSFT);
      register_code(key + KC_A);
      unregister_code(key + KC_A);
      unregister_code(KC_LSFT);
      break;
    case 26 ... 51:
      register_code(key - 26 + KC_A);
      unregister_code(key - 26 + KC_A);
      break;
    case 52:
      register_code(KC_0);
      unregister_code(KC_0);
      break;
    case 53 ... 61:
      register_code(key - 53 + KC_1);
      unregister_code(key - 53 + KC_1);
      break;
    case 62:
      register_code(KC_LSFT);
      register_code(KC_EQL);
      unregister_code(KC_EQL);
      unregister_code(KC_LSFT);
      break;
    case 63:
      register_code(KC_SLSH);
      unregister_code(KC_SLSH);
      break;
  }
}

void matrix_init_quantum() {
  #ifdef BACKLIGHT_ENABLE
    backlight_init_ports();
  #endif
  #ifdef AUDIO_ENABLE
    audio_init();
  #endif
  matrix_init_kb();
}

void matrix_scan_quantum() {
  #ifdef AUDIO_ENABLE
    matrix_scan_music();
  #endif

  #ifdef TAP_DANCE_ENABLE
    matrix_scan_tap_dance();
  #endif

  #ifdef COMBO_ENABLE
    matrix_scan_combo();
  #endif

  #if defined(BACKLIGHT_ENABLE) && defined(BACKLIGHT_PIN)
    backlight_task();
  #endif

  matrix_scan_kb();
}

#if defined(BACKLIGHT_ENABLE) && defined(BACKLIGHT_PIN)

static const uint8_t backlight_pin = BACKLIGHT_PIN;

// depending on the pin, we use a different output compare unit
#if BACKLIGHT_PIN == B7
#  define COM1x1 COM1C1
#  define OCR1x  OCR1C
#elif BACKLIGHT_PIN == B6
#  define COM1x1 COM1B1
#  define OCR1x  OCR1B
#elif BACKLIGHT_PIN == B5
#  define COM1x1 COM1A1
#  define OCR1x  OCR1A
#else
#  define NO_HARDWARE_PWM
#endif

#ifndef BACKLIGHT_ON_STATE
#define BACKLIGHT_ON_STATE 0
#endif

#ifdef NO_HARDWARE_PWM // pwm through software

__attribute__ ((weak))
void backlight_init_ports(void)
{
  // Setup backlight pin as output and output to on state.
  // DDRx |= n
  _SFR_IO8((backlight_pin >> 4) + 1) |= _BV(backlight_pin & 0xF);
  #if BACKLIGHT_ON_STATE == 0
    // PORTx &= ~n
    _SFR_IO8((backlight_pin >> 4) + 2) &= ~_BV(backlight_pin & 0xF);
  #else
    // PORTx |= n
    _SFR_IO8((backlight_pin >> 4) + 2) |= _BV(backlight_pin & 0xF);
  #endif
}

__attribute__ ((weak))
void backlight_set(uint8_t level) {}

uint8_t backlight_tick = 0;

void backlight_task(void) {
  if ((0xFFFF >> ((BACKLIGHT_LEVELS - get_backlight_level()) * ((BACKLIGHT_LEVELS + 1) / 2))) & (1 << backlight_tick)) {
    #if BACKLIGHT_ON_STATE == 0
      // PORTx &= ~n
      _SFR_IO8((backlight_pin >> 4) + 2) &= ~_BV(backlight_pin & 0xF);
    #else
      // PORTx |= n
      _SFR_IO8((backlight_pin >> 4) + 2) |= _BV(backlight_pin & 0xF);
    #endif
  } else {
    #if BACKLIGHT_ON_STATE == 0
      // PORTx |= n
      _SFR_IO8((backlight_pin >> 4) + 2) |= _BV(backlight_pin & 0xF);
    #else
      // PORTx &= ~n
      _SFR_IO8((backlight_pin >> 4) + 2) &= ~_BV(backlight_pin & 0xF);
    #endif
  }
  backlight_tick = backlight_tick + 1 % 16;
}

#ifdef BACKLIGHT_BREATHING
#error "Backlight breathing only available with hardware PWM. Please disable."
#endif

#else // pwm through timer

#define TIMER_TOP 0xFFFFU

// See http://jared.geek.nz/2013/feb/linear-led-pwm
static uint16_t cie_lightness(uint16_t v) {
  if (v <= 5243) // if below 8% of max
    return v / 9; // same as dividing by 900%
  else {
    uint32_t y = (((uint32_t) v + 10486) << 8) / (10486 + 0xFFFFUL); // add 16% of max and compare
    // to get a useful result with integer division, we shift left in the expression above
    // and revert what we've done again after squaring.
    y = y * y * y >> 8;
    if (y > 0xFFFFUL) // prevent overflow
      return 0xFFFFU;
    else
      return (uint16_t) y;
  }
}

// range for val is [0..TIMER_TOP]. PWM pin is high while the timer count is below val.
static inline void set_pwm(uint16_t val) {
  OCR1x = val;
}

__attribute__ ((weak))
void backlight_set(uint8_t level) {
  if (level > BACKLIGHT_LEVELS)
    level = BACKLIGHT_LEVELS;

  if (level == 0) {
    // Turn off PWM control on backlight pin
    TCCR1A &= ~(_BV(COM1x1));
  } else {
    // Turn on PWM control of backlight pin
    TCCR1A |= _BV(COM1x1);
  }
  // Set the brightness
  set_pwm(cie_lightness(TIMER_TOP * (uint32_t)level / BACKLIGHT_LEVELS));
}

void backlight_task(void) {}

#ifdef BACKLIGHT_BREATHING

#define BREATHING_NO_HALT  0
#define BREATHING_HALT_OFF 1
#define BREATHING_HALT_ON  2
#define BREATHING_STEPS 128

static uint8_t breathing_period = BREATHING_PERIOD;
static uint8_t breathing_halt = BREATHING_NO_HALT;
static uint16_t breathing_counter = 0;

bool is_breathing(void) {
    return !!(TIMSK1 & _BV(TOIE1));
}

#define breathing_interrupt_enable() do {TIMSK1 |= _BV(TOIE1);} while (0)
#define breathing_interrupt_disable() do {TIMSK1 &= ~_BV(TOIE1);} while (0)
#define breathing_min() do {breathing_counter = 0;} while (0)
#define breathing_max() do {breathing_counter = breathing_period * 244 / 2;} while (0)

void breathing_enable(void)
{
  breathing_counter = 0;
  breathing_halt = BREATHING_NO_HALT;
  breathing_interrupt_enable();
}

void breathing_pulse(void)
{
    if (get_backlight_level() == 0)
      breathing_min();
    else
      breathing_max();
    breathing_halt = BREATHING_HALT_ON;
    breathing_interrupt_enable();
}

void breathing_disable(void)
{
    breathing_interrupt_disable();
    // Restore backlight level
    backlight_set(get_backlight_level());
}

void breathing_self_disable(void)
{
  if (get_backlight_level() == 0)
    breathing_halt = BREATHING_HALT_OFF;
  else
    breathing_halt = BREATHING_HALT_ON;
}

void breathing_toggle(void) {
  if (is_breathing())
    breathing_disable();
  else
    breathing_enable();
}

void breathing_period_set(uint8_t value)
{
  if (!value)
    value = 1;
  breathing_period = value;
}

void breathing_period_default(void) {
  breathing_period_set(BREATHING_PERIOD);
}

void breathing_period_inc(void)
{
  breathing_period_set(breathing_period+1);
}

void breathing_period_dec(void)
{
  breathing_period_set(breathing_period-1);
}

/* To generate breathing curve in python:
 * from math import sin, pi; [int(sin(x/128.0*pi)**4*255) for x in range(128)]
 */
static const uint8_t breathing_table[BREATHING_STEPS] PROGMEM = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 17, 20, 24, 28, 32, 36, 41, 46, 51, 57, 63, 70, 76, 83, 91, 98, 106, 113, 121, 129, 138, 146, 154, 162, 170, 178, 185, 193, 200, 207, 213, 220, 225, 231, 235, 240, 244, 247, 250, 252, 253, 254, 255, 254, 253, 252, 250, 247, 244, 240, 235, 231, 225, 220, 213, 207, 200, 193, 185, 178, 170, 162, 154, 146, 138, 129, 121, 113, 106, 98, 91, 83, 76, 70, 63, 57, 51, 46, 41, 36, 32, 28, 24, 20, 17, 15, 12, 10, 8, 6, 5, 4, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Use this before the cie_lightness function.
static inline uint16_t scale_backlight(uint16_t v) {
  return v / BACKLIGHT_LEVELS * get_backlight_level();
}

/* Assuming a 16MHz CPU clock and a timer that resets at 64k (ICR1), the following interrupt handler will run
 * about 244 times per second.
 */
ISR(TIMER1_OVF_vect)
{
  uint16_t interval = (uint16_t) breathing_period * 244 / BREATHING_STEPS;
  // resetting after one period to prevent ugly reset at overflow.
  breathing_counter = (breathing_counter + 1) % (breathing_period * 244);
  uint8_t index = breathing_counter / interval % BREATHING_STEPS;

  if (((breathing_halt == BREATHING_HALT_ON) && (index == BREATHING_STEPS / 2)) ||
      ((breathing_halt == BREATHING_HALT_OFF) && (index == BREATHING_STEPS - 1)))
  {
      breathing_interrupt_disable();
  }

  set_pwm(cie_lightness(scale_backlight((uint16_t) pgm_read_byte(&breathing_table[index]) * 0x0101U)));
}

#endif // BACKLIGHT_BREATHING

__attribute__ ((weak))
void backlight_init_ports(void)
{
  // Setup backlight pin as output and output to on state.
  // DDRx |= n
  _SFR_IO8((backlight_pin >> 4) + 1) |= _BV(backlight_pin & 0xF);
  #if BACKLIGHT_ON_STATE == 0
    // PORTx &= ~n
    _SFR_IO8((backlight_pin >> 4) + 2) &= ~_BV(backlight_pin & 0xF);
  #else
    // PORTx |= n
    _SFR_IO8((backlight_pin >> 4) + 2) |= _BV(backlight_pin & 0xF);
  #endif
  // I could write a wall of text here to explain... but TL;DW
  // Go read the ATmega32u4 datasheet.
  // And this: http://blog.saikoled.com/post/43165849837/secret-konami-cheat-code-to-high-resolution-pwm-on

  // Pin PB7 = OCR1C (Timer 1, Channel C)
  // Compare Output Mode = Clear on compare match, Channel C = COM1C1=1 COM1C0=0
  // (i.e. start high, go low when counter matches.)
  // WGM Mode 14 (Fast PWM) = WGM13=1 WGM12=1 WGM11=1 WGM10=0
  // Clock Select = clk/1 (no prescaling) = CS12=0 CS11=0 CS10=1

  /*
  14.8.3:
  "In fast PWM mode, the compare units allow generation of PWM waveforms on the OCnx pins. Setting the COMnx1:0 bits to two will produce a non-inverted PWM [..]."
  "In fast PWM mode the counter is incremented until the counter value matches either one of the fixed values 0x00FF, 0x01FF, or 0x03FF (WGMn3:0 = 5, 6, or 7), the value in ICRn (WGMn3:0 = 14), or the value in OCRnA (WGMn3:0 = 15)."
  */

  TCCR1A = _BV(COM1x1) | _BV(WGM11); // = 0b00001010;
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // = 0b00011001;
  // Use full 16-bit resolution. Counter counts to ICR1 before reset to 0.
  ICR1 = TIMER_TOP;

  backlight_init();
  #ifdef BACKLIGHT_BREATHING
    breathing_enable();
  #endif
}

#endif // NO_HARDWARE_PWM

#else // backlight

__attribute__ ((weak))
void backlight_init_ports(void) {}

__attribute__ ((weak))
void backlight_set(uint8_t level) {}

#endif // backlight


// Functions for spitting out values
//

void send_dword(uint32_t number) { // this might not actually work
    uint16_t word = (number >> 16);
    send_word(word);
    send_word(number & 0xFFFFUL);
}

void send_word(uint16_t number) {
    uint8_t byte = number >> 8;
    send_byte(byte);
    send_byte(number & 0xFF);
}

void send_byte(uint8_t number) {
    uint8_t nibble = number >> 4;
    send_nibble(nibble);
    send_nibble(number & 0xF);
}

void send_nibble(uint8_t number) {
    switch (number) {
        case 0:
            register_code(KC_0);
            unregister_code(KC_0);
            break;
        case 1 ... 9:
            register_code(KC_1 + (number - 1));
            unregister_code(KC_1 + (number - 1));
            break;
        case 0xA ... 0xF:
            register_code(KC_A + (number - 0xA));
            unregister_code(KC_A + (number - 0xA));
            break;
    }
}


__attribute__((weak))
uint16_t hex_to_keycode(uint8_t hex)
{
  hex = hex & 0xF;
  if (hex == 0x0) {
    return KC_0;
  } else if (hex < 0xA) {
    return KC_1 + (hex - 0x1);
  } else {
    return KC_A + (hex - 0xA);
  }
}

void api_send_unicode(uint32_t unicode) {
#ifdef API_ENABLE
    uint8_t chunk[4];
    dword_to_bytes(unicode, chunk);
    MT_SEND_DATA(DT_UNICODE, chunk, 5);
#endif
}

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {

}

__attribute__ ((weak))
void led_set_kb(uint8_t usb_led) {
    led_set_user(usb_led);
}

__attribute__ ((weak))
void led_init_ports(void)
{

}

__attribute__ ((weak))
void led_set(uint8_t usb_led)
{

  // Example LED Code
  //
    // // Using PE6 Caps Lock LED
    // if (usb_led & (1<<USB_LED_CAPS_LOCK))
    // {
    //     // Output high.
    //     DDRE |= (1<<6);
    //     PORTE |= (1<<6);
    // }
    // else
    // {
    //     // Output low.
    //     DDRE &= ~(1<<6);
    //     PORTE &= ~(1<<6);
    // }

  led_set_kb(usb_led);
}


//------------------------------------------------------------------------------
// Override these functions in your keymap file to play different tunes on
// different events such as startup and bootloader jump

__attribute__ ((weak))
void startup_user() {}

__attribute__ ((weak))
void shutdown_user() {}

//------------------------------------------------------------------------------
