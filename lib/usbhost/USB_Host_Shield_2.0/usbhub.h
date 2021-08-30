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
#if !defined(__USBHUB_H__)
#define __USBHUB_H__

#include "Usb.h"

#define USB_DESCRIPTOR_HUB                      0x09 // Hub descriptor type

// Hub Requests
#define bmREQ_CLEAR_HUB_FEATURE                 USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_DEVICE
#define bmREQ_CLEAR_PORT_FEATURE                USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_OTHER
#define bmREQ_CLEAR_TT_BUFFER                   USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_OTHER
#define bmREQ_GET_HUB_DESCRIPTOR                USB_SETUP_DEVICE_TO_HOST|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_DEVICE
#define bmREQ_GET_HUB_STATUS                    USB_SETUP_DEVICE_TO_HOST|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_DEVICE
#define bmREQ_GET_PORT_STATUS                   USB_SETUP_DEVICE_TO_HOST|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_OTHER
#define bmREQ_RESET_TT                          USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_OTHER
#define bmREQ_SET_HUB_DESCRIPTOR                USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_DEVICE
#define bmREQ_SET_HUB_FEATURE                   USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_DEVICE
#define bmREQ_SET_PORT_FEATURE                  USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_OTHER
#define bmREQ_GET_TT_STATE                      USB_SETUP_DEVICE_TO_HOST|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_OTHER
#define bmREQ_STOP_TT                           USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_CLASS|USB_SETUP_RECIPIENT_OTHER

// Hub Class Requests
#define HUB_REQUEST_CLEAR_TT_BUFFER             8
#define HUB_REQUEST_RESET_TT                    9
#define HUB_REQUEST_GET_TT_STATE                10
#define HUB_REQUEST_STOP_TT                     11

// Hub Features
#define HUB_FEATURE_C_HUB_LOCAL_POWER           0
#define HUB_FEATURE_C_HUB_OVER_CURRENT          1
#define HUB_FEATURE_PORT_CONNECTION             0
#define HUB_FEATURE_PORT_ENABLE                 1
#define HUB_FEATURE_PORT_SUSPEND                2
#define HUB_FEATURE_PORT_OVER_CURRENT           3
#define HUB_FEATURE_PORT_RESET                  4
#define HUB_FEATURE_PORT_POWER                  8
#define HUB_FEATURE_PORT_LOW_SPEED              9
#define HUB_FEATURE_C_PORT_CONNECTION           16
#define HUB_FEATURE_C_PORT_ENABLE               17
#define HUB_FEATURE_C_PORT_SUSPEND              18
#define HUB_FEATURE_C_PORT_OVER_CURRENT         19
#define HUB_FEATURE_C_PORT_RESET                20
#define HUB_FEATURE_PORT_TEST                   21
#define HUB_FEATURE_PORT_INDICATOR              22

// Hub Port Test Modes
#define HUB_PORT_TEST_MODE_J                    1
#define HUB_PORT_TEST_MODE_K                    2
#define HUB_PORT_TEST_MODE_SE0_NAK              3
#define HUB_PORT_TEST_MODE_PACKET               4
#define HUB_PORT_TEST_MODE_FORCE_ENABLE         5

// Hub Port Indicator Color
#define HUB_PORT_INDICATOR_AUTO                 0
#define HUB_PORT_INDICATOR_AMBER                1
#define HUB_PORT_INDICATOR_GREEN                2
#define HUB_PORT_INDICATOR_OFF                  3

// Hub Port Status Bitmasks
#define bmHUB_PORT_STATUS_PORT_CONNECTION       0x0001
#define bmHUB_PORT_STATUS_PORT_ENABLE           0x0002
#define bmHUB_PORT_STATUS_PORT_SUSPEND          0x0004
#define bmHUB_PORT_STATUS_PORT_OVER_CURRENT     0x0008
#define bmHUB_PORT_STATUS_PORT_RESET            0x0010
#define bmHUB_PORT_STATUS_PORT_POWER            0x0100
#define bmHUB_PORT_STATUS_PORT_LOW_SPEED        0x0200
#define bmHUB_PORT_STATUS_PORT_HIGH_SPEED       0x0400
#define bmHUB_PORT_STATUS_PORT_TEST             0x0800
#define bmHUB_PORT_STATUS_PORT_INDICATOR        0x1000

// Hub Port Status Change Bitmasks (used one byte instead of two)
#define bmHUB_PORT_STATUS_C_PORT_CONNECTION     0x0001
#define bmHUB_PORT_STATUS_C_PORT_ENABLE         0x0002
#define bmHUB_PORT_STATUS_C_PORT_SUSPEND        0x0004
#define bmHUB_PORT_STATUS_C_PORT_OVER_CURRENT   0x0008
#define bmHUB_PORT_STATUS_C_PORT_RESET          0x0010

