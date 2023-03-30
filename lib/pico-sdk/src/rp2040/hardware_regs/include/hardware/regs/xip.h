/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : XIP
// Version        : 1
// Bus type       : ahb
// Description    : QSPI flash execute-in-place block
// =============================================================================
#ifndef HARDWARE_REGS_XIP_DEFINED
#define HARDWARE_REGS_XIP_DEFINED
// =============================================================================
// Register    : XIP_CTRL
// Description : Cache control
#define XIP_CTRL_OFFSET _u(0x00000000)
#define XIP_CTRL_BITS   _u(0x0000000b)
#define XIP_CTRL_RESET  _u(0x00000003)
// -----------------------------------------------------------------------------
// Field       : XIP_CTRL_POWER_DOWN
// Description : When 1, the cache memories are powered down. They retain state,
//               but can not be accessed. This reduces static power dissipation.
//               Writing 1 to this bit forces CTRL_EN to 0, i.e. the cache
//               cannot
//               be enabled when powered down.
//               Cache-as-SRAM accesses will produce a bus error response when
//               the cache is powered down.
#define XIP_CTRL_POWER_DOWN_RESET  _u(0x0)
#define XIP_CTRL_POWER_DOWN_BITS   _u(0x00000008)
#define XIP_CTRL_POWER_DOWN_MSB    _u(3)
#define XIP_CTRL_POWER_DOWN_LSB    _u(3)
#define XIP_CTRL_POWER_DOWN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : XIP_CTRL_ERR_BADWRITE
// Description : When 1, writes to any alias other than 0x0 (caching,
//               allocating)
//               will produce a bus fault. When 0, these writes are silently
//               ignored.
//               In either case, writes to the 0x0 alias will deallocate on tag
//               match,
//               as usual.
#define XIP_CTRL_ERR_BADWRITE_RESET  _u(0x1)
#define XIP_CTRL_ERR_BADWRITE_BITS   _u(0x00000002)
#define XIP_CTRL_ERR_BADWRITE_MSB    _u(1)
#define XIP_CTRL_ERR_BADWRITE_LSB    _u(1)
#define XIP_CTRL_ERR_BADWRITE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : XIP_CTRL_EN
// Description : When 1, enable the cache. When the cache is disabled, all XIP
//               accesses
//               will go straight to the flash, without querying the cache. When
//               enabled,
//               cacheable XIP accesses will query the cache, and the flash will
//               not be accessed if the tag matches and the valid bit is set.
//
//               If the cache is enabled, cache-as-SRAM accesses have no effect
//               on the
//               cache data RAM, and will produce a bus error response.
#define XIP_CTRL_EN_RESET  _u(0x1)
#define XIP_CTRL_EN_BITS   _u(0x00000001)
#define XIP_CTRL_EN_MSB    _u(0)
#define XIP_CTRL_EN_LSB    _u(0)
#define XIP_CTRL_EN_ACCESS "RW"
// =============================================================================
// Register    : XIP_FLUSH
// Description : Cache Flush control
//               Write 1 to flush the cache. This clears the tag memory, but
//               the data memory retains its contents. (This means cache-as-SRAM
//               contents is not affected by flush or reset.)
//               Reading will hold the bus (stall the processor) until the flush
//               completes. Alternatively STAT can be polled until completion.
#define XIP_FLUSH_OFFSET _u(0x00000004)
#define XIP_FLUSH_BITS   _u(0x00000001)
#define XIP_FLUSH_RESET  _u(0x00000000)
#define XIP_FLUSH_MSB    _u(0)
#define XIP_FLUSH_LSB    _u(0)
#define XIP_FLUSH_ACCESS "SC"
// =============================================================================
// Register    : XIP_STAT
// Description : Cache Status
#define XIP_STAT_OFFSET _u(0x00000008)
#define XIP_STAT_BITS   _u(0x00000007)
#define XIP_STAT_RESET  _u(0x00000002)
// -----------------------------------------------------------------------------
// Field       : XIP_STAT_FIFO_FULL
// Description : When 1, indicates the XIP streaming FIFO is completely full.
//               The streaming FIFO is 2 entries deep, so the full and empty
//               flag allow its level to be ascertained.
#define XIP_STAT_FIFO_FULL_RESET  _u(0x0)
#define XIP_STAT_FIFO_FULL_BITS   _u(0x00000004)
#define XIP_STAT_FIFO_FULL_MSB    _u(2)
#define XIP_STAT_FIFO_FULL_LSB    _u(2)
#define XIP_STAT_FIFO_FULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : XIP_STAT_FIFO_EMPTY
// Description : When 1, indicates the XIP streaming FIFO is completely empty.
#define XIP_STAT_FIFO_EMPTY_RESET  _u(0x1)
#define XIP_STAT_FIFO_EMPTY_BITS   _u(0x00000002)
#define XIP_STAT_FIFO_EMPTY_MSB    _u(1)
#define XIP_STAT_FIFO_EMPTY_LSB    _u(1)
#define XIP_STAT_FIFO_EMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : XIP_STAT_FLUSH_READY
// Description : Reads as 0 while a cache flush is in progress, and 1 otherwise.
//               The cache is flushed whenever the XIP block is reset, and also
//               when requested via the FLUSH register.
#define XIP_STAT_FLUSH_READY_RESET  _u(0x0)
#define XIP_STAT_FLUSH_READY_BITS   _u(0x00000001)
#define XIP_STAT_FLUSH_READY_MSB    _u(0)
#define XIP_STAT_FLUSH_READY_LSB    _u(0)
#define XIP_STAT_FLUSH_READY_ACCESS "RO"
// =============================================================================
// Register    : XIP_CTR_HIT
// Description : Cache Hit counter
//               A 32 bit saturating counter that increments upon each cache
//               hit,
//               i.e. when an XIP access is serviced directly from cached data.
//               Write any value to clear.
#define XIP_CTR_HIT_OFFSET _u(0x0000000c)
#define XIP_CTR_HIT_BITS   _u(0xffffffff)
#define XIP_CTR_HIT_RESET  _u(0x00000000)
#define XIP_CTR_HIT_MSB    _u(31)
#define XIP_CTR_HIT_LSB    _u(0)
#define XIP_CTR_HIT_ACCESS "WC"
// =============================================================================
// Register    : XIP_CTR_ACC
// Description : Cache Access counter
//               A 32 bit saturating counter that increments upon each XIP
//               access,
//               whether the cache is hit or not. This includes noncacheable
//               accesses.
//               Write any value to clear.
#define XIP_CTR_ACC_OFFSET _u(0x00000010)
#define XIP_CTR_ACC_BITS   _u(0xffffffff)
#define XIP_CTR_ACC_RESET  _u(0x00000000)
#define XIP_CTR_ACC_MSB    _u(31)
#define XIP_CTR_ACC_LSB    _u(0)
#define XIP_CTR_ACC_ACCESS "WC"
// =============================================================================
// Register    : XIP_STREAM_ADDR
// Description : FIFO stream address
//               The address of the next word to be streamed from flash to the
//               streaming FIFO.
//               Increments automatically after each flash access.
//               Write the initial access address here before starting a
//               streaming read.
#define XIP_STREAM_ADDR_OFFSET _u(0x00000014)
#define XIP_STREAM_ADDR_BITS   _u(0xfffffffc)
#define XIP_STREAM_ADDR_RESET  _u(0x00000000)
#define XIP_STREAM_ADDR_MSB    _u(31)
#define XIP_STREAM_ADDR_LSB    _u(2)
#define XIP_STREAM_ADDR_ACCESS "RW"
// =============================================================================
// Register    : XIP_STREAM_CTR
// Description : FIFO stream control
//               Write a nonzero value to start a streaming read. This will then
//               progress in the background, using flash idle cycles to transfer
//               a linear data block from flash to the streaming FIFO.
//               Decrements automatically (1 at a time) as the stream
//               progresses, and halts on reaching 0.
//               Write 0 to halt an in-progress stream, and discard any
//               in-flight
//               read, so that a new stream can immediately be started (after
//               draining the FIFO and reinitialising STREAM_ADDR)
#define XIP_STREAM_CTR_OFFSET _u(0x00000018)
#define XIP_STREAM_CTR_BITS   _u(0x003fffff)
#define XIP_STREAM_CTR_RESET  _u(0x00000000)
#define XIP_STREAM_CTR_MSB    _u(21)
#define XIP_STREAM_CTR_LSB    _u(0)
#define XIP_STREAM_CTR_ACCESS "RW"
// =============================================================================
// Register    : XIP_STREAM_FIFO
// Description : FIFO stream data
//               Streamed data is buffered here, for retrieval by the system
//               DMA.
//               This FIFO can also be accessed via the XIP_AUX slave, to avoid
//               exposing
//               the DMA to bus stalls caused by other XIP traffic.
#define XIP_STREAM_FIFO_OFFSET _u(0x0000001c)
#define XIP_STREAM_FIFO_BITS   _u(0xffffffff)
#define XIP_STREAM_FIFO_RESET  _u(0x00000000)
#define XIP_STREAM_FIFO_MSB    _u(31)
#define XIP_STREAM_FIFO_LSB    _u(0)
#define XIP_STREAM_FIFO_ACCESS "RF"
// =============================================================================
#endif // HARDWARE_REGS_XIP_DEFINED
