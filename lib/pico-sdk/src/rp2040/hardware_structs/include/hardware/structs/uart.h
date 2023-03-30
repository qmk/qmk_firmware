// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_UART_H
#define _HARDWARE_STRUCTS_UART_H

#include "hardware/address_mapped.h"
#include "hardware/regs/uart.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_uart
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/uart.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

typedef struct {
    _REG_(UART_UARTDR_OFFSET) // UART_UARTDR
    // Data Register, UARTDR
    // 0x00000800 [11]    : OE (0): Overrun error
    // 0x00000400 [10]    : BE (0): Break error
    // 0x00000200 [9]     : PE (0): Parity error
    // 0x00000100 [8]     : FE (0): Framing error
    // 0x000000ff [7:0]   : DATA (0): Receive (read) data character
    io_rw_32 dr;

    _REG_(UART_UARTRSR_OFFSET) // UART_UARTRSR
    // Receive Status Register/Error Clear Register, UARTRSR/UARTECR
    // 0x00000008 [3]     : OE (0): Overrun error
    // 0x00000004 [2]     : BE (0): Break error
    // 0x00000002 [1]     : PE (0): Parity error
    // 0x00000001 [0]     : FE (0): Framing error
    io_rw_32 rsr;

    uint32_t _pad0[4];

    _REG_(UART_UARTFR_OFFSET) // UART_UARTFR
    // Flag Register, UARTFR
    // 0x00000100 [8]     : RI (0): Ring indicator
    // 0x00000080 [7]     : TXFE (1): Transmit FIFO empty
    // 0x00000040 [6]     : RXFF (0): Receive FIFO full
    // 0x00000020 [5]     : TXFF (0): Transmit FIFO full
    // 0x00000010 [4]     : RXFE (1): Receive FIFO empty
    // 0x00000008 [3]     : BUSY (0): UART busy
    // 0x00000004 [2]     : DCD (0): Data carrier detect
    // 0x00000002 [1]     : DSR (0): Data set ready
    // 0x00000001 [0]     : CTS (0): Clear to send
    io_ro_32 fr;

    uint32_t _pad1;

    _REG_(UART_UARTILPR_OFFSET) // UART_UARTILPR
    // IrDA Low-Power Counter Register, UARTILPR
    // 0x000000ff [7:0]   : ILPDVSR (0): 8-bit low-power divisor value
    io_rw_32 ilpr;

    _REG_(UART_UARTIBRD_OFFSET) // UART_UARTIBRD
    // Integer Baud Rate Register, UARTIBRD
    // 0x0000ffff [15:0]  : BAUD_DIVINT (0): The integer baud rate divisor
    io_rw_32 ibrd;

    _REG_(UART_UARTFBRD_OFFSET) // UART_UARTFBRD
    // Fractional Baud Rate Register, UARTFBRD
    // 0x0000003f [5:0]   : BAUD_DIVFRAC (0): The fractional baud rate divisor
    io_rw_32 fbrd;

    _REG_(UART_UARTLCR_H_OFFSET) // UART_UARTLCR_H
    // Line Control Register, UARTLCR_H
    // 0x00000080 [7]     : SPS (0): Stick parity select
    // 0x00000060 [6:5]   : WLEN (0): Word length
    // 0x00000010 [4]     : FEN (0): Enable FIFOs: 0 = FIFOs are disabled (character mode) that is, the FIFOs become...
    // 0x00000008 [3]     : STP2 (0): Two stop bits select
    // 0x00000004 [2]     : EPS (0): Even parity select
    // 0x00000002 [1]     : PEN (0): Parity enable: 0 = parity is disabled and no parity bit added to the data frame 1 =...
    // 0x00000001 [0]     : BRK (0): Send break
    io_rw_32 lcr_h;

    _REG_(UART_UARTCR_OFFSET) // UART_UARTCR
    // Control Register, UARTCR
    // 0x00008000 [15]    : CTSEN (0): CTS hardware flow control enable
    // 0x00004000 [14]    : RTSEN (0): RTS hardware flow control enable
    // 0x00002000 [13]    : OUT2 (0): This bit is the complement of the UART Out2 (nUARTOut2) modem status output
    // 0x00001000 [12]    : OUT1 (0): This bit is the complement of the UART Out1 (nUARTOut1) modem status output
    // 0x00000800 [11]    : RTS (0): Request to send
    // 0x00000400 [10]    : DTR (0): Data transmit ready
    // 0x00000200 [9]     : RXE (1): Receive enable
    // 0x00000100 [8]     : TXE (1): Transmit enable
    // 0x00000080 [7]     : LBE (0): Loopback enable
    // 0x00000004 [2]     : SIRLP (0): SIR low-power IrDA mode
    // 0x00000002 [1]     : SIREN (0): SIR enable: 0 = IrDA SIR ENDEC is disabled
    // 0x00000001 [0]     : UARTEN (0): UART enable: 0 = UART is disabled
    io_rw_32 cr;

    _REG_(UART_UARTIFLS_OFFSET) // UART_UARTIFLS
    // Interrupt FIFO Level Select Register, UARTIFLS
    // 0x00000038 [5:3]   : RXIFLSEL (0x2): Receive interrupt FIFO level select
    // 0x00000007 [2:0]   : TXIFLSEL (0x2): Transmit interrupt FIFO level select
    io_rw_32 ifls;

    _REG_(UART_UARTIMSC_OFFSET) // UART_UARTIMSC
    // Interrupt Mask Set/Clear Register, UARTIMSC
    // 0x00000400 [10]    : OEIM (0): Overrun error interrupt mask
    // 0x00000200 [9]     : BEIM (0): Break error interrupt mask
    // 0x00000100 [8]     : PEIM (0): Parity error interrupt mask
    // 0x00000080 [7]     : FEIM (0): Framing error interrupt mask
    // 0x00000040 [6]     : RTIM (0): Receive timeout interrupt mask
    // 0x00000020 [5]     : TXIM (0): Transmit interrupt mask
    // 0x00000010 [4]     : RXIM (0): Receive interrupt mask
    // 0x00000008 [3]     : DSRMIM (0): nUARTDSR modem interrupt mask
    // 0x00000004 [2]     : DCDMIM (0): nUARTDCD modem interrupt mask
    // 0x00000002 [1]     : CTSMIM (0): nUARTCTS modem interrupt mask
    // 0x00000001 [0]     : RIMIM (0): nUARTRI modem interrupt mask
    io_rw_32 imsc;

    _REG_(UART_UARTRIS_OFFSET) // UART_UARTRIS
    // Raw Interrupt Status Register, UARTRIS
    // 0x00000400 [10]    : OERIS (0): Overrun error interrupt status
    // 0x00000200 [9]     : BERIS (0): Break error interrupt status
    // 0x00000100 [8]     : PERIS (0): Parity error interrupt status
    // 0x00000080 [7]     : FERIS (0): Framing error interrupt status
    // 0x00000040 [6]     : RTRIS (0): Receive timeout interrupt status
    // 0x00000020 [5]     : TXRIS (0): Transmit interrupt status
    // 0x00000010 [4]     : RXRIS (0): Receive interrupt status
    // 0x00000008 [3]     : DSRRMIS (0): nUARTDSR modem interrupt status
    // 0x00000004 [2]     : DCDRMIS (0): nUARTDCD modem interrupt status
    // 0x00000002 [1]     : CTSRMIS (0): nUARTCTS modem interrupt status
    // 0x00000001 [0]     : RIRMIS (0): nUARTRI modem interrupt status
    io_ro_32 ris;

    _REG_(UART_UARTMIS_OFFSET) // UART_UARTMIS
    // Masked Interrupt Status Register, UARTMIS
    // 0x00000400 [10]    : OEMIS (0): Overrun error masked interrupt status
    // 0x00000200 [9]     : BEMIS (0): Break error masked interrupt status
    // 0x00000100 [8]     : PEMIS (0): Parity error masked interrupt status
    // 0x00000080 [7]     : FEMIS (0): Framing error masked interrupt status
    // 0x00000040 [6]     : RTMIS (0): Receive timeout masked interrupt status
    // 0x00000020 [5]     : TXMIS (0): Transmit masked interrupt status
    // 0x00000010 [4]     : RXMIS (0): Receive masked interrupt status
    // 0x00000008 [3]     : DSRMMIS (0): nUARTDSR modem masked interrupt status
    // 0x00000004 [2]     : DCDMMIS (0): nUARTDCD modem masked interrupt status
    // 0x00000002 [1]     : CTSMMIS (0): nUARTCTS modem masked interrupt status
    // 0x00000001 [0]     : RIMMIS (0): nUARTRI modem masked interrupt status
    io_ro_32 mis;

    _REG_(UART_UARTICR_OFFSET) // UART_UARTICR
    // Interrupt Clear Register, UARTICR
    // 0x00000400 [10]    : OEIC (0): Overrun error interrupt clear
    // 0x00000200 [9]     : BEIC (0): Break error interrupt clear
    // 0x00000100 [8]     : PEIC (0): Parity error interrupt clear
    // 0x00000080 [7]     : FEIC (0): Framing error interrupt clear
    // 0x00000040 [6]     : RTIC (0): Receive timeout interrupt clear
    // 0x00000020 [5]     : TXIC (0): Transmit interrupt clear
    // 0x00000010 [4]     : RXIC (0): Receive interrupt clear
    // 0x00000008 [3]     : DSRMIC (0): nUARTDSR modem interrupt clear
    // 0x00000004 [2]     : DCDMIC (0): nUARTDCD modem interrupt clear
    // 0x00000002 [1]     : CTSMIC (0): nUARTCTS modem interrupt clear
    // 0x00000001 [0]     : RIMIC (0): nUARTRI modem interrupt clear
    io_rw_32 icr;

    _REG_(UART_UARTDMACR_OFFSET) // UART_UARTDMACR
    // DMA Control Register, UARTDMACR
    // 0x00000004 [2]     : DMAONERR (0): DMA on error
    // 0x00000002 [1]     : TXDMAE (0): Transmit DMA enable
    // 0x00000001 [0]     : RXDMAE (0): Receive DMA enable
    io_rw_32 dmacr;
} uart_hw_t;

#define uart0_hw ((uart_hw_t *)UART0_BASE)
#define uart1_hw ((uart_hw_t *)UART1_BASE)

#endif
