#include "quantum.h"

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

__attribute__ ((weak))
void leader_start(void) {}

__attribute__ ((weak))
void leader_end(void) {}

uint8_t starting_note = 0x0C;
int offset = 7;


#ifdef AUDIO_ENABLE
  bool music_activated = false;

  // music sequencer
  static bool music_sequence_recording = false;
  static bool music_sequence_playing = false;
  static float music_sequence[16] = {0};
  static uint8_t music_sequence_count = 0;
  static uint8_t music_sequence_position = 0;

  static uint16_t music_sequence_timer = 0;
  static uint16_t music_sequence_interval = 100;

#endif

#ifdef MIDI_ENABLE
  bool midi_activated = false;
#endif

// Leader key stuff
bool leading = false;
uint16_t leader_time = 0;

uint16_t leader_sequence[5] = {0, 0, 0, 0, 0};
uint8_t leader_sequence_size = 0;

// Chording stuff
#define CHORDING_MAX 4
bool chording = false;

uint8_t chord_keys[CHORDING_MAX] = {0};
uint8_t chord_key_count = 0;
uint8_t chord_key_down = 0;

#ifdef UNICODE_ENABLE
  static uint8_t input_mode;
#endif

// Shift / paren setup

#ifndef LSPO_KEY
  #define LSPO_KEY KC_9
#endif
#ifndef RSPC_KEY
  #define RSPC_KEY KC_0
#endif

static bool shift_interrupted[2] = {0, 0};

bool keys_chord(uint8_t keys[]) {
  uint8_t keys_size = sizeof(keys)/sizeof(keys[0]);
  bool pass = true;
  uint8_t in = 0;
  for (uint8_t i = 0; i < chord_key_count; i++) {
    bool found = false;
    for (uint8_t j = 0; j < keys_size; j++) {
      if (chord_keys[i] == (keys[j] & 0xFF)) {
        in++; // detects key in chord
        found = true;
        break;
      }
    }
    if (found)
      continue;
    if (chord_keys[i] != 0)  {
      pass = false; // makes sure rest are blank
    }
  }
  return (pass && (in == keys_size));
}

#ifdef UNICODE_ENABLE

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

void set_unicode_mode(uint8_t os_target)
{
  input_mode = os_target;
}

#endif

