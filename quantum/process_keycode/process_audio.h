#pragma once

float compute_freq_for_midi_note(uint8_t note);

bool process_audio(uint16_t keycode, keyrecord_t *record);
void process_audio_noteon(uint8_t note);
void process_audio_noteoff(uint8_t note);
void process_audio_all_notes_off(void);

void audio_on_user(void);
