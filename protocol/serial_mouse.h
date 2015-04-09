/*
Copyright 2014 Robin Haberkorn <robin.haberkorn@googlemail.com>

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

#ifndef SERIAL_MOUSE_H
#define SERIAL_MOUSE_H

#include <stdint.h>

#include "serial.h"

static inline uint8_t serial_mouse_init(void)
{
    serial_init();
    return 0;
}

void serial_mouse_task(void);

#endif
