/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ADC0_0 = 0,
    ADC0_1,
    ADC0_2,
    ADC0_3,
    ADC0_4,
    ADC0_5,
    ADC0_6,
    ADC0_7,
    ADC0_8,
    ADC0_9,
    ADC0_10,
    ADC0_11,
    ADC1_0,
    ADC1_1,
    ADC1_2,
    ADC1_3,
    ADC1_4,
    ADC1_5,
    ADC1_6,
    ADC1_7,
    ADC1_8,
    ADC1_9,
    ADC1_10,
    ADC1_11,
} ADCName;

typedef enum {
    DAC0_0 = 0,
} DACName;

#ifdef __cplusplus
}
#endif

#endif
