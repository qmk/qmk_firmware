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

#ifndef SCALE
#define SCALE (int8_t []){ 0 + (12*0), 2 + (12*0), 4 + (12*0), 5 + (12*0), 7 + (12*0), 9 + (12*0), 11 + (12*0), \
                           0 + (12*1), 2 + (12*1), 4 + (12*1), 5 + (12*1), 7 + (12*1), 9 + (12*1), 11 + (12*1), \
                           0 + (12*2), 2 + (12*2), 4 + (12*2), 5 + (12*2), 7 + (12*2), 9 + (12*2), 11 + (12*2), \
                           0 + (12*3), 2 + (12*3), 4 + (12*3), 5 + (12*3), 7 + (12*3), 9 + (12*3), 11 + (12*3), \
                           0 + (12*4), 2 + (12*4), 4 + (12*4), 5 + (12*4), 7 + (12*4), 9 + (12*4), 11 + (12*4), }
#endif

#endif