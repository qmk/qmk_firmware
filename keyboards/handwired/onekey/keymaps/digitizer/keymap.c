 /* Copyright 2021 QMK 
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

#include "digitizer.h"

#include "math.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {LAYOUT_ortho_1x1(KC_A)};

uint32_t timer = 0;

void matrix_scan_user() {
    if (timer_elapsed32(timer) < 200) {
        return;
    }
    
    timer               = timer_read32();
    digitizer_t digitizer;
    digitizer.x         = 0.5 - 0.2 * cos(timer_read() / 250. / 6.28);
    digitizer.y         = 0.5 - 0.2 * sin(timer_read() / 250. / 6.28);
    digitizer.tipswitch = 0;
    digitizer.inrange   = 1;
    digitizer_set_report(digitizer);
}
