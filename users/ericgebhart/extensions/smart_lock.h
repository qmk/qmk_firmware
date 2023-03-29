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
#include QMK_KEYBOARD_H
#include USERSPACE_H

#ifdef SMART_LOCK_ENABLE
typedef enum {
  sml_layer,
  sml_mod
} smart_lock_type;

typedef struct {
  bool     active;
  const uint16_t *keys;
  uint16_t keycode;
  uint16_t thing;
  smart_lock_type type;
} smart_lock_t;


// smart layer, smart mods
#undef SMLL
#undef SMLM
#define SMLL(key, layer, ...)
#define SMLM(key, mod, ...)  // to replace mod_lock..
#define COND_KEYS_END 0

#define CONCATENATE_SA(a, ...) a ## __VA_ARGS__
#define CONCATENATE_S(a, ...) a ## __VA_ARGS__
#define CAT_S(a, ...) CONCATENATE_S(a, __VA_ARGS__)
#define MK_SKEY(KC) CONCATENATE_S(sml_, KC)
#define MK_ARRAY(KC)                                    \
  const uint16_t PROGMEM CONCATENATE_SA(sml_, KC)[]

// to create an enum and find how many...
#define S_ENUM(kc, layer, ...) CAT_S(sml__, kc),
// create a const array of the condkeys for each SML
#define S_DATA(kc, thing, ...) MK_ARRAY(kc) = {__VA_ARGS__, COND_KEYS_END};

// create a list of smart_lock structs. Two names, one for mod one for layer to be concise.
#define S_SMART_LOCK(kc, layer, ...) {false, MK_SKEY(kc), kc, layer, sml_layer},
#define M_SMART_LOCK(kc, mod, ...)   {false, MK_SKEY(kc), kc, mod,   sml_mod},

#define SML(sk, sa, st, stype)                                          \
  { .keys = &(sk)[0], .keycode = (sa), .thing = (st), .smart_lock_type = stype}
#define K_SMLM(key, mod...)   [MK_SKEY(key)] = SML(MK_SKEY(key), key, mod, sml_mod),
#define K_SMLL(key, layer...) [MK_SKEY(key)] = SML(MK_SKEY(key), key, layer, sml_layer),

// Set everything up
// - Create enum of names, (sml_keycode). Used as indexes in the arrays.
//    avoids using the keycodes which would create a sparse/large array.
// - Create array of conditional locks..
// - Create array of the conditional keys for the locks, by name.

// Create Enum
#undef SMLL
#undef SMLM
#define SMLL S_ENUM
#define SMLM S_ENUM

// find how many
enum smart_locks {
#include "smart_lock.def"
  SML_LENGTH
};
uint16_t SML_LEN = SML_LENGTH;

// Bake locks into mem, name, ignore/cancel keys
#undef SMLL
#undef SMLM
#undef TOGG
#define SMLL S_DATA
#define SMLM S_DATA
#include "smart_lock.def"
#undef SMLL
#undef SMLM

// Fill array of locks by name, kc, layer/mod.
#define SMLL S_SMART_LOCK
#define SMLM M_SMART_LOCK

smart_lock_t smart_locks[] = {
#include "smart_lock.def"
};
#undef SMLL
#undef SMLM

#endif
