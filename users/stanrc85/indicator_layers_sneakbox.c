 /* Copyright 2020 Stanrc85 
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

#include "stanrc85.h"

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(INDICATOR_PIN_2, layer_state_cmp(state, _FN2_60) || layer_state_cmp(state, _DEFAULT));
    writePin(INDICATOR_PIN_1, layer_state_cmp(state, _FN1_60) || layer_state_cmp(state, _DEFAULT));    
    return state;
}

bool led_update_user(led_t led_state) {
    writePin(INDICATOR_PIN_0, led_state.caps_lock);
    return false;
}