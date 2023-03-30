/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "hardware/dma.h"
#include "hardware/claim.h"

#define DMA_CHAN_STRIDE (DMA_CH1_CTRL_TRIG_OFFSET - DMA_CH0_CTRL_TRIG_OFFSET)
check_hw_size(dma_channel_hw_t, DMA_CHAN_STRIDE);
check_hw_layout(dma_hw_t, abort, DMA_CHAN_ABORT_OFFSET);

// sanity check
static_assert(__builtin_offsetof(dma_hw_t, ch[0].ctrl_trig) == DMA_CH0_CTRL_TRIG_OFFSET, "hw mismatch");
static_assert(__builtin_offsetof(dma_hw_t, ch[1].ctrl_trig) == DMA_CH1_CTRL_TRIG_OFFSET, "hw mismatch");

static_assert(NUM_DMA_CHANNELS <= 16, "");
static uint16_t _claimed;
static uint8_t _timer_claimed;

void dma_channel_claim(uint channel) {
    check_dma_channel_param(channel);
    hw_claim_or_assert((uint8_t *) &_claimed, channel, "DMA channel %d is already claimed");
}

void dma_claim_mask(uint32_t mask) {
    for(uint i = 0; mask; i++, mask >>= 1u) {
        if (mask & 1u) dma_channel_claim(i);
    }
}

void dma_channel_unclaim(uint channel) {
    check_dma_channel_param(channel);
    hw_claim_clear((uint8_t *) &_claimed, channel);
}

void dma_unclaim_mask(uint32_t mask) {
    for(uint i = 0; mask; i++, mask >>= 1u) {
        if (mask & 1u) dma_channel_unclaim(i);
    }
}

int dma_claim_unused_channel(bool required) {
    return hw_claim_unused_from_range((uint8_t*)&_claimed, required, 0, NUM_DMA_CHANNELS-1, "No DMA channels are available");
}

bool dma_channel_is_claimed(uint channel) {
    check_dma_channel_param(channel);
    return hw_is_claimed((uint8_t *) &_claimed, channel);
}

void dma_timer_claim(uint timer) {
    check_dma_timer_param(timer);
    hw_claim_or_assert(&_timer_claimed, timer, "DMA timer %d is already claimed");
}

void dma_timer_unclaim(uint timer) {
    check_dma_timer_param(timer);
    hw_claim_clear(&_timer_claimed, timer);
}

int dma_claim_unused_timer(bool required) {
    return hw_claim_unused_from_range(&_timer_claimed, required, 0, NUM_DMA_TIMERS-1, "No DMA timers are available");
}

bool dma_timer_is_claimed(uint timer) {
    check_dma_timer_param(timer);
    return hw_is_claimed(&_timer_claimed, timer);
}

#ifndef NDEBUG

void print_dma_ctrl(dma_channel_hw_t *channel) {
    uint32_t ctrl = channel->ctrl_trig;
    int rgsz = (ctrl & DMA_CH0_CTRL_TRIG_RING_SIZE_BITS) >> DMA_CH0_CTRL_TRIG_RING_SIZE_LSB;
    printf("(%08x) ber %d rer %d wer %d busy %d trq %d cto %d rgsl %d rgsz %d inw %d inr %d sz %d hip %d en %d",
           (uint) ctrl,
           ctrl & DMA_CH0_CTRL_TRIG_AHB_ERROR_BITS ? 1 : 0,
           ctrl & DMA_CH0_CTRL_TRIG_READ_ERROR_BITS ? 1 : 0,
           ctrl & DMA_CH0_CTRL_TRIG_WRITE_ERROR_BITS ? 1 : 0,
           ctrl & DMA_CH0_CTRL_TRIG_BUSY_BITS ? 1 : 0,
           (int) ((ctrl & DMA_CH0_CTRL_TRIG_TREQ_SEL_BITS) >> DMA_CH0_CTRL_TRIG_TREQ_SEL_LSB),
           (int) ((ctrl & DMA_CH0_CTRL_TRIG_CHAIN_TO_BITS) >> DMA_CH0_CTRL_TRIG_CHAIN_TO_LSB),
           ctrl & DMA_CH0_CTRL_TRIG_RING_SEL_BITS ? 1 : 0,
           rgsz ? (1 << rgsz) : 0,
           ctrl & DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS ? 1 : 0,
           ctrl & DMA_CH0_CTRL_TRIG_INCR_READ_BITS ? 1 : 0,
           1 << ((ctrl & DMA_CH0_CTRL_TRIG_DATA_SIZE_BITS) >> DMA_CH0_CTRL_TRIG_DATA_SIZE_LSB),
           ctrl & DMA_CH0_CTRL_TRIG_HIGH_PRIORITY_BITS ? 1 : 0,
           ctrl & DMA_CH0_CTRL_TRIG_EN_BITS ? 1 : 0);
}
#endif

#if PARAM_ASSERTIONS_ENABLED(DMA)
void check_dma_channel_param_impl(uint __unused channel) {
    valid_params_if(DMA, channel < NUM_DMA_CHANNELS);
}
#endif
