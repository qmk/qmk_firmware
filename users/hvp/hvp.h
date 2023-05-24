 /* Copyright 2021 hvp
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
  * (at your option) any later version. 
  * 
  * This program is distributed in the hope that it will be useful, 
  * but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
  * GNU General Public License for more details. 
  * 
  * You should have received a copy of the GNU General Public License 
  * along with this program.  If not, see <http://www.gnu.org/licenses/>. 
  */ 


#pragma once
#include "quantum.h"
#undef TAPPING_TERM
#define TAPPING_TERM 150

#ifdef TAP_DANCE_ENABLE
#    include "tap_dances.h"
#endif

#ifdef TAPPING_TERM_PER_KEY
#    include "per_key.h"
#endif


#define D_NAVI MT(MOD_LCTL | MOD_LSFT, KC_D)

/* Home-row mods */
#define LG_A MT(MOD_LGUI, KC_A)
#define LA_S MT(MOD_LALT, KC_S)
#define LS_D MT(MOD_LSFT, KC_D)
#define LC_F MT(MOD_LCTL, KC_F)

#define RC_H MT(MOD_RCTL, KC_H)
#define RS_J MT(MOD_RSFT, KC_J)
#define RA_K MT(MOD_RALT, KC_K)
#define RG_L MT(MOD_RGUI, KC_L)