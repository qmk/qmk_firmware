#include "quantum.h"
#include "timer.h"

__attribute__ ((weak))
void matrix_init_kb(void) {}

__attribute__ ((weak))
void matrix_scan_kb(void) {}

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

uint16_t leader_sequence[3] = {0, 0, 0};
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
              // midi_send_cc(&midi_device, 1, 0x7B, 0);
              // midi_send_cc(&midi_device, 2, 0x7B, 0);
              // midi_send_cc(&midi_device, 3, 0x7B, 0);
              // midi_send_cc(&midi_device, 4, 0x7B, 0);
          }
          return false;
      }
      if (record->event.key.col == (MATRIX_COLS - 2) && record->event.key.row == (MATRIX_ROWS - 1)) {
          if (record->event.pressed) {
              starting_note--; // Change key
              midi_send_cc(&midi_device, 0, 0x7B, 0);
              // midi_send_cc(&midi_device, 1, 0x7B, 0);
              // midi_send_cc(&midi_device, 2, 0x7B, 0);
              // midi_send_cc(&midi_device, 3, 0x7B, 0);
              // midi_send_cc(&midi_device, 4, 0x7B, 0);
          }
          return false;
      }
      if (record->event.key.col == (MATRIX_COLS - 3) && record->event.key.row == (MATRIX_ROWS - 1) && record->event.pressed) {
          offset++; // Change scale
          midi_send_cc(&midi_device, 0, 0x7B, 0);
          // midi_send_cc(&midi_device, 1, 0x7B, 0);
          // midi_send_cc(&midi_device, 2, 0x7B, 0);
          // midi_send_cc(&midi_device, 3, 0x7B, 0);
          // midi_send_cc(&midi_device, 4, 0x7B, 0);
          return false;
      }
      if (record->event.key.col == (MATRIX_COLS - 4) && record->event.key.row == (MATRIX_ROWS - 1) && record->event.pressed) {
          offset--; // Change scale
          midi_send_cc(&midi_device, 0, 0x7B, 0);
          // midi_send_cc(&midi_device, 1, 0x7B, 0);
          // midi_send_cc(&midi_device, 2, 0x7B, 0);
          // midi_send_cc(&midi_device, 3, 0x7B, 0);
          // midi_send_cc(&midi_device, 4, 0x7B, 0);
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

  if (keycode >= 0x5700 && keycode <= 0x57FF) {
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

  if (keycode > UNICODE(0) && record->event.pressed) {
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

  switch(keycode) {
    case KC_LSPO: {
                    if (record->event.pressed) {
                      shift_interrupted[0] = false;
                      register_mods(MOD_BIT(KC_LSFT));
                    }
                    else {
                      if (!shift_interrupted[0]) {
                        register_code(KC_9);
                        unregister_code(KC_9);
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
                        register_code(KC_0);
                        unregister_code(KC_0);
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


void matrix_init_quantum() {
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
