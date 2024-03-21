/* Copyright 2019 Ethan Durrant (emdarcher)
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

#include "quantum.h"

#define LED1_PIN    C4
#define LED2_PIN    C5

void keyboard_pre_init_kb(void){
    //init the LED pins as outputs
    setPinOutput(LED1_PIN);
    setPinOutput(LED2_PIN);
    //call any user initialization code
    keyboard_pre_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res){
        //write the CAPS LOCK state on LED1
        writePin(LED1_PIN, led_state.caps_lock);
    }
    return res;
}
