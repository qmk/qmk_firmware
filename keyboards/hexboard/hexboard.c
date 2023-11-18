// Copyright 2022-2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only

#include "hexboard.h"

#ifdef RGB_MATRIX_ENABLE
void keyboard_post_init_user(void) {
    // Start them OFF
    rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_my_off_effect);
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef AUDIO_ENABLE
        case QK_MIDI_NOTE_C_0 ... QK_MIDI_NOTE_B_5:
            if (record->event.pressed)
                process_audio_noteon(keycode - MI_C);
            else
                process_audio_noteoff(keycode - MI_C);
            // Allow the normal handler to handle it as well.
            return true;
#endif
    }
    return process_record_user(keycode, record);
}
