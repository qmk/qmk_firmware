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

#include "quantum.h"
#include "analog.h"
#include <ch.h>
#include <hal.h>

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

// Otherwise assume V3
#if defined(STM32F0XX) || defined(STM32L0XX)
#    define USE_ADCV1
#elif defined(STM32F1XX) || defined(STM32F2XX) || defined(STM32F4XX)
#    define USE_ADCV2
#endif

// BODGE to make v2 look like v1,3 and 4
#ifdef USE_ADCV2
#    if !defined(ADC_SMPR_SMP_1P5) && defined(ADC_SAMPLE_3)
#        define ADC_SMPR_SMP_1P5 ADC_SAMPLE_3
#        define ADC_SMPR_SMP_7P5 ADC_SAMPLE_15
#        define ADC_SMPR_SMP_13P5 ADC_SAMPLE_28
#        define ADC_SMPR_SMP_28P5 ADC_SAMPLE_56
#        define ADC_SMPR_SMP_41P5 ADC_SAMPLE_84
#        define ADC_SMPR_SMP_55P5 ADC_SAMPLE_112
#        define ADC_SMPR_SMP_71P5 ADC_SAMPLE_144
#        define ADC_SMPR_SMP_239P5 ADC_SAMPLE_480
#    endif

#    if !defined(ADC_SMPR_SMP_1P5) && defined(ADC_SAMPLE_1P5)
#        define ADC_SMPR_SMP_1P5 ADC_SAMPLE_1P5
#        define ADC_SMPR_SMP_7P5 ADC_SAMPLE_7P5
#        define ADC_SMPR_SMP_13P5 ADC_SAMPLE_13P5
#        define ADC_SMPR_SMP_28P5 ADC_SAMPLE_28P5
#        define ADC_SMPR_SMP_41P5 ADC_SAMPLE_41P5
#        define ADC_SMPR_SMP_55P5 ADC_SAMPLE_55P5
#        define ADC_SMPR_SMP_71P5 ADC_SAMPLE_71P5
#        define ADC_SMPR_SMP_239P5 ADC_SAMPLE_239P5
#    endif

// we still sample at 12bit, but scale down to the requested bit range
#    define ADC_CFGR1_RES_12BIT 12
#    define ADC_CFGR1_RES_10BIT 10
#    define ADC_CFGR1_RES_8BIT 8
#    define ADC_CFGR1_RES_6BIT 6
#endif

/* User configurable ADC options */
#ifndef ADC_COUNT
#    if defined(STM32F0XX) || defined(STM32F1XX) || defined(STM32F4XX)
#        define ADC_COUNT 1
#    elif defined(STM32F3XX)
#        define ADC_COUNT 4
#    else
#        error "ADC_COUNT has not been set for this ARM microcontroller."
#    endif
#endif

#ifndef ADC_NUM_CHANNELS
#    define ADC_NUM_CHANNELS 1
#elif ADC_NUM_CHANNELS != 1
#    error "The ARM ADC implementation currently only supports reading one channel at a time."
#endif

#ifndef ADC_BUFFER_DEPTH
#    define ADC_BUFFER_DEPTH 1
#endif

// For more sampling rate options, look at hal_adc_lld.h in ChibiOS
#ifndef ADC_SAMPLING_RATE
#    define ADC_SAMPLING_RATE ADC_SMPR_SMP_1P5
#endif

// Options are 12, 10, 8, and 6 bit.
#ifndef ADC_RESOLUTION
#    define ADC_RESOLUTION ADC_CFGR1_RES_10BIT
#endif

static ADCConfig   adcCfg = {};
static adcsample_t sampleBuffer[ADC_NUM_CHANNELS * ADC_BUFFER_DEPTH];

// Initialize to max number of ADCs, set to empty object to initialize all to false.
static bool adcInitialized[ADC_COUNT] = {};

