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

#define DEVICE_CLASS 0
#define DEVICE_SUBCLASS 0
#define DEVICE_PROTOCOL 0

#define KBD

//#define MOUSE_ENABLE //rules.mk
#ifdef MOUSE_ENABLE
#    define MOU
#endif

//#define EXTRAKEY_ENABLE //rules.mk
#ifdef EXTRAKEY_ENABLE
#    define EXK
#endif

//#define RAW_ENABLE //rules.mk
#ifdef RAW_ENABLE
#    define RAW
#endif

//#define CONSOLE_ENABLE //rules.mk
#ifdef CONSOLE_ENABLE
#    define CON
#endif

//#define NKRO_ENABLE //rules.mk
#ifdef NKRO_ENABLE
#    define NKRO
#endif

//#define MIDI_ENABLE //deferred implementation
//#ifdef MIDI_ENABLE
//#define MIDI
//#endif

//#define VIRTSER_ENABLE //rules.mk
#ifdef VIRTSER_ENABLE
#    define CDC
// because CDC uses IAD (interface association descriptor
// per USB Interface Association Descriptor Device Class Code and Use Model 7/23/2003 Rev 1.0)
#    undef DEVICE_CLASS
#    define DEVICE_CLASS 0xEF
#    undef DEVICE_SUBCLASS
#    define DEVICE_SUBCLASS 0x02
#    undef DEVICE_PROTOCOL
#    define DEVICE_PROTOCOL 0x01
#endif

/* number of interfaces */
#define NEXT_INTERFACE_0 0

#ifdef KBD
#    define KEYBOARD_INTERFACE NEXT_INTERFACE_0
#    define NEXT_INTERFACE_1 (KEYBOARD_INTERFACE + 1)
#    define UDI_HID_KBD_IFACE_NUMBER KEYBOARD_INTERFACE
#else
#    define NEXT_INTERFACE_1 NEXT_INTERFACE_0
#endif

// It is important that the Raw HID interface is at a constant
// interface number, to support Linux/OSX platforms and chrome.hid
// If Raw HID is enabled, let it be always 1.
#ifdef RAW
#    define RAW_INTERFACE NEXT_INTERFACE_1
#    define NEXT_INTERFACE_2 (RAW_INTERFACE + 1)
#else
#    define NEXT_INTERFACE_2 NEXT_INTERFACE_1
#endif

#ifdef MOU
#    define MOUSE_INTERFACE NEXT_INTERFACE_2
#    define UDI_HID_MOU_IFACE_NUMBER MOUSE_INTERFACE
#    define NEXT_INTERFACE_3 (MOUSE_INTERFACE + 1)
#else
#    define NEXT_INTERFACE_3 NEXT_INTERFACE_2
#endif

#ifdef EXK
#    define EXTRAKEY_INTERFACE NEXT_INTERFACE_3
#    define NEXT_INTERFACE_4 (EXTRAKEY_INTERFACE + 1)
#    define UDI_HID_EXK_IFACE_NUMBER EXTRAKEY_INTERFACE
#else
#    define NEXT_INTERFACE_4 NEXT_INTERFACE_3
#endif

#ifdef CON
#    define CON_INTERFACE NEXT_INTERFACE_4
#    define NEXT_INTERFACE_5 (CON_INTERFACE + 1)
#    define UDI_HID_CON_IFACE_NUMBER CON_INTERFACE
#else
#    define NEXT_INTERFACE_5 NEXT_INTERFACE_4
#endif

#ifdef NKRO
#    define NKRO_INTERFACE NEXT_INTERFACE_5
#    define NEXT_INTERFACE_6 (NKRO_INTERFACE + 1)
#    define UDI_HID_NKRO_IFACE_NUMBER NKRO_INTERFACE
#else
#    define NEXT_INTERFACE_6 NEXT_INTERFACE_5
#endif

