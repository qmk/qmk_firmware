#ifndef PROCESS_UNICODEMAP_H
#define PROCESS_UNICODEMAP_H

#include "quantum.h"
#include "process_unicode_common.h"

void unicode_map_input_error(void);
bool process_unicode_map(uint16_t keycode, keyrecord_t *record);
#endif