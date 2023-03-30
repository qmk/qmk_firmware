// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_DMA_H
#define _HARDWARE_STRUCTS_DMA_H

#include "hardware/address_mapped.h"
#include "hardware/regs/dma.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_dma
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/dma.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(DMA_CH0_READ_ADDR_OFFSET) // DMA_CH0_READ_ADDR
    // DMA Channel 0 Read Address pointer
    io_rw_32 read_addr;

    _REG_(DMA_CH0_WRITE_ADDR_OFFSET) // DMA_CH0_WRITE_ADDR
    // DMA Channel 0 Write Address pointer
    io_rw_32 write_addr;

    _REG_(DMA_CH0_TRANS_COUNT_OFFSET) // DMA_CH0_TRANS_COUNT
    // DMA Channel 0 Transfer Count
    io_rw_32 transfer_count;

    _REG_(DMA_CH0_CTRL_TRIG_OFFSET) // DMA_CH0_CTRL_TRIG
    // DMA Channel 0 Control and Status
    // 0x80000000 [31]    : AHB_ERROR (0): Logical OR of the READ_ERROR and WRITE_ERROR flags
    // 0x40000000 [30]    : READ_ERROR (0): If 1, the channel received a read bus error
    // 0x20000000 [29]    : WRITE_ERROR (0): If 1, the channel received a write bus error
    // 0x01000000 [24]    : BUSY (0): This flag goes high when the channel starts a new transfer sequence, and low when the...
    // 0x00800000 [23]    : SNIFF_EN (0): If 1, this channel's data transfers are visible to the sniff hardware, and each...
    // 0x00400000 [22]    : BSWAP (0): Apply byte-swap transformation to DMA data
    // 0x00200000 [21]    : IRQ_QUIET (0): In QUIET mode, the channel does not generate IRQs at the end of every transfer block
    // 0x001f8000 [20:15] : TREQ_SEL (0): Select a Transfer Request signal
    // 0x00007800 [14:11] : CHAIN_TO (0): When this channel completes, it will trigger the channel indicated by CHAIN_TO
    // 0x00000400 [10]    : RING_SEL (0): Select whether RING_SIZE applies to read or write addresses
    // 0x000003c0 [9:6]   : RING_SIZE (0): Size of address wrap region
    // 0x00000020 [5]     : INCR_WRITE (0): If 1, the write address increments with each transfer
    // 0x00000010 [4]     : INCR_READ (0): If 1, the read address increments with each transfer
    // 0x0000000c [3:2]   : DATA_SIZE (0): Set the size of each bus transfer (byte/halfword/word)
    // 0x00000002 [1]     : HIGH_PRIORITY (0): HIGH_PRIORITY gives a channel preferential treatment in issue scheduling: in...
    // 0x00000001 [0]     : EN (0): DMA Channel Enable
    io_rw_32 ctrl_trig;

    _REG_(DMA_CH0_AL1_CTRL_OFFSET) // DMA_CH0_AL1_CTRL
    // Alias for channel 0 CTRL register
    io_rw_32 al1_ctrl;

    _REG_(DMA_CH0_AL1_READ_ADDR_OFFSET) // DMA_CH0_AL1_READ_ADDR
    // Alias for channel 0 READ_ADDR register
    io_rw_32 al1_read_addr;

    _REG_(DMA_CH0_AL1_WRITE_ADDR_OFFSET) // DMA_CH0_AL1_WRITE_ADDR
    // Alias for channel 0 WRITE_ADDR register
    io_rw_32 al1_write_addr;

    _REG_(DMA_CH0_AL1_TRANS_COUNT_TRIG_OFFSET) // DMA_CH0_AL1_TRANS_COUNT_TRIG
    // Alias for channel 0 TRANS_COUNT register
    io_rw_32 al1_transfer_count_trig;

    _REG_(DMA_CH0_AL2_CTRL_OFFSET) // DMA_CH0_AL2_CTRL
    // Alias for channel 0 CTRL register
    io_rw_32 al2_ctrl;

    _REG_(DMA_CH0_AL2_TRANS_COUNT_OFFSET) // DMA_CH0_AL2_TRANS_COUNT
    // Alias for channel 0 TRANS_COUNT register
    io_rw_32 al2_transfer_count;

    _REG_(DMA_CH0_AL2_READ_ADDR_OFFSET) // DMA_CH0_AL2_READ_ADDR
    // Alias for channel 0 READ_ADDR register
    io_rw_32 al2_read_addr;

    _REG_(DMA_CH0_AL2_WRITE_ADDR_TRIG_OFFSET) // DMA_CH0_AL2_WRITE_ADDR_TRIG
    // Alias for channel 0 WRITE_ADDR register
    io_rw_32 al2_write_addr_trig;

    _REG_(DMA_CH0_AL3_CTRL_OFFSET) // DMA_CH0_AL3_CTRL
    // Alias for channel 0 CTRL register
    io_rw_32 al3_ctrl;

    _REG_(DMA_CH0_AL3_WRITE_ADDR_OFFSET) // DMA_CH0_AL3_WRITE_ADDR
    // Alias for channel 0 WRITE_ADDR register
    io_rw_32 al3_write_addr;

    _REG_(DMA_CH0_AL3_TRANS_COUNT_OFFSET) // DMA_CH0_AL3_TRANS_COUNT
    // Alias for channel 0 TRANS_COUNT register
    io_rw_32 al3_transfer_count;

    _REG_(DMA_CH0_AL3_READ_ADDR_TRIG_OFFSET) // DMA_CH0_AL3_READ_ADDR_TRIG
    // Alias for channel 0 READ_ADDR register
    io_rw_32 al3_read_addr_trig;
} dma_channel_hw_t;

