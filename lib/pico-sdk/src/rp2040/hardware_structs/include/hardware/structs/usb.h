// THIS HEADER FILE IS AUTOMATICALLY GENERATED -- DO NOT EDIT

/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_STRUCTS_USB_H
#define _HARDWARE_STRUCTS_USB_H

#include "hardware/address_mapped.h"
#include "hardware/regs/usb.h"

// Reference to datasheet: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf#tab-registerlist_usb
//
// The _REG_ macro is intended to help make the register navigable in your IDE (for example, using the "Go to Definition" feature)
// _REG_(x) will link to the corresponding register in hardware/regs/usb.h.
//
// Bit-field descriptions are of the form:
// BITMASK [BITRANGE]: FIELDNAME (RESETVALUE): DESCRIPTION

// 0-15
#define USB_NUM_ENDPOINTS 16

// allow user to restrict number of endpoints available to save RAN
#ifndef USB_MAX_ENDPOINTS
#define USB_MAX_ENDPOINTS USB_NUM_ENDPOINTS
#endif

// 1-15
#define USB_HOST_INTERRUPT_ENDPOINTS (USB_NUM_ENDPOINTS - 1)

// Endpoint buffer control bits
#define USB_BUF_CTRL_FULL      0x00008000u
#define USB_BUF_CTRL_LAST      0x00004000u
#define USB_BUF_CTRL_DATA0_PID 0x00000000u
#define USB_BUF_CTRL_DATA1_PID 0x00002000u
#define USB_BUF_CTRL_SEL       0x00001000u
#define USB_BUF_CTRL_STALL     0x00000800u
#define USB_BUF_CTRL_AVAIL     0x00000400u
#define USB_BUF_CTRL_LEN_MASK  0x000003FFu
#define USB_BUF_CTRL_LEN_LSB   0

// ep_inout_ctrl bits
#define EP_CTRL_ENABLE_BITS (1u << 31u)
#define EP_CTRL_DOUBLE_BUFFERED_BITS (1u << 30)
#define EP_CTRL_INTERRUPT_PER_BUFFER (1u << 29)
#define EP_CTRL_INTERRUPT_PER_DOUBLE_BUFFER (1u << 28)
#define EP_CTRL_INTERRUPT_ON_NAK (1u << 16)
#define EP_CTRL_INTERRUPT_ON_STALL (1u << 17)
#define EP_CTRL_BUFFER_TYPE_LSB 26u
#define EP_CTRL_HOST_INTERRUPT_INTERVAL_LSB 16u

#define USB_DPRAM_SIZE 4096u

// PICO_CONFIG: USB_DPRAM_MAX, Set amount of USB RAM used by USB system, min=0, max=4096, default=4096, group=hardware_usb
// Allow user to claim some of the USB RAM for themselves
#ifndef USB_DPRAM_MAX
#define USB_DPRAM_MAX USB_DPRAM_SIZE
#endif

// Define maximum packet sizes
#define USB_MAX_ISO_PACKET_SIZE 1023
#define USB_MAX_PACKET_SIZE 64

typedef struct {
    // 4K of DPSRAM at beginning. Note this supports 8, 16, and 32 bit accesses
    volatile uint8_t setup_packet[8]; // First 8 bytes are always for setup packets

    // Starts at ep1
    struct usb_device_dpram_ep_ctrl {
        io_rw_32 in;
        io_rw_32 out;
    } ep_ctrl[USB_NUM_ENDPOINTS - 1];

    // Starts at ep0
    struct usb_device_dpram_ep_buf_ctrl {
        io_rw_32 in;
        io_rw_32 out;
    } ep_buf_ctrl[USB_NUM_ENDPOINTS];

    // EP0 buffers are fixed. Assumes single buffered mode for EP0
    uint8_t ep0_buf_a[0x40];
    uint8_t ep0_buf_b[0x40];

    // Rest of DPRAM can be carved up as needed
    uint8_t epx_data[USB_DPRAM_MAX - 0x180];
} usb_device_dpram_t;

static_assert(sizeof(usb_device_dpram_t) == USB_DPRAM_MAX, "");
static_assert(offsetof(usb_device_dpram_t, epx_data) == 0x180, "");

typedef struct {
    // 4K of DPSRAM at beginning. Note this supports 8, 16, and 32 bit accesses
    volatile uint8_t setup_packet[8]; // First 8 bytes are always for setup packets

    // Interrupt endpoint control 1 -> 15
    struct usb_host_dpram_ep_ctrl {
        io_rw_32 ctrl;
        io_rw_32 spare;
    } int_ep_ctrl[USB_HOST_INTERRUPT_ENDPOINTS];

    io_rw_32 epx_buf_ctrl;
    io_rw_32 _spare0;

    // Interrupt endpoint buffer control
    struct usb_host_dpram_ep_buf_ctrl {
        io_rw_32 ctrl;
        io_rw_32 spare;
    } int_ep_buffer_ctrl[USB_HOST_INTERRUPT_ENDPOINTS];

    io_rw_32 epx_ctrl;

    uint8_t _spare1[124];

    // Should start at 0x180
    uint8_t epx_data[USB_DPRAM_MAX - 0x180];
} usb_host_dpram_t;

