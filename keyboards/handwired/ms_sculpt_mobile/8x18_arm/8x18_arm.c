/*
 * Copyright 2021 QMK
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


#include "8x18_arm.h"

void keyboard_pre_init_kb(void) {
    // init the CAPS LOCK LED pin as an output
    setPinOutput(STM32LED);

    // call any user initialization code
    keyboard_pre_init_user();
}


void boardInit(void){
	// initialize anything that needs ChibiOS
	
    // disable JTAG  to enable PB3 and PB4
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_DISABLE;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(STM32LED, !led_state.caps_lock);
    }
    return res;
}
