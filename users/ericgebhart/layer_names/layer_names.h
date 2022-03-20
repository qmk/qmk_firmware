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

// Get the enums for the layers.
enum userspace_layers {

// get all the usual base layers for default lang.
#include "base_names.h"

// do it again for bepo
// + bepo specific ones.
#include "bepo_names.h"

// all the functional layers.
#include "trans_names.h"

};

// set the combo reference layer if we have one.
#undef COMBO_REF_DEFAULT
#define COMBO_REF_DEFAULT _COMBO_REF

// find the beginning and end of each locale.
#include "locale_layers.h"