static_assert(sizeof(usb_host_dpram_t) == USB_DPRAM_MAX, "");
static_assert(offsetof(usb_host_dpram_t, epx_data) == 0x180, "");

typedef struct {
    _REG_(USB_ADDR_ENDP_OFFSET) // USB_ADDR_ENDP
    // Device address and endpoint control
    // 0x000f0000 [19:16] : ENDPOINT (0): Device endpoint to send data to
    // 0x0000007f [6:0]   : ADDRESS (0): In device mode, the address that the device should respond to
    io_rw_32 dev_addr_ctrl;

    _REG_(USB_ADDR_ENDP1_OFFSET) // USB_ADDR_ENDP1
    // (Description copied from array index 0 register USB_ADDR_ENDP1 applies similarly to other array indexes)
    //
    // Interrupt endpoint 1
    // 0x04000000 [26]    : INTEP_PREAMBLE (0): Interrupt EP requires preamble (is a low speed device on a full speed hub)
    // 0x02000000 [25]    : INTEP_DIR (0): Direction of the interrupt endpoint
    // 0x000f0000 [19:16] : ENDPOINT (0): Endpoint number of the interrupt endpoint
    // 0x0000007f [6:0]   : ADDRESS (0): Device address
    io_rw_32 int_ep_addr_ctrl[USB_HOST_INTERRUPT_ENDPOINTS]; // 15

    _REG_(USB_MAIN_CTRL_OFFSET) // USB_MAIN_CTRL
    // Main control register
    // 0x80000000 [31]    : SIM_TIMING (0): Reduced timings for simulation
    // 0x00000002 [1]     : HOST_NDEVICE (0): Device mode = 0, Host mode = 1
    // 0x00000001 [0]     : CONTROLLER_EN (0): Enable controller
    io_rw_32 main_ctrl;

    _REG_(USB_SOF_WR_OFFSET) // USB_SOF_WR
    // Set the SOF (Start of Frame) frame number in the host controller
    // 0x000007ff [10:0]  : COUNT (0)
    io_wo_32 sof_rw;

    _REG_(USB_SOF_RD_OFFSET) // USB_SOF_RD
    // Read the last SOF (Start of Frame) frame number seen
    // 0x000007ff [10:0]  : COUNT (0)
    io_ro_32 sof_rd;

    _REG_(USB_SIE_CTRL_OFFSET) // USB_SIE_CTRL
    // SIE control register
    // 0x80000000 [31]    : EP0_INT_STALL (0): Device: Set bit in EP_STATUS_STALL_NAK when EP0 sends a STALL
    // 0x40000000 [30]    : EP0_DOUBLE_BUF (0): Device: EP0 single buffered = 0, double buffered = 1
    // 0x20000000 [29]    : EP0_INT_1BUF (0): Device: Set bit in BUFF_STATUS for every buffer completed on EP0
    // 0x10000000 [28]    : EP0_INT_2BUF (0): Device: Set bit in BUFF_STATUS for every 2 buffers completed on EP0
    // 0x08000000 [27]    : EP0_INT_NAK (0): Device: Set bit in EP_STATUS_STALL_NAK when EP0 sends a NAK
    // 0x04000000 [26]    : DIRECT_EN (0): Direct bus drive enable
    // 0x02000000 [25]    : DIRECT_DP (0): Direct control of DP
    // 0x01000000 [24]    : DIRECT_DM (0): Direct control of DM
    // 0x00040000 [18]    : TRANSCEIVER_PD (0): Power down bus transceiver
    // 0x00020000 [17]    : RPU_OPT (0): Device: Pull-up strength (0=1K2, 1=2k3)
    // 0x00010000 [16]    : PULLUP_EN (0): Device: Enable pull up resistor
    // 0x00008000 [15]    : PULLDOWN_EN (0): Host: Enable pull down resistors
    // 0x00002000 [13]    : RESET_BUS (0): Host: Reset bus
    // 0x00001000 [12]    : RESUME (0): Device: Remote wakeup
    // 0x00000800 [11]    : VBUS_EN (0): Host: Enable VBUS
    // 0x00000400 [10]    : KEEP_ALIVE_EN (0): Host: Enable keep alive packet (for low speed bus)
    // 0x00000200 [9]     : SOF_EN (0): Host: Enable SOF generation (for full speed bus)
    // 0x00000100 [8]     : SOF_SYNC (0): Host: Delay packet(s) until after SOF
    // 0x00000040 [6]     : PREAMBLE_EN (0): Host: Preable enable for LS device on FS hub
    // 0x00000010 [4]     : STOP_TRANS (0): Host: Stop transaction
    // 0x00000008 [3]     : RECEIVE_DATA (0): Host: Receive transaction (IN to host)
    // 0x00000004 [2]     : SEND_DATA (0): Host: Send transaction (OUT from host)
    // 0x00000002 [1]     : SEND_SETUP (0): Host: Send Setup packet
    // 0x00000001 [0]     : START_TRANS (0): Host: Start transaction
    io_rw_32 sie_ctrl;

    _REG_(USB_SIE_STATUS_OFFSET) // USB_SIE_STATUS
    // SIE status register
    // 0x80000000 [31]    : DATA_SEQ_ERROR (0): Data Sequence Error
    // 0x40000000 [30]    : ACK_REC (0): ACK received
    // 0x20000000 [29]    : STALL_REC (0): Host: STALL received
    // 0x10000000 [28]    : NAK_REC (0): Host: NAK received
    // 0x08000000 [27]    : RX_TIMEOUT (0): RX timeout is raised by both the host and device if an ACK is not received in...
    // 0x04000000 [26]    : RX_OVERFLOW (0): RX overflow is raised by the Serial RX engine if the incoming data is too fast
    // 0x02000000 [25]    : BIT_STUFF_ERROR (0): Bit Stuff Error
    // 0x01000000 [24]    : CRC_ERROR (0): CRC Error
    // 0x00080000 [19]    : BUS_RESET (0): Device: bus reset received
    // 0x00040000 [18]    : TRANS_COMPLETE (0): Transaction complete
    // 0x00020000 [17]    : SETUP_REC (0): Device: Setup packet received
    // 0x00010000 [16]    : CONNECTED (0): Device: connected
    // 0x00000800 [11]    : RESUME (0): Host: Device has initiated a remote resume
    // 0x00000400 [10]    : VBUS_OVER_CURR (0): VBUS over current detected
    // 0x00000300 [9:8]   : SPEED (0): Host: device speed
    // 0x00000010 [4]     : SUSPENDED (0): Bus in suspended state
    // 0x0000000c [3:2]   : LINE_STATE (0): USB bus line state
    // 0x00000001 [0]     : VBUS_DETECTED (0): Device: VBUS Detected
    io_rw_32 sie_status;

    _REG_(USB_INT_EP_CTRL_OFFSET) // USB_INT_EP_CTRL
    // interrupt endpoint control register
    // 0x0000fffe [15:1]  : INT_EP_ACTIVE (0): Host: Enable interrupt endpoint 1 -> 15
    io_rw_32 int_ep_ctrl;

    _REG_(USB_BUFF_STATUS_OFFSET) // USB_BUFF_STATUS
    // Buffer status register
    // 0x80000000 [31]    : EP15_OUT (0)
    // 0x40000000 [30]    : EP15_IN (0)
    // 0x20000000 [29]    : EP14_OUT (0)
    // 0x10000000 [28]    : EP14_IN (0)
    // 0x08000000 [27]    : EP13_OUT (0)
    // 0x04000000 [26]    : EP13_IN (0)
    // 0x02000000 [25]    : EP12_OUT (0)
    // 0x01000000 [24]    : EP12_IN (0)
    // 0x00800000 [23]    : EP11_OUT (0)
    // 0x00400000 [22]    : EP11_IN (0)
    // 0x00200000 [21]    : EP10_OUT (0)
    // 0x00100000 [20]    : EP10_IN (0)
    // 0x00080000 [19]    : EP9_OUT (0)
    // 0x00040000 [18]    : EP9_IN (0)
    // 0x00020000 [17]    : EP8_OUT (0)
    // 0x00010000 [16]    : EP8_IN (0)
    // 0x00008000 [15]    : EP7_OUT (0)
    // 0x00004000 [14]    : EP7_IN (0)
    // 0x00002000 [13]    : EP6_OUT (0)
    // 0x00001000 [12]    : EP6_IN (0)
    // 0x00000800 [11]    : EP5_OUT (0)
    // 0x00000400 [10]    : EP5_IN (0)
    // 0x00000200 [9]     : EP4_OUT (0)
    // 0x00000100 [8]     : EP4_IN (0)
    // 0x00000080 [7]     : EP3_OUT (0)
    // 0x00000040 [6]     : EP3_IN (0)
    // 0x00000020 [5]     : EP2_OUT (0)
    // 0x00000010 [4]     : EP2_IN (0)
    // 0x00000008 [3]     : EP1_OUT (0)
    // 0x00000004 [2]     : EP1_IN (0)
    // 0x00000002 [1]     : EP0_OUT (0)
    // 0x00000001 [0]     : EP0_IN (0)
    io_rw_32 buf_status;

    _REG_(USB_BUFF_CPU_SHOULD_HANDLE_OFFSET) // USB_BUFF_CPU_SHOULD_HANDLE
    // Which of the double buffers should be handled
    // 0x80000000 [31]    : EP15_OUT (0)
    // 0x40000000 [30]    : EP15_IN (0)
    // 0x20000000 [29]    : EP14_OUT (0)
    // 0x10000000 [28]    : EP14_IN (0)
    // 0x08000000 [27]    : EP13_OUT (0)
    // 0x04000000 [26]    : EP13_IN (0)
    // 0x02000000 [25]    : EP12_OUT (0)
    // 0x01000000 [24]    : EP12_IN (0)
    // 0x00800000 [23]    : EP11_OUT (0)
    // 0x00400000 [22]    : EP11_IN (0)
    // 0x00200000 [21]    : EP10_OUT (0)
    // 0x00100000 [20]    : EP10_IN (0)
    // 0x00080000 [19]    : EP9_OUT (0)
    // 0x00040000 [18]    : EP9_IN (0)
    // 0x00020000 [17]    : EP8_OUT (0)
    // 0x00010000 [16]    : EP8_IN (0)
    // 0x00008000 [15]    : EP7_OUT (0)
    // 0x00004000 [14]    : EP7_IN (0)
    // 0x00002000 [13]    : EP6_OUT (0)
    // 0x00001000 [12]    : EP6_IN (0)
    // 0x00000800 [11]    : EP5_OUT (0)
    // 0x00000400 [10]    : EP5_IN (0)
    // 0x00000200 [9]     : EP4_OUT (0)
    // 0x00000100 [8]     : EP4_IN (0)
    // 0x00000080 [7]     : EP3_OUT (0)
    // 0x00000040 [6]     : EP3_IN (0)
    // 0x00000020 [5]     : EP2_OUT (0)
    // 0x00000010 [4]     : EP2_IN (0)
    // 0x00000008 [3]     : EP1_OUT (0)
    // 0x00000004 [2]     : EP1_IN (0)
    // 0x00000002 [1]     : EP0_OUT (0)
    // 0x00000001 [0]     : EP0_IN (0)
    io_ro_32 buf_cpu_should_handle;

    _REG_(USB_EP_ABORT_OFFSET) // USB_EP_ABORT
    // Device only: Can be set to ignore the buffer control register for this endpoint in case you would like to revoke a buffer
    // 0x80000000 [31]    : EP15_OUT (0)
    // 0x40000000 [30]    : EP15_IN (0)
    // 0x20000000 [29]    : EP14_OUT (0)
    // 0x10000000 [28]    : EP14_IN (0)
    // 0x08000000 [27]    : EP13_OUT (0)
    // 0x04000000 [26]    : EP13_IN (0)
    // 0x02000000 [25]    : EP12_OUT (0)
    // 0x01000000 [24]    : EP12_IN (0)
    // 0x00800000 [23]    : EP11_OUT (0)
    // 0x00400000 [22]    : EP11_IN (0)
    // 0x00200000 [21]    : EP10_OUT (0)
    // 0x00100000 [20]    : EP10_IN (0)
    // 0x00080000 [19]    : EP9_OUT (0)
    // 0x00040000 [18]    : EP9_IN (0)
    // 0x00020000 [17]    : EP8_OUT (0)
    // 0x00010000 [16]    : EP8_IN (0)
    // 0x00008000 [15]    : EP7_OUT (0)
    // 0x00004000 [14]    : EP7_IN (0)
    // 0x00002000 [13]    : EP6_OUT (0)
    // 0x00001000 [12]    : EP6_IN (0)
    // 0x00000800 [11]    : EP5_OUT (0)
    // 0x00000400 [10]    : EP5_IN (0)
    // 0x00000200 [9]     : EP4_OUT (0)
    // 0x00000100 [8]     : EP4_IN (0)
    // 0x00000080 [7]     : EP3_OUT (0)
    // 0x00000040 [6]     : EP3_IN (0)
    // 0x00000020 [5]     : EP2_OUT (0)
    // 0x00000010 [4]     : EP2_IN (0)
    // 0x00000008 [3]     : EP1_OUT (0)
    // 0x00000004 [2]     : EP1_IN (0)
    // 0x00000002 [1]     : EP0_OUT (0)
    // 0x00000001 [0]     : EP0_IN (0)
    io_rw_32 abort;

    _REG_(USB_EP_ABORT_DONE_OFFSET) // USB_EP_ABORT_DONE
    // Device only: Used in conjunction with `EP_ABORT`
    // 0x80000000 [31]    : EP15_OUT (0)
    // 0x40000000 [30]    : EP15_IN (0)
    // 0x20000000 [29]    : EP14_OUT (0)
    // 0x10000000 [28]    : EP14_IN (0)
    // 0x08000000 [27]    : EP13_OUT (0)
    // 0x04000000 [26]    : EP13_IN (0)
    // 0x02000000 [25]    : EP12_OUT (0)
    // 0x01000000 [24]    : EP12_IN (0)
    // 0x00800000 [23]    : EP11_OUT (0)
    // 0x00400000 [22]    : EP11_IN (0)
    // 0x00200000 [21]    : EP10_OUT (0)
    // 0x00100000 [20]    : EP10_IN (0)
    // 0x00080000 [19]    : EP9_OUT (0)
    // 0x00040000 [18]    : EP9_IN (0)
    // 0x00020000 [17]    : EP8_OUT (0)
    // 0x00010000 [16]    : EP8_IN (0)
    // 0x00008000 [15]    : EP7_OUT (0)
    // 0x00004000 [14]    : EP7_IN (0)
    // 0x00002000 [13]    : EP6_OUT (0)
    // 0x00001000 [12]    : EP6_IN (0)
    // 0x00000800 [11]    : EP5_OUT (0)
    // 0x00000400 [10]    : EP5_IN (0)
    // 0x00000200 [9]     : EP4_OUT (0)
    // 0x00000100 [8]     : EP4_IN (0)
    // 0x00000080 [7]     : EP3_OUT (0)
    // 0x00000040 [6]     : EP3_IN (0)
    // 0x00000020 [5]     : EP2_OUT (0)
    // 0x00000010 [4]     : EP2_IN (0)
    // 0x00000008 [3]     : EP1_OUT (0)
    // 0x00000004 [2]     : EP1_IN (0)
    // 0x00000002 [1]     : EP0_OUT (0)
    // 0x00000001 [0]     : EP0_IN (0)
    io_rw_32 abort_done;

    _REG_(USB_EP_STALL_ARM_OFFSET) // USB_EP_STALL_ARM
    // Device: this bit must be set in conjunction with the `STALL` bit in the buffer control register to send a STALL on EP0
    // 0x00000002 [1]     : EP0_OUT (0)
    // 0x00000001 [0]     : EP0_IN (0)
    io_rw_32 ep_stall_arm;

    _REG_(USB_NAK_POLL_OFFSET) // USB_NAK_POLL
    // Used by the host controller
    // 0x03ff0000 [25:16] : DELAY_FS (0x10): NAK polling interval for a full speed device
    // 0x000003ff [9:0]   : DELAY_LS (0x10): NAK polling interval for a low speed device
    io_rw_32 nak_poll;

    _REG_(USB_EP_STATUS_STALL_NAK_OFFSET) // USB_EP_STATUS_STALL_NAK
    // Device: bits are set when the `IRQ_ON_NAK` or `IRQ_ON_STALL` bits are set
    // 0x80000000 [31]    : EP15_OUT (0)
    // 0x40000000 [30]    : EP15_IN (0)
    // 0x20000000 [29]    : EP14_OUT (0)
    // 0x10000000 [28]    : EP14_IN (0)
    // 0x08000000 [27]    : EP13_OUT (0)
    // 0x04000000 [26]    : EP13_IN (0)
    // 0x02000000 [25]    : EP12_OUT (0)
    // 0x01000000 [24]    : EP12_IN (0)
    // 0x00800000 [23]    : EP11_OUT (0)
    // 0x00400000 [22]    : EP11_IN (0)
    // 0x00200000 [21]    : EP10_OUT (0)
    // 0x00100000 [20]    : EP10_IN (0)
    // 0x00080000 [19]    : EP9_OUT (0)
    // 0x00040000 [18]    : EP9_IN (0)
    // 0x00020000 [17]    : EP8_OUT (0)
    // 0x00010000 [16]    : EP8_IN (0)
    // 0x00008000 [15]    : EP7_OUT (0)
    // 0x00004000 [14]    : EP7_IN (0)
    // 0x00002000 [13]    : EP6_OUT (0)
    // 0x00001000 [12]    : EP6_IN (0)
    // 0x00000800 [11]    : EP5_OUT (0)
    // 0x00000400 [10]    : EP5_IN (0)
    // 0x00000200 [9]     : EP4_OUT (0)
    // 0x00000100 [8]     : EP4_IN (0)
    // 0x00000080 [7]     : EP3_OUT (0)
    // 0x00000040 [6]     : EP3_IN (0)
    // 0x00000020 [5]     : EP2_OUT (0)
    // 0x00000010 [4]     : EP2_IN (0)
    // 0x00000008 [3]     : EP1_OUT (0)
    // 0x00000004 [2]     : EP1_IN (0)
    // 0x00000002 [1]     : EP0_OUT (0)
    // 0x00000001 [0]     : EP0_IN (0)
    io_rw_32 ep_nak_stall_status;

    _REG_(USB_USB_MUXING_OFFSET) // USB_USB_MUXING
    // Where to connect the USB controller
    // 0x00000008 [3]     : SOFTCON (0)
    // 0x00000004 [2]     : TO_DIGITAL_PAD (0)
    // 0x00000002 [1]     : TO_EXTPHY (0)
    // 0x00000001 [0]     : TO_PHY (0)
    io_rw_32 muxing;

    _REG_(USB_USB_PWR_OFFSET) // USB_USB_PWR
    // Overrides for the power signals in the event that the VBUS signals are not hooked up to GPIO
    // 0x00000020 [5]     : OVERCURR_DETECT_EN (0)
    // 0x00000010 [4]     : OVERCURR_DETECT (0)
    // 0x00000008 [3]     : VBUS_DETECT_OVERRIDE_EN (0)
    // 0x00000004 [2]     : VBUS_DETECT (0)
    // 0x00000002 [1]     : VBUS_EN_OVERRIDE_EN (0)
    // 0x00000001 [0]     : VBUS_EN (0)
    io_rw_32 pwr;

    _REG_(USB_USBPHY_DIRECT_OFFSET) // USB_USBPHY_DIRECT
    // This register allows for direct control of the USB phy
    // 0x00400000 [22]    : DM_OVV (0): DM over voltage
    // 0x00200000 [21]    : DP_OVV (0): DP over voltage
    // 0x00100000 [20]    : DM_OVCN (0): DM overcurrent
    // 0x00080000 [19]    : DP_OVCN (0): DP overcurrent
    // 0x00040000 [18]    : RX_DM (0): DPM pin state
    // 0x00020000 [17]    : RX_DP (0): DPP pin state
    // 0x00010000 [16]    : RX_DD (0): Differential RX
    // 0x00008000 [15]    : TX_DIFFMODE (0): TX_DIFFMODE=0: Single ended mode
    // 0x00004000 [14]    : TX_FSSLEW (0): TX_FSSLEW=0: Low speed slew rate
    // 0x00002000 [13]    : TX_PD (0): TX power down override (if override enable is set)
    // 0x00001000 [12]    : RX_PD (0): RX power down override (if override enable is set)
    // 0x00000800 [11]    : TX_DM (0): Output data
    // 0x00000400 [10]    : TX_DP (0): Output data
    // 0x00000200 [9]     : TX_DM_OE (0): Output enable
    // 0x00000100 [8]     : TX_DP_OE (0): Output enable
    // 0x00000040 [6]     : DM_PULLDN_EN (0): DM pull down enable
    // 0x00000020 [5]     : DM_PULLUP_EN (0): DM pull up enable
    // 0x00000010 [4]     : DM_PULLUP_HISEL (0): Enable the second DM pull up resistor
    // 0x00000004 [2]     : DP_PULLDN_EN (0): DP pull down enable
    // 0x00000002 [1]     : DP_PULLUP_EN (0): DP pull up enable
    // 0x00000001 [0]     : DP_PULLUP_HISEL (0): Enable the second DP pull up resistor
    io_rw_32 phy_direct;

    _REG_(USB_USBPHY_DIRECT_OVERRIDE_OFFSET) // USB_USBPHY_DIRECT_OVERRIDE
    // Override enable for each control in usbphy_direct
    // 0x00008000 [15]    : TX_DIFFMODE_OVERRIDE_EN (0)
    // 0x00001000 [12]    : DM_PULLUP_OVERRIDE_EN (0)
    // 0x00000800 [11]    : TX_FSSLEW_OVERRIDE_EN (0)
    // 0x00000400 [10]    : TX_PD_OVERRIDE_EN (0)
    // 0x00000200 [9]     : RX_PD_OVERRIDE_EN (0)
    // 0x00000100 [8]     : TX_DM_OVERRIDE_EN (0)
    // 0x00000080 [7]     : TX_DP_OVERRIDE_EN (0)
    // 0x00000040 [6]     : TX_DM_OE_OVERRIDE_EN (0)
    // 0x00000020 [5]     : TX_DP_OE_OVERRIDE_EN (0)
    // 0x00000010 [4]     : DM_PULLDN_EN_OVERRIDE_EN (0)
    // 0x00000008 [3]     : DP_PULLDN_EN_OVERRIDE_EN (0)
    // 0x00000004 [2]     : DP_PULLUP_EN_OVERRIDE_EN (0)
    // 0x00000002 [1]     : DM_PULLUP_HISEL_OVERRIDE_EN (0)
    // 0x00000001 [0]     : DP_PULLUP_HISEL_OVERRIDE_EN (0)
    io_rw_32 phy_direct_override;

    _REG_(USB_USBPHY_TRIM_OFFSET) // USB_USBPHY_TRIM
    // Used to adjust trim values of USB phy pull down resistors
    // 0x00001f00 [12:8]  : DM_PULLDN_TRIM (0x1f): Value to drive to USB PHY
    // 0x0000001f [4:0]   : DP_PULLDN_TRIM (0x1f): Value to drive to USB PHY
    io_rw_32 phy_trim;

    uint32_t _pad0;

    _REG_(USB_INTR_OFFSET) // USB_INTR
    // Raw Interrupts
    // 0x00080000 [19]    : EP_STALL_NAK (0): Raised when any bit in EP_STATUS_STALL_NAK is set
    // 0x00040000 [18]    : ABORT_DONE (0): Raised when any bit in ABORT_DONE is set
    // 0x00020000 [17]    : DEV_SOF (0): Set every time the device receives a SOF (Start of Frame) packet
    // 0x00010000 [16]    : SETUP_REQ (0): Device
    // 0x00008000 [15]    : DEV_RESUME_FROM_HOST (0): Set when the device receives a resume from the host
    // 0x00004000 [14]    : DEV_SUSPEND (0): Set when the device suspend state changes
    // 0x00002000 [13]    : DEV_CONN_DIS (0): Set when the device connection state changes
    // 0x00001000 [12]    : BUS_RESET (0): Source: SIE_STATUS
    // 0x00000800 [11]    : VBUS_DETECT (0): Source: SIE_STATUS
    // 0x00000400 [10]    : STALL (0): Source: SIE_STATUS
    // 0x00000200 [9]     : ERROR_CRC (0): Source: SIE_STATUS
    // 0x00000100 [8]     : ERROR_BIT_STUFF (0): Source: SIE_STATUS
    // 0x00000080 [7]     : ERROR_RX_OVERFLOW (0): Source: SIE_STATUS
    // 0x00000040 [6]     : ERROR_RX_TIMEOUT (0): Source: SIE_STATUS
    // 0x00000020 [5]     : ERROR_DATA_SEQ (0): Source: SIE_STATUS
    // 0x00000010 [4]     : BUFF_STATUS (0): Raised when any bit in BUFF_STATUS is set
    // 0x00000008 [3]     : TRANS_COMPLETE (0): Raised every time SIE_STATUS
    // 0x00000004 [2]     : HOST_SOF (0): Host: raised every time the host sends a SOF (Start of Frame)
    // 0x00000002 [1]     : HOST_RESUME (0): Host: raised when a device wakes up the host
    // 0x00000001 [0]     : HOST_CONN_DIS (0): Host: raised when a device is connected or disconnected (i
    io_ro_32 intr;

    _REG_(USB_INTE_OFFSET) // USB_INTE
    // Interrupt Enable
    // 0x00080000 [19]    : EP_STALL_NAK (0): Raised when any bit in EP_STATUS_STALL_NAK is set
    // 0x00040000 [18]    : ABORT_DONE (0): Raised when any bit in ABORT_DONE is set
    // 0x00020000 [17]    : DEV_SOF (0): Set every time the device receives a SOF (Start of Frame) packet
    // 0x00010000 [16]    : SETUP_REQ (0): Device
    // 0x00008000 [15]    : DEV_RESUME_FROM_HOST (0): Set when the device receives a resume from the host
    // 0x00004000 [14]    : DEV_SUSPEND (0): Set when the device suspend state changes
    // 0x00002000 [13]    : DEV_CONN_DIS (0): Set when the device connection state changes
    // 0x00001000 [12]    : BUS_RESET (0): Source: SIE_STATUS
    // 0x00000800 [11]    : VBUS_DETECT (0): Source: SIE_STATUS
    // 0x00000400 [10]    : STALL (0): Source: SIE_STATUS
    // 0x00000200 [9]     : ERROR_CRC (0): Source: SIE_STATUS
    // 0x00000100 [8]     : ERROR_BIT_STUFF (0): Source: SIE_STATUS
    // 0x00000080 [7]     : ERROR_RX_OVERFLOW (0): Source: SIE_STATUS
    // 0x00000040 [6]     : ERROR_RX_TIMEOUT (0): Source: SIE_STATUS
    // 0x00000020 [5]     : ERROR_DATA_SEQ (0): Source: SIE_STATUS
    // 0x00000010 [4]     : BUFF_STATUS (0): Raised when any bit in BUFF_STATUS is set
    // 0x00000008 [3]     : TRANS_COMPLETE (0): Raised every time SIE_STATUS
    // 0x00000004 [2]     : HOST_SOF (0): Host: raised every time the host sends a SOF (Start of Frame)
    // 0x00000002 [1]     : HOST_RESUME (0): Host: raised when a device wakes up the host
    // 0x00000001 [0]     : HOST_CONN_DIS (0): Host: raised when a device is connected or disconnected (i
    io_rw_32 inte;

    _REG_(USB_INTF_OFFSET) // USB_INTF
    // Interrupt Force
    // 0x00080000 [19]    : EP_STALL_NAK (0): Raised when any bit in EP_STATUS_STALL_NAK is set
    // 0x00040000 [18]    : ABORT_DONE (0): Raised when any bit in ABORT_DONE is set
    // 0x00020000 [17]    : DEV_SOF (0): Set every time the device receives a SOF (Start of Frame) packet
    // 0x00010000 [16]    : SETUP_REQ (0): Device
    // 0x00008000 [15]    : DEV_RESUME_FROM_HOST (0): Set when the device receives a resume from the host
    // 0x00004000 [14]    : DEV_SUSPEND (0): Set when the device suspend state changes
    // 0x00002000 [13]    : DEV_CONN_DIS (0): Set when the device connection state changes
    // 0x00001000 [12]    : BUS_RESET (0): Source: SIE_STATUS
    // 0x00000800 [11]    : VBUS_DETECT (0): Source: SIE_STATUS
    // 0x00000400 [10]    : STALL (0): Source: SIE_STATUS
    // 0x00000200 [9]     : ERROR_CRC (0): Source: SIE_STATUS
    // 0x00000100 [8]     : ERROR_BIT_STUFF (0): Source: SIE_STATUS
    // 0x00000080 [7]     : ERROR_RX_OVERFLOW (0): Source: SIE_STATUS
    // 0x00000040 [6]     : ERROR_RX_TIMEOUT (0): Source: SIE_STATUS
    // 0x00000020 [5]     : ERROR_DATA_SEQ (0): Source: SIE_STATUS
    // 0x00000010 [4]     : BUFF_STATUS (0): Raised when any bit in BUFF_STATUS is set
    // 0x00000008 [3]     : TRANS_COMPLETE (0): Raised every time SIE_STATUS
    // 0x00000004 [2]     : HOST_SOF (0): Host: raised every time the host sends a SOF (Start of Frame)
    // 0x00000002 [1]     : HOST_RESUME (0): Host: raised when a device wakes up the host
    // 0x00000001 [0]     : HOST_CONN_DIS (0): Host: raised when a device is connected or disconnected (i
    io_rw_32 intf;

    _REG_(USB_INTS_OFFSET) // USB_INTS
    // Interrupt status after masking & forcing
    // 0x00080000 [19]    : EP_STALL_NAK (0): Raised when any bit in EP_STATUS_STALL_NAK is set
    // 0x00040000 [18]    : ABORT_DONE (0): Raised when any bit in ABORT_DONE is set
    // 0x00020000 [17]    : DEV_SOF (0): Set every time the device receives a SOF (Start of Frame) packet
    // 0x00010000 [16]    : SETUP_REQ (0): Device
    // 0x00008000 [15]    : DEV_RESUME_FROM_HOST (0): Set when the device receives a resume from the host
    // 0x00004000 [14]    : DEV_SUSPEND (0): Set when the device suspend state changes
    // 0x00002000 [13]    : DEV_CONN_DIS (0): Set when the device connection state changes
    // 0x00001000 [12]    : BUS_RESET (0): Source: SIE_STATUS
    // 0x00000800 [11]    : VBUS_DETECT (0): Source: SIE_STATUS
    // 0x00000400 [10]    : STALL (0): Source: SIE_STATUS
    // 0x00000200 [9]     : ERROR_CRC (0): Source: SIE_STATUS
    // 0x00000100 [8]     : ERROR_BIT_STUFF (0): Source: SIE_STATUS
    // 0x00000080 [7]     : ERROR_RX_OVERFLOW (0): Source: SIE_STATUS
    // 0x00000040 [6]     : ERROR_RX_TIMEOUT (0): Source: SIE_STATUS
    // 0x00000020 [5]     : ERROR_DATA_SEQ (0): Source: SIE_STATUS
    // 0x00000010 [4]     : BUFF_STATUS (0): Raised when any bit in BUFF_STATUS is set
    // 0x00000008 [3]     : TRANS_COMPLETE (0): Raised every time SIE_STATUS
    // 0x00000004 [2]     : HOST_SOF (0): Host: raised every time the host sends a SOF (Start of Frame)
    // 0x00000002 [1]     : HOST_RESUME (0): Host: raised when a device wakes up the host
    // 0x00000001 [0]     : HOST_CONN_DIS (0): Host: raised when a device is connected or disconnected (i
    io_ro_32 ints;
} usb_hw_t;

#define usb_hw ((usb_hw_t *)USBCTRL_REGS_BASE)

#define usb_dpram ((usb_device_dpram_t *)USBCTRL_DPRAM_BASE)
#define usbh_dpram ((usb_host_dpram_t *)USBCTRL_DPRAM_BASE)

static_assert( USB_HOST_INTERRUPT_ENDPOINTS == 15, "");

#endif
