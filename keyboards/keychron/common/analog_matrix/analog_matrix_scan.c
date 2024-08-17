/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "stdint.h"
#include "hal.h"
#include "gpio.h"
#include "quantum.h"
#include "analog_matrix.h"
#include "debounce.h"
#include "lpm.h"

#ifndef HC164_DS
#    define HC164_DS B3
#endif
#ifndef HC164_CP
#    define HC164_CP B5
#endif
#ifndef HC164_MR
#    define HC164_MR D2
#endif

#define ADC_GRP_NUM_CHANNELS 6
#define ADC_GRP_BUF_DEPTH 1
#define UNUSED_DEPTH 0

extern matrix_row_t raw_matrix[MATRIX_ROWS];
extern matrix_row_t matrix[MATRIX_ROWS];
extern matrix_row_t game_controller_matrix[MATRIX_ROWS];

pin_t        row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t        col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
matrix_row_t matrix_mask[MATRIX_ROWS];
matrix_row_t virtual_matrix[MATRIX_ROWS] = {0};
static bool matrix_changed;

static adcsample_t samples[ADC_GRP_NUM_CHANNELS * ADC_GRP_BUF_DEPTH];

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {
    dprintf("err\r\n");

    (void)adcp;
    (void)err;
}

// clang-format off
ADCConversionGroup adcgrpcfg = {
    FALSE,
    6,
    NULL,
    adcerrorcallback,
    0,                                          /* CR1 */
    ADC_CR2_SWSTART,                            /* CR2 */
    ADC_SMPR1_SMP_AN10(ADC_SAMPLE_56)  |
    ADC_SMPR1_SMP_AN11(ADC_SAMPLE_56)  |
    ADC_SMPR1_SMP_AN12(ADC_SAMPLE_56)  |
    ADC_SMPR1_SMP_AN13(ADC_SAMPLE_56),          /* SMPR1*/
    ADC_SMPR2_SMP_AN0(ADC_SAMPLE_56)   | 
    ADC_SMPR2_SMP_AN1(ADC_SAMPLE_56),           /* SMPR2*/
    0,                                          /* HTR */
    0,                                          /* LTR */
    0,                                          /* SQR1 */
    0,                                          /* SQR2 */
    ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10)    |
    ADC_SQR3_SQ2_N(ADC_CHANNEL_IN11)    |
    ADC_SQR3_SQ3_N(ADC_CHANNEL_IN12)    |
    ADC_SQR3_SQ4_N(ADC_CHANNEL_IN13)    |
    ADC_SQR3_SQ5_N(ADC_CHANNEL_IN0)     |
    ADC_SQR3_SQ6_N(ADC_CHANNEL_IN1)             /* SQR3 */
};
// clang-format on

static inline void shifter_delay(uint16_t n) {
    while (n-- > 0) {
        asm volatile("nop" ::: "memory");
    }
}

static void HC164_output(uint16_t      data, bool bit_flag) {
    uint8_t n = 50;

    ATOMIC_BLOCK_FORCEON {
        for (uint8_t i = 0; i < 15; i++) {
            if (data & 0x1) {
                writePinHigh(HC164_DS);
            } else {
                writePinLow(HC164_DS);
            }
            shifter_delay(n);
            writePinHigh(HC164_CP);
            shifter_delay(n);
            writePinLow(HC164_CP);
            shifter_delay(n);
            if (bit_flag) {
                break;
            } else {
                data = data >> 1;
            }
        }

    }
}

static bool select_col(uint8_t col) {
    if (col == 0) {
        writePinLow(HC164_MR);
        shifter_delay(20);
        writePinHigh(HC164_MR);
        shifter_delay(20);
        HC164_output(0x01, true);
    }
    return true;
}

static void unselect_col(uint8_t col) {
    HC164_output(0x00, true);
    return;
}

void select_all_cols(void) { }
static void unselect_cols(void) { }

