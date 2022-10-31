/*
Copyright 2018 Massdrop Inc.

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

#define ADC_5V_START_LEVEL 2365

#define ADC_5V ADC_INPUTCTRL_MUXPOS_AIN12_Val
#define ADC_CON1 ADC_INPUTCTRL_MUXPOS_AIN14_Val
#define ADC_CON2 ADC_INPUTCTRL_MUXPOS_AIN13_Val

extern uint16_t v_5v;
extern uint16_t v_5v_avg;
extern uint16_t v_con_1;
extern uint16_t v_con_2;
extern uint16_t v_con_1_boot;
extern uint16_t v_con_2_boot;

void ADC0_clock_init(void);
void ADC0_init(void);

#endif //_ADC_H_
