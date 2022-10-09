/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _UDI_DEVICE_CONF_H_
#define _UDI_DEVICE_CONF_H_

#include "udi_device_epsize.h"
#include "usb_protocol.h"
#include "compiler.h"
#include "usb_protocol_hid.h"

#ifndef USB_POLLING_INTERVAL_MS
#    define USB_POLLING_INTERVAL_MS 10
#endif

#ifdef VIRTSER_ENABLE
// because CDC uses IAD (interface association descriptor
// per USB Interface Association Descriptor Device Class Code and Use Model 7/23/2003 Rev 1.0)
#    define DEVICE_CLASS 0xEF
#    define DEVICE_SUBCLASS 0x02
#    define DEVICE_PROTOCOL 0x01
#else
#    define DEVICE_CLASS 0x00
#    define DEVICE_SUBCLASS 0x00
#    define DEVICE_PROTOCOL 0x00
#endif

/* number of interfaces */
#define NEXT_INTERFACE_0 0

#define KEYBOARD_INTERFACE NEXT_INTERFACE_0
#define NEXT_INTERFACE_1 (KEYBOARD_INTERFACE + 1)
#define UDI_HID_KBD_IFACE_NUMBER KEYBOARD_INTERFACE

// It is important that the Raw HID interface is at a constant
// interface number, to support Linux/OSX platforms and chrome.hid
// If Raw HID is enabled, let it be always 1.
#ifdef RAW_ENABLE
#    define RAW_INTERFACE NEXT_INTERFACE_1
#    define NEXT_INTERFACE_2 (RAW_INTERFACE + 1)
#else
#    define NEXT_INTERFACE_2 NEXT_INTERFACE_1
#endif

#ifdef MOUSE_ENABLE
#    define MOUSE_INTERFACE NEXT_INTERFACE_2
#    define UDI_HID_MOU_IFACE_NUMBER MOUSE_INTERFACE
#    define NEXT_INTERFACE_3 (MOUSE_INTERFACE + 1)
#else
#    define NEXT_INTERFACE_3 NEXT_INTERFACE_2
#endif

#ifdef EXTRAKEY_ENABLE
#    define EXTRAKEY_INTERFACE NEXT_INTERFACE_3
#    define NEXT_INTERFACE_4 (EXTRAKEY_INTERFACE + 1)
#    define UDI_HID_EXK_IFACE_NUMBER EXTRAKEY_INTERFACE
#else
#    define NEXT_INTERFACE_4 NEXT_INTERFACE_3
#endif

#ifdef CONSOLE_ENABLE
#    define CON_INTERFACE NEXT_INTERFACE_4
#    define NEXT_INTERFACE_5 (CON_INTERFACE + 1)
#    define UDI_HID_CON_IFACE_NUMBER CON_INTERFACE
#else
#    define NEXT_INTERFACE_5 NEXT_INTERFACE_4
#endif

#ifdef NKRO_ENABLE
#    define NKRO_INTERFACE NEXT_INTERFACE_5
#    define NEXT_INTERFACE_6 (NKRO_INTERFACE + 1)
#    define UDI_HID_NKRO_IFACE_NUMBER NKRO_INTERFACE
#else
#    define NEXT_INTERFACE_6 NEXT_INTERFACE_5
#endif

#ifdef MIDI_ENABLE
#    define AC_INTERFACE NEXT_INTERFACE_6
#    define AS_INTERFACE (AC_INTERFACE + 1)
#    define NEXT_INTERFACE_7 (AS_INTERFACE + 1)
#else
#    define NEXT_INTERFACE_7 NEXT_INTERFACE_6
#endif

#ifdef VIRTSER_ENABLE
#    define CCI_INTERFACE NEXT_INTERFACE_7
#    define CDI_INTERFACE (CCI_INTERFACE + 1)
#    define NEXT_INTERFACE_8 (CDI_INTERFACE + 1)
#    define CDC_STATUS_INTERFACE CCI_INTERFACE
#    define CDC_DATA_INTERFACE CDI_INTERFACE
#else
#    define NEXT_INTERFACE_8 NEXT_INTERFACE_7
#endif

/* nubmer of interfaces */
#define TOTAL_INTERFACES NEXT_INTERFACE_8
#define USB_DEVICE_NB_INTERFACE TOTAL_INTERFACES

