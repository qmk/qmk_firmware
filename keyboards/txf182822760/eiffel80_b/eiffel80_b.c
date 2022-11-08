/* Copyright 2020 Koichi Katano
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
#include "eiffel80_b.h"

#if 1

void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up

  setPinOutput(PE6);
  //setPinOutput(B2);
  //writePinHigh(PE6);
  //matrix_init_user();
  
  //DDRE |= (1 << 6); PORTE|= (1 << 6);
  DDRE &= ~(1 << 6); PORTE &= ~(1 << 6);

}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);

    if(res) 
    {
        #if 1
        if(!led_state.caps_lock)
        {
        	//caps_locdflag=0;
        	//setPinInputHigh(PE6);
        	//writePinHigh(PE6);
        	DDRE &= ~(1 << 6); PORTE &= ~(1 << 6);        	  
        }		
        else 
        {
        	//caps_locdflag=1;
        	//setPinInputLow(PE6);
        	//writePinLow(PE6);
        	DDRE |= (1 << 6); PORTE|= (1 << 6);
        } 
        //writePin(PE6, !led_state.caps_lock);
        #endif      
    }
    return res;
}
#endif
