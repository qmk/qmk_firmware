#include "alfrdmalr.h"
#include "muse.h"

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void leader_end_user(void) {
    // reset keyboard to bootloader
    if (leader_sequence_five_keys(KC_R, KC_E, KC_S, KC_E, KC_T)) {
        reset_keyboard();
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool syml_pressed = false;
bool symr_pressed = false;
bool settings_active = false;
bool symbols_active = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case SYML:
      if (record->event.pressed) {
        syml_pressed = true;
      } else {
        syml_pressed = false;
      }
      break;
    case SYMR:
      if (record->event.pressed) {
        symr_pressed = true;
      } else {
        symr_pressed = false;
      }
      break;
  }

  // trilayer-esque behavior. If both SYMBOL layer keys are held, then the 
  // settings layer is open. If only one is held, SYMBOL is active.
  if (syml_pressed && symr_pressed) {
    layer_on(_SETTINGS);
    settings_active = true;
  } else if (syml_pressed || symr_pressed) {
    if (settings_active) {
      layer_off(_SETTINGS);
      settings_active = false;
    }
    layer_on(_SYMBOL);
    symbols_active = true;
  } else {
    if (symbols_active) {
      layer_off(_SYMBOL);
      symbols_active = false;
    }
  }

  return true;
}

// allow access to the settings layer to turn music mode back off
bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case SYML:
    case SYMR:
      return false;
    default:
      return true;
  }
}