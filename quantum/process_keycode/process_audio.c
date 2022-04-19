#include "audio.h"
#include "process_audio.h"

#ifndef VOICE_CHANGE_SONG
#    define VOICE_CHANGE_SONG SONG(VOICE_CHANGE_SOUND)
#endif
float voice_change_song[][2] = VOICE_CHANGE_SONG;

#ifndef PITCH_STANDARD_A
#    define PITCH_STANDARD_A 440.0f
#endif

float compute_freq_for_midi_note(uint8_t note) {
    // https://en.wikipedia.org/wiki/MIDI_tuning_standard
    return pow(2.0, (note - 69) / 12.0) * PITCH_STANDARD_A;
}

bool process_audio(uint16_t keycode, keyrecord_t *record) {
    if (keycode == AU_ON && record->event.pressed) {
        audio_on();
        return false;
    }

    if (keycode == AU_OFF && record->event.pressed) {
        audio_off();
        return false;
    }

    if (keycode == AU_TOG && record->event.pressed) {
        if (is_audio_on()) {
            audio_off();
        } else {
            audio_on();
        }
        return false;
    }

    if (keycode == MUV_IN && record->event.pressed) {
        voice_iterate();
        PLAY_SONG(voice_change_song);
        return false;
    }

    if (keycode == MUV_DE && record->event.pressed) {
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

__attribute__((weak)) void audio_on_user() {}
__attribute__((weak)) void audio_off_user() {}
