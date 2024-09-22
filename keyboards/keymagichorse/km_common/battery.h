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



// Configure the BHQ module to read the battery voltage
#ifndef BHQ_READ_VOLTAGE_ENABLED          
#   define BHQ_READ_VOLTAGE_ENABLED TRUE
#endif
// BHUpper side resitor value (uint: KΩ)
#ifndef BHQ_R_UPPER                        
#   define BHQ_R_UPPER 100 
#endif
// Lower side resitor value (uint: KΩ)
#ifndef BHQ_R_LOWER                       
#   define BHQ_R_LOWER 100          
#endif


// #ifndef BATTER_ADC_PIN                       
// #    define BATTER_ADC_PIN     B1
// #endif
// // https://docs.qmk.fm/drivers/adc#stm32
// #ifndef BATTER_ADC_DRIVER                      
// #    define BATTER_ADC_DRIVER     ADCD1
// #endif



// #ifndef VOLTAGE_MEASURE_INTERVAL
// #    define VOLTAGE_MEASURE_INTERVAL 3000
// #endif



void battery_init(void);
void battery_stop(void);
void battery_task(void);
