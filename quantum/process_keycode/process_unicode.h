#ifndef PROCESS_UNICODE_H
#define PROCESS_UNICODE_H

#include "quantum.h"

#define UC_OSX 0
#define UC_LNX 1
#define UC_WIN 2
#define UC_BSD 3

void set_unicode_input_mode(uint8_t os_target);

bool process_unicode(uint16_t keycode, keyrecord_t *record);

#endif