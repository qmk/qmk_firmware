/**
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
// =============================================================================
// Register block : USB_DEVICE_DPRAM
// Version        : 1
// Bus type       : ahbl
// Description    : DPRAM layout for USB device.
// =============================================================================
#ifndef HARDWARE_REGS_USB_DEVICE_DPRAM_DEFINED
#define HARDWARE_REGS_USB_DEVICE_DPRAM_DEFINED
// =============================================================================
// Register    : USB_DEVICE_DPRAM_SETUP_PACKET_LOW
// Description : Bytes 0-3 of the SETUP packet from the host.
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_OFFSET _u(0x00000000)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_SETUP_PACKET_LOW_WVALUE
// Description : None
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_WVALUE_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_WVALUE_BITS   _u(0xffff0000)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_WVALUE_MSB    _u(31)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_WVALUE_LSB    _u(16)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_WVALUE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BREQUEST
// Description : None
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BREQUEST_RESET  _u(0x00)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BREQUEST_BITS   _u(0x0000ff00)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BREQUEST_MSB    _u(15)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BREQUEST_LSB    _u(8)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BREQUEST_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BMREQUESTTYPE
// Description : None
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BMREQUESTTYPE_RESET  _u(0x00)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BMREQUESTTYPE_BITS   _u(0x000000ff)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BMREQUESTTYPE_MSB    _u(7)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BMREQUESTTYPE_LSB    _u(0)
#define USB_DEVICE_DPRAM_SETUP_PACKET_LOW_BMREQUESTTYPE_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_SETUP_PACKET_HIGH
// Description : Bytes 4-7 of the setup packet from the host.
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_OFFSET _u(0x00000004)
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WLENGTH
// Description : None
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WLENGTH_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WLENGTH_BITS   _u(0xffff0000)
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WLENGTH_MSB    _u(31)
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WLENGTH_LSB    _u(16)
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WLENGTH_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WINDEX
// Description : None
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WINDEX_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WINDEX_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WINDEX_MSB    _u(15)
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WINDEX_LSB    _u(0)
#define USB_DEVICE_DPRAM_SETUP_PACKET_HIGH_WINDEX_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP1_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_OFFSET _u(0x00000008)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP1_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP1_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_OFFSET _u(0x0000000c)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP1_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP2_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_OFFSET _u(0x00000010)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP2_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP2_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_OFFSET _u(0x00000014)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP2_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP3_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_OFFSET _u(0x00000018)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP3_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP3_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_OFFSET _u(0x0000001c)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP3_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP4_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_OFFSET _u(0x00000020)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP4_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP4_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_OFFSET _u(0x00000024)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP4_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP5_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_OFFSET _u(0x00000028)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP5_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP5_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_OFFSET _u(0x0000002c)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP5_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP6_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_OFFSET _u(0x00000030)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP6_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP6_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_OFFSET _u(0x00000034)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP6_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP7_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_OFFSET _u(0x00000038)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP7_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP7_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_OFFSET _u(0x0000003c)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP7_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP8_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_OFFSET _u(0x00000040)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP8_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP8_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_OFFSET _u(0x00000044)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP8_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP9_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_OFFSET _u(0x00000048)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP9_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP9_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_OFFSET _u(0x0000004c)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP9_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP10_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_OFFSET _u(0x00000050)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP10_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP10_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_OFFSET _u(0x00000054)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP10_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP11_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_OFFSET _u(0x00000058)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP11_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP11_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_OFFSET _u(0x0000005c)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP11_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP12_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_OFFSET _u(0x00000060)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP12_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP12_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_OFFSET _u(0x00000064)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP12_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP13_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_OFFSET _u(0x00000068)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP13_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP13_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_OFFSET _u(0x0000006c)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP13_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP14_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_OFFSET _u(0x00000070)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP14_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP14_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_OFFSET _u(0x00000074)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP14_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP15_IN_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_OFFSET _u(0x00000078)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP15_IN_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP15_OUT_CONTROL
// Description : None
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_OFFSET _u(0x0000007c)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_BITS   _u(0xfc03ffff)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENABLE
// Description : Enable this endpoint. The device will not reply to any packets
//               for this endpoint if this bit is not set.
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENABLE_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENABLE_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENABLE_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENABLE_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENABLE_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_CONTROL_DOUBLE_BUFFERED
// Description : This endpoint is double buffered.
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_DOUBLE_BUFFERED_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_DOUBLE_BUFFERED_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_DOUBLE_BUFFERED_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_DOUBLE_BUFFERED_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_DOUBLE_BUFFERED_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_BUFF
// Description : Trigger an interrupt each time a buffer is done.
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_BUFF_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_BUFF_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_BUFF_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF
// Description : Trigger an interrupt each time both buffers are done. Only
//               valid in double buffered mode.
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_BITS   _u(0x10000000)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_MSB    _u(28)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_LSB    _u(28)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_PER_DOUBLE_BUFF_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE
// Description : 0x0 -> Control
//               0x1 -> Isochronous
//               0x2 -> Bulk
//               0x3 -> Interrupt
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_RESET             _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_BITS              _u(0x0c000000)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_MSB               _u(27)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_LSB               _u(26)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_ACCESS            "RW"
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_VALUE_CONTROL     _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_VALUE_ISOCHRONOUS _u(0x1)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_VALUE_BULK        _u(0x2)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_ENDPOINT_TYPE_VALUE_INTERRUPT   _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_STALL
// Description : Trigger an interrupt if a STALL is sent. Intended for debug
//               only.
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_STALL_BITS   _u(0x00020000)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_STALL_MSB    _u(17)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_STALL_LSB    _u(17)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_NAK
// Description : Trigger an interrupt if a NAK is sent. Intended for debug only.
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_NAK_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_NAK_BITS   _u(0x00010000)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_NAK_MSB    _u(16)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_NAK_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_INTERRUPT_ON_NAK_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_CONTROL_BUFFER_ADDRESS
// Description : 64 byte aligned buffer address for this EP (bits 0-5 are
//               ignored). Relative to the start of the DPRAM.
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_BUFFER_ADDRESS_RESET  _u(0x0000)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_BUFFER_ADDRESS_BITS   _u(0x0000ffff)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_BUFFER_ADDRESS_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_BUFFER_ADDRESS_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP15_OUT_CONTROL_BUFFER_ADDRESS_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_OFFSET _u(0x00000080)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP0_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_OFFSET _u(0x00000084)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP0_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_OFFSET _u(0x00000088)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP1_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_OFFSET _u(0x0000008c)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP1_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_OFFSET _u(0x00000090)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP2_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_OFFSET _u(0x00000094)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP2_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_OFFSET _u(0x00000098)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP3_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_OFFSET _u(0x0000009c)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP3_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_OFFSET _u(0x000000a0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP4_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_OFFSET _u(0x000000a4)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP4_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_OFFSET _u(0x000000a8)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP5_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_OFFSET _u(0x000000ac)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP5_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_OFFSET _u(0x000000b0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP6_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_OFFSET _u(0x000000b4)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP6_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_OFFSET _u(0x000000b8)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP7_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_OFFSET _u(0x000000bc)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP7_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_OFFSET _u(0x000000c0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP8_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_OFFSET _u(0x000000c4)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP8_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_OFFSET _u(0x000000c8)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP9_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_OFFSET _u(0x000000cc)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP9_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_OFFSET _u(0x000000d0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP10_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_OFFSET _u(0x000000d4)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFS
//               ET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP10_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_OFFSET _u(0x000000d8)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP11_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_OFFSET _u(0x000000dc)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFS
//               ET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP11_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_OFFSET _u(0x000000e0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP12_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_OFFSET _u(0x000000e4)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFS
//               ET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP12_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_OFFSET _u(0x000000e8)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP13_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_OFFSET _u(0x000000ec)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFS
//               ET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP13_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_OFFSET _u(0x000000f0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP14_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_OFFSET _u(0x000000f4)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFS
//               ET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP14_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_OFFSET _u(0x000000f8)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSE
//               T
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP15_IN_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
// Register    : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL
// Description : Buffer control for both buffers of an endpoint. Fields ending
//               in a _1 are for buffer 1.
//               Fields ending in a _0 are for buffer 0. Buffer 1 controls are
//               only valid if the endpoint is in double buffered mode.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_OFFSET _u(0x000000fc)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_BITS   _u(0xffffffff)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_RESET  _u(0x00000000)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_1
// Description : Buffer 1 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_1_BITS   _u(0x80000000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_1_MSB    _u(31)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_1_LSB    _u(31)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_1
// Description : Buffer 1 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_1_BITS   _u(0x40000000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_1_MSB    _u(30)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_1_LSB    _u(30)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_1
// Description : The data pid of buffer 1.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_1_BITS   _u(0x20000000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_1_MSB    _u(29)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_1_LSB    _u(29)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFS
//               ET
// Description : The number of bytes buffer 1 is offset from buffer 0 in
//               Isochronous mode. Only valid in double buffered mode for an
//               Isochronous endpoint.
//               For a non Isochronous endpoint the offset is always 64 bytes.
//               0x0 -> 128
//               0x1 -> 256
//               0x2 -> 512
//               0x3 -> 1024
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_RESET      _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_BITS       _u(0x18000000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_MSB        _u(28)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_LSB        _u(27)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_ACCESS     "RW"
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_128  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_256  _u(0x1)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_512  _u(0x2)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_DOUBLE_BUFFER_ISO_OFFSET_VALUE_1024 _u(0x3)
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_1
// Description : Buffer 1 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_1_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_1_BITS   _u(0x04000000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_1_MSB    _u(26)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_1_LSB    _u(26)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_1
// Description : The length of the data in buffer 1.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_1_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_1_BITS   _u(0x03ff0000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_1_MSB    _u(25)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_1_LSB    _u(16)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_1_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_0
// Description : Buffer 0 is full. For an IN transfer (TX to the host) the bit
//               is set to indicate the data is valid. For an OUT transfer (RX
//               from the host) this bit should be left as a 0. The host will
//               set it when it has filled the buffer with data.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_0_BITS   _u(0x00008000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_0_MSB    _u(15)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_0_LSB    _u(15)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_FULL_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_0
// Description : Buffer 0 is the last buffer of the transfer.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_0_BITS   _u(0x00004000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_0_MSB    _u(14)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_0_LSB    _u(14)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LAST_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_0
// Description : The data pid of buffer 0.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_0_BITS   _u(0x00002000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_0_MSB    _u(13)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_0_LSB    _u(13)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_PID_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_RESET
// Description : Reset the buffer selector to buffer 0.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_RESET_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_RESET_BITS   _u(0x00001000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_RESET_MSB    _u(12)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_RESET_LSB    _u(12)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_RESET_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_STALL
// Description : Reply with a stall (valid for both buffers).
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_STALL_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_STALL_BITS   _u(0x00000800)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_STALL_MSB    _u(11)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_STALL_LSB    _u(11)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_STALL_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_0
// Description : Buffer 0 is available. This bit is set to indicate the buffer
//               can be used by the controller. The controller clears the
//               available bit when writing the status back.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_0_RESET  _u(0x0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_0_BITS   _u(0x00000400)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_0_MSB    _u(10)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_0_LSB    _u(10)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_AVAILABLE_0_ACCESS "RW"
// -----------------------------------------------------------------------------
// Field       : USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_0
// Description : The length of the data in buffer 0.
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_0_RESET  _u(0x000)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_0_BITS   _u(0x000003ff)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_0_MSB    _u(9)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_0_LSB    _u(0)
#define USB_DEVICE_DPRAM_EP15_OUT_BUFFER_CONTROL_LENGTH_0_ACCESS "RW"
// =============================================================================
#endif // HARDWARE_REGS_USB_DEVICE_DPRAM_DEFINED
