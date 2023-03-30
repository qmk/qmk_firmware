// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_PIO_H
#define _HARDWARE_STRUCTS_PIO_H

#include "hardware/address_mapped.h"
#include "hardware/regs/pio.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_pio
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/pio.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct pio_sm_hw {
    _REG_(PIO_SM0_CLKDIV_OFFSET) // PIO_SM0_CLKDIV
    // Clock divisor register for state machine 0
    // 0xffff0000 [31:16] : INT (1): Effective frequency is sysclk/(int + frac/256)
    // 0x0000ff00 [15:8]  : FRAC (0): Fractional part of clock divisor
    io_rw_32 clkdiv;

    _REG_(PIO_SM0_EXECCTRL_OFFSET) // PIO_SM0_EXECCTRL
    // Execution/behavioural settings for state machine 0
    // 0x80000000 [31]    : EXEC_STALLED (0): If 1, an instruction written to SMx_INSTR is stalled, and latched by the state machine
    // 0x40000000 [30]    : SIDE_EN (0): If 1, the MSB of the Delay/Side-set instruction field is used as side-set enable,...
    // 0x20000000 [29]    : SIDE_PINDIR (0): If 1, side-set data is asserted to pin directions, instead of pin values
    // 0x1f000000 [28:24] : JMP_PIN (0): The GPIO number to use as condition for JMP PIN
    // 0x00f80000 [23:19] : OUT_EN_SEL (0): Which data bit to use for inline OUT enable
    // 0x00040000 [18]    : INLINE_OUT_EN (0): If 1, use a bit of OUT data as an auxiliary write enable
    // 0x00020000 [17]    : OUT_STICKY (0): Continuously assert the most recent OUT/SET to the pins
    // 0x0001f000 [16:12] : WRAP_TOP (0x1f): After reaching this address, execution is wrapped to wrap_bottom
    // 0x00000f80 [11:7]  : WRAP_BOTTOM (0): After reaching wrap_top, execution is wrapped to this address
    // 0x00000010 [4]     : STATUS_SEL (0): Comparison used for the MOV x, STATUS instruction
    // 0x0000000f [3:0]   : STATUS_N (0): Comparison level for the MOV x, STATUS instruction
    io_rw_32 execctrl;

    _REG_(PIO_SM0_SHIFTCTRL_OFFSET) // PIO_SM0_SHIFTCTRL
    // Control behaviour of the input/output shift registers for state machine 0
    // 0x80000000 [31]    : FJOIN_RX (0): When 1, RX FIFO steals the TX FIFO's storage, and becomes twice as deep
    // 0x40000000 [30]    : FJOIN_TX (0): When 1, TX FIFO steals the RX FIFO's storage, and becomes twice as deep
    // 0x3e000000 [29:25] : PULL_THRESH (0): Number of bits shifted out of OSR before autopull, or conditional pull (PULL...
    // 0x01f00000 [24:20] : PUSH_THRESH (0): Number of bits shifted into ISR before autopush, or conditional push (PUSH...
    // 0x00080000 [19]    : OUT_SHIFTDIR (1): 1 = shift out of output shift register to right
    // 0x00040000 [18]    : IN_SHIFTDIR (1): 1 = shift input shift register to right (data enters from left)
    // 0x00020000 [17]    : AUTOPULL (0): Pull automatically when the output shift register is emptied, i
    // 0x00010000 [16]    : AUTOPUSH (0): Push automatically when the input shift register is filled, i
    io_rw_32 shiftctrl;

    _REG_(PIO_SM0_ADDR_OFFSET) // PIO_SM0_ADDR
    // Current instruction address of state machine 0
    // 0x0000001f [4:0]   : SM0_ADDR (0)
    io_ro_32 addr;

    _REG_(PIO_SM0_INSTR_OFFSET) // PIO_SM0_INSTR
    // Read to see the instruction currently addressed by state machine 0's program counter
    // 0x0000ffff [15:0]  : SM0_INSTR (0)
    io_rw_32 instr;

    _REG_(PIO_SM0_PINCTRL_OFFSET) // PIO_SM0_PINCTRL
    // State machine pin control
    // 0xe0000000 [31:29] : SIDESET_COUNT (0): The number of MSBs of the Delay/Side-set instruction field which are used...
    // 0x1c000000 [28:26] : SET_COUNT (0x5): The number of pins asserted by a SET
    // 0x03f00000 [25:20] : OUT_COUNT (0): The number of pins asserted by an OUT PINS, OUT PINDIRS or MOV PINS instruction
    // 0x000f8000 [19:15] : IN_BASE (0): The pin which is mapped to the least-significant bit of a state machine's IN data bus
    // 0x00007c00 [14:10] : SIDESET_BASE (0): The lowest-numbered pin that will be affected by a side-set operation
    // 0x000003e0 [9:5]   : SET_BASE (0): The lowest-numbered pin that will be affected by a SET PINS or SET PINDIRS instruction
    // 0x0000001f [4:0]   : OUT_BASE (0): The lowest-numbered pin that will be affected by an OUT PINS, OUT PINDIRS or MOV...
    io_rw_32 pinctrl;
} pio_sm_hw_t;

