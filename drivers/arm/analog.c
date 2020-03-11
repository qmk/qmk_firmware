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
#include "ch.h"
#include <hal.h>

// #if !defined(STM32F0XX) && !defined(STM32F3XX)
// #    error "Only STM23F0 and STM32F3 devices have ADC support in QMK at this time."
// #endif

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

/* User configurable ADC options */
#ifndef ADC_CIRCULAR_BUFFER
#    define ADC_CIRCULAR_BUFFER FALSE
#endif

#ifndef ADC_NUM_CHANNELS
#    define ADC_NUM_CHANNELS 1
#elif ADC_NUM_CHANNELS != 1
#    error "The ARM ADC implementation currently only supports reading one channel at a time."
#endif

#ifndef ADC_BUFFER_DEPTH
#    define ADC_BUFFER_DEPTH 8
#endif

// otherwise assume V3
#if defined(STM32F0XX) || defined(STM32L0XX)
#    define USE_ADCV1
#elif defined(STM32F1XX) || defined(STM32F4XX)
#    define USE_ADCV2
#endif

#ifndef ADC_COUNT
#    if defined(STM32F0XX) || defined(STM32F1XX) || defined(STM32F4XX)
#        define ADC_COUNT 1
#    elif defined(STM32F3XX)
#        define ADC_COUNT 4
#    else
#        error "ADC_COUNT has not been set for this ARM microcontroller."
#    endif
#endif

// BODGE to make v2 look like v1,3 and 4
#ifdef USE_ADCV2
// #define ADC_SMPR_SMP_1P5        ADC_SAMPLE_3
// #define ADC_SMPR_SMP_7P5        ADC_SAMPLE_15
// #define ADC_SMPR_SMP_13P5       ADC_SAMPLE_28
// #define ADC_SMPR_SMP_28P5       ADC_SAMPLE_56
// #define ADC_SMPR_SMP_41P5       ADC_SAMPLE_84
// #define ADC_SMPR_SMP_55P5       ADC_SAMPLE_112
// #define ADC_SMPR_SMP_71P5       ADC_SAMPLE_144
// #define ADC_SMPR_SMP_239P5      ADC_SAMPLE_480

// we still sample at 12bit, but scale down to the requested bit range
#define ADC_CFGR1_RES_12BIT     12
#define ADC_CFGR1_RES_10BIT     10
#define ADC_CFGR1_RES_8BIT      8
#define ADC_CFGR1_RES_6BIT      6
#endif

// For more sampling rate options, look at hal_adc_lld.h in ChibiOS
#ifndef ADC_SAMPLING_RATE
#    define ADC_SAMPLING_RATE ADC_SMPR_SMP_1P5
#endif

// Options are 12, 10, 8, and 6 bit.
#ifndef ADC_RESOLUTION
#    define ADC_RESOLUTION ADC_CFGR1_RES_10BIT
#endif

// #ifdef USE_ADCV2
// static 

static ADCConfig   adcCfg = {};
static adcsample_t sampleBuffer[ADC_NUM_CHANNELS * ADC_BUFFER_DEPTH];

// Initialize to max number of ADCs, set to empty object to initialize all to false.
static bool adcInitialized[ADC_COUNT] = {};

typedef struct {
    pin_t   pin;
    adc_mux mux;
} pin_to_mux;

