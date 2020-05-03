/* Copyright 2020 Richard Sutherland
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
#include QMK_KEYBOARD_H
#include "print.h"
#include "adns.h"

enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( KC_C,   KC_Q ),

  [_LOWER] = LAYOUT( KC_BSPC,   KC_Q ),

  [_RAISE] = LAYOUT( KC_ESC,  KC_F7 )
};



void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
  print("KB INIT COMPLETE");
  setPinOutput(F5);
}

void dispRegisters(void){
  int oreg[7] = {
    0x00,0x3F,0x2A,0x02  };
  char* oregname[] = {
    "Product_ID","Inverse_Product_ID","SROM_Version","Motion"  };
  uint8_t regres;


  int rctr=0;
  for(rctr=0; rctr<4; rctr++){
    print("---\n");
    uprintf("%s\n",oregname[rctr]);
    regres = adns_read(oreg[rctr]);
    uprintf("%d\n",regres);
  }
}