#ifdef MIDI
#    define AC_INTERFACE NEXT_INTERFACE_6
#    define AS_INTERFACE (AC_INTERFACE + 1)
#    define NEXT_INTERFACE_7 (AS_INTERFACE + 1)
#else
#    define NEXT_INTERFACE_7 NEXT_INTERFACE_6
#endif

#ifdef CDC
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

#ifdef KBD
#    define KEYBOARD_IN_EPNUM NEXT_IN_EPNUM_0
#    define UDI_HID_KBD_EP_IN KEYBOARD_IN_EPNUM
#    define NEXT_IN_EPNUM_1 (KEYBOARD_IN_EPNUM + 1)
#    define UDI_HID_KBD_EP_SIZE KEYBOARD_EPSIZE
#    define KBD_POLLING_INTERVAL 10
#    ifndef UDI_HID_KBD_STRING_ID
#        define UDI_HID_KBD_STRING_ID 0
#    endif
#else
#    define NEXT_IN_EPNUM_1 NEXT_IN_EPNUM_0
#endif

#ifdef MOU
#    define MOUSE_IN_EPNUM NEXT_IN_EPNUM_1
#    define NEXT_IN_EPNUM_2 (MOUSE_IN_EPNUM + 1)
#    define UDI_HID_MOU_EP_IN MOUSE_IN_EPNUM
#    define UDI_HID_MOU_EP_SIZE MOUSE_EPSIZE
#    define MOU_POLLING_INTERVAL 10
#    ifndef UDI_HID_MOU_STRING_ID
#        define UDI_HID_MOU_STRING_ID 0
#    endif
#else
#    define NEXT_IN_EPNUM_2 NEXT_IN_EPNUM_1
#endif

#ifdef EXK
#    define EXTRAKEY_IN_EPNUM NEXT_IN_EPNUM_2
#    define UDI_HID_EXK_EP_IN EXTRAKEY_IN_EPNUM
#    define NEXT_IN_EPNUM_3 (EXTRAKEY_IN_EPNUM + 1)
#    define UDI_HID_EXK_EP_SIZE EXTRAKEY_EPSIZE
#    define EXTRAKEY_POLLING_INTERVAL 10
#    ifndef UDI_HID_EXK_STRING_ID
#        define UDI_HID_EXK_STRING_ID 0
#    endif
#else
#    define NEXT_IN_EPNUM_3 NEXT_IN_EPNUM_2
#endif

#ifdef RAW
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

#ifdef CON
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

#ifdef NKRO
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

#ifdef MIDI
#    define MIDI_STREAM_IN_EPNUM NEXT_IN_EPNUM_6
#    define NEXT_IN_EPNUM_7 (MIDI_STREAM_IN_EPNUM + 1)
#    define MIDI_STREAM_OUT_EPNUM NEXT_OUT_EPNUM_2
#    define NEXT_OUT_EPNUM_3 (MIDI_STREAM_OUT_EPNUM + 1)
#    define MIDI_POLLING_INTERVAL 5
#else
#    define NEXT_IN_EPNUM_7 NEXT_IN_EPNUM_6
#    define NEXT_OUT_EPNUM_3 NEXT_OUT_EPNUM_2
#endif

#ifdef CDC
#    define CDC_NOTIFICATION_EPNUM NEXT_IN_EPNUM_7
#    define CDC_ACM_ENDPOINT CDC_NOTIFICATION_EPNUM
#    define CDC_TX_ENDPOINT (CDC_NOTIFICATION_EPNUM + 1)
#    define NEXT_IN_EPNUM_8 (CDC_TX_ENDPOINT + 1)

#    define CDC_OUT_EPNUM NEXT_OUT_EPNUM_3
#    define CDC_RX_ENDPOINT CDC_OUT_EPNUM
#    define NEXT_OUT_EPNUM_4 (CDC_OUT_EPNUM + 1)

#    define CDC_ACM_SIZE CDC_NOTIFICATION_EPSIZE
#    define CDC_RX_SIZE CDC_EPSIZE  // KFSMOD was 64
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
#ifdef KBD

COMPILER_PACK_SET(1)

