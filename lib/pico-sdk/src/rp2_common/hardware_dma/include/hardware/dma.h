/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_DMA_H
#define _HARDWARE_DMA_H

#include "pico.h"
#include "hardware/structs/dma.h"
#include "hardware/regs/dreq.h"
#include "pico/assert.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file hardware/dma.h
 *  \defgroup hardware_dma hardware_dma
 *
 * DMA Controller API
 *
 * The RP2040 Direct Memory Access (DMA) master performs bulk data transfers on a processor’s
 * behalf. This leaves processors free to attend to other tasks, or enter low-power sleep states. The
 * data throughput of the DMA is also significantly higher than one of RP2040’s processors.
 *
 * The DMA can perform one read access and one write access, up to 32 bits in size, every clock cycle.
 * There are 12 independent channels, which each supervise a sequence of bus transfers, usually in
 * one of the following scenarios:
 *
 * * Memory to peripheral
 * * Peripheral to memory
 * * Memory to memory
 */

// these are not defined in generated dreq.h
#define DREQ_DMA_TIMER0 DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0
#define DREQ_DMA_TIMER1 DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1
#define DREQ_DMA_TIMER2 DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2
#define DREQ_DMA_TIMER3 DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3
#define DREQ_FORCE      DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_DMA, Enable/disable DMA assertions, type=bool, default=0, group=hardware_dma
#ifndef PARAM_ASSERTIONS_ENABLED_DMA
#define PARAM_ASSERTIONS_ENABLED_DMA 0
#endif

static inline void check_dma_channel_param(__unused uint channel) {
#if PARAM_ASSERTIONS_ENABLED(DMA)
    // this method is used a lot by inline functions so avoid code bloat by deferring to function
    extern void check_dma_channel_param_impl(uint channel);
    check_dma_channel_param_impl(channel);
#endif
}

static inline void check_dma_timer_param(__unused uint timer_num) {
    valid_params_if(DMA, timer_num < NUM_DMA_TIMERS);
}

inline static dma_channel_hw_t *dma_channel_hw_addr(uint channel) {
    check_dma_channel_param(channel);
    return &dma_hw->ch[channel];
}

/*! \brief Mark a dma channel as used
 *  \ingroup hardware_dma
 *
 * Method for cooperative claiming of hardware. Will cause a panic if the channel
 * is already claimed. Use of this method by libraries detects accidental
 * configurations that would fail in unpredictable ways.
 *
 * \param channel the dma channel
 */
void dma_channel_claim(uint channel);

/*! \brief Mark multiple dma channels as used
 *  \ingroup hardware_dma
 *
 * Method for cooperative claiming of hardware. Will cause a panic if any of the channels
 * are already claimed. Use of this method by libraries detects accidental
 * configurations that would fail in unpredictable ways.
 *
 * \param channel_mask Bitfield of all required channels to claim (bit 0 == channel 0, bit 1 == channel 1 etc)
 */
void dma_claim_mask(uint32_t channel_mask);

/*! \brief Mark a dma channel as no longer used
 *  \ingroup hardware_dma
 *
 * \param channel the dma channel to release
 */
void dma_channel_unclaim(uint channel);

/*! \brief Mark multiple dma channels as no longer used
 *  \ingroup hardware_dma
 *
 * \param channel_mask Bitfield of all channels to unclaim (bit 0 == channel 0, bit 1 == channel 1 etc)
 */
void dma_unclaim_mask(uint32_t channel_mask);

/*! \brief Claim a free dma channel
 *  \ingroup hardware_dma
 *
 * \param required if true the function will panic if none are available
 * \return the dma channel number or -1 if required was false, and none were free
 */
int dma_claim_unused_channel(bool required);

/*! \brief Determine if a dma channel is claimed
 *  \ingroup hardware_dma
 *
 * \param channel the dma channel
 * \return true if the channel is claimed, false otherwise
 * \see dma_channel_claim
 * \see dma_channel_claim_mask
 */
bool dma_channel_is_claimed(uint channel);

/** \brief DMA channel configuration
 *  \defgroup channel_config channel_config
 *  \ingroup hardware_dma
 *
 * A DMA channel needs to be configured, these functions provide handy helpers to set up configuration
 * structures. See \ref dma_channel_config
 */

/*! \brief Enumeration of available DMA channel transfer sizes.
 *  \ingroup hardware_dma
 *
 * Names indicate the number of bits.
 */
enum dma_channel_transfer_size {
    DMA_SIZE_8 = 0,    ///< Byte transfer (8 bits)
    DMA_SIZE_16 = 1,   ///< Half word transfer (16 bits)
    DMA_SIZE_32 = 2    ///< Word transfer (32 bits)
};