// **********************************************************************
// Endopoint number and size
// **********************************************************************
#define USB_DEVICE_EP_CTRL_SIZE 8

#define NEXT_IN_EPNUM_0 1
#define NEXT_OUT_EPNUM_0 1

#define KEYBOARD_IN_EPNUM NEXT_IN_EPNUM_0
#define UDI_HID_KBD_EP_IN KEYBOARD_IN_EPNUM
#define NEXT_IN_EPNUM_1 (KEYBOARD_IN_EPNUM + 1)
#define UDI_HID_KBD_EP_SIZE KEYBOARD_EPSIZE
#define KBD_POLLING_INTERVAL USB_POLLING_INTERVAL_MS
#ifndef UDI_HID_KBD_STRING_ID
#    define UDI_HID_KBD_STRING_ID 0
#endif

#ifdef MOUSE_ENABLE
#    define MOUSE_IN_EPNUM NEXT_IN_EPNUM_1
#    define NEXT_IN_EPNUM_2 (MOUSE_IN_EPNUM + 1)
#    define UDI_HID_MOU_EP_IN MOUSE_IN_EPNUM
#    define UDI_HID_MOU_EP_SIZE MOUSE_EPSIZE
#    define MOU_POLLING_INTERVAL USB_POLLING_INTERVAL_MS
#    ifndef UDI_HID_MOU_STRING_ID
#        define UDI_HID_MOU_STRING_ID 0
#    endif
#else
#    define NEXT_IN_EPNUM_2 NEXT_IN_EPNUM_1
#endif

#ifdef EXTRAKEY_ENABLE
#    define EXTRAKEY_IN_EPNUM NEXT_IN_EPNUM_2
#    define UDI_HID_EXK_EP_IN EXTRAKEY_IN_EPNUM
#    define NEXT_IN_EPNUM_3 (EXTRAKEY_IN_EPNUM + 1)
#    define UDI_HID_EXK_EP_SIZE EXTRAKEY_EPSIZE
#    define EXTRAKEY_POLLING_INTERVAL USB_POLLING_INTERVAL_MS
#    ifndef UDI_HID_EXK_STRING_ID
#        define UDI_HID_EXK_STRING_ID 0
#    endif
#else
#    define NEXT_IN_EPNUM_3 NEXT_IN_EPNUM_2
#endif

#ifdef RAW_ENABLE
#    define RAW_IN_EPNUM NEXT_IN_EPNUM_3
#    define UDI_HID_RAW_EP_IN RAW_IN_EPNUM
#    define NEXT_IN_EPNUM_4 (RAW_IN_EPNUM + 1)
#    define RAW_OUT_EPNUM NEXT_OUT_EPNUM_0
#    define UDI_HID_RAW_EP_OUT RAW_OUT_EPNUM
#    define NEXT_OUT_EPNUM_1 (RAW_OUT_EPNUM + 1)
#    define RAW_POLLING_INTERVAL 1
#    ifndef UDI_HID_RAW_STRING_ID
#        define UDI_HID_RAW_STRING_ID 0
#    endif
#else
#    define NEXT_IN_EPNUM_4 NEXT_IN_EPNUM_3
#    define NEXT_OUT_EPNUM_1 NEXT_OUT_EPNUM_0
#endif

#ifdef CONSOLE_ENABLE
#    define CON_IN_EPNUM NEXT_IN_EPNUM_4
#    define UDI_HID_CON_EP_IN CON_IN_EPNUM
#    define NEXT_IN_EPNUM_5 (CON_IN_EPNUM + 1)
#    define CON_OUT_EPNUM NEXT_OUT_EPNUM_1
#    define UDI_HID_CON_EP_OUT CON_OUT_EPNUM
#    define NEXT_OUT_EPNUM_2 (CON_OUT_EPNUM + 1)
#    define CON_POLLING_INTERVAL 1
#    ifndef UDI_HID_CON_STRING_ID
#        define UDI_HID_CON_STRING_ID 0
#    endif
#else
#    define NEXT_IN_EPNUM_5 NEXT_IN_EPNUM_4
#    define NEXT_OUT_EPNUM_2 NEXT_OUT_EPNUM_1
#endif

