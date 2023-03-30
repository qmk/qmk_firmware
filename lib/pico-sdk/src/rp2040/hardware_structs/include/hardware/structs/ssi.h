// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_SSI_H
#define _HARDWARE_STRUCTS_SSI_H

#include "hardware/address_mapped.h"
#include "hardware/regs/ssi.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_ssi
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/ssi.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(SSI_CTRLR0_OFFSET) // SSI_CTRLR0
    // Control register 0
    // 0x01000000 [24]    : SSTE (0): Slave select toggle enable
    // 0x00600000 [22:21] : SPI_FRF (0): SPI frame format
    // 0x001f0000 [20:16] : DFS_32 (0): Data frame size in 32b transfer mode
    // 0x0000f000 [15:12] : CFS (0): Control frame size
    // 0x00000800 [11]    : SRL (0): Shift register loop (test mode)
    // 0x00000400 [10]    : SLV_OE (0): Slave output enable
    // 0x00000300 [9:8]   : TMOD (0): Transfer mode
    // 0x00000080 [7]     : SCPOL (0): Serial clock polarity
    // 0x00000040 [6]     : SCPH (0): Serial clock phase
    // 0x00000030 [5:4]   : FRF (0): Frame format
    // 0x0000000f [3:0]   : DFS (0): Data frame size
    io_rw_32 ctrlr0;

    _REG_(SSI_CTRLR1_OFFSET) // SSI_CTRLR1
    // Master Control register 1
    // 0x0000ffff [15:0]  : NDF (0): Number of data frames
    io_rw_32 ctrlr1;

    _REG_(SSI_SSIENR_OFFSET) // SSI_SSIENR
    // SSI Enable
    // 0x00000001 [0]     : SSI_EN (0): SSI enable
    io_rw_32 ssienr;

    _REG_(SSI_MWCR_OFFSET) // SSI_MWCR
    // Microwire Control
    // 0x00000004 [2]     : MHS (0): Microwire handshaking
    // 0x00000002 [1]     : MDD (0): Microwire control
    // 0x00000001 [0]     : MWMOD (0): Microwire transfer mode
    io_rw_32 mwcr;

    _REG_(SSI_SER_OFFSET) // SSI_SER
    // Slave enable
    // 0x00000001 [0]     : SER (0): For each bit:
    io_rw_32 ser;

    _REG_(SSI_BAUDR_OFFSET) // SSI_BAUDR
    // Baud rate
    // 0x0000ffff [15:0]  : SCKDV (0): SSI clock divider
    io_rw_32 baudr;

    _REG_(SSI_TXFTLR_OFFSET) // SSI_TXFTLR
    // TX FIFO threshold level
    // 0x000000ff [7:0]   : TFT (0): Transmit FIFO threshold
    io_rw_32 txftlr;

    _REG_(SSI_RXFTLR_OFFSET) // SSI_RXFTLR
    // RX FIFO threshold level
    // 0x000000ff [7:0]   : RFT (0): Receive FIFO threshold
    io_rw_32 rxftlr;

    _REG_(SSI_TXFLR_OFFSET) // SSI_TXFLR
    // TX FIFO level
    // 0x000000ff [7:0]   : TFTFL (0): Transmit FIFO level
    io_ro_32 txflr;

    _REG_(SSI_RXFLR_OFFSET) // SSI_RXFLR
    // RX FIFO level
    // 0x000000ff [7:0]   : RXTFL (0): Receive FIFO level
    io_ro_32 rxflr;

    _REG_(SSI_SR_OFFSET) // SSI_SR
    // Status register
    // 0x00000040 [6]     : DCOL (0): Data collision error
    // 0x00000020 [5]     : TXE (0): Transmission error
    // 0x00000010 [4]     : RFF (0): Receive FIFO full
    // 0x00000008 [3]     : RFNE (0): Receive FIFO not empty
    // 0x00000004 [2]     : TFE (0): Transmit FIFO empty
    // 0x00000002 [1]     : TFNF (0): Transmit FIFO not full
    // 0x00000001 [0]     : BUSY (0): SSI busy flag
    io_ro_32 sr;

    _REG_(SSI_IMR_OFFSET) // SSI_IMR
    // Interrupt mask
    // 0x00000020 [5]     : MSTIM (0): Multi-master contention interrupt mask
    // 0x00000010 [4]     : RXFIM (0): Receive FIFO full interrupt mask
    // 0x00000008 [3]     : RXOIM (0): Receive FIFO overflow interrupt mask
    // 0x00000004 [2]     : RXUIM (0): Receive FIFO underflow interrupt mask
    // 0x00000002 [1]     : TXOIM (0): Transmit FIFO overflow interrupt mask
    // 0x00000001 [0]     : TXEIM (0): Transmit FIFO empty interrupt mask
    io_rw_32 imr;

    _REG_(SSI_ISR_OFFSET) // SSI_ISR
    // Interrupt status
    // 0x00000020 [5]     : MSTIS (0): Multi-master contention interrupt status
    // 0x00000010 [4]     : RXFIS (0): Receive FIFO full interrupt status
    // 0x00000008 [3]     : RXOIS (0): Receive FIFO overflow interrupt status
    // 0x00000004 [2]     : RXUIS (0): Receive FIFO underflow interrupt status
    // 0x00000002 [1]     : TXOIS (0): Transmit FIFO overflow interrupt status
    // 0x00000001 [0]     : TXEIS (0): Transmit FIFO empty interrupt status
    io_ro_32 isr;

    _REG_(SSI_RISR_OFFSET) // SSI_RISR
    // Raw interrupt status
    // 0x00000020 [5]     : MSTIR (0): Multi-master contention raw interrupt status
    // 0x00000010 [4]     : RXFIR (0): Receive FIFO full raw interrupt status
    // 0x00000008 [3]     : RXOIR (0): Receive FIFO overflow raw interrupt status
    // 0x00000004 [2]     : RXUIR (0): Receive FIFO underflow raw interrupt status
    // 0x00000002 [1]     : TXOIR (0): Transmit FIFO overflow raw interrupt status
    // 0x00000001 [0]     : TXEIR (0): Transmit FIFO empty raw interrupt status
    io_ro_32 risr;

    _REG_(SSI_TXOICR_OFFSET) // SSI_TXOICR
    // TX FIFO overflow interrupt clear
    // 0x00000001 [0]     : TXOICR (0): Clear-on-read transmit FIFO overflow interrupt
    io_ro_32 txoicr;

    _REG_(SSI_RXOICR_OFFSET) // SSI_RXOICR
    // RX FIFO overflow interrupt clear
    // 0x00000001 [0]     : RXOICR (0): Clear-on-read receive FIFO overflow interrupt
    io_ro_32 rxoicr;

    _REG_(SSI_RXUICR_OFFSET) // SSI_RXUICR
    // RX FIFO underflow interrupt clear
    // 0x00000001 [0]     : RXUICR (0): Clear-on-read receive FIFO underflow interrupt
    io_ro_32 rxuicr;

    _REG_(SSI_MSTICR_OFFSET) // SSI_MSTICR
    // Multi-master interrupt clear
    // 0x00000001 [0]     : MSTICR (0): Clear-on-read multi-master contention interrupt
    io_ro_32 msticr;

    _REG_(SSI_ICR_OFFSET) // SSI_ICR
    // Interrupt clear
    // 0x00000001 [0]     : ICR (0): Clear-on-read all active interrupts
    io_ro_32 icr;

    _REG_(SSI_DMACR_OFFSET) // SSI_DMACR
    // DMA control
    // 0x00000002 [1]     : TDMAE (0): Transmit DMA enable
    // 0x00000001 [0]     : RDMAE (0): Receive DMA enable
    io_rw_32 dmacr;

    _REG_(SSI_DMATDLR_OFFSET) // SSI_DMATDLR
    // DMA TX data level
    // 0x000000ff [7:0]   : DMATDL (0): Transmit data watermark level
    io_rw_32 dmatdlr;

    _REG_(SSI_DMARDLR_OFFSET) // SSI_DMARDLR
    // DMA RX data level
    // 0x000000ff [7:0]   : DMARDL (0): Receive data watermark level (DMARDLR+1)
    io_rw_32 dmardlr;

    _REG_(SSI_IDR_OFFSET) // SSI_IDR
    // Identification register
    // 0xffffffff [31:0]  : IDCODE (0x51535049): Peripheral dentification code
    io_ro_32 idr;

    _REG_(SSI_SSI_VERSION_ID_OFFSET) // SSI_SSI_VERSION_ID
    // Version ID
    // 0xffffffff [31:0]  : SSI_COMP_VERSION (0x3430312a): SNPS component version (format X
    io_ro_32 ssi_version_id;

    _REG_(SSI_DR0_OFFSET) // SSI_DR0
    // Data Register 0 (of 36)
    // 0xffffffff [31:0]  : DR (0): First data register of 36
    io_rw_32 dr0;

    uint32_t _pad0[35];

    _REG_(SSI_RX_SAMPLE_DLY_OFFSET) // SSI_RX_SAMPLE_DLY
    // RX sample delay
    // 0x000000ff [7:0]   : RSD (0): RXD sample delay (in SCLK cycles)
    io_rw_32 rx_sample_dly;

    _REG_(SSI_SPI_CTRLR0_OFFSET) // SSI_SPI_CTRLR0
    // SPI control
    // 0xff000000 [31:24] : XIP_CMD (0x3): SPI Command to send in XIP mode (INST_L = 8-bit) or to append to Address (INST_L = 0-bit)
    // 0x00040000 [18]    : SPI_RXDS_EN (0): Read data strobe enable
    // 0x00020000 [17]    : INST_DDR_EN (0): Instruction DDR transfer enable
    // 0x00010000 [16]    : SPI_DDR_EN (0): SPI DDR transfer enable
    // 0x0000f800 [15:11] : WAIT_CYCLES (0): Wait cycles between control frame transmit and data reception (in SCLK cycles)
    // 0x00000300 [9:8]   : INST_L (0): Instruction length (0/4/8/16b)
    // 0x0000003c [5:2]   : ADDR_L (0): Address length (0b-60b in 4b increments)
    // 0x00000003 [1:0]   : TRANS_TYPE (0): Address and instruction transfer format
    io_rw_32 spi_ctrlr0;

    _REG_(SSI_TXD_DRIVE_EDGE_OFFSET) // SSI_TXD_DRIVE_EDGE
    // TX drive edge
    // 0x000000ff [7:0]   : TDE (0): TXD drive edge
    io_rw_32 txd_drive_edge;
} ssi_hw_t;

#define ssi_hw ((ssi_hw_t *)XIP_SSI_BASE)

#endif