void matrix_read_rows_on_col(uint8_t current_col, matrix_row_t row_shifter) {

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    } 

    wait_us(40);

    uint8_t debouce_times = ANALOG_DEBOUCE_TIME;
    uint8_t row_value = 0;
    bool changed = false;

    do {
        adcConvert(&ADCD1, &adcgrpcfg, samples, ADC_GRP_BUF_DEPTH);

        uint8_t row_value_recheck = 0;
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
            matrix_row_t row_mask = 0x01 << current_col;
            update_raw_value(row_index, current_col, samples[row_index]);

            bool pressed = analog_matrix_get_key_state(row_index, current_col);
            if (pressed) {
                if ((raw_matrix[row_index] & row_mask) == 0)
                    changed = true;

                if (debouce_times == ANALOG_DEBOUCE_TIME) {
                    row_value |= (0x01 << row_index);
                } else {
                    row_value_recheck |= (0x01 << row_index);
                }
            } else if (raw_matrix[row_index] & row_mask) {
                changed = true;
            }
        }

        if (debouce_times != ANALOG_DEBOUCE_TIME && row_value != row_value_recheck) {
            // Clear state when bounce occurs
            changed = false; 
        }

    } while (--debouce_times && changed);

    if (changed) {
        matrix_changed = true;
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
            if (row_value & (0x01 << row_index))
                raw_matrix[row_index] |= row_shifter;
            else
                raw_matrix[row_index] &= ~row_shifter;
        }
    }

    // Unselect col
    unselect_col(current_col);
}

void matrix_init_custom(void) {
#ifdef ANALOG_MATRIX_POWER_PIN    
   setPinOutput(ANALOG_MATRIX_POWER_PIN);
   writePin(ANALOG_MATRIX_POWER_PIN, ANALOG_MATRIX_POWER_ENABLE_LEVEL);
#endif
#ifdef ANALOG_MATRIX_WAKEUP_PIN
    setPinInputHigh(ANALOG_MATRIX_WAKEUP_PIN);
#endif
#ifdef ENCODER_SWITCH_PIN
    setPinInputHigh(ENCODER_SWITCH_PIN);
#endif

    // Init shift register control pins
    setPinOutput(HC164_DS);
    setPinOutput(HC164_CP);
    setPinOutput(HC164_MR);
    writePinLow(HC164_MR);
    
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            palSetLineMode(row_pins[x], PAL_MODE_INPUT_ANALOG);
            palWriteLine(row_pins[x], 0);
        }
    }

    unselect_cols();
    adcStart(&ADCD1, NULL);

    // Refer to STM32 AN4073 Option 2
    SYSCFG->PMC |= SYSCFG_PMC_ADC1DC2;

    // Value of initial ADC seems abnormal, scan to skip/drop i
    for (uint8_t i=0; i<5; i++)
        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            matrix_read_rows_on_col(current_col, 0);
        }

    analog_matrix_init();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {

    memcpy(virtual_matrix, matrix, sizeof(matrix));
    matrix_changed = false;

    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(current_col, row_shifter);
    }

    analog_matrix_task();
    extern matrix_row_t analog_matrix_mask[];
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
       raw_matrix[row] &= analog_matrix_mask[row];
    }

#if defined(ENCODER_MATRIX_ROW) && defined(ENCODER_MATRIX_ROW)
    if (readPin(ENCODER_SWITCH_PIN) == 0) {
        if ((raw_matrix[ENCODER_MATRIX_ROW] & (1 << ENCODER_MATROX_COL)) == 0) {
            matrix_changed = true;
            raw_matrix[ENCODER_MATRIX_ROW] |= (1 << ENCODER_MATROX_COL);
        }
    } else {
        if ((raw_matrix[ENCODER_MATRIX_ROW] & (1 << ENCODER_MATROX_COL))) {
            matrix_changed = true;
            raw_matrix[ENCODER_MATRIX_ROW] &= ~(1 << ENCODER_MATROX_COL);
        }
    }
#endif

//    bool changed = memcmp(raw_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
//    if (changed) memcpy(raw_matrix, curr_matrix, sizeof(curr_matrix));

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
       virtual_matrix[row] |= game_controller_matrix[row];
    }
    //changed = debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_kb();

    return matrix_changed;
}

void  matrix_lpm(void) { 
    adcStop(&ADCD1);
    
#ifdef HC164_DS
    setPinInputLow(HC164_DS);
#endif
#ifdef HC164_CP
    setPinInputLow(HC164_CP);
#endif
#ifdef HC164_MR
    setPinInputLow(HC164_MR);
#endif

#ifdef ANALOG_MATRIX_POWER_PIN    
       writePin(ANALOG_MATRIX_POWER_PIN, !ANALOG_MATRIX_POWER_ENABLE_LEVEL);
#endif

#ifdef ANALOG_MATRIX_WAKEUP_PIN
    palEnableLineEvent(ANALOG_MATRIX_WAKEUP_PIN, PAL_EVENT_MODE_FALLING_EDGE);
#endif

    // Set all row to input low
    pin_t pins_row[MATRIX_ROWS] = MATRIX_ROW_PINS;
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (pins_row[x] != NO_PIN) {
            setPinInputLow(pins_row[x]);
        }
    }

}