bool process_record_quantum(keyrecord_t *record) {

  /* This gets the keycode from the key pressed */
  keypos_t key = record->event.key;
  uint16_t keycode;

  #if !defined(NO_ACTION_LAYER) && defined(PREVENT_STUCK_MODIFIERS)
    uint8_t layer;

    if (record->event.pressed) {
      layer = layer_switch_get_layer(key);
      update_source_layers_cache(key, layer);
    } else {
      layer = read_source_layers_cache(key);
    }
    keycode = keymap_key_to_keycode(layer, key);
  #else
    keycode = keymap_key_to_keycode(layer_switch_get_layer(key), key);
  #endif

  if (!process_record_kb(keycode, record))
    return false;

    // This is how you use actions here
    // if (keycode == KC_LEAD) {
    //   action_t action;
    //   action.code = ACTION_DEFAULT_LAYER_SET(0);
    //   process_action(record, action);
    //   return false;
    // }

  #ifdef MIDI_ENABLE
    if (keycode == MI_ON && record->event.pressed) {
      midi_activated = true;
      music_scale_user();
      return false;
    }

    if (keycode == MI_OFF && record->event.pressed) {
      midi_activated = false;
      midi_send_cc(&midi_device, 0, 0x7B, 0);
      return false;
    }

    if (midi_activated) {
      if (record->event.key.col == (MATRIX_COLS - 1) && record->event.key.row == (MATRIX_ROWS - 1)) {
          if (record->event.pressed) {
              starting_note++; // Change key
              midi_send_cc(&midi_device, 0, 0x7B, 0);
          }
          return false;
      }
      if (record->event.key.col == (MATRIX_COLS - 2) && record->event.key.row == (MATRIX_ROWS - 1)) {
          if (record->event.pressed) {
              starting_note--; // Change key
              midi_send_cc(&midi_device, 0, 0x7B, 0);
          }
          return false;
      }
      if (record->event.key.col == (MATRIX_COLS - 3) && record->event.key.row == (MATRIX_ROWS - 1) && record->event.pressed) {
          offset++; // Change scale
          midi_send_cc(&midi_device, 0, 0x7B, 0);
          return false;
      }
      if (record->event.key.col == (MATRIX_COLS - 4) && record->event.key.row == (MATRIX_ROWS - 1) && record->event.pressed) {
          offset--; // Change scale
          midi_send_cc(&midi_device, 0, 0x7B, 0);
          return false;
      }
      // basic
      // uint8_t note = (starting_note + SCALE[record->event.key.col + offset])+12*(MATRIX_ROWS - record->event.key.row);
      // advanced
      // uint8_t note = (starting_note + record->event.key.col + offset)+12*(MATRIX_ROWS - record->event.key.row);
      // guitar
      uint8_t note = (starting_note + record->event.key.col + offset)+5*(MATRIX_ROWS - record->event.key.row);
      // violin
      // uint8_t note = (starting_note + record->event.key.col + offset)+7*(MATRIX_ROWS - record->event.key.row);

      if (record->event.pressed) {
        // midi_send_noteon(&midi_device, record->event.key.row, starting_note + SCALE[record->event.key.col], 127);
        midi_send_noteon(&midi_device, 0, note, 127);
      } else {
        // midi_send_noteoff(&midi_device, record->event.key.row, starting_note + SCALE[record->event.key.col], 127);
        midi_send_noteoff(&midi_device, 0, note, 127);
      }

      if (keycode < 0xFF) // ignores all normal keycodes, but lets RAISE, LOWER, etc through
        return false;
    }
  #endif

  #ifdef AUDIO_ENABLE
    if (keycode == AU_ON && record->event.pressed) {
      audio_on();
      return false;
    }

    if (keycode == AU_OFF && record->event.pressed) {
      audio_off();
      return false;
    }

    if (keycode == AU_TOG && record->event.pressed) {
        if (is_audio_on())
        {
            audio_off();
        }
        else
        {
            audio_on();
        }
      return false;
    }

    if (keycode == MU_ON && record->event.pressed) {
        music_on();
        return false;
    }

    if (keycode == MU_OFF && record->event.pressed) {
        music_off();
        return false;
    }

    if (keycode == MU_TOG && record->event.pressed) {
        if (music_activated)
        {
            music_off();
        }
        else
        {
            music_on();
        }
        return false;
    }

    if (keycode == MUV_IN && record->event.pressed) {
        voice_iterate();
        music_scale_user();
        return false;
    }

    if (keycode == MUV_DE && record->event.pressed) {
        voice_deiterate();
        music_scale_user();
        return false;
    }

    if (music_activated) {

      if (keycode == KC_LCTL && record->event.pressed) { // Start recording
        stop_all_notes();
        music_sequence_recording = true;
        music_sequence_playing = false;
        music_sequence_count = 0;
        return false;
      }

      if (keycode == KC_LALT && record->event.pressed) { // Stop recording/playing
        stop_all_notes();
        music_sequence_recording = false;
        music_sequence_playing = false;
        return false;
      }

      if (keycode == KC_LGUI && record->event.pressed) { // Start playing
        stop_all_notes();
        music_sequence_recording = false;
        music_sequence_playing = true;
        music_sequence_position = 0;
        music_sequence_timer = 0;
        return false;
      }

      if (keycode == KC_UP) {
        if (record->event.pressed)
            music_sequence_interval-=10;
        return false;
      }

      if (keycode == KC_DOWN) {
        if (record->event.pressed)
            music_sequence_interval+=10;
        return false;
      }

      float freq = ((float)220.0)*pow(2.0, -5.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row));
      if (record->event.pressed) {
        play_note(freq, 0xF);
        if (music_sequence_recording) {
          music_sequence[music_sequence_count] = freq;
          music_sequence_count++;
        }
      } else {
        stop_note(freq);
      }

      if (keycode < 0xFF) // ignores all normal keycodes, but lets RAISE, LOWER, etc through
        return false;
    }
  #endif

#ifndef DISABLE_LEADER
  // Leader key set-up
  if (record->event.pressed) {
    if (!leading && keycode == KC_LEAD) {
      leader_start();
      leading = true;
      leader_time = timer_read();
      leader_sequence_size = 0;
      leader_sequence[0] = 0;
      leader_sequence[1] = 0;
      leader_sequence[2] = 0;
      leader_sequence[3] = 0;
      leader_sequence[4] = 0;
      return false;
    }
    if (leading && timer_elapsed(leader_time) < LEADER_TIMEOUT) {
      leader_sequence[leader_sequence_size] = keycode;
      leader_sequence_size++;
      return false;
    }
  }
#endif

