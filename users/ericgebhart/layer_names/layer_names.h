/*
  Copyright 2018-2022 Eric Gebhart <e.a.gebhart@gmail.com>

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
#include QMK_KEYBOARD_H
#include "base_layers.h"
#include "layouts.h"
#include "layers.h"
#if defined(OLED_CUSTOM_ENABLE)
#    include "oled_stuff.h"
#endif

#define MO_LAYERS MO(_LAYERS)

#undef LANG_IS
#define LANG_IS LOCALE_LAYERS

enum base_layer_names{
#include "base_names.h"
  BASE_NAME_COUNT
};
#undef LANG_IS
#define LANG_IS DEFAULT_LANG


// Get the enums for the layers.
enum userspace_layers {

#include "base_names.h"

  // get them again if we have another locale.
#ifdef SECOND_LOCALE
#undef LANG_IS
#define LANG_IS SECOND_LOCALE

#include "base_names.h"

#undef LANG_IS
#define LANG_IS DEFAULT_LANG
#endif

  _LAYERS,

#include "func_names.h"

  // get them again if we have another locale.
#ifdef SECOND_LOCALE
#undef LANG_IS
#define LANG_IS SECOND_LOCALE

#include "func_names.h"

#undef LANG_IS
#define LANG_IS DEFAULT_LANG
#endif

#include "util_names.h"

};


// find the beginning and end of each locale.
#include "locale_layers.h"
