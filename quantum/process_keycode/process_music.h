#ifndef PROCESS_MUSIC_H
#define PROCESS_MUSIC_H

#include "quantum.h"

bool process_music(uint16_t keycode, keyrecord_t *record);

bool is_music_on(void);
void music_toggle(void);
void music_on(void);
void music_off(void);

void audio_on_user(void);
void music_on_user(void);
void music_scale_user(void);

void matrix_scan_music(void);

#endif