#ifdef NKRO_ENABLE
#    define NKRO_IN_EPNUM NEXT_IN_EPNUM_5
#    define UDI_HID_NKRO_EP_IN NKRO_IN_EPNUM
#    define NEXT_IN_EPNUM_6 (NKRO_IN_EPNUM + 1)
#    define UDI_HID_NKRO_EP_SIZE NKRO_EPSIZE
#    define NKRO_POLLING_INTERVAL 1
#    ifndef UDI_HID_NKRO_STRING_ID
#        define UDI_HID_NKRO_STRING_ID 0
#    endif
#else
#    define NEXT_IN_EPNUM_6 NEXT_IN_EPNUM_5
#endif

#ifdef MIDI_ENABLE
#    define MIDI_STREAM_IN_EPNUM NEXT_IN_EPNUM_6
#    define NEXT_IN_EPNUM_7 (MIDI_STREAM_IN_EPNUM + 1)
#    define MIDI_STREAM_OUT_EPNUM NEXT_OUT_EPNUM_2
#    define NEXT_OUT_EPNUM_3 (MIDI_STREAM_OUT_EPNUM + 1)
#    define MIDI_POLLING_INTERVAL 5
#else
#    define NEXT_IN_EPNUM_7 NEXT_IN_EPNUM_6
#    define NEXT_OUT_EPNUM_3 NEXT_OUT_EPNUM_2
#endif

#ifdef VIRTSER_ENABLE
#    define CDC_NOTIFICATION_EPNUM NEXT_IN_EPNUM_7
#    define CDC_ACM_ENDPOINT CDC_NOTIFICATION_EPNUM
#    define CDC_TX_ENDPOINT (CDC_NOTIFICATION_EPNUM + 1)
#    define NEXT_IN_EPNUM_8 (CDC_TX_ENDPOINT + 1)

#    define CDC_OUT_EPNUM NEXT_OUT_EPNUM_3
#    define CDC_RX_ENDPOINT CDC_OUT_EPNUM
#    define NEXT_OUT_EPNUM_4 (CDC_OUT_EPNUM + 1)

#    define CDC_ACM_SIZE CDC_NOTIFICATION_EPSIZE
#    define CDC_RX_SIZE CDC_EPSIZE // KFSMOD was 64
#    define CDC_TX_SIZE CDC_RX_SIZE
#    define CDC_ACM_POLLING_INTERVAL 255
#    define CDC_EP_INTERVAL_STATUS CDC_ACM_POLLING_INTERVAL
#    define CDC_DATA_POLLING_INTERVAL 5
#    define CDC_EP_INTERVAL_DATA CDC_DATA_POLLING_INTERVAL
#    define CDC_STATUS_NAME L"Virtual Serial Port - Status"
#    define CDC_DATA_NAME L"Virtual Serial Port - Data"
#else
#    define NEXT_IN_EPNUM_8 NEXT_IN_EPNUM_7
#    define NEXT_OUT_EPNUM_4 NEXT_OUT_EPNUM_3
#endif

#define TOTAL_OUT_EP NEXT_OUT_EPNUM_4
#define TOTAL_IN_EP NEXT_IN_EPNUM_8
#define USB_DEVICE_MAX_EP (max(NEXT_OUT_EPNUM_4, NEXT_IN_EPNUM_8))

#if USB_DEVICE_MAX_EP > 8
#    error "There are not enough available endpoints to support all functions. Remove some in the rules.mk file.(MOUSEKEY, EXTRAKEY, CONSOLE, NKRO, MIDI, VIRTSER)"
#endif

// **********************************************************************
// KBD Descriptor structure and content
// **********************************************************************
COMPILER_PACK_SET(1)

typedef struct {
    usb_iface_desc_t     iface;
    usb_hid_descriptor_t hid;
    usb_ep_desc_t        ep;
} udi_hid_kbd_desc_t;

typedef struct {
    uint8_t array[59];
} udi_hid_kbd_report_desc_t;

// clang-format off