// TODO: add back TR handling???
static ADCConversionGroup adcConversionGroup = {
    .circular     = FALSE,
    .num_channels = (uint16_t)(ADC_NUM_CHANNELS),
#if defined(USE_ADCV1)
    .cfgr1 = ADC_CFGR1_CONT | ADC_RESOLUTION,
    .smpr  = ADC_SAMPLING_RATE,
#elif defined(USE_ADCV2)
#    if !defined(STM32F1XX)
    .cr2   = ADC_CR2_SWSTART,  // F103 seem very unhappy with, F401 seems very unhappy without...
#    endif
    .smpr2 = ADC_SMPR2_SMP_AN0(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN1(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN2(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN3(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN4(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN5(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN6(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN7(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN8(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN9(ADC_SAMPLING_RATE),
    .smpr1 = ADC_SMPR1_SMP_AN10(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN11(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN12(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN13(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN14(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN15(ADC_SAMPLING_RATE),
#else
    .cfgr = ADC_CFGR_CONT | ADC_RESOLUTION,
    .smpr = {ADC_SMPR1_SMP_AN0(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN1(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN2(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN3(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN4(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN5(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN6(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN7(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN8(ADC_SAMPLING_RATE) | ADC_SMPR1_SMP_AN9(ADC_SAMPLING_RATE), ADC_SMPR2_SMP_AN10(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN11(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN12(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN13(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN14(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN15(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN16(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN17(ADC_SAMPLING_RATE) | ADC_SMPR2_SMP_AN18(ADC_SAMPLING_RATE)},
#endif
};

// clang-format off
__attribute__((weak)) adc_mux pinToMux(pin_t pin) {
    switch (pin) {
#if defined(STM32F0XX)
        case A0:  return TO_MUX( ADC_CHSELR_CHSEL0,  0 );
        case A1:  return TO_MUX( ADC_CHSELR_CHSEL1,  0 );
        case A2:  return TO_MUX( ADC_CHSELR_CHSEL2,  0 );
        case A3:  return TO_MUX( ADC_CHSELR_CHSEL3,  0 );
        case A4:  return TO_MUX( ADC_CHSELR_CHSEL4,  0 );
        case A5:  return TO_MUX( ADC_CHSELR_CHSEL5,  0 );
        case A6:  return TO_MUX( ADC_CHSELR_CHSEL6,  0 );
        case A7:  return TO_MUX( ADC_CHSELR_CHSEL7,  0 );
        case B0:  return TO_MUX( ADC_CHSELR_CHSEL8,  0 );
        case B1:  return TO_MUX( ADC_CHSELR_CHSEL9,  0 );
        case C0:  return TO_MUX( ADC_CHSELR_CHSEL10, 0 );
        case C1:  return TO_MUX( ADC_CHSELR_CHSEL11, 0 );
        case C2:  return TO_MUX( ADC_CHSELR_CHSEL12, 0 );
        case C3:  return TO_MUX( ADC_CHSELR_CHSEL13, 0 );
        case C4:  return TO_MUX( ADC_CHSELR_CHSEL14, 0 );
        case C5:  return TO_MUX( ADC_CHSELR_CHSEL15, 0 );
#elif defined(STM32F3XX)
        case A0:  return TO_MUX( ADC_CHANNEL_IN1,  0 );
        case A1:  return TO_MUX( ADC_CHANNEL_IN2,  0 );
        case A2:  return TO_MUX( ADC_CHANNEL_IN3,  0 );
        case A3:  return TO_MUX( ADC_CHANNEL_IN4,  0 );
        case A4:  return TO_MUX( ADC_CHANNEL_IN1,  1 );
        case A5:  return TO_MUX( ADC_CHANNEL_IN2,  1 );
        case A6:  return TO_MUX( ADC_CHANNEL_IN3,  1 );
        case A7:  return TO_MUX( ADC_CHANNEL_IN4,  1 );
        case B0:  return TO_MUX( ADC_CHANNEL_IN12, 2 );
        case B1:  return TO_MUX( ADC_CHANNEL_IN1,  2 );
        case B2:  return TO_MUX( ADC_CHANNEL_IN12, 1 );
        case B12: return TO_MUX( ADC_CHANNEL_IN2,  3 );
        case B13: return TO_MUX( ADC_CHANNEL_IN3,  3 );
        case B14: return TO_MUX( ADC_CHANNEL_IN4,  3 );
        case B15: return TO_MUX( ADC_CHANNEL_IN5,  3 );
        case C0:  return TO_MUX( ADC_CHANNEL_IN6,  0 ); // Can also be ADC2
        case C1:  return TO_MUX( ADC_CHANNEL_IN7,  0 ); // Can also be ADC2
        case C2:  return TO_MUX( ADC_CHANNEL_IN8,  0 ); // Can also be ADC2
        case C3:  return TO_MUX( ADC_CHANNEL_IN9,  0 ); // Can also be ADC2
        case C4:  return TO_MUX( ADC_CHANNEL_IN5,  1 );
        case C5:  return TO_MUX( ADC_CHANNEL_IN11, 1 );
        case D8:  return TO_MUX( ADC_CHANNEL_IN12, 3 );
        case D9:  return TO_MUX( ADC_CHANNEL_IN13, 3 );
        case D10: return TO_MUX( ADC_CHANNEL_IN7,  2 ); // Can also be ADC4
        case D11: return TO_MUX( ADC_CHANNEL_IN8,  2 ); // Can also be ADC4
        case D12: return TO_MUX( ADC_CHANNEL_IN9,  2 ); // Can also be ADC4
        case D13: return TO_MUX( ADC_CHANNEL_IN10, 2 ); // Can also be ADC4
        case D14: return TO_MUX( ADC_CHANNEL_IN11, 2 ); // Can also be ADC4
        case E7:  return TO_MUX( ADC_CHANNEL_IN13, 2 );
        case E8:  return TO_MUX( ADC_CHANNEL_IN6,  2 ); // Can also be ADC4
        case E9:  return TO_MUX( ADC_CHANNEL_IN2,  2 );
        case E10: return TO_MUX( ADC_CHANNEL_IN14, 2 );
        case E11: return TO_MUX( ADC_CHANNEL_IN15, 2 );
        case E12: return TO_MUX( ADC_CHANNEL_IN16, 2 );
        case E13: return TO_MUX( ADC_CHANNEL_IN3,  2 );
        case E14: return TO_MUX( ADC_CHANNEL_IN1,  3 );
        case E15: return TO_MUX( ADC_CHANNEL_IN2,  3 );
        case F2:  return TO_MUX( ADC_CHANNEL_IN10, 0 ); // Can also be ADC2
        case F4:  return TO_MUX( ADC_CHANNEL_IN5,  0 );
#elif defined(STM32F4XX) // TODO: add all pins
        case A0:  return TO_MUX( ADC_CHANNEL_IN0,  0 );
        //case A1:  return TO_MUX( ADC_CHANNEL_IN1,  0 );
#elif defined(STM32F1XX) // TODO: add all pins
        case A0:  return TO_MUX( ADC_CHANNEL_IN0,  0 );
#endif
    }

    // return an adc that would never be used so intToADCDriver will bail out
    return TO_MUX(0, 0xFF);
}
// clang-format on

static inline ADCDriver* intToADCDriver(uint8_t adcInt) {
    switch (adcInt) {
#if STM32_ADC_USE_ADC1
        case 0:
            return &ADCD1;
#endif
#if STM32_ADC_USE_ADC2
        case 1:
            return &ADCD2;
#endif
#if STM32_ADC_USE_ADC3
        case 2:
            return &ADCD3;
#endif
#if STM32_ADC_USE_ADC4
        case 3:
            return &ADCD4;
#endif
    }

    return NULL;
}

static inline void manageAdcInitializationDriver(uint8_t adc, ADCDriver* adcDriver) {
    if (!adcInitialized[adc]) {
        adcStart(adcDriver, &adcCfg);
        adcInitialized[adc] = true;
    }
}

int16_t analogReadPin(pin_t pin) {
    palSetLineMode(pin, PAL_MODE_INPUT_ANALOG);

    return adc_read(pinToMux(pin));
}

int16_t analogReadPinAdc(pin_t pin, uint8_t adc) {
    palSetLineMode(pin, PAL_MODE_INPUT_ANALOG);

    adc_mux target = pinToMux(pin);
    target.adc     = adc;
    return adc_read(target);
}

int16_t adc_read(adc_mux mux) {
#if defined(USE_ADCV1)
    // TODO: fix previous assumption of only 1 input...
    adcConversionGroup.chselr = 1 << mux.input; /*no macro to convert N to ADC_CHSELR_CHSEL1*/
#elif defined(USE_ADCV2)
    adcConversionGroup.sqr3 = ADC_SQR3_SQ1_N(mux.input);
#else
    adcConversionGroup.sqr[0] = ADC_SQR1_SQ1_N(mux.input);
#endif

    ADCDriver* targetDriver = intToADCDriver(mux.adc);
    if (!targetDriver) {
        return 0;
    }

    manageAdcInitializationDriver(mux.adc, targetDriver);
    if (adcConvert(targetDriver, &adcConversionGroup, &sampleBuffer[0], ADC_BUFFER_DEPTH) != MSG_OK) {
        return 0;
    }

#ifdef USE_ADCV2
    // fake 12-bit -> N-bit scale
    return (*sampleBuffer) >> (12 - ADC_RESOLUTION);
#else
    // already handled as part of adcConvert
    return *sampleBuffer;
#endif
}
