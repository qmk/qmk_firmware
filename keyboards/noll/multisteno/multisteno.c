/* Copyright 2022 Nathan Olivares
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

void keyboard_pre_init_kb(void){
    // Initialize LED pins to correct setting
    gpio_set_pin_output_push_pull(A0);
    gpio_set_pin_output_push_pull(A1);
    
    keyboard_pre_init_user();
}

void matrix_init_kb(void){
    gpio_write_pin_high(A0);
    gpio_write_pin_high(A1);
    wait_ms(500);
    gpio_write_pin_low(A0);
    
    matrix_init_user();
}