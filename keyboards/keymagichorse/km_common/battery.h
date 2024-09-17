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

#pragma once
#include "quantum.h"
#include "gpio.h"
#include "analog.h"

/* Battery voltage resistive voltage divider setting of MCU */
#ifndef R_UPPER                        
#   define R_UPPER 100  // Upper side resitor value (uint: KΩ)
#endif

#ifndef R_LOWER                       
#   define R_LOWER 100          // Lower side resitor value (uint: KΩ)
#endif


#ifndef BATTER_ADC_PIN                       
#    define BATTER_ADC_PIN     B1
#endif
// https://docs.qmk.fm/drivers/adc#stm32
#ifndef BATTER_ADC_DRIVER                      
#    define BATTER_ADC_DRIVER     ADCD1
#endif



#ifndef VOLTAGE_MEASURE_INTERVAL
#    define VOLTAGE_MEASURE_INTERVAL 3000
#endif



void battery_init(void);
void battery_stop(void);
void battery_task(void);
