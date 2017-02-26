#ifndef PROCESS_AUDIO_H
#define PROCESS_AUDIO_H

bool process_audio(uint16_t keycode, keyrecord_t *record);
void process_audio_noteon(uint8_t note);
void process_audio_noteoff(uint8_t note);
void process_audio_stop_all_notes(void);

void audio_on_user(void);

#endif