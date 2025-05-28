/* Copyright 2025 keymagichorse
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

// ------------------------ 电池分压电阻的配置 ------------------------
/* Battery voltage resistive voltage divider setting of MCU */
#ifndef BAT_R_UPPER                        
// Upper side resitor value (uint: KΩ)
#   define BAT_R_UPPER 100  
#endif
#ifndef BAT_R_LOWER    
 // Lower side resitor value (uint: KΩ)                   
#   define BAT_R_LOWER 100         
#endif
// ------------------------ 电池分压电阻的配置 ------------------------

// ------------------------ 电池电压读取的引脚 ------------------------
#ifndef BATTER_ADC_PIN                       
#    define BATTER_ADC_PIN     B1
#endif
// https://docs.qmk.fm/drivers/adc#stm32
#ifndef BATTER_ADC_DRIVER                      
#    define BATTER_ADC_DRIVER     ADCD1
#endif
// ------------------------ 电池电压读取的引脚 ------------------------

// 电池电压最高最低 mv
#define BATTER_MAX_MV   4150
#define BATTER_MIN_MV   3500
void battery_read_and_update_data(void);
void battery_percent_read_task(void);
void battery_reset_timer(void);