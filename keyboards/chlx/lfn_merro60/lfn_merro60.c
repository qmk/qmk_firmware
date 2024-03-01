/* 
Copyright 2024 Alexander Lee <chlx.bsmt@gmail.com> 

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
#include "quantum.h"

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up
  setPinOutput(B2);
  setPinOutput(B0);
  matrix_init_user();
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B2, !led_state.caps_lock);
        writePin(B0, !led_state.compose);
    }
    return true;
}

void eeconfig_init_kb(void) {  // EEPROM is getting reset!
  eeconfig_update_kb(0);
  eeconfig_init_user();
}
