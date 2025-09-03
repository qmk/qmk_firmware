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

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "compiler_support.h"

#ifndef BACKLIGHT_LEVELS
#    define BACKLIGHT_LEVELS 3
#elif BACKLIGHT_LEVELS > 31
#    error "Maximum value of BACKLIGHT_LEVELS is 31"
#endif

#ifndef BACKLIGHT_ON_STATE
#    define BACKLIGHT_ON_STATE 1
#endif

#ifndef BREATHING_PERIOD
#    define BREATHING_PERIOD 6
#endif

typedef union backlight_config_t {
    uint8_t raw;
    struct {
        bool    enable : 1;
        bool    breathing : 1;
        bool    valid : 1;
        uint8_t level : 5;
    };
} backlight_config_t;

STATIC_ASSERT(sizeof(backlight_config_t) == sizeof(uint8_t), "Backlight EECONFIG out of spec.");

void    backlight_init(void);
void    backlight_toggle(void);
void    backlight_enable(void);
void    backlight_disable(void);
bool    is_backlight_enabled(void);
void    backlight_step(void);
void    backlight_increase(void);
void    backlight_decrease(void);
void    backlight_level_noeeprom(uint8_t level);
void    backlight_level(uint8_t level);
uint8_t get_backlight_level(void);

void eeconfig_update_backlight_current(void);
void eeconfig_update_backlight_default(void);

// implementation specific
void backlight_init_ports(void);
void backlight_set(uint8_t level);
void backlight_task(void);

#ifdef BACKLIGHT_BREATHING

void backlight_toggle_breathing(void);
void backlight_enable_breathing(void);
void backlight_disable_breathing(void);
bool is_backlight_breathing(void);

void    breathing_period_set(uint8_t value);
uint8_t get_breathing_period(void);
void    breathing_period_default(void);
void    breathing_period_inc(void);
void    breathing_period_dec(void);

void breathing_toggle(void);

// implementation specific
void breathing_enable(void);
void breathing_disable(void);
bool is_breathing(void);
void breathing_pulse(void);
#endif
