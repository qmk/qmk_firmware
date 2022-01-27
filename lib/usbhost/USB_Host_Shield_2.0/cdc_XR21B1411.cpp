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
#include "cdc_XR21B1411.h"

XR21B1411::XR21B1411(USB *p, CDCAsyncOper *pasync) :
ACM(p, pasync) {
        // Is this needed??
        _enhanced_status = enhanced_features(); // Set up features
}

uint8_t XR21B1411::Init(uint8_t parent, uint8_t port, bool lowspeed) {
        const uint8_t constBufSize = sizeof (USB_DEVICE_DESCRIPTOR);

        uint8_t buf[constBufSize];
        USB_DEVICE_DESCRIPTOR * udd = reinterpret_cast<USB_DEVICE_DESCRIPTOR*>(buf);

        uint8_t rcode;
        UsbDevice *p = NULL;
        EpInfo *oldep_ptr = NULL;
        uint8_t num_of_conf; // number of configurations

        AddressPool &addrPool = pUsb->GetAddressPool();

        USBTRACE("XR Init\r\n");

        if(bAddress)
                return USB_ERROR_CLASS_INSTANCE_ALREADY_IN_USE;

        // Get pointer to pseudo device with address 0 assigned
        p = addrPool.GetUsbDevicePtr(0);

        if(!p)
                return USB_ERROR_ADDRESS_NOT_FOUND_IN_POOL;

        if(!p->epinfo) {
                USBTRACE("epinfo\r\n");
                return USB_ERROR_EPINFO_IS_NULL;
        }

        // Save old pointer to EP_RECORD of address 0
        oldep_ptr = p->epinfo;

        // Temporary assign new pointer to epInfo to p->epinfo in order to avoid toggle inconsistence
        p->epinfo = epInfo;

        p->lowspeed = lowspeed;

        // Get device descriptor
        rcode = pUsb->getDevDescr(0, 0, constBufSize, (uint8_t*)buf);

        // Restore p->epinfo
        p->epinfo = oldep_ptr;

        if(rcode)
                goto FailGetDevDescr;

        // Allocate new address according to device class
        bAddress = addrPool.AllocAddress(parent, false, port);

        if(!bAddress)
                return USB_ERROR_OUT_OF_ADDRESS_SPACE_IN_POOL;

        // Extract Max Packet Size from the device descriptor
        epInfo[0].maxPktSize = udd->bMaxPacketSize0;

        // Assign new address to the device
        rcode = pUsb->setAddr(0, 0, bAddress);

        if(rcode) {
                p->lowspeed = false;
                addrPool.FreeAddress(bAddress);
                bAddress = 0;
                USBTRACE2("setAddr:", rcode);
                return rcode;
        }

        USBTRACE2("Addr:", bAddress);

        p->lowspeed = false;

        p = addrPool.GetUsbDevicePtr(bAddress);

        if(!p)
                return USB_ERROR_ADDRESS_NOT_FOUND_IN_POOL;

        p->lowspeed = lowspeed;

        num_of_conf = udd->bNumConfigurations;

        if((((udd->idVendor != 0x2890U) || (udd->idProduct != 0x0201U)) && ((udd->idVendor != 0x04e2U) || (udd->idProduct != 0x1411U))))
                return USB_DEV_CONFIG_ERROR_DEVICE_NOT_SUPPORTED;

        // Assign epInfo to epinfo pointer
        rcode = pUsb->setEpInfoEntry(bAddress, 1, epInfo);

        if(rcode)
                goto FailSetDevTblEntry;

        USBTRACE2("NC:", num_of_conf);

        for(uint8_t i = 0; i < num_of_conf; i++) {
                ConfigDescParser< USB_CLASS_COM_AND_CDC_CTRL,
                        CDC_SUBCLASS_ACM,
                        CDC_PROTOCOL_ITU_T_V_250,
                        CP_MASK_COMPARE_CLASS |
                        CP_MASK_COMPARE_SUBCLASS |
                        CP_MASK_COMPARE_PROTOCOL > CdcControlParser(this);

                ConfigDescParser<USB_CLASS_CDC_DATA, 0, 0,
                        CP_MASK_COMPARE_CLASS> CdcDataParser(this);

                rcode = pUsb->getConfDescr(bAddress, 0, i, &CdcControlParser);

                if(rcode)
                        goto FailGetConfDescr;

                rcode = pUsb->getConfDescr(bAddress, 0, i, &CdcDataParser);

                if(rcode)
                        goto FailGetConfDescr;

                if(bNumEP > 1)
                        break;
        } // for

        if(bNumEP < 4)
                return USB_DEV_CONFIG_ERROR_DEVICE_NOT_SUPPORTED;

        // Assign epInfo to epinfo pointer
        rcode = pUsb->setEpInfoEntry(bAddress, bNumEP, epInfo);

        USBTRACE2("Conf:", bConfNum);

        // Set Configuration Value
        rcode = pUsb->setConf(bAddress, 0, bConfNum);

        if(rcode)
                goto FailSetConfDescr;

        // Set up features status
        _enhanced_status = enhanced_features();
        half_duplex(false);
        autoflowRTS(false);
        autoflowDSR(false);
        autoflowXON(false);
        wide(false); // Always false, because this is only available in custom mode.

        rcode = pAsync->OnInit(this);

        if(rcode)
                goto FailOnInit;

        USBTRACE("XR configured\r\n");

        ready = true;

        //bPollEnable = true;

        //USBTRACE("Poll enabled\r\n");
        return 0;

FailGetDevDescr:
#ifdef DEBUG_USB_HOST
        NotifyFailGetDevDescr();
        goto Fail;
#endif

FailSetDevTblEntry:
#ifdef DEBUG_USB_HOST
        NotifyFailSetDevTblEntry();
        goto Fail;
#endif

FailGetConfDescr:
#ifdef DEBUG_USB_HOST
        NotifyFailGetConfDescr();
        goto Fail;
#endif

FailSetConfDescr:
#ifdef DEBUG_USB_HOST
        NotifyFailSetConfDescr();
        goto Fail;
#endif

FailOnInit:
#ifdef DEBUG_USB_HOST
        USBTRACE("OnInit:");
#endif

#ifdef DEBUG_USB_HOST
Fail:
        NotifyFail(rcode);
#endif
        Release();
        return rcode;
}
