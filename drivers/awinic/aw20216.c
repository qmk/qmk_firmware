/* Copyright 2021 Jasper Chan
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

#include "aw20216.h"
#include "spi_master.h"

#define AWINIC_ID 0b1010

#define AW_PAGE_FUNCTION 0x00    // PG0
#define AW_PAGE_PWM 0x01         // PG1
#define AW_PAGE_SCALING 0x02     // PG2
#define AW_PAGE_PATCHOICE 0x03   // PG3
#define AW_PAGE_PWMSCALING 0x04  // PG4

#define AW_REG_CONFIGURATION 0x00 // PG0
#define AW_REG_GLOBALCURRENT 0x01 // PG0


void AW20216_init(void) {
    return;
}
void AW20216_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    return;
}
void AW20216_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    return;
}
void AW20216_update_pwm_buffers(void) {
    return;
}