typedef struct {
    uint32_t ctrl;
} dma_channel_config;

/*! \brief  Set DMA channel read increment in a channel configuration object
 *  \ingroup channel_config
 *
 * \param c Pointer to channel configuration object
 * \param incr True to enable read address increments, if false, each read will be from the same address
 *             Usually disabled for peripheral to memory transfers
 */
static inline void channel_config_set_read_increment(dma_channel_config *c, bool incr) {
    c->ctrl = incr ? (c->ctrl | DMA_CH0_CTRL_TRIG_INCR_READ_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_INCR_READ_BITS);
}

/*! \brief  Set DMA channel write increment in a channel configuration object
 *  \ingroup channel_config
 *
 * \param c Pointer to channel configuration object
 * \param incr True to enable write address increments, if false, each write will be to the same address
 *             Usually disabled for memory to peripheral transfers
 */
static inline void channel_config_set_write_increment(dma_channel_config *c, bool incr) {
    c->ctrl = incr ? (c->ctrl | DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS);
}

/*! \brief  Select a transfer request signal in a channel configuration object
 *  \ingroup channel_config
 *
 * The channel uses the transfer request signal to pace its data transfer rate.
 * Sources for TREQ signals are internal (TIMERS) or external (DREQ, a Data Request from the system).
 * 0x0 to 0x3a -> select DREQ n as TREQ
 * 0x3b -> Select Timer 0 as TREQ
 * 0x3c -> Select Timer 1 as TREQ
 * 0x3d -> Select Timer 2 as TREQ (Optional)
 * 0x3e -> Select Timer 3 as TREQ (Optional)
 * 0x3f -> Permanent request, for unpaced transfers.
 *
 * \param c Pointer to channel configuration data
 * \param dreq Source (see description)
 */
static inline void channel_config_set_dreq(dma_channel_config *c, uint dreq) {
    assert(dreq <= DREQ_FORCE);
    c->ctrl = (c->ctrl & ~DMA_CH0_CTRL_TRIG_TREQ_SEL_BITS) | (dreq << DMA_CH0_CTRL_TRIG_TREQ_SEL_LSB);
}

/*! \brief  Set DMA channel chain_to channel in a channel configuration object
 *  \ingroup channel_config
 *
 * When this channel completes, it will trigger the channel indicated by chain_to. Disable by
 * setting chain_to to itself (the same channel)
 *
 * \param c Pointer to channel configuration object
 * \param chain_to Channel to trigger when this channel completes.
 */
static inline void channel_config_set_chain_to(dma_channel_config *c, uint chain_to) {
    assert(chain_to <= NUM_DMA_CHANNELS);
    c->ctrl = (c->ctrl & ~DMA_CH0_CTRL_TRIG_CHAIN_TO_BITS) | (chain_to << DMA_CH0_CTRL_TRIG_CHAIN_TO_LSB);
}

/*! \brief Set the size of each DMA bus transfer in a channel configuration object
 *  \ingroup channel_config
 *
 * Set the size of each bus transfer (byte/halfword/word). The read and write addresses
 * advance by the specific amount (1/2/4 bytes) with each transfer.
 *
 * \param c Pointer to channel configuration object
 * \param size See enum for possible values.
 */
static inline void channel_config_set_transfer_data_size(dma_channel_config *c, enum dma_channel_transfer_size size) {
    assert(size == DMA_SIZE_8 || size == DMA_SIZE_16 || size == DMA_SIZE_32);
    c->ctrl = (c->ctrl & ~DMA_CH0_CTRL_TRIG_DATA_SIZE_BITS) | (((uint)size) << DMA_CH0_CTRL_TRIG_DATA_SIZE_LSB);
}

/*! \brief  Set address wrapping parameters in a channel configuration object
 *  \ingroup channel_config
 *
 * Size of address wrap region. If 0, don’t wrap. For values n > 0, only the lower n bits of the address
 * will change. This wraps the address on a (1 << n) byte boundary, facilitating access to naturally-aligned
 * ring buffers.
 * Ring sizes between 2 and 32768 bytes are possible (size_bits from 1 - 15)
 *
 * 0x0 -> No wrapping.
 *
 * \param c Pointer to channel configuration object
 * \param write True to apply to write addresses, false to apply to read addresses
 * \param size_bits 0 to disable wrapping. Otherwise the size in bits of the changing part of the address.
 *        Effectively wraps the address on a (1 << size_bits) byte boundary.
 */
