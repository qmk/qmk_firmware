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

#include "backlight.h"
extern backlight_config_t backlight_config;

#ifdef FAUXCLICKY_ENABLE
#include "fauxclicky.h"
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
#if defined(AUDIO_ENABLE) || (defined(MIDI_ENABLE) && defined(MIDI_ENABLE_BASIC))
  music_all_notes_off();
  shutdown_user();
#endif
  wait_ms(250);
#ifdef CATERINA_BOOTLOADER
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

static bool shift_interrupted[2] = {0, 0};
static uint16_t scs_timer = 0;

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
    process_record_kb(keycode, record) &&
  #if defined(MIDI_ENABLE) && defined(MIDI_ADVANCED)
    process_midi(keycode, record) &&
  #endif
  #ifdef AUDIO_ENABLE
    process_audio(keycode, record) &&
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
  #ifdef UNICODEMAP_ENABLE
    process_unicode_map(keycode, record) &&
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
      break;
    case DEBUG:
      if (record->event.pressed) {
          print("\nDEBUG: enabled.\n");
          debug_enable = true;
      }
	  return false;
      break;
  #ifdef FAUXCLICKY_ENABLE
  case FC_TOG:
    if (record->event.pressed) {
      FAUXCLICKY_TOGGLE;
    }
    return false;
    break;
  case FC_ON:
    if (record->event.pressed) {
      FAUXCLICKY_ON;
    }
    return false;
    break;
  case FC_OFF:
    if (record->event.pressed) {
      FAUXCLICKY_OFF;
    }
    return false;
    break;
  #endif
	#ifdef RGBLIGHT_ENABLE
	case RGB_TOG:
		if (record->event.pressed) {
			rgblight_toggle();
      }
	  return false;
      break;
	case RGB_MOD:
		if (record->event.pressed) {
			rgblight_step();
      }
	  return false;
      break;
	case RGB_HUI:
		if (record->event.pressed) {
			rgblight_increase_hue();
      }
	  return false;
      break;
	case RGB_HUD:
		if (record->event.pressed) {
			rgblight_decrease_hue();
      }
	  return false;
      break;
	case RGB_SAI:
		if (record->event.pressed) {
			rgblight_increase_sat();
      }
	  return false;
      break;
	case RGB_SAD:
		if (record->event.pressed) {
			rgblight_decrease_sat();
      }
	  return false;
      break;
	case RGB_VAI:
		if (record->event.pressed) {
			rgblight_increase_val();
      }
	  return false;
      break;
	case RGB_VAD:
		if (record->event.pressed) {
			rgblight_decrease_val();
      }
	  return false;
      break;
	#endif
    #ifdef PROTOCOL_LUFA
    case OUT_AUTO:
      if (record->event.pressed) {
        set_output(OUTPUT_AUTO);
      }
      return false;
      break;
    case OUT_USB:
      if (record->event.pressed) {
        set_output(OUTPUT_USB);
      }
      return false;
      break;
    #ifdef BLUETOOTH_ENABLE
    case OUT_BT:
      if (record->event.pressed) {
        set_output(OUTPUT_BLUETOOTH);
      }
      return false;
      break;
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
        scs_timer = timer_read ();
        register_mods(MOD_BIT(KC_LSFT));
      }
      else {
        #ifdef DISABLE_SPACE_CADET_ROLLOVER
          if (get_mods() & MOD_BIT(KC_RSFT)) {
            shift_interrupted[0] = true;
            shift_interrupted[1] = true;
          }
        #endif
        if (!shift_interrupted[0] && timer_elapsed(scs_timer) < TAPPING_TERM) {
          register_code(LSPO_KEY);
          unregister_code(LSPO_KEY);
        }
        unregister_mods(MOD_BIT(KC_LSFT));
      }
      return false;
      // break;
    }

    case KC_RSPC: {
      if (record->event.pressed) {
        shift_interrupted[1] = false;
        scs_timer = timer_read ();
        register_mods(MOD_BIT(KC_RSFT));
      }
      else {
        #ifdef DISABLE_SPACE_CADET_ROLLOVER
          if (get_mods() & MOD_BIT(KC_LSFT)) {
            shift_interrupted[0] = true;
            shift_interrupted[1] = true;
          }
        #endif
        if (!shift_interrupted[1] && timer_elapsed(scs_timer) < TAPPING_TERM) {
          register_code(RSPC_KEY);
          unregister_code(RSPC_KEY);
        }
        unregister_mods(MOD_BIT(KC_RSFT));
      }
      return false;
      // break;
    }
    default: {
      shift_interrupted[0] = true;
      shift_interrupted[1] = true;
      break;
    }
  }

  return process_action_kb(record);
}