// Hub Status Bitmasks (used one byte instead of two)
#define bmHUB_STATUS_LOCAL_POWER_SOURCE         0x01
#define bmHUB_STATUS_OVER_CURRENT               0x12

// Hub Status Change Bitmasks (used one byte instead of two)
#define bmHUB_STATUS_C_LOCAL_POWER_SOURCE       0x01
#define bmHUB_STATUS_C_OVER_CURRENT             0x12


// Hub Port Configuring Substates
#define USB_STATE_HUB_PORT_CONFIGURING          0xb0
#define USB_STATE_HUB_PORT_POWERED_OFF          0xb1
#define USB_STATE_HUB_PORT_WAIT_FOR_POWER_GOOD  0xb2
#define USB_STATE_HUB_PORT_DISCONNECTED         0xb3
#define USB_STATE_HUB_PORT_DISABLED             0xb4
#define USB_STATE_HUB_PORT_RESETTING            0xb5
#define USB_STATE_HUB_PORT_ENABLED              0xb6

// Additional Error Codes
#define HUB_ERROR_PORT_HAS_BEEN_RESET           0xb1

// The bit mask to check for all necessary state bits
#define bmHUB_PORT_STATUS_ALL_MAIN              ((0UL | bmHUB_PORT_STATUS_C_PORT_CONNECTION | bmHUB_PORT_STATUS_C_PORT_ENABLE | bmHUB_PORT_STATUS_C_PORT_SUSPEND | bmHUB_PORT_STATUS_C_PORT_RESET) << 16) | bmHUB_PORT_STATUS_PORT_POWER | bmHUB_PORT_STATUS_PORT_ENABLE | bmHUB_PORT_STATUS_PORT_CONNECTION | bmHUB_PORT_STATUS_PORT_SUSPEND)

// Bit mask to check for DISABLED state in HubEvent::bmStatus field
#define bmHUB_PORT_STATE_CHECK_DISABLED         (0x0000 | bmHUB_PORT_STATUS_PORT_POWER | bmHUB_PORT_STATUS_PORT_ENABLE | bmHUB_PORT_STATUS_PORT_CONNECTION | bmHUB_PORT_STATUS_PORT_SUSPEND)

// Hub Port States
#define bmHUB_PORT_STATE_DISABLED               (0x0000 | bmHUB_PORT_STATUS_PORT_POWER | bmHUB_PORT_STATUS_PORT_CONNECTION)

// Hub Port Events
#define bmHUB_PORT_EVENT_CONNECT                (((0UL | bmHUB_PORT_STATUS_C_PORT_CONNECTION) << 16) | bmHUB_PORT_STATUS_PORT_POWER | bmHUB_PORT_STATUS_PORT_CONNECTION)
#define bmHUB_PORT_EVENT_DISCONNECT             (((0UL | bmHUB_PORT_STATUS_C_PORT_CONNECTION) << 16) | bmHUB_PORT_STATUS_PORT_POWER)
#define bmHUB_PORT_EVENT_RESET_COMPLETE         (((0UL | bmHUB_PORT_STATUS_C_PORT_RESET) << 16) | bmHUB_PORT_STATUS_PORT_POWER | bmHUB_PORT_STATUS_PORT_ENABLE | bmHUB_PORT_STATUS_PORT_CONNECTION)

#define bmHUB_PORT_EVENT_LS_CONNECT             (((0UL | bmHUB_PORT_STATUS_C_PORT_CONNECTION) << 16) | bmHUB_PORT_STATUS_PORT_POWER | bmHUB_PORT_STATUS_PORT_CONNECTION | bmHUB_PORT_STATUS_PORT_LOW_SPEED)
#define bmHUB_PORT_EVENT_LS_RESET_COMPLETE      (((0UL | bmHUB_PORT_STATUS_C_PORT_RESET) << 16) | bmHUB_PORT_STATUS_PORT_POWER | bmHUB_PORT_STATUS_PORT_ENABLE | bmHUB_PORT_STATUS_PORT_CONNECTION | bmHUB_PORT_STATUS_PORT_LOW_SPEED)
#define bmHUB_PORT_EVENT_LS_PORT_ENABLED        (((0UL | bmHUB_PORT_STATUS_C_PORT_CONNECTION | bmHUB_PORT_STATUS_C_PORT_ENABLE) << 16) | bmHUB_PORT_STATUS_PORT_POWER | bmHUB_PORT_STATUS_PORT_ENABLE | bmHUB_PORT_STATUS_PORT_CONNECTION | bmHUB_PORT_STATUS_PORT_LOW_SPEED)

struct HubDescriptor {
        uint8_t bDescLength; // descriptor length
        uint8_t bDescriptorType; // descriptor type
        uint8_t bNbrPorts; // number of ports a hub equiped with

