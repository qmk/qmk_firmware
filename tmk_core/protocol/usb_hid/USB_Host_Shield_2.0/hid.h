/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */
#if !defined(__HID_H__)
#define __HID_H__

#include "Usb.h"
#include "hidusagestr.h"

#define MAX_REPORT_PARSERS                      2
#define HID_MAX_HID_CLASS_DESCRIPTORS           5

#define DATA_SIZE_MASK                          0x03
#define TYPE_MASK                               0x0C
#define TAG_MASK                                0xF0

#define DATA_SIZE_0                             0x00
#define DATA_SIZE_1                             0x01
#define DATA_SIZE_2                             0x02
#define DATA_SIZE_4                             0x03

#define TYPE_MAIN                               0x00
#define TYPE_GLOBAL                             0x04
#define TYPE_LOCAL                              0x08

#define TAG_MAIN_INPUT                          0x80
#define TAG_MAIN_OUTPUT                         0x90
#define TAG_MAIN_COLLECTION                     0xA0
#define TAG_MAIN_FEATURE                        0xB0
#define TAG_MAIN_ENDCOLLECTION                  0xC0

#define TAG_GLOBAL_USAGEPAGE                    0x00
#define TAG_GLOBAL_LOGICALMIN                   0x10
#define TAG_GLOBAL_LOGICALMAX                   0x20
#define TAG_GLOBAL_PHYSMIN                      0x30
#define TAG_GLOBAL_PHYSMAX                      0x40
#define TAG_GLOBAL_UNITEXP                      0x50
#define TAG_GLOBAL_UNIT                         0x60
#define TAG_GLOBAL_REPORTSIZE                   0x70
#define TAG_GLOBAL_REPORTID                     0x80
#define TAG_GLOBAL_REPORTCOUNT                  0x90
#define TAG_GLOBAL_PUSH                         0xA0
#define TAG_GLOBAL_POP                          0xB0

#define TAG_LOCAL_USAGE                         0x00
#define TAG_LOCAL_USAGEMIN                      0x10
#define TAG_LOCAL_USAGEMAX                      0x20

/* HID requests */
#define bmREQ_HID_OUT                           USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_INTERFACE
#define bmREQ_HID_IN                            USB_SETUP_DEVICE_TO_HOST|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_INTERFACE
#define bmREQ_HID_REPORT                        USB_SETUP_DEVICE_TO_HOST|USB_SETUP_TYPE_STANDARD|USB_SETUP_RECIPIENT_INTERFACE

/* HID constants. Not part of chapter 9 */
/* Class-Specific Requests */
#define HID_REQUEST_GET_REPORT                  0x01
#define HID_REQUEST_GET_IDLE                    0x02
#define HID_REQUEST_GET_PROTOCOL                0x03
#define HID_REQUEST_SET_REPORT                  0x09
#define HID_REQUEST_SET_IDLE                    0x0A
#define HID_REQUEST_SET_PROTOCOL                0x0B

/* Class Descriptor Types */
#define HID_DESCRIPTOR_HID                      0x21
#define HID_DESCRIPTOR_REPORT                   0x22
#define HID_DESRIPTOR_PHY                       0x23

/* Protocol Selection */
#define HID_BOOT_PROTOCOL                       0x00
#define HID_RPT_PROTOCOL                        0x01

/* HID Interface Class Code */
#define HID_INTF                                0x03

/* HID Interface Class SubClass Codes */
#define HID_BOOT_INTF_SUBCLASS                  0x01

/* HID Interface Class Protocol Codes */
#define HID_PROTOCOL_NONE                       0x00
#define HID_PROTOCOL_KEYBOARD                   0x01
#define HID_PROTOCOL_MOUSE                      0x02

#define HID_ITEM_TYPE_MAIN                      0
#define HID_ITEM_TYPE_GLOBAL                    1
#define HID_ITEM_TYPE_LOCAL                     2
#define HID_ITEM_TYPE_RESERVED                  3

#define HID_LONG_ITEM_PREFIX                    0xfe    // Long item prefix value