#    define UDI_HID_KBD_DESC { \
    .iface = { \
        .bLength = sizeof(usb_iface_desc_t), \
        .bDescriptorType = USB_DT_INTERFACE, \
        .bInterfaceNumber = UDI_HID_KBD_IFACE_NUMBER, \
        .bAlternateSetting = 0, \
        .bNumEndpoints = 1, \
        .bInterfaceClass = HID_CLASS, \
        .bInterfaceSubClass = HID_SUB_CLASS_BOOT, \
        .bInterfaceProtocol = HID_PROTOCOL_KEYBOARD, \
        .iInterface = UDI_HID_KBD_STRING_ID, \
    }, \
    .hid = { \
        .bLength = sizeof(usb_hid_descriptor_t), \
        .bDescriptorType = USB_DT_HID, \
        .bcdHID = LE16(USB_HID_BDC_V1_11), \
        .bCountryCode = USB_HID_NO_COUNTRY_CODE, \
        .bNumDescriptors = USB_HID_NUM_DESC, \
        .bRDescriptorType = USB_DT_HID_REPORT, \
        .wDescriptorLength = LE16(sizeof(udi_hid_kbd_report_desc_t)), \
    }, \
    .ep = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = UDI_HID_KBD_EP_IN | USB_EP_DIR_IN, \
        .bmAttributes = USB_EP_TYPE_INTERRUPT, \
        .wMaxPacketSize = LE16(UDI_HID_KBD_EP_SIZE), \
        .bInterval = KBD_POLLING_INTERVAL \
    } \
}

// clang-format on

// set report buffer (from host)
extern uint8_t udi_hid_kbd_report_set;

// report buffer (to host)
#define UDI_HID_KBD_REPORT_SIZE 8
extern uint8_t udi_hid_kbd_report[UDI_HID_KBD_REPORT_SIZE];

COMPILER_PACK_RESET()

// **********************************************************************
// EXK Descriptor structure and content
// **********************************************************************
#ifdef EXTRAKEY_ENABLE

COMPILER_PACK_SET(1)

typedef struct {
    usb_iface_desc_t     iface;
    usb_hid_descriptor_t hid;
    usb_ep_desc_t        ep;
} udi_hid_exk_desc_t;

typedef struct {
    uint8_t array[50];
} udi_hid_exk_report_desc_t;

// clang-format off

#    define UDI_HID_EXK_DESC { \
    .iface = { \
        .bLength = sizeof(usb_iface_desc_t), \
        .bDescriptorType = USB_DT_INTERFACE, \
        .bInterfaceNumber = UDI_HID_EXK_IFACE_NUMBER, \
        .bAlternateSetting = 0, \
        .bNumEndpoints = 1, \
        .bInterfaceClass = HID_CLASS, \
        .bInterfaceSubClass = HID_SUB_CLASS_BOOT, \
        .bInterfaceProtocol = HID_PROTOCOL_GENERIC, \
        .iInterface = UDI_HID_EXK_STRING_ID \
    }, \
    .hid = { \
        .bLength = sizeof(usb_hid_descriptor_t), \
        .bDescriptorType = USB_DT_HID, \
        .bcdHID = LE16(USB_HID_BDC_V1_11), \
        .bCountryCode = USB_HID_NO_COUNTRY_CODE, \
        .bNumDescriptors = USB_HID_NUM_DESC, \
        .bRDescriptorType = USB_DT_HID_REPORT, \
        .wDescriptorLength = LE16(sizeof(udi_hid_exk_report_desc_t)) \
    }, \
    .ep = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = UDI_HID_EXK_EP_IN | USB_EP_DIR_IN, \
        .bmAttributes = USB_EP_TYPE_INTERRUPT, \
        .wMaxPacketSize = LE16(UDI_HID_EXK_EP_SIZE), \
        .bInterval = EXTRAKEY_POLLING_INTERVAL \
    } \
}

// clang-format on

// set report buffer (from host)
extern uint8_t udi_hid_exk_report_set;

// report buffer
#    define UDI_HID_EXK_REPORT_SIZE 3

typedef union {
    struct {
        uint8_t  report_id;
        uint16_t report_data;
    } desc;
    uint8_t raw[UDI_HID_EXK_REPORT_SIZE];
} udi_hid_exk_report_t;

extern udi_hid_exk_report_t udi_hid_exk_report;

COMPILER_PACK_RESET()

#endif // EXTRAKEY_ENABLE

