// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_I2C_H
#define _HARDWARE_STRUCTS_I2C_H

#include "hardware/address_mapped.h"
#include "hardware/regs/i2c.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_i2c
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/i2c.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(I2C_IC_CON_OFFSET) // I2C_IC_CON
    // I2C Control Register
    // 0x00000400 [10]    : STOP_DET_IF_MASTER_ACTIVE (0): Master issues the STOP_DET interrupt irrespective of whether...
    // 0x00000200 [9]     : RX_FIFO_FULL_HLD_CTRL (0): This bit controls whether DW_apb_i2c should hold the bus when the Rx...
    // 0x00000100 [8]     : TX_EMPTY_CTRL (0): This bit controls the generation of the TX_EMPTY interrupt, as described in...
    // 0x00000080 [7]     : STOP_DET_IFADDRESSED (0): In slave mode: - 1'b1:  issues the STOP_DET interrupt only when it is...
    // 0x00000040 [6]     : IC_SLAVE_DISABLE (1): This bit controls whether I2C has its slave disabled, which means once...
    // 0x00000020 [5]     : IC_RESTART_EN (1): Determines whether RESTART conditions may be sent when acting as a master
    // 0x00000010 [4]     : IC_10BITADDR_MASTER (0): Controls whether the DW_apb_i2c starts its transfers in 7- or 10-bit...
    // 0x00000008 [3]     : IC_10BITADDR_SLAVE (0): When acting as a slave, this bit controls whether the DW_apb_i2c...
    // 0x00000006 [2:1]   : SPEED (0x2): These bits control at which speed the DW_apb_i2c operates; its setting is relevant...
    // 0x00000001 [0]     : MASTER_MODE (1): This bit controls whether the DW_apb_i2c master is enabled
    io_rw_32 con;

    _REG_(I2C_IC_TAR_OFFSET) // I2C_IC_TAR
    // I2C Target Address Register
    // 0x00000800 [11]    : SPECIAL (0): This bit indicates whether software performs a Device-ID or General Call or START...
    // 0x00000400 [10]    : GC_OR_START (0): If bit 11 (SPECIAL) is set to 1 and bit 13(Device-ID) is set to 0, then this...
    // 0x000003ff [9:0]   : IC_TAR (0x55): This is the target address for any master transaction
    io_rw_32 tar;

    _REG_(I2C_IC_SAR_OFFSET) // I2C_IC_SAR
    // I2C Slave Address Register
    // 0x000003ff [9:0]   : IC_SAR (0x55): The IC_SAR holds the slave address when the I2C is operating as a slave
    io_rw_32 sar;

    uint32_t _pad0;

    _REG_(I2C_IC_DATA_CMD_OFFSET) // I2C_IC_DATA_CMD
    // I2C Rx/Tx Data Buffer and Command Register; this is the register the CPU writes to when filling the TX FIFO and the...
    // 0x00000800 [11]    : FIRST_DATA_BYTE (0): Indicates the first data byte received after the address phase for receive...
    // 0x00000400 [10]    : RESTART (0): This bit controls whether a RESTART is issued before the byte is sent or received
    // 0x00000200 [9]     : STOP (0): This bit controls whether a STOP is issued after the byte is sent or received
    // 0x00000100 [8]     : CMD (0): This bit controls whether a read or a write is performed
    // 0x000000ff [7:0]   : DAT (0): This register contains the data to be transmitted or received on the I2C bus
    io_rw_32 data_cmd;

    _REG_(I2C_IC_SS_SCL_HCNT_OFFSET) // I2C_IC_SS_SCL_HCNT
    // Standard Speed I2C Clock SCL High Count Register
    // 0x0000ffff [15:0]  : IC_SS_SCL_HCNT (0x28): This register must be set before any I2C bus transaction can take place...
    io_rw_32 ss_scl_hcnt;

    _REG_(I2C_IC_SS_SCL_LCNT_OFFSET) // I2C_IC_SS_SCL_LCNT
    // Standard Speed I2C Clock SCL Low Count Register
    // 0x0000ffff [15:0]  : IC_SS_SCL_LCNT (0x2f): This register must be set before any I2C bus transaction can take place...
    io_rw_32 ss_scl_lcnt;

    _REG_(I2C_IC_FS_SCL_HCNT_OFFSET) // I2C_IC_FS_SCL_HCNT
    // Fast Mode or Fast Mode Plus I2C Clock SCL High Count Register
    // 0x0000ffff [15:0]  : IC_FS_SCL_HCNT (0x6): This register must be set before any I2C bus transaction can take place...
    io_rw_32 fs_scl_hcnt;

    _REG_(I2C_IC_FS_SCL_LCNT_OFFSET) // I2C_IC_FS_SCL_LCNT
    // Fast Mode or Fast Mode Plus I2C Clock SCL Low Count Register
    // 0x0000ffff [15:0]  : IC_FS_SCL_LCNT (0xd): This register must be set before any I2C bus transaction can take place...
    io_rw_32 fs_scl_lcnt;

    uint32_t _pad1[2];

    _REG_(I2C_IC_INTR_STAT_OFFSET) // I2C_IC_INTR_STAT
    // I2C Interrupt Status Register
    // 0x00001000 [12]    : R_RESTART_DET (0): See IC_RAW_INTR_STAT for a detailed description of R_RESTART_DET bit
    // 0x00000800 [11]    : R_GEN_CALL (0): See IC_RAW_INTR_STAT for a detailed description of R_GEN_CALL bit
    // 0x00000400 [10]    : R_START_DET (0): See IC_RAW_INTR_STAT for a detailed description of R_START_DET bit
    // 0x00000200 [9]     : R_STOP_DET (0): See IC_RAW_INTR_STAT for a detailed description of R_STOP_DET bit
    // 0x00000100 [8]     : R_ACTIVITY (0): See IC_RAW_INTR_STAT for a detailed description of R_ACTIVITY bit
    // 0x00000080 [7]     : R_RX_DONE (0): See IC_RAW_INTR_STAT for a detailed description of R_RX_DONE bit
    // 0x00000040 [6]     : R_TX_ABRT (0): See IC_RAW_INTR_STAT for a detailed description of R_TX_ABRT bit
    // 0x00000020 [5]     : R_RD_REQ (0): See IC_RAW_INTR_STAT for a detailed description of R_RD_REQ bit
    // 0x00000010 [4]     : R_TX_EMPTY (0): See IC_RAW_INTR_STAT for a detailed description of R_TX_EMPTY bit
    // 0x00000008 [3]     : R_TX_OVER (0): See IC_RAW_INTR_STAT for a detailed description of R_TX_OVER bit
    // 0x00000004 [2]     : R_RX_FULL (0): See IC_RAW_INTR_STAT for a detailed description of R_RX_FULL bit
    // 0x00000002 [1]     : R_RX_OVER (0): See IC_RAW_INTR_STAT for a detailed description of R_RX_OVER bit
    // 0x00000001 [0]     : R_RX_UNDER (0): See IC_RAW_INTR_STAT for a detailed description of R_RX_UNDER bit
    io_ro_32 intr_stat;

    _REG_(I2C_IC_INTR_MASK_OFFSET) // I2C_IC_INTR_MASK
    // I2C Interrupt Mask Register
    // 0x00001000 [12]    : M_RESTART_DET (0): This bit masks the R_RESTART_DET interrupt in IC_INTR_STAT register
    // 0x00000800 [11]    : M_GEN_CALL (1): This bit masks the R_GEN_CALL interrupt in IC_INTR_STAT register
    // 0x00000400 [10]    : M_START_DET (0): This bit masks the R_START_DET interrupt in IC_INTR_STAT register
    // 0x00000200 [9]     : M_STOP_DET (0): This bit masks the R_STOP_DET interrupt in IC_INTR_STAT register
    // 0x00000100 [8]     : M_ACTIVITY (0): This bit masks the R_ACTIVITY interrupt in IC_INTR_STAT register
    // 0x00000080 [7]     : M_RX_DONE (1): This bit masks the R_RX_DONE interrupt in IC_INTR_STAT register
    // 0x00000040 [6]     : M_TX_ABRT (1): This bit masks the R_TX_ABRT interrupt in IC_INTR_STAT register
    // 0x00000020 [5]     : M_RD_REQ (1): This bit masks the R_RD_REQ interrupt in IC_INTR_STAT register
    // 0x00000010 [4]     : M_TX_EMPTY (1): This bit masks the R_TX_EMPTY interrupt in IC_INTR_STAT register
    // 0x00000008 [3]     : M_TX_OVER (1): This bit masks the R_TX_OVER interrupt in IC_INTR_STAT register
    // 0x00000004 [2]     : M_RX_FULL (1): This bit masks the R_RX_FULL interrupt in IC_INTR_STAT register
    // 0x00000002 [1]     : M_RX_OVER (1): This bit masks the R_RX_OVER interrupt in IC_INTR_STAT register
    // 0x00000001 [0]     : M_RX_UNDER (1): This bit masks the R_RX_UNDER interrupt in IC_INTR_STAT register
    io_rw_32 intr_mask;

    _REG_(I2C_IC_RAW_INTR_STAT_OFFSET) // I2C_IC_RAW_INTR_STAT
    // I2C Raw Interrupt Status Register
    // 0x00001000 [12]    : RESTART_DET (0): Indicates whether a RESTART condition has occurred on the I2C interface when...
    // 0x00000800 [11]    : GEN_CALL (0): Set only when a General Call address is received and it is acknowledged
    // 0x00000400 [10]    : START_DET (0): Indicates whether a START or RESTART condition has occurred on the I2C interface...
    // 0x00000200 [9]     : STOP_DET (0): Indicates whether a STOP condition has occurred on the I2C interface regardless...
    // 0x00000100 [8]     : ACTIVITY (0): This bit captures DW_apb_i2c activity and stays set until it is cleared
    // 0x00000080 [7]     : RX_DONE (0): When the DW_apb_i2c is acting as a slave-transmitter, this bit is set to 1 if the...
    // 0x00000040 [6]     : TX_ABRT (0): This bit indicates if DW_apb_i2c, as an I2C transmitter, is unable to complete the...
    // 0x00000020 [5]     : RD_REQ (0): This bit is set to 1 when DW_apb_i2c is acting as a slave and another I2C master is...
    // 0x00000010 [4]     : TX_EMPTY (0): The behavior of the TX_EMPTY interrupt status differs based on the TX_EMPTY_CTRL...
    // 0x00000008 [3]     : TX_OVER (0): Set during transmit if the transmit buffer is filled to IC_TX_BUFFER_DEPTH and the...
    // 0x00000004 [2]     : RX_FULL (0): Set when the receive buffer reaches or goes above the RX_TL threshold in the...
    // 0x00000002 [1]     : RX_OVER (0): Set if the receive buffer is completely filled to IC_RX_BUFFER_DEPTH and an...
    // 0x00000001 [0]     : RX_UNDER (0): Set if the processor attempts to read the receive buffer when it is empty by...
    io_ro_32 raw_intr_stat;

    _REG_(I2C_IC_RX_TL_OFFSET) // I2C_IC_RX_TL
    // I2C Receive FIFO Threshold Register
    // 0x000000ff [7:0]   : RX_TL (0): Receive FIFO Threshold Level
    io_rw_32 rx_tl;

    _REG_(I2C_IC_TX_TL_OFFSET) // I2C_IC_TX_TL
    // I2C Transmit FIFO Threshold Register
    // 0x000000ff [7:0]   : TX_TL (0): Transmit FIFO Threshold Level
    io_rw_32 tx_tl;

    _REG_(I2C_IC_CLR_INTR_OFFSET) // I2C_IC_CLR_INTR
    // Clear Combined and Individual Interrupt Register
    // 0x00000001 [0]     : CLR_INTR (0): Read this register to clear the combined interrupt, all individual interrupts,...
    io_ro_32 clr_intr;

    _REG_(I2C_IC_CLR_RX_UNDER_OFFSET) // I2C_IC_CLR_RX_UNDER
    // Clear RX_UNDER Interrupt Register
    // 0x00000001 [0]     : CLR_RX_UNDER (0): Read this register to clear the RX_UNDER interrupt (bit 0) of the...
    io_ro_32 clr_rx_under;

    _REG_(I2C_IC_CLR_RX_OVER_OFFSET) // I2C_IC_CLR_RX_OVER
    // Clear RX_OVER Interrupt Register
    // 0x00000001 [0]     : CLR_RX_OVER (0): Read this register to clear the RX_OVER interrupt (bit 1) of the...
    io_ro_32 clr_rx_over;

    _REG_(I2C_IC_CLR_TX_OVER_OFFSET) // I2C_IC_CLR_TX_OVER
    // Clear TX_OVER Interrupt Register
    // 0x00000001 [0]     : CLR_TX_OVER (0): Read this register to clear the TX_OVER interrupt (bit 3) of the...
    io_ro_32 clr_tx_over;

    _REG_(I2C_IC_CLR_RD_REQ_OFFSET) // I2C_IC_CLR_RD_REQ
    // Clear RD_REQ Interrupt Register
    // 0x00000001 [0]     : CLR_RD_REQ (0): Read this register to clear the RD_REQ interrupt (bit 5) of the...
    io_ro_32 clr_rd_req;

    _REG_(I2C_IC_CLR_TX_ABRT_OFFSET) // I2C_IC_CLR_TX_ABRT
    // Clear TX_ABRT Interrupt Register
    // 0x00000001 [0]     : CLR_TX_ABRT (0): Read this register to clear the TX_ABRT interrupt (bit 6) of the...
    io_ro_32 clr_tx_abrt;

    _REG_(I2C_IC_CLR_RX_DONE_OFFSET) // I2C_IC_CLR_RX_DONE
    // Clear RX_DONE Interrupt Register
    // 0x00000001 [0]     : CLR_RX_DONE (0): Read this register to clear the RX_DONE interrupt (bit 7) of the...
    io_ro_32 clr_rx_done;

    _REG_(I2C_IC_CLR_ACTIVITY_OFFSET) // I2C_IC_CLR_ACTIVITY
    // Clear ACTIVITY Interrupt Register
    // 0x00000001 [0]     : CLR_ACTIVITY (0): Reading this register clears the ACTIVITY interrupt if the I2C is not active anymore
    io_ro_32 clr_activity;

    _REG_(I2C_IC_CLR_STOP_DET_OFFSET) // I2C_IC_CLR_STOP_DET
    // Clear STOP_DET Interrupt Register
    // 0x00000001 [0]     : CLR_STOP_DET (0): Read this register to clear the STOP_DET interrupt (bit 9) of the...
    io_ro_32 clr_stop_det;

    _REG_(I2C_IC_CLR_START_DET_OFFSET) // I2C_IC_CLR_START_DET
    // Clear START_DET Interrupt Register
    // 0x00000001 [0]     : CLR_START_DET (0): Read this register to clear the START_DET interrupt (bit 10) of the...
    io_ro_32 clr_start_det;

    _REG_(I2C_IC_CLR_GEN_CALL_OFFSET) // I2C_IC_CLR_GEN_CALL
    // Clear GEN_CALL Interrupt Register
    // 0x00000001 [0]     : CLR_GEN_CALL (0): Read this register to clear the GEN_CALL interrupt (bit 11) of...
    io_ro_32 clr_gen_call;

    _REG_(I2C_IC_ENABLE_OFFSET) // I2C_IC_ENABLE
    // I2C Enable Register
    // 0x00000004 [2]     : TX_CMD_BLOCK (0): In Master mode: - 1'b1: Blocks the transmission of data on I2C bus even if Tx...
    // 0x00000002 [1]     : ABORT (0): When set, the controller initiates the transfer abort
    // 0x00000001 [0]     : ENABLE (0): Controls whether the DW_apb_i2c is enabled
    io_rw_32 enable;

    _REG_(I2C_IC_STATUS_OFFSET) // I2C_IC_STATUS
    // I2C Status Register
    // 0x00000040 [6]     : SLV_ACTIVITY (0): Slave FSM Activity Status
    // 0x00000020 [5]     : MST_ACTIVITY (0): Master FSM Activity Status
    // 0x00000010 [4]     : RFF (0): Receive FIFO Completely Full
    // 0x00000008 [3]     : RFNE (0): Receive FIFO Not Empty
    // 0x00000004 [2]     : TFE (1): Transmit FIFO Completely Empty
    // 0x00000002 [1]     : TFNF (1): Transmit FIFO Not Full
    // 0x00000001 [0]     : ACTIVITY (0): I2C Activity Status
    io_ro_32 status;

    _REG_(I2C_IC_TXFLR_OFFSET) // I2C_IC_TXFLR
    // I2C Transmit FIFO Level Register This register contains the number of valid data entries in the transmit FIFO buffer
    // 0x0000001f [4:0]   : TXFLR (0): Transmit FIFO Level
    io_ro_32 txflr;

    _REG_(I2C_IC_RXFLR_OFFSET) // I2C_IC_RXFLR
    // I2C Receive FIFO Level Register This register contains the number of valid data entries in the receive FIFO buffer
    // 0x0000001f [4:0]   : RXFLR (0): Receive FIFO Level
    io_ro_32 rxflr;

    _REG_(I2C_IC_SDA_HOLD_OFFSET) // I2C_IC_SDA_HOLD
    // I2C SDA Hold Time Length Register
    // 0x00ff0000 [23:16] : IC_SDA_RX_HOLD (0): Sets the required SDA hold time in units of ic_clk period, when DW_apb_i2c...
    // 0x0000ffff [15:0]  : IC_SDA_TX_HOLD (1): Sets the required SDA hold time in units of ic_clk period, when DW_apb_i2c...
    io_rw_32 sda_hold;

    _REG_(I2C_IC_TX_ABRT_SOURCE_OFFSET) // I2C_IC_TX_ABRT_SOURCE
    // I2C Transmit Abort Source Register
    // 0xff800000 [31:23] : TX_FLUSH_CNT (0): This field indicates the number of Tx FIFO Data Commands which are flushed...
    // 0x00010000 [16]    : ABRT_USER_ABRT (0): This is a master-mode-only bit
    // 0x00008000 [15]    : ABRT_SLVRD_INTX (0): 1: When the processor side responds to a slave mode request for data to be...
    // 0x00004000 [14]    : ABRT_SLV_ARBLOST (0): This field indicates that a Slave has lost the bus while transmitting...
    // 0x00002000 [13]    : ABRT_SLVFLUSH_TXFIFO (0): This field specifies that the Slave has received a read command and...
    // 0x00001000 [12]    : ARB_LOST (0): This field specifies that the Master has lost arbitration, or if...
    // 0x00000800 [11]    : ABRT_MASTER_DIS (0): This field indicates that the User tries to initiate a Master operation...
    // 0x00000400 [10]    : ABRT_10B_RD_NORSTRT (0): This field indicates that the restart is disabled (IC_RESTART_EN bit...
    // 0x00000200 [9]     : ABRT_SBYTE_NORSTRT (0): To clear Bit 9, the source of the ABRT_SBYTE_NORSTRT must be fixed...
    // 0x00000100 [8]     : ABRT_HS_NORSTRT (0): This field indicates that the restart is disabled (IC_RESTART_EN bit...
    // 0x00000080 [7]     : ABRT_SBYTE_ACKDET (0): This field indicates that the Master has sent a START Byte and the START...
    // 0x00000040 [6]     : ABRT_HS_ACKDET (0): This field indicates that the Master is in High Speed mode and the High...
    // 0x00000020 [5]     : ABRT_GCALL_READ (0): This field indicates that DW_apb_i2c in the master mode has sent a General...
    // 0x00000010 [4]     : ABRT_GCALL_NOACK (0): This field indicates that DW_apb_i2c in master mode has sent a General...
    // 0x00000008 [3]     : ABRT_TXDATA_NOACK (0): This field indicates the master-mode only bit
    // 0x00000004 [2]     : ABRT_10ADDR2_NOACK (0): This field indicates that the Master is in 10-bit address mode and that...
    // 0x00000002 [1]     : ABRT_10ADDR1_NOACK (0): This field indicates that the Master is in 10-bit address mode and the...
    // 0x00000001 [0]     : ABRT_7B_ADDR_NOACK (0): This field indicates that the Master is in 7-bit addressing mode and...
    io_ro_32 tx_abrt_source;

    _REG_(I2C_IC_SLV_DATA_NACK_ONLY_OFFSET) // I2C_IC_SLV_DATA_NACK_ONLY
    // Generate Slave Data NACK Register
    // 0x00000001 [0]     : NACK (0): Generate NACK
    io_rw_32 slv_data_nack_only;

    _REG_(I2C_IC_DMA_CR_OFFSET) // I2C_IC_DMA_CR
    // DMA Control Register
    // 0x00000002 [1]     : TDMAE (0): Transmit DMA Enable
    // 0x00000001 [0]     : RDMAE (0): Receive DMA Enable
    io_rw_32 dma_cr;

    _REG_(I2C_IC_DMA_TDLR_OFFSET) // I2C_IC_DMA_TDLR
    // DMA Transmit Data Level Register
    // 0x0000000f [3:0]   : DMATDL (0): Transmit Data Level
    io_rw_32 dma_tdlr;

    _REG_(I2C_IC_DMA_RDLR_OFFSET) // I2C_IC_DMA_RDLR
    // I2C Receive Data Level Register
    // 0x0000000f [3:0]   : DMARDL (0): Receive Data Level
    io_rw_32 dma_rdlr;

    _REG_(I2C_IC_SDA_SETUP_OFFSET) // I2C_IC_SDA_SETUP
    // I2C SDA Setup Register
    // 0x000000ff [7:0]   : SDA_SETUP (0x64): SDA Setup
    io_rw_32 sda_setup;

    _REG_(I2C_IC_ACK_GENERAL_CALL_OFFSET) // I2C_IC_ACK_GENERAL_CALL
    // I2C ACK General Call Register
    // 0x00000001 [0]     : ACK_GEN_CALL (1): ACK General Call
    io_rw_32 ack_general_call;

    _REG_(I2C_IC_ENABLE_STATUS_OFFSET) // I2C_IC_ENABLE_STATUS
    // I2C Enable Status Register
    // 0x00000004 [2]     : SLV_RX_DATA_LOST (0): Slave Received Data Lost
    // 0x00000002 [1]     : SLV_DISABLED_WHILE_BUSY (0): Slave Disabled While Busy (Transmit, Receive)
    // 0x00000001 [0]     : IC_EN (0): ic_en Status
    io_ro_32 enable_status;

    _REG_(I2C_IC_FS_SPKLEN_OFFSET) // I2C_IC_FS_SPKLEN
    // I2C SS, FS or FM+ spike suppression limit
    // 0x000000ff [7:0]   : IC_FS_SPKLEN (0x7): This register must be set before any I2C bus transaction can take place to...
    io_rw_32 fs_spklen;

    uint32_t _pad2;

    _REG_(I2C_IC_CLR_RESTART_DET_OFFSET) // I2C_IC_CLR_RESTART_DET
    // Clear RESTART_DET Interrupt Register
    // 0x00000001 [0]     : CLR_RESTART_DET (0): Read this register to clear the RESTART_DET interrupt (bit 12) of...
    io_ro_32 clr_restart_det;

    uint32_t _pad3[18];

    _REG_(I2C_IC_COMP_PARAM_1_OFFSET) // I2C_IC_COMP_PARAM_1
    // Component Parameter Register 1
    // 0x00ff0000 [23:16] : TX_BUFFER_DEPTH (0): TX Buffer Depth = 16
    // 0x0000ff00 [15:8]  : RX_BUFFER_DEPTH (0): RX Buffer Depth = 16
    // 0x00000080 [7]     : ADD_ENCODED_PARAMS (0): Encoded parameters not visible
    // 0x00000040 [6]     : HAS_DMA (0): DMA handshaking signals are enabled
    // 0x00000020 [5]     : INTR_IO (0): COMBINED Interrupt outputs
    // 0x00000010 [4]     : HC_COUNT_VALUES (0): Programmable count values for each mode
    // 0x0000000c [3:2]   : MAX_SPEED_MODE (0): MAX SPEED MODE = FAST MODE
    // 0x00000003 [1:0]   : APB_DATA_WIDTH (0): APB data bus width is 32 bits
    io_ro_32 comp_param_1;

    _REG_(I2C_IC_COMP_VERSION_OFFSET) // I2C_IC_COMP_VERSION
    // I2C Component Version Register
    // 0xffffffff [31:0]  : IC_COMP_VERSION (0x3230312a)
    io_ro_32 comp_version;

    _REG_(I2C_IC_COMP_TYPE_OFFSET) // I2C_IC_COMP_TYPE
    // I2C Component Type Register
    // 0xffffffff [31:0]  : IC_COMP_TYPE (0x44570140): Designware Component Type number = 0x44_57_01_40
    io_ro_32 comp_type;
} i2c_hw_t;

#define i2c0_hw ((i2c_hw_t *)I2C0_BASE)
#define i2c1_hw ((i2c_hw_t *)I2C1_BASE)

#endif