static inline void channel_config_set_ring(dma_channel_config *c, bool write, uint size_bits) {
    assert(size_bits < 32);
    c->ctrl = (c->ctrl & ~(DMA_CH0_CTRL_TRIG_RING_SIZE_BITS | DMA_CH0_CTRL_TRIG_RING_SEL_BITS)) |
              (size_bits << DMA_CH0_CTRL_TRIG_RING_SIZE_LSB) |
              (write ? DMA_CH0_CTRL_TRIG_RING_SEL_BITS : 0);
}

/*! \brief  Set DMA byte swapping config in a channel configuration object
 *  \ingroup channel_config
 *
 * No effect for byte data, for halfword data, the two bytes of each halfword are
 * swapped. For word data, the four bytes of each word are swapped to reverse their order.
 *
 * \param c Pointer to channel configuration object
 * \param bswap True to enable byte swapping
 */
static inline void channel_config_set_bswap(dma_channel_config *c, bool bswap) {
    c->ctrl = bswap ? (c->ctrl | DMA_CH0_CTRL_TRIG_BSWAP_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_BSWAP_BITS);
}

/*! \brief  Set IRQ quiet mode in a channel configuration object
 *  \ingroup channel_config
 *
 * In QUIET mode, the channel does not generate IRQs at the end of every transfer block. Instead,
 * an IRQ is raised when NULL is written to a trigger register, indicating the end of a control
 * block chain.
 *
 * \param c Pointer to channel configuration object
 * \param irq_quiet True to enable quiet mode, false to disable.
 */
static inline void channel_config_set_irq_quiet(dma_channel_config *c, bool irq_quiet) {
    c->ctrl = irq_quiet ? (c->ctrl | DMA_CH0_CTRL_TRIG_IRQ_QUIET_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_IRQ_QUIET_BITS);
}

/*!
 *  \brief Set the channel priority in a channel configuration object
 *  \ingroup channel_config
 *
 * When true, gives a channel preferential treatment in issue scheduling: in each scheduling round,
 * all high priority channels are considered first, and then only a single low
 * priority channel, before returning to the high priority channels.
 *
 * This only affects the order in which the DMA schedules channels. The DMA's bus priority is not changed.
 * If the DMA is not saturated then a low priority channel will see no loss of throughput.
 *
 * \param c Pointer to channel configuration object
 * \param high_priority True to enable high priority
 */
static inline void channel_config_set_high_priority(dma_channel_config *c, bool high_priority) {
    c->ctrl = high_priority ? (c->ctrl | DMA_CH0_CTRL_TRIG_HIGH_PRIORITY_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_HIGH_PRIORITY_BITS);
}

/*!
 *  \brief Enable/Disable the DMA channel in a channel configuration object
 *  \ingroup channel_config
 *
 * When false, the channel will ignore triggers, stop issuing transfers, and pause the current transfer sequence (i.e. BUSY will
 * remain high if already high)
 *
 * \param c Pointer to channel configuration object
 * \param enable True to enable the DMA channel. When enabled, the channel will respond to triggering events, and start transferring data.
 *
 */
static inline void channel_config_set_enable(dma_channel_config *c, bool enable) {
    c->ctrl = enable ? (c->ctrl | DMA_CH0_CTRL_TRIG_EN_BITS) : (c->ctrl & ~DMA_CH0_CTRL_TRIG_EN_BITS);
}

/*! \brief  Enable access to channel by sniff hardware in a channel configuration object
 *  \ingroup channel_config
 *
 * Sniff HW must be enabled and have this channel selected.
 *
 * \param c Pointer to channel configuration object
 * \param sniff_enable True to enable the Sniff HW access to this DMA channel.
 */
static inline void channel_config_set_sniff_enable(dma_channel_config *c, bool sniff_enable) {
    c->ctrl = sniff_enable ? (c->ctrl | DMA_CH0_CTRL_TRIG_SNIFF_EN_BITS) : (c->ctrl &
                                                                             ~DMA_CH0_CTRL_TRIG_SNIFF_EN_BITS);
}

/*! \brief  Get the default channel configuration for a given channel
 *  \ingroup channel_config
 *
 * Setting | Default
 * --------|--------
 * Read Increment | true
 * Write Increment | false
 * DReq | DREQ_FORCE
 * Chain to | self
 * Data size | DMA_SIZE_32
 * Ring | write=false, size=0 (i.e. off)
 * Byte Swap | false
 * Quiet IRQs | false
 * High Priority | false
 * Channel Enable | true
 * Sniff Enable | false
 *
 * \param channel DMA channel
 * \return the default configuration which can then be modified.
 */
