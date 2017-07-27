#ifndef PROCESS_STENO_H
#define PROCESS_STENO_H

#include "quantum.h"

#if defined(STENO_ENABLE) && !defined(VIRTSER_ENABLE)
  #error "must have virtser enabled to use steno"
#endif

typedef enum { STENO_MODE_BOLT, STENO_MODE_GEMINI } steno_mode_t;

bool process_steno(uint16_t keycode, keyrecord_t *record);
void steno_init(void);
void steno_set_mode(steno_mode_t mode);

#endif