typedef struct {
    _REG_(PIO_CTRL_OFFSET) // PIO_CTRL
    // PIO control register
    // 0x00000f00 [11:8]  : CLKDIV_RESTART (0): Restart a state machine's clock divider from an initial phase of 0
    // 0x000000f0 [7:4]   : SM_RESTART (0): Write 1 to instantly clear internal SM state which may be otherwise difficult...
    // 0x0000000f [3:0]   : SM_ENABLE (0): Enable/disable each of the four state machines by writing 1/0 to each of these four bits
    io_rw_32 ctrl;

    _REG_(PIO_FSTAT_OFFSET) // PIO_FSTAT
    // FIFO status register
    // 0x0f000000 [27:24] : TXEMPTY (0xf): State machine TX FIFO is empty
    // 0x000f0000 [19:16] : TXFULL (0): State machine TX FIFO is full
    // 0x00000f00 [11:8]  : RXEMPTY (0xf): State machine RX FIFO is empty
    // 0x0000000f [3:0]   : RXFULL (0): State machine RX FIFO is full
    io_ro_32 fstat;

    _REG_(PIO_FDEBUG_OFFSET) // PIO_FDEBUG
    // FIFO debug register
    // 0x0f000000 [27:24] : TXSTALL (0): State machine has stalled on empty TX FIFO during a blocking PULL, or an OUT with...
    // 0x000f0000 [19:16] : TXOVER (0): TX FIFO overflow (i
    // 0x00000f00 [11:8]  : RXUNDER (0): RX FIFO underflow (i
    // 0x0000000f [3:0]   : RXSTALL (0): State machine has stalled on full RX FIFO during a blocking PUSH, or an IN with...
    io_rw_32 fdebug;

    _REG_(PIO_FLEVEL_OFFSET) // PIO_FLEVEL
    // FIFO levels
    // 0xf0000000 [31:28] : RX3 (0)
    // 0x0f000000 [27:24] : TX3 (0)
    // 0x00f00000 [23:20] : RX2 (0)
    // 0x000f0000 [19:16] : TX2 (0)
    // 0x0000f000 [15:12] : RX1 (0)
    // 0x00000f00 [11:8]  : TX1 (0)
    // 0x000000f0 [7:4]   : RX0 (0)
    // 0x0000000f [3:0]   : TX0 (0)
    io_ro_32 flevel;

    _REG_(PIO_TXF0_OFFSET) // PIO_TXF0
    // (Description copied from array index 0 register PIO_TXF0 applies similarly to other array indexes)
    //
    // Direct write access to the TX FIFO for this state machine
    io_wo_32 txf[NUM_PIO_STATE_MACHINES]; // 4

    _REG_(PIO_RXF0_OFFSET) // PIO_RXF0
    // (Description copied from array index 0 register PIO_RXF0 applies similarly to other array indexes)
    //
    // Direct read access to the RX FIFO for this state machine
    io_ro_32 rxf[NUM_PIO_STATE_MACHINES]; // 4

    _REG_(PIO_IRQ_OFFSET) // PIO_IRQ
    // State machine IRQ flags register
    // 0x000000ff [7:0]   : IRQ (0)
    io_rw_32 irq;

    _REG_(PIO_IRQ_FORCE_OFFSET) // PIO_IRQ_FORCE
    // Writing a 1 to each of these bits will forcibly assert the corresponding IRQ
    // 0x000000ff [7:0]   : IRQ_FORCE (0)
    io_wo_32 irq_force;

    _REG_(PIO_INPUT_SYNC_BYPASS_OFFSET) // PIO_INPUT_SYNC_BYPASS
    // There is a 2-flipflop synchronizer on each GPIO input, which protects PIO logic from metastabilities
    io_rw_32 input_sync_bypass;

    _REG_(PIO_DBG_PADOUT_OFFSET) // PIO_DBG_PADOUT
    // Read to sample the pad output values PIO is currently driving to the GPIOs
    io_ro_32 dbg_padout;

    _REG_(PIO_DBG_PADOE_OFFSET) // PIO_DBG_PADOE
    // Read to sample the pad output enables (direction) PIO is currently driving to the GPIOs
    io_ro_32 dbg_padoe;

    _REG_(PIO_DBG_CFGINFO_OFFSET) // PIO_DBG_CFGINFO
    // The PIO hardware has some free parameters that may vary between chip products
    // 0x003f0000 [21:16] : IMEM_SIZE (0): The size of the instruction memory, measured in units of one instruction
    // 0x00000f00 [11:8]  : SM_COUNT (0): The number of state machines this PIO instance is equipped with
    // 0x0000003f [5:0]   : FIFO_DEPTH (0): The depth of the state machine TX/RX FIFOs, measured in words
    io_ro_32 dbg_cfginfo;

    _REG_(PIO_INSTR_MEM0_OFFSET) // PIO_INSTR_MEM0
    // (Description copied from array index 0 register PIO_INSTR_MEM0 applies similarly to other array indexes)
    //
    // Write-only access to instruction memory location 0
    // 0x0000ffff [15:0]  : INSTR_MEM0 (0)
    io_wo_32 instr_mem[PIO_INSTRUCTION_COUNT]; // 32

    pio_sm_hw_t sm[NUM_PIO_STATE_MACHINES]; // 4

    _REG_(PIO_INTR_OFFSET) // PIO_INTR
    // Raw Interrupts
    // 0x00000800 [11]    : SM3 (0)
    // 0x00000400 [10]    : SM2 (0)
    // 0x00000200 [9]     : SM1 (0)
    // 0x00000100 [8]     : SM0 (0)
    // 0x00000080 [7]     : SM3_TXNFULL (0)
    // 0x00000040 [6]     : SM2_TXNFULL (0)
    // 0x00000020 [5]     : SM1_TXNFULL (0)
    // 0x00000010 [4]     : SM0_TXNFULL (0)
    // 0x00000008 [3]     : SM3_RXNEMPTY (0)
    // 0x00000004 [2]     : SM2_RXNEMPTY (0)
    // 0x00000002 [1]     : SM1_RXNEMPTY (0)
    // 0x00000001 [0]     : SM0_RXNEMPTY (0)
    io_ro_32 intr;

    _REG_(PIO_IRQ0_INTE_OFFSET) // PIO_IRQ0_INTE
    // Interrupt Enable for irq0
    // 0x00000800 [11]    : SM3 (0)
    // 0x00000400 [10]    : SM2 (0)
    // 0x00000200 [9]     : SM1 (0)
    // 0x00000100 [8]     : SM0 (0)
    // 0x00000080 [7]     : SM3_TXNFULL (0)
    // 0x00000040 [6]     : SM2_TXNFULL (0)
    // 0x00000020 [5]     : SM1_TXNFULL (0)
    // 0x00000010 [4]     : SM0_TXNFULL (0)
    // 0x00000008 [3]     : SM3_RXNEMPTY (0)
    // 0x00000004 [2]     : SM2_RXNEMPTY (0)
    // 0x00000002 [1]     : SM1_RXNEMPTY (0)
    // 0x00000001 [0]     : SM0_RXNEMPTY (0)
    io_rw_32 inte0;

    _REG_(PIO_IRQ0_INTF_OFFSET) // PIO_IRQ0_INTF
    // Interrupt Force for irq0
    // 0x00000800 [11]    : SM3 (0)
    // 0x00000400 [10]    : SM2 (0)
    // 0x00000200 [9]     : SM1 (0)
    // 0x00000100 [8]     : SM0 (0)
    // 0x00000080 [7]     : SM3_TXNFULL (0)
    // 0x00000040 [6]     : SM2_TXNFULL (0)
    // 0x00000020 [5]     : SM1_TXNFULL (0)
    // 0x00000010 [4]     : SM0_TXNFULL (0)
    // 0x00000008 [3]     : SM3_RXNEMPTY (0)
    // 0x00000004 [2]     : SM2_RXNEMPTY (0)
    // 0x00000002 [1]     : SM1_RXNEMPTY (0)
    // 0x00000001 [0]     : SM0_RXNEMPTY (0)
    io_rw_32 intf0;

    _REG_(PIO_IRQ0_INTS_OFFSET) // PIO_IRQ0_INTS
    // Interrupt status after masking & forcing for irq0
    // 0x00000800 [11]    : SM3 (0)
    // 0x00000400 [10]    : SM2 (0)
    // 0x00000200 [9]     : SM1 (0)
    // 0x00000100 [8]     : SM0 (0)
    // 0x00000080 [7]     : SM3_TXNFULL (0)
    // 0x00000040 [6]     : SM2_TXNFULL (0)
    // 0x00000020 [5]     : SM1_TXNFULL (0)
    // 0x00000010 [4]     : SM0_TXNFULL (0)
    // 0x00000008 [3]     : SM3_RXNEMPTY (0)
    // 0x00000004 [2]     : SM2_RXNEMPTY (0)
    // 0x00000002 [1]     : SM1_RXNEMPTY (0)
    // 0x00000001 [0]     : SM0_RXNEMPTY (0)
    io_ro_32 ints0;

    _REG_(PIO_IRQ1_INTE_OFFSET) // PIO_IRQ1_INTE
    // Interrupt Enable for irq1
    // 0x00000800 [11]    : SM3 (0)
    // 0x00000400 [10]    : SM2 (0)
    // 0x00000200 [9]     : SM1 (0)
    // 0x00000100 [8]     : SM0 (0)
    // 0x00000080 [7]     : SM3_TXNFULL (0)
    // 0x00000040 [6]     : SM2_TXNFULL (0)
    // 0x00000020 [5]     : SM1_TXNFULL (0)
    // 0x00000010 [4]     : SM0_TXNFULL (0)
    // 0x00000008 [3]     : SM3_RXNEMPTY (0)
    // 0x00000004 [2]     : SM2_RXNEMPTY (0)
    // 0x00000002 [1]     : SM1_RXNEMPTY (0)
    // 0x00000001 [0]     : SM0_RXNEMPTY (0)
    io_rw_32 inte1;

    _REG_(PIO_IRQ1_INTF_OFFSET) // PIO_IRQ1_INTF
    // Interrupt Force for irq1
    // 0x00000800 [11]    : SM3 (0)
    // 0x00000400 [10]    : SM2 (0)
    // 0x00000200 [9]     : SM1 (0)
    // 0x00000100 [8]     : SM0 (0)
    // 0x00000080 [7]     : SM3_TXNFULL (0)
    // 0x00000040 [6]     : SM2_TXNFULL (0)
    // 0x00000020 [5]     : SM1_TXNFULL (0)
    // 0x00000010 [4]     : SM0_TXNFULL (0)
    // 0x00000008 [3]     : SM3_RXNEMPTY (0)
    // 0x00000004 [2]     : SM2_RXNEMPTY (0)
    // 0x00000002 [1]     : SM1_RXNEMPTY (0)
    // 0x00000001 [0]     : SM0_RXNEMPTY (0)
    io_rw_32 intf1;

    _REG_(PIO_IRQ1_INTS_OFFSET) // PIO_IRQ1_INTS
    // Interrupt status after masking & forcing for irq1
    // 0x00000800 [11]    : SM3 (0)
    // 0x00000400 [10]    : SM2 (0)
    // 0x00000200 [9]     : SM1 (0)
    // 0x00000100 [8]     : SM0 (0)
    // 0x00000080 [7]     : SM3_TXNFULL (0)
    // 0x00000040 [6]     : SM2_TXNFULL (0)
    // 0x00000020 [5]     : SM1_TXNFULL (0)
    // 0x00000010 [4]     : SM0_TXNFULL (0)
    // 0x00000008 [3]     : SM3_RXNEMPTY (0)
    // 0x00000004 [2]     : SM2_RXNEMPTY (0)
    // 0x00000002 [1]     : SM1_RXNEMPTY (0)
    // 0x00000001 [0]     : SM0_RXNEMPTY (0)
    io_ro_32 ints1;
} pio_hw_t;

#define pio0_hw ((pio_hw_t *)PIO0_BASE)
#define pio1_hw ((pio_hw_t *)PIO1_BASE)

static_assert( NUM_PIO_STATE_MACHINES == 4, "");
static_assert( PIO_INSTRUCTION_COUNT == 32, "");

#endif
