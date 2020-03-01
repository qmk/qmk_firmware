#include "alfrdmalr.h"
#include "muse.h"

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

LEADER_EXTERNS();

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

  LEADER_DICTIONARY() {
    leading = false;
    // reset keyboard to bootloader
    SEQ_FIVE_KEYS(KC_R, KC_E, KC_S, KC_E, KC_T) {
      reset_keyboard();
    }
    // minimize window (Windows)
    SEQ_THREE_KEYS(KC_M, KC_I, KC_N) {
      SEND_STRING(SS_LALT(" ")"n");
    }
    leader_end(); 
  }
}