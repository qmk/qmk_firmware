/* Copyright 2020 bt66tech
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

#include "bt66tech60.h"
#include "ch.h"
#include "hal.h"
#include "util.h"
#include "quantum.h"

#ifdef BOARD_STM32_F103_STM32DUINO
#define LED_ON()    do { palClearPad(GPIOC, 13) ;} while (0)
#define LED_OFF()   do { palSetPad(GPIOC, 13); } while (0)
#define LED_TGL()   do { palTogglePad(GPIOC, 13); } while (0)
#else
#define LED_ON()
#define LED_OFF()
#define LED_TGL()
#endif

void matrix_init_kb(void){
    LED_ON();
    wait_ms(500);
    LED_OFF();
    matrix_init_user();
}
