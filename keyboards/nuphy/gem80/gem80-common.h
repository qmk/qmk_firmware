/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

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
#include "color.h"
#include "common/config.h"
#include "quantum_keycodes.h"

#ifdef VIA_ENABLE
enum via_indicator_value {
    // logo light controls
    id_logo_light_mode              = 20,
    id_logo_light_speed             = 21,
    id_logo_light_color             = 22,
    id_logo_light_brightness        = 23,
};
// function declaration
#endif

extern keyboard_config_t keyboard_config;
