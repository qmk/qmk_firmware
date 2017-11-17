/*
Copyright 2017 Danny Nguyen <danny@hexwire.com>

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

#ifndef LLAMA_CONFIG_H
#define LLAMA_CONFIG_H

#include "config_common.h"


/* Prevent modifiers from sticking when switching layers */
#define PREVENT_STUCK_MODIFIERS

#define MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS  true
#define MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS  false
#define MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM false



#include QMK_SUBPROJECT_CONFIG_H

#endif  // LLAMA_CONFIG_H
