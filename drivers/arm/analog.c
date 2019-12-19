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

#include "analog.h"
#include "quantum.h"


/* User configurable ADC options */
#ifndef ADC_CIRCULAR_BUFFER
#define ADC_CIRCULAR_BUFFER FALSE
#endif

#ifndef ADC_NUM_CHANNELS
#define ADC_NUM_CHANNELS 1
#elif ADC_NUM_CHANNELS != 1
#error "The ARM ADC implementation currently only supports reading one channel at a time."
#endif

#ifndef ADC_BUFFER_DEPTH
#define ADC_BUFFER_DEPTH 2
#endif

// For more sampling rate options, look at hal_adc_lld.h in ChibiOS
#ifndef ADC_SAMPLING_RATE
#define ADC_SAMPLING_RATE ADC_SMPR_SMP_1P5
#endif

// Options are 12, 10, 8, and 6 bit.
#ifndef ADC_RESOLUTION
#define ADC_RESOLUTION ADC_CFGR1_RES_12BIT
#endif



static ADCConfig adcCfg = {};
static adcsample_t sampleBuffer[ADC_NUM_CHANNELS * ADC_BUFFER_DEPTH];

// Initialize to max number of ADCs, set to empty object to initialize all to false.
#if defined(STM32F0XX)
static bool adcInitialized[1] = {};
#elif defined(STM32F3XX)
static bool adcInitialized[4] = {};
#else
#error "adcInitialized has not been implemented for this ARM microcontroller."
#endif



static ADCConversionGroup adcConversionGroup = {
    ADC_CIRCULAR_BUFFER,
    (uint16_t)(ADC_NUM_CHANNELS),
    NULL, // No end callback
    NULL, // No error callback
#if defined(STM32F0XX)
    ADC_CFGR1_CONT | ADC_RESOLUTION,
    ADC_TR(0, 0).
    ADC_SAMPLING_RATE,
    NULL, // Doesn't specify a default channel
#elif defined(STM32F3XX)
    ADC_CFGR_CONT | ADC_RESOLUTION,
    ADC_TR(0, 4095),
    {
        ADC_SAMPLING_RATE,
        ADC_SAMPLING_RATE,
    },
    {
        0, // Doesn't specify a default channel
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
        adcStart(adcDriver, &adcCfg);
        adcInitialized[adc] = true;
    }
}

static inline void manageAdcInitialization(uint8_t adc) {
    manageAdcInitializationDriver(adc, intToADCDriver(adc));
}