__attribute__((weak)) const pin_to_mux pin_to_mux_lookup[] = {
// clang-format off
#if defined(STM32F0XX)
    A0,  TO_MUX( ADC_CHANNEL_IN0,  0 ),
    A1,  TO_MUX( ADC_CHANNEL_IN1,  0 ),
    A2,  TO_MUX( ADC_CHANNEL_IN2,  0 ),
    A3,  TO_MUX( ADC_CHANNEL_IN3,  0 ),
    A4,  TO_MUX( ADC_CHANNEL_IN4,  0 ),
    A5,  TO_MUX( ADC_CHANNEL_IN5,  0 ),
    A6,  TO_MUX( ADC_CHANNEL_IN6,  0 ),
    A7,  TO_MUX( ADC_CHANNEL_IN7,  0 ),
    B0,  TO_MUX( ADC_CHANNEL_IN8,  0 ),
    B1,  TO_MUX( ADC_CHANNEL_IN9,  0 ),
    C0,  TO_MUX( ADC_CHANNEL_IN10, 0 ),
    C1,  TO_MUX( ADC_CHANNEL_IN11, 0 ),
    C2,  TO_MUX( ADC_CHANNEL_IN12, 0 ),
    C3,  TO_MUX( ADC_CHANNEL_IN13, 0 ),
    C4,  TO_MUX( ADC_CHANNEL_IN14, 0 ),
    C5,  TO_MUX( ADC_CHANNEL_IN15, 0 ),
#elif defined(STM32F3XX)
    A0,  TO_MUX( ADC_CHANNEL_IN1,  0 ),
    A1,  TO_MUX( ADC_CHANNEL_IN2,  0 ),
    A2,  TO_MUX( ADC_CHANNEL_IN3,  0 ),
    A3,  TO_MUX( ADC_CHANNEL_IN4,  0 ),
    A4,  TO_MUX( ADC_CHANNEL_IN1,  1 ),
    A5,  TO_MUX( ADC_CHANNEL_IN2,  1 ),
    A6,  TO_MUX( ADC_CHANNEL_IN3,  1 ),
    A7,  TO_MUX( ADC_CHANNEL_IN4,  1 ),
    B0,  TO_MUX( ADC_CHANNEL_IN12, 2 ),
    B1,  TO_MUX( ADC_CHANNEL_IN1,  2 ),
    B2,  TO_MUX( ADC_CHANNEL_IN12, 1 ),
    B12, TO_MUX( ADC_CHANNEL_IN2,  3 ),
    B13, TO_MUX( ADC_CHANNEL_IN3,  3 ),
    B14, TO_MUX( ADC_CHANNEL_IN4,  3 ),
    B15, TO_MUX( ADC_CHANNEL_IN5,  3 ),
    C0,  TO_MUX( ADC_CHANNEL_IN6,  0 ), // Can also be ADC2
    C1,  TO_MUX( ADC_CHANNEL_IN7,  0 ), // Can also be ADC2
    C2,  TO_MUX( ADC_CHANNEL_IN8,  0 ), // Can also be ADC2
    C3,  TO_MUX( ADC_CHANNEL_IN9,  0 ), // Can also be ADC2
    C4,  TO_MUX( ADC_CHANNEL_IN5,  1 ),
    C5,  TO_MUX( ADC_CHANNEL_IN11, 1 ),
    D8,  TO_MUX( ADC_CHANNEL_IN12, 3 ),
    D9,  TO_MUX( ADC_CHANNEL_IN13, 3 ),
    D10, TO_MUX( ADC_CHANNEL_IN7,  2 ), // Can also be ADC4
    D11, TO_MUX( ADC_CHANNEL_IN8,  2 ), // Can also be ADC4
    D12, TO_MUX( ADC_CHANNEL_IN9,  2 ), // Can also be ADC4
    D13, TO_MUX( ADC_CHANNEL_IN10, 2 ), // Can also be ADC4
    D14, TO_MUX( ADC_CHANNEL_IN11, 2 ), // Can also be ADC4
    E7,  TO_MUX( ADC_CHANNEL_IN13, 2 ),
    E8,  TO_MUX( ADC_CHANNEL_IN6,  2 ), // Can also be ADC4
    E9,  TO_MUX( ADC_CHANNEL_IN2,  2 ),
    E10, TO_MUX( ADC_CHANNEL_IN14, 2 ),
    E11, TO_MUX( ADC_CHANNEL_IN15, 2 ),
    E12, TO_MUX( ADC_CHANNEL_IN16, 2 ),
    E13, TO_MUX( ADC_CHANNEL_IN3,  2 ),
    E14, TO_MUX( ADC_CHANNEL_IN1,  3 ),
    E15, TO_MUX( ADC_CHANNEL_IN2,  3 ),
    F2,  TO_MUX( ADC_CHANNEL_IN10, 0 ), // Can also be ADC2
    F4,  TO_MUX( ADC_CHANNEL_IN5,  0 ),
#elif defined(STM32F4XX) // TODO: add all pins
    A0,  TO_MUX( ADC_CHANNEL_IN0,  0 ),
#elif defined(STM32F1XX) // TODO: add all pins
    A0,  TO_MUX( ADC_CHANNEL_IN0,  0 ),
#endif
    // clang-format on
};
#define pin_to_mux_lookup_len (sizeof(pin_to_mux_lookup) / sizeof(pin_to_mux_lookup[0]))