const bool ascii_to_qwerty_shift_lut[0x80] PROGMEM = {
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

const uint8_t ascii_to_qwerty_keycode_lut[0x80] PROGMEM = {
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

/* for users whose OSes are set to Colemak */
#if 0
#include "keymap_colemak.h"

const bool ascii_to_colemak_shift_lut[0x80] PROGMEM = {
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

const uint8_t ascii_to_colemak_keycode_lut[0x80] PROGMEM = {
    0, 0, 0, 0, 0, 0, 0, 0,
    KC_BSPC, KC_TAB, KC_ENT, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, KC_ESC, 0, 0, 0, 0,
    KC_SPC, KC_1, KC_QUOT, KC_3, KC_4, KC_5, KC_7, KC_QUOT,
    KC_9, KC_0, KC_8, KC_EQL, KC_COMM, KC_MINS, KC_DOT, KC_SLSH,
    KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
    KC_8, KC_9, CM_SCLN, CM_SCLN, KC_COMM, KC_EQL, KC_DOT, KC_SLSH,
    KC_2, CM_A, CM_B, CM_C, CM_D, CM_E, CM_F, CM_G,
    CM_H, CM_I, CM_J, CM_K, CM_L, CM_M, CM_N, CM_O,
    CM_P, CM_Q, CM_R, CM_S, CM_T, CM_U, CM_V, CM_W,
    CM_X, CM_Y, CM_Z, KC_LBRC, KC_BSLS, KC_RBRC, KC_6, KC_MINS,
    KC_GRV, CM_A, CM_B, CM_C, CM_D, CM_E, CM_F, CM_G,
    CM_H, CM_I, CM_J, CM_K, CM_L, CM_M, CM_N, CM_O,
    CM_P, CM_Q, CM_R, CM_S, CM_T, CM_U, CM_V, CM_W,
    CM_X, CM_Y, CM_Z, KC_LBRC, KC_BSLS, KC_RBRC, KC_GRV, KC_DEL
};

#endif

void send_string(const char *str) {
    while (1) {
        uint8_t keycode;
        uint8_t ascii_code = pgm_read_byte(str);
        if (!ascii_code) break;
        keycode = pgm_read_byte(&ascii_to_qwerty_keycode_lut[ascii_code]);
        if (pgm_read_byte(&ascii_to_qwerty_shift_lut[ascii_code])) {
            register_code(KC_LSFT);
            register_code(keycode);
            unregister_code(keycode);
            unregister_code(KC_LSFT);
        }
        else {
            register_code(keycode);
            unregister_code(keycode);
        }
        ++str;
    }
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
#  define NO_BACKLIGHT_CLOCK
#endif

#ifndef BACKLIGHT_ON_STATE
#define BACKLIGHT_ON_STATE 0
#endif

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

  #ifndef NO_BACKLIGHT_CLOCK
    // Use full 16-bit resolution.
    ICR1 = 0xFFFF;

    // I could write a wall of text here to explain... but TL;DW
    // Go read the ATmega32u4 datasheet.
    // And this: http://blog.saikoled.com/post/43165849837/secret-konami-cheat-code-to-high-resolution-pwm-on

    // Pin PB7 = OCR1C (Timer 1, Channel C)
    // Compare Output Mode = Clear on compare match, Channel C = COM1C1=1 COM1C0=0
    // (i.e. start high, go low when counter matches.)
    // WGM Mode 14 (Fast PWM) = WGM13=1 WGM12=1 WGM11=1 WGM10=0
    // Clock Select = clk/1 (no prescaling) = CS12=0 CS11=0 CS10=1

    TCCR1A = _BV(COM1x1) | _BV(WGM11); // = 0b00001010;
    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // = 0b00011001;
  #endif

  backlight_init();
  #ifdef BACKLIGHT_BREATHING
    breathing_defaults();
  #endif
}

__attribute__ ((weak))
void backlight_set(uint8_t level)
{
  // Prevent backlight blink on lowest level
  // #if BACKLIGHT_ON_STATE == 0
  //   // PORTx &= ~n
  //   _SFR_IO8((backlight_pin >> 4) + 2) &= ~_BV(backlight_pin & 0xF);
  // #else
  //   // PORTx |= n
  //   _SFR_IO8((backlight_pin >> 4) + 2) |= _BV(backlight_pin & 0xF);
  // #endif

  if ( level == 0 ) {
    #ifndef NO_BACKLIGHT_CLOCK
      // Turn off PWM control on backlight pin, revert to output low.
      TCCR1A &= ~(_BV(COM1x1));
      OCR1x = 0x0;
    #else
      // #if BACKLIGHT_ON_STATE == 0
      //   // PORTx |= n
      //   _SFR_IO8((backlight_pin >> 4) + 2) |= _BV(backlight_pin & 0xF);
      // #else
      //   // PORTx &= ~n
      //   _SFR_IO8((backlight_pin >> 4) + 2) &= ~_BV(backlight_pin & 0xF);
      // #endif
    #endif
  } 
  #ifndef NO_BACKLIGHT_CLOCK
    else if ( level == BACKLIGHT_LEVELS ) {
      // Turn on PWM control of backlight pin
      TCCR1A |= _BV(COM1x1);
      // Set the brightness
      OCR1x = 0xFFFF;
    } 
    else {
      // Turn on PWM control of backlight pin
      TCCR1A |= _BV(COM1x1);
      // Set the brightness
      OCR1x = 0xFFFF >> ((BACKLIGHT_LEVELS - level) * ((BACKLIGHT_LEVELS + 1) / 2));
    }
  #endif

  #ifdef BACKLIGHT_BREATHING
    breathing_intensity_default();
  #endif
}

uint8_t backlight_tick = 0;

void backlight_task(void) {
  #ifdef NO_BACKLIGHT_CLOCK
  if ((0xFFFF >> ((BACKLIGHT_LEVELS - backlight_config.level) * ((BACKLIGHT_LEVELS + 1) / 2))) & (1 << backlight_tick)) { 
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
  backlight_tick = (backlight_tick + 1) % 16;
  #endif
}

#ifdef BACKLIGHT_BREATHING

#define BREATHING_NO_HALT  0
#define BREATHING_HALT_OFF 1
#define BREATHING_HALT_ON  2

static uint8_t breath_intensity;
static uint8_t breath_speed;
static uint16_t breathing_index;
static uint8_t breathing_halt;

void breathing_enable(void)
{
    if (get_backlight_level() == 0)
    {
        breathing_index = 0;
    }
    else
    {
        // Set breathing_index to be at the midpoint (brightest point)
        breathing_index = 0x20 << breath_speed;
    }

    breathing_halt = BREATHING_NO_HALT;

    // Enable breathing interrupt
    TIMSK1 |= _BV(OCIE1A);
}

void breathing_pulse(void)
{
    if (get_backlight_level() == 0)
    {
        breathing_index = 0;
    }
    else
    {
        // Set breathing_index to be at the midpoint + 1 (brightest point)
        breathing_index = 0x21 << breath_speed;
    }

    breathing_halt = BREATHING_HALT_ON;

    // Enable breathing interrupt
    TIMSK1 |= _BV(OCIE1A);
}

void breathing_disable(void)
{
    // Disable breathing interrupt
    TIMSK1 &= ~_BV(OCIE1A);
    backlight_set(get_backlight_level());
}

void breathing_self_disable(void)
{
    if (get_backlight_level() == 0)
    {
        breathing_halt = BREATHING_HALT_OFF;
    }
    else
    {
        breathing_halt = BREATHING_HALT_ON;
    }

    //backlight_set(get_backlight_level());
}

void breathing_toggle(void)
{
    if (!is_breathing())
    {
        if (get_backlight_level() == 0)
        {
            breathing_index = 0;
        }
        else
        {
            // Set breathing_index to be at the midpoint + 1 (brightest point)
            breathing_index = 0x21 << breath_speed;
        }

        breathing_halt = BREATHING_NO_HALT;
    }

    // Toggle breathing interrupt
    TIMSK1 ^= _BV(OCIE1A);

    // Restore backlight level
    if (!is_breathing())
    {
        backlight_set(get_backlight_level());
    }
}

bool is_breathing(void)
{
    return (TIMSK1 && _BV(OCIE1A));
}

void breathing_intensity_default(void)
{
    //breath_intensity = (uint8_t)((uint16_t)100 * (uint16_t)get_backlight_level() / (uint16_t)BACKLIGHT_LEVELS);
    breath_intensity = ((BACKLIGHT_LEVELS - get_backlight_level()) * ((BACKLIGHT_LEVELS + 1) / 2));
}

void breathing_intensity_set(uint8_t value)
{
    breath_intensity = value;
}

void breathing_speed_default(void)
{
    breath_speed = 4;
}

void breathing_speed_set(uint8_t value)
{
    bool is_breathing_now = is_breathing();
    uint8_t old_breath_speed = breath_speed;

    if (is_breathing_now)
    {
        // Disable breathing interrupt
        TIMSK1 &= ~_BV(OCIE1A);
    }

    breath_speed = value;

    if (is_breathing_now)
    {
        // Adjust index to account for new speed
        breathing_index = (( (uint8_t)( (breathing_index) >> old_breath_speed ) ) & 0x3F) << breath_speed;

        // Enable breathing interrupt
        TIMSK1 |= _BV(OCIE1A);
    }

}

void breathing_speed_inc(uint8_t value)
{
    if ((uint16_t)(breath_speed - value) > 10 )
    {
        breathing_speed_set(0);
    }
    else
    {
        breathing_speed_set(breath_speed - value);
    }
}

void breathing_speed_dec(uint8_t value)
{
    if ((uint16_t)(breath_speed + value) > 10 )
    {
        breathing_speed_set(10);
    }
    else
    {
        breathing_speed_set(breath_speed + value);
    }
}

void breathing_defaults(void)
{
    breathing_intensity_default();
    breathing_speed_default();
    breathing_halt = BREATHING_NO_HALT;
}

/* Breathing Sleep LED brighness(PWM On period) table
 * (64[steps] * 4[duration]) / 64[PWM periods/s] = 4 second breath cycle
 *
 * http://www.wolframalpha.com/input/?i=%28sin%28+x%2F64*pi%29**8+*+255%2C+x%3D0+to+63
 * (0..63).each {|x| p ((sin(x/64.0*PI)**8)*255).to_i }
 */
static const uint8_t breathing_table[64] PROGMEM = {
  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   2,   4,   6,  10,
 15,  23,  32,  44,  58,  74,  93, 113, 135, 157, 179, 199, 218, 233, 245, 252,
255, 252, 245, 233, 218, 199, 179, 157, 135, 113,  93,  74,  58,  44,  32,  23,
 15,  10,   6,   4,   2,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
};

ISR(TIMER1_COMPA_vect)
{
    // OCR1x = (pgm_read_byte(&breathing_table[ ( (uint8_t)( (breathing_index++) >> breath_speed ) ) & 0x3F ] )) * breath_intensity;


    uint8_t local_index = ( (uint8_t)( (breathing_index++) >> breath_speed ) ) & 0x3F;

    if (((breathing_halt == BREATHING_HALT_ON) && (local_index == 0x20)) || ((breathing_halt == BREATHING_HALT_OFF) && (local_index == 0x3F)))
    {
        // Disable breathing interrupt
        TIMSK1 &= ~_BV(OCIE1A);
    }

    OCR1x = (uint16_t)(((uint16_t)pgm_read_byte(&breathing_table[local_index]) * 257)) >> breath_intensity;

}



#endif // breathing

#else // backlight

__attribute__ ((weak))
void backlight_init_ports(void)
{

}

__attribute__ ((weak))
void backlight_set(uint8_t level)
{

}

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