pin_and_adc pinToMux(pin_t pin) {
    switch(pin) {
        // clang-format off
#if defined(STM32F0XX)
        case A0:  return (pin_and_adc){ ADC_CHANNEL_IN0,  0 };
        case A1:  return (pin_and_adc){ ADC_CHANNEL_IN1,  0 };
        case A2:  return (pin_and_adc){ ADC_CHANNEL_IN2,  0 };
        case A3:  return (pin_and_adc){ ADC_CHANNEL_IN3,  0 };
        case A4:  return (pin_and_adc){ ADC_CHANNEL_IN4,  0 };
        case A5:  return (pin_and_adc){ ADC_CHANNEL_IN5,  0 };
        case A6:  return (pin_and_adc){ ADC_CHANNEL_IN6,  0 };
        case A7:  return (pin_and_adc){ ADC_CHANNEL_IN7,  0 };
        case B0:  return (pin_and_adc){ ADC_CHANNEL_IN8,  0 };
        case B1:  return (pin_and_adc){ ADC_CHANNEL_IN9,  0 };
        case C0:  return (pin_and_adc){ ADC_CHANNEL_IN10, 0 };
        case C1:  return (pin_and_adc){ ADC_CHANNEL_IN11, 0 };
        case C2:  return (pin_and_adc){ ADC_CHANNEL_IN12, 0 };
        case C3:  return (pin_and_adc){ ADC_CHANNEL_IN13, 0 };
        case C4:  return (pin_and_adc){ ADC_CHANNEL_IN14, 0 };
        case C5:  return (pin_and_adc){ ADC_CHANNEL_IN15, 0 };
#elif defined(STM32F3XX)
        case A0:  return (pin_and_adc){ ADC_CHANNEL_IN1,  0 };
        case A1:  return (pin_and_adc){ ADC_CHANNEL_IN2,  0 };
        case A2:  return (pin_and_adc){ ADC_CHANNEL_IN3,  0 };
        case A3:  return (pin_and_adc){ ADC_CHANNEL_IN4,  0 };
        case A4:  return (pin_and_adc){ ADC_CHANNEL_IN1,  1 };
        case A5:  return (pin_and_adc){ ADC_CHANNEL_IN2,  1 };
        case A6:  return (pin_and_adc){ ADC_CHANNEL_IN3,  1 };
        case A7:  return (pin_and_adc){ ADC_CHANNEL_IN4,  1 };
        case B0:  return (pin_and_adc){ ADC_CHANNEL_IN12, 2 };
        case B1:  return (pin_and_adc){ ADC_CHANNEL_IN1,  2 };
        case B2:  return (pin_and_adc){ ADC_CHANNEL_IN12, 1 };
        case B12: return (pin_and_adc){ ADC_CHANNEL_IN2,  3 };
        case B13: return (pin_and_adc){ ADC_CHANNEL_IN3,  3 };
        case B14: return (pin_and_adc){ ADC_CHANNEL_IN4,  3 };
        case B15: return (pin_and_adc){ ADC_CHANNEL_IN5,  3 };
        case C0:  return (pin_and_adc){ ADC_CHANNEL_IN6,  0 }; // Can also be ADC2
        case C1:  return (pin_and_adc){ ADC_CHANNEL_IN7,  0 }; // Can also be ADC2
        case C2:  return (pin_and_adc){ ADC_CHANNEL_IN8,  0 }; // Can also be ADC2
        case C3:  return (pin_and_adc){ ADC_CHANNEL_IN9,  0 }; // Can also be ADC2
        case C4:  return (pin_and_adc){ ADC_CHANNEL_IN5,  1 };
        case C5:  return (pin_and_adc){ ADC_CHANNEL_IN11, 1 };
        case D8:  return (pin_and_adc){ ADC_CHANNEL_IN12, 3 };
        case D9:  return (pin_and_adc){ ADC_CHANNEL_IN13, 3 };
        case D10: return (pin_and_adc){ ADC_CHANNEL_IN7,  2 }; // Can also be ADC4
        case D11: return (pin_and_adc){ ADC_CHANNEL_IN8,  2 }; // Can also be ADC4
        case D12: return (pin_and_adc){ ADC_CHANNEL_IN9,  2 }; // Can also be ADC4
        case D13: return (pin_and_adc){ ADC_CHANNEL_IN10, 2 }; // Can also be ADC4
        case D14: return (pin_and_adc){ ADC_CHANNEL_IN11, 2 }; // Can also be ADC4
        case E7:  return (pin_and_adc){ ADC_CHANNEL_IN13, 2 };
        case E8:  return (pin_and_adc){ ADC_CHANNEL_IN6,  2 }; // Can also be ADC4
        case E9:  return (pin_and_adc){ ADC_CHANNEL_IN2,  2 };
        case E10: return (pin_and_adc){ ADC_CHANNEL_IN14, 2 };
        case E11: return (pin_and_adc){ ADC_CHANNEL_IN15, 2 };
        case E12: return (pin_and_adc){ ADC_CHANNEL_IN16, 2 };
        case E13: return (pin_and_adc){ ADC_CHANNEL_IN3,  2 };
        case E14: return (pin_and_adc){ ADC_CHANNEL_IN1,  3 };
        case E15: return (pin_and_adc){ ADC_CHANNEL_IN2,  3 };
        case F2:  return (pin_and_adc){ ADC_CHANNEL_IN10, 0 }; // Can also be ADC2
        case F4:  return (pin_and_adc){ ADC_CHANNEL_IN5,  0 };
#else
#error "An ADC pin-to-mux configuration has not been specified for this microcontroller."
#endif
        default:  return (pin_and_adc){ 0, 0 };
        // clang-format on
    }
}

adcsample_t analogReadPin(pin_t pin) {
    return adc_read(pinToMux(pin));
}

adcsample_t analogReadPinAdc(pin_t pin, uint8_t adc) {
    pin_and_adc target = pinToMux(pin);
    target.adc = adc;
    return adc_read(target);
}

adcsample_t adc_read(pin_and_adc mux) {
#if defined(STM32F0XX)
    adcConversionGroup.sqr = ADC_CHSELR_CHSEL1;
#elif defined(STM32F3XX)
    adcConversionGroup.sqr[0] = ADC_SQR1_SQ1_N(mux.pin);
#else
#error "adc_read has not been updated to support this ARM microcontroller."
#endif

    ADCDriver* targetDriver = intToADCDriver(mux.adc);
    manageAdcInitializationDriver(mux.adc, targetDriver);

    adcConvert(targetDriver, &adcConversionGroup, &sampleBuffer[0], ADC_BUFFER_DEPTH);
    adcsample_t* result = sampleBuffer;

    return *result;
}
