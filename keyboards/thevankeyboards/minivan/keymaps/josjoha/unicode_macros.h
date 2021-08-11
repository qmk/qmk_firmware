/*
 * License (GPL):
  
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

 * Remainder: © 2019 by J.B. <joshb@xs4all.nl>
 *
 */

#pragma once

/* This file contains function declarations for functions used in
 * unicode_macros.c
 */

#define PRESCRAMBLED_U "f"  // This is the letter 'u' for Unicode input, as effective on GNU/Debian/Linux 10 set to Dvorak
static uint16_t key_timer; // Used in _DDL to differentiate layer switching in half or full descramble mode.
                           // In 'full' mode it goes to _DDD and _DDA Unicode layers, in 'half' mode to _DRA and _ACC.

short duo_press_nsy_dra = 0; // This remembers how many of the duo-press keys are being pressed: _NSY / _DRA layers
short duo_press_acc_bon = 0; // This remembers how many of the duo-press keys are being pressed: _ACC / _BON layers

void deactivate_all_but (int layer);
void activate_this_layer (int layer);
void indicate_base (void);
void leds_show_off (void);
void speed_report (int speed);
void speed_led (int speed);
void indicate_fun_stay (void);
int write_number (long int input, short divide10); 
void isolate_rgblight_set (void);


