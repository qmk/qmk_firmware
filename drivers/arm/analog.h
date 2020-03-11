/* Copyright 2019 Drew Mills
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
#include "ch.h"
#include <hal.h>

#if !defined(STM32F0XX) && !defined(STM32F3XX)
#    error "Only STM23F0 and STM32F3 devices have ADC support in QMK at this time."
#endif

#if !HAL_USE_ADC
#    error "You need to set HAL_USE_ADC to TRUE in your halconf.h to use the ADC."
#endif

#if !STM32_ADC_USE_ADC1 && !STM32_ADC_USE_ADC2 && !STM32_ADC_USE_ADC3 && !STM32_ADC_USE_ADC4
#    error "You need to set one of the 'STM32_ADC_USE_ADCx' settings to TRUE in your mcuconf.h to use the ADC."
#endif

#if STM32_ADC_DUAL_MODE
#    error "STM32 ADC Dual Mode is not supported at this time."
#endif

#if STM32_ADCV3_OVERSAMPLING
#    error "STM32 ADCV3 Oversampling is not supported at this time."
#endif

typedef struct {
    pin_t   pin;
    uint8_t adc;
} pin_and_adc;
#define PIN_AND_ADC(p, a) \
    (pin_and_adc) { p, a }

// analogReference has been left un-defined for ARM devices.
// void analogReference(uint8_t mode);

adcsample_t analogReadPin(pin_t pin);
adcsample_t analogReadPinAdc(pin_t pin, uint8_t adc);
pin_and_adc pinToMux(pin_t pin);

adcsample_t adc_read(pin_and_adc mux);
