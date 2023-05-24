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

/* Google ADK interface support header */

#if !defined(_ADK_H_)
#define _ADK_H_

#include "Usb.h"

#define ADK_VID   0x18D1
#define ADK_PID   0x2D00
#define ADB_PID   0x2D01

#define XOOM  //enables repeating getProto() and getConf() attempts
//necessary for slow devices such as Motorola XOOM
//defined by default, can be commented out to save memory

/* requests */

#define ADK_GETPROTO      51  //check USB accessory protocol version
#define ADK_SENDSTR       52  //send identifying string
#define ADK_ACCSTART      53  //start device in accessory mode

#define bmREQ_ADK_GET     USB_SETUP_DEVICE_TO_HOST|USB_SETUP_TYPE_VENDOR|USB_SETUP_RECIPIENT_DEVICE
#define bmREQ_ADK_SEND    USB_SETUP_HOST_TO_DEVICE|USB_SETUP_TYPE_VENDOR|USB_SETUP_RECIPIENT_DEVICE

#define ACCESSORY_STRING_MANUFACTURER   0
#define ACCESSORY_STRING_MODEL          1
#define ACCESSORY_STRING_DESCRIPTION    2
#define ACCESSORY_STRING_VERSION        3
#define ACCESSORY_STRING_URI            4
#define ACCESSORY_STRING_SERIAL         5

#define ADK_MAX_ENDPOINTS 3 //endpoint 0, bulk_IN, bulk_OUT

class ADK;

class ADK : public USBDeviceConfig, public UsbConfigXtracter {
private:
        /* ID strings */
        const char* manufacturer;
        const char* model;
        const char* description;
        const char* version;
        const char* uri;
        const char* serial;

        /* ADK proprietary requests */
        uint8_t getProto(uint8_t* adkproto);
        uint8_t sendStr(uint8_t index, const char* str);
        uint8_t switchAcc(void);

protected:
        static const uint8_t epDataInIndex; // DataIn endpoint index
        static const uint8_t epDataOutIndex; // DataOUT endpoint index

        /* mandatory members */
        USB *pUsb;
        uint8_t bAddress;
        uint8_t bConfNum; // configuration number

        uint8_t bNumEP; // total number of EP in the configuration
        bool ready;

        /* Endpoint data structure */
        EpInfo epInfo[ADK_MAX_ENDPOINTS];

        void PrintEndpointDescriptor(const USB_ENDPOINT_DESCRIPTOR* ep_ptr);

public:
        ADK(USB *pUsb, const char* manufacturer,
                const char* model,
                const char* description,
                const char* version,
                const char* uri,
                const char* serial);

        // Methods for receiving and sending data
        uint8_t RcvData(uint16_t *nbytesptr, uint8_t *dataptr);
        uint8_t SndData(uint16_t nbytes, uint8_t *dataptr);


        // USBDeviceConfig implementation
        uint8_t ConfigureDevice(uint8_t parent, uint8_t port, bool lowspeed);
        uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);
        uint8_t Release();

        virtual uint8_t Poll() {
                return 0;
        };

        virtual uint8_t GetAddress() {
                return bAddress;
        };

        virtual bool isReady() {
                return ready;
        };

        virtual bool VIDPIDOK(uint16_t vid, uint16_t pid) {
                return (vid == ADK_VID && (pid == ADK_PID || pid == ADB_PID));
        };

        //UsbConfigXtracter implementation
        void EndpointXtract(uint8_t conf, uint8_t iface, uint8_t alt, uint8_t proto, const USB_ENDPOINT_DESCRIPTOR *ep);
}; //class ADK : public USBDeviceConfig ...

/* get ADK protocol version */

/* returns 2 bytes in *adkproto */
inline uint8_t ADK::getProto(uint8_t* adkproto) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_ADK_GET, ADK_GETPROTO, 0, 0, 0, 2, 2, adkproto, NULL));
}

/* send ADK string */
inline uint8_t ADK::sendStr(uint8_t index, const char* str) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_ADK_SEND, ADK_SENDSTR, 0, 0, index, strlen(str) + 1, strlen(str) + 1, (uint8_t*)str, NULL));
}

/* switch to accessory mode */
inline uint8_t ADK::switchAcc(void) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_ADK_SEND, ADK_ACCSTART, 0, 0, 0, 0, 0, NULL, NULL));
}

#endif // _ADK_H_
