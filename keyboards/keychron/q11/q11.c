/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

// Mask out handedness diode to prevent it
// from keeping the keyboard awake
// - just mirroring `KC_NO` in the `LAYOUT`
//   macro to keep it simple
const matrix_row_t matrix_mask[] = {
    0b011111111,
    0b011111111,
    0b011111111,
    0b001111111,
    0b011111101,
    0b001011111,
    0b111111111,
    0b101111111,
    0b111111111,
    0b110111111,
    0b010111111,
    0b111011110,
};

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? 0 : 2));
    }
    return true;
}
#endif

#if defined(RGB_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX)
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_enable();
            }
            return false;
    }
    return true;
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    // RGB_MATRIX_INDICATOR_SET_COLOR(index, red, green, blue);
#    if defined(CAPS_LOCK_LED_INDEX)
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        }
    }
#    endif // CAPS_LOCK_LED_INDEX
#    if defined(NUM_LOCK_LED_INDEX)
    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_LED_INDEX, 0, 0, 0);
        }
    }
#    endif // NUM_LOCK_LED_INDEX
    return true;
}
#endif

#define ADC_BUFFER_DEPTH 1
#define ADC_NUM_CHANNELS 1
#define ADC_SAMPLING_RATE ADC_SMPR_SMP_12P5
#define ADC_RESOLUTION ADC_CFGR_RES_10BITS

static int16_t analogReadPin_my(pin_t pin) {
    ADCConfig          adcCfg = {};
    adcsample_t        sampleBuffer[ADC_NUM_CHANNELS * ADC_BUFFER_DEPTH];
    ADCDriver         *targetDriver       = &ADCD1;
    ADCConversionGroup adcConversionGroup = {
        .circular     = FALSE,
        .num_channels = (uint16_t)(ADC_NUM_CHANNELS),
        .cfgr         = ADC_RESOLUTION,
    };

    palSetLineMode(pin, PAL_MODE_INPUT_ANALOG);
    switch (pin) {
        case B0:
            adcConversionGroup.smpr[2] = ADC_SMPR2_SMP_AN15(ADC_SAMPLING_RATE);
            adcConversionGroup.sqr[0]  = ADC_SQR1_SQ1_N(ADC_CHANNEL_IN15);
            sampleBuffer[0]            = 0;
            break;
        case B1:
            adcConversionGroup.smpr[2] = ADC_SMPR2_SMP_AN16(ADC_SAMPLING_RATE);
            adcConversionGroup.sqr[0]  = ADC_SQR1_SQ1_N(ADC_CHANNEL_IN16);
            sampleBuffer[0]            = 0;
            break;
        default:
            return 0;
    }
    adcStart(targetDriver, &adcCfg);
    if (adcConvert(targetDriver, &adcConversionGroup, &sampleBuffer[0], ADC_BUFFER_DEPTH) != MSG_OK) {
        return 0;
    }

    return *sampleBuffer;
}

void keyboard_post_init_kb(void) {
    // 1. The pin A5/B5 of the USB C interface in the left hand is connected to the pin A0 of MCU,
    // A0 will be set to output and write high when keyboard initial.
    // 2. The same pin in the right hand is connected to the pin B0 and B1 of MCU respectively,
    // and the ADC function of B0 and B1 will be enabled when keyboard initial.
    // 3. because the serial usart RXD and TXD is multiplexed on USB's D+ and D- in the right hand.
    // So detect the voltage on the pin A5/B5 of the USB C interface by ADC,
    // and disable USB connectivity when the ADC value exceeds 1000,
    // to avoid affecting the serial usart communication between the left hand and the right hand.
    if (is_keyboard_left()) {
        setPinOutput(A0);
        writePinHigh(A0);
    } else {
        if ((analogReadPin_my(B0) > 1000) || (analogReadPin_my(B1) > 1000)) {
            setPinInput(A11);
            setPinInput(A12);
        }
    }

    keyboard_post_init_user();
}