static inline dma_channel_config dma_channel_get_default_config(uint channel) {
    dma_channel_config c = {0};
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, false);
    channel_config_set_dreq(&c, DREQ_FORCE);
    channel_config_set_chain_to(&c, channel);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
    channel_config_set_ring(&c, false, 0);
    channel_config_set_bswap(&c, false);
    channel_config_set_irq_quiet(&c, false);
    channel_config_set_enable(&c, true);
    channel_config_set_sniff_enable(&c, false);
    channel_config_set_high_priority( &c, false);
    return c;
}

/*! \brief  Get the current configuration for the specified channel.
 *  \ingroup channel_config
 *
 * \param channel DMA channel
 * \return The current configuration as read from the HW register (not cached)
 */
static inline dma_channel_config dma_get_channel_config(uint channel) {
    dma_channel_config c;
    c.ctrl = dma_channel_hw_addr(channel)->ctrl_trig;
    return c;
}

/*! \brief  Get the raw configuration register from a channel configuration
 *  \ingroup channel_config
 *
 * \param config Pointer to a config structure.
 * \return Register content
 */
static inline uint32_t channel_config_get_ctrl_value(const dma_channel_config *config) {
    return config->ctrl;
}

/*! \brief  Set a channel configuration
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param config Pointer to a config structure with required configuration
 * \param trigger True to trigger the transfer immediately
 */
static inline void dma_channel_set_config(uint channel, const dma_channel_config *config, bool trigger) {
    // Don't use CTRL_TRIG since we don't want to start a transfer
    if (!trigger) {
        dma_channel_hw_addr(channel)->al1_ctrl = channel_config_get_ctrl_value(config);
    } else {
        dma_channel_hw_addr(channel)->ctrl_trig = channel_config_get_ctrl_value(config);
    }
}

/*! \brief  Set the DMA initial read address.
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param read_addr Initial read address of transfer.
 * \param trigger True to start the transfer immediately
 */
static inline void dma_channel_set_read_addr(uint channel, const volatile void *read_addr, bool trigger) {
    if (!trigger) {
        dma_channel_hw_addr(channel)->read_addr = (uintptr_t) read_addr;
    } else {
        dma_channel_hw_addr(channel)->al3_read_addr_trig = (uintptr_t) read_addr;
    }
}

/*! \brief  Set the DMA initial write address
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param write_addr Initial write address of transfer.
 * \param trigger True to start the transfer immediately
 */
static inline void dma_channel_set_write_addr(uint channel, volatile void *write_addr, bool trigger) {
    if (!trigger) {
        dma_channel_hw_addr(channel)->write_addr = (uintptr_t) write_addr;
    } else {
        dma_channel_hw_addr(channel)->al2_write_addr_trig = (uintptr_t) write_addr;
    }
}

/*! \brief  Set the number of bus transfers the channel will do
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param trans_count The number of transfers (not NOT bytes, see channel_config_set_transfer_data_size)
 * \param trigger True to start the transfer immediately
 */
static inline void dma_channel_set_trans_count(uint channel, uint32_t trans_count, bool trigger) {
    if (!trigger) {
        dma_channel_hw_addr(channel)->transfer_count = trans_count;
    } else {
        dma_channel_hw_addr(channel)->al1_transfer_count_trig = trans_count;
    }
}

/*! \brief  Configure all DMA parameters and optionally start transfer
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param config Pointer to DMA config structure
 * \param write_addr Initial write address
 * \param read_addr Initial read address
 * \param transfer_count Number of transfers to perform
 * \param trigger True to start the transfer immediately
 */
static inline void dma_channel_configure(uint channel, const dma_channel_config *config, volatile void *write_addr,
                                         const volatile void *read_addr,
                                         uint transfer_count, bool trigger) {
    dma_channel_set_read_addr(channel, read_addr, false);
    dma_channel_set_write_addr(channel, write_addr, false);
    dma_channel_set_trans_count(channel, transfer_count, false);
    dma_channel_set_config(channel, config, trigger);
}

/*! \brief Start a DMA transfer from a buffer immediately
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param read_addr Sets the initial read address
 * \param transfer_count Number of transfers to make. Not bytes, but the number of transfers of channel_config_set_transfer_data_size() to be sent.
 */
inline static void __attribute__((always_inline)) dma_channel_transfer_from_buffer_now(uint channel, 
                                                                                       const volatile void *read_addr,
                                                                                       uint32_t transfer_count) {
//    check_dma_channel_param(channel);
    dma_channel_hw_t *hw = dma_channel_hw_addr(channel);
    hw->read_addr = (uintptr_t) read_addr;
    hw->al1_transfer_count_trig = transfer_count;
}