#define bmHID_MAIN_ITEM_TAG                     0xfc    // Main item tag mask

#define bmHID_MAIN_ITEM_INPUT                   0x80    // Main item Input tag value
#define bmHID_MAIN_ITEM_OUTPUT                  0x90    // Main item Output tag value
#define bmHID_MAIN_ITEM_FEATURE                 0xb0    // Main item Feature tag value
#define bmHID_MAIN_ITEM_COLLECTION              0xa0    // Main item Collection tag value
#define bmHID_MAIN_ITEM_END_COLLECTION          0xce    // Main item End Collection tag value

#define HID_MAIN_ITEM_COLLECTION_PHYSICAL       0
#define HID_MAIN_ITEM_COLLECTION_APPLICATION    1
#define HID_MAIN_ITEM_COLLECTION_LOGICAL        2
#define HID_MAIN_ITEM_COLLECTION_REPORT         3
#define HID_MAIN_ITEM_COLLECTION_NAMED_ARRAY    4
#define HID_MAIN_ITEM_COLLECTION_USAGE_SWITCH   5
#define HID_MAIN_ITEM_COLLECTION_USAGE_MODIFIER 6

struct HidItemPrefix {
        uint8_t bSize : 2;
        uint8_t bType : 2;
        uint8_t bTag : 4;
};

struct MainItemIOFeature {
        uint8_t bmIsConstantOrData : 1;
        uint8_t bmIsArrayOrVariable : 1;
        uint8_t bmIsRelativeOrAbsolute : 1;
        uint8_t bmIsWrapOrNoWrap : 1;
        uint8_t bmIsNonLonearOrLinear : 1;
        uint8_t bmIsNoPreferedOrPrefered : 1;
        uint8_t bmIsNullOrNoNull : 1;
        uint8_t bmIsVolatileOrNonVolatile : 1;
};

class HID;

class HIDReportParser {
public:
        virtual void Parse(HID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) = 0;
};

class HID : public USBDeviceConfig, public UsbConfigXtracter {
protected:
        USB *pUsb; // USB class instance pointer
        uint8_t bAddress; // address

protected:
        static const uint8_t epInterruptInIndex = 1; // InterruptIN  endpoint index
        static const uint8_t epInterruptOutIndex = 2; // InterruptOUT endpoint index

        static const uint8_t maxHidInterfaces = 3;
        static const uint8_t maxEpPerInterface = 2;
        static const uint8_t totalEndpoints = (maxHidInterfaces * maxEpPerInterface + 1);

        void PrintEndpointDescriptor(const USB_ENDPOINT_DESCRIPTOR* ep_ptr);
        void PrintHidDescriptor(const USB_HID_DESCRIPTOR *pDesc);

        virtual HIDReportParser* GetReportParser(uint8_t id) {
                return NULL;
        };

public:

        HID(USB *pusb) : pUsb(pusb) {
        };

        const USB* GetUsb() {
                return pUsb;
        };

        virtual bool SetReportParser(uint8_t id, HIDReportParser *prs) {
                return false;
        };

        uint8_t SetProtocol(uint8_t iface, uint8_t protocol);
        uint8_t GetProtocol(uint8_t iface, uint8_t* dataptr);
        uint8_t GetIdle(uint8_t iface, uint8_t reportID, uint8_t* dataptr);
        uint8_t SetIdle(uint8_t iface, uint8_t reportID, uint8_t duration);

        uint8_t GetReportDescr(uint16_t wIndex, USBReadParser *parser = NULL);

        uint8_t GetHidDescr(uint8_t ep, uint16_t nbytes, uint8_t* dataptr);
        uint8_t GetReport(uint8_t ep, uint8_t iface, uint8_t report_type, uint8_t report_id, uint16_t nbytes, uint8_t* dataptr);
        uint8_t SetReport(uint8_t ep, uint8_t iface, uint8_t report_type, uint8_t report_id, uint16_t nbytes, uint8_t* dataptr);
};

#endif // __HID_H__
