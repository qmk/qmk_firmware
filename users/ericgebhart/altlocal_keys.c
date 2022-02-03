/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

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

#include "ericgebhart.h"
#include "altlocal_keys.h"

#include "keymap_bepo.h"

// These are the keys for dvorak on bepo.  column one is the keycode and mods for
// the unshifted key, the second column is the keycode and mods for the shifted key.
// GR is Good Range.  It subtracts SAFE_RANGE from the keycode so we can make a
// reasnably sized array without difficulties. The macro is for the constant declarations
// the function is for when we use it.
const uint16_t key_translations[][2][2] = {
  [GR(DB_1)] =      {{BP_DQUO, MOD_LSFT},      {BP_DCIR, MOD_LSFT}},
  [GR(DB_2)] =      {{BP_LDAQ, MOD_LSFT},      {BP_AT, MOD_NONE}},
  [GR(DB_3)] =      {{BP_RDAQ, MOD_LSFT},      {BP_DLR, MOD_LSFT}},
  [GR(DB_4)] =      {{BP_LPRN, MOD_LSFT},      {BP_DLR, MOD_NONE}},
  [GR(DB_5)] =      {{BP_RPRN, MOD_LSFT},      {BP_PERC, MOD_NONE}},
  [GR(DB_6)] =      {{BP_AT, MOD_LSFT},        {BP_AT, MOD_BIT(KC_RALT)}},
  [GR(DB_7)] =      {{BP_PLUS, MOD_LSFT},      {BP_P, MOD_BIT(KC_RALT)}},
  [GR(DB_8)] =      {{BP_MINS, MOD_LSFT},      {BP_ASTR, MOD_NONE}},
  [GR(DB_9)] =      {{BP_SLSH, MOD_LSFT},     {BP_LPRN, MOD_NONE}},
  [GR(DB_0)] =      {{BP_ASTR, MOD_LSFT},      {BP_RPRN, MOD_NONE}},
  [GR(DB_GRV)] =    {{BP_PERC, MOD_LSFT},      {BP_K, MOD_BIT(KC_RALT)}},
  [GR(DB_SCOLON)] = {{BP_COMM, MOD_LSFT},      {BP_DOT, MOD_LSFT}},
  [GR(DB_SLASH)] =  {{BP_SLSH, MOD_NONE},     {BP_QUOT, MOD_LSFT}},
  [GR(DB_BACKSLASH)] = {{BP_AGRV, MOD_BIT(KC_RALT)}, {BP_B, MOD_BIT(KC_RALT)}},
  [GR(DB_EQL)] =    {{BP_EQL, MOD_NONE},       {BP_PLUS, MOD_NONE}},
  [GR(DB_COMM)] =   {{BP_COMM, MOD_NONE},     {BP_LDAQ, MOD_BIT(KC_RALT)}},
  [GR(DB_DOT)] =    {{BP_DOT, MOD_NONE},       {BP_RDAQ, MOD_BIT(KC_RALT)}},
  [GR(DB_QUOT)] =   {{BP_QUOT, MOD_NONE},      {BP_DQUO, MOD_NONE}},
  [GR(DB_MINUS)] =  {{BP_MINS, MOD_NONE},     {KC_SPC, MOD_BIT(KC_RALT)}},
  [GR(DB_LPRN)] =   {{BP_LPRN, MOD_NONE},      {BP_LPRN, MOD_BIT(KC_RALT)}},
  [GR(DB_RPRN)] =   {{BP_RPRN, MOD_NONE},      {BP_RPRN, MOD_BIT(KC_RALT)}},
  [GR(DB_LBRC)] =   {{BP_Y, MOD_BIT(KC_RALT)}, {BP_LPRN, MOD_BIT(KC_RALT)}},
  [GR(DB_RBRC)] =   {{BP_X, MOD_BIT(KC_RALT)}, {BP_RPRN, MOD_BIT(KC_RALT)}},
  // For the symbol layer
  [GR(DB_HASH)] =   {{BP_DLR, MOD_LSFT},          {BP_DLR, MOD_LSFT}},
  [GR(DB_LCBR)] =   {{BP_LPRN, MOD_BIT(KC_RALT)}, {BP_LPRN, MOD_BIT(KC_RALT)}},
  [GR(DB_RCBR)] =   {{BP_LPRN, MOD_BIT(KC_RALT)}, {BP_RPRN, MOD_BIT(KC_RALT)}},
  [GR(DB_PIPE)] =   {{BP_B, MOD_BIT(KC_RALT)},    {BP_B, MOD_BIT(KC_RALT)}},
  [GR(DB_TILD)] =   {{BP_K, MOD_BIT(KC_RALT)},    {BP_K, MOD_BIT(KC_RALT)}},
  [GR(DB_CIRC)] =   {{BP_AT, MOD_BIT(KC_RALT)},   {BP_AT, MOD_BIT(KC_RALT)}},
  [GR(DB_LESS)] =   {{BP_LDAQ, MOD_BIT(KC_RALT)}, {BP_LDAQ, MOD_BIT(KC_RALT)}},
  [GR(DB_GRTR)] =   {{BP_RDAQ, MOD_BIT(KC_RALT)}, {BP_RDAQ, MOD_BIT(KC_RALT)}},
  // Keys for BEAKL on Qwerty
  [GR(BQ_COMM)] =   {{KC_COMMA, MOD_NONE},    {KC_1, MOD_LSFT}},
  [GR(BQ_DOT)]  =   {{KC_DOT, MOD_NONE},      {KC_2, MOD_LSFT}},
  [GR(BQ_QUOT)] =   {{KC_QUOT, MOD_NONE},     {KC_GRV, MOD_NONE}},
};


uint8_t gr(uint16_t kc){
    return (kc - SAFE_RANGE);
}
// send the right keycode for the right mod.
// remove the mods we are taking care of,
// send our keycodes then restore them.
// all so we can make dvorak keys from bepo keycodes.
void send_keycode(uint16_t kc){
    uint8_t tmp_mods = get_mods();
    bool is_shifted = ( tmp_mods & (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)) );
    //uint8_t key[2][2] = key_translations[GR(kc)];
    // need to turn of the shift if it is on.
    unregister_mods((MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)));
    if(is_shifted){
        register_mods(SHIFTED_MODS(kc));
        register_code(SHIFTED_KEY(kc));
        unregister_code(SHIFTED_KEY(kc));
        unregister_mods(SHIFTED_MODS(kc));
    } else{
        register_mods(UNSHIFTED_MODS(kc));
        register_code(UNSHIFTED_KEY(kc));
        unregister_code(UNSHIFTED_KEY(kc));
        unregister_mods(UNSHIFTED_MODS(kc));
    }
    clear_mods();
  register_mods(tmp_mods);
}
