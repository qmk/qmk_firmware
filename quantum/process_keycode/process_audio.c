#include "audio.h"
#include "process_audio.h"
#include <math.h>

#ifndef VOICE_CHANGE_SONG
#    define VOICE_CHANGE_SONG SONG(VOICE_CHANGE_SOUND)
#endif
float voice_change_song[][2] = VOICE_CHANGE_SONG;

#ifndef PITCH_STANDARD_A
#    define PITCH_STANDARD_A 440.0f
#endif

float compute_freq_for_midi_note(uint8_t note) {
    // https://en.wikipedia.org/wiki/MIDI_tuning_standard
    return powf(2.0f, (note - 69) / 12.0f) * PITCH_STANDARD_A;
}

bool process_audio(uint16_t keycode, keyrecord_t *record) {
    if (keycode == QK_AUDIO_ON && record->event.pressed) {
        audio_on();
        return false;
    }

    if (keycode == QK_AUDIO_OFF && record->event.pressed) {
        audio_off();
        return false;
    }

    if (keycode == QK_AUDIO_TOGGLE && record->event.pressed) {
        if (is_audio_on()) {
            audio_off();
        } else {
            audio_on();
        }
        return false;
    }

    if (keycode == QK_AUDIO_VOICE_NEXT && record->event.pressed) {
        voice_iterate();
        PLAY_SONG(voice_change_song);
        return false;
    }

    if (keycode == QK_AUDIO_VOICE_PREVIOUS && record->event.pressed) {
        voice_deiterate();
        PLAY_SONG(voice_change_song);
        return false;
    }

    return true;
}

void process_audio_noteon(uint8_t note) {
    play_note(compute_freq_for_midi_note(note), 0xF);
}

void process_audio_noteoff(uint8_t note) {
    stop_note(compute_freq_for_midi_note(note));
}

void process_audio_all_notes_off(void) {
    stop_all_notes();
}
