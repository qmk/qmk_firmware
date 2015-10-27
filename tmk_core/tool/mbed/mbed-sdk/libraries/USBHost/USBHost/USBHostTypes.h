/* mbed USBHost Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef USB_INC_H
#define USB_INC_H

#include "mbed.h"
#include "toolchain.h"

enum USB_TYPE {
    USB_TYPE_OK = 0,

    // completion code
    USB_TYPE_CRC_ERROR = 1,
    USB_TYPE_BIT_STUFFING_ERROR = 2,
    USB_TYPE_DATA_TOGGLE_MISMATCH_ERROR = 3,
    USB_TYPE_STALL_ERROR = 4,
    USB_TYPE_DEVICE_NOT_RESPONDING_ERROR = 5,
    USB_TYPE_PID_CHECK_FAILURE_ERROR = 6,
    USB_TYPE_UNEXPECTED_PID_ERROR = 7,
    USB_TYPE_DATA_OVERRUN_ERROR = 8,
    USB_TYPE_DATA_UNDERRUN_ERROR = 9,
    USB_TYPE_RESERVED = 9,
    USB_TYPE_RESERVED_ = 10,
    USB_TYPE_BUFFER_OVERRUN_ERROR = 12,
    USB_TYPE_BUFFER_UNDERRUN_ERROR = 13,

    // general usb state
    USB_TYPE_DISCONNECTED = 14,
    USB_TYPE_FREE = 15,
    USB_TYPE_IDLE = 16,
    USB_TYPE_PROCESSING = 17,

    USB_TYPE_ERROR = 18,
};


enum ENDPOINT_DIRECTION {
    OUT = 1,
    IN
};

enum ENDPOINT_TYPE {
    CONTROL_ENDPOINT = 0,
    ISOCHRONOUS_ENDPOINT,
    BULK_ENDPOINT,
    INTERRUPT_ENDPOINT
};

#define AUDIO_CLASS     0x01
#define CDC_CLASS       0x02
#define HID_CLASS       0x03
#define MSD_CLASS       0x08
#define HUB_CLASS       0x09
#define SERIAL_CLASS    0x0A

// ------------------ HcControl Register ---------------------
#define  OR_CONTROL_PLE                 0x00000004
#define  OR_CONTROL_CLE                 0x00000010
#define  OR_CONTROL_BLE                 0x00000020
#define  OR_CONTROL_HCFS                0x000000C0
#define  OR_CONTROL_HC_OPER             0x00000080
// ----------------- HcCommandStatus Register -----------------
#define  OR_CMD_STATUS_HCR              0x00000001
#define  OR_CMD_STATUS_CLF              0x00000002
#define  OR_CMD_STATUS_BLF              0x00000004
// --------------- HcInterruptStatus Register -----------------
#define  OR_INTR_STATUS_WDH             0x00000002
#define  OR_INTR_STATUS_RHSC            0x00000040
#define  OR_INTR_STATUS_UE              0x00000010
// --------------- HcInterruptEnable Register -----------------
#define  OR_INTR_ENABLE_WDH             0x00000002
#define  OR_INTR_ENABLE_RHSC            0x00000040
#define  OR_INTR_ENABLE_MIE             0x80000000
// ---------------- HcRhDescriptorA Register ------------------
#define  OR_RH_STATUS_LPSC              0x00010000
#define  OR_RH_STATUS_DRWE              0x00008000
// -------------- HcRhPortStatus[1:NDP] Register --------------
#define  OR_RH_PORT_CCS                 0x00000001
#define  OR_RH_PORT_PRS                 0x00000010
#define  OR_RH_PORT_CSC                 0x00010000
#define  OR_RH_PORT_PRSC                0x00100000
#define  OR_RH_PORT_LSDA                0x00000200

#define  FI                     0x2EDF           // 12000 bits per frame (-1)
#define  DEFAULT_FMINTERVAL     ((((6 * (FI - 210)) / 7) << 16) | FI)

#define  ED_SKIP            (uint32_t) (0x00001000)        // Skip this ep in queue

#define  TD_ROUNDING        (uint32_t) (0x00040000)        // Buffer Rounding
#define  TD_SETUP           (uint32_t)(0)                  // Direction of Setup Packet
#define  TD_IN              (uint32_t)(0x00100000)         // Direction In
#define  TD_OUT             (uint32_t)(0x00080000)         // Direction Out
#define  TD_DELAY_INT(x)    (uint32_t)((x) << 21)          // Delay Interrupt
#define  TD_TOGGLE_0        (uint32_t)(0x02000000)         // Toggle 0
#define  TD_TOGGLE_1        (uint32_t)(0x03000000)         // Toggle 1
#define  TD_CC              (uint32_t)(0xF0000000)         // Completion Code

#define  DEVICE_DESCRIPTOR                     (1)
#define  CONFIGURATION_DESCRIPTOR              (2)
#define  INTERFACE_DESCRIPTOR                  (4)
#define  ENDPOINT_DESCRIPTOR                   (5)
#define  HID_DESCRIPTOR                        (33)

//  ----------- Control RequestType Fields  -----------
#define  USB_DEVICE_TO_HOST         0x80
#define  USB_HOST_TO_DEVICE         0x00
#define  USB_REQUEST_TYPE_CLASS     0x20
#define  USB_REQUEST_TYPE_STANDARD  0x00
#define  USB_RECIPIENT_DEVICE       0x00
#define  USB_RECIPIENT_INTERFACE    0x01
#define  USB_RECIPIENT_ENDPOINT     0x02

// -------------- USB Standard Requests  --------------
#define  SET_ADDRESS                0x05
#define  GET_DESCRIPTOR             0x06
#define  SET_CONFIGURATION          0x09
#define  SET_INTERFACE              0x0b
#define  CLEAR_FEATURE              0x01

// -------------- USB Descriptor Length  --------------
#define DEVICE_DESCRIPTOR_LENGTH            0x12
#define CONFIGURATION_DESCRIPTOR_LENGTH     0x09

// ------------ HostController Transfer Descriptor ------------
typedef struct HCTD {
    __IO  uint32_t   control;        // Transfer descriptor control
    __IO  uint8_t *  currBufPtr;    // Physical address of current buffer pointer
    __IO  HCTD *     nextTD;         // Physical pointer to next Transfer Descriptor
    __IO  uint8_t *  bufEnd;        // Physical address of end of buffer
    void * ep;                      // ep address where a td is linked in
    uint32_t dummy[3];              // padding
} PACKED HCTD;

// ----------- HostController EndPoint Descriptor -------------
typedef struct hcEd {
    __IO  uint32_t  control;        // Endpoint descriptor control
    __IO  HCTD *  tailTD;           // Physical address of tail in Transfer descriptor list
    __IO  HCTD *  headTD;           // Physcial address of head in Transfer descriptor list
    __IO  hcEd *  nextED;         // Physical address of next Endpoint descriptor
} PACKED HCED;


// ----------- Host Controller Communication Area ------------
typedef struct hcca {
    __IO  uint32_t  IntTable[32];   // Interrupt Table
    __IO  uint32_t  FrameNumber;    // Frame Number
    __IO  uint32_t  DoneHead;       // Done Head
    volatile  uint8_t   Reserved[116];  // Reserved for future use
    volatile  uint8_t   Unknown[4];     // Unused
} PACKED HCCA;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t bcdUSB;
    uint8_t bDeviceClass;
    uint8_t bDeviceSubClass;
    uint8_t bDeviceProtocol;
    uint8_t bMaxPacketSize;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t iManufacturer;
    uint8_t iProduct;
    uint8_t iSerialNumber;
    uint8_t bNumConfigurations;
} PACKED DeviceDescriptor;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint16_t wTotalLength;
    uint8_t bNumInterfaces;
    uint8_t bConfigurationValue;
    uint8_t iConfiguration;
    uint8_t bmAttributes;
    uint8_t bMaxPower;
} PACKED ConfigurationDescriptor;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} InterfaceDescriptor;

typedef struct {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bEndpointAddress;
    uint8_t bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t bInterval;
} EndpointDescriptor;

typedef struct {
    uint8_t bDescLength;
    uint8_t bDescriptorType;
    uint8_t bNbrPorts;
    uint16_t wHubCharacteristics;
    uint8_t bPwrOn2PwrGood;
    uint8_t bHubContrCurrent;
    uint8_t DeviceRemovable;
    uint8_t PortPweCtrlMak;
} HubDescriptor;

#endif
