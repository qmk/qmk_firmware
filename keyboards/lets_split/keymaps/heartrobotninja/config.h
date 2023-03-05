/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Select hand configuration */

// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 1000

#undef LEADER_TIMEOUT
#define LEADER_TIMEOUT 1000

#undef TAPPING_TERM
#define TAPPING_TERM 200

#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2

#ifdef SUBPROJECT_rev1
#include "../../rev1/config.h"
#endif
#ifdef SUBPROJECT_rev2
#include "../../rev2/config.h"
#endif
#ifdef SUBPROJECT_rev2fliphalf
#include "../../rev2fliphalf/config.h"
#endif

#endif
