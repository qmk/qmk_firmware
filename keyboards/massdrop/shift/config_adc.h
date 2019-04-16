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
#define ADC_CONFIG_C1A5 1,      2,  1, 0, ADC_INPUTCTRL_MUXPOS_AIN14_Val, ADC_REFCTRL_REFSEL_INTREF_Val,  ADC_AVGCTRL_SAMPLENUM_4_Val,    63
#define ADC_CONFIG_C1B5 1,      4,  1, 1, ADC_INPUTCTRL_MUXPOS_AIN6_Val,  ADC_REFCTRL_REFSEL_INTREF_Val,  ADC_AVGCTRL_SAMPLENUM_4_Val,    63
#define ADC_CONFIG_C2A5 1,      1,  1, 0, ADC_INPUTCTRL_MUXPOS_AIN13_Val, ADC_REFCTRL_REFSEL_INTREF_Val,  ADC_AVGCTRL_SAMPLENUM_4_Val,    63
#define ADC_CONFIG_C2B5 1,      5,  1, 1, ADC_INPUTCTRL_MUXPOS_AIN7_Val,  ADC_REFCTRL_REFSEL_INTREF_Val,  ADC_AVGCTRL_SAMPLENUM_4_Val,    63
#define ADC_CONFIG_C1I  0,      10, 1, 0, ADC_INPUTCTRL_MUXPOS_AIN10_Val, ADC_REFCTRL_REFSEL_INTVCC1_Val, ADC_AVGCTRL_SAMPLENUM_4_Val,    45
#define ADC_CONFIG_C2I  0,      11, 1, 0, ADC_INPUTCTRL_MUXPOS_AIN11_Val, ADC_REFCTRL_REFSEL_INTVCC1_Val, ADC_AVGCTRL_SAMPLENUM_4_Val,    45

//Conversion values dependant upon the circuitry
#define ADC_I_MILLIAMPS_PER_COUNT   -0.000980472f
#define ADC_I_MILLIAMPS_OFFSET      1.979711769f
#define ADC_5V_VOLTS_PER_COUNT      0.001904297f
#define ADC_5V_VOLTS_OFFSET         0.0f
#define ADC_5V_NOMINAL              5.0f
#define ADC_5V_NOMINAL_COUNTS       (ADC_5V_NOMINAL / ADC_5V_VOLTS_PER_COUNT)

//Conversion macros
#define ADC_CI_C2I(macounts)        ((float)macounts * ADC_I_MILLIAMPS_PER_COUNT + ADC_I_MILLIAMPS_OFFSET)          //Converts connector current counts to milliamps
#define ADC_CI_I2C(ma)              (uint16_t)((((float)ma - ADC_I_MILLIAMPS_OFFSET) / ADC_I_MILLIAMPS_PER_COUNT))  //Converts milliamps to connector current counts
#define ADC_5V_C2V(icounts)         ((float)icounts * ADC_5V_VOLTS_PER_COUNT + ADC_5V_VOLTS_OFFSET)                 //Converts 5V Bus counts to volts
#define ADC_5V_V2C(v)               (uint16_t)((((float)v - ADC_5V_VOLTS_OFFSET) / ADC_5V_VOLTS_PER_COUNT))         //Converts 5V Bus volts to counts
#define ADC_CC_5VCOR(v5counts, cc)  ((float)v5counts == 0 ? 0 : (uint16_t)(ADC_5V_NOMINAL_COUNTS / (float)v5counts * (float)cc)) //Corrects CC counts to nominal 5V value

//Note: The extra port's onboard/external range is not reliable for onboard/external detection due to varying device implementations,
//      so instead the extra port will follow the host port connection of onboard or external. We will still use
//      a nominal value for device detection with a wider range though.
#define ADC_USBC_ONBOARD            951                                             //ADC value indicating the USB-C Connector is on main PCB
#define ADC_USBC_EXTERNAL           881                                             //ADC value indicating the USB-C Connector is on external PCB
#define ADC_USBC_RANGE              ((ADC_USBC_ONBOARD - ADC_USBC_EXTERNAL) / 2)    //Range of detection for extra port Rd
#define ADC_USBC_EXTRA_NOMINAL      ((ADC_USBC_ONBOARD + ADC_USBC_EXTERNAL) / 2)    //Nominal ADC value for detection of connected device
#define ADC_USBC_EXTRA_TOLERANCE    (0.20f)                                         //Tolerance for Rd
#define ADC_USBC_EXTRA_ADC_MAX      ((float)ADC_USBC_EXTRA_NOMINAL + ((float)ADC_USBC_EXTRA_NOMINAL * ADC_USBC_EXTRA_TOLERANCE))    //Rd ADC max counts
#define ADC_USBC_EXTRA_ADC_MIN      ((float)ADC_USBC_EXTRA_NOMINAL - ((float)ADC_USBC_EXTRA_NOMINAL * ADC_USBC_EXTRA_TOLERANCE))    //Rd ADC min counts

#define USBC_IS_SINK(a5, b5)        ((a5 > ADC_USBC_EXTRA_ADC_MIN && a5 < ADC_USBC_EXTRA_ADC_MAX) || \
                                    (b5 > ADC_USBC_EXTRA_ADC_MIN && b5 < ADC_USBC_EXTRA_ADC_MAX))

#define ADC_USBC_RP_DELTA_MAX       400     //Amount of noise to tolerate for Rp detection (this can be very generous as long as ranges do not overlap)

#define ADC_USBC_RP_TYPES           3       //56k, 22k, 10k
#define ADC_USBC_CON_TYPES          2       //Onboard, External
#define ADC_USBC_TYPES              (ADC_USBC_RP_TYPES * ADC_USBC_CON_TYPES)

//These are the indices for ADC_USBC_RP_NOM
//xxK is a ADC_USBC_RP_TYPES
//ONB is for the onboard USB-C Connector and must have an even index number
//EXT is for the external USB-C Connector and must have an odd index number
#define ADC_USBC_56K_ONB            0
#define ADC_USBC_56K_EXT            1
#define ADC_USBC_22K_ONB            2
#define ADC_USBC_22K_EXT            3
#define ADC_USBC_10K_ONB            4
#define ADC_USBC_10K_EXT            5

#define ADC_USBC_IS_ONB(a)          (a % 2 == 0)      //Given a ADC_USBC_RP_NOM index, return true if the index refers to an onboard connector
#define ADC_USBC_IS_EXT(a)          (a % 2 == 1)      //Given a ADC_USBC_RP_NOM index, return true if the index refers to an external connector

//These values are for detecting whether or not the host is connected through the onboard USB or external USB
//The counts are calculated from a nominal 5V bus, then scaled depending on the measured 5V bus
//External connectors are detected through addition of a resistor to slightly drop readings while remaining within USB-C CC tolerances
//Set a value to -1 if it is not supported
//Source Rp                         56k-Onb 56k-Ext 22k-Onb 22k-Ext 10k-Onb 10k-Ext
#define ADC_USBC_RP_NOM             999,    852,    2232,   1940,   3955,   3528

extern uint16_t adc_usbc_rp_nominal[ADC_USBC_TYPES];

#define POWER_CHECK_INTERVAL        1       //How often to check power usage for adjustment and safety (ms)
#define V_5V_AVGS                   20      //Number of 5V readings to average for algorithms wanting stable readings rather than instantaneous
