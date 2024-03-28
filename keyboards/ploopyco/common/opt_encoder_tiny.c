/* Copyright 2023 Leorize <leorize+oss@disroot.org>
 * Copyright 2011 Ben Buxton <bb@cactii.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include <stdbool.h>
#include <stdint.h>

/* An extremely simple implementation of the encoder:
 *
 * For read out, the mechanism mimics that of a Schmitt trigger, with
 * statically defined high/low thresholds used instead of computing
 * one at runtime.
 *
 * The advantage of this approach is computing less in the decoder
 * implementation and allow the state to be measured before the wheel
 * moved.
 *
 * Compared to opt_encoder_simple.c, the use of an intermediary state
 * reduces sensitivity and de-sensitize against tiny movements caused
 * when lifting finger off the wheel.
 *
 * For turning decoded values into rotation, an algorithm inspired by
 * http://www.buxtronix.net/2011/10/rotary-encoders-done-properly.html
 * is employed.
 */

#if !defined(ENCODER_LOW_THRES_A) || !defined(ENCODER_HIGH_THRES_A)
#    error "The thresholds for phototransistors A is not defined in config.h"
#endif
#if !defined(ENCODER_LOW_THRES_B) || !defined(ENCODER_HIGH_THRES_B)
#    error "The thresholds for phototransistors B is not defined in config.h"
#endif
/*
 * Sample values, captured for a Ploopy Mini Trackball
 *
 * The following min-max values was captured by aggregating data recorded
 * when debug_encoder is enabled:
 *
 *   A: min: 0, max: 214
 *   B: min: 0, max: 204
 *
 * The threshold specified is then defined at the 1/4 and the 3/4 points.
 *
 * As these values might vary between units, you're encouraged to
 * measure your own.
 */
#if 0
#    define ENCODER_LOW_THRES_A 53
#    define ENCODER_HIGH_THRES_A 161
#    define ENCODER_LOW_THRES_B 52
#    define ENCODER_HIGH_THRES_B 153
#endif

/* Utilities for composing the encoder state */
#define MAKE_STATE(HI_A, HI_B) (((uint8_t)((HI_A) & 0x1) << 1) | ((uint8_t)((HI_B) & 0x1)))
#define STATE_A(st) ((st & 0x2) >> 1)
#define STATE_B(st) (st & 0x1)

typedef enum {
    START,
    DOWN_BEGIN,
    UP_BEGIN,
    START_MID,
    DOWN_BEGIN_MID,
    UP_BEGIN_MID,
    STATE_MASK    = 0xf, /* 0b1111 */
    EMIT_UP       = 0x10,
    EMIT_UP_MID   = EMIT_UP & START_MID,
    EMIT_DOWN     = 0x80,
    EMIT_DOWN_MID = EMIT_DOWN & START_MID,
    EMIT_MASK     = 0xf0
} encoder_state_t;

static encoder_state_t state;
static uint8_t         encState;

static const uint8_t transitions[] = {
    // clang-format off
    // START -> 00, 01, 10, 11
    START, DOWN_BEGIN, UP_BEGIN, START_MID,
    // DOWN_BEGIN -> 00, 01, 10, 11
    START, DOWN_BEGIN, START, EMIT_DOWN_MID,
    // UP_BEGIN -> 00, 01, 10, 11
    START, START, UP_BEGIN, EMIT_UP_MID,
    // START_MID -> 00, 01, 10, 11
    START, UP_BEGIN_MID, DOWN_BEGIN_MID, START_MID,
    // DOWN_BEGIN_MID -> 00, 01, 10, 11
    EMIT_DOWN, START_MID, DOWN_BEGIN_MID, START_MID,
    // UP_BEGIN_MID -> 00, 01, 10, 11
    EMIT_UP, UP_BEGIN_MID, START_MID, START_MID,
    // clang-format on
};

void opt_encoder_init(void) {
    state    = START;
    encState = 0;
}

int8_t opt_encoder_handler(uint16_t encA, uint16_t encB) {
    encState = MAKE_STATE((STATE_A(encState) & (encA > ENCODER_LOW_THRES_A)) | (encA > ENCODER_HIGH_THRES_A), (STATE_B(encState) & (encB > ENCODER_LOW_THRES_B)) | (encB > ENCODER_HIGH_THRES_B));
    state    = transitions[((state & STATE_MASK) << 2) + encState];
    return state & EMIT_MASK;
}