typedef struct {
    usb_iface_desc_t     iface;
    usb_hid_descriptor_t hid;
    usb_ep_desc_t        ep;
} udi_hid_kbd_desc_t;

typedef struct {
    uint8_t array[59];
} udi_hid_kbd_report_desc_t;

#    define UDI_HID_KBD_DESC \
        { .iface.bLength = sizeof(usb_iface_desc_t), .iface.bDescriptorType = USB_DT_INTERFACE, .iface.bInterfaceNumber = UDI_HID_KBD_IFACE_NUMBER, .iface.bAlternateSetting = 0, .iface.bNumEndpoints = 1, .iface.bInterfaceClass = HID_CLASS, .iface.bInterfaceSubClass = HID_SUB_CLASS_BOOT, .iface.bInterfaceProtocol = HID_PROTOCOL_KEYBOARD, .iface.iInterface = UDI_HID_KBD_STRING_ID, .hid.bLength = sizeof(usb_hid_descriptor_t), .hid.bDescriptorType = USB_DT_HID, .hid.bcdHID = LE16(USB_HID_BDC_V1_11), .hid.bCountryCode = USB_HID_NO_COUNTRY_CODE, .hid.bNumDescriptors = USB_HID_NUM_DESC, .hid.bRDescriptorType = USB_DT_HID_REPORT, .hid.wDescriptorLength = LE16(sizeof(udi_hid_kbd_report_desc_t)), .ep.bLength = sizeof(usb_ep_desc_t), .ep.bDescriptorType = USB_DT_ENDPOINT, .ep.bEndpointAddress = UDI_HID_KBD_EP_IN | USB_EP_DIR_IN, .ep.bmAttributes = USB_EP_TYPE_INTERRUPT, .ep.wMaxPacketSize = LE16(UDI_HID_KBD_EP_SIZE), .ep.bInterval = KBD_POLLING_INTERVAL, }

// set report buffer (from host)
extern uint8_t udi_hid_kbd_report_set;

// report buffer (to host)
#    define UDI_HID_KBD_REPORT_SIZE 8
extern uint8_t udi_hid_kbd_report[UDI_HID_KBD_REPORT_SIZE];

COMPILER_PACK_RESET()

#endif  // KBD

// **********************************************************************
// EXK Descriptor structure and content
// **********************************************************************
#ifdef EXK

COMPILER_PACK_SET(1)

typedef struct {
    usb_iface_desc_t     iface;
    usb_hid_descriptor_t hid;
    usb_ep_desc_t        ep;
} udi_hid_exk_desc_t;

typedef struct {
    uint8_t array[50];
} udi_hid_exk_report_desc_t;

#    define UDI_HID_EXK_DESC \
        { .iface.bLength = sizeof(usb_iface_desc_t), .iface.bDescriptorType = USB_DT_INTERFACE, .iface.bInterfaceNumber = UDI_HID_EXK_IFACE_NUMBER, .iface.bAlternateSetting = 0, .iface.bNumEndpoints = 1, .iface.bInterfaceClass = HID_CLASS, .iface.bInterfaceSubClass = HID_SUB_CLASS_BOOT, .iface.bInterfaceProtocol = HID_PROTOCOL_GENERIC, .iface.iInterface = UDI_HID_EXK_STRING_ID, .hid.bLength = sizeof(usb_hid_descriptor_t), .hid.bDescriptorType = USB_DT_HID, .hid.bcdHID = LE16(USB_HID_BDC_V1_11), .hid.bCountryCode = USB_HID_NO_COUNTRY_CODE, .hid.bNumDescriptors = USB_HID_NUM_DESC, .hid.bRDescriptorType = USB_DT_HID_REPORT, .hid.wDescriptorLength = LE16(sizeof(udi_hid_exk_report_desc_t)), .ep.bLength = sizeof(usb_ep_desc_t), .ep.bDescriptorType = USB_DT_ENDPOINT, .ep.bEndpointAddress = UDI_HID_EXK_EP_IN | USB_EP_DIR_IN, .ep.bmAttributes = USB_EP_TYPE_INTERRUPT, .ep.wMaxPacketSize = LE16(UDI_HID_EXK_EP_SIZE), .ep.bInterval = EXTRAKEY_POLLING_INTERVAL, }

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