// **********************************************************************
// NKRO Descriptor structure and content
// **********************************************************************
#ifdef NKRO_ENABLE

COMPILER_PACK_SET(1)

typedef struct {
    usb_iface_desc_t     iface;
    usb_hid_descriptor_t hid;
    usb_ep_desc_t        ep;
} udi_hid_nkro_desc_t;

typedef struct {
    uint8_t array[57];
} udi_hid_nkro_report_desc_t;

// clang-format off

#    define UDI_HID_NKRO_DESC { \
    .iface = { \
        .bLength = sizeof(usb_iface_desc_t), \
        .bDescriptorType = USB_DT_INTERFACE, \
        .bInterfaceNumber = UDI_HID_NKRO_IFACE_NUMBER, \
        .bAlternateSetting = 0, \
        .bNumEndpoints = 1, \
        .bInterfaceClass = HID_CLASS, \
        .bInterfaceSubClass = HID_SUB_CLASS_NOBOOT, \
        .bInterfaceProtocol = HID_PROTOCOL_KEYBOARD, \
        .iInterface = UDI_HID_NKRO_STRING_ID \
    }, \
    .hid = { \
        .bLength = sizeof(usb_hid_descriptor_t), \
        .bDescriptorType = USB_DT_HID, \
        .bcdHID = LE16(USB_HID_BDC_V1_11), \
        .bCountryCode = USB_HID_NO_COUNTRY_CODE, \
        .bNumDescriptors = USB_HID_NUM_DESC, \
        .bRDescriptorType = USB_DT_HID_REPORT, \
        .wDescriptorLength = LE16(sizeof(udi_hid_nkro_report_desc_t)) \
    }, \
    .ep = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = UDI_HID_NKRO_EP_IN | USB_EP_DIR_IN, \
        .bmAttributes = USB_EP_TYPE_INTERRUPT, \
        .wMaxPacketSize = LE16(UDI_HID_NKRO_EP_SIZE), \
        .bInterval = NKRO_POLLING_INTERVAL \
    } \
}

// clang-format on

// set report buffer
extern uint8_t udi_hid_nkro_report_set;

// report buffer
#    define UDI_HID_NKRO_REPORT_SIZE 32
extern uint8_t udi_hid_nkro_report[UDI_HID_NKRO_REPORT_SIZE];

COMPILER_PACK_RESET()

#endif // NKRO_ENABLE

// **********************************************************************
// MOU Descriptor structure and content
// **********************************************************************
#ifdef MOUSE_ENABLE

COMPILER_PACK_SET(1)

typedef struct {
    usb_iface_desc_t     iface;
    usb_hid_descriptor_t hid;
    usb_ep_desc_t        ep;
} udi_hid_mou_desc_t;

typedef struct {
    uint8_t array[77]; // MOU PDS
} udi_hid_mou_report_desc_t;

// clang-format off

#    define UDI_HID_MOU_DESC { \
    .iface = { \
        .bLength = sizeof(usb_iface_desc_t), \
        .bDescriptorType = USB_DT_INTERFACE, \
        .bInterfaceNumber = MOUSE_INTERFACE, \
        .bAlternateSetting = 0, \
        .bNumEndpoints = 1, \
        .bInterfaceClass = HID_CLASS, \
        .bInterfaceSubClass = HID_SUB_CLASS_BOOT, \
        .bInterfaceProtocol = HID_PROTOCOL_MOUSE, \
        .iInterface = UDI_HID_MOU_STRING_ID \
    }, \
    .hid = { \
        .bLength = sizeof(usb_hid_descriptor_t), \
        .bDescriptorType = USB_DT_HID, \
        .bcdHID = LE16(USB_HID_BDC_V1_11), \
        .bCountryCode = USB_HID_NO_COUNTRY_CODE, \
        .bNumDescriptors = USB_HID_NUM_DESC, \
        .bRDescriptorType = USB_DT_HID_REPORT, \
        .wDescriptorLength = LE16(sizeof(udi_hid_mou_report_desc_t)) \
    }, \
    .ep = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = UDI_HID_MOU_EP_IN | USB_EP_DIR_IN, \
        .bmAttributes = USB_EP_TYPE_INTERRUPT, \
        .wMaxPacketSize = LE16(UDI_HID_MOU_EP_SIZE), \
        .bInterval = MOU_POLLING_INTERVAL \
    } \
}

