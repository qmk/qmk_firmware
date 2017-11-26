#include "process_chording.h"

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

bool process_chording(uint16_t keycode, keyrecord_t *record) {
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
  return true;
}