#endif  // EXK

// **********************************************************************
// NKRO Descriptor structure and content
// **********************************************************************
#ifdef NKRO

COMPILER_PACK_SET(1)

typedef struct {
    usb_iface_desc_t     iface;
    usb_hid_descriptor_t hid;
    usb_ep_desc_t        ep;
} udi_hid_nkro_desc_t;

typedef struct {
    uint8_t array[57];
} udi_hid_nkro_report_desc_t;

#    define UDI_HID_NKRO_DESC \
        { .iface.bLength = sizeof(usb_iface_desc_t), .iface.bDescriptorType = USB_DT_INTERFACE, .iface.bInterfaceNumber = UDI_HID_NKRO_IFACE_NUMBER, .iface.bAlternateSetting = 0, .iface.bNumEndpoints = 1, .iface.bInterfaceClass = HID_CLASS, .iface.bInterfaceSubClass = HID_SUB_CLASS_NOBOOT, .iface.bInterfaceProtocol = HID_PROTOCOL_KEYBOARD, .iface.iInterface = UDI_HID_NKRO_STRING_ID, .hid.bLength = sizeof(usb_hid_descriptor_t), .hid.bDescriptorType = USB_DT_HID, .hid.bcdHID = LE16(USB_HID_BDC_V1_11), .hid.bCountryCode = USB_HID_NO_COUNTRY_CODE, .hid.bNumDescriptors = USB_HID_NUM_DESC, .hid.bRDescriptorType = USB_DT_HID_REPORT, .hid.wDescriptorLength = LE16(sizeof(udi_hid_nkro_report_desc_t)), .ep.bLength = sizeof(usb_ep_desc_t), .ep.bDescriptorType = USB_DT_ENDPOINT, .ep.bEndpointAddress = UDI_HID_NKRO_EP_IN | USB_EP_DIR_IN, .ep.bmAttributes = USB_EP_TYPE_INTERRUPT, .ep.wMaxPacketSize = LE16(UDI_HID_NKRO_EP_SIZE), .ep.bInterval = NKRO_POLLING_INTERVAL, }

// set report buffer
extern uint8_t udi_hid_nkro_report_set;

// report buffer
#    define UDI_HID_NKRO_REPORT_SIZE 32
extern uint8_t udi_hid_nkro_report[UDI_HID_NKRO_REPORT_SIZE];

COMPILER_PACK_RESET()

#endif  // NKRO

// **********************************************************************
// MOU Descriptor structure and content
// **********************************************************************
#ifdef MOU

COMPILER_PACK_SET(1)

typedef struct {
    usb_iface_desc_t     iface;
    usb_hid_descriptor_t hid;
    usb_ep_desc_t        ep;
} udi_hid_mou_desc_t;

typedef struct {
    uint8_t array[77];  // MOU PDS
} udi_hid_mou_report_desc_t;

#    define UDI_HID_MOU_DESC \
        { .iface.bLength = sizeof(usb_iface_desc_t), .iface.bDescriptorType = USB_DT_INTERFACE, .iface.bInterfaceNumber = MOUSE_INTERFACE, .iface.bAlternateSetting = 0, .iface.bNumEndpoints = 1, .iface.bInterfaceClass = HID_CLASS, .iface.bInterfaceSubClass = HID_SUB_CLASS_BOOT, .iface.bInterfaceProtocol = HID_PROTOCOL_MOUSE, .iface.iInterface = UDI_HID_MOU_STRING_ID, .hid.bLength = sizeof(usb_hid_descriptor_t), .hid.bDescriptorType = USB_DT_HID, .hid.bcdHID = LE16(USB_HID_BDC_V1_11), .hid.bCountryCode = USB_HID_NO_COUNTRY_CODE, .hid.bNumDescriptors = USB_HID_NUM_DESC, .hid.bRDescriptorType = USB_DT_HID_REPORT, .hid.wDescriptorLength = LE16(sizeof(udi_hid_mou_report_desc_t)), .ep.bLength = sizeof(usb_ep_desc_t), .ep.bDescriptorType = USB_DT_ENDPOINT, .ep.bEndpointAddress = UDI_HID_MOU_EP_IN | USB_EP_DIR_IN, .ep.bmAttributes = USB_EP_TYPE_INTERRUPT, .ep.wMaxPacketSize = LE16(UDI_HID_MOU_EP_SIZE), .ep.bInterval = MOU_POLLING_INTERVAL, }

