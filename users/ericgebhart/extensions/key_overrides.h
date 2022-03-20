#pragma once
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
#ifdef KEY_OVERRIDE_ENABLE

#define KO_NAME(name, ...) &name,
#define KO_T(name) const key_override_t name

#undef KOL
#define KOL(name, mods, modded_key, replacement, layer)                 \
  KO_T(name) = ko_make_with_layers(mods, modded_key, replacement, (1 << layer));

#define KO(name, mods, key, replacement)                \
  KO_T(name) = ko_make_basic(mods, key, replacement)

#define KOLN(name, mods, key, replacement, layers, neg_mods)            \
  KO_T(name) = ko_make_with_layers_and_negmods(mods, key, replacement, layers, neg_mods)

#define KOLNO(name, mods, key, replacement, layers, neg_mods, options)  \
  KO_T(name) = ko_make_with_layers_negmods_and_options                  \
    (mods, key, replacement, layers, neg_mods, options)

#include "key_overrides.def"

#undef KO
#undef KOL
#undef KOLN
#undef KOLNO
#define KO KO_NAME
#define KOL KO_NAME
#define KOLN KO_NAME
#define KOLNO KO_NAME

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
#include "key_overrides.def"
  NULL // Null terminate the array of overrides!
};
#endif
