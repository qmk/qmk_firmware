/*
Copyright 2023 RephlexZero (@RephlexZero)
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "analogkeys.h"
#include "config.h"
#include "quantum.h"
#include "custom_analog.h"
#include "lut.h"
#include "scanfunctions.h"
#include <ch.h>
#include <hal.h>
#include "gpio.h"

#if MUXES == 0
pin_t matrix_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
#endif

// External definitions
#if MUXES != 0
#include "multiplexer.h"
//extern ADCManager  adcManager;
extern const mux_t mux_index[MUXES][MUX_CHANNELS];
extern const pin_t mux_pins[MUXES];
#endif

analog_key_t keys[MATRIX_ROWS][MATRIX_COLS] = {0};

void matrix_init_custom(void) {
    generate_lut();
    lut_init();
#if MUXES != 0
    multiplexer_init();
    //initADCGroups(&adcManager);
#endif
    get_sensor_offsets();
    wait_ms(500);
    get_sensor_offsets();
    #if MUXES == 0
    SMA_init();
    #endif
    rgblight_enable();
}
    matrix_row_t previous_matrix[MATRIX_ROWS];

    bool matrix_scan_custom(matrix_row_t current_matrix[]) {
        memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));
#if MUXES != 0
    for (uint8_t channel = 0; channel < MUX_CHANNELS; ++channel) {
        uint8_t channel_greycoded = (channel >> 1) ^ channel;
        select_mux(channel_greycoded);
        //adcStartAllConversions(&adcManager);

        for (uint8_t mux = 0; mux < MUXES; ++mux) {
            const mux_t *mux_idx = &mux_index[mux][channel_greycoded];

            if (mux_idx->row == 255 && mux_idx->col == 255) continue; // NC mux pin

            analog_key_t *key = &keys[mux_idx->row][mux_idx->col];
            //key->raw          = getADCSample(&adcManager, mux);
            key->raw          = analogReadPin(mux_pins[mux]);
            //SMA_filter(key);
            key->value = (*key->lut)[key->offset + key->raw];

            switch (key->mode) {
                case dynamic_actuation:
                    matrix_read_cols_dynamic_actuation(&current_matrix[mux_idx->row], mux_idx->col, key);
                    break;
                case continuous_dynamic_actuation:
                    matrix_read_cols_continuous_dynamic_actuation(&current_matrix[mux_idx->row], mux_idx->col, key);
                    break;
                case static_actuation:
                    matrix_read_cols_static_actuation(&current_matrix[mux_idx->row], mux_idx->col, key);
                    break;
                case dynamic_keystroke:
                    break;
            }
        }
    }
#else
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
            analog_key_t *key = &keys[current_row][current_col];
            key->raw          = analogReadPin(matrix_pins[current_row][current_col]);
            SMA_filter(key);
            key->value = (*key->lut)[key->offset + key->raw];

            switch (key->mode) {
                case dynamic_actuation:
                    matrix_read_cols_dynamic_actuation(&current_matrix[current_row], current_col, key);
                    break;
                case continuous_dynamic_actuation:
                    matrix_read_cols_continuous_dynamic_actuation(&current_matrix[current_row], current_col, key);
                    break;
                case static_actuation:
                    matrix_read_cols_static_actuation(&current_matrix[current_row], current_col, key);
                    break;
                case dynamic_keystroke:
                    break;
            }
        }
    }
#endif
    return memcmp(previous_matrix, current_matrix, sizeof(previous_matrix)) != 0;
}
