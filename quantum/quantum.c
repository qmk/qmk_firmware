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
  float music_scale[][2] = SONG(MUSIC_SCALE_SOUND);
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

static bool music_sequence_recording = false;
static bool music_sequence_playing = false;
static float music_sequence[16] = {0};
static uint8_t music_sequence_count = 0;
static uint8_t music_sequence_position = 0;

static uint16_t music_sequence_timer = 0;
static uint16_t music_sequence_interval = 100;

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

    // This is how you use actions here
    // if (keycode == KC_LEAD) {
    //   action_t action;
    //   action.code = ACTION_DEFAULT_LAYER_SET(0);
    //   process_action(record, action);
    //   return false;
    // }

  #ifdef AUDIO_ENABLE
    if (keycode == AU_ON && record->event.pressed) {
      audio_on();
      audio_on_callback();
      return false;
    }

    if (keycode == AU_OFF && record->event.pressed) {
      audio_off();
      return false;
    }

    if (keycode == MU_ON && record->event.pressed) {
      music_activated = true;
      PLAY_NOTE_ARRAY(music_scale, false, 0);
      return false;
    }

    if (keycode == MU_OFF && record->event.pressed) {
      music_activated = false;
      stop_all_notes();
      return false;
    }

    if (keycode == MUV_IN && record->event.pressed) {
      voice_iterate();
      PLAY_NOTE_ARRAY(music_scale, false, 0);
      return false;
    }

    if (keycode == MUV_DE && record->event.pressed) {
      voice_deiterate();
      PLAY_NOTE_ARRAY(music_scale, false, 0);
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

      float freq = ((float)220.0)*pow(2.0, -4.0)*pow(2.0,(starting_note + SCALE[record->event.key.col + offset])/12.0+(MATRIX_ROWS - record->event.key.row));
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


  return process_action_kb(record);
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