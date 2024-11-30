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

typedef struct host_driver_t {
    bool has_init_executed;
    bool (*init)(void);
    bool (*connect)(void);
    bool (*disconnect)(void);
    bool (*is_connected)(void);
    uint8_t (*keyboard_leds)(void);
    void (*send_keyboard)(report_keyboard_t *);
    void (*send_nkro)(report_nkro_t *);
    void (*send_mouse)(report_mouse_t *);
    void (*send_extra)(report_extra_t *);
#ifdef JOYSTICK_ENABLE
    void (*send_joystick)(report_joystick_t *);
#endif // JOYSTICK_ENABLE
#ifdef DIGITIZER_ENABLE
    void (*send_digitizer)(report_digitizer_t *);
#endif // DIGITIZER_ENABLE
#ifdef PROGRAMMABLE_BUTTON_ENABLE
    void (*send_programmable_button)(report_programmable_button_t *);
#endif // PROGRAMMABLE_BUTTON_ENABLE
#ifdef CONSOLE_ENABLE
    int8_t (*send_console)(uint8_t);
#endif // CONSOLE_ENABLE
#ifdef VIRTSER_ENABLE
    void (*send_virtser)(uint8_t);
#endif // VIRTSER_ENABLE
#ifdef RAW_ENABLE
    void (*send_raw_hid)(uint8_t *, uint8_t);
#endif // RAW_ENABLE
} host_driver_t;