#define DISABLE_CHORDING
#ifndef DISABLE_CHORDING

  if (keycode >= QK_CHORDING && keycode <= QK_CHORDING_MAX) {
    if (record->event.pressed) {
      if (!chording) {
        chording = true;
        for (uint8_t i = 0; i < CHORDING_MAX; i++)
          chord_keys[i] = 0;
        chord_key_count = 0;
        chord_key_down = 0;
      }
      chord_keys[chord_key_count] = (keycode & 0xFF);
      chord_key_count++;
      chord_key_down++;
      return false;
    } else {
      if (chording) {
        chord_key_down--;
        if (chord_key_down == 0) {
          chording = false;
          // Chord Dictionary
          if (keys_chord((uint8_t[]){KC_ENTER, KC_SPACE})) {
            register_code(KC_A);
            unregister_code(KC_A);
            return false;
          }
          for (uint8_t i = 0; i < chord_key_count; i++) {
            register_code(chord_keys[i]);
            unregister_code(chord_keys[i]);
            return false;
          }
        }
      }
    }
  }

#endif

#ifdef UNICODE_ENABLE

  if (keycode > QK_UNICODE && record->event.pressed) {
    uint16_t unicode = keycode & 0x7FFF;
    switch(input_mode) {
      case UC_OSX:
        register_code(KC_LALT);
        break;
      case UC_LNX:
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_U);
        unregister_code(KC_U);
        break;
      case UC_WIN:
        register_code(KC_LALT);
        register_code(KC_PPLS);
        unregister_code(KC_PPLS);
        break;
    }
    for(int i = 3; i >= 0; i--) {
        uint8_t digit = ((unicode >> (i*4)) & 0xF);
        register_code(hex_to_keycode(digit));
        unregister_code(hex_to_keycode(digit));
    }
    switch(input_mode) {
      case UC_OSX:
      case UC_WIN:
        unregister_code(KC_LALT);
        break;
      case UC_LNX:
        unregister_code(KC_LCTL);
        unregister_code(KC_LSFT);
        break;
    }
  }