static ADCConversionGroup adcConversionGroup = {
    ADC_CIRCULAR_BUFFER,
    (uint16_t)(ADC_NUM_CHANNELS),
    NULL,  // No end callback
    NULL,  // No error callback
#if defined(USE_ADCV1)
    ADC_CFGR1_CONT | ADC_RESOLUTION,
    ADC_TR(0, 0),
    0/*ADC_SAMPLING_RATE*/,
    NULL,  // Doesn't specify a default channel
#elif defined(STM32F1XX)
    0,
    0,
    0,
    0,
    0,
    0,
    0,
#elif defined(USE_ADCV2)
    0,
    ADC_CR2_SWSTART,
    0,
    ADC_SMPR2_SMP_AN0(ADC_SAMPLE_3),
    0, 0, // TR
    0,
    0,
    0,
#else
    ADC_CFGR_CONT | ADC_RESOLUTION,
    ADC_TR(0, 0),
    {
        0/*ADC_SAMPLING_RATE*/,
        0/*ADC_SAMPLING_RATE*/,
    },
    {
        0,  // Doesn't specify a default channel
        0,
        0,
        0,
    },
#endif
};

static inline ADCDriver* intToADCDriver(uint8_t adcInt) {
    ADCDriver* target;

    switch (adcInt) {
        // clang-format off
#if STM32_ADC_USE_ADC1
        case 0: target = &ADCD1; break;
#endif
#if STM32_ADC_USE_ADC2
        case 1: target = &ADCD2; break;
#endif
#if STM32_ADC_USE_ADC3
        case 2: target = &ADCD3; break;
#endif
#if STM32_ADC_USE_ADC4
        case 3: target = &ADCD4; break;
#endif
        default: target = NULL; break;
            // clang-format on
    }

    return target;
}

static inline void manageAdcInitializationDriver(uint8_t adc, ADCDriver* adcDriver) {
    if (!adcInitialized[adc]) {
        printf("before adcstart\n");
        adcStart(adcDriver, &adcCfg);
        printf("after adcstart\n");
        adcInitialized[adc] = true;
    }
}

//static inline void manageAdcInitialization(uint8_t adc) { manageAdcInitializationDriver(adc, intToADCDriver(adc)); }

adc_mux pinToMux(pin_t pin) {
    for (uint8_t index = 0; index < pin_to_mux_lookup_len; index++) {
        const pin_to_mux cur = pin_to_mux_lookup[index];
        if (cur.pin == pin) {
            printf("found pin!!\n");
            return cur.mux;
        }
    }

    // TODO: better error case
    printf("failed to find pin...\n");
    return TO_MUX(0, 0);
}

int16_t analogReadPin(pin_t pin) {
    //palSetGroupMode(GPIOA, PAL_PORT_BIT(0) | PAL_PORT_BIT(1), 0, PAL_MODE_INPUT_ANALOG);

    return adc_read(pinToMux(pin));
}

int16_t analogReadPinAdc(pin_t pin, uint8_t adc) {
    adc_mux target = pinToMux(pin);
    target.adc     = adc;
    return adc_read(target);
}

int16_t adc_read(adc_mux mux) {
#if defined(USE_ADCV1)
    adcConversionGroup.sqr = ADC_CHSELR_CHSEL1;
#elif defined(USE_ADCV2)
    adcConversionGroup.sqr3 = ADC_SQR3_SQ1_N(mux.input);
#else
    adcConversionGroup.sqr[0] = ADC_SQR1_SQ1_N(mux.input);
#endif

    ADCDriver* targetDriver = intToADCDriver(mux.adc);
    manageAdcInitializationDriver(mux.adc, targetDriver);

printf("before adcConvert\n");
    if(adcConvert(targetDriver, &adcConversionGroup, &sampleBuffer[0], ADC_BUFFER_DEPTH) != MSG_OK)
        return -1;

    adcsample_t result = *sampleBuffer;
printf("after ret convert\n");

#ifdef USE_ADCV2
    // fake 12-bit -> N-bit scale
    result = result >> (12 - ADC_RESOLUTION);
#endif

printf("before return\n");

    return result;
}
