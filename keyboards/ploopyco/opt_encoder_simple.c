/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2020 Ploopy Corporation
 * Copyright 2022 Leorize <leorize+oss@disroot.org>
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
#include "opt_encoder.h"
#include "util.h"
#include <stdbool.h>
#include <stdint.h>

/* An alternative implementation for interpreting the encoder status:
 *
 * From graphing the phototransistor voltages, the peak and baseline appears to
 * be rather stable. Therefore there is no need to average them out, and instead
 * just simply store the min and max voltages of each phototransistor.
 *
 * This algorithm then distinguish between high and low states by employing an
 * approach similar to a Schmitt trigger: a low and high threshold is defined
 * for each phototransistor based on their min and max voltages.
 *
 * Currently, the thresholds are:
 *
 * * High threshold: The upper quarter of the voltage range.
 * * Low threshold: The lower quarter of the voltage range.
 *
 * these thresholds are defined for each phototransistor.
 *
 * For a state to cross from high -> low, it must fall below the low threshold.
 * Similarly, to cross from low -> high, the voltage must be higher than the
 * high threshold.
 *
 * Having two distinct thresholds filters out the bulk of noise from the
 * phototransistors.
 *
 * For converting the resulting high and low signals into rotation, a simple
 * quadrature decoder is used.
 */

/* The minimum value returned by the ADC */
#define ENCODER_MIN 0
/* The maximum value returned by the ADC */
#define ENCODER_MAX 1023

/* Utilities for composing the encoder state */
#define MAKE_STATE(HI_A, HI_B) (((uint8_t)((HI_A) & 0x1) << 1) | ((uint8_t)((HI_B) & 0x1)))
#define STATE_A(st) ((st & 0x2) >> 1)
#define STATE_B(st) (st & 0x1)
#define LOLO MAKE_STATE(0, 0)
#define HILO MAKE_STATE(1, 0)
#define LOHI MAKE_STATE(0, 1)

typedef enum {
    CALIBRATION, /* Recalibrate encoder state by waiting for a 01 -> 00 or 10 -> 00 transistion */
    DECODE /* Translate changes in the encoder state into movement */
} encoder_state_t;

static encoder_state_t mode;

static uint8_t lastState;

static uint16_t lowA;
static uint16_t highA;
static uint16_t lowB;
static uint16_t highB;

#define MOVE_UP 1
#define MOVE_DOWN -1
#define MOVE_NONE 0
#define MOVE_ERR 0x7F
static const uint8_t movement[] = {
    // 00 -> 00, 01, 10, 11
    MOVE_NONE, MOVE_DOWN, MOVE_UP, MOVE_ERR,
    // 01 -> 00, 01, 10, 11
    MOVE_UP, MOVE_NONE, MOVE_ERR, MOVE_DOWN,
    // 10 -> 00, 01, 10, 11
    MOVE_DOWN, MOVE_ERR, MOVE_NONE, MOVE_UP,
    // 11 -> 00, 01, 10, 11
    MOVE_ERR, MOVE_UP, MOVE_DOWN, MOVE_NONE
};

void opt_encoder_init(void) {
    mode = CALIBRATION;
    lastState = 0;

    lowA = ENCODER_MAX;
    lowB = ENCODER_MAX;
    highA = ENCODER_MIN;
    highB = ENCODER_MIN;
}

int8_t opt_encoder_handler(uint16_t encA, uint16_t encB) {
    int8_t result = 0;

    highA = MAX(encA, highA);
    lowA = MIN(encA, lowA);
    highB = MAX(encB, highB);
    lowB = MIN(encB, lowB);

    /* Only compute the thresholds after a large enough range is established */
    if (highA - lowA > SCROLL_THRESH_RANGE_LIM && highB - lowB > SCROLL_THRESH_RANGE_LIM) {
        const int16_t lowThresholdA = (highA + lowA) / 4;
        const int16_t highThresholdA = (highA + lowA) - lowThresholdA;
        const int16_t lowThresholdB = (highB + lowB) / 4;
        const int16_t highThresholdB = (highB + lowB) - lowThresholdB;

        uint8_t state = MAKE_STATE(
            STATE_A(lastState) ? encA > lowThresholdA : encA > highThresholdA,
            STATE_B(lastState) ? encB > lowThresholdB : encB > highThresholdB
        );

        switch (mode) {
            case CALIBRATION:
                if ((lastState == HILO && state == LOLO)
                        || (lastState == LOHI && state == LOLO))
                    mode = DECODE;
                else
                    mode = CALIBRATION;
                break;

            case DECODE:
                result = movement[lastState * 4 + state];
                /* If we detect a state change that should not be possible,
                 * then the wheel might have moved too fast and we need to
                 * recalibrate the encoder position. */
                mode = result == MOVE_ERR ? CALIBRATION : mode;
                result = result == MOVE_ERR ? MOVE_NONE : result;

                break;
        }

        lastState = state;
    }

    return result;
}