// clang-format on

// report buffer
#    define UDI_HID_MOU_REPORT_SIZE 5 // MOU PDS
extern uint8_t udi_hid_mou_report[UDI_HID_MOU_REPORT_SIZE];

COMPILER_PACK_RESET()

#endif // MOUSE_ENABLE

// **********************************************************************
// RAW Descriptor structure and content
// **********************************************************************
#ifdef RAW_ENABLE

COMPILER_PACK_SET(1)

typedef struct {
    usb_iface_desc_t     iface;
    usb_hid_descriptor_t hid;
    usb_ep_desc_t        ep_out;
    usb_ep_desc_t        ep_in;
} udi_hid_raw_desc_t;

typedef struct {
    uint8_t array[26];
} udi_hid_raw_report_desc_t;

// clang-format off

#    define UDI_HID_RAW_DESC { \
    .iface = { \
        .bLength = sizeof(usb_iface_desc_t), \
        .bDescriptorType = USB_DT_INTERFACE, \
        .bInterfaceNumber = RAW_INTERFACE, \
        .bAlternateSetting = 0, \
        .bNumEndpoints = 2, \
        .bInterfaceClass = HID_CLASS, \
        .bInterfaceSubClass = HID_SUB_CLASS_NOBOOT, \
        .bInterfaceProtocol = HID_SUB_CLASS_NOBOOT, \
        .iInterface = UDI_HID_RAW_STRING_ID \
    }, \
    .hid = { \
        .bLength = sizeof(usb_hid_descriptor_t), \
        .bDescriptorType = USB_DT_HID, \
        .bcdHID = LE16(USB_HID_BDC_V1_11), \
        .bCountryCode = USB_HID_NO_COUNTRY_CODE, \
        .bNumDescriptors = USB_HID_NUM_DESC, \
        .bRDescriptorType = USB_DT_HID_REPORT, \
        .wDescriptorLength = LE16(sizeof(udi_hid_raw_report_desc_t)) \
    }, \
    .ep_out = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = UDI_HID_RAW_EP_OUT | USB_EP_DIR_OUT, \
        .bmAttributes = USB_EP_TYPE_INTERRUPT, \
        .wMaxPacketSize = LE16(RAW_EPSIZE), \
        .bInterval = RAW_POLLING_INTERVAL \
    }, \
    .ep_in = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = UDI_HID_RAW_EP_IN | USB_EP_DIR_IN, \
        .bmAttributes = USB_EP_TYPE_INTERRUPT, \
        .wMaxPacketSize = LE16(RAW_EPSIZE), \
        .bInterval = RAW_POLLING_INTERVAL \
    } \
}

// clang-format on

#    define UDI_HID_RAW_REPORT_SIZE RAW_EPSIZE

extern uint8_t udi_hid_raw_report_set[UDI_HID_RAW_REPORT_SIZE];

// report buffer
extern uint8_t udi_hid_raw_report[UDI_HID_RAW_REPORT_SIZE];

COMPILER_PACK_RESET()

#endif // RAW_ENABLE

// **********************************************************************
// CON Descriptor structure and content
// **********************************************************************
#ifdef CONSOLE_ENABLE

COMPILER_PACK_SET(1)

typedef struct {
    usb_iface_desc_t     iface;
    usb_hid_descriptor_t hid;
    usb_ep_desc_t        ep_out;
    usb_ep_desc_t        ep_in;
} udi_hid_con_desc_t;

typedef struct {
    uint8_t array[34];
} udi_hid_con_report_desc_t;

// clang-format off

