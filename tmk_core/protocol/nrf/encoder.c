/*
Copyright 2020 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"

#include "apidef.h"
#include "bmp_encoder.h"
#include "bmp_encoder_actions.h"

#ifndef ENCODER_RESOLUTION
#    define ENCODER_RESOLUTION 4
#endif

#ifndef ENCODER_SCANTIME_MS
#    define ENCODER_SCANTIME_MS 2
#endif

// #if !defined(ENCODERS_PAD_A) || !defined(ENCODERS_PAD_B)
// #    error "No encoder pads defined by ENCODERS_PAD_A and ENCODERS_PAD_B"
// #endif

#define NUMBER_OF_ENCODERS 16
static pin_t   encoders_pad_a[NUMBER_OF_ENCODERS];
static pin_t   encoders_pad_b[NUMBER_OF_ENCODERS];
static int32_t encoder_value[NUMBER_OF_ENCODERS] = {0};
static int     encoder_cnt                       = 0;

__attribute__((weak)) void encoder_update_user(int8_t index, bool clockwise) {}

__attribute__((weak)) void encoder_update_kb(int8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
}

__attribute__((weak)) void encoder_key_interrupt_user(int8_t index) {}

__attribute__((weak)) void encoder_key_interrupt_kb(int8_t index) {
    encoder_key_interrupt_user(index);
}

__attribute__((weak)) void encoder_no_move_kb(int8_t index) {}

__attribute__((weak)) void encoder_no_move_user(int8_t index) {
    encoder_no_move_user(index);
}

void bmp_encoder_init(bmp_encoder_config_t const* const encoder_config) {
    if (encoder_config->enabled) {
        for (encoder_cnt = 0; encoder_cnt < NUMBER_OF_ENCODERS; encoder_cnt++) {
            encoders_pad_a[encoder_cnt] =
                encoder_config->encoder[encoder_cnt].pin[0];
            encoders_pad_b[encoder_cnt] =
                encoder_config->encoder[encoder_cnt].pin[1];

            if (encoders_pad_a[encoder_cnt] == 0 &&
                encoders_pad_b[encoder_cnt] == 0) {
                break;
            }
        }

        if (encoder_cnt > 0) {
            BMPAPI->encoder.init(ENCODER_SCANTIME_MS, encoders_pad_a,
                                 encoders_pad_b, encoder_cnt);
        }
    }
}

__attribute__((weak))
void bmp_encoder_read(bmp_encoder_config_t const* const encoder_config, uint32_t key_event_cnt) {
    int32_t encoder_diff;

    if (encoder_cnt > 0) {
        if (key_event_cnt > 0) {
            for (int i = 0; i < encoder_cnt; i++) {
                encoder_key_interrupt_bmp(i);
            }

            return;
        }

        for (int i = 0; i < encoder_cnt; i++) {
            encoder_diff = BMPAPI->encoder.get_count(i);
            encoder_value[i] += encoder_diff;

            if (encoder_value[i] >= encoder_config->encoder[i].step) {
                encoder_update_bmp(i, false);
            } else if (encoder_value[i] <= -encoder_config->encoder[i].step) {
                // direction is arbitrary here, but this clockwise
                encoder_update_bmp(i, true);
            } else {
                encoder_no_move_bmp(i);
            }

            encoder_value[i] %= encoder_config->encoder[i].step;
        }
    }
}