/*! \brief Start a DMA transfer to a buffer immediately
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param write_addr Sets the initial write address
 * \param transfer_count Number of transfers to make. Not bytes, but the number of transfers of channel_config_set_transfer_data_size() to be sent.
 */
inline static void dma_channel_transfer_to_buffer_now(uint channel, volatile void *write_addr, uint32_t transfer_count) {
    dma_channel_hw_t *hw = dma_channel_hw_addr(channel);
    hw->write_addr = (uintptr_t) write_addr;
    hw->al1_transfer_count_trig = transfer_count;
}

/*! \brief  Start one or more channels simultaneously
 *  \ingroup hardware_dma
 *
 * \param chan_mask Bitmask of all the channels requiring starting. Channel 0 = bit 0, channel 1 = bit 1 etc.
 */
static inline void dma_start_channel_mask(uint32_t chan_mask) {
    valid_params_if(DMA, chan_mask && chan_mask < (1u << NUM_DMA_CHANNELS));
    dma_hw->multi_channel_trigger = chan_mask;
}

/*! \brief  Start a single DMA channel
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 */
static inline void dma_channel_start(uint channel) {
    dma_start_channel_mask(1u << channel);
}

/*! \brief  Stop a DMA transfer
 *  \ingroup hardware_dma
 *
 * Function will only return once the DMA has stopped.
 *
 * Note that due to errata RP2040-E13, aborting a channel which has transfers
 * in-flight (i.e. an individual read has taken place but the corresponding write has not), the ABORT
 * status bit will clear prematurely, and subsequently the in-flight
 * transfers will trigger a completion interrupt once they complete.
 *
 * The effect of this is that you \em may see a spurious completion interrupt
 * on the channel as a result of calling this method.
 *
 * The calling code should be sure to ignore a completion IRQ as a result of this method. This may
 * not require any additional work, as aborting a channel which may be about to complete, when you have a completion
 * IRQ handler registered, is inherently race-prone, and so code is likely needed to disambiguate the two occurrences.
 *
 * If that is not the case, but you do have a channel completion IRQ handler registered, you can simply
 * disable/re-enable the IRQ around the call to this method as shown by this code fragment (using DMA IRQ0).
 *
 * \code
 *  // disable the channel on IRQ0
 *  dma_channel_set_irq0_enabled(channel, false);
 *  // abort the channel
 *  dma_channel_abort(channel);
 *  // clear the spurious IRQ (if there was one)
 *  dma_channel_acknowledge_irq0(channel);
 *  // re-enable the channel on IRQ0
 *  dma_channel_set_irq0_enabled(channel, true);
 *\endcode
 *
 * \param channel DMA channel
 */
static inline void dma_channel_abort(uint channel) {
    check_dma_channel_param(channel);
    dma_hw->abort = 1u << channel;
    // Bit will go 0 once channel has reached safe state
    // (i.e. any in-flight transfers have retired)
    while (dma_hw->ch[channel].ctrl_trig & DMA_CH0_CTRL_TRIG_BUSY_BITS) tight_loop_contents();
}

/*! \brief  Enable single DMA channel's interrupt via DMA_IRQ_0
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param enabled true to enable interrupt 0 on specified channel, false to disable.
 */
static inline void dma_channel_set_irq0_enabled(uint channel, bool enabled) {
    check_dma_channel_param(channel);
    check_hw_layout(dma_hw_t, inte0, DMA_INTE0_OFFSET);
    if (enabled)
        hw_set_bits(&dma_hw->inte0, 1u << channel);
    else
        hw_clear_bits(&dma_hw->inte0, 1u << channel);
}

/*! \brief  Enable multiple DMA channels' interrupts via DMA_IRQ_0
 *  \ingroup hardware_dma
 *
 * \param channel_mask Bitmask of all the channels to enable/disable. Channel 0 = bit 0, channel 1 = bit 1 etc.
 * \param enabled true to enable all the interrupts specified in the mask, false to disable all the interrupts specified in the mask.
 */
static inline void dma_set_irq0_channel_mask_enabled(uint32_t channel_mask, bool enabled) {
    if (enabled) {
        hw_set_bits(&dma_hw->inte0, channel_mask);
    } else {
        hw_clear_bits(&dma_hw->inte0, channel_mask);
    }
}

/*! \brief  Enable single DMA channel's interrupt via DMA_IRQ_1
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \param enabled true to enable interrupt 1 on specified channel, false to disable.
 */
