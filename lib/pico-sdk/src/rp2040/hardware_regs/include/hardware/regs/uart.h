/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : UART
// Version        : 1
// Bus type       : apb
// Description    : None
// =============================================================================
#ifndef HARDWARE_REGS_UART_DEFINED
#define HARDWARE_REGS_UART_DEFINED
// =============================================================================
// Register    : UART_UARTDR
// Description : Data Register, UARTDR
#define UART_UARTDR_OFFSET _u(0x00000000)
#define UART_UARTDR_BITS   _u(0x00000fff)
#define UART_UARTDR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTDR_OE
// Description : Overrun error. This bit is set to 1 if data is received and the
//               receive FIFO is already full. This is cleared to 0 once there
//               is an empty space in the FIFO and a new character can be
//               written to it.
#define UART_UARTDR_OE_RESET  "-"
#define UART_UARTDR_OE_BITS   _u(0x00000800)
#define UART_UARTDR_OE_MSB    _u(11)
#define UART_UARTDR_OE_LSB    _u(11)
#define UART_UARTDR_OE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTDR_BE
// Description : Break error. This bit is set to 1 if a break condition was
//               detected, indicating that the received data input was held LOW
//               for longer than a full-word transmission time (defined as
//               start, data, parity and stop bits). In FIFO mode, this error is
//               associated with the character at the top of the FIFO. When a
//               break occurs, only one 0 character is loaded into the FIFO. The
//               next character is only enabled after the receive data input
//               goes to a 1 (marking state), and the next valid start bit is
//               received.
#define UART_UARTDR_BE_RESET  "-"
#define UART_UARTDR_BE_BITS   _u(0x00000400)
#define UART_UARTDR_BE_MSB    _u(10)
#define UART_UARTDR_BE_LSB    _u(10)
#define UART_UARTDR_BE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTDR_PE
// Description : Parity error. When set to 1, it indicates that the parity of
//               the received data character does not match the parity that the
//               EPS and SPS bits in the Line Control Register, UARTLCR_H. In
//               FIFO mode, this error is associated with the character at the
//               top of the FIFO.
#define UART_UARTDR_PE_RESET  "-"
#define UART_UARTDR_PE_BITS   _u(0x00000200)
#define UART_UARTDR_PE_MSB    _u(9)
#define UART_UARTDR_PE_LSB    _u(9)
#define UART_UARTDR_PE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTDR_FE
// Description : Framing error. When set to 1, it indicates that the received
//               character did not have a valid stop bit (a valid stop bit is
//               1). In FIFO mode, this error is associated with the character
//               at the top of the FIFO.
#define UART_UARTDR_FE_RESET  "-"
#define UART_UARTDR_FE_BITS   _u(0x00000100)
#define UART_UARTDR_FE_MSB    _u(8)
#define UART_UARTDR_FE_LSB    _u(8)
#define UART_UARTDR_FE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTDR_DATA
// Description : Receive (read) data character. Transmit (write) data character.
#define UART_UARTDR_DATA_RESET  "-"
#define UART_UARTDR_DATA_BITS   _u(0x000000ff)
#define UART_UARTDR_DATA_MSB    _u(7)
#define UART_UARTDR_DATA_LSB    _u(0)
#define UART_UARTDR_DATA_ACCESS "RWF"
// =============================================================================
// Register    : UART_UARTRSR
// Description : Receive Status Register/Error Clear Register, UARTRSR/UARTECR
#define UART_UARTRSR_OFFSET _u(0x00000004)
#define UART_UARTRSR_BITS   _u(0x0000000f)
#define UART_UARTRSR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTRSR_OE
// Description : Overrun error. This bit is set to 1 if data is received and the
//               FIFO is already full. This bit is cleared to 0 by a write to
//               UARTECR. The FIFO contents remain valid because no more data is
//               written when the FIFO is full, only the contents of the shift
//               register are overwritten. The CPU must now read the data, to
//               empty the FIFO.
#define UART_UARTRSR_OE_RESET  _u(0x0)
#define UART_UARTRSR_OE_BITS   _u(0x00000008)
#define UART_UARTRSR_OE_MSB    _u(3)
#define UART_UARTRSR_OE_LSB    _u(3)
#define UART_UARTRSR_OE_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRSR_BE
// Description : Break error. This bit is set to 1 if a break condition was
//               detected, indicating that the received data input was held LOW
//               for longer than a full-word transmission time (defined as
//               start, data, parity, and stop bits). This bit is cleared to 0
//               after a write to UARTECR. In FIFO mode, this error is
//               associated with the character at the top of the FIFO. When a
//               break occurs, only one 0 character is loaded into the FIFO. The
//               next character is only enabled after the receive data input
//               goes to a 1 (marking state) and the next valid start bit is
//               received.
#define UART_UARTRSR_BE_RESET  _u(0x0)
#define UART_UARTRSR_BE_BITS   _u(0x00000004)
#define UART_UARTRSR_BE_MSB    _u(2)
#define UART_UARTRSR_BE_LSB    _u(2)
#define UART_UARTRSR_BE_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRSR_PE
// Description : Parity error. When set to 1, it indicates that the parity of
//               the received data character does not match the parity that the
//               EPS and SPS bits in the Line Control Register, UARTLCR_H. This
//               bit is cleared to 0 by a write to UARTECR. In FIFO mode, this
//               error is associated with the character at the top of the FIFO.
#define UART_UARTRSR_PE_RESET  _u(0x0)
#define UART_UARTRSR_PE_BITS   _u(0x00000002)
#define UART_UARTRSR_PE_MSB    _u(1)
#define UART_UARTRSR_PE_LSB    _u(1)
#define UART_UARTRSR_PE_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRSR_FE
// Description : Framing error. When set to 1, it indicates that the received
//               character did not have a valid stop bit (a valid stop bit is
//               1). This bit is cleared to 0 by a write to UARTECR. In FIFO
//               mode, this error is associated with the character at the top of
//               the FIFO.
#define UART_UARTRSR_FE_RESET  _u(0x0)
#define UART_UARTRSR_FE_BITS   _u(0x00000001)
#define UART_UARTRSR_FE_MSB    _u(0)
#define UART_UARTRSR_FE_LSB    _u(0)
#define UART_UARTRSR_FE_ACCESS "WC"
// =============================================================================
// Register    : UART_UARTFR
// Description : Flag Register, UARTFR
#define UART_UARTFR_OFFSET _u(0x00000018)
#define UART_UARTFR_BITS   _u(0x000001ff)
#define UART_UARTFR_RESET  _u(0x00000090)
// -----------------------------------------------------------------------------
// Field       : UART_UARTFR_RI
// Description : Ring indicator. This bit is the complement of the UART ring
//               indicator, nUARTRI, modem status input. That is, the bit is 1
//               when nUARTRI is LOW.
#define UART_UARTFR_RI_RESET  "-"
#define UART_UARTFR_RI_BITS   _u(0x00000100)
#define UART_UARTFR_RI_MSB    _u(8)
#define UART_UARTFR_RI_LSB    _u(8)
#define UART_UARTFR_RI_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTFR_TXFE
// Description : Transmit FIFO empty. The meaning of this bit depends on the
//               state of the FEN bit in the Line Control Register, UARTLCR_H.
//               If the FIFO is disabled, this bit is set when the transmit
//               holding register is empty. If the FIFO is enabled, the TXFE bit
//               is set when the transmit FIFO is empty. This bit does not
//               indicate if there is data in the transmit shift register.
#define UART_UARTFR_TXFE_RESET  _u(0x1)
#define UART_UARTFR_TXFE_BITS   _u(0x00000080)
#define UART_UARTFR_TXFE_MSB    _u(7)
#define UART_UARTFR_TXFE_LSB    _u(7)
#define UART_UARTFR_TXFE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTFR_RXFF
// Description : Receive FIFO full. The meaning of this bit depends on the state
//               of the FEN bit in the UARTLCR_H Register. If the FIFO is
//               disabled, this bit is set when the receive holding register is
//               full. If the FIFO is enabled, the RXFF bit is set when the
//               receive FIFO is full.
#define UART_UARTFR_RXFF_RESET  _u(0x0)
#define UART_UARTFR_RXFF_BITS   _u(0x00000040)
#define UART_UARTFR_RXFF_MSB    _u(6)
#define UART_UARTFR_RXFF_LSB    _u(6)
#define UART_UARTFR_RXFF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTFR_TXFF
// Description : Transmit FIFO full. The meaning of this bit depends on the
//               state of the FEN bit in the UARTLCR_H Register. If the FIFO is
//               disabled, this bit is set when the transmit holding register is
//               full. If the FIFO is enabled, the TXFF bit is set when the
//               transmit FIFO is full.
#define UART_UARTFR_TXFF_RESET  _u(0x0)
#define UART_UARTFR_TXFF_BITS   _u(0x00000020)
#define UART_UARTFR_TXFF_MSB    _u(5)
#define UART_UARTFR_TXFF_LSB    _u(5)
#define UART_UARTFR_TXFF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTFR_RXFE
// Description : Receive FIFO empty. The meaning of this bit depends on the
//               state of the FEN bit in the UARTLCR_H Register. If the FIFO is
//               disabled, this bit is set when the receive holding register is
//               empty. If the FIFO is enabled, the RXFE bit is set when the
//               receive FIFO is empty.
#define UART_UARTFR_RXFE_RESET  _u(0x1)
#define UART_UARTFR_RXFE_BITS   _u(0x00000010)
#define UART_UARTFR_RXFE_MSB    _u(4)
#define UART_UARTFR_RXFE_LSB    _u(4)
#define UART_UARTFR_RXFE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTFR_BUSY
// Description : UART busy. If this bit is set to 1, the UART is busy
//               transmitting data. This bit remains set until the complete
//               byte, including all the stop bits, has been sent from the shift
//               register. This bit is set as soon as the transmit FIFO becomes
//               non-empty, regardless of whether the UART is enabled or not.
#define UART_UARTFR_BUSY_RESET  _u(0x0)
#define UART_UARTFR_BUSY_BITS   _u(0x00000008)
#define UART_UARTFR_BUSY_MSB    _u(3)
#define UART_UARTFR_BUSY_LSB    _u(3)
#define UART_UARTFR_BUSY_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTFR_DCD
// Description : Data carrier detect. This bit is the complement of the UART
//               data carrier detect, nUARTDCD, modem status input. That is, the
//               bit is 1 when nUARTDCD is LOW.
#define UART_UARTFR_DCD_RESET  "-"
#define UART_UARTFR_DCD_BITS   _u(0x00000004)
#define UART_UARTFR_DCD_MSB    _u(2)
#define UART_UARTFR_DCD_LSB    _u(2)
#define UART_UARTFR_DCD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTFR_DSR
// Description : Data set ready. This bit is the complement of the UART data set
//               ready, nUARTDSR, modem status input. That is, the bit is 1 when
//               nUARTDSR is LOW.
#define UART_UARTFR_DSR_RESET  "-"
#define UART_UARTFR_DSR_BITS   _u(0x00000002)
#define UART_UARTFR_DSR_MSB    _u(1)
#define UART_UARTFR_DSR_LSB    _u(1)
#define UART_UARTFR_DSR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTFR_CTS
// Description : Clear to send. This bit is the complement of the UART clear to
//               send, nUARTCTS, modem status input. That is, the bit is 1 when
//               nUARTCTS is LOW.
#define UART_UARTFR_CTS_RESET  "-"
#define UART_UARTFR_CTS_BITS   _u(0x00000001)
#define UART_UARTFR_CTS_MSB    _u(0)
#define UART_UARTFR_CTS_LSB    _u(0)
#define UART_UARTFR_CTS_ACCESS "RO"
// =============================================================================
// Register    : UART_UARTILPR
// Description : IrDA Low-Power Counter Register, UARTILPR
#define UART_UARTILPR_OFFSET _u(0x00000020)
#define UART_UARTILPR_BITS   _u(0x000000ff)
#define UART_UARTILPR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTILPR_ILPDVSR
// Description : 8-bit low-power divisor value. These bits are cleared to 0 at
//               reset.
#define UART_UARTILPR_ILPDVSR_RESET  _u(0x00)
#define UART_UARTILPR_ILPDVSR_BITS   _u(0x000000ff)
#define UART_UARTILPR_ILPDVSR_MSB    _u(7)
#define UART_UARTILPR_ILPDVSR_LSB    _u(0)
#define UART_UARTILPR_ILPDVSR_ACCESS "RW"
// =============================================================================
// Register    : UART_UARTIBRD
// Description : Integer Baud Rate Register, UARTIBRD
#define UART_UARTIBRD_OFFSET _u(0x00000024)
#define UART_UARTIBRD_BITS   _u(0x0000ffff)
#define UART_UARTIBRD_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTIBRD_BAUD_DIVINT
// Description : The integer baud rate divisor. These bits are cleared to 0 on
//               reset.
#define UART_UARTIBRD_BAUD_DIVINT_RESET  _u(0x0000)
#define UART_UARTIBRD_BAUD_DIVINT_BITS   _u(0x0000ffff)
#define UART_UARTIBRD_BAUD_DIVINT_MSB    _u(15)
#define UART_UARTIBRD_BAUD_DIVINT_LSB    _u(0)
#define UART_UARTIBRD_BAUD_DIVINT_ACCESS "RW"
// =============================================================================
// Register    : UART_UARTFBRD
// Description : Fractional Baud Rate Register, UARTFBRD
#define UART_UARTFBRD_OFFSET _u(0x00000028)
#define UART_UARTFBRD_BITS   _u(0x0000003f)
#define UART_UARTFBRD_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTFBRD_BAUD_DIVFRAC
// Description : The fractional baud rate divisor. These bits are cleared to 0
//               on reset.
#define UART_UARTFBRD_BAUD_DIVFRAC_RESET  _u(0x00)
#define UART_UARTFBRD_BAUD_DIVFRAC_BITS   _u(0x0000003f)
#define UART_UARTFBRD_BAUD_DIVFRAC_MSB    _u(5)
#define UART_UARTFBRD_BAUD_DIVFRAC_LSB    _u(0)
#define UART_UARTFBRD_BAUD_DIVFRAC_ACCESS "RW"
// =============================================================================
// Register    : UART_UARTLCR_H
// Description : Line Control Register, UARTLCR_H
#define UART_UARTLCR_H_OFFSET _u(0x0000002c)
#define UART_UARTLCR_H_BITS   _u(0x000000ff)
#define UART_UARTLCR_H_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTLCR_H_SPS
// Description : Stick parity select. 0 = stick parity is disabled 1 = either: *
//               if the EPS bit is 0 then the parity bit is transmitted and
//               checked as a 1 * if the EPS bit is 1 then the parity bit is
//               transmitted and checked as a 0. This bit has no effect when the
//               PEN bit disables parity checking and generation.
#define UART_UARTLCR_H_SPS_RESET  _u(0x0)
#define UART_UARTLCR_H_SPS_BITS   _u(0x00000080)
#define UART_UARTLCR_H_SPS_MSB    _u(7)
#define UART_UARTLCR_H_SPS_LSB    _u(7)
#define UART_UARTLCR_H_SPS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTLCR_H_WLEN
// Description : Word length. These bits indicate the number of data bits
//               transmitted or received in a frame as follows: b11 = 8 bits b10
//               = 7 bits b01 = 6 bits b00 = 5 bits.
#define UART_UARTLCR_H_WLEN_RESET  _u(0x0)
#define UART_UARTLCR_H_WLEN_BITS   _u(0x00000060)
#define UART_UARTLCR_H_WLEN_MSB    _u(6)
#define UART_UARTLCR_H_WLEN_LSB    _u(5)
#define UART_UARTLCR_H_WLEN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTLCR_H_FEN
// Description : Enable FIFOs: 0 = FIFOs are disabled (character mode) that is,
//               the FIFOs become 1-byte-deep holding registers 1 = transmit and
//               receive FIFO buffers are enabled (FIFO mode).
#define UART_UARTLCR_H_FEN_RESET  _u(0x0)
#define UART_UARTLCR_H_FEN_BITS   _u(0x00000010)
#define UART_UARTLCR_H_FEN_MSB    _u(4)
#define UART_UARTLCR_H_FEN_LSB    _u(4)
#define UART_UARTLCR_H_FEN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTLCR_H_STP2
// Description : Two stop bits select. If this bit is set to 1, two stop bits
//               are transmitted at the end of the frame. The receive logic does
//               not check for two stop bits being received.
#define UART_UARTLCR_H_STP2_RESET  _u(0x0)
#define UART_UARTLCR_H_STP2_BITS   _u(0x00000008)
#define UART_UARTLCR_H_STP2_MSB    _u(3)
#define UART_UARTLCR_H_STP2_LSB    _u(3)
#define UART_UARTLCR_H_STP2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTLCR_H_EPS
// Description : Even parity select. Controls the type of parity the UART uses
//               during transmission and reception: 0 = odd parity. The UART
//               generates or checks for an odd number of 1s in the data and
//               parity bits. 1 = even parity. The UART generates or checks for
//               an even number of 1s in the data and parity bits. This bit has
//               no effect when the PEN bit disables parity checking and
//               generation.
#define UART_UARTLCR_H_EPS_RESET  _u(0x0)
#define UART_UARTLCR_H_EPS_BITS   _u(0x00000004)
#define UART_UARTLCR_H_EPS_MSB    _u(2)
#define UART_UARTLCR_H_EPS_LSB    _u(2)
#define UART_UARTLCR_H_EPS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTLCR_H_PEN
// Description : Parity enable: 0 = parity is disabled and no parity bit added
//               to the data frame 1 = parity checking and generation is
//               enabled.
#define UART_UARTLCR_H_PEN_RESET  _u(0x0)
#define UART_UARTLCR_H_PEN_BITS   _u(0x00000002)
#define UART_UARTLCR_H_PEN_MSB    _u(1)
#define UART_UARTLCR_H_PEN_LSB    _u(1)
#define UART_UARTLCR_H_PEN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTLCR_H_BRK
// Description : Send break. If this bit is set to 1, a low-level is continually
//               output on the UARTTXD output, after completing transmission of
//               the current character. For the proper execution of the break
//               command, the software must set this bit for at least two
//               complete frames. For normal use, this bit must be cleared to 0.
#define UART_UARTLCR_H_BRK_RESET  _u(0x0)
#define UART_UARTLCR_H_BRK_BITS   _u(0x00000001)
#define UART_UARTLCR_H_BRK_MSB    _u(0)
#define UART_UARTLCR_H_BRK_LSB    _u(0)
#define UART_UARTLCR_H_BRK_ACCESS "RW"
// =============================================================================
// Register    : UART_UARTCR
// Description : Control Register, UARTCR
#define UART_UARTCR_OFFSET _u(0x00000030)
#define UART_UARTCR_BITS   _u(0x0000ff87)
#define UART_UARTCR_RESET  _u(0x00000300)
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_CTSEN
// Description : CTS hardware flow control enable. If this bit is set to 1, CTS
//               hardware flow control is enabled. Data is only transmitted when
//               the nUARTCTS signal is asserted.
#define UART_UARTCR_CTSEN_RESET  _u(0x0)
#define UART_UARTCR_CTSEN_BITS   _u(0x00008000)
#define UART_UARTCR_CTSEN_MSB    _u(15)
#define UART_UARTCR_CTSEN_LSB    _u(15)
#define UART_UARTCR_CTSEN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_RTSEN
// Description : RTS hardware flow control enable. If this bit is set to 1, RTS
//               hardware flow control is enabled. Data is only requested when
//               there is space in the receive FIFO for it to be received.
#define UART_UARTCR_RTSEN_RESET  _u(0x0)
#define UART_UARTCR_RTSEN_BITS   _u(0x00004000)
#define UART_UARTCR_RTSEN_MSB    _u(14)
#define UART_UARTCR_RTSEN_LSB    _u(14)
#define UART_UARTCR_RTSEN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_OUT2
// Description : This bit is the complement of the UART Out2 (nUARTOut2) modem
//               status output. That is, when the bit is programmed to a 1, the
//               output is 0. For DTE this can be used as Ring Indicator (RI).
#define UART_UARTCR_OUT2_RESET  _u(0x0)
#define UART_UARTCR_OUT2_BITS   _u(0x00002000)
#define UART_UARTCR_OUT2_MSB    _u(13)
#define UART_UARTCR_OUT2_LSB    _u(13)
#define UART_UARTCR_OUT2_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_OUT1
// Description : This bit is the complement of the UART Out1 (nUARTOut1) modem
//               status output. That is, when the bit is programmed to a 1 the
//               output is 0. For DTE this can be used as Data Carrier Detect
//               (DCD).
#define UART_UARTCR_OUT1_RESET  _u(0x0)
#define UART_UARTCR_OUT1_BITS   _u(0x00001000)
#define UART_UARTCR_OUT1_MSB    _u(12)
#define UART_UARTCR_OUT1_LSB    _u(12)
#define UART_UARTCR_OUT1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_RTS
// Description : Request to send. This bit is the complement of the UART request
//               to send, nUARTRTS, modem status output. That is, when the bit
//               is programmed to a 1 then nUARTRTS is LOW.
#define UART_UARTCR_RTS_RESET  _u(0x0)
#define UART_UARTCR_RTS_BITS   _u(0x00000800)
#define UART_UARTCR_RTS_MSB    _u(11)
#define UART_UARTCR_RTS_LSB    _u(11)
#define UART_UARTCR_RTS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_DTR
// Description : Data transmit ready. This bit is the complement of the UART
//               data transmit ready, nUARTDTR, modem status output. That is,
//               when the bit is programmed to a 1 then nUARTDTR is LOW.
#define UART_UARTCR_DTR_RESET  _u(0x0)
#define UART_UARTCR_DTR_BITS   _u(0x00000400)
#define UART_UARTCR_DTR_MSB    _u(10)
#define UART_UARTCR_DTR_LSB    _u(10)
#define UART_UARTCR_DTR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_RXE
// Description : Receive enable. If this bit is set to 1, the receive section of
//               the UART is enabled. Data reception occurs for either UART
//               signals or SIR signals depending on the setting of the SIREN
//               bit. When the UART is disabled in the middle of reception, it
//               completes the current character before stopping.
#define UART_UARTCR_RXE_RESET  _u(0x1)
#define UART_UARTCR_RXE_BITS   _u(0x00000200)
#define UART_UARTCR_RXE_MSB    _u(9)
#define UART_UARTCR_RXE_LSB    _u(9)
#define UART_UARTCR_RXE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_TXE
// Description : Transmit enable. If this bit is set to 1, the transmit section
//               of the UART is enabled. Data transmission occurs for either
//               UART signals, or SIR signals depending on the setting of the
//               SIREN bit. When the UART is disabled in the middle of
//               transmission, it completes the current character before
//               stopping.
#define UART_UARTCR_TXE_RESET  _u(0x1)
#define UART_UARTCR_TXE_BITS   _u(0x00000100)
#define UART_UARTCR_TXE_MSB    _u(8)
#define UART_UARTCR_TXE_LSB    _u(8)
#define UART_UARTCR_TXE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_LBE
// Description : Loopback enable. If this bit is set to 1 and the SIREN bit is
//               set to 1 and the SIRTEST bit in the Test Control Register,
//               UARTTCR is set to 1, then the nSIROUT path is inverted, and fed
//               through to the SIRIN path. The SIRTEST bit in the test register
//               must be set to 1 to override the normal half-duplex SIR
//               operation. This must be the requirement for accessing the test
//               registers during normal operation, and SIRTEST must be cleared
//               to 0 when loopback testing is finished. This feature reduces
//               the amount of external coupling required during system test. If
//               this bit is set to 1, and the SIRTEST bit is set to 0, the
//               UARTTXD path is fed through to the UARTRXD path. In either SIR
//               mode or UART mode, when this bit is set, the modem outputs are
//               also fed through to the modem inputs. This bit is cleared to 0
//               on reset, to disable loopback.
#define UART_UARTCR_LBE_RESET  _u(0x0)
#define UART_UARTCR_LBE_BITS   _u(0x00000080)
#define UART_UARTCR_LBE_MSB    _u(7)
#define UART_UARTCR_LBE_LSB    _u(7)
#define UART_UARTCR_LBE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_SIRLP
// Description : SIR low-power IrDA mode. This bit selects the IrDA encoding
//               mode. If this bit is cleared to 0, low-level bits are
//               transmitted as an active high pulse with a width of 3 / 16th of
//               the bit period. If this bit is set to 1, low-level bits are
//               transmitted with a pulse width that is 3 times the period of
//               the IrLPBaud16 input signal, regardless of the selected bit
//               rate. Setting this bit uses less power, but might reduce
//               transmission distances.
#define UART_UARTCR_SIRLP_RESET  _u(0x0)
#define UART_UARTCR_SIRLP_BITS   _u(0x00000004)
#define UART_UARTCR_SIRLP_MSB    _u(2)
#define UART_UARTCR_SIRLP_LSB    _u(2)
#define UART_UARTCR_SIRLP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_SIREN
// Description : SIR enable: 0 = IrDA SIR ENDEC is disabled. nSIROUT remains LOW
//               (no light pulse generated), and signal transitions on SIRIN
//               have no effect. 1 = IrDA SIR ENDEC is enabled. Data is
//               transmitted and received on nSIROUT and SIRIN. UARTTXD remains
//               HIGH, in the marking state. Signal transitions on UARTRXD or
//               modem status inputs have no effect. This bit has no effect if
//               the UARTEN bit disables the UART.
#define UART_UARTCR_SIREN_RESET  _u(0x0)
#define UART_UARTCR_SIREN_BITS   _u(0x00000002)
#define UART_UARTCR_SIREN_MSB    _u(1)
#define UART_UARTCR_SIREN_LSB    _u(1)
#define UART_UARTCR_SIREN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTCR_UARTEN
// Description : UART enable: 0 = UART is disabled. If the UART is disabled in
//               the middle of transmission or reception, it completes the
//               current character before stopping. 1 = the UART is enabled.
//               Data transmission and reception occurs for either UART signals
//               or SIR signals depending on the setting of the SIREN bit.
#define UART_UARTCR_UARTEN_RESET  _u(0x0)
#define UART_UARTCR_UARTEN_BITS   _u(0x00000001)
#define UART_UARTCR_UARTEN_MSB    _u(0)
#define UART_UARTCR_UARTEN_LSB    _u(0)
#define UART_UARTCR_UARTEN_ACCESS "RW"
// =============================================================================
// Register    : UART_UARTIFLS
// Description : Interrupt FIFO Level Select Register, UARTIFLS
#define UART_UARTIFLS_OFFSET _u(0x00000034)
#define UART_UARTIFLS_BITS   _u(0x0000003f)
#define UART_UARTIFLS_RESET  _u(0x00000012)
// -----------------------------------------------------------------------------
// Field       : UART_UARTIFLS_RXIFLSEL
// Description : Receive interrupt FIFO level select. The trigger points for the
//               receive interrupt are as follows: b000 = Receive FIFO becomes
//               >= 1 / 8 full b001 = Receive FIFO becomes >= 1 / 4 full b010 =
//               Receive FIFO becomes >= 1 / 2 full b011 = Receive FIFO becomes
//               >= 3 / 4 full b100 = Receive FIFO becomes >= 7 / 8 full
//               b101-b111 = reserved.
#define UART_UARTIFLS_RXIFLSEL_RESET  _u(0x2)
#define UART_UARTIFLS_RXIFLSEL_BITS   _u(0x00000038)
#define UART_UARTIFLS_RXIFLSEL_MSB    _u(5)
#define UART_UARTIFLS_RXIFLSEL_LSB    _u(3)
#define UART_UARTIFLS_RXIFLSEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIFLS_TXIFLSEL
// Description : Transmit interrupt FIFO level select. The trigger points for
//               the transmit interrupt are as follows: b000 = Transmit FIFO
//               becomes <= 1 / 8 full b001 = Transmit FIFO becomes <= 1 / 4
//               full b010 = Transmit FIFO becomes <= 1 / 2 full b011 = Transmit
//               FIFO becomes <= 3 / 4 full b100 = Transmit FIFO becomes <= 7 /
//               8 full b101-b111 = reserved.
#define UART_UARTIFLS_TXIFLSEL_RESET  _u(0x2)
#define UART_UARTIFLS_TXIFLSEL_BITS   _u(0x00000007)
#define UART_UARTIFLS_TXIFLSEL_MSB    _u(2)
#define UART_UARTIFLS_TXIFLSEL_LSB    _u(0)
#define UART_UARTIFLS_TXIFLSEL_ACCESS "RW"
// =============================================================================
// Register    : UART_UARTIMSC
// Description : Interrupt Mask Set/Clear Register, UARTIMSC
#define UART_UARTIMSC_OFFSET _u(0x00000038)
#define UART_UARTIMSC_BITS   _u(0x000007ff)
#define UART_UARTIMSC_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_OEIM
// Description : Overrun error interrupt mask. A read returns the current mask
//               for the UARTOEINTR interrupt. On a write of 1, the mask of the
//               UARTOEINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_OEIM_RESET  _u(0x0)
#define UART_UARTIMSC_OEIM_BITS   _u(0x00000400)
#define UART_UARTIMSC_OEIM_MSB    _u(10)
#define UART_UARTIMSC_OEIM_LSB    _u(10)
#define UART_UARTIMSC_OEIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_BEIM
// Description : Break error interrupt mask. A read returns the current mask for
//               the UARTBEINTR interrupt. On a write of 1, the mask of the
//               UARTBEINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_BEIM_RESET  _u(0x0)
#define UART_UARTIMSC_BEIM_BITS   _u(0x00000200)
#define UART_UARTIMSC_BEIM_MSB    _u(9)
#define UART_UARTIMSC_BEIM_LSB    _u(9)
#define UART_UARTIMSC_BEIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_PEIM
// Description : Parity error interrupt mask. A read returns the current mask
//               for the UARTPEINTR interrupt. On a write of 1, the mask of the
//               UARTPEINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_PEIM_RESET  _u(0x0)
#define UART_UARTIMSC_PEIM_BITS   _u(0x00000100)
#define UART_UARTIMSC_PEIM_MSB    _u(8)
#define UART_UARTIMSC_PEIM_LSB    _u(8)
#define UART_UARTIMSC_PEIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_FEIM
// Description : Framing error interrupt mask. A read returns the current mask
//               for the UARTFEINTR interrupt. On a write of 1, the mask of the
//               UARTFEINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_FEIM_RESET  _u(0x0)
#define UART_UARTIMSC_FEIM_BITS   _u(0x00000080)
#define UART_UARTIMSC_FEIM_MSB    _u(7)
#define UART_UARTIMSC_FEIM_LSB    _u(7)
#define UART_UARTIMSC_FEIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_RTIM
// Description : Receive timeout interrupt mask. A read returns the current mask
//               for the UARTRTINTR interrupt. On a write of 1, the mask of the
//               UARTRTINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_RTIM_RESET  _u(0x0)
#define UART_UARTIMSC_RTIM_BITS   _u(0x00000040)
#define UART_UARTIMSC_RTIM_MSB    _u(6)
#define UART_UARTIMSC_RTIM_LSB    _u(6)
#define UART_UARTIMSC_RTIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_TXIM
// Description : Transmit interrupt mask. A read returns the current mask for
//               the UARTTXINTR interrupt. On a write of 1, the mask of the
//               UARTTXINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_TXIM_RESET  _u(0x0)
#define UART_UARTIMSC_TXIM_BITS   _u(0x00000020)
#define UART_UARTIMSC_TXIM_MSB    _u(5)
#define UART_UARTIMSC_TXIM_LSB    _u(5)
#define UART_UARTIMSC_TXIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_RXIM
// Description : Receive interrupt mask. A read returns the current mask for the
//               UARTRXINTR interrupt. On a write of 1, the mask of the
//               UARTRXINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_RXIM_RESET  _u(0x0)
#define UART_UARTIMSC_RXIM_BITS   _u(0x00000010)
#define UART_UARTIMSC_RXIM_MSB    _u(4)
#define UART_UARTIMSC_RXIM_LSB    _u(4)
#define UART_UARTIMSC_RXIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_DSRMIM
// Description : nUARTDSR modem interrupt mask. A read returns the current mask
//               for the UARTDSRINTR interrupt. On a write of 1, the mask of the
//               UARTDSRINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_DSRMIM_RESET  _u(0x0)
#define UART_UARTIMSC_DSRMIM_BITS   _u(0x00000008)
#define UART_UARTIMSC_DSRMIM_MSB    _u(3)
#define UART_UARTIMSC_DSRMIM_LSB    _u(3)
#define UART_UARTIMSC_DSRMIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_DCDMIM
// Description : nUARTDCD modem interrupt mask. A read returns the current mask
//               for the UARTDCDINTR interrupt. On a write of 1, the mask of the
//               UARTDCDINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_DCDMIM_RESET  _u(0x0)
#define UART_UARTIMSC_DCDMIM_BITS   _u(0x00000004)
#define UART_UARTIMSC_DCDMIM_MSB    _u(2)
#define UART_UARTIMSC_DCDMIM_LSB    _u(2)
#define UART_UARTIMSC_DCDMIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_CTSMIM
// Description : nUARTCTS modem interrupt mask. A read returns the current mask
//               for the UARTCTSINTR interrupt. On a write of 1, the mask of the
//               UARTCTSINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_CTSMIM_RESET  _u(0x0)
#define UART_UARTIMSC_CTSMIM_BITS   _u(0x00000002)
#define UART_UARTIMSC_CTSMIM_MSB    _u(1)
#define UART_UARTIMSC_CTSMIM_LSB    _u(1)
#define UART_UARTIMSC_CTSMIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTIMSC_RIMIM
// Description : nUARTRI modem interrupt mask. A read returns the current mask
//               for the UARTRIINTR interrupt. On a write of 1, the mask of the
//               UARTRIINTR interrupt is set. A write of 0 clears the mask.
#define UART_UARTIMSC_RIMIM_RESET  _u(0x0)
#define UART_UARTIMSC_RIMIM_BITS   _u(0x00000001)
#define UART_UARTIMSC_RIMIM_MSB    _u(0)
#define UART_UARTIMSC_RIMIM_LSB    _u(0)
#define UART_UARTIMSC_RIMIM_ACCESS "RW"
// =============================================================================
// Register    : UART_UARTRIS
// Description : Raw Interrupt Status Register, UARTRIS
#define UART_UARTRIS_OFFSET _u(0x0000003c)
#define UART_UARTRIS_BITS   _u(0x000007ff)
#define UART_UARTRIS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_OERIS
// Description : Overrun error interrupt status. Returns the raw interrupt state
//               of the UARTOEINTR interrupt.
#define UART_UARTRIS_OERIS_RESET  _u(0x0)
#define UART_UARTRIS_OERIS_BITS   _u(0x00000400)
#define UART_UARTRIS_OERIS_MSB    _u(10)
#define UART_UARTRIS_OERIS_LSB    _u(10)
#define UART_UARTRIS_OERIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_BERIS
// Description : Break error interrupt status. Returns the raw interrupt state
//               of the UARTBEINTR interrupt.
#define UART_UARTRIS_BERIS_RESET  _u(0x0)
#define UART_UARTRIS_BERIS_BITS   _u(0x00000200)
#define UART_UARTRIS_BERIS_MSB    _u(9)
#define UART_UARTRIS_BERIS_LSB    _u(9)
#define UART_UARTRIS_BERIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_PERIS
// Description : Parity error interrupt status. Returns the raw interrupt state
//               of the UARTPEINTR interrupt.
#define UART_UARTRIS_PERIS_RESET  _u(0x0)
#define UART_UARTRIS_PERIS_BITS   _u(0x00000100)
#define UART_UARTRIS_PERIS_MSB    _u(8)
#define UART_UARTRIS_PERIS_LSB    _u(8)
#define UART_UARTRIS_PERIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_FERIS
// Description : Framing error interrupt status. Returns the raw interrupt state
//               of the UARTFEINTR interrupt.
#define UART_UARTRIS_FERIS_RESET  _u(0x0)
#define UART_UARTRIS_FERIS_BITS   _u(0x00000080)
#define UART_UARTRIS_FERIS_MSB    _u(7)
#define UART_UARTRIS_FERIS_LSB    _u(7)
#define UART_UARTRIS_FERIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_RTRIS
// Description : Receive timeout interrupt status. Returns the raw interrupt
//               state of the UARTRTINTR interrupt. a
#define UART_UARTRIS_RTRIS_RESET  _u(0x0)
#define UART_UARTRIS_RTRIS_BITS   _u(0x00000040)
#define UART_UARTRIS_RTRIS_MSB    _u(6)
#define UART_UARTRIS_RTRIS_LSB    _u(6)
#define UART_UARTRIS_RTRIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_TXRIS
// Description : Transmit interrupt status. Returns the raw interrupt state of
//               the UARTTXINTR interrupt.
#define UART_UARTRIS_TXRIS_RESET  _u(0x0)
#define UART_UARTRIS_TXRIS_BITS   _u(0x00000020)
#define UART_UARTRIS_TXRIS_MSB    _u(5)
#define UART_UARTRIS_TXRIS_LSB    _u(5)
#define UART_UARTRIS_TXRIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_RXRIS
// Description : Receive interrupt status. Returns the raw interrupt state of
//               the UARTRXINTR interrupt.
#define UART_UARTRIS_RXRIS_RESET  _u(0x0)
#define UART_UARTRIS_RXRIS_BITS   _u(0x00000010)
#define UART_UARTRIS_RXRIS_MSB    _u(4)
#define UART_UARTRIS_RXRIS_LSB    _u(4)
#define UART_UARTRIS_RXRIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_DSRRMIS
// Description : nUARTDSR modem interrupt status. Returns the raw interrupt
//               state of the UARTDSRINTR interrupt.
#define UART_UARTRIS_DSRRMIS_RESET  "-"
#define UART_UARTRIS_DSRRMIS_BITS   _u(0x00000008)
#define UART_UARTRIS_DSRRMIS_MSB    _u(3)
#define UART_UARTRIS_DSRRMIS_LSB    _u(3)
#define UART_UARTRIS_DSRRMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_DCDRMIS
// Description : nUARTDCD modem interrupt status. Returns the raw interrupt
//               state of the UARTDCDINTR interrupt.
#define UART_UARTRIS_DCDRMIS_RESET  "-"
#define UART_UARTRIS_DCDRMIS_BITS   _u(0x00000004)
#define UART_UARTRIS_DCDRMIS_MSB    _u(2)
#define UART_UARTRIS_DCDRMIS_LSB    _u(2)
#define UART_UARTRIS_DCDRMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_CTSRMIS
// Description : nUARTCTS modem interrupt status. Returns the raw interrupt
//               state of the UARTCTSINTR interrupt.
#define UART_UARTRIS_CTSRMIS_RESET  "-"
#define UART_UARTRIS_CTSRMIS_BITS   _u(0x00000002)
#define UART_UARTRIS_CTSRMIS_MSB    _u(1)
#define UART_UARTRIS_CTSRMIS_LSB    _u(1)
#define UART_UARTRIS_CTSRMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTRIS_RIRMIS
// Description : nUARTRI modem interrupt status. Returns the raw interrupt state
//               of the UARTRIINTR interrupt.
#define UART_UARTRIS_RIRMIS_RESET  "-"
#define UART_UARTRIS_RIRMIS_BITS   _u(0x00000001)
#define UART_UARTRIS_RIRMIS_MSB    _u(0)
#define UART_UARTRIS_RIRMIS_LSB    _u(0)
#define UART_UARTRIS_RIRMIS_ACCESS "RO"
// =============================================================================
// Register    : UART_UARTMIS
// Description : Masked Interrupt Status Register, UARTMIS
#define UART_UARTMIS_OFFSET _u(0x00000040)
#define UART_UARTMIS_BITS   _u(0x000007ff)
#define UART_UARTMIS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_OEMIS
// Description : Overrun error masked interrupt status. Returns the masked
//               interrupt state of the UARTOEINTR interrupt.
#define UART_UARTMIS_OEMIS_RESET  _u(0x0)
#define UART_UARTMIS_OEMIS_BITS   _u(0x00000400)
#define UART_UARTMIS_OEMIS_MSB    _u(10)
#define UART_UARTMIS_OEMIS_LSB    _u(10)
#define UART_UARTMIS_OEMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_BEMIS
// Description : Break error masked interrupt status. Returns the masked
//               interrupt state of the UARTBEINTR interrupt.
#define UART_UARTMIS_BEMIS_RESET  _u(0x0)
#define UART_UARTMIS_BEMIS_BITS   _u(0x00000200)
#define UART_UARTMIS_BEMIS_MSB    _u(9)
#define UART_UARTMIS_BEMIS_LSB    _u(9)
#define UART_UARTMIS_BEMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_PEMIS
// Description : Parity error masked interrupt status. Returns the masked
//               interrupt state of the UARTPEINTR interrupt.
#define UART_UARTMIS_PEMIS_RESET  _u(0x0)
#define UART_UARTMIS_PEMIS_BITS   _u(0x00000100)
#define UART_UARTMIS_PEMIS_MSB    _u(8)
#define UART_UARTMIS_PEMIS_LSB    _u(8)
#define UART_UARTMIS_PEMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_FEMIS
// Description : Framing error masked interrupt status. Returns the masked
//               interrupt state of the UARTFEINTR interrupt.
#define UART_UARTMIS_FEMIS_RESET  _u(0x0)
#define UART_UARTMIS_FEMIS_BITS   _u(0x00000080)
#define UART_UARTMIS_FEMIS_MSB    _u(7)
#define UART_UARTMIS_FEMIS_LSB    _u(7)
#define UART_UARTMIS_FEMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_RTMIS
// Description : Receive timeout masked interrupt status. Returns the masked
//               interrupt state of the UARTRTINTR interrupt.
#define UART_UARTMIS_RTMIS_RESET  _u(0x0)
#define UART_UARTMIS_RTMIS_BITS   _u(0x00000040)
#define UART_UARTMIS_RTMIS_MSB    _u(6)
#define UART_UARTMIS_RTMIS_LSB    _u(6)
#define UART_UARTMIS_RTMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_TXMIS
// Description : Transmit masked interrupt status. Returns the masked interrupt
//               state of the UARTTXINTR interrupt.
#define UART_UARTMIS_TXMIS_RESET  _u(0x0)
#define UART_UARTMIS_TXMIS_BITS   _u(0x00000020)
#define UART_UARTMIS_TXMIS_MSB    _u(5)
#define UART_UARTMIS_TXMIS_LSB    _u(5)
#define UART_UARTMIS_TXMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_RXMIS
// Description : Receive masked interrupt status. Returns the masked interrupt
//               state of the UARTRXINTR interrupt.
#define UART_UARTMIS_RXMIS_RESET  _u(0x0)
#define UART_UARTMIS_RXMIS_BITS   _u(0x00000010)
#define UART_UARTMIS_RXMIS_MSB    _u(4)
#define UART_UARTMIS_RXMIS_LSB    _u(4)
#define UART_UARTMIS_RXMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_DSRMMIS
// Description : nUARTDSR modem masked interrupt status. Returns the masked
//               interrupt state of the UARTDSRINTR interrupt.
#define UART_UARTMIS_DSRMMIS_RESET  "-"
#define UART_UARTMIS_DSRMMIS_BITS   _u(0x00000008)
#define UART_UARTMIS_DSRMMIS_MSB    _u(3)
#define UART_UARTMIS_DSRMMIS_LSB    _u(3)
#define UART_UARTMIS_DSRMMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_DCDMMIS
// Description : nUARTDCD modem masked interrupt status. Returns the masked
//               interrupt state of the UARTDCDINTR interrupt.
#define UART_UARTMIS_DCDMMIS_RESET  "-"
#define UART_UARTMIS_DCDMMIS_BITS   _u(0x00000004)
#define UART_UARTMIS_DCDMMIS_MSB    _u(2)
#define UART_UARTMIS_DCDMMIS_LSB    _u(2)
#define UART_UARTMIS_DCDMMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_CTSMMIS
// Description : nUARTCTS modem masked interrupt status. Returns the masked
//               interrupt state of the UARTCTSINTR interrupt.
#define UART_UARTMIS_CTSMMIS_RESET  "-"
#define UART_UARTMIS_CTSMMIS_BITS   _u(0x00000002)
#define UART_UARTMIS_CTSMMIS_MSB    _u(1)
#define UART_UARTMIS_CTSMMIS_LSB    _u(1)
#define UART_UARTMIS_CTSMMIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTMIS_RIMMIS
// Description : nUARTRI modem masked interrupt status. Returns the masked
//               interrupt state of the UARTRIINTR interrupt.
#define UART_UARTMIS_RIMMIS_RESET  "-"
#define UART_UARTMIS_RIMMIS_BITS   _u(0x00000001)
#define UART_UARTMIS_RIMMIS_MSB    _u(0)
#define UART_UARTMIS_RIMMIS_LSB    _u(0)
#define UART_UARTMIS_RIMMIS_ACCESS "RO"
// =============================================================================
// Register    : UART_UARTICR
// Description : Interrupt Clear Register, UARTICR
#define UART_UARTICR_OFFSET _u(0x00000044)
#define UART_UARTICR_BITS   _u(0x000007ff)
#define UART_UARTICR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_OEIC
// Description : Overrun error interrupt clear. Clears the UARTOEINTR interrupt.
#define UART_UARTICR_OEIC_RESET  "-"
#define UART_UARTICR_OEIC_BITS   _u(0x00000400)
#define UART_UARTICR_OEIC_MSB    _u(10)
#define UART_UARTICR_OEIC_LSB    _u(10)
#define UART_UARTICR_OEIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_BEIC
// Description : Break error interrupt clear. Clears the UARTBEINTR interrupt.
#define UART_UARTICR_BEIC_RESET  "-"
#define UART_UARTICR_BEIC_BITS   _u(0x00000200)
#define UART_UARTICR_BEIC_MSB    _u(9)
#define UART_UARTICR_BEIC_LSB    _u(9)
#define UART_UARTICR_BEIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_PEIC
// Description : Parity error interrupt clear. Clears the UARTPEINTR interrupt.
#define UART_UARTICR_PEIC_RESET  "-"
#define UART_UARTICR_PEIC_BITS   _u(0x00000100)
#define UART_UARTICR_PEIC_MSB    _u(8)
#define UART_UARTICR_PEIC_LSB    _u(8)
#define UART_UARTICR_PEIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_FEIC
// Description : Framing error interrupt clear. Clears the UARTFEINTR interrupt.
#define UART_UARTICR_FEIC_RESET  "-"
#define UART_UARTICR_FEIC_BITS   _u(0x00000080)
#define UART_UARTICR_FEIC_MSB    _u(7)
#define UART_UARTICR_FEIC_LSB    _u(7)
#define UART_UARTICR_FEIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_RTIC
// Description : Receive timeout interrupt clear. Clears the UARTRTINTR
//               interrupt.
#define UART_UARTICR_RTIC_RESET  "-"
#define UART_UARTICR_RTIC_BITS   _u(0x00000040)
#define UART_UARTICR_RTIC_MSB    _u(6)
#define UART_UARTICR_RTIC_LSB    _u(6)
#define UART_UARTICR_RTIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_TXIC
// Description : Transmit interrupt clear. Clears the UARTTXINTR interrupt.
#define UART_UARTICR_TXIC_RESET  "-"
#define UART_UARTICR_TXIC_BITS   _u(0x00000020)
#define UART_UARTICR_TXIC_MSB    _u(5)
#define UART_UARTICR_TXIC_LSB    _u(5)
#define UART_UARTICR_TXIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_RXIC
// Description : Receive interrupt clear. Clears the UARTRXINTR interrupt.
#define UART_UARTICR_RXIC_RESET  "-"
#define UART_UARTICR_RXIC_BITS   _u(0x00000010)
#define UART_UARTICR_RXIC_MSB    _u(4)
#define UART_UARTICR_RXIC_LSB    _u(4)
#define UART_UARTICR_RXIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_DSRMIC
// Description : nUARTDSR modem interrupt clear. Clears the UARTDSRINTR
//               interrupt.
#define UART_UARTICR_DSRMIC_RESET  "-"
#define UART_UARTICR_DSRMIC_BITS   _u(0x00000008)
#define UART_UARTICR_DSRMIC_MSB    _u(3)
#define UART_UARTICR_DSRMIC_LSB    _u(3)
#define UART_UARTICR_DSRMIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_DCDMIC
// Description : nUARTDCD modem interrupt clear. Clears the UARTDCDINTR
//               interrupt.
#define UART_UARTICR_DCDMIC_RESET  "-"
#define UART_UARTICR_DCDMIC_BITS   _u(0x00000004)
#define UART_UARTICR_DCDMIC_MSB    _u(2)
#define UART_UARTICR_DCDMIC_LSB    _u(2)
#define UART_UARTICR_DCDMIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_CTSMIC
// Description : nUARTCTS modem interrupt clear. Clears the UARTCTSINTR
//               interrupt.
#define UART_UARTICR_CTSMIC_RESET  "-"
#define UART_UARTICR_CTSMIC_BITS   _u(0x00000002)
#define UART_UARTICR_CTSMIC_MSB    _u(1)
#define UART_UARTICR_CTSMIC_LSB    _u(1)
#define UART_UARTICR_CTSMIC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : UART_UARTICR_RIMIC
// Description : nUARTRI modem interrupt clear. Clears the UARTRIINTR interrupt.
#define UART_UARTICR_RIMIC_RESET  "-"
#define UART_UARTICR_RIMIC_BITS   _u(0x00000001)
#define UART_UARTICR_RIMIC_MSB    _u(0)
#define UART_UARTICR_RIMIC_LSB    _u(0)
#define UART_UARTICR_RIMIC_ACCESS "WC"
// =============================================================================
// Register    : UART_UARTDMACR
// Description : DMA Control Register, UARTDMACR
#define UART_UARTDMACR_OFFSET _u(0x00000048)
#define UART_UARTDMACR_BITS   _u(0x00000007)
#define UART_UARTDMACR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTDMACR_DMAONERR
// Description : DMA on error. If this bit is set to 1, the DMA receive request
//               outputs, UARTRXDMASREQ or UARTRXDMABREQ, are disabled when the
//               UART error interrupt is asserted.
#define UART_UARTDMACR_DMAONERR_RESET  _u(0x0)
#define UART_UARTDMACR_DMAONERR_BITS   _u(0x00000004)
#define UART_UARTDMACR_DMAONERR_MSB    _u(2)
#define UART_UARTDMACR_DMAONERR_LSB    _u(2)
#define UART_UARTDMACR_DMAONERR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTDMACR_TXDMAE
// Description : Transmit DMA enable. If this bit is set to 1, DMA for the
//               transmit FIFO is enabled.
#define UART_UARTDMACR_TXDMAE_RESET  _u(0x0)
#define UART_UARTDMACR_TXDMAE_BITS   _u(0x00000002)
#define UART_UARTDMACR_TXDMAE_MSB    _u(1)
#define UART_UARTDMACR_TXDMAE_LSB    _u(1)
#define UART_UARTDMACR_TXDMAE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : UART_UARTDMACR_RXDMAE
// Description : Receive DMA enable. If this bit is set to 1, DMA for the
//               receive FIFO is enabled.
#define UART_UARTDMACR_RXDMAE_RESET  _u(0x0)
#define UART_UARTDMACR_RXDMAE_BITS   _u(0x00000001)
#define UART_UARTDMACR_RXDMAE_MSB    _u(0)
#define UART_UARTDMACR_RXDMAE_LSB    _u(0)
#define UART_UARTDMACR_RXDMAE_ACCESS "RW"
// =============================================================================
// Register    : UART_UARTPERIPHID0
// Description : UARTPeriphID0 Register
#define UART_UARTPERIPHID0_OFFSET _u(0x00000fe0)
#define UART_UARTPERIPHID0_BITS   _u(0x000000ff)
#define UART_UARTPERIPHID0_RESET  _u(0x00000011)
// -----------------------------------------------------------------------------
// Field       : UART_UARTPERIPHID0_PARTNUMBER0
// Description : These bits read back as 0x11
#define UART_UARTPERIPHID0_PARTNUMBER0_RESET  _u(0x11)
#define UART_UARTPERIPHID0_PARTNUMBER0_BITS   _u(0x000000ff)
#define UART_UARTPERIPHID0_PARTNUMBER0_MSB    _u(7)
#define UART_UARTPERIPHID0_PARTNUMBER0_LSB    _u(0)
#define UART_UARTPERIPHID0_PARTNUMBER0_ACCESS "RO"
// =============================================================================
// Register    : UART_UARTPERIPHID1
// Description : UARTPeriphID1 Register
#define UART_UARTPERIPHID1_OFFSET _u(0x00000fe4)
#define UART_UARTPERIPHID1_BITS   _u(0x000000ff)
#define UART_UARTPERIPHID1_RESET  _u(0x00000010)
// -----------------------------------------------------------------------------
// Field       : UART_UARTPERIPHID1_DESIGNER0
// Description : These bits read back as 0x1
#define UART_UARTPERIPHID1_DESIGNER0_RESET  _u(0x1)
#define UART_UARTPERIPHID1_DESIGNER0_BITS   _u(0x000000f0)
#define UART_UARTPERIPHID1_DESIGNER0_MSB    _u(7)
#define UART_UARTPERIPHID1_DESIGNER0_LSB    _u(4)
#define UART_UARTPERIPHID1_DESIGNER0_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTPERIPHID1_PARTNUMBER1
// Description : These bits read back as 0x0
#define UART_UARTPERIPHID1_PARTNUMBER1_RESET  _u(0x0)
#define UART_UARTPERIPHID1_PARTNUMBER1_BITS   _u(0x0000000f)
#define UART_UARTPERIPHID1_PARTNUMBER1_MSB    _u(3)
#define UART_UARTPERIPHID1_PARTNUMBER1_LSB    _u(0)
#define UART_UARTPERIPHID1_PARTNUMBER1_ACCESS "RO"
// =============================================================================
// Register    : UART_UARTPERIPHID2
// Description : UARTPeriphID2 Register
#define UART_UARTPERIPHID2_OFFSET _u(0x00000fe8)
#define UART_UARTPERIPHID2_BITS   _u(0x000000ff)
#define UART_UARTPERIPHID2_RESET  _u(0x00000034)
// -----------------------------------------------------------------------------
// Field       : UART_UARTPERIPHID2_REVISION
// Description : This field depends on the revision of the UART: r1p0 0x0 r1p1
//               0x1 r1p3 0x2 r1p4 0x2 r1p5 0x3
#define UART_UARTPERIPHID2_REVISION_RESET  _u(0x3)
#define UART_UARTPERIPHID2_REVISION_BITS   _u(0x000000f0)
#define UART_UARTPERIPHID2_REVISION_MSB    _u(7)
#define UART_UARTPERIPHID2_REVISION_LSB    _u(4)
#define UART_UARTPERIPHID2_REVISION_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : UART_UARTPERIPHID2_DESIGNER1
// Description : These bits read back as 0x4
#define UART_UARTPERIPHID2_DESIGNER1_RESET  _u(0x4)
#define UART_UARTPERIPHID2_DESIGNER1_BITS   _u(0x0000000f)
#define UART_UARTPERIPHID2_DESIGNER1_MSB    _u(3)
#define UART_UARTPERIPHID2_DESIGNER1_LSB    _u(0)
#define UART_UARTPERIPHID2_DESIGNER1_ACCESS "RO"
// =============================================================================
// Register    : UART_UARTPERIPHID3
// Description : UARTPeriphID3 Register
#define UART_UARTPERIPHID3_OFFSET _u(0x00000fec)
#define UART_UARTPERIPHID3_BITS   _u(0x000000ff)
#define UART_UARTPERIPHID3_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : UART_UARTPERIPHID3_CONFIGURATION
// Description : These bits read back as 0x00
#define UART_UARTPERIPHID3_CONFIGURATION_RESET  _u(0x00)
#define UART_UARTPERIPHID3_CONFIGURATION_BITS   _u(0x000000ff)
#define UART_UARTPERIPHID3_CONFIGURATION_MSB    _u(7)
#define UART_UARTPERIPHID3_CONFIGURATION_LSB    _u(0)
#define UART_UARTPERIPHID3_CONFIGURATION_ACCESS "RO"
// =============================================================================
// Register    : UART_UARTPCELLID0
// Description : UARTPCellID0 Register
#define UART_UARTPCELLID0_OFFSET _u(0x00000ff0)
#define UART_UARTPCELLID0_BITS   _u(0x000000ff)
#define UART_UARTPCELLID0_RESET  _u(0x0000000d)
// -----------------------------------------------------------------------------
// Field       : UART_UARTPCELLID0_UARTPCELLID0
// Description : These bits read back as 0x0D
#define UART_UARTPCELLID0_UARTPCELLID0_RESET  _u(0x0d)
#define UART_UARTPCELLID0_UARTPCELLID0_BITS   _u(0x000000ff)
#define UART_UARTPCELLID0_UARTPCELLID0_MSB    _u(7)
#define UART_UARTPCELLID0_UARTPCELLID0_LSB    _u(0)
#define UART_UARTPCELLID0_UARTPCELLID0_ACCESS "RO"
// =============================================================================
// Register    : UART_UARTPCELLID1
// Description : UARTPCellID1 Register
#define UART_UARTPCELLID1_OFFSET _u(0x00000ff4)
#define UART_UARTPCELLID1_BITS   _u(0x000000ff)
#define UART_UARTPCELLID1_RESET  _u(0x000000f0)
// -----------------------------------------------------------------------------
// Field       : UART_UARTPCELLID1_UARTPCELLID1
// Description : These bits read back as 0xF0
#define UART_UARTPCELLID1_UARTPCELLID1_RESET  _u(0xf0)
#define UART_UARTPCELLID1_UARTPCELLID1_BITS   _u(0x000000ff)
#define UART_UARTPCELLID1_UARTPCELLID1_MSB    _u(7)
#define UART_UARTPCELLID1_UARTPCELLID1_LSB    _u(0)
#define UART_UARTPCELLID1_UARTPCELLID1_ACCESS "RO"
// =============================================================================
// Register    : UART_UARTPCELLID2
// Description : UARTPCellID2 Register
#define UART_UARTPCELLID2_OFFSET _u(0x00000ff8)
#define UART_UARTPCELLID2_BITS   _u(0x000000ff)
#define UART_UARTPCELLID2_RESET  _u(0x00000005)
// -----------------------------------------------------------------------------
// Field       : UART_UARTPCELLID2_UARTPCELLID2
// Description : These bits read back as 0x05
#define UART_UARTPCELLID2_UARTPCELLID2_RESET  _u(0x05)
#define UART_UARTPCELLID2_UARTPCELLID2_BITS   _u(0x000000ff)
#define UART_UARTPCELLID2_UARTPCELLID2_MSB    _u(7)
#define UART_UARTPCELLID2_UARTPCELLID2_LSB    _u(0)
#define UART_UARTPCELLID2_UARTPCELLID2_ACCESS "RO"
// =============================================================================
// Register    : UART_UARTPCELLID3
// Description : UARTPCellID3 Register
#define UART_UARTPCELLID3_OFFSET _u(0x00000ffc)
#define UART_UARTPCELLID3_BITS   _u(0x000000ff)
#define UART_UARTPCELLID3_RESET  _u(0x000000b1)
// -----------------------------------------------------------------------------
// Field       : UART_UARTPCELLID3_UARTPCELLID3
// Description : These bits read back as 0xB1
#define UART_UARTPCELLID3_UARTPCELLID3_RESET  _u(0xb1)
#define UART_UARTPCELLID3_UARTPCELLID3_BITS   _u(0x000000ff)
#define UART_UARTPCELLID3_UARTPCELLID3_MSB    _u(7)
#define UART_UARTPCELLID3_UARTPCELLID3_LSB    _u(0)
#define UART_UARTPCELLID3_UARTPCELLID3_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_UART_DEFINED
