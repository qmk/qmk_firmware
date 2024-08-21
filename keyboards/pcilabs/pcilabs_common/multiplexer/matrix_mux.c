/*
Copyright 2023 RephlexZero (@RephlexZero)
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "pcilabs_common/analogkeys.h"
#include "config.h"
#include "quantum.h"
#include "pcilabs_common/custom_analog.h"
#include "pcilabs_common/lut.h"
#include "pcilabs_common/scanfunctions.h"
#include <ch.h>
#include <hal.h>
#include "gpio.h"
#include "pcilabs_common/sma.h"

#include "multiplexer.h"

//extern ADCManager  adcManager;
extern const mux_t mux_index[MUXES][MUX_CHANNELS];
extern const pin_t mux_pins[MUXES];

extern analog_key_t keys[MATRIX_ROWS][MATRIX_COLS];

extern void handle_key_mode(analog_key_t*);
extern void matrix_init_common(void);

void matrix_init_custom(void) {
    matrix_init_common();
    multiplexer_init();
    //initADCGroups(&adcManager);

}

extern matrix_row_t previous_matrix[MATRIX_ROWS];

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));
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
            SMA_filter(key);
            key->value = (*key->lut)[key->offset + key->raw];
            matrix_read_mode_array[key->mode](&current_matrix[mux_idx->row], mux_idx->col, key);
        }
    }
    return memcmp(previous_matrix, current_matrix, sizeof(previous_matrix)) != 0;
}