static inline void dma_channel_set_irq1_enabled(uint channel, bool enabled) {
    check_dma_channel_param(channel);
    check_hw_layout(dma_hw_t, inte1, DMA_INTE1_OFFSET);
    if (enabled)
        hw_set_bits(&dma_hw->inte1, 1u << channel);
    else
        hw_clear_bits(&dma_hw->inte1, 1u << channel);
}

/*! \brief  Enable multiple DMA channels' interrupts via DMA_IRQ_1
 *  \ingroup hardware_dma
 *
 * \param channel_mask Bitmask of all the channels to enable/disable. Channel 0 = bit 0, channel 1 = bit 1 etc.
 * \param enabled true to enable all the interrupts specified in the mask, false to disable all the interrupts specified in the mask.
 */
static inline void dma_set_irq1_channel_mask_enabled(uint32_t channel_mask, bool enabled) {
    if (enabled) {
        hw_set_bits(&dma_hw->inte1, channel_mask);
    } else {
        hw_clear_bits(&dma_hw->inte1, channel_mask);
    }
}

/*! \brief  Enable single DMA channel interrupt on either DMA_IRQ_0 or DMA_IRQ_1
 *  \ingroup hardware_dma
 *
 * \param irq_index the IRQ index; either 0 or 1 for DMA_IRQ_0 or DMA_IRQ_1
 * \param channel DMA channel
 * \param enabled true to enable interrupt via irq_index for specified channel, false to disable.
 */
static inline void dma_irqn_set_channel_enabled(uint irq_index, uint channel, bool enabled) {
    invalid_params_if(DMA, irq_index > 1);
    if (irq_index) {
        dma_channel_set_irq1_enabled(channel, enabled);
    } else {
        dma_channel_set_irq0_enabled(channel, enabled);
    }
}

/*! \brief  Enable multiple DMA channels' interrupt via either DMA_IRQ_0 or DMA_IRQ_1
 *  \ingroup hardware_dma
 *
 * \param irq_index the IRQ index; either 0 or 1 for DMA_IRQ_0 or DMA_IRQ_1
 * \param channel_mask Bitmask of all the channels to enable/disable. Channel 0 = bit 0, channel 1 = bit 1 etc.
 * \param enabled true to enable all the interrupts specified in the mask, false to disable all the interrupts specified in the mask.
 */
static inline void dma_irqn_set_channel_mask_enabled(uint irq_index, uint32_t channel_mask,  bool enabled) {
    invalid_params_if(DMA, irq_index > 1);
    if (irq_index) {
        dma_set_irq1_channel_mask_enabled(channel_mask, enabled);
    } else {
        dma_set_irq0_channel_mask_enabled(channel_mask, enabled);
    }
}

/*! \brief  Determine if a particular channel is a cause of DMA_IRQ_0
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \return true if the channel is a cause of DMA_IRQ_0, false otherwise
 */
static inline bool dma_channel_get_irq0_status(uint channel) {
    check_dma_channel_param(channel);
    return dma_hw->ints0 & (1u << channel);
}

/*! \brief  Determine if a particular channel is a cause of DMA_IRQ_1
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \return true if the channel is a cause of DMA_IRQ_1, false otherwise
 */
static inline bool dma_channel_get_irq1_status(uint channel) {
    check_dma_channel_param(channel);
    return dma_hw->ints1 & (1u << channel);
}

/*! \brief  Determine if a particular channel is a cause of DMA_IRQ_N
 *  \ingroup hardware_dma
 *
 * \param irq_index the IRQ index; either 0 or 1 for DMA_IRQ_0 or DMA_IRQ_1
 * \param channel DMA channel
 * \return true if the channel is a cause of the DMA_IRQ_N, false otherwise
 */
static inline bool dma_irqn_get_channel_status(uint irq_index, uint channel) {
    invalid_params_if(DMA, irq_index > 1);
    check_dma_channel_param(channel);
    return (irq_index ? dma_hw->ints1 : dma_hw->ints0) & (1u << channel);
}

/*! \brief  Acknowledge a channel IRQ, resetting it as the cause of DMA_IRQ_0
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 */
static inline void dma_channel_acknowledge_irq0(uint channel) {
    check_dma_channel_param(channel);
    dma_hw->ints0 = 1u << channel;
}

/*! \brief  Acknowledge a channel IRQ, resetting it as the cause of DMA_IRQ_1
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 */
static inline void dma_channel_acknowledge_irq1(uint channel) {
    check_dma_channel_param(channel);
    dma_hw->ints1 = 1u << channel;
}