typedef struct {
    dma_channel_hw_t ch[NUM_DMA_CHANNELS]; // 12

    uint32_t _pad0[64];

    _REG_(DMA_INTR_OFFSET) // DMA_INTR
    // Interrupt Status (raw)
    // 0x0000ffff [15:0]  : INTR (0): Raw interrupt status for DMA Channels 0
    io_rw_32 intr;

    _REG_(DMA_INTE0_OFFSET) // DMA_INTE0
    // Interrupt Enables for IRQ 0
    // 0x0000ffff [15:0]  : INTE0 (0): Set bit n to pass interrupts from channel n to DMA IRQ 0
    io_rw_32 inte0;

    _REG_(DMA_INTF0_OFFSET) // DMA_INTF0
    // Force Interrupts
    // 0x0000ffff [15:0]  : INTF0 (0): Write 1s to force the corresponding bits in INTE0
    io_rw_32 intf0;

    _REG_(DMA_INTS0_OFFSET) // DMA_INTS0
    // Interrupt Status for IRQ 0
    // 0x0000ffff [15:0]  : INTS0 (0): Indicates active channel interrupt requests which are currently causing IRQ 0 to be asserted
    io_rw_32 ints0;

    uint32_t _pad1;

    _REG_(DMA_INTE1_OFFSET) // DMA_INTE1
    // Interrupt Enables for IRQ 1
    // 0x0000ffff [15:0]  : INTE1 (0): Set bit n to pass interrupts from channel n to DMA IRQ 1
    io_rw_32 inte1;

    _REG_(DMA_INTF1_OFFSET) // DMA_INTF1
    // Force Interrupts for IRQ 1
    // 0x0000ffff [15:0]  : INTF1 (0): Write 1s to force the corresponding bits in INTE0
    io_rw_32 intf1;

    _REG_(DMA_INTS1_OFFSET) // DMA_INTS1
    // Interrupt Status (masked) for IRQ 1
    // 0x0000ffff [15:0]  : INTS1 (0): Indicates active channel interrupt requests which are currently causing IRQ 1 to be asserted
    io_rw_32 ints1;

    _REG_(DMA_TIMER0_OFFSET) // DMA_TIMER0
    // (Description copied from array index 0 register DMA_TIMER0 applies similarly to other array indexes)
    //
    // Pacing (X/Y) Fractional Timer
    // 0xffff0000 [31:16] : X (0): Pacing Timer Dividend
    // 0x0000ffff [15:0]  : Y (0): Pacing Timer Divisor
    io_rw_32 timer[NUM_DMA_TIMERS]; // 4

    _REG_(DMA_MULTI_CHAN_TRIGGER_OFFSET) // DMA_MULTI_CHAN_TRIGGER
    // Trigger one or more channels simultaneously
    // 0x0000ffff [15:0]  : MULTI_CHAN_TRIGGER (0): Each bit in this register corresponds to a DMA channel
    io_rw_32 multi_channel_trigger;

    _REG_(DMA_SNIFF_CTRL_OFFSET) // DMA_SNIFF_CTRL
    // Sniffer Control
    // 0x00000800 [11]    : OUT_INV (0): If set, the result appears inverted (bitwise complement) when read
    // 0x00000400 [10]    : OUT_REV (0): If set, the result appears bit-reversed when read
    // 0x00000200 [9]     : BSWAP (0): Locally perform a byte reverse on the sniffed data, before feeding into checksum
    // 0x000001e0 [8:5]   : CALC (0)
    // 0x0000001e [4:1]   : DMACH (0): DMA channel for Sniffer to observe
    // 0x00000001 [0]     : EN (0): Enable sniffer
    io_rw_32 sniff_ctrl;

    _REG_(DMA_SNIFF_DATA_OFFSET) // DMA_SNIFF_DATA
    // Data accumulator for sniff hardware
    io_rw_32 sniff_data;

    uint32_t _pad2;

    _REG_(DMA_FIFO_LEVELS_OFFSET) // DMA_FIFO_LEVELS
    // Debug RAF, WAF, TDF levels
    // 0x00ff0000 [23:16] : RAF_LVL (0): Current Read-Address-FIFO fill level
    // 0x0000ff00 [15:8]  : WAF_LVL (0): Current Write-Address-FIFO fill level
    // 0x000000ff [7:0]   : TDF_LVL (0): Current Transfer-Data-FIFO fill level
    io_ro_32 fifo_levels;

    _REG_(DMA_CHAN_ABORT_OFFSET) // DMA_CHAN_ABORT
    // Abort an in-progress transfer sequence on one or more channels
    // 0x0000ffff [15:0]  : CHAN_ABORT (0): Each bit corresponds to a channel
    io_rw_32 abort;
} dma_hw_t;

typedef struct {
    struct dma_debug_hw_channel {
        io_rw_32 ctrdeq;
        io_ro_32 tcr;
        uint32_t pad[14];
    } ch[NUM_DMA_CHANNELS];
} dma_debug_hw_t;

#define dma_hw ((dma_hw_t *)DMA_BASE)
#define dma_debug_hw ((dma_debug_hw_t *)(DMA_BASE + DMA_CH0_DBG_CTDREQ_OFFSET))

static_assert( NUM_DMA_TIMERS == 4, "");
static_assert( NUM_DMA_CHANNELS == 12, "");

#endif