// no set report buffer

// report buffer
#    define UDI_HID_MOU_REPORT_SIZE 5  // MOU PDS
extern uint8_t udi_hid_mou_report[UDI_HID_MOU_REPORT_SIZE];

COMPILER_PACK_RESET()

#endif  // MOU

// **********************************************************************
// RAW Descriptor structure and content
// **********************************************************************
#ifdef RAW

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

#    define UDI_HID_RAW_DESC                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              \
            .iface.bLength = sizeof(usb_iface_desc_t), .iface.bDescriptorType = USB_DT_INTERFACE, .iface.bInterfaceNumber = RAW_INTERFACE, .iface.bAlternateSetting = 0, .iface.bNumEndpoints = 2, .iface.bInterfaceClass = HID_CLASS, .iface.bInterfaceSubClass = HID_SUB_CLASS_NOBOOT, .iface.bInterfaceProtocol = HID_SUB_CLASS_NOBOOT, .iface.iInterface = UDI_HID_RAW_STRING_ID, .hid.bLength = sizeof(usb_hid_descriptor_t), .hid.bDescriptorType = USB_DT_HID, .hid.bcdHID = LE16(USB_HID_BDC_V1_11), .hid.bCountryCode = USB_HID_NO_COUNTRY_CODE, .hid.bNumDescriptors = USB_HID_NUM_DESC, .hid.bRDescriptorType = USB_DT_HID_REPORT, .hid.wDescriptorLength = LE16(sizeof(udi_hid_raw_report_desc_t)), .ep_out.bLength = sizeof(usb_ep_desc_t), .ep_out.bDescriptorType = USB_DT_ENDPOINT, .ep_out.bEndpointAddress = UDI_HID_RAW_EP_OUT | USB_EP_DIR_OUT, .ep_out.bmAttributes = USB_EP_TYPE_INTERRUPT, .ep_out.wMaxPacketSize = LE16(RAW_EPSIZE), .ep_out.bInterval = RAW_POLLING_INTERVAL, \
            .ep_in.bLength = sizeof(usb_ep_desc_t), .ep_in.bDescriptorType = USB_DT_ENDPOINT, .ep_in.bEndpointAddress = UDI_HID_RAW_EP_IN | USB_EP_DIR_IN, .ep_in.bmAttributes = USB_EP_TYPE_INTERRUPT, .ep_in.wMaxPacketSize = LE16(RAW_EPSIZE), .ep_in.bInterval = RAW_POLLING_INTERVAL,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             \
        }

#    define UDI_HID_RAW_REPORT_SIZE RAW_EPSIZE

extern uint8_t udi_hid_raw_report_set[UDI_HID_RAW_REPORT_SIZE];

// report buffer
extern uint8_t udi_hid_raw_report[UDI_HID_RAW_REPORT_SIZE];

COMPILER_PACK_RESET()

#endif  // RAW

// **********************************************************************
// CON Descriptor structure and content
// **********************************************************************
#ifdef CON

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