/*! \brief  Acknowledge a channel IRQ, resetting it as the cause of DMA_IRQ_N
 *  \ingroup hardware_dma
 *
 * \param irq_index the IRQ index; either 0 or 1 for DMA_IRQ_0 or DMA_IRQ_1
 * \param channel DMA channel
 */
static inline void dma_irqn_acknowledge_channel(uint irq_index, uint channel) {
    invalid_params_if(DMA, irq_index > 1);
    check_dma_channel_param(channel);
    if (irq_index)
        dma_hw->ints1 = 1u << channel;
    else
        dma_hw->ints0 = 1u << channel;
}

/*! \brief  Check if DMA channel is busy
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 * \return true if the channel is currently busy
 */
inline static bool dma_channel_is_busy(uint channel) {
    check_dma_channel_param(channel);
    return !!(dma_hw->ch[channel].al1_ctrl & DMA_CH0_CTRL_TRIG_BUSY_BITS);
}

/*! \brief  Wait for a DMA channel transfer to complete
 *  \ingroup hardware_dma
 *
 * \param channel DMA channel
 */
inline static void dma_channel_wait_for_finish_blocking(uint channel) {
    while (dma_channel_is_busy(channel)) tight_loop_contents();
    // stop the compiler hoisting a non volatile buffer access above the DMA completion.
    __compiler_memory_barrier();
}

/*! \brief Enable the DMA sniffing targeting the specified channel
 *  \ingroup hardware_dma
 *
 * The mode can be one of the following:
 *
 * Mode | Function
 * -----|---------
 * 0x0 | Calculate a CRC-32 (IEEE802.3 polynomial)
 * 0x1 | Calculate a CRC-32 (IEEE802.3 polynomial) with bit reversed data
 * 0x2 | Calculate a CRC-16-CCITT
 * 0x3 | Calculate a CRC-16-CCITT with bit reversed data
 * 0xe | XOR reduction over all data. == 1 if the total 1 population count is odd.
 * 0xf | Calculate a simple 32-bit checksum (addition with a 32 bit accumulator)
 *
 * \param channel DMA channel
 * \param mode See description
 * \param force_channel_enable Set true to also turn on sniffing in the channel configuration (this
 * is usually what you want, but sometimes you might have a chain DMA with only certain segments
 * of the chain sniffed, in which case you might pass false).
 */
inline static void dma_sniffer_enable(uint channel, uint mode, bool force_channel_enable) {
    check_dma_channel_param(channel);
    check_hw_layout(dma_hw_t, sniff_ctrl, DMA_SNIFF_CTRL_OFFSET);
    if (force_channel_enable) {
        hw_set_bits(&dma_hw->ch[channel].al1_ctrl, DMA_CH0_CTRL_TRIG_SNIFF_EN_BITS);
    }
    hw_write_masked(&dma_hw->sniff_ctrl,
        (((channel << DMA_SNIFF_CTRL_DMACH_LSB) & DMA_SNIFF_CTRL_DMACH_BITS) |
         ((mode << DMA_SNIFF_CTRL_CALC_LSB) & DMA_SNIFF_CTRL_CALC_BITS) |
         DMA_SNIFF_CTRL_EN_BITS),
        (DMA_SNIFF_CTRL_DMACH_BITS |
         DMA_SNIFF_CTRL_CALC_BITS |
         DMA_SNIFF_CTRL_EN_BITS));
}

/*! \brief Enable the Sniffer byte swap function
 *  \ingroup hardware_dma
 *
 * Locally perform a byte reverse on the sniffed data, before feeding into checksum.
 *
 * Note that the sniff hardware is downstream of the DMA channel byteswap performed in the
 * read master: if channel_config_set_bswap() and dma_sniffer_set_byte_swap_enabled() are both enabled,
 * their effects cancel from the sniffer’s point of view.
 *
 * \param swap Set true to enable byte swapping
 */
inline static void dma_sniffer_set_byte_swap_enabled(bool swap) {
    if (swap)
        hw_set_bits(&dma_hw->sniff_ctrl, DMA_SNIFF_CTRL_BSWAP_BITS);
    else
        hw_clear_bits(&dma_hw->sniff_ctrl, DMA_SNIFF_CTRL_BSWAP_BITS);
}

/*! \brief Enable the Sniffer output invert function
 *  \ingroup hardware_dma
 *
 * If enabled, the sniff data result appears bit-inverted when read.
 * This does not affect the way the checksum is calculated.
 *
 * \param invert Set true to enable output bit inversion
 */
