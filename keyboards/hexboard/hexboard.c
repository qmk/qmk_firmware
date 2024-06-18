// Copyright 2022-2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only

#include "quantum.h"

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

#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    oled_write_P(PSTR("HexBoard running QMK\n"), false);
    oled_write_P(PSTR("\n"), false);
    oled_write_P(PSTR("FW is GPLv3-licensed\n"), false);
    oled_write_P(PSTR("https://qmk.fm/\n"), false);
    return false;
}
#endif
