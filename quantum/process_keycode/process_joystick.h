#pragma once

#include <stdint.h>
#include "quantum.h"

bool process_joystick(uint16_t keycode, keyrecord_t *record);

void joystick_task(void);
void joystick_flush(void);

void register_joystick_button(uint8_t button);
void unregister_joystick_button(uint8_t button);

bool process_joystick_analogread(void);
bool process_joystick_analogread_quantum(void);