inline static void dma_sniffer_set_output_invert_enabled(bool invert) {
    if (invert)
        hw_set_bits(&dma_hw->sniff_ctrl, DMA_SNIFF_CTRL_OUT_INV_BITS);
    else
        hw_clear_bits(&dma_hw->sniff_ctrl, DMA_SNIFF_CTRL_OUT_INV_BITS);
}

/*! \brief Enable the Sniffer output bit reversal function
 *  \ingroup hardware_dma
 *
 * If enabled, the sniff data result appears bit-reversed when read.
 * This does not affect the way the checksum is calculated.
 *
 * \param reverse Set true to enable output bit reversal
 */
inline static void dma_sniffer_set_output_reverse_enabled(bool reverse) {
    if (reverse)
        hw_set_bits(&dma_hw->sniff_ctrl, DMA_SNIFF_CTRL_OUT_REV_BITS);
    else
        hw_clear_bits(&dma_hw->sniff_ctrl, DMA_SNIFF_CTRL_OUT_REV_BITS);
}

/*! \brief Disable the DMA sniffer
 *  \ingroup hardware_dma
 *
 */
inline static void dma_sniffer_disable(void) {
    dma_hw->sniff_ctrl = 0;
}

/*! \brief Set the sniffer's data accumulator with initial value
 *  \ingroup hardware_dma
 *
 * Generally, CRC algorithms are used with the data accumulator initially
 * seeded with 0xFFFF or 0xFFFFFFFF (for crc16 and crc32 algorithms)
 *
 * \param seed_value value to set data accumulator
 */
inline static void dma_sniffer_set_data_accumulator(uint32_t seed_value) {
    dma_hw->sniff_data = seed_value;
}

/*! \brief Get the sniffer's data accumulator value
 *  \ingroup hardware_dma
 *
 * Read value calculated by the hardware from sniffing the DMA stream
 */
inline static uint32_t dma_sniffer_get_data_accumulator(void) {
    return dma_hw->sniff_data;
}

/*! \brief Mark a dma timer as used
 *  \ingroup hardware_dma
 *
 * Method for cooperative claiming of hardware. Will cause a panic if the timer
 * is already claimed. Use of this method by libraries detects accidental
 * configurations that would fail in unpredictable ways.
 *
 * \param timer the dma timer
 */
void dma_timer_claim(uint timer);

/*! \brief Mark a dma timer as no longer used
 *  \ingroup hardware_dma
 *
 * Method for cooperative claiming of hardware.
 *
 * \param timer the dma timer to release
 */
void dma_timer_unclaim(uint timer);

/*! \brief Claim a free dma timer
 *  \ingroup hardware_dma
 *
 * \param required if true the function will panic if none are available
 * \return the dma timer number or -1 if required was false, and none were free
 */
int dma_claim_unused_timer(bool required);

/*! \brief Determine if a dma timer is claimed
 *  \ingroup hardware_dma
 *
 * \param timer the dma timer
 * \return true if the timer is claimed, false otherwise
 * \see dma_timer_claim
 */
bool dma_timer_is_claimed(uint timer);

/*! \brief Set the divider for the given DMA timer
 *  \ingroup hardware_dma
 *
 * The timer will run at the system_clock_freq * numerator / denominator, so this is the speed
 * that data elements will be transferred at via a DMA channel using this timer as a DREQ
 *
 * \param timer the dma timer
 * \param numerator the fraction's numerator
 * \param denominator the fraction's denominator
 */
static inline void dma_timer_set_fraction(uint timer, uint16_t numerator, uint16_t denominator) {
    check_dma_timer_param(timer);
    dma_hw->timer[timer] = (((uint32_t)numerator) << DMA_TIMER0_X_LSB) | (((uint32_t)denominator) << DMA_TIMER0_Y_LSB);
}

/*! \brief Return the DREQ number for a given DMA timer
 *  \ingroup hardware_dma
 *
 * \param timer_num DMA timer number 0-3
 */
static inline uint dma_get_timer_dreq(uint timer_num) {
    static_assert(DREQ_DMA_TIMER1 == DREQ_DMA_TIMER0 + 1, "");
    static_assert(DREQ_DMA_TIMER2 == DREQ_DMA_TIMER0 + 2, "");
    static_assert(DREQ_DMA_TIMER3 == DREQ_DMA_TIMER0 + 3, "");
    check_dma_timer_param(timer_num);
    return DREQ_DMA_TIMER0 + timer_num;
}

#ifndef NDEBUG
void print_dma_ctrl(dma_channel_hw_t *channel);
#endif

#ifdef __cplusplus
}
#endif

#endif
