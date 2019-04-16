/*
Copyright 2019 Massdrop Inc.

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
*/

#ifndef _ADC_H_
#define _ADC_H_

#include "config_adc.h" //From keyboard's directory

#define ADC_NA                  -1      //Value to mark an ADC as not available for use and return from an acquire
#define ADC_5V_START_LEVEL      4.75f   //In volts, system will wait until voltage is greater than this

extern uint16_t g_v_5v;
extern float g_v_5v_avg;

void ADC0_clock_init(void);
void ADC_init(void);
void ADC_configure(uint8_t adc_index);
uint16_t adc_get(uint8_t adc_id);

#endif //_ADC_H_
