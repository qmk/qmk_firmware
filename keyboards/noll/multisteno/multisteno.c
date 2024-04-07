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
#include <ch.h>
#include <hal.h>
#include "util.h"
#include "quantum.h"

#ifdef BOARD_STM32_F103_STM32DUINO

// this is fairly unnecessary
#define RED_LED_OFF()    do { palClearPad(GPIOA, 0) ;} while (0) // GPIOA1 is right green LED
#define RED_LED_ON()   do { palSetPad(GPIOA, 0); } while (0)
#define RED_LED_TGL()   do { palTogglePad(GPIOA, 0); } while (0)

#define GREEN_LED_OFF()    do { palClearPad(GPIOA, 1) ;} while (0) // GPIOA1 is right green LED
#define GREEN_LED_ON()   do { palSetPad(GPIOA, 1); } while (0)
#define GREEN_LED_TGL()   do { palTogglePad(GPIOA, 1); } while (0)

#else
#define LED_ON()
#define LED_OFF()
#define LED_TGL()
#endif

void keyboard_pre_init_user(void){
    // Initialize LED pins to correct setting
    palSetPadMode(GPIOA, 0, PAL_MODE_OUTPUT_PUSHPULL); // 6U correct
    palSetPadMode(GPIOA, 1, PAL_MODE_OUTPUT_PUSHPULL); // 6U correct

}

void matrix_init_kb(void){
    RED_LED_ON();
    GREEN_LED_ON();
    wait_ms(500);
    RED_LED_OFF();
}