#    define UDI_HID_CON_DESC { \
    .iface = { \
        .bLength = sizeof(usb_iface_desc_t), \
        .bDescriptorType = USB_DT_INTERFACE, \
        .bInterfaceNumber = UDI_HID_CON_IFACE_NUMBER, \
        .bAlternateSetting = 0, \
        .bNumEndpoints = 2, \
        .bInterfaceClass = HID_CLASS, \
        .bInterfaceSubClass = HID_SUB_CLASS_NOBOOT, \
        .bInterfaceProtocol = HID_SUB_CLASS_NOBOOT, \
        .iInterface = UDI_HID_CON_STRING_ID \
    }, \
    .hid = { \
        .bLength = sizeof(usb_hid_descriptor_t), \
        .bDescriptorType = USB_DT_HID, \
        .bcdHID = LE16(USB_HID_BDC_V1_11), \
        .bCountryCode = USB_HID_NO_COUNTRY_CODE, \
        .bNumDescriptors = USB_HID_NUM_DESC, \
        .bRDescriptorType = USB_DT_HID_REPORT, \
        .wDescriptorLength = LE16(sizeof(udi_hid_con_report_desc_t)) \
    }, \
    .ep_out = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = UDI_HID_CON_EP_OUT | USB_EP_DIR_OUT, \
        .bmAttributes = USB_EP_TYPE_INTERRUPT, \
        .wMaxPacketSize = LE16(CONSOLE_EPSIZE), \
        .bInterval = CON_POLLING_INTERVAL \
    }, \
    .ep_in = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = UDI_HID_CON_EP_IN | USB_EP_DIR_IN, \
        .bmAttributes = USB_EP_TYPE_INTERRUPT, \
        .wMaxPacketSize = LE16(CONSOLE_EPSIZE), \
        .bInterval = CON_POLLING_INTERVAL \
    } \
}

// clang-format on

#    define UDI_HID_CON_REPORT_SIZE CONSOLE_EPSIZE

extern uint8_t udi_hid_con_report_set[UDI_HID_CON_REPORT_SIZE];

// report buffer
extern uint8_t udi_hid_con_report[UDI_HID_CON_REPORT_SIZE];

COMPILER_PACK_RESET()

#endif // CONSOLE_ENABLE

// **********************************************************************
// CDC Descriptor structure and content
// **********************************************************************
#ifdef VIRTSER_ENABLE

COMPILER_PACK_SET(1)

typedef struct {
    uint8_t bFunctionLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    le16_t  bcdCDC;
} usb_cdc_hdr_desc_t;

typedef struct {
    uint8_t bFunctionLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bmCapabilities;
    uint8_t bDataInterface;
} usb_cdc_call_mgmt_desc_t;

typedef struct {
    uint8_t bFunctionLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bmCapabilities;
} usb_cdc_acm_desc_t;

typedef struct {
    uint8_t bFunctionLength;
    uint8_t bDescriptorType;
    uint8_t bDescriptorSubtype;
    uint8_t bMasterInterface;
    uint8_t bSlaveInterface0;
} usb_cdc_union_desc_t;

typedef struct {
    usb_association_desc_t   iaface;
    usb_iface_desc_t         iface_c;
    usb_cdc_hdr_desc_t       fd;
    usb_cdc_call_mgmt_desc_t mfd;
    usb_cdc_acm_desc_t       acmd;
    usb_cdc_union_desc_t     ufd;
    usb_ep_desc_t            ep_c;
    usb_iface_desc_t         iface_d;
    usb_ep_desc_t            ep_tx;
    usb_ep_desc_t            ep_rx;
} udi_cdc_desc_t;

// clang-format off