#endif

  // Shift / paren setup

  switch(keycode) {
    case RESET:
      if (record->event.pressed) {
        clear_keyboard();
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          shutdown_user();
        #endif
        _delay_ms(250);
        #ifdef ATREUS_ASTAR
            *(uint16_t *)0x0800 = 0x7777; // these two are a-star-specific
        #endif
        bootloader_jump();
        return false;
      }
      break;
    case DEBUG:
      if (record->event.pressed) {
          print("\nDEBUG: enabled.\n");
          debug_enable = true;
          return false;
      }
      break;
    case MAGIC_SWAP_CONTROL_CAPSLOCK ... MAGIC_UNSWAP_ALT_GUI:
      if (record->event.pressed) {
        // MAGIC actions (BOOTMAGIC without the boot)
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        /* keymap config */
        keymap_config.raw = eeconfig_read_keymap();
        if (keycode == MAGIC_SWAP_CONTROL_CAPSLOCK) {
            keymap_config.swap_control_capslock = 1;
        } else if (keycode == MAGIC_CAPSLOCK_TO_CONTROL) {
            keymap_config.capslock_to_control = 1;
        } else if (keycode == MAGIC_SWAP_LALT_LGUI) {
            keymap_config.swap_lalt_lgui = 1;
        } else if (keycode == MAGIC_SWAP_RALT_RGUI) {
            keymap_config.swap_ralt_rgui = 1;
        } else if (keycode == MAGIC_NO_GUI) {
            keymap_config.no_gui = 1;
        } else if (keycode == MAGIC_SWAP_GRAVE_ESC) {
            keymap_config.swap_grave_esc = 1;
        } else if (keycode == MAGIC_SWAP_BACKSLASH_BACKSPACE) {
            keymap_config.swap_backslash_backspace = 1;
        } else if (keycode == MAGIC_HOST_NKRO) {
            keymap_config.nkro = 1;
        } else if (keycode == MAGIC_SWAP_ALT_GUI) {
            keymap_config.swap_lalt_lgui = 1;
            keymap_config.swap_ralt_rgui = 1;
        }
        /* UNs */
        else if (keycode == MAGIC_UNSWAP_CONTROL_CAPSLOCK) {
            keymap_config.swap_control_capslock = 0;
        } else if (keycode == MAGIC_UNCAPSLOCK_TO_CONTROL) {
            keymap_config.capslock_to_control = 0;
        } else if (keycode == MAGIC_UNSWAP_LALT_LGUI) {
            keymap_config.swap_lalt_lgui = 0;
        } else if (keycode == MAGIC_UNSWAP_RALT_RGUI) {
            keymap_config.swap_ralt_rgui = 0;
        } else if (keycode == MAGIC_UNNO_GUI) {
            keymap_config.no_gui = 0;
        } else if (keycode == MAGIC_UNSWAP_GRAVE_ESC) {
            keymap_config.swap_grave_esc = 0;
        } else if (keycode == MAGIC_UNSWAP_BACKSLASH_BACKSPACE) {
            keymap_config.swap_backslash_backspace = 0;
        } else if (keycode == MAGIC_UNHOST_NKRO) {
            keymap_config.nkro = 0;
        } else if (keycode == MAGIC_UNSWAP_ALT_GUI) {
            keymap_config.swap_lalt_lgui = 0;
            keymap_config.swap_ralt_rgui = 0;
        }
        eeconfig_update_keymap(keymap_config.raw);
        return false;
      }
      break;
    case KC_LSPO: {
      if (record->event.pressed) {
        shift_interrupted[0] = false;
        register_mods(MOD_BIT(KC_LSFT));
      }
      else {
        if (!shift_interrupted[0]) {
          register_code(LSPO_KEY);
          unregister_code(LSPO_KEY);
        }
        unregister_mods(MOD_BIT(KC_LSFT));
      }
      return false;
      break;
    }

    case KC_RSPC: {
      if (record->event.pressed) {
        shift_interrupted[1] = false;
        register_mods(MOD_BIT(KC_RSFT));
      }
      else {
        if (!shift_interrupted[1]) {
          register_code(RSPC_KEY);
          unregister_code(RSPC_KEY);
        }
        unregister_mods(MOD_BIT(KC_RSFT));
      }
      return false;
      break;
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

void matrix_init_quantum() {
  #ifdef BACKLIGHT_ENABLE
    backlight_init_ports();
  #endif
  matrix_init_kb();
}

void matrix_scan_quantum() {
  #ifdef AUDIO_ENABLE
  if (music_sequence_playing) {
    if ((music_sequence_timer == 0) || (timer_elapsed(music_sequence_timer) > music_sequence_interval)) {
      music_sequence_timer = timer_read();
      stop_note(music_sequence[(music_sequence_position - 1 < 0)?(music_sequence_position - 1 + music_sequence_count):(music_sequence_position - 1)]);
      play_note(music_sequence[music_sequence_position], 0xF);
      music_sequence_position = (music_sequence_position + 1) % music_sequence_count;
    }
  }

  #endif

  matrix_scan_kb();
}

#ifdef AUDIO_ENABLE
  bool is_music_on(void) {
      return (music_activated != 0);
  }

  void music_toggle(void) {
      if (!music_activated) {
          music_on();
      } else {
          music_off();
      }
  }

  void music_on(void) {
      music_activated = 1;
      music_on_user();
  }

  void music_off(void) {
      music_activated = 0;
      stop_all_notes();
  }

#endif


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
#  error "Backlight pin not supported - use B5, B6, or B7"
#endif

__attribute__ ((weak))
void backlight_init_ports(void)
{

  // Setup backlight pin as output and output low.
  // DDRx |= n
  _SFR_IO8((backlight_pin >> 4) + 1) |= _BV(backlight_pin & 0xF);
  // PORTx &= ~n
  _SFR_IO8((backlight_pin >> 4) + 2) &= ~_BV(backlight_pin & 0xF);

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

  backlight_init();
  #ifdef BACKLIGHT_BREATHING
    breathing_defaults();
  #endif
}

__attribute__ ((weak))
void backlight_set(uint8_t level)
{
  // Prevent backlight blink on lowest level
  // PORTx &= ~n
  _SFR_IO8((backlight_pin >> 4) + 2) &= ~_BV(backlight_pin & 0xF);

  if ( level == 0 ) {
    // Turn off PWM control on backlight pin, revert to output low.
    TCCR1A &= ~(_BV(COM1x1));
    OCR1x = 0x0;
  } else if ( level == BACKLIGHT_LEVELS ) {
    // Turn on PWM control of backlight pin
    TCCR1A |= _BV(COM1x1);
    // Set the brightness
    OCR1x = 0xFFFF;
  } else {
    // Turn on PWM control of backlight pin
    TCCR1A |= _BV(COM1x1);
    // Set the brightness
    OCR1x = 0xFFFF >> ((BACKLIGHT_LEVELS - level) * ((BACKLIGHT_LEVELS + 1) / 2));
  }

  #ifdef BACKLIGHT_BREATHING
    breathing_intensity_default();
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

__attribute__ ((weak))
void music_on_user() {}

__attribute__ ((weak))
void audio_on_user() {}

__attribute__ ((weak))
void music_scale_user() {}

//------------------------------------------------------------------------------
