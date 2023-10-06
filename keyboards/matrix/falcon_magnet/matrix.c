/**
 * Copyright 2023 astro
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

#include "apc.h"
#include "analog.h"

#define LEFT_KEY_PIN A1
#define RIGHT_KEY_PIN A2
#define LEFT_KEY_CHANNEL ADC_CHANNEL_IN1
#define RIGHT_KEY_CHANNEL ADC_CHANNEL_IN2
#define ADC_GRP1_NUM_CHANNELS 2
#define ADC_GRP1_BUF_DEPTH 1

static adcsample_t samples1[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

/*
 * ADC conversion group.
 * Mode:        Linear buffer, 1 samples of 2 channel, SW triggered.
 * Channels:    IN1&IN2.
 */
static const ADCConversionGroup adcgrpcfg1 = {
    FALSE,
    ADC_GRP1_NUM_CHANNELS,
    NULL,
    NULL,
    0,               /* CR1 */
    ADC_CR2_SWSTART, /* CR2 */
    0,               /* SMPR1 */
    ADC_SMPR2_SMP_AN1(ADC_SAMPLE_3) | ADC_SMPR2_SMP_AN2(ADC_SAMPLE_3),
    0, /* HTR */
    0, /* LTR */
    0, /* SQR1 */
    0, /* SQR2 */
    ADC_SQR3_SQ1_N(ADC_CHANNEL_IN1) | ADC_SQR3_SQ2_N(ADC_CHANNEL_IN2),
};

#define COL_A_MASK 0x01
#define COL_B_MASK 0x02
#define COL_C_MASK 0x04

static pin_t custom_row_pins[] = MATRIX_ROW_PINS;
static pin_t custom_col_pins[] = MATRIX_COL_CHANNELS;

// static adc_mux left_mux;
// static adc_mux right_mux;

void matrix_init_custom(void) {
    // initialize row pins
    for (int i = 0; i < MATRIX_ROWS; i++) {
        setPinOutput(custom_row_pins[i]);
        writePinLow(custom_row_pins[i]);
    }

    // initialize col pins
    setPinOutput(LEFT_EN_PIN);
    writePinHigh(LEFT_EN_PIN);

    setPinOutput(RIGHT_EN_PIN);
    writePinHigh(RIGHT_EN_PIN);

    setPinOutput(COL_A_PIN);
    writePinLow(COL_A_PIN);

    setPinOutput(COL_B_PIN);
    writePinLow(COL_B_PIN);

    setPinOutput(COL_C_PIN);
    writePinLow(COL_C_PIN);

    // initialize analog pin
    palSetLineMode(LEFT_KEY_PIN, PAL_MODE_INPUT_ANALOG);
    palSetLineMode(RIGHT_KEY_PIN, PAL_MODE_INPUT_ANALOG);
    adcStart(&ADCD1, NULL);

    apc_matrix_init();
}

static uint8_t right_col_map[] = {14, 15, 16, 13, 9, 12, 11, 10};

static void sense_key(bool* left, bool* right, uint32_t row, uint32_t col) {
    adcConvert(&ADCD1, &adcgrpcfg1, samples1, ADC_GRP1_BUF_DEPTH);

    *left = apc_matrix_update(row, col, samples1[0]);
    if (right_col_map[col] != 16) {
        *right = apc_matrix_update(row, right_col_map[col] - 1, samples1[1]);
    }
}

bool matrix_scan_custom(matrix_row_t* raw) {
    bool changed = false;

    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t last_row_value    = raw[row];
        matrix_row_t current_row_value = last_row_value;
        writePinHigh(custom_row_pins[row]);
        wait_us(400);

        for (int col = 0; col < 8; col++) {
            writePin(COL_A_PIN, (custom_col_pins[col] & COL_A_MASK) ? 1 : 0);
            writePin(COL_B_PIN, (custom_col_pins[col] & COL_B_MASK) ? 1 : 0);
            writePin(COL_C_PIN, (custom_col_pins[col] & COL_C_MASK) ? 1 : 0);

            writePinLow(LEFT_EN_PIN);
            writePinLow(RIGHT_EN_PIN);
            bool left  = false;
            bool right = false;

            sense_key(&left, &right, row, col);

            if (left) {
                current_row_value |= (1 << col);
            } else {
                current_row_value &= ~(1 << col);
            }

            if (right_col_map[col] != 16) {
                if (right) {
                    current_row_value |= (1 << (right_col_map[col] - 1));
                } else {
                    current_row_value &= ~(1 << (right_col_map[col] - 1));
                }
            }

            if (last_row_value != current_row_value) {
                raw[row] = current_row_value;
                changed  = true;
            }
        }

        writePinHigh(LEFT_EN_PIN);
        writePinHigh(RIGHT_EN_PIN);
        writePinLow(custom_row_pins[row]);
        wait_us(10);
    }

    return changed;
}
