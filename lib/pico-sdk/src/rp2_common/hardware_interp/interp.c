/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/interp.h"
#include "hardware/structs/sio.h"
#include "hardware/claim.h"

check_hw_size(interp_hw_t, SIO_INTERP1_ACCUM0_OFFSET - SIO_INTERP0_ACCUM0_OFFSET);

check_hw_layout(sio_hw_t, interp, SIO_INTERP0_ACCUM0_OFFSET);

static_assert(NUM_DMA_CHANNELS <= 16, "");

static uint8_t _claimed;

static inline uint interp_lane_bit(interp_hw_t * interp, uint lane) {
    return (interp_index(interp) << 1u) | lane;
}

void interp_claim_lane(interp_hw_t *interp, uint lane) {
    valid_params_if(INTERP, lane < 2);
    hw_claim_or_assert((uint8_t *) &_claimed, interp_lane_bit(interp, lane), "Lane is already claimed");
}

void interp_claim_lane_mask(interp_hw_t *interp, uint lane_mask) {
    valid_params_if(INTERP, lane_mask && lane_mask <= 0x3);
    if (lane_mask & 1u) interp_claim_lane(interp, 0);
    if (lane_mask & 2u) interp_claim_lane(interp, 1);
}

void interp_unclaim_lane(interp_hw_t *interp, uint lane) {
    valid_params_if(INTERP, lane < 2);
    hw_claim_clear((uint8_t *) &_claimed, interp_lane_bit(interp, lane));
}

bool interp_lane_is_claimed(interp_hw_t *interp, uint lane) {
    valid_params_if(INTERP, lane < 2);
    return hw_is_claimed((uint8_t *) &_claimed, interp_lane_bit(interp, lane));
}

void interp_unclaim_lane_mask(interp_hw_t *interp, uint lane_mask) {
    valid_params_if(INTERP, lane_mask <= 0x3);
    if (lane_mask & 1u) interp_unclaim_lane(interp, 0);
    if (lane_mask & 2u) interp_unclaim_lane(interp, 1);
}

void interp_save(interp_hw_t *interp, interp_hw_save_t *saver) {
    saver->accum[0] = interp->accum[0];
    saver->accum[1] = interp->accum[1];
    saver->base[0] = interp->base[0];
    saver->base[1] = interp->base[1];
    saver->base[2] = interp->base[2];
    saver->ctrl[0] = interp->ctrl[0];
    saver->ctrl[1] = interp->ctrl[1];
}

void interp_restore(interp_hw_t *interp, interp_hw_save_t *saver) {
    interp->accum[0] = saver->accum[0];
    interp->accum[1] = saver->accum[1];
    interp->base[0] = saver->base[0];
    interp->base[1] = saver->base[1];
    interp->base[2] = saver->base[2];
    interp->ctrl[0] = saver->ctrl[0];
    interp->ctrl[1] = saver->ctrl[1];
}