        struct {
                uint16_t LogPwrSwitchMode : 2;
                uint16_t CompoundDevice : 1;
                uint16_t OverCurrentProtectMode : 2;
                uint16_t TTThinkTime : 2;
                uint16_t PortIndicatorsSupported : 1;
                uint16_t Reserved : 8;
        } __attribute__((packed));

        uint8_t bPwrOn2PwrGood;
        uint8_t bHubContrCurrent;
} __attribute__((packed));

struct HubEvent {

        union {

                struct {
                        uint16_t bmStatus; // port status bits
                        uint16_t bmChange; // port status change bits
                } __attribute__((packed));
                uint32_t bmEvent;
                uint8_t evtBuff[4];
        };
} __attribute__((packed));

class USBHub : USBDeviceConfig {
        static bool bResetInitiated; // True when reset is triggered

        USB *pUsb; // USB class instance pointer

        EpInfo epInfo[2]; // interrupt endpoint info structure

        uint8_t bAddress; // address
        uint8_t bNbrPorts; // number of ports
        //        uint8_t bInitState; // initialization state variable
        uint32_t qNextPollTime; // next poll time
        bool bPollEnable; // poll enable flag

        uint8_t CheckHubStatus();
        uint8_t PortStatusChange(uint8_t port, HubEvent &evt);

public:
        USBHub(USB *p);

        uint8_t ClearHubFeature(uint8_t fid);
        uint8_t ClearPortFeature(uint8_t fid, uint8_t port, uint8_t sel = 0);
        uint8_t GetHubDescriptor(uint8_t index, uint16_t nbytes, uint8_t *dataptr);
        uint8_t GetHubStatus(uint16_t nbytes, uint8_t* dataptr);
        uint8_t GetPortStatus(uint8_t port, uint16_t nbytes, uint8_t* dataptr);
        uint8_t SetHubDescriptor(uint8_t port, uint16_t nbytes, uint8_t* dataptr);
        uint8_t SetHubFeature(uint8_t fid);
        uint8_t SetPortFeature(uint8_t fid, uint8_t port, uint8_t sel = 0);

        void PrintHubStatus();

        uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);
        uint8_t Release();
        uint8_t Poll();
        void ResetHubPort(uint8_t port);

        virtual uint8_t GetAddress() {
                return bAddress;
        };

        virtual bool DEVCLASSOK(uint8_t klass) {
                return (klass == 0x09);
        }

};

// Clear Hub Feature

inline uint8_t USBHub::ClearHubFeature(uint8_t fid) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_CLEAR_HUB_FEATURE, USB_REQUEST_CLEAR_FEATURE, fid, 0, 0, 0, 0, NULL, NULL));
}
// Clear Port Feature

inline uint8_t USBHub::ClearPortFeature(uint8_t fid, uint8_t port, uint8_t sel) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_CLEAR_PORT_FEATURE, USB_REQUEST_CLEAR_FEATURE, fid, 0, ((0x0000 | port) | (sel << 8)), 0, 0, NULL, NULL));
}
// Get Hub Descriptor

inline uint8_t USBHub::GetHubDescriptor(uint8_t index, uint16_t nbytes, uint8_t *dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_GET_HUB_DESCRIPTOR, USB_REQUEST_GET_DESCRIPTOR, index, 0x29, 0, nbytes, nbytes, dataptr, NULL));
}
// Get Hub Status

inline uint8_t USBHub::GetHubStatus(uint16_t nbytes, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_GET_HUB_STATUS, USB_REQUEST_GET_STATUS, 0, 0, 0x0000, nbytes, nbytes, dataptr, NULL));
}
// Get Port Status

inline uint8_t USBHub::GetPortStatus(uint8_t port, uint16_t nbytes, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_GET_PORT_STATUS, USB_REQUEST_GET_STATUS, 0, 0, port, nbytes, nbytes, dataptr, NULL));
}
// Set Hub Descriptor

inline uint8_t USBHub::SetHubDescriptor(uint8_t port, uint16_t nbytes, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_SET_HUB_DESCRIPTOR, USB_REQUEST_SET_DESCRIPTOR, 0, 0, port, nbytes, nbytes, dataptr, NULL));
}
// Set Hub Feature

inline uint8_t USBHub::SetHubFeature(uint8_t fid) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_SET_HUB_FEATURE, USB_REQUEST_SET_FEATURE, fid, 0, 0, 0, 0, NULL, NULL));
}
// Set Port Feature

inline uint8_t USBHub::SetPortFeature(uint8_t fid, uint8_t port, uint8_t sel) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_SET_PORT_FEATURE, USB_REQUEST_SET_FEATURE, fid, 0, (((0x0000 | sel) << 8) | port), 0, 0, NULL, NULL));
}

void PrintHubPortStatus(USB *usbptr, uint8_t addr, uint8_t port, bool print_changes = false);

#endif // __USBHUB_H__
