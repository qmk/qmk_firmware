

void matrix_init_kb(void) {
  // Keyboard start-up code goes here
  // Runs once when the firmware starts up
  matrix_init_user();
  led_init_ports();
}

void led_init_ports(void) {
   setPinOutput(B5);
   setPinOutput(B6);
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B6, led_state.caps_lock);
        writePin(B5, led_state.scroll_lock);
    }
    return true;
}
/* Copyright 2021 UTDKeyboard 
 * 
 * this program is free software: you can redistribute it and/or modify 
 * it under the terms of the gnu general public license as published by 
 * the free software foundation, either version 2 of the license, or 
 * (at your option) any later version. 
 * 
 * this program is distributed in the hope that it will be useful, 
 * but without any warranty; without even the implied warranty of 
 * merchantability or fitness for a particular purpose.  see the 
 * gnu general public license for more details. 
 * 
 * you should have received a copy of the gnu general public license 
 * along with this program.  if not, see <http://www.gnu.org/licenses/>. 
 */ 
#include "utd80.h"
