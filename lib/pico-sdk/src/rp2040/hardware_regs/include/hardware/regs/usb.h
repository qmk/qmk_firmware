/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : USB
// Version        : 1
// Bus type       : ahbl
// Description    : USB FS/LS controller device registers
// =============================================================================
#ifndef HARDWARE_REGS_USB_DEFINED
#define HARDWARE_REGS_USB_DEFINED
// =============================================================================
// Register    : USB_ADDR_ENDP
// Description : Device address and endpoint control
#define USB_ADDR_ENDP_OFFSET _u(0x00000000)
#define USB_ADDR_ENDP_BITS   _u(0x000f007f)
#define USB_ADDR_ENDP_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP_ENDPOINT
// Description : Device endpoint to send data to. Only valid for HOST mode.
#define USB_ADDR_ENDP_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP_ADDRESS
// Description : In device mode, the address that the device should respond to.
//               Set in response to a SET_ADDR setup packet from the host. In
//               host mode set to the address of the device to communicate with.
#define USB_ADDR_ENDP_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP1
// Description : Interrupt endpoint 1. Only valid for HOST mode.
#define USB_ADDR_ENDP1_OFFSET _u(0x00000004)
#define USB_ADDR_ENDP1_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP1_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP1_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP1_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP1_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP1_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP1_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP1_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP1_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP1_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP1_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP1_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP1_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP1_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP1_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP1_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP1_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP1_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP1_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP1_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP1_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP1_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP1_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP1_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP1_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP1_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP2
// Description : Interrupt endpoint 2. Only valid for HOST mode.
#define USB_ADDR_ENDP2_OFFSET _u(0x00000008)
#define USB_ADDR_ENDP2_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP2_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP2_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP2_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP2_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP2_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP2_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP2_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP2_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP2_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP2_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP2_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP2_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP2_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP2_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP2_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP2_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP2_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP2_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP2_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP2_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP2_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP2_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP2_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP2_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP2_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP3
// Description : Interrupt endpoint 3. Only valid for HOST mode.
#define USB_ADDR_ENDP3_OFFSET _u(0x0000000c)
#define USB_ADDR_ENDP3_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP3_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP3_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP3_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP3_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP3_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP3_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP3_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP3_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP3_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP3_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP3_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP3_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP3_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP3_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP3_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP3_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP3_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP3_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP3_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP3_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP3_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP3_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP3_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP3_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP3_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP4
// Description : Interrupt endpoint 4. Only valid for HOST mode.
#define USB_ADDR_ENDP4_OFFSET _u(0x00000010)
#define USB_ADDR_ENDP4_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP4_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP4_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP4_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP4_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP4_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP4_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP4_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP4_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP4_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP4_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP4_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP4_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP4_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP4_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP4_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP4_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP4_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP4_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP4_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP4_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP4_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP4_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP4_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP4_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP4_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP5
// Description : Interrupt endpoint 5. Only valid for HOST mode.
#define USB_ADDR_ENDP5_OFFSET _u(0x00000014)
#define USB_ADDR_ENDP5_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP5_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP5_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP5_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP5_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP5_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP5_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP5_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP5_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP5_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP5_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP5_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP5_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP5_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP5_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP5_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP5_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP5_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP5_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP5_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP5_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP5_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP5_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP5_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP5_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP5_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP6
// Description : Interrupt endpoint 6. Only valid for HOST mode.
#define USB_ADDR_ENDP6_OFFSET _u(0x00000018)
#define USB_ADDR_ENDP6_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP6_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP6_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP6_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP6_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP6_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP6_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP6_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP6_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP6_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP6_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP6_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP6_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP6_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP6_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP6_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP6_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP6_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP6_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP6_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP6_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP6_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP6_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP6_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP6_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP6_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP7
// Description : Interrupt endpoint 7. Only valid for HOST mode.
#define USB_ADDR_ENDP7_OFFSET _u(0x0000001c)
#define USB_ADDR_ENDP7_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP7_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP7_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP7_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP7_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP7_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP7_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP7_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP7_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP7_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP7_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP7_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP7_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP7_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP7_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP7_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP7_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP7_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP7_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP7_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP7_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP7_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP7_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP7_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP7_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP7_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP8
// Description : Interrupt endpoint 8. Only valid for HOST mode.
#define USB_ADDR_ENDP8_OFFSET _u(0x00000020)
#define USB_ADDR_ENDP8_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP8_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP8_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP8_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP8_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP8_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP8_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP8_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP8_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP8_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP8_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP8_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP8_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP8_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP8_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP8_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP8_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP8_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP8_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP8_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP8_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP8_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP8_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP8_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP8_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP8_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP9
// Description : Interrupt endpoint 9. Only valid for HOST mode.
#define USB_ADDR_ENDP9_OFFSET _u(0x00000024)
#define USB_ADDR_ENDP9_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP9_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP9_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP9_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP9_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP9_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP9_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP9_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP9_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP9_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP9_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP9_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP9_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP9_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP9_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP9_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP9_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP9_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP9_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP9_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP9_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP9_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP9_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP9_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP9_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP9_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP10
// Description : Interrupt endpoint 10. Only valid for HOST mode.
#define USB_ADDR_ENDP10_OFFSET _u(0x00000028)
#define USB_ADDR_ENDP10_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP10_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP10_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP10_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP10_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP10_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP10_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP10_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP10_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP10_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP10_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP10_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP10_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP10_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP10_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP10_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP10_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP10_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP10_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP10_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP10_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP10_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP10_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP10_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP10_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP10_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP11
// Description : Interrupt endpoint 11. Only valid for HOST mode.
#define USB_ADDR_ENDP11_OFFSET _u(0x0000002c)
#define USB_ADDR_ENDP11_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP11_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP11_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP11_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP11_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP11_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP11_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP11_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP11_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP11_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP11_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP11_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP11_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP11_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP11_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP11_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP11_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP11_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP11_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP11_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP11_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP11_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP11_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP11_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP11_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP11_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP12
// Description : Interrupt endpoint 12. Only valid for HOST mode.
#define USB_ADDR_ENDP12_OFFSET _u(0x00000030)
#define USB_ADDR_ENDP12_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP12_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP12_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP12_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP12_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP12_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP12_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP12_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP12_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP12_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP12_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP12_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP12_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP12_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP12_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP12_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP12_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP12_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP12_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP12_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP12_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP12_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP12_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP12_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP12_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP12_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP13
// Description : Interrupt endpoint 13. Only valid for HOST mode.
#define USB_ADDR_ENDP13_OFFSET _u(0x00000034)
#define USB_ADDR_ENDP13_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP13_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP13_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP13_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP13_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP13_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP13_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP13_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP13_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP13_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP13_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP13_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP13_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP13_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP13_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP13_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP13_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP13_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP13_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP13_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP13_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP13_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP13_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP13_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP13_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP13_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP14
// Description : Interrupt endpoint 14. Only valid for HOST mode.
#define USB_ADDR_ENDP14_OFFSET _u(0x00000038)
#define USB_ADDR_ENDP14_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP14_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP14_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP14_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP14_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP14_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP14_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP14_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP14_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP14_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP14_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP14_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP14_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP14_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP14_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP14_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP14_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP14_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP14_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP14_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP14_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP14_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP14_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP14_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP14_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP14_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_ADDR_ENDP15
// Description : Interrupt endpoint 15. Only valid for HOST mode.
#define USB_ADDR_ENDP15_OFFSET _u(0x0000003c)
#define USB_ADDR_ENDP15_BITS   _u(0x060f007f)
#define USB_ADDR_ENDP15_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP15_INTEP_PREAMBLE
// Description : Interrupt EP requires preamble (is a low speed device on a full
//               speed hub)
#define USB_ADDR_ENDP15_INTEP_PREAMBLE_RESET  _u(0x0)
#define USB_ADDR_ENDP15_INTEP_PREAMBLE_BITS   _u(0x04000000)
#define USB_ADDR_ENDP15_INTEP_PREAMBLE_MSB    _u(26)
#define USB_ADDR_ENDP15_INTEP_PREAMBLE_LSB    _u(26)
#define USB_ADDR_ENDP15_INTEP_PREAMBLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP15_INTEP_DIR
// Description : Direction of the interrupt endpoint. In=0, Out=1
#define USB_ADDR_ENDP15_INTEP_DIR_RESET  _u(0x0)
#define USB_ADDR_ENDP15_INTEP_DIR_BITS   _u(0x02000000)
#define USB_ADDR_ENDP15_INTEP_DIR_MSB    _u(25)
#define USB_ADDR_ENDP15_INTEP_DIR_LSB    _u(25)
#define USB_ADDR_ENDP15_INTEP_DIR_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP15_ENDPOINT
// Description : Endpoint number of the interrupt endpoint
#define USB_ADDR_ENDP15_ENDPOINT_RESET  _u(0x0)
#define USB_ADDR_ENDP15_ENDPOINT_BITS   _u(0x000f0000)
#define USB_ADDR_ENDP15_ENDPOINT_MSB    _u(19)
#define USB_ADDR_ENDP15_ENDPOINT_LSB    _u(16)
#define USB_ADDR_ENDP15_ENDPOINT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_ADDR_ENDP15_ADDRESS
// Description : Device address
#define USB_ADDR_ENDP15_ADDRESS_RESET  _u(0x00)
#define USB_ADDR_ENDP15_ADDRESS_BITS   _u(0x0000007f)
#define USB_ADDR_ENDP15_ADDRESS_MSB    _u(6)
#define USB_ADDR_ENDP15_ADDRESS_LSB    _u(0)
#define USB_ADDR_ENDP15_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_MAIN_CTRL
// Description : Main control register
#define USB_MAIN_CTRL_OFFSET _u(0x00000040)
#define USB_MAIN_CTRL_BITS   _u(0x80000003)
#define USB_MAIN_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_MAIN_CTRL_SIM_TIMING
// Description : Reduced timings for simulation
#define USB_MAIN_CTRL_SIM_TIMING_RESET  _u(0x0)
#define USB_MAIN_CTRL_SIM_TIMING_BITS   _u(0x80000000)
#define USB_MAIN_CTRL_SIM_TIMING_MSB    _u(31)
#define USB_MAIN_CTRL_SIM_TIMING_LSB    _u(31)
#define USB_MAIN_CTRL_SIM_TIMING_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_MAIN_CTRL_HOST_NDEVICE
// Description : Device mode = 0, Host mode = 1
#define USB_MAIN_CTRL_HOST_NDEVICE_RESET  _u(0x0)
#define USB_MAIN_CTRL_HOST_NDEVICE_BITS   _u(0x00000002)
#define USB_MAIN_CTRL_HOST_NDEVICE_MSB    _u(1)
#define USB_MAIN_CTRL_HOST_NDEVICE_LSB    _u(1)
#define USB_MAIN_CTRL_HOST_NDEVICE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_MAIN_CTRL_CONTROLLER_EN
// Description : Enable controller
#define USB_MAIN_CTRL_CONTROLLER_EN_RESET  _u(0x0)
#define USB_MAIN_CTRL_CONTROLLER_EN_BITS   _u(0x00000001)
#define USB_MAIN_CTRL_CONTROLLER_EN_MSB    _u(0)
#define USB_MAIN_CTRL_CONTROLLER_EN_LSB    _u(0)
#define USB_MAIN_CTRL_CONTROLLER_EN_ACCESS "RW"
// =============================================================================
// Register    : USB_SOF_WR
// Description : Set the SOF (Start of Frame) frame number in the host
//               controller. The SOF packet is sent every 1ms and the host will
//               increment the frame number by 1 each time.
#define USB_SOF_WR_OFFSET _u(0x00000044)
#define USB_SOF_WR_BITS   _u(0x000007ff)
#define USB_SOF_WR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_SOF_WR_COUNT
// Description : None
#define USB_SOF_WR_COUNT_RESET  _u(0x000)
#define USB_SOF_WR_COUNT_BITS   _u(0x000007ff)
#define USB_SOF_WR_COUNT_MSB    _u(10)
#define USB_SOF_WR_COUNT_LSB    _u(0)
#define USB_SOF_WR_COUNT_ACCESS "WF"
// =============================================================================
// Register    : USB_SOF_RD
// Description : Read the last SOF (Start of Frame) frame number seen. In device
//               mode the last SOF received from the host. In host mode the last
//               SOF sent by the host.
#define USB_SOF_RD_OFFSET _u(0x00000048)
#define USB_SOF_RD_BITS   _u(0x000007ff)
#define USB_SOF_RD_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_SOF_RD_COUNT
// Description : None
#define USB_SOF_RD_COUNT_RESET  _u(0x000)
#define USB_SOF_RD_COUNT_BITS   _u(0x000007ff)
#define USB_SOF_RD_COUNT_MSB    _u(10)
#define USB_SOF_RD_COUNT_LSB    _u(0)
#define USB_SOF_RD_COUNT_ACCESS "RO"
// =============================================================================
// Register    : USB_SIE_CTRL
// Description : SIE control register
#define USB_SIE_CTRL_OFFSET _u(0x0000004c)
#define USB_SIE_CTRL_BITS   _u(0xff07bf5f)
#define USB_SIE_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_EP0_INT_STALL
// Description : Device: Set bit in EP_STATUS_STALL_NAK when EP0 sends a STALL
#define USB_SIE_CTRL_EP0_INT_STALL_RESET  _u(0x0)
#define USB_SIE_CTRL_EP0_INT_STALL_BITS   _u(0x80000000)
#define USB_SIE_CTRL_EP0_INT_STALL_MSB    _u(31)
#define USB_SIE_CTRL_EP0_INT_STALL_LSB    _u(31)
#define USB_SIE_CTRL_EP0_INT_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_EP0_DOUBLE_BUF
// Description : Device: EP0 single buffered = 0, double buffered = 1
#define USB_SIE_CTRL_EP0_DOUBLE_BUF_RESET  _u(0x0)
#define USB_SIE_CTRL_EP0_DOUBLE_BUF_BITS   _u(0x40000000)
#define USB_SIE_CTRL_EP0_DOUBLE_BUF_MSB    _u(30)
#define USB_SIE_CTRL_EP0_DOUBLE_BUF_LSB    _u(30)
#define USB_SIE_CTRL_EP0_DOUBLE_BUF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_EP0_INT_1BUF
// Description : Device: Set bit in BUFF_STATUS for every buffer completed on
//               EP0
#define USB_SIE_CTRL_EP0_INT_1BUF_RESET  _u(0x0)
#define USB_SIE_CTRL_EP0_INT_1BUF_BITS   _u(0x20000000)
#define USB_SIE_CTRL_EP0_INT_1BUF_MSB    _u(29)
#define USB_SIE_CTRL_EP0_INT_1BUF_LSB    _u(29)
#define USB_SIE_CTRL_EP0_INT_1BUF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_EP0_INT_2BUF
// Description : Device: Set bit in BUFF_STATUS for every 2 buffers completed on
//               EP0
#define USB_SIE_CTRL_EP0_INT_2BUF_RESET  _u(0x0)
#define USB_SIE_CTRL_EP0_INT_2BUF_BITS   _u(0x10000000)
#define USB_SIE_CTRL_EP0_INT_2BUF_MSB    _u(28)
#define USB_SIE_CTRL_EP0_INT_2BUF_LSB    _u(28)
#define USB_SIE_CTRL_EP0_INT_2BUF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_EP0_INT_NAK
// Description : Device: Set bit in EP_STATUS_STALL_NAK when EP0 sends a NAK
#define USB_SIE_CTRL_EP0_INT_NAK_RESET  _u(0x0)
#define USB_SIE_CTRL_EP0_INT_NAK_BITS   _u(0x08000000)
#define USB_SIE_CTRL_EP0_INT_NAK_MSB    _u(27)
#define USB_SIE_CTRL_EP0_INT_NAK_LSB    _u(27)
#define USB_SIE_CTRL_EP0_INT_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_DIRECT_EN
// Description : Direct bus drive enable
#define USB_SIE_CTRL_DIRECT_EN_RESET  _u(0x0)
#define USB_SIE_CTRL_DIRECT_EN_BITS   _u(0x04000000)
#define USB_SIE_CTRL_DIRECT_EN_MSB    _u(26)
#define USB_SIE_CTRL_DIRECT_EN_LSB    _u(26)
#define USB_SIE_CTRL_DIRECT_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_DIRECT_DP
// Description : Direct control of DP
#define USB_SIE_CTRL_DIRECT_DP_RESET  _u(0x0)
#define USB_SIE_CTRL_DIRECT_DP_BITS   _u(0x02000000)
#define USB_SIE_CTRL_DIRECT_DP_MSB    _u(25)
#define USB_SIE_CTRL_DIRECT_DP_LSB    _u(25)
#define USB_SIE_CTRL_DIRECT_DP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_DIRECT_DM
// Description : Direct control of DM
#define USB_SIE_CTRL_DIRECT_DM_RESET  _u(0x0)
#define USB_SIE_CTRL_DIRECT_DM_BITS   _u(0x01000000)
#define USB_SIE_CTRL_DIRECT_DM_MSB    _u(24)
#define USB_SIE_CTRL_DIRECT_DM_LSB    _u(24)
#define USB_SIE_CTRL_DIRECT_DM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_TRANSCEIVER_PD
// Description : Power down bus transceiver
#define USB_SIE_CTRL_TRANSCEIVER_PD_RESET  _u(0x0)
#define USB_SIE_CTRL_TRANSCEIVER_PD_BITS   _u(0x00040000)
#define USB_SIE_CTRL_TRANSCEIVER_PD_MSB    _u(18)
#define USB_SIE_CTRL_TRANSCEIVER_PD_LSB    _u(18)
#define USB_SIE_CTRL_TRANSCEIVER_PD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_RPU_OPT
// Description : Device: Pull-up strength (0=1K2, 1=2k3)
#define USB_SIE_CTRL_RPU_OPT_RESET  _u(0x0)
#define USB_SIE_CTRL_RPU_OPT_BITS   _u(0x00020000)
#define USB_SIE_CTRL_RPU_OPT_MSB    _u(17)
#define USB_SIE_CTRL_RPU_OPT_LSB    _u(17)
#define USB_SIE_CTRL_RPU_OPT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_PULLUP_EN
// Description : Device: Enable pull up resistor
#define USB_SIE_CTRL_PULLUP_EN_RESET  _u(0x0)
#define USB_SIE_CTRL_PULLUP_EN_BITS   _u(0x00010000)
#define USB_SIE_CTRL_PULLUP_EN_MSB    _u(16)
#define USB_SIE_CTRL_PULLUP_EN_LSB    _u(16)
#define USB_SIE_CTRL_PULLUP_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_PULLDOWN_EN
// Description : Host: Enable pull down resistors
#define USB_SIE_CTRL_PULLDOWN_EN_RESET  _u(0x0)
#define USB_SIE_CTRL_PULLDOWN_EN_BITS   _u(0x00008000)
#define USB_SIE_CTRL_PULLDOWN_EN_MSB    _u(15)
#define USB_SIE_CTRL_PULLDOWN_EN_LSB    _u(15)
#define USB_SIE_CTRL_PULLDOWN_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_RESET_BUS
// Description : Host: Reset bus
#define USB_SIE_CTRL_RESET_BUS_RESET  _u(0x0)
#define USB_SIE_CTRL_RESET_BUS_BITS   _u(0x00002000)
#define USB_SIE_CTRL_RESET_BUS_MSB    _u(13)
#define USB_SIE_CTRL_RESET_BUS_LSB    _u(13)
#define USB_SIE_CTRL_RESET_BUS_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_RESUME
// Description : Device: Remote wakeup. Device can initiate its own resume after
//               suspend.
#define USB_SIE_CTRL_RESUME_RESET  _u(0x0)
#define USB_SIE_CTRL_RESUME_BITS   _u(0x00001000)
#define USB_SIE_CTRL_RESUME_MSB    _u(12)
#define USB_SIE_CTRL_RESUME_LSB    _u(12)
#define USB_SIE_CTRL_RESUME_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_VBUS_EN
// Description : Host: Enable VBUS
#define USB_SIE_CTRL_VBUS_EN_RESET  _u(0x0)
#define USB_SIE_CTRL_VBUS_EN_BITS   _u(0x00000800)
#define USB_SIE_CTRL_VBUS_EN_MSB    _u(11)
#define USB_SIE_CTRL_VBUS_EN_LSB    _u(11)
#define USB_SIE_CTRL_VBUS_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_KEEP_ALIVE_EN
// Description : Host: Enable keep alive packet (for low speed bus)
#define USB_SIE_CTRL_KEEP_ALIVE_EN_RESET  _u(0x0)
#define USB_SIE_CTRL_KEEP_ALIVE_EN_BITS   _u(0x00000400)
#define USB_SIE_CTRL_KEEP_ALIVE_EN_MSB    _u(10)
#define USB_SIE_CTRL_KEEP_ALIVE_EN_LSB    _u(10)
#define USB_SIE_CTRL_KEEP_ALIVE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_SOF_EN
// Description : Host: Enable SOF generation (for full speed bus)
#define USB_SIE_CTRL_SOF_EN_RESET  _u(0x0)
#define USB_SIE_CTRL_SOF_EN_BITS   _u(0x00000200)
#define USB_SIE_CTRL_SOF_EN_MSB    _u(9)
#define USB_SIE_CTRL_SOF_EN_LSB    _u(9)
#define USB_SIE_CTRL_SOF_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_SOF_SYNC
// Description : Host: Delay packet(s) until after SOF
#define USB_SIE_CTRL_SOF_SYNC_RESET  _u(0x0)
#define USB_SIE_CTRL_SOF_SYNC_BITS   _u(0x00000100)
#define USB_SIE_CTRL_SOF_SYNC_MSB    _u(8)
#define USB_SIE_CTRL_SOF_SYNC_LSB    _u(8)
#define USB_SIE_CTRL_SOF_SYNC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_PREAMBLE_EN
// Description : Host: Preable enable for LS device on FS hub
#define USB_SIE_CTRL_PREAMBLE_EN_RESET  _u(0x0)
#define USB_SIE_CTRL_PREAMBLE_EN_BITS   _u(0x00000040)
#define USB_SIE_CTRL_PREAMBLE_EN_MSB    _u(6)
#define USB_SIE_CTRL_PREAMBLE_EN_LSB    _u(6)
#define USB_SIE_CTRL_PREAMBLE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_STOP_TRANS
// Description : Host: Stop transaction
#define USB_SIE_CTRL_STOP_TRANS_RESET  _u(0x0)
#define USB_SIE_CTRL_STOP_TRANS_BITS   _u(0x00000010)
#define USB_SIE_CTRL_STOP_TRANS_MSB    _u(4)
#define USB_SIE_CTRL_STOP_TRANS_LSB    _u(4)
#define USB_SIE_CTRL_STOP_TRANS_ACCESS "SC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_RECEIVE_DATA
// Description : Host: Receive transaction (IN to host)
#define USB_SIE_CTRL_RECEIVE_DATA_RESET  _u(0x0)
#define USB_SIE_CTRL_RECEIVE_DATA_BITS   _u(0x00000008)
#define USB_SIE_CTRL_RECEIVE_DATA_MSB    _u(3)
#define USB_SIE_CTRL_RECEIVE_DATA_LSB    _u(3)
#define USB_SIE_CTRL_RECEIVE_DATA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_SEND_DATA
// Description : Host: Send transaction (OUT from host)
#define USB_SIE_CTRL_SEND_DATA_RESET  _u(0x0)
#define USB_SIE_CTRL_SEND_DATA_BITS   _u(0x00000004)
#define USB_SIE_CTRL_SEND_DATA_MSB    _u(2)
#define USB_SIE_CTRL_SEND_DATA_LSB    _u(2)
#define USB_SIE_CTRL_SEND_DATA_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_SEND_SETUP
// Description : Host: Send Setup packet
#define USB_SIE_CTRL_SEND_SETUP_RESET  _u(0x0)
#define USB_SIE_CTRL_SEND_SETUP_BITS   _u(0x00000002)
#define USB_SIE_CTRL_SEND_SETUP_MSB    _u(1)
#define USB_SIE_CTRL_SEND_SETUP_LSB    _u(1)
#define USB_SIE_CTRL_SEND_SETUP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_CTRL_START_TRANS
// Description : Host: Start transaction
#define USB_SIE_CTRL_START_TRANS_RESET  _u(0x0)
#define USB_SIE_CTRL_START_TRANS_BITS   _u(0x00000001)
#define USB_SIE_CTRL_START_TRANS_MSB    _u(0)
#define USB_SIE_CTRL_START_TRANS_LSB    _u(0)
#define USB_SIE_CTRL_START_TRANS_ACCESS "SC"
// =============================================================================
// Register    : USB_SIE_STATUS
// Description : SIE status register
#define USB_SIE_STATUS_OFFSET _u(0x00000050)
#define USB_SIE_STATUS_BITS   _u(0xff0f0f1d)
#define USB_SIE_STATUS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_DATA_SEQ_ERROR
// Description : Data Sequence Error.
//
//               The device can raise a sequence error in the following
//               conditions:
//
//               * A SETUP packet is received followed by a DATA1 packet (data
//               phase should always be DATA0) * An OUT packet is received from
//               the host but doesn't match the data pid in the buffer control
//               register read from DPSRAM
//
//               The host can raise a data sequence error in the following
//               conditions:
//
//               * An IN packet from the device has the wrong data PID
#define USB_SIE_STATUS_DATA_SEQ_ERROR_RESET  _u(0x0)
#define USB_SIE_STATUS_DATA_SEQ_ERROR_BITS   _u(0x80000000)
#define USB_SIE_STATUS_DATA_SEQ_ERROR_MSB    _u(31)
#define USB_SIE_STATUS_DATA_SEQ_ERROR_LSB    _u(31)
#define USB_SIE_STATUS_DATA_SEQ_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_ACK_REC
// Description : ACK received. Raised by both host and device.
#define USB_SIE_STATUS_ACK_REC_RESET  _u(0x0)
#define USB_SIE_STATUS_ACK_REC_BITS   _u(0x40000000)
#define USB_SIE_STATUS_ACK_REC_MSB    _u(30)
#define USB_SIE_STATUS_ACK_REC_LSB    _u(30)
#define USB_SIE_STATUS_ACK_REC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_STALL_REC
// Description : Host: STALL received
#define USB_SIE_STATUS_STALL_REC_RESET  _u(0x0)
#define USB_SIE_STATUS_STALL_REC_BITS   _u(0x20000000)
#define USB_SIE_STATUS_STALL_REC_MSB    _u(29)
#define USB_SIE_STATUS_STALL_REC_LSB    _u(29)
#define USB_SIE_STATUS_STALL_REC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_NAK_REC
// Description : Host: NAK received
#define USB_SIE_STATUS_NAK_REC_RESET  _u(0x0)
#define USB_SIE_STATUS_NAK_REC_BITS   _u(0x10000000)
#define USB_SIE_STATUS_NAK_REC_MSB    _u(28)
#define USB_SIE_STATUS_NAK_REC_LSB    _u(28)
#define USB_SIE_STATUS_NAK_REC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_RX_TIMEOUT
// Description : RX timeout is raised by both the host and device if an ACK is
//               not received in the maximum time specified by the USB spec.
#define USB_SIE_STATUS_RX_TIMEOUT_RESET  _u(0x0)
#define USB_SIE_STATUS_RX_TIMEOUT_BITS   _u(0x08000000)
#define USB_SIE_STATUS_RX_TIMEOUT_MSB    _u(27)
#define USB_SIE_STATUS_RX_TIMEOUT_LSB    _u(27)
#define USB_SIE_STATUS_RX_TIMEOUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_RX_OVERFLOW
// Description : RX overflow is raised by the Serial RX engine if the incoming
//               data is too fast.
#define USB_SIE_STATUS_RX_OVERFLOW_RESET  _u(0x0)
#define USB_SIE_STATUS_RX_OVERFLOW_BITS   _u(0x04000000)
#define USB_SIE_STATUS_RX_OVERFLOW_MSB    _u(26)
#define USB_SIE_STATUS_RX_OVERFLOW_LSB    _u(26)
#define USB_SIE_STATUS_RX_OVERFLOW_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_BIT_STUFF_ERROR
// Description : Bit Stuff Error. Raised by the Serial RX engine.
#define USB_SIE_STATUS_BIT_STUFF_ERROR_RESET  _u(0x0)
#define USB_SIE_STATUS_BIT_STUFF_ERROR_BITS   _u(0x02000000)
#define USB_SIE_STATUS_BIT_STUFF_ERROR_MSB    _u(25)
#define USB_SIE_STATUS_BIT_STUFF_ERROR_LSB    _u(25)
#define USB_SIE_STATUS_BIT_STUFF_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_CRC_ERROR
// Description : CRC Error. Raised by the Serial RX engine.
#define USB_SIE_STATUS_CRC_ERROR_RESET  _u(0x0)
#define USB_SIE_STATUS_CRC_ERROR_BITS   _u(0x01000000)
#define USB_SIE_STATUS_CRC_ERROR_MSB    _u(24)
#define USB_SIE_STATUS_CRC_ERROR_LSB    _u(24)
#define USB_SIE_STATUS_CRC_ERROR_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_BUS_RESET
// Description : Device: bus reset received
#define USB_SIE_STATUS_BUS_RESET_RESET  _u(0x0)
#define USB_SIE_STATUS_BUS_RESET_BITS   _u(0x00080000)
#define USB_SIE_STATUS_BUS_RESET_MSB    _u(19)
#define USB_SIE_STATUS_BUS_RESET_LSB    _u(19)
#define USB_SIE_STATUS_BUS_RESET_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_TRANS_COMPLETE
// Description : Transaction complete.
//
//               Raised by device if:
//
//               * An IN or OUT packet is sent with the `LAST_BUFF` bit set in
//               the buffer control register
//
//               Raised by host if:
//
//               * A setup packet is sent when no data in or data out
//               transaction follows * An IN packet is received and the
//               `LAST_BUFF` bit is set in the buffer control register * An IN
//               packet is received with zero length * An OUT packet is sent and
//               the `LAST_BUFF` bit is set
#define USB_SIE_STATUS_TRANS_COMPLETE_RESET  _u(0x0)
#define USB_SIE_STATUS_TRANS_COMPLETE_BITS   _u(0x00040000)
#define USB_SIE_STATUS_TRANS_COMPLETE_MSB    _u(18)
#define USB_SIE_STATUS_TRANS_COMPLETE_LSB    _u(18)
#define USB_SIE_STATUS_TRANS_COMPLETE_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_SETUP_REC
// Description : Device: Setup packet received
#define USB_SIE_STATUS_SETUP_REC_RESET  _u(0x0)
#define USB_SIE_STATUS_SETUP_REC_BITS   _u(0x00020000)
#define USB_SIE_STATUS_SETUP_REC_MSB    _u(17)
#define USB_SIE_STATUS_SETUP_REC_LSB    _u(17)
#define USB_SIE_STATUS_SETUP_REC_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_CONNECTED
// Description : Device: connected
#define USB_SIE_STATUS_CONNECTED_RESET  _u(0x0)
#define USB_SIE_STATUS_CONNECTED_BITS   _u(0x00010000)
#define USB_SIE_STATUS_CONNECTED_MSB    _u(16)
#define USB_SIE_STATUS_CONNECTED_LSB    _u(16)
#define USB_SIE_STATUS_CONNECTED_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_RESUME
// Description : Host: Device has initiated a remote resume. Device: host has
//               initiated a resume.
#define USB_SIE_STATUS_RESUME_RESET  _u(0x0)
#define USB_SIE_STATUS_RESUME_BITS   _u(0x00000800)
#define USB_SIE_STATUS_RESUME_MSB    _u(11)
#define USB_SIE_STATUS_RESUME_LSB    _u(11)
#define USB_SIE_STATUS_RESUME_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_VBUS_OVER_CURR
// Description : VBUS over current detected
#define USB_SIE_STATUS_VBUS_OVER_CURR_RESET  _u(0x0)
#define USB_SIE_STATUS_VBUS_OVER_CURR_BITS   _u(0x00000400)
#define USB_SIE_STATUS_VBUS_OVER_CURR_MSB    _u(10)
#define USB_SIE_STATUS_VBUS_OVER_CURR_LSB    _u(10)
#define USB_SIE_STATUS_VBUS_OVER_CURR_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_SPEED
// Description : Host: device speed. Disconnected = 00, LS = 01, FS = 10
#define USB_SIE_STATUS_SPEED_RESET  _u(0x0)
#define USB_SIE_STATUS_SPEED_BITS   _u(0x00000300)
#define USB_SIE_STATUS_SPEED_MSB    _u(9)
#define USB_SIE_STATUS_SPEED_LSB    _u(8)
#define USB_SIE_STATUS_SPEED_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_SUSPENDED
// Description : Bus in suspended state. Valid for device and host. Host and
//               device will go into suspend if neither Keep Alive / SOF frames
//               are enabled.
#define USB_SIE_STATUS_SUSPENDED_RESET  _u(0x0)
#define USB_SIE_STATUS_SUSPENDED_BITS   _u(0x00000010)
#define USB_SIE_STATUS_SUSPENDED_MSB    _u(4)
#define USB_SIE_STATUS_SUSPENDED_LSB    _u(4)
#define USB_SIE_STATUS_SUSPENDED_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_LINE_STATE
// Description : USB bus line state
#define USB_SIE_STATUS_LINE_STATE_RESET  _u(0x0)
#define USB_SIE_STATUS_LINE_STATE_BITS   _u(0x0000000c)
#define USB_SIE_STATUS_LINE_STATE_MSB    _u(3)
#define USB_SIE_STATUS_LINE_STATE_LSB    _u(2)
#define USB_SIE_STATUS_LINE_STATE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_SIE_STATUS_VBUS_DETECTED
// Description : Device: VBUS Detected
#define USB_SIE_STATUS_VBUS_DETECTED_RESET  _u(0x0)
#define USB_SIE_STATUS_VBUS_DETECTED_BITS   _u(0x00000001)
#define USB_SIE_STATUS_VBUS_DETECTED_MSB    _u(0)
#define USB_SIE_STATUS_VBUS_DETECTED_LSB    _u(0)
#define USB_SIE_STATUS_VBUS_DETECTED_ACCESS "RO"
// =============================================================================
// Register    : USB_INT_EP_CTRL
// Description : interrupt endpoint control register
#define USB_INT_EP_CTRL_OFFSET _u(0x00000054)
#define USB_INT_EP_CTRL_BITS   _u(0x0000fffe)
#define USB_INT_EP_CTRL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_INT_EP_CTRL_INT_EP_ACTIVE
// Description : Host: Enable interrupt endpoint 1 -> 15
#define USB_INT_EP_CTRL_INT_EP_ACTIVE_RESET  _u(0x0000)
#define USB_INT_EP_CTRL_INT_EP_ACTIVE_BITS   _u(0x0000fffe)
#define USB_INT_EP_CTRL_INT_EP_ACTIVE_MSB    _u(15)
#define USB_INT_EP_CTRL_INT_EP_ACTIVE_LSB    _u(1)
#define USB_INT_EP_CTRL_INT_EP_ACTIVE_ACCESS "RW"
// =============================================================================
// Register    : USB_BUFF_STATUS
// Description : Buffer status register. A bit set here indicates that a buffer
//               has completed on the endpoint (if the buffer interrupt is
//               enabled). It is possible for 2 buffers to be completed, so
//               clearing the buffer status bit may instantly re set it on the
//               next clock cycle.
#define USB_BUFF_STATUS_OFFSET _u(0x00000058)
#define USB_BUFF_STATUS_BITS   _u(0xffffffff)
#define USB_BUFF_STATUS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP15_OUT
// Description : None
#define USB_BUFF_STATUS_EP15_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP15_OUT_BITS   _u(0x80000000)
#define USB_BUFF_STATUS_EP15_OUT_MSB    _u(31)
#define USB_BUFF_STATUS_EP15_OUT_LSB    _u(31)
#define USB_BUFF_STATUS_EP15_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP15_IN
// Description : None
#define USB_BUFF_STATUS_EP15_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP15_IN_BITS   _u(0x40000000)
#define USB_BUFF_STATUS_EP15_IN_MSB    _u(30)
#define USB_BUFF_STATUS_EP15_IN_LSB    _u(30)
#define USB_BUFF_STATUS_EP15_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP14_OUT
// Description : None
#define USB_BUFF_STATUS_EP14_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP14_OUT_BITS   _u(0x20000000)
#define USB_BUFF_STATUS_EP14_OUT_MSB    _u(29)
#define USB_BUFF_STATUS_EP14_OUT_LSB    _u(29)
#define USB_BUFF_STATUS_EP14_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP14_IN
// Description : None
#define USB_BUFF_STATUS_EP14_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP14_IN_BITS   _u(0x10000000)
#define USB_BUFF_STATUS_EP14_IN_MSB    _u(28)
#define USB_BUFF_STATUS_EP14_IN_LSB    _u(28)
#define USB_BUFF_STATUS_EP14_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP13_OUT
// Description : None
#define USB_BUFF_STATUS_EP13_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP13_OUT_BITS   _u(0x08000000)
#define USB_BUFF_STATUS_EP13_OUT_MSB    _u(27)
#define USB_BUFF_STATUS_EP13_OUT_LSB    _u(27)
#define USB_BUFF_STATUS_EP13_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP13_IN
// Description : None
#define USB_BUFF_STATUS_EP13_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP13_IN_BITS   _u(0x04000000)
#define USB_BUFF_STATUS_EP13_IN_MSB    _u(26)
#define USB_BUFF_STATUS_EP13_IN_LSB    _u(26)
#define USB_BUFF_STATUS_EP13_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP12_OUT
// Description : None
#define USB_BUFF_STATUS_EP12_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP12_OUT_BITS   _u(0x02000000)
#define USB_BUFF_STATUS_EP12_OUT_MSB    _u(25)
#define USB_BUFF_STATUS_EP12_OUT_LSB    _u(25)
#define USB_BUFF_STATUS_EP12_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP12_IN
// Description : None
#define USB_BUFF_STATUS_EP12_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP12_IN_BITS   _u(0x01000000)
#define USB_BUFF_STATUS_EP12_IN_MSB    _u(24)
#define USB_BUFF_STATUS_EP12_IN_LSB    _u(24)
#define USB_BUFF_STATUS_EP12_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP11_OUT
// Description : None
#define USB_BUFF_STATUS_EP11_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP11_OUT_BITS   _u(0x00800000)
#define USB_BUFF_STATUS_EP11_OUT_MSB    _u(23)
#define USB_BUFF_STATUS_EP11_OUT_LSB    _u(23)
#define USB_BUFF_STATUS_EP11_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP11_IN
// Description : None
#define USB_BUFF_STATUS_EP11_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP11_IN_BITS   _u(0x00400000)
#define USB_BUFF_STATUS_EP11_IN_MSB    _u(22)
#define USB_BUFF_STATUS_EP11_IN_LSB    _u(22)
#define USB_BUFF_STATUS_EP11_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP10_OUT
// Description : None
#define USB_BUFF_STATUS_EP10_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP10_OUT_BITS   _u(0x00200000)
#define USB_BUFF_STATUS_EP10_OUT_MSB    _u(21)
#define USB_BUFF_STATUS_EP10_OUT_LSB    _u(21)
#define USB_BUFF_STATUS_EP10_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP10_IN
// Description : None
#define USB_BUFF_STATUS_EP10_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP10_IN_BITS   _u(0x00100000)
#define USB_BUFF_STATUS_EP10_IN_MSB    _u(20)
#define USB_BUFF_STATUS_EP10_IN_LSB    _u(20)
#define USB_BUFF_STATUS_EP10_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP9_OUT
// Description : None
#define USB_BUFF_STATUS_EP9_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP9_OUT_BITS   _u(0x00080000)
#define USB_BUFF_STATUS_EP9_OUT_MSB    _u(19)
#define USB_BUFF_STATUS_EP9_OUT_LSB    _u(19)
#define USB_BUFF_STATUS_EP9_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP9_IN
// Description : None
#define USB_BUFF_STATUS_EP9_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP9_IN_BITS   _u(0x00040000)
#define USB_BUFF_STATUS_EP9_IN_MSB    _u(18)
#define USB_BUFF_STATUS_EP9_IN_LSB    _u(18)
#define USB_BUFF_STATUS_EP9_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP8_OUT
// Description : None
#define USB_BUFF_STATUS_EP8_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP8_OUT_BITS   _u(0x00020000)
#define USB_BUFF_STATUS_EP8_OUT_MSB    _u(17)
#define USB_BUFF_STATUS_EP8_OUT_LSB    _u(17)
#define USB_BUFF_STATUS_EP8_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP8_IN
// Description : None
#define USB_BUFF_STATUS_EP8_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP8_IN_BITS   _u(0x00010000)
#define USB_BUFF_STATUS_EP8_IN_MSB    _u(16)
#define USB_BUFF_STATUS_EP8_IN_LSB    _u(16)
#define USB_BUFF_STATUS_EP8_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP7_OUT
// Description : None
#define USB_BUFF_STATUS_EP7_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP7_OUT_BITS   _u(0x00008000)
#define USB_BUFF_STATUS_EP7_OUT_MSB    _u(15)
#define USB_BUFF_STATUS_EP7_OUT_LSB    _u(15)
#define USB_BUFF_STATUS_EP7_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP7_IN
// Description : None
#define USB_BUFF_STATUS_EP7_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP7_IN_BITS   _u(0x00004000)
#define USB_BUFF_STATUS_EP7_IN_MSB    _u(14)
#define USB_BUFF_STATUS_EP7_IN_LSB    _u(14)
#define USB_BUFF_STATUS_EP7_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP6_OUT
// Description : None
#define USB_BUFF_STATUS_EP6_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP6_OUT_BITS   _u(0x00002000)
#define USB_BUFF_STATUS_EP6_OUT_MSB    _u(13)
#define USB_BUFF_STATUS_EP6_OUT_LSB    _u(13)
#define USB_BUFF_STATUS_EP6_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP6_IN
// Description : None
#define USB_BUFF_STATUS_EP6_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP6_IN_BITS   _u(0x00001000)
#define USB_BUFF_STATUS_EP6_IN_MSB    _u(12)
#define USB_BUFF_STATUS_EP6_IN_LSB    _u(12)
#define USB_BUFF_STATUS_EP6_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP5_OUT
// Description : None
#define USB_BUFF_STATUS_EP5_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP5_OUT_BITS   _u(0x00000800)
#define USB_BUFF_STATUS_EP5_OUT_MSB    _u(11)
#define USB_BUFF_STATUS_EP5_OUT_LSB    _u(11)
#define USB_BUFF_STATUS_EP5_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP5_IN
// Description : None
#define USB_BUFF_STATUS_EP5_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP5_IN_BITS   _u(0x00000400)
#define USB_BUFF_STATUS_EP5_IN_MSB    _u(10)
#define USB_BUFF_STATUS_EP5_IN_LSB    _u(10)
#define USB_BUFF_STATUS_EP5_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP4_OUT
// Description : None
#define USB_BUFF_STATUS_EP4_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP4_OUT_BITS   _u(0x00000200)
#define USB_BUFF_STATUS_EP4_OUT_MSB    _u(9)
#define USB_BUFF_STATUS_EP4_OUT_LSB    _u(9)
#define USB_BUFF_STATUS_EP4_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP4_IN
// Description : None
#define USB_BUFF_STATUS_EP4_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP4_IN_BITS   _u(0x00000100)
#define USB_BUFF_STATUS_EP4_IN_MSB    _u(8)
#define USB_BUFF_STATUS_EP4_IN_LSB    _u(8)
#define USB_BUFF_STATUS_EP4_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP3_OUT
// Description : None
#define USB_BUFF_STATUS_EP3_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP3_OUT_BITS   _u(0x00000080)
#define USB_BUFF_STATUS_EP3_OUT_MSB    _u(7)
#define USB_BUFF_STATUS_EP3_OUT_LSB    _u(7)
#define USB_BUFF_STATUS_EP3_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP3_IN
// Description : None
#define USB_BUFF_STATUS_EP3_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP3_IN_BITS   _u(0x00000040)
#define USB_BUFF_STATUS_EP3_IN_MSB    _u(6)
#define USB_BUFF_STATUS_EP3_IN_LSB    _u(6)
#define USB_BUFF_STATUS_EP3_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP2_OUT
// Description : None
#define USB_BUFF_STATUS_EP2_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP2_OUT_BITS   _u(0x00000020)
#define USB_BUFF_STATUS_EP2_OUT_MSB    _u(5)
#define USB_BUFF_STATUS_EP2_OUT_LSB    _u(5)
#define USB_BUFF_STATUS_EP2_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP2_IN
// Description : None
#define USB_BUFF_STATUS_EP2_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP2_IN_BITS   _u(0x00000010)
#define USB_BUFF_STATUS_EP2_IN_MSB    _u(4)
#define USB_BUFF_STATUS_EP2_IN_LSB    _u(4)
#define USB_BUFF_STATUS_EP2_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP1_OUT
// Description : None
#define USB_BUFF_STATUS_EP1_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP1_OUT_BITS   _u(0x00000008)
#define USB_BUFF_STATUS_EP1_OUT_MSB    _u(3)
#define USB_BUFF_STATUS_EP1_OUT_LSB    _u(3)
#define USB_BUFF_STATUS_EP1_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP1_IN
// Description : None
#define USB_BUFF_STATUS_EP1_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP1_IN_BITS   _u(0x00000004)
#define USB_BUFF_STATUS_EP1_IN_MSB    _u(2)
#define USB_BUFF_STATUS_EP1_IN_LSB    _u(2)
#define USB_BUFF_STATUS_EP1_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP0_OUT
// Description : None
#define USB_BUFF_STATUS_EP0_OUT_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP0_OUT_BITS   _u(0x00000002)
#define USB_BUFF_STATUS_EP0_OUT_MSB    _u(1)
#define USB_BUFF_STATUS_EP0_OUT_LSB    _u(1)
#define USB_BUFF_STATUS_EP0_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_STATUS_EP0_IN
// Description : None
#define USB_BUFF_STATUS_EP0_IN_RESET  _u(0x0)
#define USB_BUFF_STATUS_EP0_IN_BITS   _u(0x00000001)
#define USB_BUFF_STATUS_EP0_IN_MSB    _u(0)
#define USB_BUFF_STATUS_EP0_IN_LSB    _u(0)
#define USB_BUFF_STATUS_EP0_IN_ACCESS "WC"
// =============================================================================
// Register    : USB_BUFF_CPU_SHOULD_HANDLE
// Description : Which of the double buffers should be handled. Only valid if
//               using an interrupt per buffer (i.e. not per 2 buffers). Not
//               valid for host interrupt endpoint polling because they are only
//               single buffered.
#define USB_BUFF_CPU_SHOULD_HANDLE_OFFSET _u(0x0000005c)
#define USB_BUFF_CPU_SHOULD_HANDLE_BITS   _u(0xffffffff)
#define USB_BUFF_CPU_SHOULD_HANDLE_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP15_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP15_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP15_OUT_BITS   _u(0x80000000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP15_OUT_MSB    _u(31)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP15_OUT_LSB    _u(31)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP15_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP15_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP15_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP15_IN_BITS   _u(0x40000000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP15_IN_MSB    _u(30)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP15_IN_LSB    _u(30)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP15_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP14_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP14_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP14_OUT_BITS   _u(0x20000000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP14_OUT_MSB    _u(29)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP14_OUT_LSB    _u(29)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP14_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP14_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP14_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP14_IN_BITS   _u(0x10000000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP14_IN_MSB    _u(28)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP14_IN_LSB    _u(28)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP14_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP13_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP13_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP13_OUT_BITS   _u(0x08000000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP13_OUT_MSB    _u(27)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP13_OUT_LSB    _u(27)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP13_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP13_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP13_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP13_IN_BITS   _u(0x04000000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP13_IN_MSB    _u(26)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP13_IN_LSB    _u(26)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP13_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP12_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP12_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP12_OUT_BITS   _u(0x02000000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP12_OUT_MSB    _u(25)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP12_OUT_LSB    _u(25)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP12_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP12_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP12_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP12_IN_BITS   _u(0x01000000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP12_IN_MSB    _u(24)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP12_IN_LSB    _u(24)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP12_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP11_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP11_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP11_OUT_BITS   _u(0x00800000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP11_OUT_MSB    _u(23)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP11_OUT_LSB    _u(23)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP11_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP11_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP11_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP11_IN_BITS   _u(0x00400000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP11_IN_MSB    _u(22)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP11_IN_LSB    _u(22)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP11_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP10_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP10_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP10_OUT_BITS   _u(0x00200000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP10_OUT_MSB    _u(21)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP10_OUT_LSB    _u(21)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP10_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP10_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP10_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP10_IN_BITS   _u(0x00100000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP10_IN_MSB    _u(20)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP10_IN_LSB    _u(20)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP10_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP9_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP9_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP9_OUT_BITS   _u(0x00080000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP9_OUT_MSB    _u(19)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP9_OUT_LSB    _u(19)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP9_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP9_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP9_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP9_IN_BITS   _u(0x00040000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP9_IN_MSB    _u(18)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP9_IN_LSB    _u(18)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP9_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP8_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP8_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP8_OUT_BITS   _u(0x00020000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP8_OUT_MSB    _u(17)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP8_OUT_LSB    _u(17)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP8_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP8_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP8_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP8_IN_BITS   _u(0x00010000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP8_IN_MSB    _u(16)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP8_IN_LSB    _u(16)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP8_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP7_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP7_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP7_OUT_BITS   _u(0x00008000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP7_OUT_MSB    _u(15)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP7_OUT_LSB    _u(15)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP7_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP7_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP7_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP7_IN_BITS   _u(0x00004000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP7_IN_MSB    _u(14)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP7_IN_LSB    _u(14)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP7_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP6_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP6_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP6_OUT_BITS   _u(0x00002000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP6_OUT_MSB    _u(13)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP6_OUT_LSB    _u(13)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP6_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP6_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP6_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP6_IN_BITS   _u(0x00001000)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP6_IN_MSB    _u(12)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP6_IN_LSB    _u(12)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP6_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP5_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP5_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP5_OUT_BITS   _u(0x00000800)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP5_OUT_MSB    _u(11)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP5_OUT_LSB    _u(11)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP5_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP5_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP5_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP5_IN_BITS   _u(0x00000400)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP5_IN_MSB    _u(10)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP5_IN_LSB    _u(10)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP5_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP4_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP4_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP4_OUT_BITS   _u(0x00000200)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP4_OUT_MSB    _u(9)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP4_OUT_LSB    _u(9)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP4_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP4_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP4_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP4_IN_BITS   _u(0x00000100)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP4_IN_MSB    _u(8)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP4_IN_LSB    _u(8)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP4_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP3_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP3_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP3_OUT_BITS   _u(0x00000080)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP3_OUT_MSB    _u(7)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP3_OUT_LSB    _u(7)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP3_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP3_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP3_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP3_IN_BITS   _u(0x00000040)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP3_IN_MSB    _u(6)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP3_IN_LSB    _u(6)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP3_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP2_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP2_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP2_OUT_BITS   _u(0x00000020)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP2_OUT_MSB    _u(5)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP2_OUT_LSB    _u(5)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP2_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP2_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP2_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP2_IN_BITS   _u(0x00000010)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP2_IN_MSB    _u(4)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP2_IN_LSB    _u(4)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP2_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP1_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP1_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP1_OUT_BITS   _u(0x00000008)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP1_OUT_MSB    _u(3)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP1_OUT_LSB    _u(3)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP1_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP1_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP1_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP1_IN_BITS   _u(0x00000004)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP1_IN_MSB    _u(2)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP1_IN_LSB    _u(2)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP1_IN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP0_OUT
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP0_OUT_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP0_OUT_BITS   _u(0x00000002)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP0_OUT_MSB    _u(1)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP0_OUT_LSB    _u(1)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP0_OUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_BUFF_CPU_SHOULD_HANDLE_EP0_IN
// Description : None
#define USB_BUFF_CPU_SHOULD_HANDLE_EP0_IN_RESET  _u(0x0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP0_IN_BITS   _u(0x00000001)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP0_IN_MSB    _u(0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP0_IN_LSB    _u(0)
#define USB_BUFF_CPU_SHOULD_HANDLE_EP0_IN_ACCESS "RO"
// =============================================================================
// Register    : USB_EP_ABORT
// Description : Device only: Can be set to ignore the buffer control register
//               for this endpoint in case you would like to revoke a buffer. A
//               NAK will be sent for every access to the endpoint until this
//               bit is cleared. A corresponding bit in `EP_ABORT_DONE` is set
//               when it is safe to modify the buffer control register.
#define USB_EP_ABORT_OFFSET _u(0x00000060)
#define USB_EP_ABORT_BITS   _u(0xffffffff)
#define USB_EP_ABORT_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP15_OUT
// Description : None
#define USB_EP_ABORT_EP15_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP15_OUT_BITS   _u(0x80000000)
#define USB_EP_ABORT_EP15_OUT_MSB    _u(31)
#define USB_EP_ABORT_EP15_OUT_LSB    _u(31)
#define USB_EP_ABORT_EP15_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP15_IN
// Description : None
#define USB_EP_ABORT_EP15_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP15_IN_BITS   _u(0x40000000)
#define USB_EP_ABORT_EP15_IN_MSB    _u(30)
#define USB_EP_ABORT_EP15_IN_LSB    _u(30)
#define USB_EP_ABORT_EP15_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP14_OUT
// Description : None
#define USB_EP_ABORT_EP14_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP14_OUT_BITS   _u(0x20000000)
#define USB_EP_ABORT_EP14_OUT_MSB    _u(29)
#define USB_EP_ABORT_EP14_OUT_LSB    _u(29)
#define USB_EP_ABORT_EP14_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP14_IN
// Description : None
#define USB_EP_ABORT_EP14_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP14_IN_BITS   _u(0x10000000)
#define USB_EP_ABORT_EP14_IN_MSB    _u(28)
#define USB_EP_ABORT_EP14_IN_LSB    _u(28)
#define USB_EP_ABORT_EP14_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP13_OUT
// Description : None
#define USB_EP_ABORT_EP13_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP13_OUT_BITS   _u(0x08000000)
#define USB_EP_ABORT_EP13_OUT_MSB    _u(27)
#define USB_EP_ABORT_EP13_OUT_LSB    _u(27)
#define USB_EP_ABORT_EP13_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP13_IN
// Description : None
#define USB_EP_ABORT_EP13_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP13_IN_BITS   _u(0x04000000)
#define USB_EP_ABORT_EP13_IN_MSB    _u(26)
#define USB_EP_ABORT_EP13_IN_LSB    _u(26)
#define USB_EP_ABORT_EP13_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP12_OUT
// Description : None
#define USB_EP_ABORT_EP12_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP12_OUT_BITS   _u(0x02000000)
#define USB_EP_ABORT_EP12_OUT_MSB    _u(25)
#define USB_EP_ABORT_EP12_OUT_LSB    _u(25)
#define USB_EP_ABORT_EP12_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP12_IN
// Description : None
#define USB_EP_ABORT_EP12_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP12_IN_BITS   _u(0x01000000)
#define USB_EP_ABORT_EP12_IN_MSB    _u(24)
#define USB_EP_ABORT_EP12_IN_LSB    _u(24)
#define USB_EP_ABORT_EP12_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP11_OUT
// Description : None
#define USB_EP_ABORT_EP11_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP11_OUT_BITS   _u(0x00800000)
#define USB_EP_ABORT_EP11_OUT_MSB    _u(23)
#define USB_EP_ABORT_EP11_OUT_LSB    _u(23)
#define USB_EP_ABORT_EP11_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP11_IN
// Description : None
#define USB_EP_ABORT_EP11_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP11_IN_BITS   _u(0x00400000)
#define USB_EP_ABORT_EP11_IN_MSB    _u(22)
#define USB_EP_ABORT_EP11_IN_LSB    _u(22)
#define USB_EP_ABORT_EP11_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP10_OUT
// Description : None
#define USB_EP_ABORT_EP10_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP10_OUT_BITS   _u(0x00200000)
#define USB_EP_ABORT_EP10_OUT_MSB    _u(21)
#define USB_EP_ABORT_EP10_OUT_LSB    _u(21)
#define USB_EP_ABORT_EP10_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP10_IN
// Description : None
#define USB_EP_ABORT_EP10_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP10_IN_BITS   _u(0x00100000)
#define USB_EP_ABORT_EP10_IN_MSB    _u(20)
#define USB_EP_ABORT_EP10_IN_LSB    _u(20)
#define USB_EP_ABORT_EP10_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP9_OUT
// Description : None
#define USB_EP_ABORT_EP9_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP9_OUT_BITS   _u(0x00080000)
#define USB_EP_ABORT_EP9_OUT_MSB    _u(19)
#define USB_EP_ABORT_EP9_OUT_LSB    _u(19)
#define USB_EP_ABORT_EP9_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP9_IN
// Description : None
#define USB_EP_ABORT_EP9_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP9_IN_BITS   _u(0x00040000)
#define USB_EP_ABORT_EP9_IN_MSB    _u(18)
#define USB_EP_ABORT_EP9_IN_LSB    _u(18)
#define USB_EP_ABORT_EP9_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP8_OUT
// Description : None
#define USB_EP_ABORT_EP8_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP8_OUT_BITS   _u(0x00020000)
#define USB_EP_ABORT_EP8_OUT_MSB    _u(17)
#define USB_EP_ABORT_EP8_OUT_LSB    _u(17)
#define USB_EP_ABORT_EP8_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP8_IN
// Description : None
#define USB_EP_ABORT_EP8_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP8_IN_BITS   _u(0x00010000)
#define USB_EP_ABORT_EP8_IN_MSB    _u(16)
#define USB_EP_ABORT_EP8_IN_LSB    _u(16)
#define USB_EP_ABORT_EP8_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP7_OUT
// Description : None
#define USB_EP_ABORT_EP7_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP7_OUT_BITS   _u(0x00008000)
#define USB_EP_ABORT_EP7_OUT_MSB    _u(15)
#define USB_EP_ABORT_EP7_OUT_LSB    _u(15)
#define USB_EP_ABORT_EP7_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP7_IN
// Description : None
#define USB_EP_ABORT_EP7_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP7_IN_BITS   _u(0x00004000)
#define USB_EP_ABORT_EP7_IN_MSB    _u(14)
#define USB_EP_ABORT_EP7_IN_LSB    _u(14)
#define USB_EP_ABORT_EP7_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP6_OUT
// Description : None
#define USB_EP_ABORT_EP6_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP6_OUT_BITS   _u(0x00002000)
#define USB_EP_ABORT_EP6_OUT_MSB    _u(13)
#define USB_EP_ABORT_EP6_OUT_LSB    _u(13)
#define USB_EP_ABORT_EP6_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP6_IN
// Description : None
#define USB_EP_ABORT_EP6_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP6_IN_BITS   _u(0x00001000)
#define USB_EP_ABORT_EP6_IN_MSB    _u(12)
#define USB_EP_ABORT_EP6_IN_LSB    _u(12)
#define USB_EP_ABORT_EP6_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP5_OUT
// Description : None
#define USB_EP_ABORT_EP5_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP5_OUT_BITS   _u(0x00000800)
#define USB_EP_ABORT_EP5_OUT_MSB    _u(11)
#define USB_EP_ABORT_EP5_OUT_LSB    _u(11)
#define USB_EP_ABORT_EP5_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP5_IN
// Description : None
#define USB_EP_ABORT_EP5_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP5_IN_BITS   _u(0x00000400)
#define USB_EP_ABORT_EP5_IN_MSB    _u(10)
#define USB_EP_ABORT_EP5_IN_LSB    _u(10)
#define USB_EP_ABORT_EP5_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP4_OUT
// Description : None
#define USB_EP_ABORT_EP4_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP4_OUT_BITS   _u(0x00000200)
#define USB_EP_ABORT_EP4_OUT_MSB    _u(9)
#define USB_EP_ABORT_EP4_OUT_LSB    _u(9)
#define USB_EP_ABORT_EP4_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP4_IN
// Description : None
#define USB_EP_ABORT_EP4_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP4_IN_BITS   _u(0x00000100)
#define USB_EP_ABORT_EP4_IN_MSB    _u(8)
#define USB_EP_ABORT_EP4_IN_LSB    _u(8)
#define USB_EP_ABORT_EP4_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP3_OUT
// Description : None
#define USB_EP_ABORT_EP3_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP3_OUT_BITS   _u(0x00000080)
#define USB_EP_ABORT_EP3_OUT_MSB    _u(7)
#define USB_EP_ABORT_EP3_OUT_LSB    _u(7)
#define USB_EP_ABORT_EP3_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP3_IN
// Description : None
#define USB_EP_ABORT_EP3_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP3_IN_BITS   _u(0x00000040)
#define USB_EP_ABORT_EP3_IN_MSB    _u(6)
#define USB_EP_ABORT_EP3_IN_LSB    _u(6)
#define USB_EP_ABORT_EP3_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP2_OUT
// Description : None
#define USB_EP_ABORT_EP2_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP2_OUT_BITS   _u(0x00000020)
#define USB_EP_ABORT_EP2_OUT_MSB    _u(5)
#define USB_EP_ABORT_EP2_OUT_LSB    _u(5)
#define USB_EP_ABORT_EP2_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP2_IN
// Description : None
#define USB_EP_ABORT_EP2_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP2_IN_BITS   _u(0x00000010)
#define USB_EP_ABORT_EP2_IN_MSB    _u(4)
#define USB_EP_ABORT_EP2_IN_LSB    _u(4)
#define USB_EP_ABORT_EP2_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP1_OUT
// Description : None
#define USB_EP_ABORT_EP1_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP1_OUT_BITS   _u(0x00000008)
#define USB_EP_ABORT_EP1_OUT_MSB    _u(3)
#define USB_EP_ABORT_EP1_OUT_LSB    _u(3)
#define USB_EP_ABORT_EP1_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP1_IN
// Description : None
#define USB_EP_ABORT_EP1_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP1_IN_BITS   _u(0x00000004)
#define USB_EP_ABORT_EP1_IN_MSB    _u(2)
#define USB_EP_ABORT_EP1_IN_LSB    _u(2)
#define USB_EP_ABORT_EP1_IN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP0_OUT
// Description : None
#define USB_EP_ABORT_EP0_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_EP0_OUT_BITS   _u(0x00000002)
#define USB_EP_ABORT_EP0_OUT_MSB    _u(1)
#define USB_EP_ABORT_EP0_OUT_LSB    _u(1)
#define USB_EP_ABORT_EP0_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_EP0_IN
// Description : None
#define USB_EP_ABORT_EP0_IN_RESET  _u(0x0)
#define USB_EP_ABORT_EP0_IN_BITS   _u(0x00000001)
#define USB_EP_ABORT_EP0_IN_MSB    _u(0)
#define USB_EP_ABORT_EP0_IN_LSB    _u(0)
#define USB_EP_ABORT_EP0_IN_ACCESS "RW"
// =============================================================================
// Register    : USB_EP_ABORT_DONE
// Description : Device only: Used in conjunction with `EP_ABORT`. Set once an
//               endpoint is idle so the programmer knows it is safe to modify
//               the buffer control register.
#define USB_EP_ABORT_DONE_OFFSET _u(0x00000064)
#define USB_EP_ABORT_DONE_BITS   _u(0xffffffff)
#define USB_EP_ABORT_DONE_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP15_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP15_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP15_OUT_BITS   _u(0x80000000)
#define USB_EP_ABORT_DONE_EP15_OUT_MSB    _u(31)
#define USB_EP_ABORT_DONE_EP15_OUT_LSB    _u(31)
#define USB_EP_ABORT_DONE_EP15_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP15_IN
// Description : None
#define USB_EP_ABORT_DONE_EP15_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP15_IN_BITS   _u(0x40000000)
#define USB_EP_ABORT_DONE_EP15_IN_MSB    _u(30)
#define USB_EP_ABORT_DONE_EP15_IN_LSB    _u(30)
#define USB_EP_ABORT_DONE_EP15_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP14_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP14_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP14_OUT_BITS   _u(0x20000000)
#define USB_EP_ABORT_DONE_EP14_OUT_MSB    _u(29)
#define USB_EP_ABORT_DONE_EP14_OUT_LSB    _u(29)
#define USB_EP_ABORT_DONE_EP14_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP14_IN
// Description : None
#define USB_EP_ABORT_DONE_EP14_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP14_IN_BITS   _u(0x10000000)
#define USB_EP_ABORT_DONE_EP14_IN_MSB    _u(28)
#define USB_EP_ABORT_DONE_EP14_IN_LSB    _u(28)
#define USB_EP_ABORT_DONE_EP14_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP13_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP13_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP13_OUT_BITS   _u(0x08000000)
#define USB_EP_ABORT_DONE_EP13_OUT_MSB    _u(27)
#define USB_EP_ABORT_DONE_EP13_OUT_LSB    _u(27)
#define USB_EP_ABORT_DONE_EP13_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP13_IN
// Description : None
#define USB_EP_ABORT_DONE_EP13_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP13_IN_BITS   _u(0x04000000)
#define USB_EP_ABORT_DONE_EP13_IN_MSB    _u(26)
#define USB_EP_ABORT_DONE_EP13_IN_LSB    _u(26)
#define USB_EP_ABORT_DONE_EP13_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP12_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP12_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP12_OUT_BITS   _u(0x02000000)
#define USB_EP_ABORT_DONE_EP12_OUT_MSB    _u(25)
#define USB_EP_ABORT_DONE_EP12_OUT_LSB    _u(25)
#define USB_EP_ABORT_DONE_EP12_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP12_IN
// Description : None
#define USB_EP_ABORT_DONE_EP12_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP12_IN_BITS   _u(0x01000000)
#define USB_EP_ABORT_DONE_EP12_IN_MSB    _u(24)
#define USB_EP_ABORT_DONE_EP12_IN_LSB    _u(24)
#define USB_EP_ABORT_DONE_EP12_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP11_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP11_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP11_OUT_BITS   _u(0x00800000)
#define USB_EP_ABORT_DONE_EP11_OUT_MSB    _u(23)
#define USB_EP_ABORT_DONE_EP11_OUT_LSB    _u(23)
#define USB_EP_ABORT_DONE_EP11_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP11_IN
// Description : None
#define USB_EP_ABORT_DONE_EP11_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP11_IN_BITS   _u(0x00400000)
#define USB_EP_ABORT_DONE_EP11_IN_MSB    _u(22)
#define USB_EP_ABORT_DONE_EP11_IN_LSB    _u(22)
#define USB_EP_ABORT_DONE_EP11_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP10_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP10_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP10_OUT_BITS   _u(0x00200000)
#define USB_EP_ABORT_DONE_EP10_OUT_MSB    _u(21)
#define USB_EP_ABORT_DONE_EP10_OUT_LSB    _u(21)
#define USB_EP_ABORT_DONE_EP10_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP10_IN
// Description : None
#define USB_EP_ABORT_DONE_EP10_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP10_IN_BITS   _u(0x00100000)
#define USB_EP_ABORT_DONE_EP10_IN_MSB    _u(20)
#define USB_EP_ABORT_DONE_EP10_IN_LSB    _u(20)
#define USB_EP_ABORT_DONE_EP10_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP9_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP9_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP9_OUT_BITS   _u(0x00080000)
#define USB_EP_ABORT_DONE_EP9_OUT_MSB    _u(19)
#define USB_EP_ABORT_DONE_EP9_OUT_LSB    _u(19)
#define USB_EP_ABORT_DONE_EP9_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP9_IN
// Description : None
#define USB_EP_ABORT_DONE_EP9_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP9_IN_BITS   _u(0x00040000)
#define USB_EP_ABORT_DONE_EP9_IN_MSB    _u(18)
#define USB_EP_ABORT_DONE_EP9_IN_LSB    _u(18)
#define USB_EP_ABORT_DONE_EP9_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP8_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP8_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP8_OUT_BITS   _u(0x00020000)
#define USB_EP_ABORT_DONE_EP8_OUT_MSB    _u(17)
#define USB_EP_ABORT_DONE_EP8_OUT_LSB    _u(17)
#define USB_EP_ABORT_DONE_EP8_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP8_IN
// Description : None
#define USB_EP_ABORT_DONE_EP8_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP8_IN_BITS   _u(0x00010000)
#define USB_EP_ABORT_DONE_EP8_IN_MSB    _u(16)
#define USB_EP_ABORT_DONE_EP8_IN_LSB    _u(16)
#define USB_EP_ABORT_DONE_EP8_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP7_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP7_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP7_OUT_BITS   _u(0x00008000)
#define USB_EP_ABORT_DONE_EP7_OUT_MSB    _u(15)
#define USB_EP_ABORT_DONE_EP7_OUT_LSB    _u(15)
#define USB_EP_ABORT_DONE_EP7_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP7_IN
// Description : None
#define USB_EP_ABORT_DONE_EP7_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP7_IN_BITS   _u(0x00004000)
#define USB_EP_ABORT_DONE_EP7_IN_MSB    _u(14)
#define USB_EP_ABORT_DONE_EP7_IN_LSB    _u(14)
#define USB_EP_ABORT_DONE_EP7_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP6_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP6_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP6_OUT_BITS   _u(0x00002000)
#define USB_EP_ABORT_DONE_EP6_OUT_MSB    _u(13)
#define USB_EP_ABORT_DONE_EP6_OUT_LSB    _u(13)
#define USB_EP_ABORT_DONE_EP6_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP6_IN
// Description : None
#define USB_EP_ABORT_DONE_EP6_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP6_IN_BITS   _u(0x00001000)
#define USB_EP_ABORT_DONE_EP6_IN_MSB    _u(12)
#define USB_EP_ABORT_DONE_EP6_IN_LSB    _u(12)
#define USB_EP_ABORT_DONE_EP6_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP5_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP5_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP5_OUT_BITS   _u(0x00000800)
#define USB_EP_ABORT_DONE_EP5_OUT_MSB    _u(11)
#define USB_EP_ABORT_DONE_EP5_OUT_LSB    _u(11)
#define USB_EP_ABORT_DONE_EP5_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP5_IN
// Description : None
#define USB_EP_ABORT_DONE_EP5_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP5_IN_BITS   _u(0x00000400)
#define USB_EP_ABORT_DONE_EP5_IN_MSB    _u(10)
#define USB_EP_ABORT_DONE_EP5_IN_LSB    _u(10)
#define USB_EP_ABORT_DONE_EP5_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP4_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP4_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP4_OUT_BITS   _u(0x00000200)
#define USB_EP_ABORT_DONE_EP4_OUT_MSB    _u(9)
#define USB_EP_ABORT_DONE_EP4_OUT_LSB    _u(9)
#define USB_EP_ABORT_DONE_EP4_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP4_IN
// Description : None
#define USB_EP_ABORT_DONE_EP4_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP4_IN_BITS   _u(0x00000100)
#define USB_EP_ABORT_DONE_EP4_IN_MSB    _u(8)
#define USB_EP_ABORT_DONE_EP4_IN_LSB    _u(8)
#define USB_EP_ABORT_DONE_EP4_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP3_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP3_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP3_OUT_BITS   _u(0x00000080)
#define USB_EP_ABORT_DONE_EP3_OUT_MSB    _u(7)
#define USB_EP_ABORT_DONE_EP3_OUT_LSB    _u(7)
#define USB_EP_ABORT_DONE_EP3_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP3_IN
// Description : None
#define USB_EP_ABORT_DONE_EP3_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP3_IN_BITS   _u(0x00000040)
#define USB_EP_ABORT_DONE_EP3_IN_MSB    _u(6)
#define USB_EP_ABORT_DONE_EP3_IN_LSB    _u(6)
#define USB_EP_ABORT_DONE_EP3_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP2_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP2_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP2_OUT_BITS   _u(0x00000020)
#define USB_EP_ABORT_DONE_EP2_OUT_MSB    _u(5)
#define USB_EP_ABORT_DONE_EP2_OUT_LSB    _u(5)
#define USB_EP_ABORT_DONE_EP2_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP2_IN
// Description : None
#define USB_EP_ABORT_DONE_EP2_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP2_IN_BITS   _u(0x00000010)
#define USB_EP_ABORT_DONE_EP2_IN_MSB    _u(4)
#define USB_EP_ABORT_DONE_EP2_IN_LSB    _u(4)
#define USB_EP_ABORT_DONE_EP2_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP1_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP1_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP1_OUT_BITS   _u(0x00000008)
#define USB_EP_ABORT_DONE_EP1_OUT_MSB    _u(3)
#define USB_EP_ABORT_DONE_EP1_OUT_LSB    _u(3)
#define USB_EP_ABORT_DONE_EP1_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP1_IN
// Description : None
#define USB_EP_ABORT_DONE_EP1_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP1_IN_BITS   _u(0x00000004)
#define USB_EP_ABORT_DONE_EP1_IN_MSB    _u(2)
#define USB_EP_ABORT_DONE_EP1_IN_LSB    _u(2)
#define USB_EP_ABORT_DONE_EP1_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP0_OUT
// Description : None
#define USB_EP_ABORT_DONE_EP0_OUT_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP0_OUT_BITS   _u(0x00000002)
#define USB_EP_ABORT_DONE_EP0_OUT_MSB    _u(1)
#define USB_EP_ABORT_DONE_EP0_OUT_LSB    _u(1)
#define USB_EP_ABORT_DONE_EP0_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_ABORT_DONE_EP0_IN
// Description : None
#define USB_EP_ABORT_DONE_EP0_IN_RESET  _u(0x0)
#define USB_EP_ABORT_DONE_EP0_IN_BITS   _u(0x00000001)
#define USB_EP_ABORT_DONE_EP0_IN_MSB    _u(0)
#define USB_EP_ABORT_DONE_EP0_IN_LSB    _u(0)
#define USB_EP_ABORT_DONE_EP0_IN_ACCESS "WC"
// =============================================================================
// Register    : USB_EP_STALL_ARM
// Description : Device: this bit must be set in conjunction with the `STALL`
//               bit in the buffer control register to send a STALL on EP0. The
//               device controller clears these bits when a SETUP packet is
//               received because the USB spec requires that a STALL condition
//               is cleared when a SETUP packet is received.
#define USB_EP_STALL_ARM_OFFSET _u(0x00000068)
#define USB_EP_STALL_ARM_BITS   _u(0x00000003)
#define USB_EP_STALL_ARM_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_EP_STALL_ARM_EP0_OUT
// Description : None
#define USB_EP_STALL_ARM_EP0_OUT_RESET  _u(0x0)
#define USB_EP_STALL_ARM_EP0_OUT_BITS   _u(0x00000002)
#define USB_EP_STALL_ARM_EP0_OUT_MSB    _u(1)
#define USB_EP_STALL_ARM_EP0_OUT_LSB    _u(1)
#define USB_EP_STALL_ARM_EP0_OUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STALL_ARM_EP0_IN
// Description : None
#define USB_EP_STALL_ARM_EP0_IN_RESET  _u(0x0)
#define USB_EP_STALL_ARM_EP0_IN_BITS   _u(0x00000001)
#define USB_EP_STALL_ARM_EP0_IN_MSB    _u(0)
#define USB_EP_STALL_ARM_EP0_IN_LSB    _u(0)
#define USB_EP_STALL_ARM_EP0_IN_ACCESS "RW"
// =============================================================================
// Register    : USB_NAK_POLL
// Description : Used by the host controller. Sets the wait time in microseconds
//               before trying again if the device replies with a NAK.
#define USB_NAK_POLL_OFFSET _u(0x0000006c)
#define USB_NAK_POLL_BITS   _u(0x03ff03ff)
#define USB_NAK_POLL_RESET  _u(0x00100010)
// -----------------------------------------------------------------------------
// Field       : USB_NAK_POLL_DELAY_FS
// Description : NAK polling interval for a full speed device
#define USB_NAK_POLL_DELAY_FS_RESET  _u(0x010)
#define USB_NAK_POLL_DELAY_FS_BITS   _u(0x03ff0000)
#define USB_NAK_POLL_DELAY_FS_MSB    _u(25)
#define USB_NAK_POLL_DELAY_FS_LSB    _u(16)
#define USB_NAK_POLL_DELAY_FS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_NAK_POLL_DELAY_LS
// Description : NAK polling interval for a low speed device
#define USB_NAK_POLL_DELAY_LS_RESET  _u(0x010)
#define USB_NAK_POLL_DELAY_LS_BITS   _u(0x000003ff)
#define USB_NAK_POLL_DELAY_LS_MSB    _u(9)
#define USB_NAK_POLL_DELAY_LS_LSB    _u(0)
#define USB_NAK_POLL_DELAY_LS_ACCESS "RW"
// =============================================================================
// Register    : USB_EP_STATUS_STALL_NAK
// Description : Device: bits are set when the `IRQ_ON_NAK` or `IRQ_ON_STALL`
//               bits are set. For EP0 this comes from `SIE_CTRL`. For all other
//               endpoints it comes from the endpoint control register.
#define USB_EP_STATUS_STALL_NAK_OFFSET _u(0x00000070)
#define USB_EP_STATUS_STALL_NAK_BITS   _u(0xffffffff)
#define USB_EP_STATUS_STALL_NAK_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP15_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP15_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP15_OUT_BITS   _u(0x80000000)
#define USB_EP_STATUS_STALL_NAK_EP15_OUT_MSB    _u(31)
#define USB_EP_STATUS_STALL_NAK_EP15_OUT_LSB    _u(31)
#define USB_EP_STATUS_STALL_NAK_EP15_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP15_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP15_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP15_IN_BITS   _u(0x40000000)
#define USB_EP_STATUS_STALL_NAK_EP15_IN_MSB    _u(30)
#define USB_EP_STATUS_STALL_NAK_EP15_IN_LSB    _u(30)
#define USB_EP_STATUS_STALL_NAK_EP15_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP14_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP14_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP14_OUT_BITS   _u(0x20000000)
#define USB_EP_STATUS_STALL_NAK_EP14_OUT_MSB    _u(29)
#define USB_EP_STATUS_STALL_NAK_EP14_OUT_LSB    _u(29)
#define USB_EP_STATUS_STALL_NAK_EP14_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP14_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP14_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP14_IN_BITS   _u(0x10000000)
#define USB_EP_STATUS_STALL_NAK_EP14_IN_MSB    _u(28)
#define USB_EP_STATUS_STALL_NAK_EP14_IN_LSB    _u(28)
#define USB_EP_STATUS_STALL_NAK_EP14_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP13_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP13_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP13_OUT_BITS   _u(0x08000000)
#define USB_EP_STATUS_STALL_NAK_EP13_OUT_MSB    _u(27)
#define USB_EP_STATUS_STALL_NAK_EP13_OUT_LSB    _u(27)
#define USB_EP_STATUS_STALL_NAK_EP13_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP13_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP13_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP13_IN_BITS   _u(0x04000000)
#define USB_EP_STATUS_STALL_NAK_EP13_IN_MSB    _u(26)
#define USB_EP_STATUS_STALL_NAK_EP13_IN_LSB    _u(26)
#define USB_EP_STATUS_STALL_NAK_EP13_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP12_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP12_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP12_OUT_BITS   _u(0x02000000)
#define USB_EP_STATUS_STALL_NAK_EP12_OUT_MSB    _u(25)
#define USB_EP_STATUS_STALL_NAK_EP12_OUT_LSB    _u(25)
#define USB_EP_STATUS_STALL_NAK_EP12_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP12_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP12_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP12_IN_BITS   _u(0x01000000)
#define USB_EP_STATUS_STALL_NAK_EP12_IN_MSB    _u(24)
#define USB_EP_STATUS_STALL_NAK_EP12_IN_LSB    _u(24)
#define USB_EP_STATUS_STALL_NAK_EP12_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP11_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP11_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP11_OUT_BITS   _u(0x00800000)
#define USB_EP_STATUS_STALL_NAK_EP11_OUT_MSB    _u(23)
#define USB_EP_STATUS_STALL_NAK_EP11_OUT_LSB    _u(23)
#define USB_EP_STATUS_STALL_NAK_EP11_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP11_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP11_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP11_IN_BITS   _u(0x00400000)
#define USB_EP_STATUS_STALL_NAK_EP11_IN_MSB    _u(22)
#define USB_EP_STATUS_STALL_NAK_EP11_IN_LSB    _u(22)
#define USB_EP_STATUS_STALL_NAK_EP11_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP10_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP10_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP10_OUT_BITS   _u(0x00200000)
#define USB_EP_STATUS_STALL_NAK_EP10_OUT_MSB    _u(21)
#define USB_EP_STATUS_STALL_NAK_EP10_OUT_LSB    _u(21)
#define USB_EP_STATUS_STALL_NAK_EP10_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP10_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP10_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP10_IN_BITS   _u(0x00100000)
#define USB_EP_STATUS_STALL_NAK_EP10_IN_MSB    _u(20)
#define USB_EP_STATUS_STALL_NAK_EP10_IN_LSB    _u(20)
#define USB_EP_STATUS_STALL_NAK_EP10_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP9_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP9_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP9_OUT_BITS   _u(0x00080000)
#define USB_EP_STATUS_STALL_NAK_EP9_OUT_MSB    _u(19)
#define USB_EP_STATUS_STALL_NAK_EP9_OUT_LSB    _u(19)
#define USB_EP_STATUS_STALL_NAK_EP9_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP9_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP9_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP9_IN_BITS   _u(0x00040000)
#define USB_EP_STATUS_STALL_NAK_EP9_IN_MSB    _u(18)
#define USB_EP_STATUS_STALL_NAK_EP9_IN_LSB    _u(18)
#define USB_EP_STATUS_STALL_NAK_EP9_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP8_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP8_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP8_OUT_BITS   _u(0x00020000)
#define USB_EP_STATUS_STALL_NAK_EP8_OUT_MSB    _u(17)
#define USB_EP_STATUS_STALL_NAK_EP8_OUT_LSB    _u(17)
#define USB_EP_STATUS_STALL_NAK_EP8_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP8_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP8_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP8_IN_BITS   _u(0x00010000)
#define USB_EP_STATUS_STALL_NAK_EP8_IN_MSB    _u(16)
#define USB_EP_STATUS_STALL_NAK_EP8_IN_LSB    _u(16)
#define USB_EP_STATUS_STALL_NAK_EP8_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP7_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP7_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP7_OUT_BITS   _u(0x00008000)
#define USB_EP_STATUS_STALL_NAK_EP7_OUT_MSB    _u(15)
#define USB_EP_STATUS_STALL_NAK_EP7_OUT_LSB    _u(15)
#define USB_EP_STATUS_STALL_NAK_EP7_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP7_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP7_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP7_IN_BITS   _u(0x00004000)
#define USB_EP_STATUS_STALL_NAK_EP7_IN_MSB    _u(14)
#define USB_EP_STATUS_STALL_NAK_EP7_IN_LSB    _u(14)
#define USB_EP_STATUS_STALL_NAK_EP7_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP6_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP6_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP6_OUT_BITS   _u(0x00002000)
#define USB_EP_STATUS_STALL_NAK_EP6_OUT_MSB    _u(13)
#define USB_EP_STATUS_STALL_NAK_EP6_OUT_LSB    _u(13)
#define USB_EP_STATUS_STALL_NAK_EP6_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP6_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP6_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP6_IN_BITS   _u(0x00001000)
#define USB_EP_STATUS_STALL_NAK_EP6_IN_MSB    _u(12)
#define USB_EP_STATUS_STALL_NAK_EP6_IN_LSB    _u(12)
#define USB_EP_STATUS_STALL_NAK_EP6_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP5_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP5_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP5_OUT_BITS   _u(0x00000800)
#define USB_EP_STATUS_STALL_NAK_EP5_OUT_MSB    _u(11)
#define USB_EP_STATUS_STALL_NAK_EP5_OUT_LSB    _u(11)
#define USB_EP_STATUS_STALL_NAK_EP5_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP5_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP5_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP5_IN_BITS   _u(0x00000400)
#define USB_EP_STATUS_STALL_NAK_EP5_IN_MSB    _u(10)
#define USB_EP_STATUS_STALL_NAK_EP5_IN_LSB    _u(10)
#define USB_EP_STATUS_STALL_NAK_EP5_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP4_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP4_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP4_OUT_BITS   _u(0x00000200)
#define USB_EP_STATUS_STALL_NAK_EP4_OUT_MSB    _u(9)
#define USB_EP_STATUS_STALL_NAK_EP4_OUT_LSB    _u(9)
#define USB_EP_STATUS_STALL_NAK_EP4_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP4_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP4_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP4_IN_BITS   _u(0x00000100)
#define USB_EP_STATUS_STALL_NAK_EP4_IN_MSB    _u(8)
#define USB_EP_STATUS_STALL_NAK_EP4_IN_LSB    _u(8)
#define USB_EP_STATUS_STALL_NAK_EP4_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP3_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP3_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP3_OUT_BITS   _u(0x00000080)
#define USB_EP_STATUS_STALL_NAK_EP3_OUT_MSB    _u(7)
#define USB_EP_STATUS_STALL_NAK_EP3_OUT_LSB    _u(7)
#define USB_EP_STATUS_STALL_NAK_EP3_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP3_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP3_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP3_IN_BITS   _u(0x00000040)
#define USB_EP_STATUS_STALL_NAK_EP3_IN_MSB    _u(6)
#define USB_EP_STATUS_STALL_NAK_EP3_IN_LSB    _u(6)
#define USB_EP_STATUS_STALL_NAK_EP3_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP2_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP2_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP2_OUT_BITS   _u(0x00000020)
#define USB_EP_STATUS_STALL_NAK_EP2_OUT_MSB    _u(5)
#define USB_EP_STATUS_STALL_NAK_EP2_OUT_LSB    _u(5)
#define USB_EP_STATUS_STALL_NAK_EP2_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP2_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP2_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP2_IN_BITS   _u(0x00000010)
#define USB_EP_STATUS_STALL_NAK_EP2_IN_MSB    _u(4)
#define USB_EP_STATUS_STALL_NAK_EP2_IN_LSB    _u(4)
#define USB_EP_STATUS_STALL_NAK_EP2_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP1_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP1_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP1_OUT_BITS   _u(0x00000008)
#define USB_EP_STATUS_STALL_NAK_EP1_OUT_MSB    _u(3)
#define USB_EP_STATUS_STALL_NAK_EP1_OUT_LSB    _u(3)
#define USB_EP_STATUS_STALL_NAK_EP1_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP1_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP1_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP1_IN_BITS   _u(0x00000004)
#define USB_EP_STATUS_STALL_NAK_EP1_IN_MSB    _u(2)
#define USB_EP_STATUS_STALL_NAK_EP1_IN_LSB    _u(2)
#define USB_EP_STATUS_STALL_NAK_EP1_IN_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP0_OUT
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP0_OUT_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP0_OUT_BITS   _u(0x00000002)
#define USB_EP_STATUS_STALL_NAK_EP0_OUT_MSB    _u(1)
#define USB_EP_STATUS_STALL_NAK_EP0_OUT_LSB    _u(1)
#define USB_EP_STATUS_STALL_NAK_EP0_OUT_ACCESS "WC"
// -----------------------------------------------------------------------------
// Field       : USB_EP_STATUS_STALL_NAK_EP0_IN
// Description : None
#define USB_EP_STATUS_STALL_NAK_EP0_IN_RESET  _u(0x0)
#define USB_EP_STATUS_STALL_NAK_EP0_IN_BITS   _u(0x00000001)
#define USB_EP_STATUS_STALL_NAK_EP0_IN_MSB    _u(0)
#define USB_EP_STATUS_STALL_NAK_EP0_IN_LSB    _u(0)
#define USB_EP_STATUS_STALL_NAK_EP0_IN_ACCESS "WC"
// =============================================================================
// Register    : USB_USB_MUXING
// Description : Where to connect the USB controller. Should be to_phy by
//               default.
#define USB_USB_MUXING_OFFSET _u(0x00000074)
#define USB_USB_MUXING_BITS   _u(0x0000000f)
#define USB_USB_MUXING_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_USB_MUXING_SOFTCON
// Description : None
#define USB_USB_MUXING_SOFTCON_RESET  _u(0x0)
#define USB_USB_MUXING_SOFTCON_BITS   _u(0x00000008)
#define USB_USB_MUXING_SOFTCON_MSB    _u(3)
#define USB_USB_MUXING_SOFTCON_LSB    _u(3)
#define USB_USB_MUXING_SOFTCON_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USB_MUXING_TO_DIGITAL_PAD
// Description : None
#define USB_USB_MUXING_TO_DIGITAL_PAD_RESET  _u(0x0)
#define USB_USB_MUXING_TO_DIGITAL_PAD_BITS   _u(0x00000004)
#define USB_USB_MUXING_TO_DIGITAL_PAD_MSB    _u(2)
#define USB_USB_MUXING_TO_DIGITAL_PAD_LSB    _u(2)
#define USB_USB_MUXING_TO_DIGITAL_PAD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USB_MUXING_TO_EXTPHY
// Description : None
#define USB_USB_MUXING_TO_EXTPHY_RESET  _u(0x0)
#define USB_USB_MUXING_TO_EXTPHY_BITS   _u(0x00000002)
#define USB_USB_MUXING_TO_EXTPHY_MSB    _u(1)
#define USB_USB_MUXING_TO_EXTPHY_LSB    _u(1)
#define USB_USB_MUXING_TO_EXTPHY_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USB_MUXING_TO_PHY
// Description : None
#define USB_USB_MUXING_TO_PHY_RESET  _u(0x0)
#define USB_USB_MUXING_TO_PHY_BITS   _u(0x00000001)
#define USB_USB_MUXING_TO_PHY_MSB    _u(0)
#define USB_USB_MUXING_TO_PHY_LSB    _u(0)
#define USB_USB_MUXING_TO_PHY_ACCESS "RW"
// =============================================================================
// Register    : USB_USB_PWR
// Description : Overrides for the power signals in the event that the VBUS
//               signals are not hooked up to GPIO. Set the value of the
//               override and then the override enable to switch over to the
//               override value.
#define USB_USB_PWR_OFFSET _u(0x00000078)
#define USB_USB_PWR_BITS   _u(0x0000003f)
#define USB_USB_PWR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_USB_PWR_OVERCURR_DETECT_EN
// Description : None
#define USB_USB_PWR_OVERCURR_DETECT_EN_RESET  _u(0x0)
#define USB_USB_PWR_OVERCURR_DETECT_EN_BITS   _u(0x00000020)
#define USB_USB_PWR_OVERCURR_DETECT_EN_MSB    _u(5)
#define USB_USB_PWR_OVERCURR_DETECT_EN_LSB    _u(5)
#define USB_USB_PWR_OVERCURR_DETECT_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USB_PWR_OVERCURR_DETECT
// Description : None
#define USB_USB_PWR_OVERCURR_DETECT_RESET  _u(0x0)
#define USB_USB_PWR_OVERCURR_DETECT_BITS   _u(0x00000010)
#define USB_USB_PWR_OVERCURR_DETECT_MSB    _u(4)
#define USB_USB_PWR_OVERCURR_DETECT_LSB    _u(4)
#define USB_USB_PWR_OVERCURR_DETECT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USB_PWR_VBUS_DETECT_OVERRIDE_EN
// Description : None
#define USB_USB_PWR_VBUS_DETECT_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USB_PWR_VBUS_DETECT_OVERRIDE_EN_BITS   _u(0x00000008)
#define USB_USB_PWR_VBUS_DETECT_OVERRIDE_EN_MSB    _u(3)
#define USB_USB_PWR_VBUS_DETECT_OVERRIDE_EN_LSB    _u(3)
#define USB_USB_PWR_VBUS_DETECT_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USB_PWR_VBUS_DETECT
// Description : None
#define USB_USB_PWR_VBUS_DETECT_RESET  _u(0x0)
#define USB_USB_PWR_VBUS_DETECT_BITS   _u(0x00000004)
#define USB_USB_PWR_VBUS_DETECT_MSB    _u(2)
#define USB_USB_PWR_VBUS_DETECT_LSB    _u(2)
#define USB_USB_PWR_VBUS_DETECT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USB_PWR_VBUS_EN_OVERRIDE_EN
// Description : None
#define USB_USB_PWR_VBUS_EN_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USB_PWR_VBUS_EN_OVERRIDE_EN_BITS   _u(0x00000002)
#define USB_USB_PWR_VBUS_EN_OVERRIDE_EN_MSB    _u(1)
#define USB_USB_PWR_VBUS_EN_OVERRIDE_EN_LSB    _u(1)
#define USB_USB_PWR_VBUS_EN_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USB_PWR_VBUS_EN
// Description : None
#define USB_USB_PWR_VBUS_EN_RESET  _u(0x0)
#define USB_USB_PWR_VBUS_EN_BITS   _u(0x00000001)
#define USB_USB_PWR_VBUS_EN_MSB    _u(0)
#define USB_USB_PWR_VBUS_EN_LSB    _u(0)
#define USB_USB_PWR_VBUS_EN_ACCESS "RW"
// =============================================================================
// Register    : USB_USBPHY_DIRECT
// Description : This register allows for direct control of the USB phy. Use in
//               conjunction with usbphy_direct_override register to enable each
//               override bit.
#define USB_USBPHY_DIRECT_OFFSET _u(0x0000007c)
#define USB_USBPHY_DIRECT_BITS   _u(0x007fff77)
#define USB_USBPHY_DIRECT_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_DM_OVV
// Description : DM over voltage
#define USB_USBPHY_DIRECT_DM_OVV_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_DM_OVV_BITS   _u(0x00400000)
#define USB_USBPHY_DIRECT_DM_OVV_MSB    _u(22)
#define USB_USBPHY_DIRECT_DM_OVV_LSB    _u(22)
#define USB_USBPHY_DIRECT_DM_OVV_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_DP_OVV
// Description : DP over voltage
#define USB_USBPHY_DIRECT_DP_OVV_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_DP_OVV_BITS   _u(0x00200000)
#define USB_USBPHY_DIRECT_DP_OVV_MSB    _u(21)
#define USB_USBPHY_DIRECT_DP_OVV_LSB    _u(21)
#define USB_USBPHY_DIRECT_DP_OVV_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_DM_OVCN
// Description : DM overcurrent
#define USB_USBPHY_DIRECT_DM_OVCN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_DM_OVCN_BITS   _u(0x00100000)
#define USB_USBPHY_DIRECT_DM_OVCN_MSB    _u(20)
#define USB_USBPHY_DIRECT_DM_OVCN_LSB    _u(20)
#define USB_USBPHY_DIRECT_DM_OVCN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_DP_OVCN
// Description : DP overcurrent
#define USB_USBPHY_DIRECT_DP_OVCN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_DP_OVCN_BITS   _u(0x00080000)
#define USB_USBPHY_DIRECT_DP_OVCN_MSB    _u(19)
#define USB_USBPHY_DIRECT_DP_OVCN_LSB    _u(19)
#define USB_USBPHY_DIRECT_DP_OVCN_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_RX_DM
// Description : DPM pin state
#define USB_USBPHY_DIRECT_RX_DM_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_RX_DM_BITS   _u(0x00040000)
#define USB_USBPHY_DIRECT_RX_DM_MSB    _u(18)
#define USB_USBPHY_DIRECT_RX_DM_LSB    _u(18)
#define USB_USBPHY_DIRECT_RX_DM_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_RX_DP
// Description : DPP pin state
#define USB_USBPHY_DIRECT_RX_DP_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_RX_DP_BITS   _u(0x00020000)
#define USB_USBPHY_DIRECT_RX_DP_MSB    _u(17)
#define USB_USBPHY_DIRECT_RX_DP_LSB    _u(17)
#define USB_USBPHY_DIRECT_RX_DP_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_RX_DD
// Description : Differential RX
#define USB_USBPHY_DIRECT_RX_DD_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_RX_DD_BITS   _u(0x00010000)
#define USB_USBPHY_DIRECT_RX_DD_MSB    _u(16)
#define USB_USBPHY_DIRECT_RX_DD_LSB    _u(16)
#define USB_USBPHY_DIRECT_RX_DD_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_TX_DIFFMODE
// Description : TX_DIFFMODE=0: Single ended mode
//               TX_DIFFMODE=1: Differential drive mode (TX_DM, TX_DM_OE
//               ignored)
#define USB_USBPHY_DIRECT_TX_DIFFMODE_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_TX_DIFFMODE_BITS   _u(0x00008000)
#define USB_USBPHY_DIRECT_TX_DIFFMODE_MSB    _u(15)
#define USB_USBPHY_DIRECT_TX_DIFFMODE_LSB    _u(15)
#define USB_USBPHY_DIRECT_TX_DIFFMODE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_TX_FSSLEW
// Description : TX_FSSLEW=0: Low speed slew rate
//               TX_FSSLEW=1: Full speed slew rate
#define USB_USBPHY_DIRECT_TX_FSSLEW_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_TX_FSSLEW_BITS   _u(0x00004000)
#define USB_USBPHY_DIRECT_TX_FSSLEW_MSB    _u(14)
#define USB_USBPHY_DIRECT_TX_FSSLEW_LSB    _u(14)
#define USB_USBPHY_DIRECT_TX_FSSLEW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_TX_PD
// Description : TX power down override (if override enable is set). 1 = powered
//               down.
#define USB_USBPHY_DIRECT_TX_PD_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_TX_PD_BITS   _u(0x00002000)
#define USB_USBPHY_DIRECT_TX_PD_MSB    _u(13)
#define USB_USBPHY_DIRECT_TX_PD_LSB    _u(13)
#define USB_USBPHY_DIRECT_TX_PD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_RX_PD
// Description : RX power down override (if override enable is set). 1 = powered
//               down.
#define USB_USBPHY_DIRECT_RX_PD_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_RX_PD_BITS   _u(0x00001000)
#define USB_USBPHY_DIRECT_RX_PD_MSB    _u(12)
#define USB_USBPHY_DIRECT_RX_PD_LSB    _u(12)
#define USB_USBPHY_DIRECT_RX_PD_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_TX_DM
// Description : Output data. TX_DIFFMODE=1, Ignored
//               TX_DIFFMODE=0, Drives DPM only. TX_DM_OE=1 to enable drive.
//               DPM=TX_DM
#define USB_USBPHY_DIRECT_TX_DM_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_TX_DM_BITS   _u(0x00000800)
#define USB_USBPHY_DIRECT_TX_DM_MSB    _u(11)
#define USB_USBPHY_DIRECT_TX_DM_LSB    _u(11)
#define USB_USBPHY_DIRECT_TX_DM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_TX_DP
// Description : Output data. If TX_DIFFMODE=1, Drives DPP/DPM diff pair.
//               TX_DP_OE=1 to enable drive. DPP=TX_DP, DPM=~TX_DP
//               If TX_DIFFMODE=0, Drives DPP only. TX_DP_OE=1 to enable drive.
//               DPP=TX_DP
#define USB_USBPHY_DIRECT_TX_DP_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_TX_DP_BITS   _u(0x00000400)
#define USB_USBPHY_DIRECT_TX_DP_MSB    _u(10)
#define USB_USBPHY_DIRECT_TX_DP_LSB    _u(10)
#define USB_USBPHY_DIRECT_TX_DP_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_TX_DM_OE
// Description : Output enable. If TX_DIFFMODE=1, Ignored.
//               If TX_DIFFMODE=0, OE for DPM only. 0 - DPM in Hi-Z state; 1 -
//               DPM driving
#define USB_USBPHY_DIRECT_TX_DM_OE_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_TX_DM_OE_BITS   _u(0x00000200)
#define USB_USBPHY_DIRECT_TX_DM_OE_MSB    _u(9)
#define USB_USBPHY_DIRECT_TX_DM_OE_LSB    _u(9)
#define USB_USBPHY_DIRECT_TX_DM_OE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_TX_DP_OE
// Description : Output enable. If TX_DIFFMODE=1, OE for DPP/DPM diff pair. 0 -
//               DPP/DPM in Hi-Z state; 1 - DPP/DPM driving
//               If TX_DIFFMODE=0, OE for DPP only. 0 - DPP in Hi-Z state; 1 -
//               DPP driving
#define USB_USBPHY_DIRECT_TX_DP_OE_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_TX_DP_OE_BITS   _u(0x00000100)
#define USB_USBPHY_DIRECT_TX_DP_OE_MSB    _u(8)
#define USB_USBPHY_DIRECT_TX_DP_OE_LSB    _u(8)
#define USB_USBPHY_DIRECT_TX_DP_OE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_DM_PULLDN_EN
// Description : DM pull down enable
#define USB_USBPHY_DIRECT_DM_PULLDN_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_DM_PULLDN_EN_BITS   _u(0x00000040)
#define USB_USBPHY_DIRECT_DM_PULLDN_EN_MSB    _u(6)
#define USB_USBPHY_DIRECT_DM_PULLDN_EN_LSB    _u(6)
#define USB_USBPHY_DIRECT_DM_PULLDN_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_DM_PULLUP_EN
// Description : DM pull up enable
#define USB_USBPHY_DIRECT_DM_PULLUP_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_DM_PULLUP_EN_BITS   _u(0x00000020)
#define USB_USBPHY_DIRECT_DM_PULLUP_EN_MSB    _u(5)
#define USB_USBPHY_DIRECT_DM_PULLUP_EN_LSB    _u(5)
#define USB_USBPHY_DIRECT_DM_PULLUP_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_DM_PULLUP_HISEL
// Description : Enable the second DM pull up resistor. 0 - Pull = Rpu2; 1 -
//               Pull = Rpu1 + Rpu2
#define USB_USBPHY_DIRECT_DM_PULLUP_HISEL_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_DM_PULLUP_HISEL_BITS   _u(0x00000010)
#define USB_USBPHY_DIRECT_DM_PULLUP_HISEL_MSB    _u(4)
#define USB_USBPHY_DIRECT_DM_PULLUP_HISEL_LSB    _u(4)
#define USB_USBPHY_DIRECT_DM_PULLUP_HISEL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_DP_PULLDN_EN
// Description : DP pull down enable
#define USB_USBPHY_DIRECT_DP_PULLDN_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_DP_PULLDN_EN_BITS   _u(0x00000004)
#define USB_USBPHY_DIRECT_DP_PULLDN_EN_MSB    _u(2)
#define USB_USBPHY_DIRECT_DP_PULLDN_EN_LSB    _u(2)
#define USB_USBPHY_DIRECT_DP_PULLDN_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_DP_PULLUP_EN
// Description : DP pull up enable
#define USB_USBPHY_DIRECT_DP_PULLUP_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_DP_PULLUP_EN_BITS   _u(0x00000002)
#define USB_USBPHY_DIRECT_DP_PULLUP_EN_MSB    _u(1)
#define USB_USBPHY_DIRECT_DP_PULLUP_EN_LSB    _u(1)
#define USB_USBPHY_DIRECT_DP_PULLUP_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_DP_PULLUP_HISEL
// Description : Enable the second DP pull up resistor. 0 - Pull = Rpu2; 1 -
//               Pull = Rpu1 + Rpu2
#define USB_USBPHY_DIRECT_DP_PULLUP_HISEL_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_DP_PULLUP_HISEL_BITS   _u(0x00000001)
#define USB_USBPHY_DIRECT_DP_PULLUP_HISEL_MSB    _u(0)
#define USB_USBPHY_DIRECT_DP_PULLUP_HISEL_LSB    _u(0)
#define USB_USBPHY_DIRECT_DP_PULLUP_HISEL_ACCESS "RW"
// =============================================================================
// Register    : USB_USBPHY_DIRECT_OVERRIDE
// Description : Override enable for each control in usbphy_direct
#define USB_USBPHY_DIRECT_OVERRIDE_OFFSET _u(0x00000080)
#define USB_USBPHY_DIRECT_OVERRIDE_BITS   _u(0x00009fff)
#define USB_USBPHY_DIRECT_OVERRIDE_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_TX_DIFFMODE_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DIFFMODE_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DIFFMODE_OVERRIDE_EN_BITS   _u(0x00008000)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DIFFMODE_OVERRIDE_EN_MSB    _u(15)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DIFFMODE_OVERRIDE_EN_LSB    _u(15)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DIFFMODE_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_OVERRIDE_EN_BITS   _u(0x00001000)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_OVERRIDE_EN_MSB    _u(12)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_OVERRIDE_EN_LSB    _u(12)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_TX_FSSLEW_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_TX_FSSLEW_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_FSSLEW_OVERRIDE_EN_BITS   _u(0x00000800)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_FSSLEW_OVERRIDE_EN_MSB    _u(11)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_FSSLEW_OVERRIDE_EN_LSB    _u(11)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_FSSLEW_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_TX_PD_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_TX_PD_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_PD_OVERRIDE_EN_BITS   _u(0x00000400)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_PD_OVERRIDE_EN_MSB    _u(10)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_PD_OVERRIDE_EN_LSB    _u(10)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_PD_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_RX_PD_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_RX_PD_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_RX_PD_OVERRIDE_EN_BITS   _u(0x00000200)
#define USB_USBPHY_DIRECT_OVERRIDE_RX_PD_OVERRIDE_EN_MSB    _u(9)
#define USB_USBPHY_DIRECT_OVERRIDE_RX_PD_OVERRIDE_EN_LSB    _u(9)
#define USB_USBPHY_DIRECT_OVERRIDE_RX_PD_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OVERRIDE_EN_BITS   _u(0x00000100)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OVERRIDE_EN_MSB    _u(8)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OVERRIDE_EN_LSB    _u(8)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OVERRIDE_EN_BITS   _u(0x00000080)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OVERRIDE_EN_MSB    _u(7)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OVERRIDE_EN_LSB    _u(7)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OE_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OE_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OE_OVERRIDE_EN_BITS   _u(0x00000040)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OE_OVERRIDE_EN_MSB    _u(6)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OE_OVERRIDE_EN_LSB    _u(6)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DM_OE_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OE_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OE_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OE_OVERRIDE_EN_BITS   _u(0x00000020)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OE_OVERRIDE_EN_MSB    _u(5)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OE_OVERRIDE_EN_LSB    _u(5)
#define USB_USBPHY_DIRECT_OVERRIDE_TX_DP_OE_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_DM_PULLDN_EN_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLDN_EN_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLDN_EN_OVERRIDE_EN_BITS   _u(0x00000010)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLDN_EN_OVERRIDE_EN_MSB    _u(4)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLDN_EN_OVERRIDE_EN_LSB    _u(4)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLDN_EN_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_DP_PULLDN_EN_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLDN_EN_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLDN_EN_OVERRIDE_EN_BITS   _u(0x00000008)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLDN_EN_OVERRIDE_EN_MSB    _u(3)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLDN_EN_OVERRIDE_EN_LSB    _u(3)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLDN_EN_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_EN_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_EN_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_EN_OVERRIDE_EN_BITS   _u(0x00000004)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_EN_OVERRIDE_EN_MSB    _u(2)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_EN_OVERRIDE_EN_LSB    _u(2)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_EN_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_HISEL_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_HISEL_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_HISEL_OVERRIDE_EN_BITS   _u(0x00000002)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_HISEL_OVERRIDE_EN_MSB    _u(1)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_HISEL_OVERRIDE_EN_LSB    _u(1)
#define USB_USBPHY_DIRECT_OVERRIDE_DM_PULLUP_HISEL_OVERRIDE_EN_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_HISEL_OVERRIDE_EN
// Description : None
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_HISEL_OVERRIDE_EN_RESET  _u(0x0)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_HISEL_OVERRIDE_EN_BITS   _u(0x00000001)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_HISEL_OVERRIDE_EN_MSB    _u(0)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_HISEL_OVERRIDE_EN_LSB    _u(0)
#define USB_USBPHY_DIRECT_OVERRIDE_DP_PULLUP_HISEL_OVERRIDE_EN_ACCESS "RW"
// =============================================================================
// Register    : USB_USBPHY_TRIM
// Description : Used to adjust trim values of USB phy pull down resistors.
#define USB_USBPHY_TRIM_OFFSET _u(0x00000084)
#define USB_USBPHY_TRIM_BITS   _u(0x00001f1f)
#define USB_USBPHY_TRIM_RESET  _u(0x00001f1f)
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_TRIM_DM_PULLDN_TRIM
// Description : Value to drive to USB PHY
//               DM pulldown resistor trim control
//               Experimental data suggests that the reset value will work, but
//               this register allows adjustment if required
#define USB_USBPHY_TRIM_DM_PULLDN_TRIM_RESET  _u(0x1f)
#define USB_USBPHY_TRIM_DM_PULLDN_TRIM_BITS   _u(0x00001f00)
#define USB_USBPHY_TRIM_DM_PULLDN_TRIM_MSB    _u(12)
#define USB_USBPHY_TRIM_DM_PULLDN_TRIM_LSB    _u(8)
#define USB_USBPHY_TRIM_DM_PULLDN_TRIM_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_USBPHY_TRIM_DP_PULLDN_TRIM
// Description : Value to drive to USB PHY
//               DP pulldown resistor trim control
//               Experimental data suggests that the reset value will work, but
//               this register allows adjustment if required
#define USB_USBPHY_TRIM_DP_PULLDN_TRIM_RESET  _u(0x1f)
#define USB_USBPHY_TRIM_DP_PULLDN_TRIM_BITS   _u(0x0000001f)
#define USB_USBPHY_TRIM_DP_PULLDN_TRIM_MSB    _u(4)
#define USB_USBPHY_TRIM_DP_PULLDN_TRIM_LSB    _u(0)
#define USB_USBPHY_TRIM_DP_PULLDN_TRIM_ACCESS "RW"
// =============================================================================
// Register    : USB_INTR
// Description : Raw Interrupts
#define USB_INTR_OFFSET _u(0x0000008c)
#define USB_INTR_BITS   _u(0x000fffff)
#define USB_INTR_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_INTR_EP_STALL_NAK
// Description : Raised when any bit in EP_STATUS_STALL_NAK is set. Clear by
//               clearing all bits in EP_STATUS_STALL_NAK.
#define USB_INTR_EP_STALL_NAK_RESET  _u(0x0)
#define USB_INTR_EP_STALL_NAK_BITS   _u(0x00080000)
#define USB_INTR_EP_STALL_NAK_MSB    _u(19)
#define USB_INTR_EP_STALL_NAK_LSB    _u(19)
#define USB_INTR_EP_STALL_NAK_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_ABORT_DONE
// Description : Raised when any bit in ABORT_DONE is set. Clear by clearing all
//               bits in ABORT_DONE.
#define USB_INTR_ABORT_DONE_RESET  _u(0x0)
#define USB_INTR_ABORT_DONE_BITS   _u(0x00040000)
#define USB_INTR_ABORT_DONE_MSB    _u(18)
#define USB_INTR_ABORT_DONE_LSB    _u(18)
#define USB_INTR_ABORT_DONE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_DEV_SOF
// Description : Set every time the device receives a SOF (Start of Frame)
//               packet. Cleared by reading SOF_RD
#define USB_INTR_DEV_SOF_RESET  _u(0x0)
#define USB_INTR_DEV_SOF_BITS   _u(0x00020000)
#define USB_INTR_DEV_SOF_MSB    _u(17)
#define USB_INTR_DEV_SOF_LSB    _u(17)
#define USB_INTR_DEV_SOF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_SETUP_REQ
// Description : Device. Source: SIE_STATUS.SETUP_REC
#define USB_INTR_SETUP_REQ_RESET  _u(0x0)
#define USB_INTR_SETUP_REQ_BITS   _u(0x00010000)
#define USB_INTR_SETUP_REQ_MSB    _u(16)
#define USB_INTR_SETUP_REQ_LSB    _u(16)
#define USB_INTR_SETUP_REQ_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_DEV_RESUME_FROM_HOST
// Description : Set when the device receives a resume from the host. Cleared by
//               writing to SIE_STATUS.RESUME
#define USB_INTR_DEV_RESUME_FROM_HOST_RESET  _u(0x0)
#define USB_INTR_DEV_RESUME_FROM_HOST_BITS   _u(0x00008000)
#define USB_INTR_DEV_RESUME_FROM_HOST_MSB    _u(15)
#define USB_INTR_DEV_RESUME_FROM_HOST_LSB    _u(15)
#define USB_INTR_DEV_RESUME_FROM_HOST_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_DEV_SUSPEND
// Description : Set when the device suspend state changes. Cleared by writing
//               to SIE_STATUS.SUSPENDED
#define USB_INTR_DEV_SUSPEND_RESET  _u(0x0)
#define USB_INTR_DEV_SUSPEND_BITS   _u(0x00004000)
#define USB_INTR_DEV_SUSPEND_MSB    _u(14)
#define USB_INTR_DEV_SUSPEND_LSB    _u(14)
#define USB_INTR_DEV_SUSPEND_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_DEV_CONN_DIS
// Description : Set when the device connection state changes. Cleared by
//               writing to SIE_STATUS.CONNECTED
#define USB_INTR_DEV_CONN_DIS_RESET  _u(0x0)
#define USB_INTR_DEV_CONN_DIS_BITS   _u(0x00002000)
#define USB_INTR_DEV_CONN_DIS_MSB    _u(13)
#define USB_INTR_DEV_CONN_DIS_LSB    _u(13)
#define USB_INTR_DEV_CONN_DIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_BUS_RESET
// Description : Source: SIE_STATUS.BUS_RESET
#define USB_INTR_BUS_RESET_RESET  _u(0x0)
#define USB_INTR_BUS_RESET_BITS   _u(0x00001000)
#define USB_INTR_BUS_RESET_MSB    _u(12)
#define USB_INTR_BUS_RESET_LSB    _u(12)
#define USB_INTR_BUS_RESET_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_VBUS_DETECT
// Description : Source: SIE_STATUS.VBUS_DETECTED
#define USB_INTR_VBUS_DETECT_RESET  _u(0x0)
#define USB_INTR_VBUS_DETECT_BITS   _u(0x00000800)
#define USB_INTR_VBUS_DETECT_MSB    _u(11)
#define USB_INTR_VBUS_DETECT_LSB    _u(11)
#define USB_INTR_VBUS_DETECT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_STALL
// Description : Source: SIE_STATUS.STALL_REC
#define USB_INTR_STALL_RESET  _u(0x0)
#define USB_INTR_STALL_BITS   _u(0x00000400)
#define USB_INTR_STALL_MSB    _u(10)
#define USB_INTR_STALL_LSB    _u(10)
#define USB_INTR_STALL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_ERROR_CRC
// Description : Source: SIE_STATUS.CRC_ERROR
#define USB_INTR_ERROR_CRC_RESET  _u(0x0)
#define USB_INTR_ERROR_CRC_BITS   _u(0x00000200)
#define USB_INTR_ERROR_CRC_MSB    _u(9)
#define USB_INTR_ERROR_CRC_LSB    _u(9)
#define USB_INTR_ERROR_CRC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_ERROR_BIT_STUFF
// Description : Source: SIE_STATUS.BIT_STUFF_ERROR
#define USB_INTR_ERROR_BIT_STUFF_RESET  _u(0x0)
#define USB_INTR_ERROR_BIT_STUFF_BITS   _u(0x00000100)
#define USB_INTR_ERROR_BIT_STUFF_MSB    _u(8)
#define USB_INTR_ERROR_BIT_STUFF_LSB    _u(8)
#define USB_INTR_ERROR_BIT_STUFF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_ERROR_RX_OVERFLOW
// Description : Source: SIE_STATUS.RX_OVERFLOW
#define USB_INTR_ERROR_RX_OVERFLOW_RESET  _u(0x0)
#define USB_INTR_ERROR_RX_OVERFLOW_BITS   _u(0x00000080)
#define USB_INTR_ERROR_RX_OVERFLOW_MSB    _u(7)
#define USB_INTR_ERROR_RX_OVERFLOW_LSB    _u(7)
#define USB_INTR_ERROR_RX_OVERFLOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_ERROR_RX_TIMEOUT
// Description : Source: SIE_STATUS.RX_TIMEOUT
#define USB_INTR_ERROR_RX_TIMEOUT_RESET  _u(0x0)
#define USB_INTR_ERROR_RX_TIMEOUT_BITS   _u(0x00000040)
#define USB_INTR_ERROR_RX_TIMEOUT_MSB    _u(6)
#define USB_INTR_ERROR_RX_TIMEOUT_LSB    _u(6)
#define USB_INTR_ERROR_RX_TIMEOUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_ERROR_DATA_SEQ
// Description : Source: SIE_STATUS.DATA_SEQ_ERROR
#define USB_INTR_ERROR_DATA_SEQ_RESET  _u(0x0)
#define USB_INTR_ERROR_DATA_SEQ_BITS   _u(0x00000020)
#define USB_INTR_ERROR_DATA_SEQ_MSB    _u(5)
#define USB_INTR_ERROR_DATA_SEQ_LSB    _u(5)
#define USB_INTR_ERROR_DATA_SEQ_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_BUFF_STATUS
// Description : Raised when any bit in BUFF_STATUS is set. Clear by clearing
//               all bits in BUFF_STATUS.
#define USB_INTR_BUFF_STATUS_RESET  _u(0x0)
#define USB_INTR_BUFF_STATUS_BITS   _u(0x00000010)
#define USB_INTR_BUFF_STATUS_MSB    _u(4)
#define USB_INTR_BUFF_STATUS_LSB    _u(4)
#define USB_INTR_BUFF_STATUS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_TRANS_COMPLETE
// Description : Raised every time SIE_STATUS.TRANS_COMPLETE is set. Clear by
//               writing to this bit.
#define USB_INTR_TRANS_COMPLETE_RESET  _u(0x0)
#define USB_INTR_TRANS_COMPLETE_BITS   _u(0x00000008)
#define USB_INTR_TRANS_COMPLETE_MSB    _u(3)
#define USB_INTR_TRANS_COMPLETE_LSB    _u(3)
#define USB_INTR_TRANS_COMPLETE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_HOST_SOF
// Description : Host: raised every time the host sends a SOF (Start of Frame).
//               Cleared by reading SOF_RD
#define USB_INTR_HOST_SOF_RESET  _u(0x0)
#define USB_INTR_HOST_SOF_BITS   _u(0x00000004)
#define USB_INTR_HOST_SOF_MSB    _u(2)
#define USB_INTR_HOST_SOF_LSB    _u(2)
#define USB_INTR_HOST_SOF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_HOST_RESUME
// Description : Host: raised when a device wakes up the host. Cleared by
//               writing to SIE_STATUS.RESUME
#define USB_INTR_HOST_RESUME_RESET  _u(0x0)
#define USB_INTR_HOST_RESUME_BITS   _u(0x00000002)
#define USB_INTR_HOST_RESUME_MSB    _u(1)
#define USB_INTR_HOST_RESUME_LSB    _u(1)
#define USB_INTR_HOST_RESUME_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTR_HOST_CONN_DIS
// Description : Host: raised when a device is connected or disconnected (i.e.
//               when SIE_STATUS.SPEED changes). Cleared by writing to
//               SIE_STATUS.SPEED
#define USB_INTR_HOST_CONN_DIS_RESET  _u(0x0)
#define USB_INTR_HOST_CONN_DIS_BITS   _u(0x00000001)
#define USB_INTR_HOST_CONN_DIS_MSB    _u(0)
#define USB_INTR_HOST_CONN_DIS_LSB    _u(0)
#define USB_INTR_HOST_CONN_DIS_ACCESS "RO"
// =============================================================================
// Register    : USB_INTE
// Description : Interrupt Enable
#define USB_INTE_OFFSET _u(0x00000090)
#define USB_INTE_BITS   _u(0x000fffff)
#define USB_INTE_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_INTE_EP_STALL_NAK
// Description : Raised when any bit in EP_STATUS_STALL_NAK is set. Clear by
//               clearing all bits in EP_STATUS_STALL_NAK.
#define USB_INTE_EP_STALL_NAK_RESET  _u(0x0)
#define USB_INTE_EP_STALL_NAK_BITS   _u(0x00080000)
#define USB_INTE_EP_STALL_NAK_MSB    _u(19)
#define USB_INTE_EP_STALL_NAK_LSB    _u(19)
#define USB_INTE_EP_STALL_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_ABORT_DONE
// Description : Raised when any bit in ABORT_DONE is set. Clear by clearing all
//               bits in ABORT_DONE.
#define USB_INTE_ABORT_DONE_RESET  _u(0x0)
#define USB_INTE_ABORT_DONE_BITS   _u(0x00040000)
#define USB_INTE_ABORT_DONE_MSB    _u(18)
#define USB_INTE_ABORT_DONE_LSB    _u(18)
#define USB_INTE_ABORT_DONE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_DEV_SOF
// Description : Set every time the device receives a SOF (Start of Frame)
//               packet. Cleared by reading SOF_RD
#define USB_INTE_DEV_SOF_RESET  _u(0x0)
#define USB_INTE_DEV_SOF_BITS   _u(0x00020000)
#define USB_INTE_DEV_SOF_MSB    _u(17)
#define USB_INTE_DEV_SOF_LSB    _u(17)
#define USB_INTE_DEV_SOF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_SETUP_REQ
// Description : Device. Source: SIE_STATUS.SETUP_REC
#define USB_INTE_SETUP_REQ_RESET  _u(0x0)
#define USB_INTE_SETUP_REQ_BITS   _u(0x00010000)
#define USB_INTE_SETUP_REQ_MSB    _u(16)
#define USB_INTE_SETUP_REQ_LSB    _u(16)
#define USB_INTE_SETUP_REQ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_DEV_RESUME_FROM_HOST
// Description : Set when the device receives a resume from the host. Cleared by
//               writing to SIE_STATUS.RESUME
#define USB_INTE_DEV_RESUME_FROM_HOST_RESET  _u(0x0)
#define USB_INTE_DEV_RESUME_FROM_HOST_BITS   _u(0x00008000)
#define USB_INTE_DEV_RESUME_FROM_HOST_MSB    _u(15)
#define USB_INTE_DEV_RESUME_FROM_HOST_LSB    _u(15)
#define USB_INTE_DEV_RESUME_FROM_HOST_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_DEV_SUSPEND
// Description : Set when the device suspend state changes. Cleared by writing
//               to SIE_STATUS.SUSPENDED
#define USB_INTE_DEV_SUSPEND_RESET  _u(0x0)
#define USB_INTE_DEV_SUSPEND_BITS   _u(0x00004000)
#define USB_INTE_DEV_SUSPEND_MSB    _u(14)
#define USB_INTE_DEV_SUSPEND_LSB    _u(14)
#define USB_INTE_DEV_SUSPEND_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_DEV_CONN_DIS
// Description : Set when the device connection state changes. Cleared by
//               writing to SIE_STATUS.CONNECTED
#define USB_INTE_DEV_CONN_DIS_RESET  _u(0x0)
#define USB_INTE_DEV_CONN_DIS_BITS   _u(0x00002000)
#define USB_INTE_DEV_CONN_DIS_MSB    _u(13)
#define USB_INTE_DEV_CONN_DIS_LSB    _u(13)
#define USB_INTE_DEV_CONN_DIS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_BUS_RESET
// Description : Source: SIE_STATUS.BUS_RESET
#define USB_INTE_BUS_RESET_RESET  _u(0x0)
#define USB_INTE_BUS_RESET_BITS   _u(0x00001000)
#define USB_INTE_BUS_RESET_MSB    _u(12)
#define USB_INTE_BUS_RESET_LSB    _u(12)
#define USB_INTE_BUS_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_VBUS_DETECT
// Description : Source: SIE_STATUS.VBUS_DETECTED
#define USB_INTE_VBUS_DETECT_RESET  _u(0x0)
#define USB_INTE_VBUS_DETECT_BITS   _u(0x00000800)
#define USB_INTE_VBUS_DETECT_MSB    _u(11)
#define USB_INTE_VBUS_DETECT_LSB    _u(11)
#define USB_INTE_VBUS_DETECT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_STALL
// Description : Source: SIE_STATUS.STALL_REC
#define USB_INTE_STALL_RESET  _u(0x0)
#define USB_INTE_STALL_BITS   _u(0x00000400)
#define USB_INTE_STALL_MSB    _u(10)
#define USB_INTE_STALL_LSB    _u(10)
#define USB_INTE_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_ERROR_CRC
// Description : Source: SIE_STATUS.CRC_ERROR
#define USB_INTE_ERROR_CRC_RESET  _u(0x0)
#define USB_INTE_ERROR_CRC_BITS   _u(0x00000200)
#define USB_INTE_ERROR_CRC_MSB    _u(9)
#define USB_INTE_ERROR_CRC_LSB    _u(9)
#define USB_INTE_ERROR_CRC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_ERROR_BIT_STUFF
// Description : Source: SIE_STATUS.BIT_STUFF_ERROR
#define USB_INTE_ERROR_BIT_STUFF_RESET  _u(0x0)
#define USB_INTE_ERROR_BIT_STUFF_BITS   _u(0x00000100)
#define USB_INTE_ERROR_BIT_STUFF_MSB    _u(8)
#define USB_INTE_ERROR_BIT_STUFF_LSB    _u(8)
#define USB_INTE_ERROR_BIT_STUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_ERROR_RX_OVERFLOW
// Description : Source: SIE_STATUS.RX_OVERFLOW
#define USB_INTE_ERROR_RX_OVERFLOW_RESET  _u(0x0)
#define USB_INTE_ERROR_RX_OVERFLOW_BITS   _u(0x00000080)
#define USB_INTE_ERROR_RX_OVERFLOW_MSB    _u(7)
#define USB_INTE_ERROR_RX_OVERFLOW_LSB    _u(7)
#define USB_INTE_ERROR_RX_OVERFLOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_ERROR_RX_TIMEOUT
// Description : Source: SIE_STATUS.RX_TIMEOUT
#define USB_INTE_ERROR_RX_TIMEOUT_RESET  _u(0x0)
#define USB_INTE_ERROR_RX_TIMEOUT_BITS   _u(0x00000040)
#define USB_INTE_ERROR_RX_TIMEOUT_MSB    _u(6)
#define USB_INTE_ERROR_RX_TIMEOUT_LSB    _u(6)
#define USB_INTE_ERROR_RX_TIMEOUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_ERROR_DATA_SEQ
// Description : Source: SIE_STATUS.DATA_SEQ_ERROR
#define USB_INTE_ERROR_DATA_SEQ_RESET  _u(0x0)
#define USB_INTE_ERROR_DATA_SEQ_BITS   _u(0x00000020)
#define USB_INTE_ERROR_DATA_SEQ_MSB    _u(5)
#define USB_INTE_ERROR_DATA_SEQ_LSB    _u(5)
#define USB_INTE_ERROR_DATA_SEQ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_BUFF_STATUS
// Description : Raised when any bit in BUFF_STATUS is set. Clear by clearing
//               all bits in BUFF_STATUS.
#define USB_INTE_BUFF_STATUS_RESET  _u(0x0)
#define USB_INTE_BUFF_STATUS_BITS   _u(0x00000010)
#define USB_INTE_BUFF_STATUS_MSB    _u(4)
#define USB_INTE_BUFF_STATUS_LSB    _u(4)
#define USB_INTE_BUFF_STATUS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_TRANS_COMPLETE
// Description : Raised every time SIE_STATUS.TRANS_COMPLETE is set. Clear by
//               writing to this bit.
#define USB_INTE_TRANS_COMPLETE_RESET  _u(0x0)
#define USB_INTE_TRANS_COMPLETE_BITS   _u(0x00000008)
#define USB_INTE_TRANS_COMPLETE_MSB    _u(3)
#define USB_INTE_TRANS_COMPLETE_LSB    _u(3)
#define USB_INTE_TRANS_COMPLETE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_HOST_SOF
// Description : Host: raised every time the host sends a SOF (Start of Frame).
//               Cleared by reading SOF_RD
#define USB_INTE_HOST_SOF_RESET  _u(0x0)
#define USB_INTE_HOST_SOF_BITS   _u(0x00000004)
#define USB_INTE_HOST_SOF_MSB    _u(2)
#define USB_INTE_HOST_SOF_LSB    _u(2)
#define USB_INTE_HOST_SOF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_HOST_RESUME
// Description : Host: raised when a device wakes up the host. Cleared by
//               writing to SIE_STATUS.RESUME
#define USB_INTE_HOST_RESUME_RESET  _u(0x0)
#define USB_INTE_HOST_RESUME_BITS   _u(0x00000002)
#define USB_INTE_HOST_RESUME_MSB    _u(1)
#define USB_INTE_HOST_RESUME_LSB    _u(1)
#define USB_INTE_HOST_RESUME_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTE_HOST_CONN_DIS
// Description : Host: raised when a device is connected or disconnected (i.e.
//               when SIE_STATUS.SPEED changes). Cleared by writing to
//               SIE_STATUS.SPEED
#define USB_INTE_HOST_CONN_DIS_RESET  _u(0x0)
#define USB_INTE_HOST_CONN_DIS_BITS   _u(0x00000001)
#define USB_INTE_HOST_CONN_DIS_MSB    _u(0)
#define USB_INTE_HOST_CONN_DIS_LSB    _u(0)
#define USB_INTE_HOST_CONN_DIS_ACCESS "RW"
// =============================================================================
// Register    : USB_INTF
// Description : Interrupt Force
#define USB_INTF_OFFSET _u(0x00000094)
#define USB_INTF_BITS   _u(0x000fffff)
#define USB_INTF_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_INTF_EP_STALL_NAK
// Description : Raised when any bit in EP_STATUS_STALL_NAK is set. Clear by
//               clearing all bits in EP_STATUS_STALL_NAK.
#define USB_INTF_EP_STALL_NAK_RESET  _u(0x0)
#define USB_INTF_EP_STALL_NAK_BITS   _u(0x00080000)
#define USB_INTF_EP_STALL_NAK_MSB    _u(19)
#define USB_INTF_EP_STALL_NAK_LSB    _u(19)
#define USB_INTF_EP_STALL_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_ABORT_DONE
// Description : Raised when any bit in ABORT_DONE is set. Clear by clearing all
//               bits in ABORT_DONE.
#define USB_INTF_ABORT_DONE_RESET  _u(0x0)
#define USB_INTF_ABORT_DONE_BITS   _u(0x00040000)
#define USB_INTF_ABORT_DONE_MSB    _u(18)
#define USB_INTF_ABORT_DONE_LSB    _u(18)
#define USB_INTF_ABORT_DONE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_DEV_SOF
// Description : Set every time the device receives a SOF (Start of Frame)
//               packet. Cleared by reading SOF_RD
#define USB_INTF_DEV_SOF_RESET  _u(0x0)
#define USB_INTF_DEV_SOF_BITS   _u(0x00020000)
#define USB_INTF_DEV_SOF_MSB    _u(17)
#define USB_INTF_DEV_SOF_LSB    _u(17)
#define USB_INTF_DEV_SOF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_SETUP_REQ
// Description : Device. Source: SIE_STATUS.SETUP_REC
#define USB_INTF_SETUP_REQ_RESET  _u(0x0)
#define USB_INTF_SETUP_REQ_BITS   _u(0x00010000)
#define USB_INTF_SETUP_REQ_MSB    _u(16)
#define USB_INTF_SETUP_REQ_LSB    _u(16)
#define USB_INTF_SETUP_REQ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_DEV_RESUME_FROM_HOST
// Description : Set when the device receives a resume from the host. Cleared by
//               writing to SIE_STATUS.RESUME
#define USB_INTF_DEV_RESUME_FROM_HOST_RESET  _u(0x0)
#define USB_INTF_DEV_RESUME_FROM_HOST_BITS   _u(0x00008000)
#define USB_INTF_DEV_RESUME_FROM_HOST_MSB    _u(15)
#define USB_INTF_DEV_RESUME_FROM_HOST_LSB    _u(15)
#define USB_INTF_DEV_RESUME_FROM_HOST_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_DEV_SUSPEND
// Description : Set when the device suspend state changes. Cleared by writing
//               to SIE_STATUS.SUSPENDED
#define USB_INTF_DEV_SUSPEND_RESET  _u(0x0)
#define USB_INTF_DEV_SUSPEND_BITS   _u(0x00004000)
#define USB_INTF_DEV_SUSPEND_MSB    _u(14)
#define USB_INTF_DEV_SUSPEND_LSB    _u(14)
#define USB_INTF_DEV_SUSPEND_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_DEV_CONN_DIS
// Description : Set when the device connection state changes. Cleared by
//               writing to SIE_STATUS.CONNECTED
#define USB_INTF_DEV_CONN_DIS_RESET  _u(0x0)
#define USB_INTF_DEV_CONN_DIS_BITS   _u(0x00002000)
#define USB_INTF_DEV_CONN_DIS_MSB    _u(13)
#define USB_INTF_DEV_CONN_DIS_LSB    _u(13)
#define USB_INTF_DEV_CONN_DIS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_BUS_RESET
// Description : Source: SIE_STATUS.BUS_RESET
#define USB_INTF_BUS_RESET_RESET  _u(0x0)
#define USB_INTF_BUS_RESET_BITS   _u(0x00001000)
#define USB_INTF_BUS_RESET_MSB    _u(12)
#define USB_INTF_BUS_RESET_LSB    _u(12)
#define USB_INTF_BUS_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_VBUS_DETECT
// Description : Source: SIE_STATUS.VBUS_DETECTED
#define USB_INTF_VBUS_DETECT_RESET  _u(0x0)
#define USB_INTF_VBUS_DETECT_BITS   _u(0x00000800)
#define USB_INTF_VBUS_DETECT_MSB    _u(11)
#define USB_INTF_VBUS_DETECT_LSB    _u(11)
#define USB_INTF_VBUS_DETECT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_STALL
// Description : Source: SIE_STATUS.STALL_REC
#define USB_INTF_STALL_RESET  _u(0x0)
#define USB_INTF_STALL_BITS   _u(0x00000400)
#define USB_INTF_STALL_MSB    _u(10)
#define USB_INTF_STALL_LSB    _u(10)
#define USB_INTF_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_ERROR_CRC
// Description : Source: SIE_STATUS.CRC_ERROR
#define USB_INTF_ERROR_CRC_RESET  _u(0x0)
#define USB_INTF_ERROR_CRC_BITS   _u(0x00000200)
#define USB_INTF_ERROR_CRC_MSB    _u(9)
#define USB_INTF_ERROR_CRC_LSB    _u(9)
#define USB_INTF_ERROR_CRC_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_ERROR_BIT_STUFF
// Description : Source: SIE_STATUS.BIT_STUFF_ERROR
#define USB_INTF_ERROR_BIT_STUFF_RESET  _u(0x0)
#define USB_INTF_ERROR_BIT_STUFF_BITS   _u(0x00000100)
#define USB_INTF_ERROR_BIT_STUFF_MSB    _u(8)
#define USB_INTF_ERROR_BIT_STUFF_LSB    _u(8)
#define USB_INTF_ERROR_BIT_STUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_ERROR_RX_OVERFLOW
// Description : Source: SIE_STATUS.RX_OVERFLOW
#define USB_INTF_ERROR_RX_OVERFLOW_RESET  _u(0x0)
#define USB_INTF_ERROR_RX_OVERFLOW_BITS   _u(0x00000080)
#define USB_INTF_ERROR_RX_OVERFLOW_MSB    _u(7)
#define USB_INTF_ERROR_RX_OVERFLOW_LSB    _u(7)
#define USB_INTF_ERROR_RX_OVERFLOW_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_ERROR_RX_TIMEOUT
// Description : Source: SIE_STATUS.RX_TIMEOUT
#define USB_INTF_ERROR_RX_TIMEOUT_RESET  _u(0x0)
#define USB_INTF_ERROR_RX_TIMEOUT_BITS   _u(0x00000040)
#define USB_INTF_ERROR_RX_TIMEOUT_MSB    _u(6)
#define USB_INTF_ERROR_RX_TIMEOUT_LSB    _u(6)
#define USB_INTF_ERROR_RX_TIMEOUT_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_ERROR_DATA_SEQ
// Description : Source: SIE_STATUS.DATA_SEQ_ERROR
#define USB_INTF_ERROR_DATA_SEQ_RESET  _u(0x0)
#define USB_INTF_ERROR_DATA_SEQ_BITS   _u(0x00000020)
#define USB_INTF_ERROR_DATA_SEQ_MSB    _u(5)
#define USB_INTF_ERROR_DATA_SEQ_LSB    _u(5)
#define USB_INTF_ERROR_DATA_SEQ_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_BUFF_STATUS
// Description : Raised when any bit in BUFF_STATUS is set. Clear by clearing
//               all bits in BUFF_STATUS.
#define USB_INTF_BUFF_STATUS_RESET  _u(0x0)
#define USB_INTF_BUFF_STATUS_BITS   _u(0x00000010)
#define USB_INTF_BUFF_STATUS_MSB    _u(4)
#define USB_INTF_BUFF_STATUS_LSB    _u(4)
#define USB_INTF_BUFF_STATUS_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_TRANS_COMPLETE
// Description : Raised every time SIE_STATUS.TRANS_COMPLETE is set. Clear by
//               writing to this bit.
#define USB_INTF_TRANS_COMPLETE_RESET  _u(0x0)
#define USB_INTF_TRANS_COMPLETE_BITS   _u(0x00000008)
#define USB_INTF_TRANS_COMPLETE_MSB    _u(3)
#define USB_INTF_TRANS_COMPLETE_LSB    _u(3)
#define USB_INTF_TRANS_COMPLETE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_HOST_SOF
// Description : Host: raised every time the host sends a SOF (Start of Frame).
//               Cleared by reading SOF_RD
#define USB_INTF_HOST_SOF_RESET  _u(0x0)
#define USB_INTF_HOST_SOF_BITS   _u(0x00000004)
#define USB_INTF_HOST_SOF_MSB    _u(2)
#define USB_INTF_HOST_SOF_LSB    _u(2)
#define USB_INTF_HOST_SOF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_HOST_RESUME
// Description : Host: raised when a device wakes up the host. Cleared by
//               writing to SIE_STATUS.RESUME
#define USB_INTF_HOST_RESUME_RESET  _u(0x0)
#define USB_INTF_HOST_RESUME_BITS   _u(0x00000002)
#define USB_INTF_HOST_RESUME_MSB    _u(1)
#define USB_INTF_HOST_RESUME_LSB    _u(1)
#define USB_INTF_HOST_RESUME_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_INTF_HOST_CONN_DIS
// Description : Host: raised when a device is connected or disconnected (i.e.
//               when SIE_STATUS.SPEED changes). Cleared by writing to
//               SIE_STATUS.SPEED
#define USB_INTF_HOST_CONN_DIS_RESET  _u(0x0)
#define USB_INTF_HOST_CONN_DIS_BITS   _u(0x00000001)
#define USB_INTF_HOST_CONN_DIS_MSB    _u(0)
#define USB_INTF_HOST_CONN_DIS_LSB    _u(0)
#define USB_INTF_HOST_CONN_DIS_ACCESS "RW"
// =============================================================================
// Register    : USB_INTS
// Description : Interrupt status after masking & forcing
#define USB_INTS_OFFSET _u(0x00000098)
#define USB_INTS_BITS   _u(0x000fffff)
#define USB_INTS_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_INTS_EP_STALL_NAK
// Description : Raised when any bit in EP_STATUS_STALL_NAK is set. Clear by
//               clearing all bits in EP_STATUS_STALL_NAK.
#define USB_INTS_EP_STALL_NAK_RESET  _u(0x0)
#define USB_INTS_EP_STALL_NAK_BITS   _u(0x00080000)
#define USB_INTS_EP_STALL_NAK_MSB    _u(19)
#define USB_INTS_EP_STALL_NAK_LSB    _u(19)
#define USB_INTS_EP_STALL_NAK_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_ABORT_DONE
// Description : Raised when any bit in ABORT_DONE is set. Clear by clearing all
//               bits in ABORT_DONE.
#define USB_INTS_ABORT_DONE_RESET  _u(0x0)
#define USB_INTS_ABORT_DONE_BITS   _u(0x00040000)
#define USB_INTS_ABORT_DONE_MSB    _u(18)
#define USB_INTS_ABORT_DONE_LSB    _u(18)
#define USB_INTS_ABORT_DONE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_DEV_SOF
// Description : Set every time the device receives a SOF (Start of Frame)
//               packet. Cleared by reading SOF_RD
#define USB_INTS_DEV_SOF_RESET  _u(0x0)
#define USB_INTS_DEV_SOF_BITS   _u(0x00020000)
#define USB_INTS_DEV_SOF_MSB    _u(17)
#define USB_INTS_DEV_SOF_LSB    _u(17)
#define USB_INTS_DEV_SOF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_SETUP_REQ
// Description : Device. Source: SIE_STATUS.SETUP_REC
#define USB_INTS_SETUP_REQ_RESET  _u(0x0)
#define USB_INTS_SETUP_REQ_BITS   _u(0x00010000)
#define USB_INTS_SETUP_REQ_MSB    _u(16)
#define USB_INTS_SETUP_REQ_LSB    _u(16)
#define USB_INTS_SETUP_REQ_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_DEV_RESUME_FROM_HOST
// Description : Set when the device receives a resume from the host. Cleared by
//               writing to SIE_STATUS.RESUME
#define USB_INTS_DEV_RESUME_FROM_HOST_RESET  _u(0x0)
#define USB_INTS_DEV_RESUME_FROM_HOST_BITS   _u(0x00008000)
#define USB_INTS_DEV_RESUME_FROM_HOST_MSB    _u(15)
#define USB_INTS_DEV_RESUME_FROM_HOST_LSB    _u(15)
#define USB_INTS_DEV_RESUME_FROM_HOST_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_DEV_SUSPEND
// Description : Set when the device suspend state changes. Cleared by writing
//               to SIE_STATUS.SUSPENDED
#define USB_INTS_DEV_SUSPEND_RESET  _u(0x0)
#define USB_INTS_DEV_SUSPEND_BITS   _u(0x00004000)
#define USB_INTS_DEV_SUSPEND_MSB    _u(14)
#define USB_INTS_DEV_SUSPEND_LSB    _u(14)
#define USB_INTS_DEV_SUSPEND_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_DEV_CONN_DIS
// Description : Set when the device connection state changes. Cleared by
//               writing to SIE_STATUS.CONNECTED
#define USB_INTS_DEV_CONN_DIS_RESET  _u(0x0)
#define USB_INTS_DEV_CONN_DIS_BITS   _u(0x00002000)
#define USB_INTS_DEV_CONN_DIS_MSB    _u(13)
#define USB_INTS_DEV_CONN_DIS_LSB    _u(13)
#define USB_INTS_DEV_CONN_DIS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_BUS_RESET
// Description : Source: SIE_STATUS.BUS_RESET
#define USB_INTS_BUS_RESET_RESET  _u(0x0)
#define USB_INTS_BUS_RESET_BITS   _u(0x00001000)
#define USB_INTS_BUS_RESET_MSB    _u(12)
#define USB_INTS_BUS_RESET_LSB    _u(12)
#define USB_INTS_BUS_RESET_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_VBUS_DETECT
// Description : Source: SIE_STATUS.VBUS_DETECTED
#define USB_INTS_VBUS_DETECT_RESET  _u(0x0)
#define USB_INTS_VBUS_DETECT_BITS   _u(0x00000800)
#define USB_INTS_VBUS_DETECT_MSB    _u(11)
#define USB_INTS_VBUS_DETECT_LSB    _u(11)
#define USB_INTS_VBUS_DETECT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_STALL
// Description : Source: SIE_STATUS.STALL_REC
#define USB_INTS_STALL_RESET  _u(0x0)
#define USB_INTS_STALL_BITS   _u(0x00000400)
#define USB_INTS_STALL_MSB    _u(10)
#define USB_INTS_STALL_LSB    _u(10)
#define USB_INTS_STALL_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_ERROR_CRC
// Description : Source: SIE_STATUS.CRC_ERROR
#define USB_INTS_ERROR_CRC_RESET  _u(0x0)
#define USB_INTS_ERROR_CRC_BITS   _u(0x00000200)
#define USB_INTS_ERROR_CRC_MSB    _u(9)
#define USB_INTS_ERROR_CRC_LSB    _u(9)
#define USB_INTS_ERROR_CRC_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_ERROR_BIT_STUFF
// Description : Source: SIE_STATUS.BIT_STUFF_ERROR
#define USB_INTS_ERROR_BIT_STUFF_RESET  _u(0x0)
#define USB_INTS_ERROR_BIT_STUFF_BITS   _u(0x00000100)
#define USB_INTS_ERROR_BIT_STUFF_MSB    _u(8)
#define USB_INTS_ERROR_BIT_STUFF_LSB    _u(8)
#define USB_INTS_ERROR_BIT_STUFF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_ERROR_RX_OVERFLOW
// Description : Source: SIE_STATUS.RX_OVERFLOW
#define USB_INTS_ERROR_RX_OVERFLOW_RESET  _u(0x0)
#define USB_INTS_ERROR_RX_OVERFLOW_BITS   _u(0x00000080)
#define USB_INTS_ERROR_RX_OVERFLOW_MSB    _u(7)
#define USB_INTS_ERROR_RX_OVERFLOW_LSB    _u(7)
#define USB_INTS_ERROR_RX_OVERFLOW_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_ERROR_RX_TIMEOUT
// Description : Source: SIE_STATUS.RX_TIMEOUT
#define USB_INTS_ERROR_RX_TIMEOUT_RESET  _u(0x0)
#define USB_INTS_ERROR_RX_TIMEOUT_BITS   _u(0x00000040)
#define USB_INTS_ERROR_RX_TIMEOUT_MSB    _u(6)
#define USB_INTS_ERROR_RX_TIMEOUT_LSB    _u(6)
#define USB_INTS_ERROR_RX_TIMEOUT_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_ERROR_DATA_SEQ
// Description : Source: SIE_STATUS.DATA_SEQ_ERROR
#define USB_INTS_ERROR_DATA_SEQ_RESET  _u(0x0)
#define USB_INTS_ERROR_DATA_SEQ_BITS   _u(0x00000020)
#define USB_INTS_ERROR_DATA_SEQ_MSB    _u(5)
#define USB_INTS_ERROR_DATA_SEQ_LSB    _u(5)
#define USB_INTS_ERROR_DATA_SEQ_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_BUFF_STATUS
// Description : Raised when any bit in BUFF_STATUS is set. Clear by clearing
//               all bits in BUFF_STATUS.
#define USB_INTS_BUFF_STATUS_RESET  _u(0x0)
#define USB_INTS_BUFF_STATUS_BITS   _u(0x00000010)
#define USB_INTS_BUFF_STATUS_MSB    _u(4)
#define USB_INTS_BUFF_STATUS_LSB    _u(4)
#define USB_INTS_BUFF_STATUS_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_TRANS_COMPLETE
// Description : Raised every time SIE_STATUS.TRANS_COMPLETE is set. Clear by
//               writing to this bit.
#define USB_INTS_TRANS_COMPLETE_RESET  _u(0x0)
#define USB_INTS_TRANS_COMPLETE_BITS   _u(0x00000008)
#define USB_INTS_TRANS_COMPLETE_MSB    _u(3)
#define USB_INTS_TRANS_COMPLETE_LSB    _u(3)
#define USB_INTS_TRANS_COMPLETE_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_HOST_SOF
// Description : Host: raised every time the host sends a SOF (Start of Frame).
//               Cleared by reading SOF_RD
#define USB_INTS_HOST_SOF_RESET  _u(0x0)
#define USB_INTS_HOST_SOF_BITS   _u(0x00000004)
#define USB_INTS_HOST_SOF_MSB    _u(2)
#define USB_INTS_HOST_SOF_LSB    _u(2)
#define USB_INTS_HOST_SOF_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_HOST_RESUME
// Description : Host: raised when a device wakes up the host. Cleared by
//               writing to SIE_STATUS.RESUME
#define USB_INTS_HOST_RESUME_RESET  _u(0x0)
#define USB_INTS_HOST_RESUME_BITS   _u(0x00000002)
#define USB_INTS_HOST_RESUME_MSB    _u(1)
#define USB_INTS_HOST_RESUME_LSB    _u(1)
#define USB_INTS_HOST_RESUME_ACCESS "RO"
// -----------------------------------------------------------------------------
// Field       : USB_INTS_HOST_CONN_DIS
// Description : Host: raised when a device is connected or disconnected (i.e.
//               when SIE_STATUS.SPEED changes). Cleared by writing to
//               SIE_STATUS.SPEED
#define USB_INTS_HOST_CONN_DIS_RESET  _u(0x0)
#define USB_INTS_HOST_CONN_DIS_BITS   _u(0x00000001)
#define USB_INTS_HOST_CONN_DIS_MSB    _u(0)
#define USB_INTS_HOST_CONN_DIS_LSB    _u(0)
#define USB_INTS_HOST_CONN_DIS_ACCESS "RO"
// =============================================================================
#endif // HARDWARE_REGS_USB_DEFINED
