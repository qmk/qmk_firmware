#ifndef PROCESS_JOYSTICK_H
#define PROCESS_JOYSTICK_H

#include <stdint.h>
#include "quantum.h"

bool process_joystick(uint16_t keycode, keyrecord_t *record);

void joystick_task(void);

bool process_joystick_analog(void);

#endif //PROCESS_JOYSTICK_H