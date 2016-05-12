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
#endif

bool leading = false;
uint16_t leader_time = 0;

uint16_t leader_sequence[3] = {0, 0, 0};
uint8_t leader_sequence_size = 0;

bool process_action_quantum(keyrecord_t *record) {

#ifdef AUDIO_ENABLE
  #ifdef _MUSIC
  if (IS_LAYER_ON(_MUSIC)) {
    if (record->event.pressed) {
        play_note(((double)220.0)*pow(2.0, -4.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row)), 0xF);
    } else {
        stop_note(((double)220.0)*pow(2.0, -4.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row)));
    }
  }
  #endif
#endif

#ifndef DISABLE_LEADER
  // Leader key set-up
  if (record->event.pressed) {
    keypos_t key = record->event.key;
    uint16_t keycode;

    #ifndef NO_ACTION_LAYER
      uint32_t layers = layer_state | default_layer_state;
      /* check top layer first */
      for (int8_t i = 31; i >= 0; i--) {
          if (layers & (1UL<<i)) {
            // action = action_for_key(i, key);
            // if (action.code != ACTION_TRANSPARENT) {
              keycode = keymap_key_to_keycode(i, key);
            }
      }
      /* fall back to layer 0 */
      keycode = keymap_key_to_keycode(0, key);
    #else
      keycode = keymap_key_to_keycode(biton32(default_layer_state), key);
    #endif

    if (keycode == KC_LEAD) {
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

  return process_action_kb(record);
}

void matrix_init_quantum() {
  matrix_init_kb();
}

void matrix_scan_quantum() {
  matrix_scan_kb();
}