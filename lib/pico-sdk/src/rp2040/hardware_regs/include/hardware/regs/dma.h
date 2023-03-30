/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : DMA
// Version        : 1
// Bus type       : apb
// Description    : DMA with separate read and write masters
// =============================================================================
#ifndef HARDWARE_REGS_DMA_DEFINED
#define HARDWARE_REGS_DMA_DEFINED
// =============================================================================
// Register    : DMA_CH0_READ_ADDR
// Description : DMA Channel 0 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH0_READ_ADDR_OFFSET _u(0x00000000)
#define DMA_CH0_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH0_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH0_READ_ADDR_MSB    _u(31)
#define DMA_CH0_READ_ADDR_LSB    _u(0)
#define DMA_CH0_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_WRITE_ADDR
// Description : DMA Channel 0 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH0_WRITE_ADDR_OFFSET _u(0x00000004)
#define DMA_CH0_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH0_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH0_WRITE_ADDR_MSB    _u(31)
#define DMA_CH0_WRITE_ADDR_LSB    _u(0)
#define DMA_CH0_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_TRANS_COUNT
// Description : DMA Channel 0 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH0_TRANS_COUNT_OFFSET _u(0x00000008)
#define DMA_CH0_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH0_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH0_TRANS_COUNT_MSB    _u(31)
#define DMA_CH0_TRANS_COUNT_LSB    _u(0)
#define DMA_CH0_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_CTRL_TRIG
// Description : DMA Channel 0 Control and Status
#define DMA_CH0_CTRL_TRIG_OFFSET _u(0x0000000c)
#define DMA_CH0_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH0_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH0_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH0_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH0_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH0_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH0_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH0_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH0_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH0_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH0_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH0_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH0_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH0_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH0_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH0_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH0_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH0_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH0_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH0_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH0_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH0_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH0_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH0_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH0_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH0_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH0_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH0_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH0_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH0_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH0_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH0_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH0_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH0_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH0_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH0_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH0_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH0_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH0_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH0_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH0_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH0_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH0_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH0_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH0_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH0_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH0_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH0_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH0_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH0_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH0_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH0_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH0_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH0_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH0_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH0_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH0_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH0_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH0_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH0_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH0_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH0_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH0_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH0_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL1_CTRL
// Description : Alias for channel 0 CTRL register
#define DMA_CH0_AL1_CTRL_OFFSET _u(0x00000010)
#define DMA_CH0_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH0_AL1_CTRL_RESET  "-"
#define DMA_CH0_AL1_CTRL_MSB    _u(31)
#define DMA_CH0_AL1_CTRL_LSB    _u(0)
#define DMA_CH0_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL1_READ_ADDR
// Description : Alias for channel 0 READ_ADDR register
#define DMA_CH0_AL1_READ_ADDR_OFFSET _u(0x00000014)
#define DMA_CH0_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH0_AL1_READ_ADDR_RESET  "-"
#define DMA_CH0_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH0_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH0_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL1_WRITE_ADDR
// Description : Alias for channel 0 WRITE_ADDR register
#define DMA_CH0_AL1_WRITE_ADDR_OFFSET _u(0x00000018)
#define DMA_CH0_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH0_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH0_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH0_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH0_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 0 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH0_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x0000001c)
#define DMA_CH0_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH0_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH0_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH0_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH0_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL2_CTRL
// Description : Alias for channel 0 CTRL register
#define DMA_CH0_AL2_CTRL_OFFSET _u(0x00000020)
#define DMA_CH0_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH0_AL2_CTRL_RESET  "-"
#define DMA_CH0_AL2_CTRL_MSB    _u(31)
#define DMA_CH0_AL2_CTRL_LSB    _u(0)
#define DMA_CH0_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL2_TRANS_COUNT
// Description : Alias for channel 0 TRANS_COUNT register
#define DMA_CH0_AL2_TRANS_COUNT_OFFSET _u(0x00000024)
#define DMA_CH0_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH0_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH0_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH0_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH0_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL2_READ_ADDR
// Description : Alias for channel 0 READ_ADDR register
#define DMA_CH0_AL2_READ_ADDR_OFFSET _u(0x00000028)
#define DMA_CH0_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH0_AL2_READ_ADDR_RESET  "-"
#define DMA_CH0_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH0_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH0_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 0 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH0_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x0000002c)
#define DMA_CH0_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH0_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH0_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH0_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH0_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL3_CTRL
// Description : Alias for channel 0 CTRL register
#define DMA_CH0_AL3_CTRL_OFFSET _u(0x00000030)
#define DMA_CH0_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH0_AL3_CTRL_RESET  "-"
#define DMA_CH0_AL3_CTRL_MSB    _u(31)
#define DMA_CH0_AL3_CTRL_LSB    _u(0)
#define DMA_CH0_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL3_WRITE_ADDR
// Description : Alias for channel 0 WRITE_ADDR register
#define DMA_CH0_AL3_WRITE_ADDR_OFFSET _u(0x00000034)
#define DMA_CH0_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH0_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH0_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH0_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH0_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL3_TRANS_COUNT
// Description : Alias for channel 0 TRANS_COUNT register
#define DMA_CH0_AL3_TRANS_COUNT_OFFSET _u(0x00000038)
#define DMA_CH0_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH0_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH0_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH0_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH0_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH0_AL3_READ_ADDR_TRIG
// Description : Alias for channel 0 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH0_AL3_READ_ADDR_TRIG_OFFSET _u(0x0000003c)
#define DMA_CH0_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH0_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH0_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH0_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH0_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_READ_ADDR
// Description : DMA Channel 1 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH1_READ_ADDR_OFFSET _u(0x00000040)
#define DMA_CH1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH1_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH1_READ_ADDR_MSB    _u(31)
#define DMA_CH1_READ_ADDR_LSB    _u(0)
#define DMA_CH1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_WRITE_ADDR
// Description : DMA Channel 1 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH1_WRITE_ADDR_OFFSET _u(0x00000044)
#define DMA_CH1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH1_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_TRANS_COUNT
// Description : DMA Channel 1 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH1_TRANS_COUNT_OFFSET _u(0x00000048)
#define DMA_CH1_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH1_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH1_TRANS_COUNT_MSB    _u(31)
#define DMA_CH1_TRANS_COUNT_LSB    _u(0)
#define DMA_CH1_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_CTRL_TRIG
// Description : DMA Channel 1 Control and Status
#define DMA_CH1_CTRL_TRIG_OFFSET _u(0x0000004c)
#define DMA_CH1_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH1_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH1_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH1_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH1_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH1_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH1_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH1_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH1_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH1_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH1_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH1_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH1_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH1_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH1_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH1_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH1_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH1_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH1_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH1_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH1_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH1_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH1_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH1_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH1_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH1_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH1_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH1_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH1_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH1_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH1_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH1_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH1_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH1_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH1_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH1_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH1_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH1_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH1_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH1_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH1_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH1_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH1_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH1_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH1_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH1_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH1_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH1_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH1_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH1_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH1_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH1_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH1_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH1_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH1_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH1_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH1_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH1_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH1_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH1_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH1_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH1_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH1_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH1_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL1_CTRL
// Description : Alias for channel 1 CTRL register
#define DMA_CH1_AL1_CTRL_OFFSET _u(0x00000050)
#define DMA_CH1_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH1_AL1_CTRL_RESET  "-"
#define DMA_CH1_AL1_CTRL_MSB    _u(31)
#define DMA_CH1_AL1_CTRL_LSB    _u(0)
#define DMA_CH1_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL1_READ_ADDR
// Description : Alias for channel 1 READ_ADDR register
#define DMA_CH1_AL1_READ_ADDR_OFFSET _u(0x00000054)
#define DMA_CH1_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH1_AL1_READ_ADDR_RESET  "-"
#define DMA_CH1_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH1_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH1_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL1_WRITE_ADDR
// Description : Alias for channel 1 WRITE_ADDR register
#define DMA_CH1_AL1_WRITE_ADDR_OFFSET _u(0x00000058)
#define DMA_CH1_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH1_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH1_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH1_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH1_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 1 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH1_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x0000005c)
#define DMA_CH1_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH1_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH1_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH1_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH1_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL2_CTRL
// Description : Alias for channel 1 CTRL register
#define DMA_CH1_AL2_CTRL_OFFSET _u(0x00000060)
#define DMA_CH1_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH1_AL2_CTRL_RESET  "-"
#define DMA_CH1_AL2_CTRL_MSB    _u(31)
#define DMA_CH1_AL2_CTRL_LSB    _u(0)
#define DMA_CH1_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL2_TRANS_COUNT
// Description : Alias for channel 1 TRANS_COUNT register
#define DMA_CH1_AL2_TRANS_COUNT_OFFSET _u(0x00000064)
#define DMA_CH1_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH1_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH1_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH1_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH1_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL2_READ_ADDR
// Description : Alias for channel 1 READ_ADDR register
#define DMA_CH1_AL2_READ_ADDR_OFFSET _u(0x00000068)
#define DMA_CH1_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH1_AL2_READ_ADDR_RESET  "-"
#define DMA_CH1_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH1_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH1_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 1 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH1_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x0000006c)
#define DMA_CH1_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH1_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH1_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH1_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH1_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL3_CTRL
// Description : Alias for channel 1 CTRL register
#define DMA_CH1_AL3_CTRL_OFFSET _u(0x00000070)
#define DMA_CH1_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH1_AL3_CTRL_RESET  "-"
#define DMA_CH1_AL3_CTRL_MSB    _u(31)
#define DMA_CH1_AL3_CTRL_LSB    _u(0)
#define DMA_CH1_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL3_WRITE_ADDR
// Description : Alias for channel 1 WRITE_ADDR register
#define DMA_CH1_AL3_WRITE_ADDR_OFFSET _u(0x00000074)
#define DMA_CH1_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH1_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH1_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH1_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH1_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL3_TRANS_COUNT
// Description : Alias for channel 1 TRANS_COUNT register
#define DMA_CH1_AL3_TRANS_COUNT_OFFSET _u(0x00000078)
#define DMA_CH1_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH1_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH1_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH1_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH1_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH1_AL3_READ_ADDR_TRIG
// Description : Alias for channel 1 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH1_AL3_READ_ADDR_TRIG_OFFSET _u(0x0000007c)
#define DMA_CH1_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH1_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH1_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH1_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH1_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_READ_ADDR
// Description : DMA Channel 2 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH2_READ_ADDR_OFFSET _u(0x00000080)
#define DMA_CH2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH2_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH2_READ_ADDR_MSB    _u(31)
#define DMA_CH2_READ_ADDR_LSB    _u(0)
#define DMA_CH2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_WRITE_ADDR
// Description : DMA Channel 2 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH2_WRITE_ADDR_OFFSET _u(0x00000084)
#define DMA_CH2_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH2_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH2_WRITE_ADDR_MSB    _u(31)
#define DMA_CH2_WRITE_ADDR_LSB    _u(0)
#define DMA_CH2_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_TRANS_COUNT
// Description : DMA Channel 2 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH2_TRANS_COUNT_OFFSET _u(0x00000088)
#define DMA_CH2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH2_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_CTRL_TRIG
// Description : DMA Channel 2 Control and Status
#define DMA_CH2_CTRL_TRIG_OFFSET _u(0x0000008c)
#define DMA_CH2_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH2_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH2_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH2_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH2_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH2_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH2_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH2_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH2_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH2_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH2_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH2_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH2_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH2_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH2_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH2_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH2_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH2_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH2_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH2_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH2_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH2_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH2_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH2_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH2_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH2_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH2_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH2_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH2_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH2_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH2_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH2_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH2_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH2_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH2_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH2_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH2_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH2_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH2_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH2_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH2_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH2_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH2_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH2_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH2_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH2_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH2_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH2_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH2_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH2_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH2_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH2_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH2_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH2_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH2_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH2_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH2_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH2_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH2_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH2_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH2_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH2_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH2_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH2_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL1_CTRL
// Description : Alias for channel 2 CTRL register
#define DMA_CH2_AL1_CTRL_OFFSET _u(0x00000090)
#define DMA_CH2_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH2_AL1_CTRL_RESET  "-"
#define DMA_CH2_AL1_CTRL_MSB    _u(31)
#define DMA_CH2_AL1_CTRL_LSB    _u(0)
#define DMA_CH2_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL1_READ_ADDR
// Description : Alias for channel 2 READ_ADDR register
#define DMA_CH2_AL1_READ_ADDR_OFFSET _u(0x00000094)
#define DMA_CH2_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH2_AL1_READ_ADDR_RESET  "-"
#define DMA_CH2_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH2_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH2_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL1_WRITE_ADDR
// Description : Alias for channel 2 WRITE_ADDR register
#define DMA_CH2_AL1_WRITE_ADDR_OFFSET _u(0x00000098)
#define DMA_CH2_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH2_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH2_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH2_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH2_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 2 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH2_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x0000009c)
#define DMA_CH2_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH2_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH2_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH2_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH2_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL2_CTRL
// Description : Alias for channel 2 CTRL register
#define DMA_CH2_AL2_CTRL_OFFSET _u(0x000000a0)
#define DMA_CH2_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH2_AL2_CTRL_RESET  "-"
#define DMA_CH2_AL2_CTRL_MSB    _u(31)
#define DMA_CH2_AL2_CTRL_LSB    _u(0)
#define DMA_CH2_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL2_TRANS_COUNT
// Description : Alias for channel 2 TRANS_COUNT register
#define DMA_CH2_AL2_TRANS_COUNT_OFFSET _u(0x000000a4)
#define DMA_CH2_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH2_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH2_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH2_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH2_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL2_READ_ADDR
// Description : Alias for channel 2 READ_ADDR register
#define DMA_CH2_AL2_READ_ADDR_OFFSET _u(0x000000a8)
#define DMA_CH2_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH2_AL2_READ_ADDR_RESET  "-"
#define DMA_CH2_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH2_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH2_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 2 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH2_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x000000ac)
#define DMA_CH2_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH2_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH2_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH2_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH2_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL3_CTRL
// Description : Alias for channel 2 CTRL register
#define DMA_CH2_AL3_CTRL_OFFSET _u(0x000000b0)
#define DMA_CH2_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH2_AL3_CTRL_RESET  "-"
#define DMA_CH2_AL3_CTRL_MSB    _u(31)
#define DMA_CH2_AL3_CTRL_LSB    _u(0)
#define DMA_CH2_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL3_WRITE_ADDR
// Description : Alias for channel 2 WRITE_ADDR register
#define DMA_CH2_AL3_WRITE_ADDR_OFFSET _u(0x000000b4)
#define DMA_CH2_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH2_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH2_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH2_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH2_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL3_TRANS_COUNT
// Description : Alias for channel 2 TRANS_COUNT register
#define DMA_CH2_AL3_TRANS_COUNT_OFFSET _u(0x000000b8)
#define DMA_CH2_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH2_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH2_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH2_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH2_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH2_AL3_READ_ADDR_TRIG
// Description : Alias for channel 2 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH2_AL3_READ_ADDR_TRIG_OFFSET _u(0x000000bc)
#define DMA_CH2_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH2_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH2_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH2_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH2_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_READ_ADDR
// Description : DMA Channel 3 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH3_READ_ADDR_OFFSET _u(0x000000c0)
#define DMA_CH3_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH3_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH3_READ_ADDR_MSB    _u(31)
#define DMA_CH3_READ_ADDR_LSB    _u(0)
#define DMA_CH3_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_WRITE_ADDR
// Description : DMA Channel 3 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH3_WRITE_ADDR_OFFSET _u(0x000000c4)
#define DMA_CH3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH3_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_TRANS_COUNT
// Description : DMA Channel 3 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH3_TRANS_COUNT_OFFSET _u(0x000000c8)
#define DMA_CH3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH3_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_CTRL_TRIG
// Description : DMA Channel 3 Control and Status
#define DMA_CH3_CTRL_TRIG_OFFSET _u(0x000000cc)
#define DMA_CH3_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH3_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH3_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH3_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH3_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH3_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH3_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH3_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH3_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH3_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH3_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH3_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH3_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH3_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH3_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH3_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH3_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH3_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH3_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH3_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH3_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH3_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH3_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH3_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH3_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH3_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH3_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH3_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH3_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH3_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH3_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH3_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH3_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH3_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH3_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH3_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH3_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH3_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH3_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH3_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH3_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH3_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH3_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH3_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH3_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH3_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH3_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH3_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH3_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH3_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH3_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH3_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH3_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH3_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH3_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH3_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH3_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH3_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH3_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH3_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH3_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH3_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH3_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH3_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL1_CTRL
// Description : Alias for channel 3 CTRL register
#define DMA_CH3_AL1_CTRL_OFFSET _u(0x000000d0)
#define DMA_CH3_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH3_AL1_CTRL_RESET  "-"
#define DMA_CH3_AL1_CTRL_MSB    _u(31)
#define DMA_CH3_AL1_CTRL_LSB    _u(0)
#define DMA_CH3_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL1_READ_ADDR
// Description : Alias for channel 3 READ_ADDR register
#define DMA_CH3_AL1_READ_ADDR_OFFSET _u(0x000000d4)
#define DMA_CH3_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH3_AL1_READ_ADDR_RESET  "-"
#define DMA_CH3_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH3_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH3_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL1_WRITE_ADDR
// Description : Alias for channel 3 WRITE_ADDR register
#define DMA_CH3_AL1_WRITE_ADDR_OFFSET _u(0x000000d8)
#define DMA_CH3_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH3_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH3_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH3_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH3_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 3 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH3_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x000000dc)
#define DMA_CH3_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH3_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH3_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH3_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH3_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL2_CTRL
// Description : Alias for channel 3 CTRL register
#define DMA_CH3_AL2_CTRL_OFFSET _u(0x000000e0)
#define DMA_CH3_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH3_AL2_CTRL_RESET  "-"
#define DMA_CH3_AL2_CTRL_MSB    _u(31)
#define DMA_CH3_AL2_CTRL_LSB    _u(0)
#define DMA_CH3_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL2_TRANS_COUNT
// Description : Alias for channel 3 TRANS_COUNT register
#define DMA_CH3_AL2_TRANS_COUNT_OFFSET _u(0x000000e4)
#define DMA_CH3_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH3_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH3_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH3_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH3_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL2_READ_ADDR
// Description : Alias for channel 3 READ_ADDR register
#define DMA_CH3_AL2_READ_ADDR_OFFSET _u(0x000000e8)
#define DMA_CH3_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH3_AL2_READ_ADDR_RESET  "-"
#define DMA_CH3_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH3_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH3_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 3 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH3_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x000000ec)
#define DMA_CH3_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH3_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH3_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH3_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH3_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL3_CTRL
// Description : Alias for channel 3 CTRL register
#define DMA_CH3_AL3_CTRL_OFFSET _u(0x000000f0)
#define DMA_CH3_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH3_AL3_CTRL_RESET  "-"
#define DMA_CH3_AL3_CTRL_MSB    _u(31)
#define DMA_CH3_AL3_CTRL_LSB    _u(0)
#define DMA_CH3_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL3_WRITE_ADDR
// Description : Alias for channel 3 WRITE_ADDR register
#define DMA_CH3_AL3_WRITE_ADDR_OFFSET _u(0x000000f4)
#define DMA_CH3_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH3_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH3_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH3_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH3_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL3_TRANS_COUNT
// Description : Alias for channel 3 TRANS_COUNT register
#define DMA_CH3_AL3_TRANS_COUNT_OFFSET _u(0x000000f8)
#define DMA_CH3_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH3_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH3_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH3_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH3_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH3_AL3_READ_ADDR_TRIG
// Description : Alias for channel 3 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH3_AL3_READ_ADDR_TRIG_OFFSET _u(0x000000fc)
#define DMA_CH3_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH3_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH3_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH3_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH3_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_READ_ADDR
// Description : DMA Channel 4 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH4_READ_ADDR_OFFSET _u(0x00000100)
#define DMA_CH4_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH4_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH4_READ_ADDR_MSB    _u(31)
#define DMA_CH4_READ_ADDR_LSB    _u(0)
#define DMA_CH4_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_WRITE_ADDR
// Description : DMA Channel 4 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH4_WRITE_ADDR_OFFSET _u(0x00000104)
#define DMA_CH4_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH4_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH4_WRITE_ADDR_MSB    _u(31)
#define DMA_CH4_WRITE_ADDR_LSB    _u(0)
#define DMA_CH4_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_TRANS_COUNT
// Description : DMA Channel 4 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH4_TRANS_COUNT_OFFSET _u(0x00000108)
#define DMA_CH4_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH4_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH4_TRANS_COUNT_MSB    _u(31)
#define DMA_CH4_TRANS_COUNT_LSB    _u(0)
#define DMA_CH4_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_CTRL_TRIG
// Description : DMA Channel 4 Control and Status
#define DMA_CH4_CTRL_TRIG_OFFSET _u(0x0000010c)
#define DMA_CH4_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH4_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH4_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH4_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH4_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH4_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH4_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH4_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH4_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH4_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH4_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH4_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH4_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH4_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH4_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH4_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH4_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH4_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH4_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH4_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH4_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH4_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH4_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH4_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH4_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH4_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH4_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH4_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH4_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH4_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH4_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH4_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH4_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH4_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH4_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH4_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH4_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH4_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH4_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH4_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH4_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH4_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH4_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH4_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH4_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH4_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH4_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH4_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH4_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH4_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH4_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH4_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH4_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH4_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH4_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH4_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH4_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH4_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH4_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH4_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH4_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH4_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH4_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH4_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL1_CTRL
// Description : Alias for channel 4 CTRL register
#define DMA_CH4_AL1_CTRL_OFFSET _u(0x00000110)
#define DMA_CH4_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH4_AL1_CTRL_RESET  "-"
#define DMA_CH4_AL1_CTRL_MSB    _u(31)
#define DMA_CH4_AL1_CTRL_LSB    _u(0)
#define DMA_CH4_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL1_READ_ADDR
// Description : Alias for channel 4 READ_ADDR register
#define DMA_CH4_AL1_READ_ADDR_OFFSET _u(0x00000114)
#define DMA_CH4_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH4_AL1_READ_ADDR_RESET  "-"
#define DMA_CH4_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH4_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH4_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL1_WRITE_ADDR
// Description : Alias for channel 4 WRITE_ADDR register
#define DMA_CH4_AL1_WRITE_ADDR_OFFSET _u(0x00000118)
#define DMA_CH4_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH4_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH4_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH4_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH4_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 4 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH4_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x0000011c)
#define DMA_CH4_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH4_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH4_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH4_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH4_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL2_CTRL
// Description : Alias for channel 4 CTRL register
#define DMA_CH4_AL2_CTRL_OFFSET _u(0x00000120)
#define DMA_CH4_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH4_AL2_CTRL_RESET  "-"
#define DMA_CH4_AL2_CTRL_MSB    _u(31)
#define DMA_CH4_AL2_CTRL_LSB    _u(0)
#define DMA_CH4_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL2_TRANS_COUNT
// Description : Alias for channel 4 TRANS_COUNT register
#define DMA_CH4_AL2_TRANS_COUNT_OFFSET _u(0x00000124)
#define DMA_CH4_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH4_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH4_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH4_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH4_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL2_READ_ADDR
// Description : Alias for channel 4 READ_ADDR register
#define DMA_CH4_AL2_READ_ADDR_OFFSET _u(0x00000128)
#define DMA_CH4_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH4_AL2_READ_ADDR_RESET  "-"
#define DMA_CH4_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH4_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH4_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 4 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH4_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x0000012c)
#define DMA_CH4_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH4_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH4_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH4_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH4_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL3_CTRL
// Description : Alias for channel 4 CTRL register
#define DMA_CH4_AL3_CTRL_OFFSET _u(0x00000130)
#define DMA_CH4_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH4_AL3_CTRL_RESET  "-"
#define DMA_CH4_AL3_CTRL_MSB    _u(31)
#define DMA_CH4_AL3_CTRL_LSB    _u(0)
#define DMA_CH4_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL3_WRITE_ADDR
// Description : Alias for channel 4 WRITE_ADDR register
#define DMA_CH4_AL3_WRITE_ADDR_OFFSET _u(0x00000134)
#define DMA_CH4_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH4_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH4_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH4_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH4_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL3_TRANS_COUNT
// Description : Alias for channel 4 TRANS_COUNT register
#define DMA_CH4_AL3_TRANS_COUNT_OFFSET _u(0x00000138)
#define DMA_CH4_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH4_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH4_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH4_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH4_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH4_AL3_READ_ADDR_TRIG
// Description : Alias for channel 4 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH4_AL3_READ_ADDR_TRIG_OFFSET _u(0x0000013c)
#define DMA_CH4_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH4_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH4_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH4_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH4_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_READ_ADDR
// Description : DMA Channel 5 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH5_READ_ADDR_OFFSET _u(0x00000140)
#define DMA_CH5_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH5_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH5_READ_ADDR_MSB    _u(31)
#define DMA_CH5_READ_ADDR_LSB    _u(0)
#define DMA_CH5_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_WRITE_ADDR
// Description : DMA Channel 5 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH5_WRITE_ADDR_OFFSET _u(0x00000144)
#define DMA_CH5_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH5_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH5_WRITE_ADDR_MSB    _u(31)
#define DMA_CH5_WRITE_ADDR_LSB    _u(0)
#define DMA_CH5_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_TRANS_COUNT
// Description : DMA Channel 5 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH5_TRANS_COUNT_OFFSET _u(0x00000148)
#define DMA_CH5_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH5_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH5_TRANS_COUNT_MSB    _u(31)
#define DMA_CH5_TRANS_COUNT_LSB    _u(0)
#define DMA_CH5_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_CTRL_TRIG
// Description : DMA Channel 5 Control and Status
#define DMA_CH5_CTRL_TRIG_OFFSET _u(0x0000014c)
#define DMA_CH5_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH5_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH5_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH5_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH5_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH5_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH5_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH5_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH5_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH5_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH5_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH5_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH5_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH5_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH5_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH5_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH5_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH5_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH5_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH5_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH5_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH5_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH5_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH5_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH5_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH5_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH5_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH5_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH5_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH5_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH5_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH5_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH5_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH5_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH5_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH5_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH5_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH5_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH5_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH5_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH5_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH5_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH5_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH5_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH5_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH5_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH5_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH5_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH5_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH5_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH5_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH5_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH5_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH5_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH5_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH5_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH5_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH5_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH5_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH5_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH5_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH5_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH5_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH5_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL1_CTRL
// Description : Alias for channel 5 CTRL register
#define DMA_CH5_AL1_CTRL_OFFSET _u(0x00000150)
#define DMA_CH5_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH5_AL1_CTRL_RESET  "-"
#define DMA_CH5_AL1_CTRL_MSB    _u(31)
#define DMA_CH5_AL1_CTRL_LSB    _u(0)
#define DMA_CH5_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL1_READ_ADDR
// Description : Alias for channel 5 READ_ADDR register
#define DMA_CH5_AL1_READ_ADDR_OFFSET _u(0x00000154)
#define DMA_CH5_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH5_AL1_READ_ADDR_RESET  "-"
#define DMA_CH5_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH5_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH5_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL1_WRITE_ADDR
// Description : Alias for channel 5 WRITE_ADDR register
#define DMA_CH5_AL1_WRITE_ADDR_OFFSET _u(0x00000158)
#define DMA_CH5_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH5_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH5_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH5_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH5_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 5 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH5_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x0000015c)
#define DMA_CH5_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH5_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH5_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH5_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH5_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL2_CTRL
// Description : Alias for channel 5 CTRL register
#define DMA_CH5_AL2_CTRL_OFFSET _u(0x00000160)
#define DMA_CH5_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH5_AL2_CTRL_RESET  "-"
#define DMA_CH5_AL2_CTRL_MSB    _u(31)
#define DMA_CH5_AL2_CTRL_LSB    _u(0)
#define DMA_CH5_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL2_TRANS_COUNT
// Description : Alias for channel 5 TRANS_COUNT register
#define DMA_CH5_AL2_TRANS_COUNT_OFFSET _u(0x00000164)
#define DMA_CH5_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH5_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH5_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH5_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH5_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL2_READ_ADDR
// Description : Alias for channel 5 READ_ADDR register
#define DMA_CH5_AL2_READ_ADDR_OFFSET _u(0x00000168)
#define DMA_CH5_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH5_AL2_READ_ADDR_RESET  "-"
#define DMA_CH5_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH5_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH5_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 5 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH5_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x0000016c)
#define DMA_CH5_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH5_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH5_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH5_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH5_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL3_CTRL
// Description : Alias for channel 5 CTRL register
#define DMA_CH5_AL3_CTRL_OFFSET _u(0x00000170)
#define DMA_CH5_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH5_AL3_CTRL_RESET  "-"
#define DMA_CH5_AL3_CTRL_MSB    _u(31)
#define DMA_CH5_AL3_CTRL_LSB    _u(0)
#define DMA_CH5_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL3_WRITE_ADDR
// Description : Alias for channel 5 WRITE_ADDR register
#define DMA_CH5_AL3_WRITE_ADDR_OFFSET _u(0x00000174)
#define DMA_CH5_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH5_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH5_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH5_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH5_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL3_TRANS_COUNT
// Description : Alias for channel 5 TRANS_COUNT register
#define DMA_CH5_AL3_TRANS_COUNT_OFFSET _u(0x00000178)
#define DMA_CH5_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH5_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH5_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH5_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH5_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH5_AL3_READ_ADDR_TRIG
// Description : Alias for channel 5 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH5_AL3_READ_ADDR_TRIG_OFFSET _u(0x0000017c)
#define DMA_CH5_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH5_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH5_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH5_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH5_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_READ_ADDR
// Description : DMA Channel 6 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH6_READ_ADDR_OFFSET _u(0x00000180)
#define DMA_CH6_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH6_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH6_READ_ADDR_MSB    _u(31)
#define DMA_CH6_READ_ADDR_LSB    _u(0)
#define DMA_CH6_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_WRITE_ADDR
// Description : DMA Channel 6 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH6_WRITE_ADDR_OFFSET _u(0x00000184)
#define DMA_CH6_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH6_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH6_WRITE_ADDR_MSB    _u(31)
#define DMA_CH6_WRITE_ADDR_LSB    _u(0)
#define DMA_CH6_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_TRANS_COUNT
// Description : DMA Channel 6 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH6_TRANS_COUNT_OFFSET _u(0x00000188)
#define DMA_CH6_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH6_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH6_TRANS_COUNT_MSB    _u(31)
#define DMA_CH6_TRANS_COUNT_LSB    _u(0)
#define DMA_CH6_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_CTRL_TRIG
// Description : DMA Channel 6 Control and Status
#define DMA_CH6_CTRL_TRIG_OFFSET _u(0x0000018c)
#define DMA_CH6_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH6_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH6_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH6_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH6_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH6_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH6_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH6_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH6_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH6_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH6_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH6_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH6_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH6_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH6_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH6_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH6_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH6_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH6_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH6_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH6_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH6_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH6_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH6_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH6_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH6_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH6_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH6_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH6_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH6_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH6_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH6_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH6_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH6_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH6_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH6_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH6_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH6_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH6_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH6_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH6_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH6_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH6_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH6_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH6_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH6_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH6_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH6_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH6_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH6_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH6_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH6_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH6_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH6_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH6_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH6_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH6_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH6_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH6_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH6_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH6_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH6_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH6_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH6_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL1_CTRL
// Description : Alias for channel 6 CTRL register
#define DMA_CH6_AL1_CTRL_OFFSET _u(0x00000190)
#define DMA_CH6_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH6_AL1_CTRL_RESET  "-"
#define DMA_CH6_AL1_CTRL_MSB    _u(31)
#define DMA_CH6_AL1_CTRL_LSB    _u(0)
#define DMA_CH6_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL1_READ_ADDR
// Description : Alias for channel 6 READ_ADDR register
#define DMA_CH6_AL1_READ_ADDR_OFFSET _u(0x00000194)
#define DMA_CH6_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH6_AL1_READ_ADDR_RESET  "-"
#define DMA_CH6_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH6_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH6_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL1_WRITE_ADDR
// Description : Alias for channel 6 WRITE_ADDR register
#define DMA_CH6_AL1_WRITE_ADDR_OFFSET _u(0x00000198)
#define DMA_CH6_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH6_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH6_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH6_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH6_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 6 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH6_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x0000019c)
#define DMA_CH6_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH6_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH6_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH6_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH6_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL2_CTRL
// Description : Alias for channel 6 CTRL register
#define DMA_CH6_AL2_CTRL_OFFSET _u(0x000001a0)
#define DMA_CH6_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH6_AL2_CTRL_RESET  "-"
#define DMA_CH6_AL2_CTRL_MSB    _u(31)
#define DMA_CH6_AL2_CTRL_LSB    _u(0)
#define DMA_CH6_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL2_TRANS_COUNT
// Description : Alias for channel 6 TRANS_COUNT register
#define DMA_CH6_AL2_TRANS_COUNT_OFFSET _u(0x000001a4)
#define DMA_CH6_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH6_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH6_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH6_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH6_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL2_READ_ADDR
// Description : Alias for channel 6 READ_ADDR register
#define DMA_CH6_AL2_READ_ADDR_OFFSET _u(0x000001a8)
#define DMA_CH6_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH6_AL2_READ_ADDR_RESET  "-"
#define DMA_CH6_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH6_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH6_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 6 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH6_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x000001ac)
#define DMA_CH6_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH6_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH6_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH6_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH6_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL3_CTRL
// Description : Alias for channel 6 CTRL register
#define DMA_CH6_AL3_CTRL_OFFSET _u(0x000001b0)
#define DMA_CH6_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH6_AL3_CTRL_RESET  "-"
#define DMA_CH6_AL3_CTRL_MSB    _u(31)
#define DMA_CH6_AL3_CTRL_LSB    _u(0)
#define DMA_CH6_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL3_WRITE_ADDR
// Description : Alias for channel 6 WRITE_ADDR register
#define DMA_CH6_AL3_WRITE_ADDR_OFFSET _u(0x000001b4)
#define DMA_CH6_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH6_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH6_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH6_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH6_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL3_TRANS_COUNT
// Description : Alias for channel 6 TRANS_COUNT register
#define DMA_CH6_AL3_TRANS_COUNT_OFFSET _u(0x000001b8)
#define DMA_CH6_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH6_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH6_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH6_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH6_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH6_AL3_READ_ADDR_TRIG
// Description : Alias for channel 6 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH6_AL3_READ_ADDR_TRIG_OFFSET _u(0x000001bc)
#define DMA_CH6_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH6_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH6_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH6_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH6_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_READ_ADDR
// Description : DMA Channel 7 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH7_READ_ADDR_OFFSET _u(0x000001c0)
#define DMA_CH7_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH7_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH7_READ_ADDR_MSB    _u(31)
#define DMA_CH7_READ_ADDR_LSB    _u(0)
#define DMA_CH7_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_WRITE_ADDR
// Description : DMA Channel 7 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH7_WRITE_ADDR_OFFSET _u(0x000001c4)
#define DMA_CH7_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH7_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH7_WRITE_ADDR_MSB    _u(31)
#define DMA_CH7_WRITE_ADDR_LSB    _u(0)
#define DMA_CH7_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_TRANS_COUNT
// Description : DMA Channel 7 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH7_TRANS_COUNT_OFFSET _u(0x000001c8)
#define DMA_CH7_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH7_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH7_TRANS_COUNT_MSB    _u(31)
#define DMA_CH7_TRANS_COUNT_LSB    _u(0)
#define DMA_CH7_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_CTRL_TRIG
// Description : DMA Channel 7 Control and Status
#define DMA_CH7_CTRL_TRIG_OFFSET _u(0x000001cc)
#define DMA_CH7_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH7_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH7_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH7_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH7_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH7_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH7_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH7_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH7_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH7_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH7_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH7_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH7_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH7_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH7_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH7_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH7_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH7_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH7_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH7_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH7_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH7_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH7_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH7_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH7_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH7_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH7_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH7_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH7_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH7_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH7_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH7_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH7_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH7_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH7_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH7_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH7_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH7_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH7_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH7_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH7_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH7_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH7_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH7_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH7_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH7_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH7_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH7_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH7_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH7_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH7_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH7_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH7_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH7_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH7_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH7_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH7_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH7_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH7_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH7_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH7_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH7_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH7_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH7_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL1_CTRL
// Description : Alias for channel 7 CTRL register
#define DMA_CH7_AL1_CTRL_OFFSET _u(0x000001d0)
#define DMA_CH7_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH7_AL1_CTRL_RESET  "-"
#define DMA_CH7_AL1_CTRL_MSB    _u(31)
#define DMA_CH7_AL1_CTRL_LSB    _u(0)
#define DMA_CH7_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL1_READ_ADDR
// Description : Alias for channel 7 READ_ADDR register
#define DMA_CH7_AL1_READ_ADDR_OFFSET _u(0x000001d4)
#define DMA_CH7_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH7_AL1_READ_ADDR_RESET  "-"
#define DMA_CH7_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH7_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH7_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL1_WRITE_ADDR
// Description : Alias for channel 7 WRITE_ADDR register
#define DMA_CH7_AL1_WRITE_ADDR_OFFSET _u(0x000001d8)
#define DMA_CH7_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH7_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH7_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH7_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH7_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 7 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH7_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x000001dc)
#define DMA_CH7_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH7_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH7_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH7_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH7_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL2_CTRL
// Description : Alias for channel 7 CTRL register
#define DMA_CH7_AL2_CTRL_OFFSET _u(0x000001e0)
#define DMA_CH7_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH7_AL2_CTRL_RESET  "-"
#define DMA_CH7_AL2_CTRL_MSB    _u(31)
#define DMA_CH7_AL2_CTRL_LSB    _u(0)
#define DMA_CH7_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL2_TRANS_COUNT
// Description : Alias for channel 7 TRANS_COUNT register
#define DMA_CH7_AL2_TRANS_COUNT_OFFSET _u(0x000001e4)
#define DMA_CH7_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH7_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH7_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH7_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH7_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL2_READ_ADDR
// Description : Alias for channel 7 READ_ADDR register
#define DMA_CH7_AL2_READ_ADDR_OFFSET _u(0x000001e8)
#define DMA_CH7_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH7_AL2_READ_ADDR_RESET  "-"
#define DMA_CH7_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH7_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH7_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 7 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH7_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x000001ec)
#define DMA_CH7_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH7_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH7_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH7_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH7_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL3_CTRL
// Description : Alias for channel 7 CTRL register
#define DMA_CH7_AL3_CTRL_OFFSET _u(0x000001f0)
#define DMA_CH7_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH7_AL3_CTRL_RESET  "-"
#define DMA_CH7_AL3_CTRL_MSB    _u(31)
#define DMA_CH7_AL3_CTRL_LSB    _u(0)
#define DMA_CH7_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL3_WRITE_ADDR
// Description : Alias for channel 7 WRITE_ADDR register
#define DMA_CH7_AL3_WRITE_ADDR_OFFSET _u(0x000001f4)
#define DMA_CH7_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH7_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH7_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH7_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH7_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL3_TRANS_COUNT
// Description : Alias for channel 7 TRANS_COUNT register
#define DMA_CH7_AL3_TRANS_COUNT_OFFSET _u(0x000001f8)
#define DMA_CH7_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH7_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH7_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH7_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH7_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH7_AL3_READ_ADDR_TRIG
// Description : Alias for channel 7 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH7_AL3_READ_ADDR_TRIG_OFFSET _u(0x000001fc)
#define DMA_CH7_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH7_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH7_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH7_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH7_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_READ_ADDR
// Description : DMA Channel 8 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH8_READ_ADDR_OFFSET _u(0x00000200)
#define DMA_CH8_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH8_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH8_READ_ADDR_MSB    _u(31)
#define DMA_CH8_READ_ADDR_LSB    _u(0)
#define DMA_CH8_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_WRITE_ADDR
// Description : DMA Channel 8 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH8_WRITE_ADDR_OFFSET _u(0x00000204)
#define DMA_CH8_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH8_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH8_WRITE_ADDR_MSB    _u(31)
#define DMA_CH8_WRITE_ADDR_LSB    _u(0)
#define DMA_CH8_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_TRANS_COUNT
// Description : DMA Channel 8 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH8_TRANS_COUNT_OFFSET _u(0x00000208)
#define DMA_CH8_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH8_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH8_TRANS_COUNT_MSB    _u(31)
#define DMA_CH8_TRANS_COUNT_LSB    _u(0)
#define DMA_CH8_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_CTRL_TRIG
// Description : DMA Channel 8 Control and Status
#define DMA_CH8_CTRL_TRIG_OFFSET _u(0x0000020c)
#define DMA_CH8_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH8_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH8_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH8_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH8_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH8_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH8_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH8_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH8_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH8_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH8_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH8_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH8_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH8_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH8_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH8_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH8_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH8_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH8_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH8_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH8_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH8_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH8_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH8_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH8_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH8_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH8_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH8_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH8_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH8_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH8_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH8_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH8_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH8_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH8_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH8_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH8_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH8_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH8_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH8_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH8_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH8_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH8_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH8_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH8_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH8_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH8_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH8_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH8_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH8_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH8_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH8_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH8_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH8_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH8_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH8_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH8_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH8_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH8_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH8_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH8_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH8_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH8_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH8_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL1_CTRL
// Description : Alias for channel 8 CTRL register
#define DMA_CH8_AL1_CTRL_OFFSET _u(0x00000210)
#define DMA_CH8_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH8_AL1_CTRL_RESET  "-"
#define DMA_CH8_AL1_CTRL_MSB    _u(31)
#define DMA_CH8_AL1_CTRL_LSB    _u(0)
#define DMA_CH8_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL1_READ_ADDR
// Description : Alias for channel 8 READ_ADDR register
#define DMA_CH8_AL1_READ_ADDR_OFFSET _u(0x00000214)
#define DMA_CH8_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH8_AL1_READ_ADDR_RESET  "-"
#define DMA_CH8_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH8_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH8_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL1_WRITE_ADDR
// Description : Alias for channel 8 WRITE_ADDR register
#define DMA_CH8_AL1_WRITE_ADDR_OFFSET _u(0x00000218)
#define DMA_CH8_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH8_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH8_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH8_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH8_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 8 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH8_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x0000021c)
#define DMA_CH8_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH8_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH8_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH8_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH8_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL2_CTRL
// Description : Alias for channel 8 CTRL register
#define DMA_CH8_AL2_CTRL_OFFSET _u(0x00000220)
#define DMA_CH8_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH8_AL2_CTRL_RESET  "-"
#define DMA_CH8_AL2_CTRL_MSB    _u(31)
#define DMA_CH8_AL2_CTRL_LSB    _u(0)
#define DMA_CH8_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL2_TRANS_COUNT
// Description : Alias for channel 8 TRANS_COUNT register
#define DMA_CH8_AL2_TRANS_COUNT_OFFSET _u(0x00000224)
#define DMA_CH8_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH8_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH8_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH8_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH8_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL2_READ_ADDR
// Description : Alias for channel 8 READ_ADDR register
#define DMA_CH8_AL2_READ_ADDR_OFFSET _u(0x00000228)
#define DMA_CH8_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH8_AL2_READ_ADDR_RESET  "-"
#define DMA_CH8_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH8_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH8_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 8 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH8_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x0000022c)
#define DMA_CH8_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH8_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH8_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH8_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH8_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL3_CTRL
// Description : Alias for channel 8 CTRL register
#define DMA_CH8_AL3_CTRL_OFFSET _u(0x00000230)
#define DMA_CH8_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH8_AL3_CTRL_RESET  "-"
#define DMA_CH8_AL3_CTRL_MSB    _u(31)
#define DMA_CH8_AL3_CTRL_LSB    _u(0)
#define DMA_CH8_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL3_WRITE_ADDR
// Description : Alias for channel 8 WRITE_ADDR register
#define DMA_CH8_AL3_WRITE_ADDR_OFFSET _u(0x00000234)
#define DMA_CH8_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH8_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH8_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH8_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH8_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL3_TRANS_COUNT
// Description : Alias for channel 8 TRANS_COUNT register
#define DMA_CH8_AL3_TRANS_COUNT_OFFSET _u(0x00000238)
#define DMA_CH8_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH8_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH8_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH8_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH8_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH8_AL3_READ_ADDR_TRIG
// Description : Alias for channel 8 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH8_AL3_READ_ADDR_TRIG_OFFSET _u(0x0000023c)
#define DMA_CH8_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH8_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH8_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH8_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH8_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_READ_ADDR
// Description : DMA Channel 9 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH9_READ_ADDR_OFFSET _u(0x00000240)
#define DMA_CH9_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH9_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH9_READ_ADDR_MSB    _u(31)
#define DMA_CH9_READ_ADDR_LSB    _u(0)
#define DMA_CH9_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_WRITE_ADDR
// Description : DMA Channel 9 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH9_WRITE_ADDR_OFFSET _u(0x00000244)
#define DMA_CH9_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH9_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH9_WRITE_ADDR_MSB    _u(31)
#define DMA_CH9_WRITE_ADDR_LSB    _u(0)
#define DMA_CH9_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_TRANS_COUNT
// Description : DMA Channel 9 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH9_TRANS_COUNT_OFFSET _u(0x00000248)
#define DMA_CH9_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH9_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH9_TRANS_COUNT_MSB    _u(31)
#define DMA_CH9_TRANS_COUNT_LSB    _u(0)
#define DMA_CH9_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_CTRL_TRIG
// Description : DMA Channel 9 Control and Status
#define DMA_CH9_CTRL_TRIG_OFFSET _u(0x0000024c)
#define DMA_CH9_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH9_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH9_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH9_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH9_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH9_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH9_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH9_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH9_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH9_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH9_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH9_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH9_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH9_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH9_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH9_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH9_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH9_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH9_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH9_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH9_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH9_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH9_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH9_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH9_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH9_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH9_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH9_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH9_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH9_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH9_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH9_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH9_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH9_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH9_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH9_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH9_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH9_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH9_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH9_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH9_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH9_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH9_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH9_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH9_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH9_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH9_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH9_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH9_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH9_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH9_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH9_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH9_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH9_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH9_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH9_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH9_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH9_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH9_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH9_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH9_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH9_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH9_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH9_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL1_CTRL
// Description : Alias for channel 9 CTRL register
#define DMA_CH9_AL1_CTRL_OFFSET _u(0x00000250)
#define DMA_CH9_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH9_AL1_CTRL_RESET  "-"
#define DMA_CH9_AL1_CTRL_MSB    _u(31)
#define DMA_CH9_AL1_CTRL_LSB    _u(0)
#define DMA_CH9_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL1_READ_ADDR
// Description : Alias for channel 9 READ_ADDR register
#define DMA_CH9_AL1_READ_ADDR_OFFSET _u(0x00000254)
#define DMA_CH9_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH9_AL1_READ_ADDR_RESET  "-"
#define DMA_CH9_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH9_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH9_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL1_WRITE_ADDR
// Description : Alias for channel 9 WRITE_ADDR register
#define DMA_CH9_AL1_WRITE_ADDR_OFFSET _u(0x00000258)
#define DMA_CH9_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH9_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH9_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH9_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH9_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 9 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH9_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x0000025c)
#define DMA_CH9_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH9_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH9_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH9_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH9_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL2_CTRL
// Description : Alias for channel 9 CTRL register
#define DMA_CH9_AL2_CTRL_OFFSET _u(0x00000260)
#define DMA_CH9_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH9_AL2_CTRL_RESET  "-"
#define DMA_CH9_AL2_CTRL_MSB    _u(31)
#define DMA_CH9_AL2_CTRL_LSB    _u(0)
#define DMA_CH9_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL2_TRANS_COUNT
// Description : Alias for channel 9 TRANS_COUNT register
#define DMA_CH9_AL2_TRANS_COUNT_OFFSET _u(0x00000264)
#define DMA_CH9_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH9_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH9_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH9_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH9_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL2_READ_ADDR
// Description : Alias for channel 9 READ_ADDR register
#define DMA_CH9_AL2_READ_ADDR_OFFSET _u(0x00000268)
#define DMA_CH9_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH9_AL2_READ_ADDR_RESET  "-"
#define DMA_CH9_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH9_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH9_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 9 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH9_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x0000026c)
#define DMA_CH9_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH9_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH9_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH9_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH9_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL3_CTRL
// Description : Alias for channel 9 CTRL register
#define DMA_CH9_AL3_CTRL_OFFSET _u(0x00000270)
#define DMA_CH9_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH9_AL3_CTRL_RESET  "-"
#define DMA_CH9_AL3_CTRL_MSB    _u(31)
#define DMA_CH9_AL3_CTRL_LSB    _u(0)
#define DMA_CH9_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL3_WRITE_ADDR
// Description : Alias for channel 9 WRITE_ADDR register
#define DMA_CH9_AL3_WRITE_ADDR_OFFSET _u(0x00000274)
#define DMA_CH9_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH9_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH9_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH9_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH9_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL3_TRANS_COUNT
// Description : Alias for channel 9 TRANS_COUNT register
#define DMA_CH9_AL3_TRANS_COUNT_OFFSET _u(0x00000278)
#define DMA_CH9_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH9_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH9_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH9_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH9_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH9_AL3_READ_ADDR_TRIG
// Description : Alias for channel 9 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH9_AL3_READ_ADDR_TRIG_OFFSET _u(0x0000027c)
#define DMA_CH9_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH9_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH9_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH9_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH9_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_READ_ADDR
// Description : DMA Channel 10 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH10_READ_ADDR_OFFSET _u(0x00000280)
#define DMA_CH10_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH10_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH10_READ_ADDR_MSB    _u(31)
#define DMA_CH10_READ_ADDR_LSB    _u(0)
#define DMA_CH10_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_WRITE_ADDR
// Description : DMA Channel 10 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH10_WRITE_ADDR_OFFSET _u(0x00000284)
#define DMA_CH10_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH10_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH10_WRITE_ADDR_MSB    _u(31)
#define DMA_CH10_WRITE_ADDR_LSB    _u(0)
#define DMA_CH10_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_TRANS_COUNT
// Description : DMA Channel 10 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH10_TRANS_COUNT_OFFSET _u(0x00000288)
#define DMA_CH10_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH10_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH10_TRANS_COUNT_MSB    _u(31)
#define DMA_CH10_TRANS_COUNT_LSB    _u(0)
#define DMA_CH10_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_CTRL_TRIG
// Description : DMA Channel 10 Control and Status
#define DMA_CH10_CTRL_TRIG_OFFSET _u(0x0000028c)
#define DMA_CH10_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH10_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH10_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH10_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH10_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH10_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH10_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH10_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH10_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH10_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH10_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH10_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH10_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH10_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH10_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH10_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH10_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH10_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH10_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH10_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH10_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH10_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH10_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH10_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH10_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH10_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH10_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH10_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH10_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH10_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH10_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH10_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH10_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH10_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH10_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH10_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH10_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH10_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH10_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH10_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH10_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH10_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH10_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH10_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH10_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH10_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH10_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH10_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH10_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH10_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH10_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH10_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH10_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH10_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH10_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH10_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH10_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH10_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH10_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH10_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH10_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH10_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH10_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH10_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL1_CTRL
// Description : Alias for channel 10 CTRL register
#define DMA_CH10_AL1_CTRL_OFFSET _u(0x00000290)
#define DMA_CH10_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH10_AL1_CTRL_RESET  "-"
#define DMA_CH10_AL1_CTRL_MSB    _u(31)
#define DMA_CH10_AL1_CTRL_LSB    _u(0)
#define DMA_CH10_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL1_READ_ADDR
// Description : Alias for channel 10 READ_ADDR register
#define DMA_CH10_AL1_READ_ADDR_OFFSET _u(0x00000294)
#define DMA_CH10_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH10_AL1_READ_ADDR_RESET  "-"
#define DMA_CH10_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH10_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH10_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL1_WRITE_ADDR
// Description : Alias for channel 10 WRITE_ADDR register
#define DMA_CH10_AL1_WRITE_ADDR_OFFSET _u(0x00000298)
#define DMA_CH10_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH10_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH10_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH10_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH10_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 10 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH10_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x0000029c)
#define DMA_CH10_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH10_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH10_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH10_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH10_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL2_CTRL
// Description : Alias for channel 10 CTRL register
#define DMA_CH10_AL2_CTRL_OFFSET _u(0x000002a0)
#define DMA_CH10_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH10_AL2_CTRL_RESET  "-"
#define DMA_CH10_AL2_CTRL_MSB    _u(31)
#define DMA_CH10_AL2_CTRL_LSB    _u(0)
#define DMA_CH10_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL2_TRANS_COUNT
// Description : Alias for channel 10 TRANS_COUNT register
#define DMA_CH10_AL2_TRANS_COUNT_OFFSET _u(0x000002a4)
#define DMA_CH10_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH10_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH10_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH10_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH10_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL2_READ_ADDR
// Description : Alias for channel 10 READ_ADDR register
#define DMA_CH10_AL2_READ_ADDR_OFFSET _u(0x000002a8)
#define DMA_CH10_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH10_AL2_READ_ADDR_RESET  "-"
#define DMA_CH10_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH10_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH10_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 10 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH10_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x000002ac)
#define DMA_CH10_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH10_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH10_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH10_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH10_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL3_CTRL
// Description : Alias for channel 10 CTRL register
#define DMA_CH10_AL3_CTRL_OFFSET _u(0x000002b0)
#define DMA_CH10_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH10_AL3_CTRL_RESET  "-"
#define DMA_CH10_AL3_CTRL_MSB    _u(31)
#define DMA_CH10_AL3_CTRL_LSB    _u(0)
#define DMA_CH10_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL3_WRITE_ADDR
// Description : Alias for channel 10 WRITE_ADDR register
#define DMA_CH10_AL3_WRITE_ADDR_OFFSET _u(0x000002b4)
#define DMA_CH10_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH10_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH10_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH10_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH10_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL3_TRANS_COUNT
// Description : Alias for channel 10 TRANS_COUNT register
#define DMA_CH10_AL3_TRANS_COUNT_OFFSET _u(0x000002b8)
#define DMA_CH10_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH10_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH10_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH10_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH10_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH10_AL3_READ_ADDR_TRIG
// Description : Alias for channel 10 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH10_AL3_READ_ADDR_TRIG_OFFSET _u(0x000002bc)
#define DMA_CH10_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH10_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH10_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH10_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH10_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_READ_ADDR
// Description : DMA Channel 11 Read Address pointer
//               This register updates automatically each time a read completes.
//               The current value is the next address to be read by this
//               channel.
#define DMA_CH11_READ_ADDR_OFFSET _u(0x000002c0)
#define DMA_CH11_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH11_READ_ADDR_RESET  _u(0x00000000)
#define DMA_CH11_READ_ADDR_MSB    _u(31)
#define DMA_CH11_READ_ADDR_LSB    _u(0)
#define DMA_CH11_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_WRITE_ADDR
// Description : DMA Channel 11 Write Address pointer
//               This register updates automatically each time a write
//               completes. The current value is the next address to be written
//               by this channel.
#define DMA_CH11_WRITE_ADDR_OFFSET _u(0x000002c4)
#define DMA_CH11_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH11_WRITE_ADDR_RESET  _u(0x00000000)
#define DMA_CH11_WRITE_ADDR_MSB    _u(31)
#define DMA_CH11_WRITE_ADDR_LSB    _u(0)
#define DMA_CH11_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_TRANS_COUNT
// Description : DMA Channel 11 Transfer Count
//               Program the number of bus transfers a channel will perform
//               before halting. Note that, if transfers are larger than one
//               byte in size, this is not equal to the number of bytes
//               transferred (see CTRL_DATA_SIZE).
//
//               When the channel is active, reading this register shows the
//               number of transfers remaining, updating automatically each time
//               a write transfer completes.
//
//               Writing this register sets the RELOAD value for the transfer
//               counter. Each time this channel is triggered, the RELOAD value
//               is copied into the live transfer counter. The channel can be
//               started multiple times, and will perform the same number of
//               transfers each time, as programmed by most recent write.
//
//               The RELOAD value can be observed at CHx_DBG_TCR. If TRANS_COUNT
//               is used as a trigger, the written value is used immediately as
//               the length of the new transfer sequence, as well as being
//               written to RELOAD.
#define DMA_CH11_TRANS_COUNT_OFFSET _u(0x000002c8)
#define DMA_CH11_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH11_TRANS_COUNT_RESET  _u(0x00000000)
#define DMA_CH11_TRANS_COUNT_MSB    _u(31)
#define DMA_CH11_TRANS_COUNT_LSB    _u(0)
#define DMA_CH11_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_CTRL_TRIG
// Description : DMA Channel 11 Control and Status
#define DMA_CH11_CTRL_TRIG_OFFSET _u(0x000002cc)
#define DMA_CH11_CTRL_TRIG_BITS   _u(0xe1ffffff)
#define DMA_CH11_CTRL_TRIG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_AHB_ERROR
// Description : Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
//               halts when it encounters any bus error, and always raises its
//               channel IRQ flag.
#define DMA_CH11_CTRL_TRIG_AHB_ERROR_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_AHB_ERROR_BITS   _u(0x80000000)
#define DMA_CH11_CTRL_TRIG_AHB_ERROR_MSB    _u(31)
#define DMA_CH11_CTRL_TRIG_AHB_ERROR_LSB    _u(31)
#define DMA_CH11_CTRL_TRIG_AHB_ERROR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_READ_ERROR
// Description : If 1, the channel received a read bus error. Write one to
//               clear.
//               READ_ADDR shows the approximate address where the bus error was
//               encountered (will not be earlier, or more than 3 transfers
//               later)
#define DMA_CH11_CTRL_TRIG_READ_ERROR_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_READ_ERROR_BITS   _u(0x40000000)
#define DMA_CH11_CTRL_TRIG_READ_ERROR_MSB    _u(30)
#define DMA_CH11_CTRL_TRIG_READ_ERROR_LSB    _u(30)
#define DMA_CH11_CTRL_TRIG_READ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_WRITE_ERROR
// Description : If 1, the channel received a write bus error. Write one to
//               clear.
//               WRITE_ADDR shows the approximate address where the bus error
//               was encountered (will not be earlier, or more than 5 transfers
//               later)
#define DMA_CH11_CTRL_TRIG_WRITE_ERROR_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_WRITE_ERROR_BITS   _u(0x20000000)
#define DMA_CH11_CTRL_TRIG_WRITE_ERROR_MSB    _u(29)
#define DMA_CH11_CTRL_TRIG_WRITE_ERROR_LSB    _u(29)
#define DMA_CH11_CTRL_TRIG_WRITE_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_BUSY
// Description : This flag goes high when the channel starts a new transfer
//               sequence, and low when the last transfer of that sequence
//               completes. Clearing EN while BUSY is high pauses the channel,
//               and BUSY will stay high while paused.
//
//               To terminate a sequence early (and clear the BUSY flag), see
//               CHAN_ABORT.
#define DMA_CH11_CTRL_TRIG_BUSY_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_BUSY_BITS   _u(0x01000000)
#define DMA_CH11_CTRL_TRIG_BUSY_MSB    _u(24)
#define DMA_CH11_CTRL_TRIG_BUSY_LSB    _u(24)
#define DMA_CH11_CTRL_TRIG_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_SNIFF_EN
// Description : If 1, this channel's data transfers are visible to the sniff
//               hardware, and each transfer will advance the state of the
//               checksum. This only applies if the sniff hardware is enabled,
//               and has this channel selected.
//
//               This allows checksum to be enabled or disabled on a
//               per-control- block basis.
#define DMA_CH11_CTRL_TRIG_SNIFF_EN_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_SNIFF_EN_BITS   _u(0x00800000)
#define DMA_CH11_CTRL_TRIG_SNIFF_EN_MSB    _u(23)
#define DMA_CH11_CTRL_TRIG_SNIFF_EN_LSB    _u(23)
#define DMA_CH11_CTRL_TRIG_SNIFF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_BSWAP
// Description : Apply byte-swap transformation to DMA data.
//               For byte data, this has no effect. For halfword data, the two
//               bytes of each halfword are swapped. For word data, the four
//               bytes of each word are swapped to reverse order.
#define DMA_CH11_CTRL_TRIG_BSWAP_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_BSWAP_BITS   _u(0x00400000)
#define DMA_CH11_CTRL_TRIG_BSWAP_MSB    _u(22)
#define DMA_CH11_CTRL_TRIG_BSWAP_LSB    _u(22)
#define DMA_CH11_CTRL_TRIG_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_IRQ_QUIET
// Description : In QUIET mode, the channel does not generate IRQs at the end of
//               every transfer block. Instead, an IRQ is raised when NULL is
//               written to a trigger register, indicating the end of a control
//               block chain.
//
//               This reduces the number of interrupts to be serviced by the CPU
//               when transferring a DMA chain of many small control blocks.
#define DMA_CH11_CTRL_TRIG_IRQ_QUIET_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_IRQ_QUIET_BITS   _u(0x00200000)
#define DMA_CH11_CTRL_TRIG_IRQ_QUIET_MSB    _u(21)
#define DMA_CH11_CTRL_TRIG_IRQ_QUIET_LSB    _u(21)
#define DMA_CH11_CTRL_TRIG_IRQ_QUIET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_TREQ_SEL
// Description : Select a Transfer Request signal.
//               The channel uses the transfer request signal to pace its data
//               transfer rate. Sources for TREQ signals are internal (TIMERS)
//               or external (DREQ, a Data Request from the system).
//               0x0 to 0x3a -> select DREQ n as TREQ
//               0x3b -> Select Timer 0 as TREQ
//               0x3c -> Select Timer 1 as TREQ
//               0x3d -> Select Timer 2 as TREQ (Optional)
//               0x3e -> Select Timer 3 as TREQ (Optional)
//               0x3f -> Permanent request, for unpaced transfers.
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_RESET           _u(0x00)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_BITS            _u(0x001f8000)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_MSB             _u(20)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_LSB             _u(15)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_ACCESS          "RW"
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_VALUE_TIMER0    _u(0x3b)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_VALUE_TIMER1    _u(0x3c)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_VALUE_TIMER2    _u(0x3d)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_VALUE_TIMER3    _u(0x3e)
#define DMA_CH11_CTRL_TRIG_TREQ_SEL_VALUE_PERMANENT _u(0x3f)
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_CHAIN_TO
// Description : When this channel completes, it will trigger the channel
//               indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
//               channel)_.
#define DMA_CH11_CTRL_TRIG_CHAIN_TO_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_CHAIN_TO_BITS   _u(0x00007800)
#define DMA_CH11_CTRL_TRIG_CHAIN_TO_MSB    _u(14)
#define DMA_CH11_CTRL_TRIG_CHAIN_TO_LSB    _u(11)
#define DMA_CH11_CTRL_TRIG_CHAIN_TO_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_RING_SEL
// Description : Select whether RING_SIZE applies to read or write addresses.
//               If 0, read addresses are wrapped on a (1 << RING_SIZE)
//               boundary. If 1, write addresses are wrapped.
#define DMA_CH11_CTRL_TRIG_RING_SEL_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_RING_SEL_BITS   _u(0x00000400)
#define DMA_CH11_CTRL_TRIG_RING_SEL_MSB    _u(10)
#define DMA_CH11_CTRL_TRIG_RING_SEL_LSB    _u(10)
#define DMA_CH11_CTRL_TRIG_RING_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_RING_SIZE
// Description : Size of address wrap region. If 0, don't wrap. For values n >
//               0, only the lower n bits of the address will change. This wraps
//               the address on a (1 << n) byte boundary, facilitating access to
//               naturally-aligned ring buffers.
//
//               Ring sizes between 2 and 32768 bytes are possible. This can
//               apply to either read or write addresses, based on value of
//               RING_SEL.
//               0x0 -> RING_NONE
#define DMA_CH11_CTRL_TRIG_RING_SIZE_RESET           _u(0x0)
#define DMA_CH11_CTRL_TRIG_RING_SIZE_BITS            _u(0x000003c0)
#define DMA_CH11_CTRL_TRIG_RING_SIZE_MSB             _u(9)
#define DMA_CH11_CTRL_TRIG_RING_SIZE_LSB             _u(6)
#define DMA_CH11_CTRL_TRIG_RING_SIZE_ACCESS          "RW"
#define DMA_CH11_CTRL_TRIG_RING_SIZE_VALUE_RING_NONE _u(0x0)
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_INCR_WRITE
// Description : If 1, the write address increments with each transfer. If 0,
//               each write is directed to the same, initial address.
//
//               Generally this should be disabled for memory-to-peripheral
//               transfers.
#define DMA_CH11_CTRL_TRIG_INCR_WRITE_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_INCR_WRITE_BITS   _u(0x00000020)
#define DMA_CH11_CTRL_TRIG_INCR_WRITE_MSB    _u(5)
#define DMA_CH11_CTRL_TRIG_INCR_WRITE_LSB    _u(5)
#define DMA_CH11_CTRL_TRIG_INCR_WRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_INCR_READ
// Description : If 1, the read address increments with each transfer. If 0,
//               each read is directed to the same, initial address.
//
//               Generally this should be disabled for peripheral-to-memory
//               transfers.
#define DMA_CH11_CTRL_TRIG_INCR_READ_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_INCR_READ_BITS   _u(0x00000010)
#define DMA_CH11_CTRL_TRIG_INCR_READ_MSB    _u(4)
#define DMA_CH11_CTRL_TRIG_INCR_READ_LSB    _u(4)
#define DMA_CH11_CTRL_TRIG_INCR_READ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_DATA_SIZE
// Description : Set the size of each bus transfer (byte/halfword/word).
//               READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
//               with each transfer.
//               0x0 -> SIZE_BYTE
//               0x1 -> SIZE_HALFWORD
//               0x2 -> SIZE_WORD
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_RESET               _u(0x0)
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_BITS                _u(0x0000000c)
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_MSB                 _u(3)
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_LSB                 _u(2)
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_ACCESS              "RW"
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_BYTE     _u(0x0)
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_HALFWORD _u(0x1)
#define DMA_CH11_CTRL_TRIG_DATA_SIZE_VALUE_SIZE_WORD     _u(0x2)
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_HIGH_PRIORITY
// Description : HIGH_PRIORITY gives a channel preferential treatment in issue
//               scheduling: in each scheduling round, all high priority
//               channels are considered first, and then only a single low
//               priority channel, before returning to the high priority
//               channels.
//
//               This only affects the order in which the DMA schedules
//               channels. The DMA's bus priority is not changed. If the DMA is
//               not saturated then a low priority channel will see no loss of
//               throughput.
#define DMA_CH11_CTRL_TRIG_HIGH_PRIORITY_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_HIGH_PRIORITY_BITS   _u(0x00000002)
#define DMA_CH11_CTRL_TRIG_HIGH_PRIORITY_MSB    _u(1)
#define DMA_CH11_CTRL_TRIG_HIGH_PRIORITY_LSB    _u(1)
#define DMA_CH11_CTRL_TRIG_HIGH_PRIORITY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_CH11_CTRL_TRIG_EN
// Description : DMA Channel Enable.
//               When 1, the channel will respond to triggering events, which
//               will cause it to become BUSY and start transferring data. When
//               0, the channel will ignore triggers, stop issuing transfers,
//               and pause the current transfer sequence (i.e. BUSY will remain
//               high if already high)
#define DMA_CH11_CTRL_TRIG_EN_RESET  _u(0x0)
#define DMA_CH11_CTRL_TRIG_EN_BITS   _u(0x00000001)
#define DMA_CH11_CTRL_TRIG_EN_MSB    _u(0)
#define DMA_CH11_CTRL_TRIG_EN_LSB    _u(0)
#define DMA_CH11_CTRL_TRIG_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL1_CTRL
// Description : Alias for channel 11 CTRL register
#define DMA_CH11_AL1_CTRL_OFFSET _u(0x000002d0)
#define DMA_CH11_AL1_CTRL_BITS   _u(0xffffffff)
#define DMA_CH11_AL1_CTRL_RESET  "-"
#define DMA_CH11_AL1_CTRL_MSB    _u(31)
#define DMA_CH11_AL1_CTRL_LSB    _u(0)
#define DMA_CH11_AL1_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL1_READ_ADDR
// Description : Alias for channel 11 READ_ADDR register
#define DMA_CH11_AL1_READ_ADDR_OFFSET _u(0x000002d4)
#define DMA_CH11_AL1_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH11_AL1_READ_ADDR_RESET  "-"
#define DMA_CH11_AL1_READ_ADDR_MSB    _u(31)
#define DMA_CH11_AL1_READ_ADDR_LSB    _u(0)
#define DMA_CH11_AL1_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL1_WRITE_ADDR
// Description : Alias for channel 11 WRITE_ADDR register
#define DMA_CH11_AL1_WRITE_ADDR_OFFSET _u(0x000002d8)
#define DMA_CH11_AL1_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH11_AL1_WRITE_ADDR_RESET  "-"
#define DMA_CH11_AL1_WRITE_ADDR_MSB    _u(31)
#define DMA_CH11_AL1_WRITE_ADDR_LSB    _u(0)
#define DMA_CH11_AL1_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL1_TRANS_COUNT_TRIG
// Description : Alias for channel 11 TRANS_COUNT register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH11_AL1_TRANS_COUNT_TRIG_OFFSET _u(0x000002dc)
#define DMA_CH11_AL1_TRANS_COUNT_TRIG_BITS   _u(0xffffffff)
#define DMA_CH11_AL1_TRANS_COUNT_TRIG_RESET  "-"
#define DMA_CH11_AL1_TRANS_COUNT_TRIG_MSB    _u(31)
#define DMA_CH11_AL1_TRANS_COUNT_TRIG_LSB    _u(0)
#define DMA_CH11_AL1_TRANS_COUNT_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL2_CTRL
// Description : Alias for channel 11 CTRL register
#define DMA_CH11_AL2_CTRL_OFFSET _u(0x000002e0)
#define DMA_CH11_AL2_CTRL_BITS   _u(0xffffffff)
#define DMA_CH11_AL2_CTRL_RESET  "-"
#define DMA_CH11_AL2_CTRL_MSB    _u(31)
#define DMA_CH11_AL2_CTRL_LSB    _u(0)
#define DMA_CH11_AL2_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL2_TRANS_COUNT
// Description : Alias for channel 11 TRANS_COUNT register
#define DMA_CH11_AL2_TRANS_COUNT_OFFSET _u(0x000002e4)
#define DMA_CH11_AL2_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH11_AL2_TRANS_COUNT_RESET  "-"
#define DMA_CH11_AL2_TRANS_COUNT_MSB    _u(31)
#define DMA_CH11_AL2_TRANS_COUNT_LSB    _u(0)
#define DMA_CH11_AL2_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL2_READ_ADDR
// Description : Alias for channel 11 READ_ADDR register
#define DMA_CH11_AL2_READ_ADDR_OFFSET _u(0x000002e8)
#define DMA_CH11_AL2_READ_ADDR_BITS   _u(0xffffffff)
#define DMA_CH11_AL2_READ_ADDR_RESET  "-"
#define DMA_CH11_AL2_READ_ADDR_MSB    _u(31)
#define DMA_CH11_AL2_READ_ADDR_LSB    _u(0)
#define DMA_CH11_AL2_READ_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL2_WRITE_ADDR_TRIG
// Description : Alias for channel 11 WRITE_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH11_AL2_WRITE_ADDR_TRIG_OFFSET _u(0x000002ec)
#define DMA_CH11_AL2_WRITE_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH11_AL2_WRITE_ADDR_TRIG_RESET  "-"
#define DMA_CH11_AL2_WRITE_ADDR_TRIG_MSB    _u(31)
#define DMA_CH11_AL2_WRITE_ADDR_TRIG_LSB    _u(0)
#define DMA_CH11_AL2_WRITE_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL3_CTRL
// Description : Alias for channel 11 CTRL register
#define DMA_CH11_AL3_CTRL_OFFSET _u(0x000002f0)
#define DMA_CH11_AL3_CTRL_BITS   _u(0xffffffff)
#define DMA_CH11_AL3_CTRL_RESET  "-"
#define DMA_CH11_AL3_CTRL_MSB    _u(31)
#define DMA_CH11_AL3_CTRL_LSB    _u(0)
#define DMA_CH11_AL3_CTRL_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL3_WRITE_ADDR
// Description : Alias for channel 11 WRITE_ADDR register
#define DMA_CH11_AL3_WRITE_ADDR_OFFSET _u(0x000002f4)
#define DMA_CH11_AL3_WRITE_ADDR_BITS   _u(0xffffffff)
#define DMA_CH11_AL3_WRITE_ADDR_RESET  "-"
#define DMA_CH11_AL3_WRITE_ADDR_MSB    _u(31)
#define DMA_CH11_AL3_WRITE_ADDR_LSB    _u(0)
#define DMA_CH11_AL3_WRITE_ADDR_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL3_TRANS_COUNT
// Description : Alias for channel 11 TRANS_COUNT register
#define DMA_CH11_AL3_TRANS_COUNT_OFFSET _u(0x000002f8)
#define DMA_CH11_AL3_TRANS_COUNT_BITS   _u(0xffffffff)
#define DMA_CH11_AL3_TRANS_COUNT_RESET  "-"
#define DMA_CH11_AL3_TRANS_COUNT_MSB    _u(31)
#define DMA_CH11_AL3_TRANS_COUNT_LSB    _u(0)
#define DMA_CH11_AL3_TRANS_COUNT_ACCESS "RW"
// =============================================================================
// Register    : DMA_CH11_AL3_READ_ADDR_TRIG
// Description : Alias for channel 11 READ_ADDR register
//               This is a trigger register (0xc). Writing a nonzero value will
//               reload the channel counter and start the channel.
#define DMA_CH11_AL3_READ_ADDR_TRIG_OFFSET _u(0x000002fc)
#define DMA_CH11_AL3_READ_ADDR_TRIG_BITS   _u(0xffffffff)
#define DMA_CH11_AL3_READ_ADDR_TRIG_RESET  "-"
#define DMA_CH11_AL3_READ_ADDR_TRIG_MSB    _u(31)
#define DMA_CH11_AL3_READ_ADDR_TRIG_LSB    _u(0)
#define DMA_CH11_AL3_READ_ADDR_TRIG_ACCESS "RW"
// =============================================================================
// Register    : DMA_INTR
// Description : Interrupt Status (raw)
//               Raw interrupt status for DMA Channels 0..15. Bit n corresponds
//               to channel n. Ignores any masking or forcing. Channel
//               interrupts can be cleared by writing a bit mask to INTR, INTS0
//               or INTS1.
//
//               Channel interrupts can be routed to either of two system-level
//               IRQs based on INTE0 and INTE1.
//
//               This can be used vector different channel interrupts to
//               different ISRs: this might be done to allow NVIC IRQ preemption
//               for more time-critical channels, or to spread IRQ load across
//               different cores.
//
//               It is also valid to ignore this behaviour and just use
//               INTE0/INTS0/IRQ 0.
#define DMA_INTR_OFFSET _u(0x00000400)
#define DMA_INTR_BITS   _u(0x0000ffff)
#define DMA_INTR_RESET  _u(0x00000000)
#define DMA_INTR_MSB    _u(15)
#define DMA_INTR_LSB    _u(0)
#define DMA_INTR_ACCESS "WC"
// =============================================================================
// Register    : DMA_INTE0
// Description : Interrupt Enables for IRQ 0
//               Set bit n to pass interrupts from channel n to DMA IRQ 0.
#define DMA_INTE0_OFFSET _u(0x00000404)
#define DMA_INTE0_BITS   _u(0x0000ffff)
#define DMA_INTE0_RESET  _u(0x00000000)
#define DMA_INTE0_MSB    _u(15)
#define DMA_INTE0_LSB    _u(0)
#define DMA_INTE0_ACCESS "RW"
// =============================================================================
// Register    : DMA_INTF0
// Description : Force Interrupts
//               Write 1s to force the corresponding bits in INTE0. The
//               interrupt remains asserted until INTF0 is cleared.
#define DMA_INTF0_OFFSET _u(0x00000408)
#define DMA_INTF0_BITS   _u(0x0000ffff)
#define DMA_INTF0_RESET  _u(0x00000000)
#define DMA_INTF0_MSB    _u(15)
#define DMA_INTF0_LSB    _u(0)
#define DMA_INTF0_ACCESS "RW"
// =============================================================================
// Register    : DMA_INTS0
// Description : Interrupt Status for IRQ 0
//               Indicates active channel interrupt requests which are currently
//               causing IRQ 0 to be asserted.
//               Channel interrupts can be cleared by writing a bit mask here.
#define DMA_INTS0_OFFSET _u(0x0000040c)
#define DMA_INTS0_BITS   _u(0x0000ffff)
#define DMA_INTS0_RESET  _u(0x00000000)
#define DMA_INTS0_MSB    _u(15)
#define DMA_INTS0_LSB    _u(0)
#define DMA_INTS0_ACCESS "WC"
// =============================================================================
// Register    : DMA_INTE1
// Description : Interrupt Enables for IRQ 1
//               Set bit n to pass interrupts from channel n to DMA IRQ 1.
#define DMA_INTE1_OFFSET _u(0x00000414)
#define DMA_INTE1_BITS   _u(0x0000ffff)
#define DMA_INTE1_RESET  _u(0x00000000)
#define DMA_INTE1_MSB    _u(15)
#define DMA_INTE1_LSB    _u(0)
#define DMA_INTE1_ACCESS "RW"
// =============================================================================
// Register    : DMA_INTF1
// Description : Force Interrupts for IRQ 1
//               Write 1s to force the corresponding bits in INTE0. The
//               interrupt remains asserted until INTF0 is cleared.
#define DMA_INTF1_OFFSET _u(0x00000418)
#define DMA_INTF1_BITS   _u(0x0000ffff)
#define DMA_INTF1_RESET  _u(0x00000000)
#define DMA_INTF1_MSB    _u(15)
#define DMA_INTF1_LSB    _u(0)
#define DMA_INTF1_ACCESS "RW"
// =============================================================================
// Register    : DMA_INTS1
// Description : Interrupt Status (masked) for IRQ 1
//               Indicates active channel interrupt requests which are currently
//               causing IRQ 1 to be asserted.
//               Channel interrupts can be cleared by writing a bit mask here.
#define DMA_INTS1_OFFSET _u(0x0000041c)
#define DMA_INTS1_BITS   _u(0x0000ffff)
#define DMA_INTS1_RESET  _u(0x00000000)
#define DMA_INTS1_MSB    _u(15)
#define DMA_INTS1_LSB    _u(0)
#define DMA_INTS1_ACCESS "WC"
// =============================================================================
// Register    : DMA_TIMER0
// Description : Pacing (X/Y) Fractional Timer
//               The pacing timer produces TREQ assertions at a rate set by
//               ((X/Y) * sys_clk). This equation is evaluated every sys_clk
//               cycles and therefore can only generate TREQs at a rate of 1 per
//               sys_clk (i.e. permanent TREQ) or less.
#define DMA_TIMER0_OFFSET _u(0x00000420)
#define DMA_TIMER0_BITS   _u(0xffffffff)
#define DMA_TIMER0_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_TIMER0_X
// Description : Pacing Timer Dividend. Specifies the X value for the (X/Y)
//               fractional timer.
#define DMA_TIMER0_X_RESET  _u(0x0000)
#define DMA_TIMER0_X_BITS   _u(0xffff0000)
#define DMA_TIMER0_X_MSB    _u(31)
#define DMA_TIMER0_X_LSB    _u(16)
#define DMA_TIMER0_X_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_TIMER0_Y
// Description : Pacing Timer Divisor. Specifies the Y value for the (X/Y)
//               fractional timer.
#define DMA_TIMER0_Y_RESET  _u(0x0000)
#define DMA_TIMER0_Y_BITS   _u(0x0000ffff)
#define DMA_TIMER0_Y_MSB    _u(15)
#define DMA_TIMER0_Y_LSB    _u(0)
#define DMA_TIMER0_Y_ACCESS "RW"
// =============================================================================
// Register    : DMA_TIMER1
// Description : Pacing (X/Y) Fractional Timer
//               The pacing timer produces TREQ assertions at a rate set by
//               ((X/Y) * sys_clk). This equation is evaluated every sys_clk
//               cycles and therefore can only generate TREQs at a rate of 1 per
//               sys_clk (i.e. permanent TREQ) or less.
#define DMA_TIMER1_OFFSET _u(0x00000424)
#define DMA_TIMER1_BITS   _u(0xffffffff)
#define DMA_TIMER1_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_TIMER1_X
// Description : Pacing Timer Dividend. Specifies the X value for the (X/Y)
//               fractional timer.
#define DMA_TIMER1_X_RESET  _u(0x0000)
#define DMA_TIMER1_X_BITS   _u(0xffff0000)
#define DMA_TIMER1_X_MSB    _u(31)
#define DMA_TIMER1_X_LSB    _u(16)
#define DMA_TIMER1_X_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_TIMER1_Y
// Description : Pacing Timer Divisor. Specifies the Y value for the (X/Y)
//               fractional timer.
#define DMA_TIMER1_Y_RESET  _u(0x0000)
#define DMA_TIMER1_Y_BITS   _u(0x0000ffff)
#define DMA_TIMER1_Y_MSB    _u(15)
#define DMA_TIMER1_Y_LSB    _u(0)
#define DMA_TIMER1_Y_ACCESS "RW"
// =============================================================================
// Register    : DMA_TIMER2
// Description : Pacing (X/Y) Fractional Timer
//               The pacing timer produces TREQ assertions at a rate set by
//               ((X/Y) * sys_clk). This equation is evaluated every sys_clk
//               cycles and therefore can only generate TREQs at a rate of 1 per
//               sys_clk (i.e. permanent TREQ) or less.
#define DMA_TIMER2_OFFSET _u(0x00000428)
#define DMA_TIMER2_BITS   _u(0xffffffff)
#define DMA_TIMER2_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_TIMER2_X
// Description : Pacing Timer Dividend. Specifies the X value for the (X/Y)
//               fractional timer.
#define DMA_TIMER2_X_RESET  _u(0x0000)
#define DMA_TIMER2_X_BITS   _u(0xffff0000)
#define DMA_TIMER2_X_MSB    _u(31)
#define DMA_TIMER2_X_LSB    _u(16)
#define DMA_TIMER2_X_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_TIMER2_Y
// Description : Pacing Timer Divisor. Specifies the Y value for the (X/Y)
//               fractional timer.
#define DMA_TIMER2_Y_RESET  _u(0x0000)
#define DMA_TIMER2_Y_BITS   _u(0x0000ffff)
#define DMA_TIMER2_Y_MSB    _u(15)
#define DMA_TIMER2_Y_LSB    _u(0)
#define DMA_TIMER2_Y_ACCESS "RW"
// =============================================================================
// Register    : DMA_TIMER3
// Description : Pacing (X/Y) Fractional Timer
//               The pacing timer produces TREQ assertions at a rate set by
//               ((X/Y) * sys_clk). This equation is evaluated every sys_clk
//               cycles and therefore can only generate TREQs at a rate of 1 per
//               sys_clk (i.e. permanent TREQ) or less.
#define DMA_TIMER3_OFFSET _u(0x0000042c)
#define DMA_TIMER3_BITS   _u(0xffffffff)
#define DMA_TIMER3_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_TIMER3_X
// Description : Pacing Timer Dividend. Specifies the X value for the (X/Y)
//               fractional timer.
#define DMA_TIMER3_X_RESET  _u(0x0000)
#define DMA_TIMER3_X_BITS   _u(0xffff0000)
#define DMA_TIMER3_X_MSB    _u(31)
#define DMA_TIMER3_X_LSB    _u(16)
#define DMA_TIMER3_X_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_TIMER3_Y
// Description : Pacing Timer Divisor. Specifies the Y value for the (X/Y)
//               fractional timer.
#define DMA_TIMER3_Y_RESET  _u(0x0000)
#define DMA_TIMER3_Y_BITS   _u(0x0000ffff)
#define DMA_TIMER3_Y_MSB    _u(15)
#define DMA_TIMER3_Y_LSB    _u(0)
#define DMA_TIMER3_Y_ACCESS "RW"
// =============================================================================
// Register    : DMA_MULTI_CHAN_TRIGGER
// Description : Trigger one or more channels simultaneously
//               Each bit in this register corresponds to a DMA channel. Writing
//               a 1 to the relevant bit is the same as writing to that
//               channel's trigger register; the channel will start if it is
//               currently enabled and not already busy.
#define DMA_MULTI_CHAN_TRIGGER_OFFSET _u(0x00000430)
#define DMA_MULTI_CHAN_TRIGGER_BITS   _u(0x0000ffff)
#define DMA_MULTI_CHAN_TRIGGER_RESET  _u(0x00000000)
#define DMA_MULTI_CHAN_TRIGGER_MSB    _u(15)
#define DMA_MULTI_CHAN_TRIGGER_LSB    _u(0)
#define DMA_MULTI_CHAN_TRIGGER_ACCESS "SC"
// =============================================================================
// Register    : DMA_SNIFF_CTRL
// Description : Sniffer Control
#define DMA_SNIFF_CTRL_OFFSET _u(0x00000434)
#define DMA_SNIFF_CTRL_BITS   _u(0x00000fff)
#define DMA_SNIFF_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_SNIFF_CTRL_OUT_INV
// Description : If set, the result appears inverted (bitwise complement) when
//               read. This does not affect the way the checksum is calculated;
//               the result is transformed on-the-fly between the result
//               register and the bus.
#define DMA_SNIFF_CTRL_OUT_INV_RESET  _u(0x0)
#define DMA_SNIFF_CTRL_OUT_INV_BITS   _u(0x00000800)
#define DMA_SNIFF_CTRL_OUT_INV_MSB    _u(11)
#define DMA_SNIFF_CTRL_OUT_INV_LSB    _u(11)
#define DMA_SNIFF_CTRL_OUT_INV_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_SNIFF_CTRL_OUT_REV
// Description : If set, the result appears bit-reversed when read. This does
//               not affect the way the checksum is calculated; the result is
//               transformed on-the-fly between the result register and the bus.
#define DMA_SNIFF_CTRL_OUT_REV_RESET  _u(0x0)
#define DMA_SNIFF_CTRL_OUT_REV_BITS   _u(0x00000400)
#define DMA_SNIFF_CTRL_OUT_REV_MSB    _u(10)
#define DMA_SNIFF_CTRL_OUT_REV_LSB    _u(10)
#define DMA_SNIFF_CTRL_OUT_REV_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_SNIFF_CTRL_BSWAP
// Description : Locally perform a byte reverse on the sniffed data, before
//               feeding into checksum.
//
//               Note that the sniff hardware is downstream of the DMA channel
//               byteswap performed in the read master: if channel CTRL_BSWAP
//               and SNIFF_CTRL_BSWAP are both enabled, their effects cancel
//               from the sniffer's point of view.
#define DMA_SNIFF_CTRL_BSWAP_RESET  _u(0x0)
#define DMA_SNIFF_CTRL_BSWAP_BITS   _u(0x00000200)
#define DMA_SNIFF_CTRL_BSWAP_MSB    _u(9)
#define DMA_SNIFF_CTRL_BSWAP_LSB    _u(9)
#define DMA_SNIFF_CTRL_BSWAP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_SNIFF_CTRL_CALC
// Description : 0x0 -> Calculate a CRC-32 (IEEE802.3 polynomial)
//               0x1 -> Calculate a CRC-32 (IEEE802.3 polynomial) with bit
//               reversed data
//               0x2 -> Calculate a CRC-16-CCITT
//               0x3 -> Calculate a CRC-16-CCITT with bit reversed data
//               0xe -> XOR reduction over all data. == 1 if the total 1
//               population count is odd.
//               0xf -> Calculate a simple 32-bit checksum (addition with a 32
//               bit accumulator)
#define DMA_SNIFF_CTRL_CALC_RESET        _u(0x0)
#define DMA_SNIFF_CTRL_CALC_BITS         _u(0x000001e0)
#define DMA_SNIFF_CTRL_CALC_MSB          _u(8)
#define DMA_SNIFF_CTRL_CALC_LSB          _u(5)
#define DMA_SNIFF_CTRL_CALC_ACCESS       "RW"
#define DMA_SNIFF_CTRL_CALC_VALUE_CRC32  _u(0x0)
#define DMA_SNIFF_CTRL_CALC_VALUE_CRC32R _u(0x1)
#define DMA_SNIFF_CTRL_CALC_VALUE_CRC16  _u(0x2)
#define DMA_SNIFF_CTRL_CALC_VALUE_CRC16R _u(0x3)
#define DMA_SNIFF_CTRL_CALC_VALUE_EVEN   _u(0xe)
#define DMA_SNIFF_CTRL_CALC_VALUE_SUM    _u(0xf)
// -----------------------------------------------------------------------------
// Field       : DMA_SNIFF_CTRL_DMACH
// Description : DMA channel for Sniffer to observe
#define DMA_SNIFF_CTRL_DMACH_RESET  _u(0x0)
#define DMA_SNIFF_CTRL_DMACH_BITS   _u(0x0000001e)
#define DMA_SNIFF_CTRL_DMACH_MSB    _u(4)
#define DMA_SNIFF_CTRL_DMACH_LSB    _u(1)
#define DMA_SNIFF_CTRL_DMACH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : DMA_SNIFF_CTRL_EN
// Description : Enable sniffer
#define DMA_SNIFF_CTRL_EN_RESET  _u(0x0)
#define DMA_SNIFF_CTRL_EN_BITS   _u(0x00000001)
#define DMA_SNIFF_CTRL_EN_MSB    _u(0)
#define DMA_SNIFF_CTRL_EN_LSB    _u(0)
#define DMA_SNIFF_CTRL_EN_ACCESS "RW"
// =============================================================================
// Register    : DMA_SNIFF_DATA
// Description : Data accumulator for sniff hardware
//               Write an initial seed value here before starting a DMA transfer
//               on the channel indicated by SNIFF_CTRL_DMACH. The hardware will
//               update this register each time it observes a read from the
//               indicated channel. Once the channel completes, the final result
//               can be read from this register.
#define DMA_SNIFF_DATA_OFFSET _u(0x00000438)
#define DMA_SNIFF_DATA_BITS   _u(0xffffffff)
#define DMA_SNIFF_DATA_RESET  _u(0x00000000)
#define DMA_SNIFF_DATA_MSB    _u(31)
#define DMA_SNIFF_DATA_LSB    _u(0)
#define DMA_SNIFF_DATA_ACCESS "RW"
// =============================================================================
// Register    : DMA_FIFO_LEVELS
// Description : Debug RAF, WAF, TDF levels
#define DMA_FIFO_LEVELS_OFFSET _u(0x00000440)
#define DMA_FIFO_LEVELS_BITS   _u(0x00ffffff)
#define DMA_FIFO_LEVELS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : DMA_FIFO_LEVELS_RAF_LVL
// Description : Current Read-Address-FIFO fill level
#define DMA_FIFO_LEVELS_RAF_LVL_RESET  _u(0x00)
#define DMA_FIFO_LEVELS_RAF_LVL_BITS   _u(0x00ff0000)
#define DMA_FIFO_LEVELS_RAF_LVL_MSB    _u(23)
#define DMA_FIFO_LEVELS_RAF_LVL_LSB    _u(16)
#define DMA_FIFO_LEVELS_RAF_LVL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_FIFO_LEVELS_WAF_LVL
// Description : Current Write-Address-FIFO fill level
#define DMA_FIFO_LEVELS_WAF_LVL_RESET  _u(0x00)
#define DMA_FIFO_LEVELS_WAF_LVL_BITS   _u(0x0000ff00)
#define DMA_FIFO_LEVELS_WAF_LVL_MSB    _u(15)
#define DMA_FIFO_LEVELS_WAF_LVL_LSB    _u(8)
#define DMA_FIFO_LEVELS_WAF_LVL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : DMA_FIFO_LEVELS_TDF_LVL
// Description : Current Transfer-Data-FIFO fill level
#define DMA_FIFO_LEVELS_TDF_LVL_RESET  _u(0x00)
#define DMA_FIFO_LEVELS_TDF_LVL_BITS   _u(0x000000ff)
#define DMA_FIFO_LEVELS_TDF_LVL_MSB    _u(7)
#define DMA_FIFO_LEVELS_TDF_LVL_LSB    _u(0)
#define DMA_FIFO_LEVELS_TDF_LVL_ACCESS "RO"
// =============================================================================
// Register    : DMA_CHAN_ABORT
// Description : Abort an in-progress transfer sequence on one or more channels
//               Each bit corresponds to a channel. Writing a 1 aborts whatever
//               transfer sequence is in progress on that channel. The bit will
//               remain high until any in-flight transfers have been flushed
//               through the address and data FIFOs.
//
//               After writing, this register must be polled until it returns
//               all-zero. Until this point, it is unsafe to restart the
//               channel.
#define DMA_CHAN_ABORT_OFFSET _u(0x00000444)
#define DMA_CHAN_ABORT_BITS   _u(0x0000ffff)
#define DMA_CHAN_ABORT_RESET  _u(0x00000000)
#define DMA_CHAN_ABORT_MSB    _u(15)
#define DMA_CHAN_ABORT_LSB    _u(0)
#define DMA_CHAN_ABORT_ACCESS "SC"
// =============================================================================
// Register    : DMA_N_CHANNELS
// Description : The number of channels this DMA instance is equipped with. This
//               DMA supports up to 16 hardware channels, but can be configured
//               with as few as one, to minimise silicon area.
#define DMA_N_CHANNELS_OFFSET _u(0x00000448)
#define DMA_N_CHANNELS_BITS   _u(0x0000001f)
#define DMA_N_CHANNELS_RESET  "-"
#define DMA_N_CHANNELS_MSB    _u(4)
#define DMA_N_CHANNELS_LSB    _u(0)
#define DMA_N_CHANNELS_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH0_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH0_DBG_CTDREQ_OFFSET _u(0x00000800)
#define DMA_CH0_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH0_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH0_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH0_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH0_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH0_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH0_DBG_TCR_OFFSET _u(0x00000804)
#define DMA_CH0_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH0_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH0_DBG_TCR_MSB    _u(31)
#define DMA_CH0_DBG_TCR_LSB    _u(0)
#define DMA_CH0_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH1_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH1_DBG_CTDREQ_OFFSET _u(0x00000840)
#define DMA_CH1_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH1_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH1_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH1_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH1_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH1_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH1_DBG_TCR_OFFSET _u(0x00000844)
#define DMA_CH1_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH1_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH1_DBG_TCR_MSB    _u(31)
#define DMA_CH1_DBG_TCR_LSB    _u(0)
#define DMA_CH1_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH2_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH2_DBG_CTDREQ_OFFSET _u(0x00000880)
#define DMA_CH2_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH2_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH2_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH2_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH2_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH2_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH2_DBG_TCR_OFFSET _u(0x00000884)
#define DMA_CH2_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH2_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH2_DBG_TCR_MSB    _u(31)
#define DMA_CH2_DBG_TCR_LSB    _u(0)
#define DMA_CH2_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH3_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH3_DBG_CTDREQ_OFFSET _u(0x000008c0)
#define DMA_CH3_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH3_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH3_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH3_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH3_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH3_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH3_DBG_TCR_OFFSET _u(0x000008c4)
#define DMA_CH3_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH3_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH3_DBG_TCR_MSB    _u(31)
#define DMA_CH3_DBG_TCR_LSB    _u(0)
#define DMA_CH3_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH4_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH4_DBG_CTDREQ_OFFSET _u(0x00000900)
#define DMA_CH4_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH4_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH4_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH4_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH4_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH4_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH4_DBG_TCR_OFFSET _u(0x00000904)
#define DMA_CH4_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH4_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH4_DBG_TCR_MSB    _u(31)
#define DMA_CH4_DBG_TCR_LSB    _u(0)
#define DMA_CH4_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH5_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH5_DBG_CTDREQ_OFFSET _u(0x00000940)
#define DMA_CH5_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH5_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH5_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH5_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH5_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH5_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH5_DBG_TCR_OFFSET _u(0x00000944)
#define DMA_CH5_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH5_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH5_DBG_TCR_MSB    _u(31)
#define DMA_CH5_DBG_TCR_LSB    _u(0)
#define DMA_CH5_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH6_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH6_DBG_CTDREQ_OFFSET _u(0x00000980)
#define DMA_CH6_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH6_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH6_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH6_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH6_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH6_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH6_DBG_TCR_OFFSET _u(0x00000984)
#define DMA_CH6_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH6_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH6_DBG_TCR_MSB    _u(31)
#define DMA_CH6_DBG_TCR_LSB    _u(0)
#define DMA_CH6_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH7_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH7_DBG_CTDREQ_OFFSET _u(0x000009c0)
#define DMA_CH7_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH7_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH7_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH7_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH7_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH7_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH7_DBG_TCR_OFFSET _u(0x000009c4)
#define DMA_CH7_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH7_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH7_DBG_TCR_MSB    _u(31)
#define DMA_CH7_DBG_TCR_LSB    _u(0)
#define DMA_CH7_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH8_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH8_DBG_CTDREQ_OFFSET _u(0x00000a00)
#define DMA_CH8_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH8_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH8_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH8_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH8_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH8_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH8_DBG_TCR_OFFSET _u(0x00000a04)
#define DMA_CH8_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH8_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH8_DBG_TCR_MSB    _u(31)
#define DMA_CH8_DBG_TCR_LSB    _u(0)
#define DMA_CH8_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH9_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH9_DBG_CTDREQ_OFFSET _u(0x00000a40)
#define DMA_CH9_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH9_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH9_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH9_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH9_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH9_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH9_DBG_TCR_OFFSET _u(0x00000a44)
#define DMA_CH9_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH9_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH9_DBG_TCR_MSB    _u(31)
#define DMA_CH9_DBG_TCR_LSB    _u(0)
#define DMA_CH9_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH10_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH10_DBG_CTDREQ_OFFSET _u(0x00000a80)
#define DMA_CH10_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH10_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH10_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH10_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH10_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH10_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH10_DBG_TCR_OFFSET _u(0x00000a84)
#define DMA_CH10_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH10_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH10_DBG_TCR_MSB    _u(31)
#define DMA_CH10_DBG_TCR_LSB    _u(0)
#define DMA_CH10_DBG_TCR_ACCESS "RO"
// =============================================================================
// Register    : DMA_CH11_DBG_CTDREQ
// Description : Read: get channel DREQ counter (i.e. how many accesses the DMA
//               expects it can perform on the peripheral without
//               overflow/underflow. Write any value: clears the counter, and
//               cause channel to re-initiate DREQ handshake.
#define DMA_CH11_DBG_CTDREQ_OFFSET _u(0x00000ac0)
#define DMA_CH11_DBG_CTDREQ_BITS   _u(0x0000003f)
#define DMA_CH11_DBG_CTDREQ_RESET  _u(0x00000000)
#define DMA_CH11_DBG_CTDREQ_MSB    _u(5)
#define DMA_CH11_DBG_CTDREQ_LSB    _u(0)
#define DMA_CH11_DBG_CTDREQ_ACCESS "WC"
// =============================================================================
// Register    : DMA_CH11_DBG_TCR
// Description : Read to get channel TRANS_COUNT reload value, i.e. the length
//               of the next transfer
#define DMA_CH11_DBG_TCR_OFFSET _u(0x00000ac4)
#define DMA_CH11_DBG_TCR_BITS   _u(0xffffffff)
#define DMA_CH11_DBG_TCR_RESET  _u(0x00000000)
#define DMA_CH11_DBG_TCR_MSB    _u(31)
#define DMA_CH11_DBG_TCR_LSB    _u(0)
#define DMA_CH11_DBG_TCR_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_DMA_DEFINED
