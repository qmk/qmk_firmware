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

#include "battery.h"
#include "gpio.h"
#include "analog.h"
#include "km_printf.h"
#include "bhq.h"


// TODO: The MCU is reserved for reading battery voltage interfaces
uint32_t battery_timer_buffer = 0;
void battery_init(void)
{
    battery_timer_buffer = 0;
}


void battery_stop(void)
{
}

uint16_t battery_adc_read(void)
{
    return 0;
}


void battery_task(void)
{
 
}