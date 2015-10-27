/*
Copyright 2013 Mathias Andersson <wraul@dbox.se>

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

#ifndef BACKLIGHT_H
#define BACKLIGHT_H

#include <stdint.h>
#include <stdbool.h>

typedef union {
    uint8_t raw;
    struct {
        bool    enable :1;
        uint8_t level  :7;
    };
} backlight_config_t;

void backlight_init(void);
void backlight_increase(void);
void backlight_decrease(void);
void backlight_toggle(void);
void backlight_step(void);
void backlight_set(uint8_t level);
void backlight_level(uint8_t level);

#endif
