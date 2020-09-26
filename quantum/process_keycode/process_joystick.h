#pragma once

#include <stdint.h>
#include "quantum.h"

#   ifndef JOYSTICK_AXES_RESOLUTION
        #define JOYSTICK_AXES_RESOLUTION 8
#   endif

bool process_joystick(uint16_t keycode, keyrecord_t *record);

void joystick_task(void);

bool process_joystick_analogread(void);
bool process_joystick_analogread_quantum(void);