#    define CDC_DESCRIPTOR { \
    .iaface = { \
        .bLength = sizeof(usb_association_desc_t), \
        .bDescriptorType = USB_DT_IAD, \
        .bFirstInterface = CDC_STATUS_INTERFACE, \
        .bInterfaceCount = 2, \
        .bFunctionClass = CDC_CLASS_DEVICE, \
        .bFunctionSubClass = CDC_SUBCLASS_ACM, \
        .bFunctionProtocol = CDC_PROTOCOL_V25TER, \
        .iFunction = 0 \
    }, \
    .iface_c = { \
        .bLength = sizeof(usb_iface_desc_t), \
        .bDescriptorType = USB_DT_INTERFACE, \
        .bInterfaceNumber = CDC_STATUS_INTERFACE, \
        .bAlternateSetting = 0, \
        .bNumEndpoints = 1, \
        .bInterfaceClass = 0x02, \
        .bInterfaceSubClass = 0x02, \
        .bInterfaceProtocol = CDC_PROTOCOL_V25TER, \
        .iInterface = 0 \
    }, \
    .fd = { \
        .bFunctionLength = sizeof(usb_cdc_hdr_desc_t), \
        .bDescriptorType = CDC_CS_INTERFACE, \
        .bDescriptorSubtype = CDC_SCS_HEADER, \
        .bcdCDC = 0x0110 \
    }, \
    .mfd = { \
        .bFunctionLength = sizeof(usb_cdc_call_mgmt_desc_t), \
        .bDescriptorType = CDC_CS_INTERFACE, \
        .bDescriptorSubtype = CDC_SCS_CALL_MGMT, \
        .bmCapabilities = CDC_CALL_MGMT_SUPPORTED, \
        .bDataInterface = CDC_DATA_INTERFACE \
    }, \
    .acmd = { \
        .bFunctionLength = sizeof(usb_cdc_acm_desc_t), \
        .bDescriptorType = CDC_CS_INTERFACE, \
        .bDescriptorSubtype = CDC_SCS_ACM, \
        .bmCapabilities = CDC_ACM_SUPPORT_LINE_REQUESTS \
    }, \
    .ufd = { \
        .bFunctionLength = sizeof(usb_cdc_union_desc_t), \
        .bDescriptorType = CDC_CS_INTERFACE, \
        .bDescriptorSubtype = CDC_SCS_UNION, \
        .bMasterInterface = CDC_STATUS_INTERFACE, \
        .bSlaveInterface0 = CDC_DATA_INTERFACE \
    }, \
    .ep_c = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = CDC_ACM_ENDPOINT | USB_EP_DIR_IN, \
        .bmAttributes = USB_EP_TYPE_INTERRUPT, \
        .wMaxPacketSize = LE16(CDC_ACM_SIZE), \
        .bInterval = CDC_EP_INTERVAL_STATUS \
    }, \
    .iface_d = { \
        .bLength = sizeof(usb_iface_desc_t), \
        .bDescriptorType = USB_DT_INTERFACE, \
        .bInterfaceNumber = CDC_DATA_INTERFACE, \
        .bAlternateSetting = 0, \
        .bNumEndpoints = 2, \
        .bInterfaceClass = CDC_CLASS_DATA, \
        .bInterfaceSubClass = 0, \
        .bInterfaceProtocol = 0, \
        .iInterface = 0 \
    }, \
    .ep_rx = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = CDC_RX_ENDPOINT | USB_EP_DIR_OUT, \
        .bmAttributes = USB_EP_TYPE_BULK, \
        .wMaxPacketSize = LE16(CDC_RX_SIZE), \
        .bInterval = CDC_EP_INTERVAL_DATA \
    }, \
    .ep_tx = { \
        .bLength = sizeof(usb_ep_desc_t), \
        .bDescriptorType = USB_DT_ENDPOINT, \
        .bEndpointAddress = CDC_TX_ENDPOINT | USB_EP_DIR_IN, \
        .bmAttributes = USB_EP_TYPE_BULK, \
        .wMaxPacketSize = LE16(CDC_TX_SIZE), \
        .bInterval = CDC_EP_INTERVAL_DATA \
    } \
}

// clang-format on

COMPILER_PACK_RESET()

#endif // VIRTSER_ENABLE

// **********************************************************************
// CONFIGURATION Descriptor structure and content
// **********************************************************************
COMPILER_PACK_SET(1)

typedef struct {
    usb_conf_desc_t    conf;
    udi_hid_kbd_desc_t hid_kbd;
#ifdef MOUSE_ENABLE
    udi_hid_mou_desc_t hid_mou;
#endif
#ifdef EXTRAKEY_ENABLE
    udi_hid_exk_desc_t hid_exk;
#endif
#ifdef RAW_ENABLE
    udi_hid_raw_desc_t hid_raw;
#endif
#ifdef CONSOLE_ENABLE
    udi_hid_con_desc_t hid_con;
#endif
#ifdef NKRO_ENABLE
    udi_hid_nkro_desc_t hid_nkro;
#endif
#ifdef MIDI_ENABLE
    udi_hid_midi_desc_t hid_midi;
#endif
#ifdef VIRTSER_ENABLE
    udi_cdc_desc_t cdc_serial;
#endif
} udc_desc_t;

COMPILER_PACK_RESET()

#endif //_UDI_DEVICE_CONF_H_
