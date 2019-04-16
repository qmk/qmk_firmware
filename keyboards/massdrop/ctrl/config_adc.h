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

#pragma once

//ADC configuration table column indices
#define ADC_PORT        0
#define ADC_PIN         1
#define ADC_MUX         2
#define ADC_INDEX       3
#define ADC_MUXPOS      4
#define ADC_REFSEL      5
#define ADC_SAMPLENUM   6
#define ADC_SAMPLEN     7

//ADC configuration table row indices
#define ADC_5V          0   //5V bus voltage
#define ADC_C1A5        1   //Connector 1 A5 CC voltage
#define ADC_C1B5        2   //Connector 1 B5 CC voltage
#define ADC_C2A5        3   //Connector 2 A5 CC voltage
#define ADC_C2B5        4   //Connector 2 B5 CC voltage
#define ADC_C1I         5   //Connector 1 current
#define ADC_C2I         6   //Connector 2 current

//ADC_PORT: PORT of the PIN on the MCU (Ex: 0 = PA, 1 = PB, ...)
//          Set ADC_PORT to ADC_NA if it is not available for use
//ADC_PIN: PIN on the MCU (Ex: 0 = 00, 1 = 01, 12 = 12, ...)
//ADC_MUX: PMUX setting for the MCU PIN (Ex: 0 = A, 1 = B, 2 = C, ...)
//ADC_INDEX: ADC to use (Ex: 0 = ADC0, 1 = ADC1, ...)
//ADC_MUXPOS: MUXPOS setting to read on the ADC (Use macros from Atmel library adc.h ADC_INPUTCTRL_MUXPOS_AIN*_Val)
//ADC_REFSEL: Reference the ADC is to use (Use macros from Atmel library adc.h ADC_REFCTRL_REFSEL_*_Val)
//ADC_SAMPLENUM: Number of samples to average for output (Use macros from Atmel library adc.h ADC_AVGCTRL_SAMPLENUM_*_Val)
//ADC_SAMPLEN: Sampling time for each sample in units of CLK_ADC cycles depending on the ADC clock frequency
//                      ADC_PORT    ADC_MUX
//                      |  ADC_PIN  |  ADC_INDEX
//                      |       |   |  |  ADC_MUXPOS                      ADC_REFSEL                      ADC_SAMPLENUM                   ADC_SAMPLEN
#define ADC_CONFIG_5V   1,      0,  1, 0, ADC_INPUTCTRL_MUXPOS_AIN12_Val, ADC_REFCTRL_REFSEL_INTREF_Val,  ADC_AVGCTRL_SAMPLENUM_4_Val,    45
#define ADC_CONFIG_C1A5 1,      2,  1, 0, ADC_INPUTCTRL_MUXPOS_AIN14_Val, ADC_REFCTRL_REFSEL_INTREF_Val,  ADC_AVGCTRL_SAMPLENUM_16_Val,   63
#define ADC_CONFIG_C1B5 ADC_NA, 0,  0, 0, 0,                              0,                              0,                              0
#define ADC_CONFIG_C2A5 1,      1,  1, 0, ADC_INPUTCTRL_MUXPOS_AIN13_Val, ADC_REFCTRL_REFSEL_INTREF_Val,  ADC_AVGCTRL_SAMPLENUM_16_Val,   63
#define ADC_CONFIG_C2B5 ADC_NA, 0,  0, 0, 0,                              0,                              0,                              0
#define ADC_CONFIG_C1I  ADC_NA, 0,  0, 0, 0,                              0,                              0,                              0
#define ADC_CONFIG_C2I  ADC_NA, 0,  0, 0, 0,                              0,                              0,                              0

//Conversion values dependant upon the circuitry
#define ADC_5V_VOLTS_PER_COUNT      0.001904297f
#define ADC_5V_VOLTS_OFFSET         0.0f
#define ADC_5V_NOMINAL              5.0f
#define ADC_5V_NOMINAL_COUNTS       (ADC_5V_NOMINAL / ADC_5V_VOLTS_PER_COUNT)

//Conversion macros
#define ADC_5V_C2V(icounts)         ((float)icounts * ADC_5V_VOLTS_PER_COUNT + ADC_5V_VOLTS_OFFSET)         //Converts 5V Bus counts to volts
#define ADC_5V_V2C(v)               (((float)v - ADC_5V_VOLTS_OFFSET) / ADC_5V_VOLTS_PER_COUNT)             //Converts 5V Bus volts to counts
#define ADC_CC_5VCOR(v5counts, cc)  ((float)v5counts == 0 ? 0 : ADC_5V_NOMINAL_COUNTS / (float)v5counts * (float)cc) //Corrects CC counts to nominal 5V value

#define ADC_USBC_EXTRA_NOMINAL      850     //Nominal ADC value for detection of connected device

#define USBC_IS_SINK(a5, b5)        (a5 < ADC_USBC_EXTRA_NOMINAL || b5 < ADC_USBC_EXTRA_NOMINAL)

#define POWER_CHECK_INTERVAL        1       //How often to check power usage for adjustment and safety (ms)
#define V_5V_AVGS                   50      //Number of 5V readings to average for algorithms wanting stable readings rather than instantaneous
