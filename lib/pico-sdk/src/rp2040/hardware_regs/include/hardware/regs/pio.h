/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : PIO
// Version        : 1
// Bus type       : ahbl
// Description    : Programmable IO block
// =============================================================================
#ifndef HARDWARE_REGS_PIO_DEFINED
#define HARDWARE_REGS_PIO_DEFINED
// =============================================================================
// Register    : PIO_CTRL
// Description : PIO control register
#define PIO_CTRL_OFFSET _u(0x00000000)
#define PIO_CTRL_BITS   _u(0x00000fff)
#define PIO_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_CTRL_CLKDIV_RESTART
// Description : Restart a state machine's clock divider from an initial phase
//               of 0. Clock dividers are free-running, so once started, their
//               output (including fractional jitter) is completely determined
//               by the integer/fractional divisor configured in SMx_CLKDIV.
//               This means that, if multiple clock dividers with the same
//               divisor are restarted simultaneously, by writing multiple 1
//               bits to this field, the execution clocks of those state
//               machines will run in precise lockstep.
//
//               Note that setting/clearing SM_ENABLE does not stop the clock
//               divider from running, so once multiple state machines' clocks
//               are synchronised, it is safe to disable/reenable a state
//               machine, whilst keeping the clock dividers in sync.
//
//               Note also that CLKDIV_RESTART can be written to whilst the
//               state machine is running, and this is useful to resynchronise
//               clock dividers after the divisors (SMx_CLKDIV) have been
//               changed on-the-fly.
#define PIO_CTRL_CLKDIV_RESTART_RESET  _u(0x0)
#define PIO_CTRL_CLKDIV_RESTART_BITS   _u(0x00000f00)
#define PIO_CTRL_CLKDIV_RESTART_MSB    _u(11)
#define PIO_CTRL_CLKDIV_RESTART_LSB    _u(8)
#define PIO_CTRL_CLKDIV_RESTART_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : PIO_CTRL_SM_RESTART
// Description : Write 1 to instantly clear internal SM state which may be
//               otherwise difficult to access and will affect future execution.
//
//               Specifically, the following are cleared: input and output shift
//               counters; the contents of the input shift register; the delay
//               counter; the waiting-on-IRQ state; any stalled instruction
//               written to SMx_INSTR or run by OUT/MOV EXEC; any pin write left
//               asserted due to OUT_STICKY.
//
//               The program counter, the contents of the output shift register
//               and the X/Y scratch registers are not affected.
#define PIO_CTRL_SM_RESTART_RESET  _u(0x0)
#define PIO_CTRL_SM_RESTART_BITS   _u(0x000000f0)
#define PIO_CTRL_SM_RESTART_MSB    _u(7)
#define PIO_CTRL_SM_RESTART_LSB    _u(4)
#define PIO_CTRL_SM_RESTART_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : PIO_CTRL_SM_ENABLE
// Description : Enable/disable each of the four state machines by writing 1/0
//               to each of these four bits. When disabled, a state machine will
//               cease executing instructions, except those written directly to
//               SMx_INSTR by the system. Multiple bits can be set/cleared at
//               once to run/halt multiple state machines simultaneously.
#define PIO_CTRL_SM_ENABLE_RESET  _u(0x0)
#define PIO_CTRL_SM_ENABLE_BITS   _u(0x0000000f)
#define PIO_CTRL_SM_ENABLE_MSB    _u(3)
#define PIO_CTRL_SM_ENABLE_LSB    _u(0)
#define PIO_CTRL_SM_ENABLE_ACCESS "RW"
// =============================================================================
// Register    : PIO_FSTAT
// Description : FIFO status register
#define PIO_FSTAT_OFFSET _u(0x00000004)
#define PIO_FSTAT_BITS   _u(0x0f0f0f0f)
#define PIO_FSTAT_RESET  _u(0x0f000f00)
// -----------------------------------------------------------------------------
// Field       : PIO_FSTAT_TXEMPTY
// Description : State machine TX FIFO is empty
#define PIO_FSTAT_TXEMPTY_RESET  _u(0xf)
#define PIO_FSTAT_TXEMPTY_BITS   _u(0x0f000000)
#define PIO_FSTAT_TXEMPTY_MSB    _u(27)
#define PIO_FSTAT_TXEMPTY_LSB    _u(24)
#define PIO_FSTAT_TXEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FSTAT_TXFULL
// Description : State machine TX FIFO is full
#define PIO_FSTAT_TXFULL_RESET  _u(0x0)
#define PIO_FSTAT_TXFULL_BITS   _u(0x000f0000)
#define PIO_FSTAT_TXFULL_MSB    _u(19)
#define PIO_FSTAT_TXFULL_LSB    _u(16)
#define PIO_FSTAT_TXFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FSTAT_RXEMPTY
// Description : State machine RX FIFO is empty
#define PIO_FSTAT_RXEMPTY_RESET  _u(0xf)
#define PIO_FSTAT_RXEMPTY_BITS   _u(0x00000f00)
#define PIO_FSTAT_RXEMPTY_MSB    _u(11)
#define PIO_FSTAT_RXEMPTY_LSB    _u(8)
#define PIO_FSTAT_RXEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FSTAT_RXFULL
// Description : State machine RX FIFO is full
#define PIO_FSTAT_RXFULL_RESET  _u(0x0)
#define PIO_FSTAT_RXFULL_BITS   _u(0x0000000f)
#define PIO_FSTAT_RXFULL_MSB    _u(3)
#define PIO_FSTAT_RXFULL_LSB    _u(0)
#define PIO_FSTAT_RXFULL_ACCESS "RO"
// =============================================================================
// Register    : PIO_FDEBUG
// Description : FIFO debug register
#define PIO_FDEBUG_OFFSET _u(0x00000008)
#define PIO_FDEBUG_BITS   _u(0x0f0f0f0f)
#define PIO_FDEBUG_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_FDEBUG_TXSTALL
// Description : State machine has stalled on empty TX FIFO during a blocking
//               PULL, or an OUT with autopull enabled. Write 1 to clear.
#define PIO_FDEBUG_TXSTALL_RESET  _u(0x0)
#define PIO_FDEBUG_TXSTALL_BITS   _u(0x0f000000)
#define PIO_FDEBUG_TXSTALL_MSB    _u(27)
#define PIO_FDEBUG_TXSTALL_LSB    _u(24)
#define PIO_FDEBUG_TXSTALL_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : PIO_FDEBUG_TXOVER
// Description : TX FIFO overflow (i.e. write-on-full by the system) has
//               occurred. Write 1 to clear. Note that write-on-full does not
//               alter the state or contents of the FIFO in any way, but the
//               data that the system attempted to write is dropped, so if this
//               flag is set, your software has quite likely dropped some data
//               on the floor.
#define PIO_FDEBUG_TXOVER_RESET  _u(0x0)
#define PIO_FDEBUG_TXOVER_BITS   _u(0x000f0000)
#define PIO_FDEBUG_TXOVER_MSB    _u(19)
#define PIO_FDEBUG_TXOVER_LSB    _u(16)
#define PIO_FDEBUG_TXOVER_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : PIO_FDEBUG_RXUNDER
// Description : RX FIFO underflow (i.e. read-on-empty by the system) has
//               occurred. Write 1 to clear. Note that read-on-empty does not
//               perturb the state of the FIFO in any way, but the data returned
//               by reading from an empty FIFO is undefined, so this flag
//               generally only becomes set due to some kind of software error.
#define PIO_FDEBUG_RXUNDER_RESET  _u(0x0)
#define PIO_FDEBUG_RXUNDER_BITS   _u(0x00000f00)
#define PIO_FDEBUG_RXUNDER_MSB    _u(11)
#define PIO_FDEBUG_RXUNDER_LSB    _u(8)
#define PIO_FDEBUG_RXUNDER_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : PIO_FDEBUG_RXSTALL
// Description : State machine has stalled on full RX FIFO during a blocking
//               PUSH, or an IN with autopush enabled. This flag is also set
//               when a nonblocking PUSH to a full FIFO took place, in which
//               case the state machine has dropped data. Write 1 to clear.
#define PIO_FDEBUG_RXSTALL_RESET  _u(0x0)
#define PIO_FDEBUG_RXSTALL_BITS   _u(0x0000000f)
#define PIO_FDEBUG_RXSTALL_MSB    _u(3)
#define PIO_FDEBUG_RXSTALL_LSB    _u(0)
#define PIO_FDEBUG_RXSTALL_ACCESS "WC"
// =============================================================================
// Register    : PIO_FLEVEL
// Description : FIFO levels
#define PIO_FLEVEL_OFFSET _u(0x0000000c)
#define PIO_FLEVEL_BITS   _u(0xffffffff)
#define PIO_FLEVEL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_RX3
// Description : None
#define PIO_FLEVEL_RX3_RESET  _u(0x0)
#define PIO_FLEVEL_RX3_BITS   _u(0xf0000000)
#define PIO_FLEVEL_RX3_MSB    _u(31)
#define PIO_FLEVEL_RX3_LSB    _u(28)
#define PIO_FLEVEL_RX3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_TX3
// Description : None
#define PIO_FLEVEL_TX3_RESET  _u(0x0)
#define PIO_FLEVEL_TX3_BITS   _u(0x0f000000)
#define PIO_FLEVEL_TX3_MSB    _u(27)
#define PIO_FLEVEL_TX3_LSB    _u(24)
#define PIO_FLEVEL_TX3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_RX2
// Description : None
#define PIO_FLEVEL_RX2_RESET  _u(0x0)
#define PIO_FLEVEL_RX2_BITS   _u(0x00f00000)
#define PIO_FLEVEL_RX2_MSB    _u(23)
#define PIO_FLEVEL_RX2_LSB    _u(20)
#define PIO_FLEVEL_RX2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_TX2
// Description : None
#define PIO_FLEVEL_TX2_RESET  _u(0x0)
#define PIO_FLEVEL_TX2_BITS   _u(0x000f0000)
#define PIO_FLEVEL_TX2_MSB    _u(19)
#define PIO_FLEVEL_TX2_LSB    _u(16)
#define PIO_FLEVEL_TX2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_RX1
// Description : None
#define PIO_FLEVEL_RX1_RESET  _u(0x0)
#define PIO_FLEVEL_RX1_BITS   _u(0x0000f000)
#define PIO_FLEVEL_RX1_MSB    _u(15)
#define PIO_FLEVEL_RX1_LSB    _u(12)
#define PIO_FLEVEL_RX1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_TX1
// Description : None
#define PIO_FLEVEL_TX1_RESET  _u(0x0)
#define PIO_FLEVEL_TX1_BITS   _u(0x00000f00)
#define PIO_FLEVEL_TX1_MSB    _u(11)
#define PIO_FLEVEL_TX1_LSB    _u(8)
#define PIO_FLEVEL_TX1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_RX0
// Description : None
#define PIO_FLEVEL_RX0_RESET  _u(0x0)
#define PIO_FLEVEL_RX0_BITS   _u(0x000000f0)
#define PIO_FLEVEL_RX0_MSB    _u(7)
#define PIO_FLEVEL_RX0_LSB    _u(4)
#define PIO_FLEVEL_RX0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_FLEVEL_TX0
// Description : None
#define PIO_FLEVEL_TX0_RESET  _u(0x0)
#define PIO_FLEVEL_TX0_BITS   _u(0x0000000f)
#define PIO_FLEVEL_TX0_MSB    _u(3)
#define PIO_FLEVEL_TX0_LSB    _u(0)
#define PIO_FLEVEL_TX0_ACCESS "RO"
// =============================================================================
// Register    : PIO_TXF0
// Description : Direct write access to the TX FIFO for this state machine. Each
//               write pushes one word to the FIFO. Attempting to write to a
//               full FIFO has no effect on the FIFO state or contents, and sets
//               the sticky FDEBUG_TXOVER error flag for this FIFO.
#define PIO_TXF0_OFFSET _u(0x00000010)
#define PIO_TXF0_BITS   _u(0xffffffff)
#define PIO_TXF0_RESET  _u(0x00000000)
#define PIO_TXF0_MSB    _u(31)
#define PIO_TXF0_LSB    _u(0)
#define PIO_TXF0_ACCESS "WF"
// =============================================================================
// Register    : PIO_TXF1
// Description : Direct write access to the TX FIFO for this state machine. Each
//               write pushes one word to the FIFO. Attempting to write to a
//               full FIFO has no effect on the FIFO state or contents, and sets
//               the sticky FDEBUG_TXOVER error flag for this FIFO.
#define PIO_TXF1_OFFSET _u(0x00000014)
#define PIO_TXF1_BITS   _u(0xffffffff)
#define PIO_TXF1_RESET  _u(0x00000000)
#define PIO_TXF1_MSB    _u(31)
#define PIO_TXF1_LSB    _u(0)
#define PIO_TXF1_ACCESS "WF"
// =============================================================================
// Register    : PIO_TXF2
// Description : Direct write access to the TX FIFO for this state machine. Each
//               write pushes one word to the FIFO. Attempting to write to a
//               full FIFO has no effect on the FIFO state or contents, and sets
//               the sticky FDEBUG_TXOVER error flag for this FIFO.
#define PIO_TXF2_OFFSET _u(0x00000018)
#define PIO_TXF2_BITS   _u(0xffffffff)
#define PIO_TXF2_RESET  _u(0x00000000)
#define PIO_TXF2_MSB    _u(31)
#define PIO_TXF2_LSB    _u(0)
#define PIO_TXF2_ACCESS "WF"
// =============================================================================
// Register    : PIO_TXF3
// Description : Direct write access to the TX FIFO for this state machine. Each
//               write pushes one word to the FIFO. Attempting to write to a
//               full FIFO has no effect on the FIFO state or contents, and sets
//               the sticky FDEBUG_TXOVER error flag for this FIFO.
#define PIO_TXF3_OFFSET _u(0x0000001c)
#define PIO_TXF3_BITS   _u(0xffffffff)
#define PIO_TXF3_RESET  _u(0x00000000)
#define PIO_TXF3_MSB    _u(31)
#define PIO_TXF3_LSB    _u(0)
#define PIO_TXF3_ACCESS "WF"
// =============================================================================
// Register    : PIO_RXF0
// Description : Direct read access to the RX FIFO for this state machine. Each
//               read pops one word from the FIFO. Attempting to read from an
//               empty FIFO has no effect on the FIFO state, and sets the sticky
//               FDEBUG_RXUNDER error flag for this FIFO. The data returned to
//               the system on a read from an empty FIFO is undefined.
#define PIO_RXF0_OFFSET _u(0x00000020)
#define PIO_RXF0_BITS   _u(0xffffffff)
#define PIO_RXF0_RESET  "-"
#define PIO_RXF0_MSB    _u(31)
#define PIO_RXF0_LSB    _u(0)
#define PIO_RXF0_ACCESS "RF"
// =============================================================================
// Register    : PIO_RXF1
// Description : Direct read access to the RX FIFO for this state machine. Each
//               read pops one word from the FIFO. Attempting to read from an
//               empty FIFO has no effect on the FIFO state, and sets the sticky
//               FDEBUG_RXUNDER error flag for this FIFO. The data returned to
//               the system on a read from an empty FIFO is undefined.
#define PIO_RXF1_OFFSET _u(0x00000024)
#define PIO_RXF1_BITS   _u(0xffffffff)
#define PIO_RXF1_RESET  "-"
#define PIO_RXF1_MSB    _u(31)
#define PIO_RXF1_LSB    _u(0)
#define PIO_RXF1_ACCESS "RF"
// =============================================================================
// Register    : PIO_RXF2
// Description : Direct read access to the RX FIFO for this state machine. Each
//               read pops one word from the FIFO. Attempting to read from an
//               empty FIFO has no effect on the FIFO state, and sets the sticky
//               FDEBUG_RXUNDER error flag for this FIFO. The data returned to
//               the system on a read from an empty FIFO is undefined.
#define PIO_RXF2_OFFSET _u(0x00000028)
#define PIO_RXF2_BITS   _u(0xffffffff)
#define PIO_RXF2_RESET  "-"
#define PIO_RXF2_MSB    _u(31)
#define PIO_RXF2_LSB    _u(0)
#define PIO_RXF2_ACCESS "RF"
// =============================================================================
// Register    : PIO_RXF3
// Description : Direct read access to the RX FIFO for this state machine. Each
//               read pops one word from the FIFO. Attempting to read from an
//               empty FIFO has no effect on the FIFO state, and sets the sticky
//               FDEBUG_RXUNDER error flag for this FIFO. The data returned to
//               the system on a read from an empty FIFO is undefined.
#define PIO_RXF3_OFFSET _u(0x0000002c)
#define PIO_RXF3_BITS   _u(0xffffffff)
#define PIO_RXF3_RESET  "-"
#define PIO_RXF3_MSB    _u(31)
#define PIO_RXF3_LSB    _u(0)
#define PIO_RXF3_ACCESS "RF"
// =============================================================================
// Register    : PIO_IRQ
// Description : State machine IRQ flags register. Write 1 to clear. There are 8
//               state machine IRQ flags, which can be set, cleared, and waited
//               on by the state machines. There's no fixed association between
//               flags and state machines -- any state machine can use any flag.
//
//               Any of the 8 flags can be used for timing synchronisation
//               between state machines, using IRQ and WAIT instructions. The
//               lower four of these flags are also routed out to system-level
//               interrupt requests, alongside FIFO status interrupts -- see
//               e.g. IRQ0_INTE.
#define PIO_IRQ_OFFSET _u(0x00000030)
#define PIO_IRQ_BITS   _u(0x000000ff)
#define PIO_IRQ_RESET  _u(0x00000000)
#define PIO_IRQ_MSB    _u(7)
#define PIO_IRQ_LSB    _u(0)
#define PIO_IRQ_ACCESS "WC"
// =============================================================================
// Register    : PIO_IRQ_FORCE
// Description : Writing a 1 to each of these bits will forcibly assert the
//               corresponding IRQ. Note this is different to the INTF register:
//               writing here affects PIO internal state. INTF just asserts the
//               processor-facing IRQ signal for testing ISRs, and is not
//               visible to the state machines.
#define PIO_IRQ_FORCE_OFFSET _u(0x00000034)
#define PIO_IRQ_FORCE_BITS   _u(0x000000ff)
#define PIO_IRQ_FORCE_RESET  _u(0x00000000)
#define PIO_IRQ_FORCE_MSB    _u(7)
#define PIO_IRQ_FORCE_LSB    _u(0)
#define PIO_IRQ_FORCE_ACCESS "WF"
// =============================================================================
// Register    : PIO_INPUT_SYNC_BYPASS
// Description : There is a 2-flipflop synchronizer on each GPIO input, which
//               protects PIO logic from metastabilities. This increases input
//               delay, and for fast synchronous IO (e.g. SPI) these
//               synchronizers may need to be bypassed. Each bit in this
//               register corresponds to one GPIO.
//               0 -> input is synchronized (default)
//               1 -> synchronizer is bypassed
//               If in doubt, leave this register as all zeroes.
#define PIO_INPUT_SYNC_BYPASS_OFFSET _u(0x00000038)
#define PIO_INPUT_SYNC_BYPASS_BITS   _u(0xffffffff)
#define PIO_INPUT_SYNC_BYPASS_RESET  _u(0x00000000)
#define PIO_INPUT_SYNC_BYPASS_MSB    _u(31)
#define PIO_INPUT_SYNC_BYPASS_LSB    _u(0)
#define PIO_INPUT_SYNC_BYPASS_ACCESS "RW"
// =============================================================================
// Register    : PIO_DBG_PADOUT
// Description : Read to sample the pad output values PIO is currently driving
//               to the GPIOs. On RP2040 there are 30 GPIOs, so the two most
//               significant bits are hardwired to 0.
#define PIO_DBG_PADOUT_OFFSET _u(0x0000003c)
#define PIO_DBG_PADOUT_BITS   _u(0xffffffff)
#define PIO_DBG_PADOUT_RESET  _u(0x00000000)
#define PIO_DBG_PADOUT_MSB    _u(31)
#define PIO_DBG_PADOUT_LSB    _u(0)
#define PIO_DBG_PADOUT_ACCESS "RO"
// =============================================================================
// Register    : PIO_DBG_PADOE
// Description : Read to sample the pad output enables (direction) PIO is
//               currently driving to the GPIOs. On RP2040 there are 30 GPIOs,
//               so the two most significant bits are hardwired to 0.
#define PIO_DBG_PADOE_OFFSET _u(0x00000040)
#define PIO_DBG_PADOE_BITS   _u(0xffffffff)
#define PIO_DBG_PADOE_RESET  _u(0x00000000)
#define PIO_DBG_PADOE_MSB    _u(31)
#define PIO_DBG_PADOE_LSB    _u(0)
#define PIO_DBG_PADOE_ACCESS "RO"
// =============================================================================
// Register    : PIO_DBG_CFGINFO
// Description : The PIO hardware has some free parameters that may vary between
//               chip products.
//               These should be provided in the chip datasheet, but are also
//               exposed here.
#define PIO_DBG_CFGINFO_OFFSET _u(0x00000044)
#define PIO_DBG_CFGINFO_BITS   _u(0x003f0f3f)
#define PIO_DBG_CFGINFO_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_DBG_CFGINFO_IMEM_SIZE
// Description : The size of the instruction memory, measured in units of one
//               instruction
#define PIO_DBG_CFGINFO_IMEM_SIZE_RESET  "-"
#define PIO_DBG_CFGINFO_IMEM_SIZE_BITS   _u(0x003f0000)
#define PIO_DBG_CFGINFO_IMEM_SIZE_MSB    _u(21)
#define PIO_DBG_CFGINFO_IMEM_SIZE_LSB    _u(16)
#define PIO_DBG_CFGINFO_IMEM_SIZE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_DBG_CFGINFO_SM_COUNT
// Description : The number of state machines this PIO instance is equipped
//               with.
#define PIO_DBG_CFGINFO_SM_COUNT_RESET  "-"
#define PIO_DBG_CFGINFO_SM_COUNT_BITS   _u(0x00000f00)
#define PIO_DBG_CFGINFO_SM_COUNT_MSB    _u(11)
#define PIO_DBG_CFGINFO_SM_COUNT_LSB    _u(8)
#define PIO_DBG_CFGINFO_SM_COUNT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_DBG_CFGINFO_FIFO_DEPTH
// Description : The depth of the state machine TX/RX FIFOs, measured in words.
//               Joining fifos via SHIFTCTRL_FJOIN gives one FIFO with double
//               this depth.
#define PIO_DBG_CFGINFO_FIFO_DEPTH_RESET  "-"
#define PIO_DBG_CFGINFO_FIFO_DEPTH_BITS   _u(0x0000003f)
#define PIO_DBG_CFGINFO_FIFO_DEPTH_MSB    _u(5)
#define PIO_DBG_CFGINFO_FIFO_DEPTH_LSB    _u(0)
#define PIO_DBG_CFGINFO_FIFO_DEPTH_ACCESS "RO"
// =============================================================================
// Register    : PIO_INSTR_MEM0
// Description : Write-only access to instruction memory location 0
#define PIO_INSTR_MEM0_OFFSET _u(0x00000048)
#define PIO_INSTR_MEM0_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM0_RESET  _u(0x00000000)
#define PIO_INSTR_MEM0_MSB    _u(15)
#define PIO_INSTR_MEM0_LSB    _u(0)
#define PIO_INSTR_MEM0_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM1
// Description : Write-only access to instruction memory location 1
#define PIO_INSTR_MEM1_OFFSET _u(0x0000004c)
#define PIO_INSTR_MEM1_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM1_RESET  _u(0x00000000)
#define PIO_INSTR_MEM1_MSB    _u(15)
#define PIO_INSTR_MEM1_LSB    _u(0)
#define PIO_INSTR_MEM1_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM2
// Description : Write-only access to instruction memory location 2
#define PIO_INSTR_MEM2_OFFSET _u(0x00000050)
#define PIO_INSTR_MEM2_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM2_RESET  _u(0x00000000)
#define PIO_INSTR_MEM2_MSB    _u(15)
#define PIO_INSTR_MEM2_LSB    _u(0)
#define PIO_INSTR_MEM2_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM3
// Description : Write-only access to instruction memory location 3
#define PIO_INSTR_MEM3_OFFSET _u(0x00000054)
#define PIO_INSTR_MEM3_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM3_RESET  _u(0x00000000)
#define PIO_INSTR_MEM3_MSB    _u(15)
#define PIO_INSTR_MEM3_LSB    _u(0)
#define PIO_INSTR_MEM3_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM4
// Description : Write-only access to instruction memory location 4
#define PIO_INSTR_MEM4_OFFSET _u(0x00000058)
#define PIO_INSTR_MEM4_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM4_RESET  _u(0x00000000)
#define PIO_INSTR_MEM4_MSB    _u(15)
#define PIO_INSTR_MEM4_LSB    _u(0)
#define PIO_INSTR_MEM4_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM5
// Description : Write-only access to instruction memory location 5
#define PIO_INSTR_MEM5_OFFSET _u(0x0000005c)
#define PIO_INSTR_MEM5_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM5_RESET  _u(0x00000000)
#define PIO_INSTR_MEM5_MSB    _u(15)
#define PIO_INSTR_MEM5_LSB    _u(0)
#define PIO_INSTR_MEM5_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM6
// Description : Write-only access to instruction memory location 6
#define PIO_INSTR_MEM6_OFFSET _u(0x00000060)
#define PIO_INSTR_MEM6_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM6_RESET  _u(0x00000000)
#define PIO_INSTR_MEM6_MSB    _u(15)
#define PIO_INSTR_MEM6_LSB    _u(0)
#define PIO_INSTR_MEM6_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM7
// Description : Write-only access to instruction memory location 7
#define PIO_INSTR_MEM7_OFFSET _u(0x00000064)
#define PIO_INSTR_MEM7_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM7_RESET  _u(0x00000000)
#define PIO_INSTR_MEM7_MSB    _u(15)
#define PIO_INSTR_MEM7_LSB    _u(0)
#define PIO_INSTR_MEM7_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM8
// Description : Write-only access to instruction memory location 8
#define PIO_INSTR_MEM8_OFFSET _u(0x00000068)
#define PIO_INSTR_MEM8_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM8_RESET  _u(0x00000000)
#define PIO_INSTR_MEM8_MSB    _u(15)
#define PIO_INSTR_MEM8_LSB    _u(0)
#define PIO_INSTR_MEM8_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM9
// Description : Write-only access to instruction memory location 9
#define PIO_INSTR_MEM9_OFFSET _u(0x0000006c)
#define PIO_INSTR_MEM9_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM9_RESET  _u(0x00000000)
#define PIO_INSTR_MEM9_MSB    _u(15)
#define PIO_INSTR_MEM9_LSB    _u(0)
#define PIO_INSTR_MEM9_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM10
// Description : Write-only access to instruction memory location 10
#define PIO_INSTR_MEM10_OFFSET _u(0x00000070)
#define PIO_INSTR_MEM10_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM10_RESET  _u(0x00000000)
#define PIO_INSTR_MEM10_MSB    _u(15)
#define PIO_INSTR_MEM10_LSB    _u(0)
#define PIO_INSTR_MEM10_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM11
// Description : Write-only access to instruction memory location 11
#define PIO_INSTR_MEM11_OFFSET _u(0x00000074)
#define PIO_INSTR_MEM11_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM11_RESET  _u(0x00000000)
#define PIO_INSTR_MEM11_MSB    _u(15)
#define PIO_INSTR_MEM11_LSB    _u(0)
#define PIO_INSTR_MEM11_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM12
// Description : Write-only access to instruction memory location 12
#define PIO_INSTR_MEM12_OFFSET _u(0x00000078)
#define PIO_INSTR_MEM12_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM12_RESET  _u(0x00000000)
#define PIO_INSTR_MEM12_MSB    _u(15)
#define PIO_INSTR_MEM12_LSB    _u(0)
#define PIO_INSTR_MEM12_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM13
// Description : Write-only access to instruction memory location 13
#define PIO_INSTR_MEM13_OFFSET _u(0x0000007c)
#define PIO_INSTR_MEM13_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM13_RESET  _u(0x00000000)
#define PIO_INSTR_MEM13_MSB    _u(15)
#define PIO_INSTR_MEM13_LSB    _u(0)
#define PIO_INSTR_MEM13_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM14
// Description : Write-only access to instruction memory location 14
#define PIO_INSTR_MEM14_OFFSET _u(0x00000080)
#define PIO_INSTR_MEM14_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM14_RESET  _u(0x00000000)
#define PIO_INSTR_MEM14_MSB    _u(15)
#define PIO_INSTR_MEM14_LSB    _u(0)
#define PIO_INSTR_MEM14_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM15
// Description : Write-only access to instruction memory location 15
#define PIO_INSTR_MEM15_OFFSET _u(0x00000084)
#define PIO_INSTR_MEM15_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM15_RESET  _u(0x00000000)
#define PIO_INSTR_MEM15_MSB    _u(15)
#define PIO_INSTR_MEM15_LSB    _u(0)
#define PIO_INSTR_MEM15_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM16
// Description : Write-only access to instruction memory location 16
#define PIO_INSTR_MEM16_OFFSET _u(0x00000088)
#define PIO_INSTR_MEM16_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM16_RESET  _u(0x00000000)
#define PIO_INSTR_MEM16_MSB    _u(15)
#define PIO_INSTR_MEM16_LSB    _u(0)
#define PIO_INSTR_MEM16_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM17
// Description : Write-only access to instruction memory location 17
#define PIO_INSTR_MEM17_OFFSET _u(0x0000008c)
#define PIO_INSTR_MEM17_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM17_RESET  _u(0x00000000)
#define PIO_INSTR_MEM17_MSB    _u(15)
#define PIO_INSTR_MEM17_LSB    _u(0)
#define PIO_INSTR_MEM17_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM18
// Description : Write-only access to instruction memory location 18
#define PIO_INSTR_MEM18_OFFSET _u(0x00000090)
#define PIO_INSTR_MEM18_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM18_RESET  _u(0x00000000)
#define PIO_INSTR_MEM18_MSB    _u(15)
#define PIO_INSTR_MEM18_LSB    _u(0)
#define PIO_INSTR_MEM18_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM19
// Description : Write-only access to instruction memory location 19
#define PIO_INSTR_MEM19_OFFSET _u(0x00000094)
#define PIO_INSTR_MEM19_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM19_RESET  _u(0x00000000)
#define PIO_INSTR_MEM19_MSB    _u(15)
#define PIO_INSTR_MEM19_LSB    _u(0)
#define PIO_INSTR_MEM19_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM20
// Description : Write-only access to instruction memory location 20
#define PIO_INSTR_MEM20_OFFSET _u(0x00000098)
#define PIO_INSTR_MEM20_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM20_RESET  _u(0x00000000)
#define PIO_INSTR_MEM20_MSB    _u(15)
#define PIO_INSTR_MEM20_LSB    _u(0)
#define PIO_INSTR_MEM20_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM21
// Description : Write-only access to instruction memory location 21
#define PIO_INSTR_MEM21_OFFSET _u(0x0000009c)
#define PIO_INSTR_MEM21_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM21_RESET  _u(0x00000000)
#define PIO_INSTR_MEM21_MSB    _u(15)
#define PIO_INSTR_MEM21_LSB    _u(0)
#define PIO_INSTR_MEM21_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM22
// Description : Write-only access to instruction memory location 22
#define PIO_INSTR_MEM22_OFFSET _u(0x000000a0)
#define PIO_INSTR_MEM22_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM22_RESET  _u(0x00000000)
#define PIO_INSTR_MEM22_MSB    _u(15)
#define PIO_INSTR_MEM22_LSB    _u(0)
#define PIO_INSTR_MEM22_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM23
// Description : Write-only access to instruction memory location 23
#define PIO_INSTR_MEM23_OFFSET _u(0x000000a4)
#define PIO_INSTR_MEM23_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM23_RESET  _u(0x00000000)
#define PIO_INSTR_MEM23_MSB    _u(15)
#define PIO_INSTR_MEM23_LSB    _u(0)
#define PIO_INSTR_MEM23_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM24
// Description : Write-only access to instruction memory location 24
#define PIO_INSTR_MEM24_OFFSET _u(0x000000a8)
#define PIO_INSTR_MEM24_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM24_RESET  _u(0x00000000)
#define PIO_INSTR_MEM24_MSB    _u(15)
#define PIO_INSTR_MEM24_LSB    _u(0)
#define PIO_INSTR_MEM24_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM25
// Description : Write-only access to instruction memory location 25
#define PIO_INSTR_MEM25_OFFSET _u(0x000000ac)
#define PIO_INSTR_MEM25_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM25_RESET  _u(0x00000000)
#define PIO_INSTR_MEM25_MSB    _u(15)
#define PIO_INSTR_MEM25_LSB    _u(0)
#define PIO_INSTR_MEM25_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM26
// Description : Write-only access to instruction memory location 26
#define PIO_INSTR_MEM26_OFFSET _u(0x000000b0)
#define PIO_INSTR_MEM26_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM26_RESET  _u(0x00000000)
#define PIO_INSTR_MEM26_MSB    _u(15)
#define PIO_INSTR_MEM26_LSB    _u(0)
#define PIO_INSTR_MEM26_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM27
// Description : Write-only access to instruction memory location 27
#define PIO_INSTR_MEM27_OFFSET _u(0x000000b4)
#define PIO_INSTR_MEM27_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM27_RESET  _u(0x00000000)
#define PIO_INSTR_MEM27_MSB    _u(15)
#define PIO_INSTR_MEM27_LSB    _u(0)
#define PIO_INSTR_MEM27_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM28
// Description : Write-only access to instruction memory location 28
#define PIO_INSTR_MEM28_OFFSET _u(0x000000b8)
#define PIO_INSTR_MEM28_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM28_RESET  _u(0x00000000)
#define PIO_INSTR_MEM28_MSB    _u(15)
#define PIO_INSTR_MEM28_LSB    _u(0)
#define PIO_INSTR_MEM28_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM29
// Description : Write-only access to instruction memory location 29
#define PIO_INSTR_MEM29_OFFSET _u(0x000000bc)
#define PIO_INSTR_MEM29_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM29_RESET  _u(0x00000000)
#define PIO_INSTR_MEM29_MSB    _u(15)
#define PIO_INSTR_MEM29_LSB    _u(0)
#define PIO_INSTR_MEM29_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM30
// Description : Write-only access to instruction memory location 30
#define PIO_INSTR_MEM30_OFFSET _u(0x000000c0)
#define PIO_INSTR_MEM30_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM30_RESET  _u(0x00000000)
#define PIO_INSTR_MEM30_MSB    _u(15)
#define PIO_INSTR_MEM30_LSB    _u(0)
#define PIO_INSTR_MEM30_ACCESS "WO"
// =============================================================================
// Register    : PIO_INSTR_MEM31
// Description : Write-only access to instruction memory location 31
#define PIO_INSTR_MEM31_OFFSET _u(0x000000c4)
#define PIO_INSTR_MEM31_BITS   _u(0x0000ffff)
#define PIO_INSTR_MEM31_RESET  _u(0x00000000)
#define PIO_INSTR_MEM31_MSB    _u(15)
#define PIO_INSTR_MEM31_LSB    _u(0)
#define PIO_INSTR_MEM31_ACCESS "WO"
// =============================================================================
// Register    : PIO_SM0_CLKDIV
// Description : Clock divisor register for state machine 0
//               Frequency = clock freq / (CLKDIV_INT + CLKDIV_FRAC / 256)
#define PIO_SM0_CLKDIV_OFFSET _u(0x000000c8)
#define PIO_SM0_CLKDIV_BITS   _u(0xffffff00)
#define PIO_SM0_CLKDIV_RESET  _u(0x00010000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_CLKDIV_INT
// Description : Effective frequency is sysclk/(int + frac/256).
//               Value of 0 is interpreted as 65536. If INT is 0, FRAC must also
//               be 0.
#define PIO_SM0_CLKDIV_INT_RESET  _u(0x0001)
#define PIO_SM0_CLKDIV_INT_BITS   _u(0xffff0000)
#define PIO_SM0_CLKDIV_INT_MSB    _u(31)
#define PIO_SM0_CLKDIV_INT_LSB    _u(16)
#define PIO_SM0_CLKDIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_CLKDIV_FRAC
// Description : Fractional part of clock divisor
#define PIO_SM0_CLKDIV_FRAC_RESET  _u(0x00)
#define PIO_SM0_CLKDIV_FRAC_BITS   _u(0x0000ff00)
#define PIO_SM0_CLKDIV_FRAC_MSB    _u(15)
#define PIO_SM0_CLKDIV_FRAC_LSB    _u(8)
#define PIO_SM0_CLKDIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM0_EXECCTRL
// Description : Execution/behavioural settings for state machine 0
#define PIO_SM0_EXECCTRL_OFFSET _u(0x000000cc)
#define PIO_SM0_EXECCTRL_BITS   _u(0xffffff9f)
#define PIO_SM0_EXECCTRL_RESET  _u(0x0001f000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_EXEC_STALLED
// Description : If 1, an instruction written to SMx_INSTR is stalled, and
//               latched by the state machine. Will clear to 0 once this
//               instruction completes.
#define PIO_SM0_EXECCTRL_EXEC_STALLED_RESET  _u(0x0)
#define PIO_SM0_EXECCTRL_EXEC_STALLED_BITS   _u(0x80000000)
#define PIO_SM0_EXECCTRL_EXEC_STALLED_MSB    _u(31)
#define PIO_SM0_EXECCTRL_EXEC_STALLED_LSB    _u(31)
#define PIO_SM0_EXECCTRL_EXEC_STALLED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_SIDE_EN
// Description : If 1, the MSB of the Delay/Side-set instruction field is used
//               as side-set enable, rather than a side-set data bit. This
//               allows instructions to perform side-set optionally, rather than
//               on every instruction, but the maximum possible side-set width
//               is reduced from 5 to 4. Note that the value of
//               PINCTRL_SIDESET_COUNT is inclusive of this enable bit.
#define PIO_SM0_EXECCTRL_SIDE_EN_RESET  _u(0x0)
#define PIO_SM0_EXECCTRL_SIDE_EN_BITS   _u(0x40000000)
#define PIO_SM0_EXECCTRL_SIDE_EN_MSB    _u(30)
#define PIO_SM0_EXECCTRL_SIDE_EN_LSB    _u(30)
#define PIO_SM0_EXECCTRL_SIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_SIDE_PINDIR
// Description : If 1, side-set data is asserted to pin directions, instead of
//               pin values
#define PIO_SM0_EXECCTRL_SIDE_PINDIR_RESET  _u(0x0)
#define PIO_SM0_EXECCTRL_SIDE_PINDIR_BITS   _u(0x20000000)
#define PIO_SM0_EXECCTRL_SIDE_PINDIR_MSB    _u(29)
#define PIO_SM0_EXECCTRL_SIDE_PINDIR_LSB    _u(29)
#define PIO_SM0_EXECCTRL_SIDE_PINDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_JMP_PIN
// Description : The GPIO number to use as condition for JMP PIN. Unaffected by
//               input mapping.
#define PIO_SM0_EXECCTRL_JMP_PIN_RESET  _u(0x00)
#define PIO_SM0_EXECCTRL_JMP_PIN_BITS   _u(0x1f000000)
#define PIO_SM0_EXECCTRL_JMP_PIN_MSB    _u(28)
#define PIO_SM0_EXECCTRL_JMP_PIN_LSB    _u(24)
#define PIO_SM0_EXECCTRL_JMP_PIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_OUT_EN_SEL
// Description : Which data bit to use for inline OUT enable
#define PIO_SM0_EXECCTRL_OUT_EN_SEL_RESET  _u(0x00)
#define PIO_SM0_EXECCTRL_OUT_EN_SEL_BITS   _u(0x00f80000)
#define PIO_SM0_EXECCTRL_OUT_EN_SEL_MSB    _u(23)
#define PIO_SM0_EXECCTRL_OUT_EN_SEL_LSB    _u(19)
#define PIO_SM0_EXECCTRL_OUT_EN_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_INLINE_OUT_EN
// Description : If 1, use a bit of OUT data as an auxiliary write enable
//               When used in conjunction with OUT_STICKY, writes with an enable
//               of 0 will
//               deassert the latest pin write. This can create useful
//               masking/override behaviour
//               due to the priority ordering of state machine pin writes (SM0 <
//               SM1 < ...)
#define PIO_SM0_EXECCTRL_INLINE_OUT_EN_RESET  _u(0x0)
#define PIO_SM0_EXECCTRL_INLINE_OUT_EN_BITS   _u(0x00040000)
#define PIO_SM0_EXECCTRL_INLINE_OUT_EN_MSB    _u(18)
#define PIO_SM0_EXECCTRL_INLINE_OUT_EN_LSB    _u(18)
#define PIO_SM0_EXECCTRL_INLINE_OUT_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_OUT_STICKY
// Description : Continuously assert the most recent OUT/SET to the pins
#define PIO_SM0_EXECCTRL_OUT_STICKY_RESET  _u(0x0)
#define PIO_SM0_EXECCTRL_OUT_STICKY_BITS   _u(0x00020000)
#define PIO_SM0_EXECCTRL_OUT_STICKY_MSB    _u(17)
#define PIO_SM0_EXECCTRL_OUT_STICKY_LSB    _u(17)
#define PIO_SM0_EXECCTRL_OUT_STICKY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_WRAP_TOP
// Description : After reaching this address, execution is wrapped to
//               wrap_bottom.
//               If the instruction is a jump, and the jump condition is true,
//               the jump takes priority.
#define PIO_SM0_EXECCTRL_WRAP_TOP_RESET  _u(0x1f)
#define PIO_SM0_EXECCTRL_WRAP_TOP_BITS   _u(0x0001f000)
#define PIO_SM0_EXECCTRL_WRAP_TOP_MSB    _u(16)
#define PIO_SM0_EXECCTRL_WRAP_TOP_LSB    _u(12)
#define PIO_SM0_EXECCTRL_WRAP_TOP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_WRAP_BOTTOM
// Description : After reaching wrap_top, execution is wrapped to this address.
#define PIO_SM0_EXECCTRL_WRAP_BOTTOM_RESET  _u(0x00)
#define PIO_SM0_EXECCTRL_WRAP_BOTTOM_BITS   _u(0x00000f80)
#define PIO_SM0_EXECCTRL_WRAP_BOTTOM_MSB    _u(11)
#define PIO_SM0_EXECCTRL_WRAP_BOTTOM_LSB    _u(7)
#define PIO_SM0_EXECCTRL_WRAP_BOTTOM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_STATUS_SEL
// Description : Comparison used for the MOV x, STATUS instruction.
//               0x0 -> All-ones if TX FIFO level < N, otherwise all-zeroes
//               0x1 -> All-ones if RX FIFO level < N, otherwise all-zeroes
#define PIO_SM0_EXECCTRL_STATUS_SEL_RESET         _u(0x0)
#define PIO_SM0_EXECCTRL_STATUS_SEL_BITS          _u(0x00000010)
#define PIO_SM0_EXECCTRL_STATUS_SEL_MSB           _u(4)
#define PIO_SM0_EXECCTRL_STATUS_SEL_LSB           _u(4)
#define PIO_SM0_EXECCTRL_STATUS_SEL_ACCESS        "RW"
#define PIO_SM0_EXECCTRL_STATUS_SEL_VALUE_TXLEVEL _u(0x0)
#define PIO_SM0_EXECCTRL_STATUS_SEL_VALUE_RXLEVEL _u(0x1)
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_EXECCTRL_STATUS_N
// Description : Comparison level for the MOV x, STATUS instruction
#define PIO_SM0_EXECCTRL_STATUS_N_RESET  _u(0x0)
#define PIO_SM0_EXECCTRL_STATUS_N_BITS   _u(0x0000000f)
#define PIO_SM0_EXECCTRL_STATUS_N_MSB    _u(3)
#define PIO_SM0_EXECCTRL_STATUS_N_LSB    _u(0)
#define PIO_SM0_EXECCTRL_STATUS_N_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM0_SHIFTCTRL
// Description : Control behaviour of the input/output shift registers for state
//               machine 0
#define PIO_SM0_SHIFTCTRL_OFFSET _u(0x000000d0)
#define PIO_SM0_SHIFTCTRL_BITS   _u(0xffff0000)
#define PIO_SM0_SHIFTCTRL_RESET  _u(0x000c0000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_FJOIN_RX
// Description : When 1, RX FIFO steals the TX FIFO's storage, and becomes twice
//               as deep.
//               TX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM0_SHIFTCTRL_FJOIN_RX_RESET  _u(0x0)
#define PIO_SM0_SHIFTCTRL_FJOIN_RX_BITS   _u(0x80000000)
#define PIO_SM0_SHIFTCTRL_FJOIN_RX_MSB    _u(31)
#define PIO_SM0_SHIFTCTRL_FJOIN_RX_LSB    _u(31)
#define PIO_SM0_SHIFTCTRL_FJOIN_RX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_FJOIN_TX
// Description : When 1, TX FIFO steals the RX FIFO's storage, and becomes twice
//               as deep.
//               RX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM0_SHIFTCTRL_FJOIN_TX_RESET  _u(0x0)
#define PIO_SM0_SHIFTCTRL_FJOIN_TX_BITS   _u(0x40000000)
#define PIO_SM0_SHIFTCTRL_FJOIN_TX_MSB    _u(30)
#define PIO_SM0_SHIFTCTRL_FJOIN_TX_LSB    _u(30)
#define PIO_SM0_SHIFTCTRL_FJOIN_TX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_PULL_THRESH
// Description : Number of bits shifted out of OSR before autopull, or
//               conditional pull (PULL IFEMPTY), will take place.
//               Write 0 for value of 32.
#define PIO_SM0_SHIFTCTRL_PULL_THRESH_RESET  _u(0x00)
#define PIO_SM0_SHIFTCTRL_PULL_THRESH_BITS   _u(0x3e000000)
#define PIO_SM0_SHIFTCTRL_PULL_THRESH_MSB    _u(29)
#define PIO_SM0_SHIFTCTRL_PULL_THRESH_LSB    _u(25)
#define PIO_SM0_SHIFTCTRL_PULL_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_PUSH_THRESH
// Description : Number of bits shifted into ISR before autopush, or conditional
//               push (PUSH IFFULL), will take place.
//               Write 0 for value of 32.
#define PIO_SM0_SHIFTCTRL_PUSH_THRESH_RESET  _u(0x00)
#define PIO_SM0_SHIFTCTRL_PUSH_THRESH_BITS   _u(0x01f00000)
#define PIO_SM0_SHIFTCTRL_PUSH_THRESH_MSB    _u(24)
#define PIO_SM0_SHIFTCTRL_PUSH_THRESH_LSB    _u(20)
#define PIO_SM0_SHIFTCTRL_PUSH_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR
// Description : 1 = shift out of output shift register to right. 0 = to left.
#define PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_RESET  _u(0x1)
#define PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_BITS   _u(0x00080000)
#define PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_MSB    _u(19)
#define PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_LSB    _u(19)
#define PIO_SM0_SHIFTCTRL_OUT_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_IN_SHIFTDIR
// Description : 1 = shift input shift register to right (data enters from
//               left). 0 = to left.
#define PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_RESET  _u(0x1)
#define PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_BITS   _u(0x00040000)
#define PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_MSB    _u(18)
#define PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_LSB    _u(18)
#define PIO_SM0_SHIFTCTRL_IN_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_AUTOPULL
// Description : Pull automatically when the output shift register is emptied,
//               i.e. on or following an OUT instruction which causes the output
//               shift counter to reach or exceed PULL_THRESH.
#define PIO_SM0_SHIFTCTRL_AUTOPULL_RESET  _u(0x0)
#define PIO_SM0_SHIFTCTRL_AUTOPULL_BITS   _u(0x00020000)
#define PIO_SM0_SHIFTCTRL_AUTOPULL_MSB    _u(17)
#define PIO_SM0_SHIFTCTRL_AUTOPULL_LSB    _u(17)
#define PIO_SM0_SHIFTCTRL_AUTOPULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_SHIFTCTRL_AUTOPUSH
// Description : Push automatically when the input shift register is filled,
//               i.e. on an IN instruction which causes the input shift counter
//               to reach or exceed PUSH_THRESH.
#define PIO_SM0_SHIFTCTRL_AUTOPUSH_RESET  _u(0x0)
#define PIO_SM0_SHIFTCTRL_AUTOPUSH_BITS   _u(0x00010000)
#define PIO_SM0_SHIFTCTRL_AUTOPUSH_MSB    _u(16)
#define PIO_SM0_SHIFTCTRL_AUTOPUSH_LSB    _u(16)
#define PIO_SM0_SHIFTCTRL_AUTOPUSH_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM0_ADDR
// Description : Current instruction address of state machine 0
#define PIO_SM0_ADDR_OFFSET _u(0x000000d4)
#define PIO_SM0_ADDR_BITS   _u(0x0000001f)
#define PIO_SM0_ADDR_RESET  _u(0x00000000)
#define PIO_SM0_ADDR_MSB    _u(4)
#define PIO_SM0_ADDR_LSB    _u(0)
#define PIO_SM0_ADDR_ACCESS "RO"
// =============================================================================
// Register    : PIO_SM0_INSTR
// Description : Read to see the instruction currently addressed by state
//               machine 0's program counter
//               Write to execute an instruction immediately (including jumps)
//               and then resume execution.
#define PIO_SM0_INSTR_OFFSET _u(0x000000d8)
#define PIO_SM0_INSTR_BITS   _u(0x0000ffff)
#define PIO_SM0_INSTR_RESET  "-"
#define PIO_SM0_INSTR_MSB    _u(15)
#define PIO_SM0_INSTR_LSB    _u(0)
#define PIO_SM0_INSTR_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM0_PINCTRL
// Description : State machine pin control
#define PIO_SM0_PINCTRL_OFFSET _u(0x000000dc)
#define PIO_SM0_PINCTRL_BITS   _u(0xffffffff)
#define PIO_SM0_PINCTRL_RESET  _u(0x14000000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_SIDESET_COUNT
// Description : The number of MSBs of the Delay/Side-set instruction field
//               which are used for side-set. Inclusive of the enable bit, if
//               present. Minimum of 0 (all delay bits, no side-set) and maximum
//               of 5 (all side-set, no delay).
#define PIO_SM0_PINCTRL_SIDESET_COUNT_RESET  _u(0x0)
#define PIO_SM0_PINCTRL_SIDESET_COUNT_BITS   _u(0xe0000000)
#define PIO_SM0_PINCTRL_SIDESET_COUNT_MSB    _u(31)
#define PIO_SM0_PINCTRL_SIDESET_COUNT_LSB    _u(29)
#define PIO_SM0_PINCTRL_SIDESET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_SET_COUNT
// Description : The number of pins asserted by a SET. In the range 0 to 5
//               inclusive.
#define PIO_SM0_PINCTRL_SET_COUNT_RESET  _u(0x5)
#define PIO_SM0_PINCTRL_SET_COUNT_BITS   _u(0x1c000000)
#define PIO_SM0_PINCTRL_SET_COUNT_MSB    _u(28)
#define PIO_SM0_PINCTRL_SET_COUNT_LSB    _u(26)
#define PIO_SM0_PINCTRL_SET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_OUT_COUNT
// Description : The number of pins asserted by an OUT PINS, OUT PINDIRS or MOV
//               PINS instruction. In the range 0 to 32 inclusive.
#define PIO_SM0_PINCTRL_OUT_COUNT_RESET  _u(0x00)
#define PIO_SM0_PINCTRL_OUT_COUNT_BITS   _u(0x03f00000)
#define PIO_SM0_PINCTRL_OUT_COUNT_MSB    _u(25)
#define PIO_SM0_PINCTRL_OUT_COUNT_LSB    _u(20)
#define PIO_SM0_PINCTRL_OUT_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_IN_BASE
// Description : The pin which is mapped to the least-significant bit of a state
//               machine's IN data bus. Higher-numbered pins are mapped to
//               consecutively more-significant data bits, with a modulo of 32
//               applied to pin number.
#define PIO_SM0_PINCTRL_IN_BASE_RESET  _u(0x00)
#define PIO_SM0_PINCTRL_IN_BASE_BITS   _u(0x000f8000)
#define PIO_SM0_PINCTRL_IN_BASE_MSB    _u(19)
#define PIO_SM0_PINCTRL_IN_BASE_LSB    _u(15)
#define PIO_SM0_PINCTRL_IN_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_SIDESET_BASE
// Description : The lowest-numbered pin that will be affected by a side-set
//               operation. The MSBs of an instruction's side-set/delay field
//               (up to 5, determined by SIDESET_COUNT) are used for side-set
//               data, with the remaining LSBs used for delay. The
//               least-significant bit of the side-set portion is the bit
//               written to this pin, with more-significant bits written to
//               higher-numbered pins.
#define PIO_SM0_PINCTRL_SIDESET_BASE_RESET  _u(0x00)
#define PIO_SM0_PINCTRL_SIDESET_BASE_BITS   _u(0x00007c00)
#define PIO_SM0_PINCTRL_SIDESET_BASE_MSB    _u(14)
#define PIO_SM0_PINCTRL_SIDESET_BASE_LSB    _u(10)
#define PIO_SM0_PINCTRL_SIDESET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_SET_BASE
// Description : The lowest-numbered pin that will be affected by a SET PINS or
//               SET PINDIRS instruction. The data written to this pin is the
//               least-significant bit of the SET data.
#define PIO_SM0_PINCTRL_SET_BASE_RESET  _u(0x00)
#define PIO_SM0_PINCTRL_SET_BASE_BITS   _u(0x000003e0)
#define PIO_SM0_PINCTRL_SET_BASE_MSB    _u(9)
#define PIO_SM0_PINCTRL_SET_BASE_LSB    _u(5)
#define PIO_SM0_PINCTRL_SET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM0_PINCTRL_OUT_BASE
// Description : The lowest-numbered pin that will be affected by an OUT PINS,
//               OUT PINDIRS or MOV PINS instruction. The data written to this
//               pin will always be the least-significant bit of the OUT or MOV
//               data.
#define PIO_SM0_PINCTRL_OUT_BASE_RESET  _u(0x00)
#define PIO_SM0_PINCTRL_OUT_BASE_BITS   _u(0x0000001f)
#define PIO_SM0_PINCTRL_OUT_BASE_MSB    _u(4)
#define PIO_SM0_PINCTRL_OUT_BASE_LSB    _u(0)
#define PIO_SM0_PINCTRL_OUT_BASE_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM1_CLKDIV
// Description : Clock divisor register for state machine 1
//               Frequency = clock freq / (CLKDIV_INT + CLKDIV_FRAC / 256)
#define PIO_SM1_CLKDIV_OFFSET _u(0x000000e0)
#define PIO_SM1_CLKDIV_BITS   _u(0xffffff00)
#define PIO_SM1_CLKDIV_RESET  _u(0x00010000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_CLKDIV_INT
// Description : Effective frequency is sysclk/(int + frac/256).
//               Value of 0 is interpreted as 65536. If INT is 0, FRAC must also
//               be 0.
#define PIO_SM1_CLKDIV_INT_RESET  _u(0x0001)
#define PIO_SM1_CLKDIV_INT_BITS   _u(0xffff0000)
#define PIO_SM1_CLKDIV_INT_MSB    _u(31)
#define PIO_SM1_CLKDIV_INT_LSB    _u(16)
#define PIO_SM1_CLKDIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_CLKDIV_FRAC
// Description : Fractional part of clock divisor
#define PIO_SM1_CLKDIV_FRAC_RESET  _u(0x00)
#define PIO_SM1_CLKDIV_FRAC_BITS   _u(0x0000ff00)
#define PIO_SM1_CLKDIV_FRAC_MSB    _u(15)
#define PIO_SM1_CLKDIV_FRAC_LSB    _u(8)
#define PIO_SM1_CLKDIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM1_EXECCTRL
// Description : Execution/behavioural settings for state machine 1
#define PIO_SM1_EXECCTRL_OFFSET _u(0x000000e4)
#define PIO_SM1_EXECCTRL_BITS   _u(0xffffff9f)
#define PIO_SM1_EXECCTRL_RESET  _u(0x0001f000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_EXEC_STALLED
// Description : If 1, an instruction written to SMx_INSTR is stalled, and
//               latched by the state machine. Will clear to 0 once this
//               instruction completes.
#define PIO_SM1_EXECCTRL_EXEC_STALLED_RESET  _u(0x0)
#define PIO_SM1_EXECCTRL_EXEC_STALLED_BITS   _u(0x80000000)
#define PIO_SM1_EXECCTRL_EXEC_STALLED_MSB    _u(31)
#define PIO_SM1_EXECCTRL_EXEC_STALLED_LSB    _u(31)
#define PIO_SM1_EXECCTRL_EXEC_STALLED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_SIDE_EN
// Description : If 1, the MSB of the Delay/Side-set instruction field is used
//               as side-set enable, rather than a side-set data bit. This
//               allows instructions to perform side-set optionally, rather than
//               on every instruction, but the maximum possible side-set width
//               is reduced from 5 to 4. Note that the value of
//               PINCTRL_SIDESET_COUNT is inclusive of this enable bit.
#define PIO_SM1_EXECCTRL_SIDE_EN_RESET  _u(0x0)
#define PIO_SM1_EXECCTRL_SIDE_EN_BITS   _u(0x40000000)
#define PIO_SM1_EXECCTRL_SIDE_EN_MSB    _u(30)
#define PIO_SM1_EXECCTRL_SIDE_EN_LSB    _u(30)
#define PIO_SM1_EXECCTRL_SIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_SIDE_PINDIR
// Description : If 1, side-set data is asserted to pin directions, instead of
//               pin values
#define PIO_SM1_EXECCTRL_SIDE_PINDIR_RESET  _u(0x0)
#define PIO_SM1_EXECCTRL_SIDE_PINDIR_BITS   _u(0x20000000)
#define PIO_SM1_EXECCTRL_SIDE_PINDIR_MSB    _u(29)
#define PIO_SM1_EXECCTRL_SIDE_PINDIR_LSB    _u(29)
#define PIO_SM1_EXECCTRL_SIDE_PINDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_JMP_PIN
// Description : The GPIO number to use as condition for JMP PIN. Unaffected by
//               input mapping.
#define PIO_SM1_EXECCTRL_JMP_PIN_RESET  _u(0x00)
#define PIO_SM1_EXECCTRL_JMP_PIN_BITS   _u(0x1f000000)
#define PIO_SM1_EXECCTRL_JMP_PIN_MSB    _u(28)
#define PIO_SM1_EXECCTRL_JMP_PIN_LSB    _u(24)
#define PIO_SM1_EXECCTRL_JMP_PIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_OUT_EN_SEL
// Description : Which data bit to use for inline OUT enable
#define PIO_SM1_EXECCTRL_OUT_EN_SEL_RESET  _u(0x00)
#define PIO_SM1_EXECCTRL_OUT_EN_SEL_BITS   _u(0x00f80000)
#define PIO_SM1_EXECCTRL_OUT_EN_SEL_MSB    _u(23)
#define PIO_SM1_EXECCTRL_OUT_EN_SEL_LSB    _u(19)
#define PIO_SM1_EXECCTRL_OUT_EN_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_INLINE_OUT_EN
// Description : If 1, use a bit of OUT data as an auxiliary write enable
//               When used in conjunction with OUT_STICKY, writes with an enable
//               of 0 will
//               deassert the latest pin write. This can create useful
//               masking/override behaviour
//               due to the priority ordering of state machine pin writes (SM0 <
//               SM1 < ...)
#define PIO_SM1_EXECCTRL_INLINE_OUT_EN_RESET  _u(0x0)
#define PIO_SM1_EXECCTRL_INLINE_OUT_EN_BITS   _u(0x00040000)
#define PIO_SM1_EXECCTRL_INLINE_OUT_EN_MSB    _u(18)
#define PIO_SM1_EXECCTRL_INLINE_OUT_EN_LSB    _u(18)
#define PIO_SM1_EXECCTRL_INLINE_OUT_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_OUT_STICKY
// Description : Continuously assert the most recent OUT/SET to the pins
#define PIO_SM1_EXECCTRL_OUT_STICKY_RESET  _u(0x0)
#define PIO_SM1_EXECCTRL_OUT_STICKY_BITS   _u(0x00020000)
#define PIO_SM1_EXECCTRL_OUT_STICKY_MSB    _u(17)
#define PIO_SM1_EXECCTRL_OUT_STICKY_LSB    _u(17)
#define PIO_SM1_EXECCTRL_OUT_STICKY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_WRAP_TOP
// Description : After reaching this address, execution is wrapped to
//               wrap_bottom.
//               If the instruction is a jump, and the jump condition is true,
//               the jump takes priority.
#define PIO_SM1_EXECCTRL_WRAP_TOP_RESET  _u(0x1f)
#define PIO_SM1_EXECCTRL_WRAP_TOP_BITS   _u(0x0001f000)
#define PIO_SM1_EXECCTRL_WRAP_TOP_MSB    _u(16)
#define PIO_SM1_EXECCTRL_WRAP_TOP_LSB    _u(12)
#define PIO_SM1_EXECCTRL_WRAP_TOP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_WRAP_BOTTOM
// Description : After reaching wrap_top, execution is wrapped to this address.
#define PIO_SM1_EXECCTRL_WRAP_BOTTOM_RESET  _u(0x00)
#define PIO_SM1_EXECCTRL_WRAP_BOTTOM_BITS   _u(0x00000f80)
#define PIO_SM1_EXECCTRL_WRAP_BOTTOM_MSB    _u(11)
#define PIO_SM1_EXECCTRL_WRAP_BOTTOM_LSB    _u(7)
#define PIO_SM1_EXECCTRL_WRAP_BOTTOM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_STATUS_SEL
// Description : Comparison used for the MOV x, STATUS instruction.
//               0x0 -> All-ones if TX FIFO level < N, otherwise all-zeroes
//               0x1 -> All-ones if RX FIFO level < N, otherwise all-zeroes
#define PIO_SM1_EXECCTRL_STATUS_SEL_RESET         _u(0x0)
#define PIO_SM1_EXECCTRL_STATUS_SEL_BITS          _u(0x00000010)
#define PIO_SM1_EXECCTRL_STATUS_SEL_MSB           _u(4)
#define PIO_SM1_EXECCTRL_STATUS_SEL_LSB           _u(4)
#define PIO_SM1_EXECCTRL_STATUS_SEL_ACCESS        "RW"
#define PIO_SM1_EXECCTRL_STATUS_SEL_VALUE_TXLEVEL _u(0x0)
#define PIO_SM1_EXECCTRL_STATUS_SEL_VALUE_RXLEVEL _u(0x1)
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_EXECCTRL_STATUS_N
// Description : Comparison level for the MOV x, STATUS instruction
#define PIO_SM1_EXECCTRL_STATUS_N_RESET  _u(0x0)
#define PIO_SM1_EXECCTRL_STATUS_N_BITS   _u(0x0000000f)
#define PIO_SM1_EXECCTRL_STATUS_N_MSB    _u(3)
#define PIO_SM1_EXECCTRL_STATUS_N_LSB    _u(0)
#define PIO_SM1_EXECCTRL_STATUS_N_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM1_SHIFTCTRL
// Description : Control behaviour of the input/output shift registers for state
//               machine 1
#define PIO_SM1_SHIFTCTRL_OFFSET _u(0x000000e8)
#define PIO_SM1_SHIFTCTRL_BITS   _u(0xffff0000)
#define PIO_SM1_SHIFTCTRL_RESET  _u(0x000c0000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_FJOIN_RX
// Description : When 1, RX FIFO steals the TX FIFO's storage, and becomes twice
//               as deep.
//               TX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM1_SHIFTCTRL_FJOIN_RX_RESET  _u(0x0)
#define PIO_SM1_SHIFTCTRL_FJOIN_RX_BITS   _u(0x80000000)
#define PIO_SM1_SHIFTCTRL_FJOIN_RX_MSB    _u(31)
#define PIO_SM1_SHIFTCTRL_FJOIN_RX_LSB    _u(31)
#define PIO_SM1_SHIFTCTRL_FJOIN_RX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_FJOIN_TX
// Description : When 1, TX FIFO steals the RX FIFO's storage, and becomes twice
//               as deep.
//               RX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM1_SHIFTCTRL_FJOIN_TX_RESET  _u(0x0)
#define PIO_SM1_SHIFTCTRL_FJOIN_TX_BITS   _u(0x40000000)
#define PIO_SM1_SHIFTCTRL_FJOIN_TX_MSB    _u(30)
#define PIO_SM1_SHIFTCTRL_FJOIN_TX_LSB    _u(30)
#define PIO_SM1_SHIFTCTRL_FJOIN_TX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_PULL_THRESH
// Description : Number of bits shifted out of OSR before autopull, or
//               conditional pull (PULL IFEMPTY), will take place.
//               Write 0 for value of 32.
#define PIO_SM1_SHIFTCTRL_PULL_THRESH_RESET  _u(0x00)
#define PIO_SM1_SHIFTCTRL_PULL_THRESH_BITS   _u(0x3e000000)
#define PIO_SM1_SHIFTCTRL_PULL_THRESH_MSB    _u(29)
#define PIO_SM1_SHIFTCTRL_PULL_THRESH_LSB    _u(25)
#define PIO_SM1_SHIFTCTRL_PULL_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_PUSH_THRESH
// Description : Number of bits shifted into ISR before autopush, or conditional
//               push (PUSH IFFULL), will take place.
//               Write 0 for value of 32.
#define PIO_SM1_SHIFTCTRL_PUSH_THRESH_RESET  _u(0x00)
#define PIO_SM1_SHIFTCTRL_PUSH_THRESH_BITS   _u(0x01f00000)
#define PIO_SM1_SHIFTCTRL_PUSH_THRESH_MSB    _u(24)
#define PIO_SM1_SHIFTCTRL_PUSH_THRESH_LSB    _u(20)
#define PIO_SM1_SHIFTCTRL_PUSH_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR
// Description : 1 = shift out of output shift register to right. 0 = to left.
#define PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR_RESET  _u(0x1)
#define PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR_BITS   _u(0x00080000)
#define PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR_MSB    _u(19)
#define PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR_LSB    _u(19)
#define PIO_SM1_SHIFTCTRL_OUT_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_IN_SHIFTDIR
// Description : 1 = shift input shift register to right (data enters from
//               left). 0 = to left.
#define PIO_SM1_SHIFTCTRL_IN_SHIFTDIR_RESET  _u(0x1)
#define PIO_SM1_SHIFTCTRL_IN_SHIFTDIR_BITS   _u(0x00040000)
#define PIO_SM1_SHIFTCTRL_IN_SHIFTDIR_MSB    _u(18)
#define PIO_SM1_SHIFTCTRL_IN_SHIFTDIR_LSB    _u(18)
#define PIO_SM1_SHIFTCTRL_IN_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_AUTOPULL
// Description : Pull automatically when the output shift register is emptied,
//               i.e. on or following an OUT instruction which causes the output
//               shift counter to reach or exceed PULL_THRESH.
#define PIO_SM1_SHIFTCTRL_AUTOPULL_RESET  _u(0x0)
#define PIO_SM1_SHIFTCTRL_AUTOPULL_BITS   _u(0x00020000)
#define PIO_SM1_SHIFTCTRL_AUTOPULL_MSB    _u(17)
#define PIO_SM1_SHIFTCTRL_AUTOPULL_LSB    _u(17)
#define PIO_SM1_SHIFTCTRL_AUTOPULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_SHIFTCTRL_AUTOPUSH
// Description : Push automatically when the input shift register is filled,
//               i.e. on an IN instruction which causes the input shift counter
//               to reach or exceed PUSH_THRESH.
#define PIO_SM1_SHIFTCTRL_AUTOPUSH_RESET  _u(0x0)
#define PIO_SM1_SHIFTCTRL_AUTOPUSH_BITS   _u(0x00010000)
#define PIO_SM1_SHIFTCTRL_AUTOPUSH_MSB    _u(16)
#define PIO_SM1_SHIFTCTRL_AUTOPUSH_LSB    _u(16)
#define PIO_SM1_SHIFTCTRL_AUTOPUSH_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM1_ADDR
// Description : Current instruction address of state machine 1
#define PIO_SM1_ADDR_OFFSET _u(0x000000ec)
#define PIO_SM1_ADDR_BITS   _u(0x0000001f)
#define PIO_SM1_ADDR_RESET  _u(0x00000000)
#define PIO_SM1_ADDR_MSB    _u(4)
#define PIO_SM1_ADDR_LSB    _u(0)
#define PIO_SM1_ADDR_ACCESS "RO"
// =============================================================================
// Register    : PIO_SM1_INSTR
// Description : Read to see the instruction currently addressed by state
//               machine 1's program counter
//               Write to execute an instruction immediately (including jumps)
//               and then resume execution.
#define PIO_SM1_INSTR_OFFSET _u(0x000000f0)
#define PIO_SM1_INSTR_BITS   _u(0x0000ffff)
#define PIO_SM1_INSTR_RESET  "-"
#define PIO_SM1_INSTR_MSB    _u(15)
#define PIO_SM1_INSTR_LSB    _u(0)
#define PIO_SM1_INSTR_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM1_PINCTRL
// Description : State machine pin control
#define PIO_SM1_PINCTRL_OFFSET _u(0x000000f4)
#define PIO_SM1_PINCTRL_BITS   _u(0xffffffff)
#define PIO_SM1_PINCTRL_RESET  _u(0x14000000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_SIDESET_COUNT
// Description : The number of MSBs of the Delay/Side-set instruction field
//               which are used for side-set. Inclusive of the enable bit, if
//               present. Minimum of 0 (all delay bits, no side-set) and maximum
//               of 5 (all side-set, no delay).
#define PIO_SM1_PINCTRL_SIDESET_COUNT_RESET  _u(0x0)
#define PIO_SM1_PINCTRL_SIDESET_COUNT_BITS   _u(0xe0000000)
#define PIO_SM1_PINCTRL_SIDESET_COUNT_MSB    _u(31)
#define PIO_SM1_PINCTRL_SIDESET_COUNT_LSB    _u(29)
#define PIO_SM1_PINCTRL_SIDESET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_SET_COUNT
// Description : The number of pins asserted by a SET. In the range 0 to 5
//               inclusive.
#define PIO_SM1_PINCTRL_SET_COUNT_RESET  _u(0x5)
#define PIO_SM1_PINCTRL_SET_COUNT_BITS   _u(0x1c000000)
#define PIO_SM1_PINCTRL_SET_COUNT_MSB    _u(28)
#define PIO_SM1_PINCTRL_SET_COUNT_LSB    _u(26)
#define PIO_SM1_PINCTRL_SET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_OUT_COUNT
// Description : The number of pins asserted by an OUT PINS, OUT PINDIRS or MOV
//               PINS instruction. In the range 0 to 32 inclusive.
#define PIO_SM1_PINCTRL_OUT_COUNT_RESET  _u(0x00)
#define PIO_SM1_PINCTRL_OUT_COUNT_BITS   _u(0x03f00000)
#define PIO_SM1_PINCTRL_OUT_COUNT_MSB    _u(25)
#define PIO_SM1_PINCTRL_OUT_COUNT_LSB    _u(20)
#define PIO_SM1_PINCTRL_OUT_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_IN_BASE
// Description : The pin which is mapped to the least-significant bit of a state
//               machine's IN data bus. Higher-numbered pins are mapped to
//               consecutively more-significant data bits, with a modulo of 32
//               applied to pin number.
#define PIO_SM1_PINCTRL_IN_BASE_RESET  _u(0x00)
#define PIO_SM1_PINCTRL_IN_BASE_BITS   _u(0x000f8000)
#define PIO_SM1_PINCTRL_IN_BASE_MSB    _u(19)
#define PIO_SM1_PINCTRL_IN_BASE_LSB    _u(15)
#define PIO_SM1_PINCTRL_IN_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_SIDESET_BASE
// Description : The lowest-numbered pin that will be affected by a side-set
//               operation. The MSBs of an instruction's side-set/delay field
//               (up to 5, determined by SIDESET_COUNT) are used for side-set
//               data, with the remaining LSBs used for delay. The
//               least-significant bit of the side-set portion is the bit
//               written to this pin, with more-significant bits written to
//               higher-numbered pins.
#define PIO_SM1_PINCTRL_SIDESET_BASE_RESET  _u(0x00)
#define PIO_SM1_PINCTRL_SIDESET_BASE_BITS   _u(0x00007c00)
#define PIO_SM1_PINCTRL_SIDESET_BASE_MSB    _u(14)
#define PIO_SM1_PINCTRL_SIDESET_BASE_LSB    _u(10)
#define PIO_SM1_PINCTRL_SIDESET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_SET_BASE
// Description : The lowest-numbered pin that will be affected by a SET PINS or
//               SET PINDIRS instruction. The data written to this pin is the
//               least-significant bit of the SET data.
#define PIO_SM1_PINCTRL_SET_BASE_RESET  _u(0x00)
#define PIO_SM1_PINCTRL_SET_BASE_BITS   _u(0x000003e0)
#define PIO_SM1_PINCTRL_SET_BASE_MSB    _u(9)
#define PIO_SM1_PINCTRL_SET_BASE_LSB    _u(5)
#define PIO_SM1_PINCTRL_SET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM1_PINCTRL_OUT_BASE
// Description : The lowest-numbered pin that will be affected by an OUT PINS,
//               OUT PINDIRS or MOV PINS instruction. The data written to this
//               pin will always be the least-significant bit of the OUT or MOV
//               data.
#define PIO_SM1_PINCTRL_OUT_BASE_RESET  _u(0x00)
#define PIO_SM1_PINCTRL_OUT_BASE_BITS   _u(0x0000001f)
#define PIO_SM1_PINCTRL_OUT_BASE_MSB    _u(4)
#define PIO_SM1_PINCTRL_OUT_BASE_LSB    _u(0)
#define PIO_SM1_PINCTRL_OUT_BASE_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM2_CLKDIV
// Description : Clock divisor register for state machine 2
//               Frequency = clock freq / (CLKDIV_INT + CLKDIV_FRAC / 256)
#define PIO_SM2_CLKDIV_OFFSET _u(0x000000f8)
#define PIO_SM2_CLKDIV_BITS   _u(0xffffff00)
#define PIO_SM2_CLKDIV_RESET  _u(0x00010000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_CLKDIV_INT
// Description : Effective frequency is sysclk/(int + frac/256).
//               Value of 0 is interpreted as 65536. If INT is 0, FRAC must also
//               be 0.
#define PIO_SM2_CLKDIV_INT_RESET  _u(0x0001)
#define PIO_SM2_CLKDIV_INT_BITS   _u(0xffff0000)
#define PIO_SM2_CLKDIV_INT_MSB    _u(31)
#define PIO_SM2_CLKDIV_INT_LSB    _u(16)
#define PIO_SM2_CLKDIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_CLKDIV_FRAC
// Description : Fractional part of clock divisor
#define PIO_SM2_CLKDIV_FRAC_RESET  _u(0x00)
#define PIO_SM2_CLKDIV_FRAC_BITS   _u(0x0000ff00)
#define PIO_SM2_CLKDIV_FRAC_MSB    _u(15)
#define PIO_SM2_CLKDIV_FRAC_LSB    _u(8)
#define PIO_SM2_CLKDIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM2_EXECCTRL
// Description : Execution/behavioural settings for state machine 2
#define PIO_SM2_EXECCTRL_OFFSET _u(0x000000fc)
#define PIO_SM2_EXECCTRL_BITS   _u(0xffffff9f)
#define PIO_SM2_EXECCTRL_RESET  _u(0x0001f000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_EXEC_STALLED
// Description : If 1, an instruction written to SMx_INSTR is stalled, and
//               latched by the state machine. Will clear to 0 once this
//               instruction completes.
#define PIO_SM2_EXECCTRL_EXEC_STALLED_RESET  _u(0x0)
#define PIO_SM2_EXECCTRL_EXEC_STALLED_BITS   _u(0x80000000)
#define PIO_SM2_EXECCTRL_EXEC_STALLED_MSB    _u(31)
#define PIO_SM2_EXECCTRL_EXEC_STALLED_LSB    _u(31)
#define PIO_SM2_EXECCTRL_EXEC_STALLED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_SIDE_EN
// Description : If 1, the MSB of the Delay/Side-set instruction field is used
//               as side-set enable, rather than a side-set data bit. This
//               allows instructions to perform side-set optionally, rather than
//               on every instruction, but the maximum possible side-set width
//               is reduced from 5 to 4. Note that the value of
//               PINCTRL_SIDESET_COUNT is inclusive of this enable bit.
#define PIO_SM2_EXECCTRL_SIDE_EN_RESET  _u(0x0)
#define PIO_SM2_EXECCTRL_SIDE_EN_BITS   _u(0x40000000)
#define PIO_SM2_EXECCTRL_SIDE_EN_MSB    _u(30)
#define PIO_SM2_EXECCTRL_SIDE_EN_LSB    _u(30)
#define PIO_SM2_EXECCTRL_SIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_SIDE_PINDIR
// Description : If 1, side-set data is asserted to pin directions, instead of
//               pin values
#define PIO_SM2_EXECCTRL_SIDE_PINDIR_RESET  _u(0x0)
#define PIO_SM2_EXECCTRL_SIDE_PINDIR_BITS   _u(0x20000000)
#define PIO_SM2_EXECCTRL_SIDE_PINDIR_MSB    _u(29)
#define PIO_SM2_EXECCTRL_SIDE_PINDIR_LSB    _u(29)
#define PIO_SM2_EXECCTRL_SIDE_PINDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_JMP_PIN
// Description : The GPIO number to use as condition for JMP PIN. Unaffected by
//               input mapping.
#define PIO_SM2_EXECCTRL_JMP_PIN_RESET  _u(0x00)
#define PIO_SM2_EXECCTRL_JMP_PIN_BITS   _u(0x1f000000)
#define PIO_SM2_EXECCTRL_JMP_PIN_MSB    _u(28)
#define PIO_SM2_EXECCTRL_JMP_PIN_LSB    _u(24)
#define PIO_SM2_EXECCTRL_JMP_PIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_OUT_EN_SEL
// Description : Which data bit to use for inline OUT enable
#define PIO_SM2_EXECCTRL_OUT_EN_SEL_RESET  _u(0x00)
#define PIO_SM2_EXECCTRL_OUT_EN_SEL_BITS   _u(0x00f80000)
#define PIO_SM2_EXECCTRL_OUT_EN_SEL_MSB    _u(23)
#define PIO_SM2_EXECCTRL_OUT_EN_SEL_LSB    _u(19)
#define PIO_SM2_EXECCTRL_OUT_EN_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_INLINE_OUT_EN
// Description : If 1, use a bit of OUT data as an auxiliary write enable
//               When used in conjunction with OUT_STICKY, writes with an enable
//               of 0 will
//               deassert the latest pin write. This can create useful
//               masking/override behaviour
//               due to the priority ordering of state machine pin writes (SM0 <
//               SM1 < ...)
#define PIO_SM2_EXECCTRL_INLINE_OUT_EN_RESET  _u(0x0)
#define PIO_SM2_EXECCTRL_INLINE_OUT_EN_BITS   _u(0x00040000)
#define PIO_SM2_EXECCTRL_INLINE_OUT_EN_MSB    _u(18)
#define PIO_SM2_EXECCTRL_INLINE_OUT_EN_LSB    _u(18)
#define PIO_SM2_EXECCTRL_INLINE_OUT_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_OUT_STICKY
// Description : Continuously assert the most recent OUT/SET to the pins
#define PIO_SM2_EXECCTRL_OUT_STICKY_RESET  _u(0x0)
#define PIO_SM2_EXECCTRL_OUT_STICKY_BITS   _u(0x00020000)
#define PIO_SM2_EXECCTRL_OUT_STICKY_MSB    _u(17)
#define PIO_SM2_EXECCTRL_OUT_STICKY_LSB    _u(17)
#define PIO_SM2_EXECCTRL_OUT_STICKY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_WRAP_TOP
// Description : After reaching this address, execution is wrapped to
//               wrap_bottom.
//               If the instruction is a jump, and the jump condition is true,
//               the jump takes priority.
#define PIO_SM2_EXECCTRL_WRAP_TOP_RESET  _u(0x1f)
#define PIO_SM2_EXECCTRL_WRAP_TOP_BITS   _u(0x0001f000)
#define PIO_SM2_EXECCTRL_WRAP_TOP_MSB    _u(16)
#define PIO_SM2_EXECCTRL_WRAP_TOP_LSB    _u(12)
#define PIO_SM2_EXECCTRL_WRAP_TOP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_WRAP_BOTTOM
// Description : After reaching wrap_top, execution is wrapped to this address.
#define PIO_SM2_EXECCTRL_WRAP_BOTTOM_RESET  _u(0x00)
#define PIO_SM2_EXECCTRL_WRAP_BOTTOM_BITS   _u(0x00000f80)
#define PIO_SM2_EXECCTRL_WRAP_BOTTOM_MSB    _u(11)
#define PIO_SM2_EXECCTRL_WRAP_BOTTOM_LSB    _u(7)
#define PIO_SM2_EXECCTRL_WRAP_BOTTOM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_STATUS_SEL
// Description : Comparison used for the MOV x, STATUS instruction.
//               0x0 -> All-ones if TX FIFO level < N, otherwise all-zeroes
//               0x1 -> All-ones if RX FIFO level < N, otherwise all-zeroes
#define PIO_SM2_EXECCTRL_STATUS_SEL_RESET         _u(0x0)
#define PIO_SM2_EXECCTRL_STATUS_SEL_BITS          _u(0x00000010)
#define PIO_SM2_EXECCTRL_STATUS_SEL_MSB           _u(4)
#define PIO_SM2_EXECCTRL_STATUS_SEL_LSB           _u(4)
#define PIO_SM2_EXECCTRL_STATUS_SEL_ACCESS        "RW"
#define PIO_SM2_EXECCTRL_STATUS_SEL_VALUE_TXLEVEL _u(0x0)
#define PIO_SM2_EXECCTRL_STATUS_SEL_VALUE_RXLEVEL _u(0x1)
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_EXECCTRL_STATUS_N
// Description : Comparison level for the MOV x, STATUS instruction
#define PIO_SM2_EXECCTRL_STATUS_N_RESET  _u(0x0)
#define PIO_SM2_EXECCTRL_STATUS_N_BITS   _u(0x0000000f)
#define PIO_SM2_EXECCTRL_STATUS_N_MSB    _u(3)
#define PIO_SM2_EXECCTRL_STATUS_N_LSB    _u(0)
#define PIO_SM2_EXECCTRL_STATUS_N_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM2_SHIFTCTRL
// Description : Control behaviour of the input/output shift registers for state
//               machine 2
#define PIO_SM2_SHIFTCTRL_OFFSET _u(0x00000100)
#define PIO_SM2_SHIFTCTRL_BITS   _u(0xffff0000)
#define PIO_SM2_SHIFTCTRL_RESET  _u(0x000c0000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_FJOIN_RX
// Description : When 1, RX FIFO steals the TX FIFO's storage, and becomes twice
//               as deep.
//               TX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM2_SHIFTCTRL_FJOIN_RX_RESET  _u(0x0)
#define PIO_SM2_SHIFTCTRL_FJOIN_RX_BITS   _u(0x80000000)
#define PIO_SM2_SHIFTCTRL_FJOIN_RX_MSB    _u(31)
#define PIO_SM2_SHIFTCTRL_FJOIN_RX_LSB    _u(31)
#define PIO_SM2_SHIFTCTRL_FJOIN_RX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_FJOIN_TX
// Description : When 1, TX FIFO steals the RX FIFO's storage, and becomes twice
//               as deep.
//               RX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM2_SHIFTCTRL_FJOIN_TX_RESET  _u(0x0)
#define PIO_SM2_SHIFTCTRL_FJOIN_TX_BITS   _u(0x40000000)
#define PIO_SM2_SHIFTCTRL_FJOIN_TX_MSB    _u(30)
#define PIO_SM2_SHIFTCTRL_FJOIN_TX_LSB    _u(30)
#define PIO_SM2_SHIFTCTRL_FJOIN_TX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_PULL_THRESH
// Description : Number of bits shifted out of OSR before autopull, or
//               conditional pull (PULL IFEMPTY), will take place.
//               Write 0 for value of 32.
#define PIO_SM2_SHIFTCTRL_PULL_THRESH_RESET  _u(0x00)
#define PIO_SM2_SHIFTCTRL_PULL_THRESH_BITS   _u(0x3e000000)
#define PIO_SM2_SHIFTCTRL_PULL_THRESH_MSB    _u(29)
#define PIO_SM2_SHIFTCTRL_PULL_THRESH_LSB    _u(25)
#define PIO_SM2_SHIFTCTRL_PULL_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_PUSH_THRESH
// Description : Number of bits shifted into ISR before autopush, or conditional
//               push (PUSH IFFULL), will take place.
//               Write 0 for value of 32.
#define PIO_SM2_SHIFTCTRL_PUSH_THRESH_RESET  _u(0x00)
#define PIO_SM2_SHIFTCTRL_PUSH_THRESH_BITS   _u(0x01f00000)
#define PIO_SM2_SHIFTCTRL_PUSH_THRESH_MSB    _u(24)
#define PIO_SM2_SHIFTCTRL_PUSH_THRESH_LSB    _u(20)
#define PIO_SM2_SHIFTCTRL_PUSH_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR
// Description : 1 = shift out of output shift register to right. 0 = to left.
#define PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR_RESET  _u(0x1)
#define PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR_BITS   _u(0x00080000)
#define PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR_MSB    _u(19)
#define PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR_LSB    _u(19)
#define PIO_SM2_SHIFTCTRL_OUT_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_IN_SHIFTDIR
// Description : 1 = shift input shift register to right (data enters from
//               left). 0 = to left.
#define PIO_SM2_SHIFTCTRL_IN_SHIFTDIR_RESET  _u(0x1)
#define PIO_SM2_SHIFTCTRL_IN_SHIFTDIR_BITS   _u(0x00040000)
#define PIO_SM2_SHIFTCTRL_IN_SHIFTDIR_MSB    _u(18)
#define PIO_SM2_SHIFTCTRL_IN_SHIFTDIR_LSB    _u(18)
#define PIO_SM2_SHIFTCTRL_IN_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_AUTOPULL
// Description : Pull automatically when the output shift register is emptied,
//               i.e. on or following an OUT instruction which causes the output
//               shift counter to reach or exceed PULL_THRESH.
#define PIO_SM2_SHIFTCTRL_AUTOPULL_RESET  _u(0x0)
#define PIO_SM2_SHIFTCTRL_AUTOPULL_BITS   _u(0x00020000)
#define PIO_SM2_SHIFTCTRL_AUTOPULL_MSB    _u(17)
#define PIO_SM2_SHIFTCTRL_AUTOPULL_LSB    _u(17)
#define PIO_SM2_SHIFTCTRL_AUTOPULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_SHIFTCTRL_AUTOPUSH
// Description : Push automatically when the input shift register is filled,
//               i.e. on an IN instruction which causes the input shift counter
//               to reach or exceed PUSH_THRESH.
#define PIO_SM2_SHIFTCTRL_AUTOPUSH_RESET  _u(0x0)
#define PIO_SM2_SHIFTCTRL_AUTOPUSH_BITS   _u(0x00010000)
#define PIO_SM2_SHIFTCTRL_AUTOPUSH_MSB    _u(16)
#define PIO_SM2_SHIFTCTRL_AUTOPUSH_LSB    _u(16)
#define PIO_SM2_SHIFTCTRL_AUTOPUSH_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM2_ADDR
// Description : Current instruction address of state machine 2
#define PIO_SM2_ADDR_OFFSET _u(0x00000104)
#define PIO_SM2_ADDR_BITS   _u(0x0000001f)
#define PIO_SM2_ADDR_RESET  _u(0x00000000)
#define PIO_SM2_ADDR_MSB    _u(4)
#define PIO_SM2_ADDR_LSB    _u(0)
#define PIO_SM2_ADDR_ACCESS "RO"
// =============================================================================
// Register    : PIO_SM2_INSTR
// Description : Read to see the instruction currently addressed by state
//               machine 2's program counter
//               Write to execute an instruction immediately (including jumps)
//               and then resume execution.
#define PIO_SM2_INSTR_OFFSET _u(0x00000108)
#define PIO_SM2_INSTR_BITS   _u(0x0000ffff)
#define PIO_SM2_INSTR_RESET  "-"
#define PIO_SM2_INSTR_MSB    _u(15)
#define PIO_SM2_INSTR_LSB    _u(0)
#define PIO_SM2_INSTR_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM2_PINCTRL
// Description : State machine pin control
#define PIO_SM2_PINCTRL_OFFSET _u(0x0000010c)
#define PIO_SM2_PINCTRL_BITS   _u(0xffffffff)
#define PIO_SM2_PINCTRL_RESET  _u(0x14000000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_SIDESET_COUNT
// Description : The number of MSBs of the Delay/Side-set instruction field
//               which are used for side-set. Inclusive of the enable bit, if
//               present. Minimum of 0 (all delay bits, no side-set) and maximum
//               of 5 (all side-set, no delay).
#define PIO_SM2_PINCTRL_SIDESET_COUNT_RESET  _u(0x0)
#define PIO_SM2_PINCTRL_SIDESET_COUNT_BITS   _u(0xe0000000)
#define PIO_SM2_PINCTRL_SIDESET_COUNT_MSB    _u(31)
#define PIO_SM2_PINCTRL_SIDESET_COUNT_LSB    _u(29)
#define PIO_SM2_PINCTRL_SIDESET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_SET_COUNT
// Description : The number of pins asserted by a SET. In the range 0 to 5
//               inclusive.
#define PIO_SM2_PINCTRL_SET_COUNT_RESET  _u(0x5)
#define PIO_SM2_PINCTRL_SET_COUNT_BITS   _u(0x1c000000)
#define PIO_SM2_PINCTRL_SET_COUNT_MSB    _u(28)
#define PIO_SM2_PINCTRL_SET_COUNT_LSB    _u(26)
#define PIO_SM2_PINCTRL_SET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_OUT_COUNT
// Description : The number of pins asserted by an OUT PINS, OUT PINDIRS or MOV
//               PINS instruction. In the range 0 to 32 inclusive.
#define PIO_SM2_PINCTRL_OUT_COUNT_RESET  _u(0x00)
#define PIO_SM2_PINCTRL_OUT_COUNT_BITS   _u(0x03f00000)
#define PIO_SM2_PINCTRL_OUT_COUNT_MSB    _u(25)
#define PIO_SM2_PINCTRL_OUT_COUNT_LSB    _u(20)
#define PIO_SM2_PINCTRL_OUT_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_IN_BASE
// Description : The pin which is mapped to the least-significant bit of a state
//               machine's IN data bus. Higher-numbered pins are mapped to
//               consecutively more-significant data bits, with a modulo of 32
//               applied to pin number.
#define PIO_SM2_PINCTRL_IN_BASE_RESET  _u(0x00)
#define PIO_SM2_PINCTRL_IN_BASE_BITS   _u(0x000f8000)
#define PIO_SM2_PINCTRL_IN_BASE_MSB    _u(19)
#define PIO_SM2_PINCTRL_IN_BASE_LSB    _u(15)
#define PIO_SM2_PINCTRL_IN_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_SIDESET_BASE
// Description : The lowest-numbered pin that will be affected by a side-set
//               operation. The MSBs of an instruction's side-set/delay field
//               (up to 5, determined by SIDESET_COUNT) are used for side-set
//               data, with the remaining LSBs used for delay. The
//               least-significant bit of the side-set portion is the bit
//               written to this pin, with more-significant bits written to
//               higher-numbered pins.
#define PIO_SM2_PINCTRL_SIDESET_BASE_RESET  _u(0x00)
#define PIO_SM2_PINCTRL_SIDESET_BASE_BITS   _u(0x00007c00)
#define PIO_SM2_PINCTRL_SIDESET_BASE_MSB    _u(14)
#define PIO_SM2_PINCTRL_SIDESET_BASE_LSB    _u(10)
#define PIO_SM2_PINCTRL_SIDESET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_SET_BASE
// Description : The lowest-numbered pin that will be affected by a SET PINS or
//               SET PINDIRS instruction. The data written to this pin is the
//               least-significant bit of the SET data.
#define PIO_SM2_PINCTRL_SET_BASE_RESET  _u(0x00)
#define PIO_SM2_PINCTRL_SET_BASE_BITS   _u(0x000003e0)
#define PIO_SM2_PINCTRL_SET_BASE_MSB    _u(9)
#define PIO_SM2_PINCTRL_SET_BASE_LSB    _u(5)
#define PIO_SM2_PINCTRL_SET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM2_PINCTRL_OUT_BASE
// Description : The lowest-numbered pin that will be affected by an OUT PINS,
//               OUT PINDIRS or MOV PINS instruction. The data written to this
//               pin will always be the least-significant bit of the OUT or MOV
//               data.
#define PIO_SM2_PINCTRL_OUT_BASE_RESET  _u(0x00)
#define PIO_SM2_PINCTRL_OUT_BASE_BITS   _u(0x0000001f)
#define PIO_SM2_PINCTRL_OUT_BASE_MSB    _u(4)
#define PIO_SM2_PINCTRL_OUT_BASE_LSB    _u(0)
#define PIO_SM2_PINCTRL_OUT_BASE_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM3_CLKDIV
// Description : Clock divisor register for state machine 3
//               Frequency = clock freq / (CLKDIV_INT + CLKDIV_FRAC / 256)
#define PIO_SM3_CLKDIV_OFFSET _u(0x00000110)
#define PIO_SM3_CLKDIV_BITS   _u(0xffffff00)
#define PIO_SM3_CLKDIV_RESET  _u(0x00010000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_CLKDIV_INT
// Description : Effective frequency is sysclk/(int + frac/256).
//               Value of 0 is interpreted as 65536. If INT is 0, FRAC must also
//               be 0.
#define PIO_SM3_CLKDIV_INT_RESET  _u(0x0001)
#define PIO_SM3_CLKDIV_INT_BITS   _u(0xffff0000)
#define PIO_SM3_CLKDIV_INT_MSB    _u(31)
#define PIO_SM3_CLKDIV_INT_LSB    _u(16)
#define PIO_SM3_CLKDIV_INT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_CLKDIV_FRAC
// Description : Fractional part of clock divisor
#define PIO_SM3_CLKDIV_FRAC_RESET  _u(0x00)
#define PIO_SM3_CLKDIV_FRAC_BITS   _u(0x0000ff00)
#define PIO_SM3_CLKDIV_FRAC_MSB    _u(15)
#define PIO_SM3_CLKDIV_FRAC_LSB    _u(8)
#define PIO_SM3_CLKDIV_FRAC_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM3_EXECCTRL
// Description : Execution/behavioural settings for state machine 3
#define PIO_SM3_EXECCTRL_OFFSET _u(0x00000114)
#define PIO_SM3_EXECCTRL_BITS   _u(0xffffff9f)
#define PIO_SM3_EXECCTRL_RESET  _u(0x0001f000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_EXEC_STALLED
// Description : If 1, an instruction written to SMx_INSTR is stalled, and
//               latched by the state machine. Will clear to 0 once this
//               instruction completes.
#define PIO_SM3_EXECCTRL_EXEC_STALLED_RESET  _u(0x0)
#define PIO_SM3_EXECCTRL_EXEC_STALLED_BITS   _u(0x80000000)
#define PIO_SM3_EXECCTRL_EXEC_STALLED_MSB    _u(31)
#define PIO_SM3_EXECCTRL_EXEC_STALLED_LSB    _u(31)
#define PIO_SM3_EXECCTRL_EXEC_STALLED_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_SIDE_EN
// Description : If 1, the MSB of the Delay/Side-set instruction field is used
//               as side-set enable, rather than a side-set data bit. This
//               allows instructions to perform side-set optionally, rather than
//               on every instruction, but the maximum possible side-set width
//               is reduced from 5 to 4. Note that the value of
//               PINCTRL_SIDESET_COUNT is inclusive of this enable bit.
#define PIO_SM3_EXECCTRL_SIDE_EN_RESET  _u(0x0)
#define PIO_SM3_EXECCTRL_SIDE_EN_BITS   _u(0x40000000)
#define PIO_SM3_EXECCTRL_SIDE_EN_MSB    _u(30)
#define PIO_SM3_EXECCTRL_SIDE_EN_LSB    _u(30)
#define PIO_SM3_EXECCTRL_SIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_SIDE_PINDIR
// Description : If 1, side-set data is asserted to pin directions, instead of
//               pin values
#define PIO_SM3_EXECCTRL_SIDE_PINDIR_RESET  _u(0x0)
#define PIO_SM3_EXECCTRL_SIDE_PINDIR_BITS   _u(0x20000000)
#define PIO_SM3_EXECCTRL_SIDE_PINDIR_MSB    _u(29)
#define PIO_SM3_EXECCTRL_SIDE_PINDIR_LSB    _u(29)
#define PIO_SM3_EXECCTRL_SIDE_PINDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_JMP_PIN
// Description : The GPIO number to use as condition for JMP PIN. Unaffected by
//               input mapping.
#define PIO_SM3_EXECCTRL_JMP_PIN_RESET  _u(0x00)
#define PIO_SM3_EXECCTRL_JMP_PIN_BITS   _u(0x1f000000)
#define PIO_SM3_EXECCTRL_JMP_PIN_MSB    _u(28)
#define PIO_SM3_EXECCTRL_JMP_PIN_LSB    _u(24)
#define PIO_SM3_EXECCTRL_JMP_PIN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_OUT_EN_SEL
// Description : Which data bit to use for inline OUT enable
#define PIO_SM3_EXECCTRL_OUT_EN_SEL_RESET  _u(0x00)
#define PIO_SM3_EXECCTRL_OUT_EN_SEL_BITS   _u(0x00f80000)
#define PIO_SM3_EXECCTRL_OUT_EN_SEL_MSB    _u(23)
#define PIO_SM3_EXECCTRL_OUT_EN_SEL_LSB    _u(19)
#define PIO_SM3_EXECCTRL_OUT_EN_SEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_INLINE_OUT_EN
// Description : If 1, use a bit of OUT data as an auxiliary write enable
//               When used in conjunction with OUT_STICKY, writes with an enable
//               of 0 will
//               deassert the latest pin write. This can create useful
//               masking/override behaviour
//               due to the priority ordering of state machine pin writes (SM0 <
//               SM1 < ...)
#define PIO_SM3_EXECCTRL_INLINE_OUT_EN_RESET  _u(0x0)
#define PIO_SM3_EXECCTRL_INLINE_OUT_EN_BITS   _u(0x00040000)
#define PIO_SM3_EXECCTRL_INLINE_OUT_EN_MSB    _u(18)
#define PIO_SM3_EXECCTRL_INLINE_OUT_EN_LSB    _u(18)
#define PIO_SM3_EXECCTRL_INLINE_OUT_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_OUT_STICKY
// Description : Continuously assert the most recent OUT/SET to the pins
#define PIO_SM3_EXECCTRL_OUT_STICKY_RESET  _u(0x0)
#define PIO_SM3_EXECCTRL_OUT_STICKY_BITS   _u(0x00020000)
#define PIO_SM3_EXECCTRL_OUT_STICKY_MSB    _u(17)
#define PIO_SM3_EXECCTRL_OUT_STICKY_LSB    _u(17)
#define PIO_SM3_EXECCTRL_OUT_STICKY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_WRAP_TOP
// Description : After reaching this address, execution is wrapped to
//               wrap_bottom.
//               If the instruction is a jump, and the jump condition is true,
//               the jump takes priority.
#define PIO_SM3_EXECCTRL_WRAP_TOP_RESET  _u(0x1f)
#define PIO_SM3_EXECCTRL_WRAP_TOP_BITS   _u(0x0001f000)
#define PIO_SM3_EXECCTRL_WRAP_TOP_MSB    _u(16)
#define PIO_SM3_EXECCTRL_WRAP_TOP_LSB    _u(12)
#define PIO_SM3_EXECCTRL_WRAP_TOP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_WRAP_BOTTOM
// Description : After reaching wrap_top, execution is wrapped to this address.
#define PIO_SM3_EXECCTRL_WRAP_BOTTOM_RESET  _u(0x00)
#define PIO_SM3_EXECCTRL_WRAP_BOTTOM_BITS   _u(0x00000f80)
#define PIO_SM3_EXECCTRL_WRAP_BOTTOM_MSB    _u(11)
#define PIO_SM3_EXECCTRL_WRAP_BOTTOM_LSB    _u(7)
#define PIO_SM3_EXECCTRL_WRAP_BOTTOM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_STATUS_SEL
// Description : Comparison used for the MOV x, STATUS instruction.
//               0x0 -> All-ones if TX FIFO level < N, otherwise all-zeroes
//               0x1 -> All-ones if RX FIFO level < N, otherwise all-zeroes
#define PIO_SM3_EXECCTRL_STATUS_SEL_RESET         _u(0x0)
#define PIO_SM3_EXECCTRL_STATUS_SEL_BITS          _u(0x00000010)
#define PIO_SM3_EXECCTRL_STATUS_SEL_MSB           _u(4)
#define PIO_SM3_EXECCTRL_STATUS_SEL_LSB           _u(4)
#define PIO_SM3_EXECCTRL_STATUS_SEL_ACCESS        "RW"
#define PIO_SM3_EXECCTRL_STATUS_SEL_VALUE_TXLEVEL _u(0x0)
#define PIO_SM3_EXECCTRL_STATUS_SEL_VALUE_RXLEVEL _u(0x1)
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_EXECCTRL_STATUS_N
// Description : Comparison level for the MOV x, STATUS instruction
#define PIO_SM3_EXECCTRL_STATUS_N_RESET  _u(0x0)
#define PIO_SM3_EXECCTRL_STATUS_N_BITS   _u(0x0000000f)
#define PIO_SM3_EXECCTRL_STATUS_N_MSB    _u(3)
#define PIO_SM3_EXECCTRL_STATUS_N_LSB    _u(0)
#define PIO_SM3_EXECCTRL_STATUS_N_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM3_SHIFTCTRL
// Description : Control behaviour of the input/output shift registers for state
//               machine 3
#define PIO_SM3_SHIFTCTRL_OFFSET _u(0x00000118)
#define PIO_SM3_SHIFTCTRL_BITS   _u(0xffff0000)
#define PIO_SM3_SHIFTCTRL_RESET  _u(0x000c0000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_FJOIN_RX
// Description : When 1, RX FIFO steals the TX FIFO's storage, and becomes twice
//               as deep.
//               TX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM3_SHIFTCTRL_FJOIN_RX_RESET  _u(0x0)
#define PIO_SM3_SHIFTCTRL_FJOIN_RX_BITS   _u(0x80000000)
#define PIO_SM3_SHIFTCTRL_FJOIN_RX_MSB    _u(31)
#define PIO_SM3_SHIFTCTRL_FJOIN_RX_LSB    _u(31)
#define PIO_SM3_SHIFTCTRL_FJOIN_RX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_FJOIN_TX
// Description : When 1, TX FIFO steals the RX FIFO's storage, and becomes twice
//               as deep.
//               RX FIFO is disabled as a result (always reads as both full and
//               empty).
//               FIFOs are flushed when this bit is changed.
#define PIO_SM3_SHIFTCTRL_FJOIN_TX_RESET  _u(0x0)
#define PIO_SM3_SHIFTCTRL_FJOIN_TX_BITS   _u(0x40000000)
#define PIO_SM3_SHIFTCTRL_FJOIN_TX_MSB    _u(30)
#define PIO_SM3_SHIFTCTRL_FJOIN_TX_LSB    _u(30)
#define PIO_SM3_SHIFTCTRL_FJOIN_TX_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_PULL_THRESH
// Description : Number of bits shifted out of OSR before autopull, or
//               conditional pull (PULL IFEMPTY), will take place.
//               Write 0 for value of 32.
#define PIO_SM3_SHIFTCTRL_PULL_THRESH_RESET  _u(0x00)
#define PIO_SM3_SHIFTCTRL_PULL_THRESH_BITS   _u(0x3e000000)
#define PIO_SM3_SHIFTCTRL_PULL_THRESH_MSB    _u(29)
#define PIO_SM3_SHIFTCTRL_PULL_THRESH_LSB    _u(25)
#define PIO_SM3_SHIFTCTRL_PULL_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_PUSH_THRESH
// Description : Number of bits shifted into ISR before autopush, or conditional
//               push (PUSH IFFULL), will take place.
//               Write 0 for value of 32.
#define PIO_SM3_SHIFTCTRL_PUSH_THRESH_RESET  _u(0x00)
#define PIO_SM3_SHIFTCTRL_PUSH_THRESH_BITS   _u(0x01f00000)
#define PIO_SM3_SHIFTCTRL_PUSH_THRESH_MSB    _u(24)
#define PIO_SM3_SHIFTCTRL_PUSH_THRESH_LSB    _u(20)
#define PIO_SM3_SHIFTCTRL_PUSH_THRESH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR
// Description : 1 = shift out of output shift register to right. 0 = to left.
#define PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR_RESET  _u(0x1)
#define PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR_BITS   _u(0x00080000)
#define PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR_MSB    _u(19)
#define PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR_LSB    _u(19)
#define PIO_SM3_SHIFTCTRL_OUT_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_IN_SHIFTDIR
// Description : 1 = shift input shift register to right (data enters from
//               left). 0 = to left.
#define PIO_SM3_SHIFTCTRL_IN_SHIFTDIR_RESET  _u(0x1)
#define PIO_SM3_SHIFTCTRL_IN_SHIFTDIR_BITS   _u(0x00040000)
#define PIO_SM3_SHIFTCTRL_IN_SHIFTDIR_MSB    _u(18)
#define PIO_SM3_SHIFTCTRL_IN_SHIFTDIR_LSB    _u(18)
#define PIO_SM3_SHIFTCTRL_IN_SHIFTDIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_AUTOPULL
// Description : Pull automatically when the output shift register is emptied,
//               i.e. on or following an OUT instruction which causes the output
//               shift counter to reach or exceed PULL_THRESH.
#define PIO_SM3_SHIFTCTRL_AUTOPULL_RESET  _u(0x0)
#define PIO_SM3_SHIFTCTRL_AUTOPULL_BITS   _u(0x00020000)
#define PIO_SM3_SHIFTCTRL_AUTOPULL_MSB    _u(17)
#define PIO_SM3_SHIFTCTRL_AUTOPULL_LSB    _u(17)
#define PIO_SM3_SHIFTCTRL_AUTOPULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_SHIFTCTRL_AUTOPUSH
// Description : Push automatically when the input shift register is filled,
//               i.e. on an IN instruction which causes the input shift counter
//               to reach or exceed PUSH_THRESH.
#define PIO_SM3_SHIFTCTRL_AUTOPUSH_RESET  _u(0x0)
#define PIO_SM3_SHIFTCTRL_AUTOPUSH_BITS   _u(0x00010000)
#define PIO_SM3_SHIFTCTRL_AUTOPUSH_MSB    _u(16)
#define PIO_SM3_SHIFTCTRL_AUTOPUSH_LSB    _u(16)
#define PIO_SM3_SHIFTCTRL_AUTOPUSH_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM3_ADDR
// Description : Current instruction address of state machine 3
#define PIO_SM3_ADDR_OFFSET _u(0x0000011c)
#define PIO_SM3_ADDR_BITS   _u(0x0000001f)
#define PIO_SM3_ADDR_RESET  _u(0x00000000)
#define PIO_SM3_ADDR_MSB    _u(4)
#define PIO_SM3_ADDR_LSB    _u(0)
#define PIO_SM3_ADDR_ACCESS "RO"
// =============================================================================
// Register    : PIO_SM3_INSTR
// Description : Read to see the instruction currently addressed by state
//               machine 3's program counter
//               Write to execute an instruction immediately (including jumps)
//               and then resume execution.
#define PIO_SM3_INSTR_OFFSET _u(0x00000120)
#define PIO_SM3_INSTR_BITS   _u(0x0000ffff)
#define PIO_SM3_INSTR_RESET  "-"
#define PIO_SM3_INSTR_MSB    _u(15)
#define PIO_SM3_INSTR_LSB    _u(0)
#define PIO_SM3_INSTR_ACCESS "RW"
// =============================================================================
// Register    : PIO_SM3_PINCTRL
// Description : State machine pin control
#define PIO_SM3_PINCTRL_OFFSET _u(0x00000124)
#define PIO_SM3_PINCTRL_BITS   _u(0xffffffff)
#define PIO_SM3_PINCTRL_RESET  _u(0x14000000)
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_SIDESET_COUNT
// Description : The number of MSBs of the Delay/Side-set instruction field
//               which are used for side-set. Inclusive of the enable bit, if
//               present. Minimum of 0 (all delay bits, no side-set) and maximum
//               of 5 (all side-set, no delay).
#define PIO_SM3_PINCTRL_SIDESET_COUNT_RESET  _u(0x0)
#define PIO_SM3_PINCTRL_SIDESET_COUNT_BITS   _u(0xe0000000)
#define PIO_SM3_PINCTRL_SIDESET_COUNT_MSB    _u(31)
#define PIO_SM3_PINCTRL_SIDESET_COUNT_LSB    _u(29)
#define PIO_SM3_PINCTRL_SIDESET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_SET_COUNT
// Description : The number of pins asserted by a SET. In the range 0 to 5
//               inclusive.
#define PIO_SM3_PINCTRL_SET_COUNT_RESET  _u(0x5)
#define PIO_SM3_PINCTRL_SET_COUNT_BITS   _u(0x1c000000)
#define PIO_SM3_PINCTRL_SET_COUNT_MSB    _u(28)
#define PIO_SM3_PINCTRL_SET_COUNT_LSB    _u(26)
#define PIO_SM3_PINCTRL_SET_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_OUT_COUNT
// Description : The number of pins asserted by an OUT PINS, OUT PINDIRS or MOV
//               PINS instruction. In the range 0 to 32 inclusive.
#define PIO_SM3_PINCTRL_OUT_COUNT_RESET  _u(0x00)
#define PIO_SM3_PINCTRL_OUT_COUNT_BITS   _u(0x03f00000)
#define PIO_SM3_PINCTRL_OUT_COUNT_MSB    _u(25)
#define PIO_SM3_PINCTRL_OUT_COUNT_LSB    _u(20)
#define PIO_SM3_PINCTRL_OUT_COUNT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_IN_BASE
// Description : The pin which is mapped to the least-significant bit of a state
//               machine's IN data bus. Higher-numbered pins are mapped to
//               consecutively more-significant data bits, with a modulo of 32
//               applied to pin number.
#define PIO_SM3_PINCTRL_IN_BASE_RESET  _u(0x00)
#define PIO_SM3_PINCTRL_IN_BASE_BITS   _u(0x000f8000)
#define PIO_SM3_PINCTRL_IN_BASE_MSB    _u(19)
#define PIO_SM3_PINCTRL_IN_BASE_LSB    _u(15)
#define PIO_SM3_PINCTRL_IN_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_SIDESET_BASE
// Description : The lowest-numbered pin that will be affected by a side-set
//               operation. The MSBs of an instruction's side-set/delay field
//               (up to 5, determined by SIDESET_COUNT) are used for side-set
//               data, with the remaining LSBs used for delay. The
//               least-significant bit of the side-set portion is the bit
//               written to this pin, with more-significant bits written to
//               higher-numbered pins.
#define PIO_SM3_PINCTRL_SIDESET_BASE_RESET  _u(0x00)
#define PIO_SM3_PINCTRL_SIDESET_BASE_BITS   _u(0x00007c00)
#define PIO_SM3_PINCTRL_SIDESET_BASE_MSB    _u(14)
#define PIO_SM3_PINCTRL_SIDESET_BASE_LSB    _u(10)
#define PIO_SM3_PINCTRL_SIDESET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_SET_BASE
// Description : The lowest-numbered pin that will be affected by a SET PINS or
//               SET PINDIRS instruction. The data written to this pin is the
//               least-significant bit of the SET data.
#define PIO_SM3_PINCTRL_SET_BASE_RESET  _u(0x00)
#define PIO_SM3_PINCTRL_SET_BASE_BITS   _u(0x000003e0)
#define PIO_SM3_PINCTRL_SET_BASE_MSB    _u(9)
#define PIO_SM3_PINCTRL_SET_BASE_LSB    _u(5)
#define PIO_SM3_PINCTRL_SET_BASE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_SM3_PINCTRL_OUT_BASE
// Description : The lowest-numbered pin that will be affected by an OUT PINS,
//               OUT PINDIRS or MOV PINS instruction. The data written to this
//               pin will always be the least-significant bit of the OUT or MOV
//               data.
#define PIO_SM3_PINCTRL_OUT_BASE_RESET  _u(0x00)
#define PIO_SM3_PINCTRL_OUT_BASE_BITS   _u(0x0000001f)
#define PIO_SM3_PINCTRL_OUT_BASE_MSB    _u(4)
#define PIO_SM3_PINCTRL_OUT_BASE_LSB    _u(0)
#define PIO_SM3_PINCTRL_OUT_BASE_ACCESS "RW"
// =============================================================================
// Register    : PIO_INTR
// Description : Raw Interrupts
#define PIO_INTR_OFFSET _u(0x00000128)
#define PIO_INTR_BITS   _u(0x00000fff)
#define PIO_INTR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM3
// Description : None
#define PIO_INTR_SM3_RESET  _u(0x0)
#define PIO_INTR_SM3_BITS   _u(0x00000800)
#define PIO_INTR_SM3_MSB    _u(11)
#define PIO_INTR_SM3_LSB    _u(11)
#define PIO_INTR_SM3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM2
// Description : None
#define PIO_INTR_SM2_RESET  _u(0x0)
#define PIO_INTR_SM2_BITS   _u(0x00000400)
#define PIO_INTR_SM2_MSB    _u(10)
#define PIO_INTR_SM2_LSB    _u(10)
#define PIO_INTR_SM2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM1
// Description : None
#define PIO_INTR_SM1_RESET  _u(0x0)
#define PIO_INTR_SM1_BITS   _u(0x00000200)
#define PIO_INTR_SM1_MSB    _u(9)
#define PIO_INTR_SM1_LSB    _u(9)
#define PIO_INTR_SM1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM0
// Description : None
#define PIO_INTR_SM0_RESET  _u(0x0)
#define PIO_INTR_SM0_BITS   _u(0x00000100)
#define PIO_INTR_SM0_MSB    _u(8)
#define PIO_INTR_SM0_LSB    _u(8)
#define PIO_INTR_SM0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM3_TXNFULL
// Description : None
#define PIO_INTR_SM3_TXNFULL_RESET  _u(0x0)
#define PIO_INTR_SM3_TXNFULL_BITS   _u(0x00000080)
#define PIO_INTR_SM3_TXNFULL_MSB    _u(7)
#define PIO_INTR_SM3_TXNFULL_LSB    _u(7)
#define PIO_INTR_SM3_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM2_TXNFULL
// Description : None
#define PIO_INTR_SM2_TXNFULL_RESET  _u(0x0)
#define PIO_INTR_SM2_TXNFULL_BITS   _u(0x00000040)
#define PIO_INTR_SM2_TXNFULL_MSB    _u(6)
#define PIO_INTR_SM2_TXNFULL_LSB    _u(6)
#define PIO_INTR_SM2_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM1_TXNFULL
// Description : None
#define PIO_INTR_SM1_TXNFULL_RESET  _u(0x0)
#define PIO_INTR_SM1_TXNFULL_BITS   _u(0x00000020)
#define PIO_INTR_SM1_TXNFULL_MSB    _u(5)
#define PIO_INTR_SM1_TXNFULL_LSB    _u(5)
#define PIO_INTR_SM1_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM0_TXNFULL
// Description : None
#define PIO_INTR_SM0_TXNFULL_RESET  _u(0x0)
#define PIO_INTR_SM0_TXNFULL_BITS   _u(0x00000010)
#define PIO_INTR_SM0_TXNFULL_MSB    _u(4)
#define PIO_INTR_SM0_TXNFULL_LSB    _u(4)
#define PIO_INTR_SM0_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM3_RXNEMPTY
// Description : None
#define PIO_INTR_SM3_RXNEMPTY_RESET  _u(0x0)
#define PIO_INTR_SM3_RXNEMPTY_BITS   _u(0x00000008)
#define PIO_INTR_SM3_RXNEMPTY_MSB    _u(3)
#define PIO_INTR_SM3_RXNEMPTY_LSB    _u(3)
#define PIO_INTR_SM3_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM2_RXNEMPTY
// Description : None
#define PIO_INTR_SM2_RXNEMPTY_RESET  _u(0x0)
#define PIO_INTR_SM2_RXNEMPTY_BITS   _u(0x00000004)
#define PIO_INTR_SM2_RXNEMPTY_MSB    _u(2)
#define PIO_INTR_SM2_RXNEMPTY_LSB    _u(2)
#define PIO_INTR_SM2_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM1_RXNEMPTY
// Description : None
#define PIO_INTR_SM1_RXNEMPTY_RESET  _u(0x0)
#define PIO_INTR_SM1_RXNEMPTY_BITS   _u(0x00000002)
#define PIO_INTR_SM1_RXNEMPTY_MSB    _u(1)
#define PIO_INTR_SM1_RXNEMPTY_LSB    _u(1)
#define PIO_INTR_SM1_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_INTR_SM0_RXNEMPTY
// Description : None
#define PIO_INTR_SM0_RXNEMPTY_RESET  _u(0x0)
#define PIO_INTR_SM0_RXNEMPTY_BITS   _u(0x00000001)
#define PIO_INTR_SM0_RXNEMPTY_MSB    _u(0)
#define PIO_INTR_SM0_RXNEMPTY_LSB    _u(0)
#define PIO_INTR_SM0_RXNEMPTY_ACCESS "RO"
// =============================================================================
// Register    : PIO_IRQ0_INTE
// Description : Interrupt Enable for irq0
#define PIO_IRQ0_INTE_OFFSET _u(0x0000012c)
#define PIO_IRQ0_INTE_BITS   _u(0x00000fff)
#define PIO_IRQ0_INTE_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM3
// Description : None
#define PIO_IRQ0_INTE_SM3_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM3_BITS   _u(0x00000800)
#define PIO_IRQ0_INTE_SM3_MSB    _u(11)
#define PIO_IRQ0_INTE_SM3_LSB    _u(11)
#define PIO_IRQ0_INTE_SM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM2
// Description : None
#define PIO_IRQ0_INTE_SM2_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM2_BITS   _u(0x00000400)
#define PIO_IRQ0_INTE_SM2_MSB    _u(10)
#define PIO_IRQ0_INTE_SM2_LSB    _u(10)
#define PIO_IRQ0_INTE_SM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM1
// Description : None
#define PIO_IRQ0_INTE_SM1_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM1_BITS   _u(0x00000200)
#define PIO_IRQ0_INTE_SM1_MSB    _u(9)
#define PIO_IRQ0_INTE_SM1_LSB    _u(9)
#define PIO_IRQ0_INTE_SM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM0
// Description : None
#define PIO_IRQ0_INTE_SM0_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM0_BITS   _u(0x00000100)
#define PIO_IRQ0_INTE_SM0_MSB    _u(8)
#define PIO_IRQ0_INTE_SM0_LSB    _u(8)
#define PIO_IRQ0_INTE_SM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM3_TXNFULL
// Description : None
#define PIO_IRQ0_INTE_SM3_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM3_TXNFULL_BITS   _u(0x00000080)
#define PIO_IRQ0_INTE_SM3_TXNFULL_MSB    _u(7)
#define PIO_IRQ0_INTE_SM3_TXNFULL_LSB    _u(7)
#define PIO_IRQ0_INTE_SM3_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM2_TXNFULL
// Description : None
#define PIO_IRQ0_INTE_SM2_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM2_TXNFULL_BITS   _u(0x00000040)
#define PIO_IRQ0_INTE_SM2_TXNFULL_MSB    _u(6)
#define PIO_IRQ0_INTE_SM2_TXNFULL_LSB    _u(6)
#define PIO_IRQ0_INTE_SM2_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM1_TXNFULL
// Description : None
#define PIO_IRQ0_INTE_SM1_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM1_TXNFULL_BITS   _u(0x00000020)
#define PIO_IRQ0_INTE_SM1_TXNFULL_MSB    _u(5)
#define PIO_IRQ0_INTE_SM1_TXNFULL_LSB    _u(5)
#define PIO_IRQ0_INTE_SM1_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM0_TXNFULL
// Description : None
#define PIO_IRQ0_INTE_SM0_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM0_TXNFULL_BITS   _u(0x00000010)
#define PIO_IRQ0_INTE_SM0_TXNFULL_MSB    _u(4)
#define PIO_IRQ0_INTE_SM0_TXNFULL_LSB    _u(4)
#define PIO_IRQ0_INTE_SM0_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTE_SM3_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM3_RXNEMPTY_BITS   _u(0x00000008)
#define PIO_IRQ0_INTE_SM3_RXNEMPTY_MSB    _u(3)
#define PIO_IRQ0_INTE_SM3_RXNEMPTY_LSB    _u(3)
#define PIO_IRQ0_INTE_SM3_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTE_SM2_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM2_RXNEMPTY_BITS   _u(0x00000004)
#define PIO_IRQ0_INTE_SM2_RXNEMPTY_MSB    _u(2)
#define PIO_IRQ0_INTE_SM2_RXNEMPTY_LSB    _u(2)
#define PIO_IRQ0_INTE_SM2_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTE_SM1_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM1_RXNEMPTY_BITS   _u(0x00000002)
#define PIO_IRQ0_INTE_SM1_RXNEMPTY_MSB    _u(1)
#define PIO_IRQ0_INTE_SM1_RXNEMPTY_LSB    _u(1)
#define PIO_IRQ0_INTE_SM1_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTE_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTE_SM0_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTE_SM0_RXNEMPTY_BITS   _u(0x00000001)
#define PIO_IRQ0_INTE_SM0_RXNEMPTY_MSB    _u(0)
#define PIO_IRQ0_INTE_SM0_RXNEMPTY_LSB    _u(0)
#define PIO_IRQ0_INTE_SM0_RXNEMPTY_ACCESS "RW"
// =============================================================================
// Register    : PIO_IRQ0_INTF
// Description : Interrupt Force for irq0
#define PIO_IRQ0_INTF_OFFSET _u(0x00000130)
#define PIO_IRQ0_INTF_BITS   _u(0x00000fff)
#define PIO_IRQ0_INTF_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM3
// Description : None
#define PIO_IRQ0_INTF_SM3_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM3_BITS   _u(0x00000800)
#define PIO_IRQ0_INTF_SM3_MSB    _u(11)
#define PIO_IRQ0_INTF_SM3_LSB    _u(11)
#define PIO_IRQ0_INTF_SM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM2
// Description : None
#define PIO_IRQ0_INTF_SM2_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM2_BITS   _u(0x00000400)
#define PIO_IRQ0_INTF_SM2_MSB    _u(10)
#define PIO_IRQ0_INTF_SM2_LSB    _u(10)
#define PIO_IRQ0_INTF_SM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM1
// Description : None
#define PIO_IRQ0_INTF_SM1_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM1_BITS   _u(0x00000200)
#define PIO_IRQ0_INTF_SM1_MSB    _u(9)
#define PIO_IRQ0_INTF_SM1_LSB    _u(9)
#define PIO_IRQ0_INTF_SM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM0
// Description : None
#define PIO_IRQ0_INTF_SM0_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM0_BITS   _u(0x00000100)
#define PIO_IRQ0_INTF_SM0_MSB    _u(8)
#define PIO_IRQ0_INTF_SM0_LSB    _u(8)
#define PIO_IRQ0_INTF_SM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM3_TXNFULL
// Description : None
#define PIO_IRQ0_INTF_SM3_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM3_TXNFULL_BITS   _u(0x00000080)
#define PIO_IRQ0_INTF_SM3_TXNFULL_MSB    _u(7)
#define PIO_IRQ0_INTF_SM3_TXNFULL_LSB    _u(7)
#define PIO_IRQ0_INTF_SM3_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM2_TXNFULL
// Description : None
#define PIO_IRQ0_INTF_SM2_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM2_TXNFULL_BITS   _u(0x00000040)
#define PIO_IRQ0_INTF_SM2_TXNFULL_MSB    _u(6)
#define PIO_IRQ0_INTF_SM2_TXNFULL_LSB    _u(6)
#define PIO_IRQ0_INTF_SM2_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM1_TXNFULL
// Description : None
#define PIO_IRQ0_INTF_SM1_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM1_TXNFULL_BITS   _u(0x00000020)
#define PIO_IRQ0_INTF_SM1_TXNFULL_MSB    _u(5)
#define PIO_IRQ0_INTF_SM1_TXNFULL_LSB    _u(5)
#define PIO_IRQ0_INTF_SM1_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM0_TXNFULL
// Description : None
#define PIO_IRQ0_INTF_SM0_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM0_TXNFULL_BITS   _u(0x00000010)
#define PIO_IRQ0_INTF_SM0_TXNFULL_MSB    _u(4)
#define PIO_IRQ0_INTF_SM0_TXNFULL_LSB    _u(4)
#define PIO_IRQ0_INTF_SM0_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTF_SM3_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM3_RXNEMPTY_BITS   _u(0x00000008)
#define PIO_IRQ0_INTF_SM3_RXNEMPTY_MSB    _u(3)
#define PIO_IRQ0_INTF_SM3_RXNEMPTY_LSB    _u(3)
#define PIO_IRQ0_INTF_SM3_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTF_SM2_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM2_RXNEMPTY_BITS   _u(0x00000004)
#define PIO_IRQ0_INTF_SM2_RXNEMPTY_MSB    _u(2)
#define PIO_IRQ0_INTF_SM2_RXNEMPTY_LSB    _u(2)
#define PIO_IRQ0_INTF_SM2_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTF_SM1_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM1_RXNEMPTY_BITS   _u(0x00000002)
#define PIO_IRQ0_INTF_SM1_RXNEMPTY_MSB    _u(1)
#define PIO_IRQ0_INTF_SM1_RXNEMPTY_LSB    _u(1)
#define PIO_IRQ0_INTF_SM1_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTF_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTF_SM0_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTF_SM0_RXNEMPTY_BITS   _u(0x00000001)
#define PIO_IRQ0_INTF_SM0_RXNEMPTY_MSB    _u(0)
#define PIO_IRQ0_INTF_SM0_RXNEMPTY_LSB    _u(0)
#define PIO_IRQ0_INTF_SM0_RXNEMPTY_ACCESS "RW"
// =============================================================================
// Register    : PIO_IRQ0_INTS
// Description : Interrupt status after masking & forcing for irq0
#define PIO_IRQ0_INTS_OFFSET _u(0x00000134)
#define PIO_IRQ0_INTS_BITS   _u(0x00000fff)
#define PIO_IRQ0_INTS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM3
// Description : None
#define PIO_IRQ0_INTS_SM3_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM3_BITS   _u(0x00000800)
#define PIO_IRQ0_INTS_SM3_MSB    _u(11)
#define PIO_IRQ0_INTS_SM3_LSB    _u(11)
#define PIO_IRQ0_INTS_SM3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM2
// Description : None
#define PIO_IRQ0_INTS_SM2_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM2_BITS   _u(0x00000400)
#define PIO_IRQ0_INTS_SM2_MSB    _u(10)
#define PIO_IRQ0_INTS_SM2_LSB    _u(10)
#define PIO_IRQ0_INTS_SM2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM1
// Description : None
#define PIO_IRQ0_INTS_SM1_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM1_BITS   _u(0x00000200)
#define PIO_IRQ0_INTS_SM1_MSB    _u(9)
#define PIO_IRQ0_INTS_SM1_LSB    _u(9)
#define PIO_IRQ0_INTS_SM1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM0
// Description : None
#define PIO_IRQ0_INTS_SM0_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM0_BITS   _u(0x00000100)
#define PIO_IRQ0_INTS_SM0_MSB    _u(8)
#define PIO_IRQ0_INTS_SM0_LSB    _u(8)
#define PIO_IRQ0_INTS_SM0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM3_TXNFULL
// Description : None
#define PIO_IRQ0_INTS_SM3_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM3_TXNFULL_BITS   _u(0x00000080)
#define PIO_IRQ0_INTS_SM3_TXNFULL_MSB    _u(7)
#define PIO_IRQ0_INTS_SM3_TXNFULL_LSB    _u(7)
#define PIO_IRQ0_INTS_SM3_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM2_TXNFULL
// Description : None
#define PIO_IRQ0_INTS_SM2_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM2_TXNFULL_BITS   _u(0x00000040)
#define PIO_IRQ0_INTS_SM2_TXNFULL_MSB    _u(6)
#define PIO_IRQ0_INTS_SM2_TXNFULL_LSB    _u(6)
#define PIO_IRQ0_INTS_SM2_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM1_TXNFULL
// Description : None
#define PIO_IRQ0_INTS_SM1_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM1_TXNFULL_BITS   _u(0x00000020)
#define PIO_IRQ0_INTS_SM1_TXNFULL_MSB    _u(5)
#define PIO_IRQ0_INTS_SM1_TXNFULL_LSB    _u(5)
#define PIO_IRQ0_INTS_SM1_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM0_TXNFULL
// Description : None
#define PIO_IRQ0_INTS_SM0_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM0_TXNFULL_BITS   _u(0x00000010)
#define PIO_IRQ0_INTS_SM0_TXNFULL_MSB    _u(4)
#define PIO_IRQ0_INTS_SM0_TXNFULL_LSB    _u(4)
#define PIO_IRQ0_INTS_SM0_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTS_SM3_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM3_RXNEMPTY_BITS   _u(0x00000008)
#define PIO_IRQ0_INTS_SM3_RXNEMPTY_MSB    _u(3)
#define PIO_IRQ0_INTS_SM3_RXNEMPTY_LSB    _u(3)
#define PIO_IRQ0_INTS_SM3_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTS_SM2_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM2_RXNEMPTY_BITS   _u(0x00000004)
#define PIO_IRQ0_INTS_SM2_RXNEMPTY_MSB    _u(2)
#define PIO_IRQ0_INTS_SM2_RXNEMPTY_LSB    _u(2)
#define PIO_IRQ0_INTS_SM2_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTS_SM1_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM1_RXNEMPTY_BITS   _u(0x00000002)
#define PIO_IRQ0_INTS_SM1_RXNEMPTY_MSB    _u(1)
#define PIO_IRQ0_INTS_SM1_RXNEMPTY_LSB    _u(1)
#define PIO_IRQ0_INTS_SM1_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ0_INTS_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ0_INTS_SM0_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ0_INTS_SM0_RXNEMPTY_BITS   _u(0x00000001)
#define PIO_IRQ0_INTS_SM0_RXNEMPTY_MSB    _u(0)
#define PIO_IRQ0_INTS_SM0_RXNEMPTY_LSB    _u(0)
#define PIO_IRQ0_INTS_SM0_RXNEMPTY_ACCESS "RO"
// =============================================================================
// Register    : PIO_IRQ1_INTE
// Description : Interrupt Enable for irq1
#define PIO_IRQ1_INTE_OFFSET _u(0x00000138)
#define PIO_IRQ1_INTE_BITS   _u(0x00000fff)
#define PIO_IRQ1_INTE_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM3
// Description : None
#define PIO_IRQ1_INTE_SM3_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM3_BITS   _u(0x00000800)
#define PIO_IRQ1_INTE_SM3_MSB    _u(11)
#define PIO_IRQ1_INTE_SM3_LSB    _u(11)
#define PIO_IRQ1_INTE_SM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM2
// Description : None
#define PIO_IRQ1_INTE_SM2_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM2_BITS   _u(0x00000400)
#define PIO_IRQ1_INTE_SM2_MSB    _u(10)
#define PIO_IRQ1_INTE_SM2_LSB    _u(10)
#define PIO_IRQ1_INTE_SM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM1
// Description : None
#define PIO_IRQ1_INTE_SM1_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM1_BITS   _u(0x00000200)
#define PIO_IRQ1_INTE_SM1_MSB    _u(9)
#define PIO_IRQ1_INTE_SM1_LSB    _u(9)
#define PIO_IRQ1_INTE_SM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM0
// Description : None
#define PIO_IRQ1_INTE_SM0_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM0_BITS   _u(0x00000100)
#define PIO_IRQ1_INTE_SM0_MSB    _u(8)
#define PIO_IRQ1_INTE_SM0_LSB    _u(8)
#define PIO_IRQ1_INTE_SM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM3_TXNFULL
// Description : None
#define PIO_IRQ1_INTE_SM3_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM3_TXNFULL_BITS   _u(0x00000080)
#define PIO_IRQ1_INTE_SM3_TXNFULL_MSB    _u(7)
#define PIO_IRQ1_INTE_SM3_TXNFULL_LSB    _u(7)
#define PIO_IRQ1_INTE_SM3_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM2_TXNFULL
// Description : None
#define PIO_IRQ1_INTE_SM2_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM2_TXNFULL_BITS   _u(0x00000040)
#define PIO_IRQ1_INTE_SM2_TXNFULL_MSB    _u(6)
#define PIO_IRQ1_INTE_SM2_TXNFULL_LSB    _u(6)
#define PIO_IRQ1_INTE_SM2_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM1_TXNFULL
// Description : None
#define PIO_IRQ1_INTE_SM1_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM1_TXNFULL_BITS   _u(0x00000020)
#define PIO_IRQ1_INTE_SM1_TXNFULL_MSB    _u(5)
#define PIO_IRQ1_INTE_SM1_TXNFULL_LSB    _u(5)
#define PIO_IRQ1_INTE_SM1_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM0_TXNFULL
// Description : None
#define PIO_IRQ1_INTE_SM0_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM0_TXNFULL_BITS   _u(0x00000010)
#define PIO_IRQ1_INTE_SM0_TXNFULL_MSB    _u(4)
#define PIO_IRQ1_INTE_SM0_TXNFULL_LSB    _u(4)
#define PIO_IRQ1_INTE_SM0_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTE_SM3_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM3_RXNEMPTY_BITS   _u(0x00000008)
#define PIO_IRQ1_INTE_SM3_RXNEMPTY_MSB    _u(3)
#define PIO_IRQ1_INTE_SM3_RXNEMPTY_LSB    _u(3)
#define PIO_IRQ1_INTE_SM3_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTE_SM2_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM2_RXNEMPTY_BITS   _u(0x00000004)
#define PIO_IRQ1_INTE_SM2_RXNEMPTY_MSB    _u(2)
#define PIO_IRQ1_INTE_SM2_RXNEMPTY_LSB    _u(2)
#define PIO_IRQ1_INTE_SM2_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTE_SM1_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM1_RXNEMPTY_BITS   _u(0x00000002)
#define PIO_IRQ1_INTE_SM1_RXNEMPTY_MSB    _u(1)
#define PIO_IRQ1_INTE_SM1_RXNEMPTY_LSB    _u(1)
#define PIO_IRQ1_INTE_SM1_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTE_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTE_SM0_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTE_SM0_RXNEMPTY_BITS   _u(0x00000001)
#define PIO_IRQ1_INTE_SM0_RXNEMPTY_MSB    _u(0)
#define PIO_IRQ1_INTE_SM0_RXNEMPTY_LSB    _u(0)
#define PIO_IRQ1_INTE_SM0_RXNEMPTY_ACCESS "RW"
// =============================================================================
// Register    : PIO_IRQ1_INTF
// Description : Interrupt Force for irq1
#define PIO_IRQ1_INTF_OFFSET _u(0x0000013c)
#define PIO_IRQ1_INTF_BITS   _u(0x00000fff)
#define PIO_IRQ1_INTF_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM3
// Description : None
#define PIO_IRQ1_INTF_SM3_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM3_BITS   _u(0x00000800)
#define PIO_IRQ1_INTF_SM3_MSB    _u(11)
#define PIO_IRQ1_INTF_SM3_LSB    _u(11)
#define PIO_IRQ1_INTF_SM3_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM2
// Description : None
#define PIO_IRQ1_INTF_SM2_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM2_BITS   _u(0x00000400)
#define PIO_IRQ1_INTF_SM2_MSB    _u(10)
#define PIO_IRQ1_INTF_SM2_LSB    _u(10)
#define PIO_IRQ1_INTF_SM2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM1
// Description : None
#define PIO_IRQ1_INTF_SM1_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM1_BITS   _u(0x00000200)
#define PIO_IRQ1_INTF_SM1_MSB    _u(9)
#define PIO_IRQ1_INTF_SM1_LSB    _u(9)
#define PIO_IRQ1_INTF_SM1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM0
// Description : None
#define PIO_IRQ1_INTF_SM0_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM0_BITS   _u(0x00000100)
#define PIO_IRQ1_INTF_SM0_MSB    _u(8)
#define PIO_IRQ1_INTF_SM0_LSB    _u(8)
#define PIO_IRQ1_INTF_SM0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM3_TXNFULL
// Description : None
#define PIO_IRQ1_INTF_SM3_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM3_TXNFULL_BITS   _u(0x00000080)
#define PIO_IRQ1_INTF_SM3_TXNFULL_MSB    _u(7)
#define PIO_IRQ1_INTF_SM3_TXNFULL_LSB    _u(7)
#define PIO_IRQ1_INTF_SM3_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM2_TXNFULL
// Description : None
#define PIO_IRQ1_INTF_SM2_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM2_TXNFULL_BITS   _u(0x00000040)
#define PIO_IRQ1_INTF_SM2_TXNFULL_MSB    _u(6)
#define PIO_IRQ1_INTF_SM2_TXNFULL_LSB    _u(6)
#define PIO_IRQ1_INTF_SM2_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM1_TXNFULL
// Description : None
#define PIO_IRQ1_INTF_SM1_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM1_TXNFULL_BITS   _u(0x00000020)
#define PIO_IRQ1_INTF_SM1_TXNFULL_MSB    _u(5)
#define PIO_IRQ1_INTF_SM1_TXNFULL_LSB    _u(5)
#define PIO_IRQ1_INTF_SM1_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM0_TXNFULL
// Description : None
#define PIO_IRQ1_INTF_SM0_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM0_TXNFULL_BITS   _u(0x00000010)
#define PIO_IRQ1_INTF_SM0_TXNFULL_MSB    _u(4)
#define PIO_IRQ1_INTF_SM0_TXNFULL_LSB    _u(4)
#define PIO_IRQ1_INTF_SM0_TXNFULL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTF_SM3_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM3_RXNEMPTY_BITS   _u(0x00000008)
#define PIO_IRQ1_INTF_SM3_RXNEMPTY_MSB    _u(3)
#define PIO_IRQ1_INTF_SM3_RXNEMPTY_LSB    _u(3)
#define PIO_IRQ1_INTF_SM3_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTF_SM2_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM2_RXNEMPTY_BITS   _u(0x00000004)
#define PIO_IRQ1_INTF_SM2_RXNEMPTY_MSB    _u(2)
#define PIO_IRQ1_INTF_SM2_RXNEMPTY_LSB    _u(2)
#define PIO_IRQ1_INTF_SM2_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTF_SM1_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM1_RXNEMPTY_BITS   _u(0x00000002)
#define PIO_IRQ1_INTF_SM1_RXNEMPTY_MSB    _u(1)
#define PIO_IRQ1_INTF_SM1_RXNEMPTY_LSB    _u(1)
#define PIO_IRQ1_INTF_SM1_RXNEMPTY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTF_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTF_SM0_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTF_SM0_RXNEMPTY_BITS   _u(0x00000001)
#define PIO_IRQ1_INTF_SM0_RXNEMPTY_MSB    _u(0)
#define PIO_IRQ1_INTF_SM0_RXNEMPTY_LSB    _u(0)
#define PIO_IRQ1_INTF_SM0_RXNEMPTY_ACCESS "RW"
// =============================================================================
// Register    : PIO_IRQ1_INTS
// Description : Interrupt status after masking & forcing for irq1
#define PIO_IRQ1_INTS_OFFSET _u(0x00000140)
#define PIO_IRQ1_INTS_BITS   _u(0x00000fff)
#define PIO_IRQ1_INTS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM3
// Description : None
#define PIO_IRQ1_INTS_SM3_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM3_BITS   _u(0x00000800)
#define PIO_IRQ1_INTS_SM3_MSB    _u(11)
#define PIO_IRQ1_INTS_SM3_LSB    _u(11)
#define PIO_IRQ1_INTS_SM3_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM2
// Description : None
#define PIO_IRQ1_INTS_SM2_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM2_BITS   _u(0x00000400)
#define PIO_IRQ1_INTS_SM2_MSB    _u(10)
#define PIO_IRQ1_INTS_SM2_LSB    _u(10)
#define PIO_IRQ1_INTS_SM2_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM1
// Description : None
#define PIO_IRQ1_INTS_SM1_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM1_BITS   _u(0x00000200)
#define PIO_IRQ1_INTS_SM1_MSB    _u(9)
#define PIO_IRQ1_INTS_SM1_LSB    _u(9)
#define PIO_IRQ1_INTS_SM1_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM0
// Description : None
#define PIO_IRQ1_INTS_SM0_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM0_BITS   _u(0x00000100)
#define PIO_IRQ1_INTS_SM0_MSB    _u(8)
#define PIO_IRQ1_INTS_SM0_LSB    _u(8)
#define PIO_IRQ1_INTS_SM0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM3_TXNFULL
// Description : None
#define PIO_IRQ1_INTS_SM3_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM3_TXNFULL_BITS   _u(0x00000080)
#define PIO_IRQ1_INTS_SM3_TXNFULL_MSB    _u(7)
#define PIO_IRQ1_INTS_SM3_TXNFULL_LSB    _u(7)
#define PIO_IRQ1_INTS_SM3_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM2_TXNFULL
// Description : None
#define PIO_IRQ1_INTS_SM2_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM2_TXNFULL_BITS   _u(0x00000040)
#define PIO_IRQ1_INTS_SM2_TXNFULL_MSB    _u(6)
#define PIO_IRQ1_INTS_SM2_TXNFULL_LSB    _u(6)
#define PIO_IRQ1_INTS_SM2_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM1_TXNFULL
// Description : None
#define PIO_IRQ1_INTS_SM1_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM1_TXNFULL_BITS   _u(0x00000020)
#define PIO_IRQ1_INTS_SM1_TXNFULL_MSB    _u(5)
#define PIO_IRQ1_INTS_SM1_TXNFULL_LSB    _u(5)
#define PIO_IRQ1_INTS_SM1_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM0_TXNFULL
// Description : None
#define PIO_IRQ1_INTS_SM0_TXNFULL_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM0_TXNFULL_BITS   _u(0x00000010)
#define PIO_IRQ1_INTS_SM0_TXNFULL_MSB    _u(4)
#define PIO_IRQ1_INTS_SM0_TXNFULL_LSB    _u(4)
#define PIO_IRQ1_INTS_SM0_TXNFULL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM3_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTS_SM3_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM3_RXNEMPTY_BITS   _u(0x00000008)
#define PIO_IRQ1_INTS_SM3_RXNEMPTY_MSB    _u(3)
#define PIO_IRQ1_INTS_SM3_RXNEMPTY_LSB    _u(3)
#define PIO_IRQ1_INTS_SM3_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM2_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTS_SM2_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM2_RXNEMPTY_BITS   _u(0x00000004)
#define PIO_IRQ1_INTS_SM2_RXNEMPTY_MSB    _u(2)
#define PIO_IRQ1_INTS_SM2_RXNEMPTY_LSB    _u(2)
#define PIO_IRQ1_INTS_SM2_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM1_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTS_SM1_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM1_RXNEMPTY_BITS   _u(0x00000002)
#define PIO_IRQ1_INTS_SM1_RXNEMPTY_MSB    _u(1)
#define PIO_IRQ1_INTS_SM1_RXNEMPTY_LSB    _u(1)
#define PIO_IRQ1_INTS_SM1_RXNEMPTY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : PIO_IRQ1_INTS_SM0_RXNEMPTY
// Description : None
#define PIO_IRQ1_INTS_SM0_RXNEMPTY_RESET  _u(0x0)
#define PIO_IRQ1_INTS_SM0_RXNEMPTY_BITS   _u(0x00000001)
#define PIO_IRQ1_INTS_SM0_RXNEMPTY_MSB    _u(0)
#define PIO_IRQ1_INTS_SM0_RXNEMPTY_LSB    _u(0)
#define PIO_IRQ1_INTS_SM0_RXNEMPTY_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_PIO_DEFINED
