// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_XIP_CTRL_H
#define _HARDWARE_STRUCTS_XIP_CTRL_H

#include "hardware/address_mapped.h"
#include "hardware/regs/xip.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_xip
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/xip.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(XIP_CTRL_OFFSET) // XIP_CTRL
    // Cache control
    // 0x00000008 [3]     : POWER_DOWN (0): When 1, the cache memories are powered down
    // 0x00000002 [1]     : ERR_BADWRITE (1): When 1, writes to any alias other than 0x0 (caching, allocating)
    // 0x00000001 [0]     : EN (1): When 1, enable the cache
    io_rw_32 ctrl;

    _REG_(XIP_FLUSH_OFFSET) // XIP_FLUSH
    // Cache Flush control
    // 0x00000001 [0]     : FLUSH (0): Write 1 to flush the cache
    io_rw_32 flush;

    _REG_(XIP_STAT_OFFSET) // XIP_STAT
    // Cache Status
    // 0x00000004 [2]     : FIFO_FULL (0): When 1, indicates the XIP streaming FIFO is completely full
    // 0x00000002 [1]     : FIFO_EMPTY (1): When 1, indicates the XIP streaming FIFO is completely empty
    // 0x00000001 [0]     : FLUSH_READY (0): Reads as 0 while a cache flush is in progress, and 1 otherwise
    io_ro_32 stat;

    _REG_(XIP_CTR_HIT_OFFSET) // XIP_CTR_HIT
    // Cache Hit counter
    io_rw_32 ctr_hit;

    _REG_(XIP_CTR_ACC_OFFSET) // XIP_CTR_ACC
    // Cache Access counter
    io_rw_32 ctr_acc;

    _REG_(XIP_STREAM_ADDR_OFFSET) // XIP_STREAM_ADDR
    // FIFO stream address
    // 0xfffffffc [31:2]  : STREAM_ADDR (0): The address of the next word to be streamed from flash to the streaming FIFO
    io_rw_32 stream_addr;

    _REG_(XIP_STREAM_CTR_OFFSET) // XIP_STREAM_CTR
    // FIFO stream control
    // 0x003fffff [21:0]  : STREAM_CTR (0): Write a nonzero value to start a streaming read
    io_rw_32 stream_ctr;

    _REG_(XIP_STREAM_FIFO_OFFSET) // XIP_STREAM_FIFO
    // FIFO stream data
    io_ro_32 stream_fifo;
} xip_ctrl_hw_t;

#define xip_ctrl_hw ((xip_ctrl_hw_t *)XIP_CTRL_BASE)

#define XIP_STAT_FIFO_FULL XIP_STAT_FIFO_FULL_BITS
#define XIP_STAT_FIFO_EMPTY XIP_STAT_FIFO_EMPTY_BITS
#define XIP_STAT_FLUSH_RDY XIP_STAT_FLUSH_READY_BITS

#endif