#    define UDI_HID_CON_DESC                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          \
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             \
            .iface.bLength = sizeof(usb_iface_desc_t), .iface.bDescriptorType = USB_DT_INTERFACE, .iface.bInterfaceNumber = UDI_HID_CON_IFACE_NUMBER, .iface.bAlternateSetting = 0, .iface.bNumEndpoints = 2, .iface.bInterfaceClass = HID_CLASS, .iface.bInterfaceSubClass = HID_SUB_CLASS_NOBOOT, .iface.bInterfaceProtocol = HID_SUB_CLASS_NOBOOT, .iface.iInterface = UDI_HID_CON_STRING_ID, .hid.bLength = sizeof(usb_hid_descriptor_t), .hid.bDescriptorType = USB_DT_HID, .hid.bcdHID = LE16(USB_HID_BDC_V1_11), .hid.bCountryCode = USB_HID_NO_COUNTRY_CODE, .hid.bNumDescriptors = USB_HID_NUM_DESC, .hid.bRDescriptorType = USB_DT_HID_REPORT, .hid.wDescriptorLength = LE16(sizeof(udi_hid_con_report_desc_t)), .ep_out.bLength = sizeof(usb_ep_desc_t), .ep_out.bDescriptorType = USB_DT_ENDPOINT, .ep_out.bEndpointAddress = UDI_HID_CON_EP_OUT | USB_EP_DIR_OUT, .ep_out.bmAttributes = USB_EP_TYPE_INTERRUPT, .ep_out.wMaxPacketSize = LE16(CONSOLE_EPSIZE), .ep_out.bInterval = CON_POLLING_INTERVAL, \
            .ep_in.bLength = sizeof(usb_ep_desc_t), .ep_in.bDescriptorType = USB_DT_ENDPOINT, .ep_in.bEndpointAddress = UDI_HID_CON_EP_IN | USB_EP_DIR_IN, .ep_in.bmAttributes = USB_EP_TYPE_INTERRUPT, .ep_in.wMaxPacketSize = LE16(CONSOLE_EPSIZE), .ep_in.bInterval = CON_POLLING_INTERVAL,                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        \
        }

#    define UDI_HID_CON_REPORT_SIZE CONSOLE_EPSIZE

extern uint8_t udi_hid_con_report_set[UDI_HID_CON_REPORT_SIZE];

// report buffer
extern uint8_t udi_hid_con_report[UDI_HID_CON_REPORT_SIZE];

COMPILER_PACK_RESET()

#endif  // CON

// **********************************************************************
// CDC Descriptor structure and content
// **********************************************************************
#ifdef CDC

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

