/* Copyright 2024 keymagichorse
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
void board_init(void) {


    // 禁用调试功能以降低功耗
    DBGMCU->CR &= ~DBGMCU_CR_DBG_SLEEP;   // 禁用在Sleep模式下的调试
    DBGMCU->CR &= ~DBGMCU_CR_DBG_STOP;    // 禁用在Stop模式下的调试
    DBGMCU->CR &= ~DBGMCU_CR_DBG_STANDBY; // 禁用在Standby模式下的调试
    // 在系统初始化代码中禁用SWD接口
    palSetLineMode(A13, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(A14, PAL_MODE_INPUT_ANALOG);



    palSetLineMode(A0, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A1, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A2, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A3, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A4, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A5, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A6, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A7, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A8, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A9, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A10, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A11, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A13, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A14, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(A15, PAL_MODE_INPUT_ANALOG); 

    palSetLineMode(B0, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B1, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B2, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B3, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B4, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B5, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B6, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B7, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B8, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B9, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B10, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B11, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B13, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B14, PAL_MODE_INPUT_ANALOG); 
    palSetLineMode(B15, PAL_MODE_INPUT_ANALOG); 



}


#ifdef RGBLIGHT_ENABLE



bool led_update_kb(led_t led_state) {
    return true;
}

void keyboard_post_init_kb(void) {
}

#endif
