#ifndef PROCESS_STENO_H
#define PROCESS_STENO_H

#include "quantum.h"

#if defined(STENO_ENABLE) && !defined(VIRTSER_ENABLE)
  #error "must have virtser enabled to use steno"
#endif

bool process_steno(uint16_t keycode, keyrecord_t *record);

#endif