#    define CDC_DESCRIPTOR                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          \
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           \
            .iaface.bLength = sizeof(usb_association_desc_t), .iaface.bDescriptorType = USB_DT_IAD, .iaface.bFirstInterface = CDC_STATUS_INTERFACE, .iaface.bInterfaceCount = 2, .iaface.bFunctionClass = CDC_CLASS_DEVICE, .iaface.bFunctionSubClass = CDC_SUBCLASS_ACM, .iaface.bFunctionProtocol = CDC_PROTOCOL_V25TER, .iaface.iFunction = 0, .iface_c.bLength = sizeof(usb_iface_desc_t), .iface_c.bDescriptorType = USB_DT_INTERFACE, .iface_c.bInterfaceNumber = CDC_STATUS_INTERFACE, .iface_c.bAlternateSetting = 0, .iface_c.bNumEndpoints = 1, .iface_c.bInterfaceClass = 0x02, .iface_c.bInterfaceSubClass = 0x02, .iface_c.bInterfaceProtocol = CDC_PROTOCOL_V25TER, .iface_c.iInterface = 0, .fd.bFunctionLength = sizeof(usb_cdc_hdr_desc_t), .fd.bDescriptorType = CDC_CS_INTERFACE, .fd.bDescriptorSubtype = CDC_SCS_HEADER, .fd.bcdCDC = 0x0110, .mfd.bFunctionLength = sizeof(usb_cdc_call_mgmt_desc_t), .mfd.bDescriptorType = CDC_CS_INTERFACE, .mfd.bDescriptorSubtype = CDC_SCS_CALL_MGMT,   \
            .mfd.bmCapabilities = CDC_CALL_MGMT_SUPPORTED, .mfd.bDataInterface = CDC_DATA_INTERFACE, .acmd.bFunctionLength = sizeof(usb_cdc_acm_desc_t), .acmd.bDescriptorType = CDC_CS_INTERFACE, .acmd.bDescriptorSubtype = CDC_SCS_ACM, .acmd.bmCapabilities = CDC_ACM_SUPPORT_LINE_REQUESTS, .ufd.bFunctionLength = sizeof(usb_cdc_union_desc_t), .ufd.bDescriptorType = CDC_CS_INTERFACE, .ufd.bDescriptorSubtype = CDC_SCS_UNION, .ufd.bMasterInterface = CDC_STATUS_INTERFACE, .ufd.bSlaveInterface0 = CDC_DATA_INTERFACE, .ep_c.bLength = sizeof(usb_ep_desc_t), .ep_c.bDescriptorType = USB_DT_ENDPOINT, .ep_c.bEndpointAddress = CDC_ACM_ENDPOINT | USB_EP_DIR_IN, .ep_c.bmAttributes = USB_EP_TYPE_INTERRUPT, .ep_c.wMaxPacketSize = LE16(CDC_ACM_SIZE), .ep_c.bInterval = CDC_EP_INTERVAL_STATUS, .iface_d.bLength = sizeof(usb_iface_desc_t), .iface_d.bDescriptorType = USB_DT_INTERFACE, .iface_d.bInterfaceNumber = CDC_DATA_INTERFACE, .iface_d.bAlternateSetting = 0, .iface_d.bNumEndpoints = 2, \
            .iface_d.bInterfaceClass = CDC_CLASS_DATA, .iface_d.bInterfaceSubClass = 0, .iface_d.bInterfaceProtocol = 0, .iface_d.iInterface = 0, .ep_rx.bLength = sizeof(usb_ep_desc_t), .ep_rx.bDescriptorType = USB_DT_ENDPOINT, .ep_rx.bEndpointAddress = CDC_RX_ENDPOINT | USB_EP_DIR_OUT, .ep_rx.bmAttributes = USB_EP_TYPE_BULK, .ep_rx.wMaxPacketSize = LE16(CDC_RX_SIZE), .ep_rx.bInterval = CDC_EP_INTERVAL_DATA, .ep_tx.bLength = sizeof(usb_ep_desc_t), .ep_tx.bDescriptorType = USB_DT_ENDPOINT, .ep_tx.bEndpointAddress = CDC_TX_ENDPOINT | USB_EP_DIR_IN, .ep_tx.bmAttributes = USB_EP_TYPE_BULK, .ep_tx.wMaxPacketSize = LE16(CDC_TX_SIZE), .ep_tx.bInterval = CDC_EP_INTERVAL_DATA,                                                                                                                                                                                                                                                                                                                \
        }

COMPILER_PACK_RESET()

#endif  // CDC

// **********************************************************************
// CONFIGURATION Descriptor structure and content
// **********************************************************************
COMPILER_PACK_SET(1)

typedef struct {
    usb_conf_desc_t conf;
#ifdef KBD
    udi_hid_kbd_desc_t hid_kbd;
#endif
#ifdef MOU
    udi_hid_mou_desc_t hid_mou;
#endif
#ifdef EXK
    udi_hid_exk_desc_t hid_exk;
#endif
#ifdef RAW
    udi_hid_raw_desc_t hid_raw;
#endif
#ifdef CON
    udi_hid_con_desc_t hid_con;
#endif
#ifdef NKRO
    udi_hid_nkro_desc_t hid_nkro;
#endif
#ifdef MIDI
    udi_hid_midi_desc_t hid_midi;
#endif
#ifdef CDC
    udi_cdc_desc_t cdc_serial;
#endif
} udc_desc_t;

COMPILER_PACK_RESET()

#endif  //_UDI_DEVICE_CONF_H_
