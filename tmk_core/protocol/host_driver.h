/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>
#include "report.h"
#ifdef MIDI_ENABLE
#    include "midi.h"
#endif

typedef struct {
    uint8_t (*keyboard_leds)(void);
    void (*send_keyboard)(report_keyboard_t *);
    void (*send_mouse)(report_mouse_t *);
    void (*send_extra)(report_extra_t *);
} host_driver_t;

void send_joystick(report_joystick_t *report);
void send_digitizer(report_digitizer_t *report);
void send_programmable_button(report_programmable_button_t *report);
