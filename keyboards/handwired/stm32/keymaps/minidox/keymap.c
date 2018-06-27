/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#include "keymap_extras/keymap_spanish.h"
#include "stm32.h"

#define LSPO_KEY ES_LPRN
#define RSPC_KEY ES_RPRN

// Highly Modified by Xydane
const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        KEYMAP_SPLITMINI(
          K00, K01, K02, K03, K04, K05, K06,                  K07, K08, K09, K0A, K0B, K0C, K0D, \
		      K10, K11, K12, K13, K14, K15, K16,                  K17, K18, K19, K1A, K1B, K1C, K1D, \
		      K20, K21, K22, K23, K24, K25, K26,                  K27, K28, K29, K2A, K2B, K2C, K2D, \
		      K30, K31, K32, K33, K34, K35, K36,                  K37, K38, K39, K3A, K3B, K3C, K3D, \
		      K40, K41, K42, K43, K44, K45, K46,                  K47, K48, K49, K4A, K4B, K4C, K4D, \
		      K50, K51, K52, K53, K54, K55, K56,                  K57, K58, K59, K5A, K5B, K5C, K5D ),
        
        KEYMAP_SPLITMINI(
          K00, K01, K02, K03, K04, K05, K06,                  K07, K08, K09, K0A, K0B, K0C, K0D, \
          K10, K11, K12, K13, K14, K15, K16,                  K17, K18, K19, K1A, K1B, K1C, K1D, \
          K20, K21, K22, K23, K24, K25, K26,                  K27, K28, K29, K2A, K2B, K2C, K2D, \
          K30, K31, K32, K33, K34, K35, K36,                  K37, K38, K39, K3A, K3B, K3C, K3D, \
          K40, K41, K42, K43, K44, K45, K46,                  K47, K48, K49, K4A, K4B, K4C, K4D, \
          K50, K51, K52, K53, K54, K55, K56,                  F(2), K58, K59, K5A, K5B, K5C, K5D ),

        KEYMAP_SPLITMINI(
          K00, K01, K02, K03, K04, K05, K06,                  K07, K08, K09, K0A, K0B, K0C, K0D, \
          K10, K11, K12, K13, K14, K15, K16,                  K17, K18, K19, K1A, K1B, K1C, K1D, \
          K20, K21, K22, K23, K24, K25, K26,                  K27, K28, K29, K2A, K2B, K2C, K2D, \
          K30, K31, K32, K33, K34, K35, K36,                  K37, K38, K39, K3A, K3B, K3C, K3D, \
          K40, K41, K42, K43, K44, K45, K46,                  K47, K48, K49, K4A, K4B, K4C, K4D, \
          K50, K51, K52, K53, K54, K55, K56,                  F(2), K58, K59, K5A, K5B, K5C, K5D ),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
    [1] = ACTION_LAYER_TOGGLE(2),  // to Fn overlay
    [2] = ACTION_FUNCTION(2),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {
  case 2:
    if (record->event.pressed) {
      palTogglePad(GPIOA, 1);
    }     
    break;
  }
}