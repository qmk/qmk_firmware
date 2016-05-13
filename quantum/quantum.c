#include "quantum.h"

__attribute__ ((weak))
void matrix_init_kb(void) {}

__attribute__ ((weak))
void matrix_scan_kb(void) {}

__attribute__ ((weak))
bool process_action_kb(keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
void leader_start(void) {}

__attribute__ ((weak))
void leader_end(void) {}

#ifdef AUDIO_ENABLE
  uint8_t starting_note = 0x0C;
  int offset = 0;
  bool music_activated = false;
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

bool process_action_quantum(keyrecord_t *record) {

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

  #ifdef AUDIO_ENABLE
    if (music_activated) {
      if (record->event.pressed) {
          play_note(((double)220.0)*pow(2.0, -4.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row)), 0xF);
      } else {
          stop_note(((double)220.0)*pow(2.0, -4.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row)));
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


  return process_action_kb(record);
}

void matrix_init_quantum() {
  matrix_init_kb();
}

void matrix_scan_quantum() {
  matrix_scan_kb();
}