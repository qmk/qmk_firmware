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

#include "hiduniversal.h"

HIDUniversal::HIDUniversal(USB *p) :
HID(p),
qNextPollTime(0),
pollInterval(0),
bPollEnable(false),
bHasReportId(false) {
        Initialize();

        if(pUsb)
                pUsb->RegisterDeviceClass(this);
}

uint16_t HIDUniversal::GetHidClassDescrLen(uint8_t type, uint8_t num) {
        for(uint8_t i = 0, n = 0; i < HID_MAX_HID_CLASS_DESCRIPTORS; i++) {
                if(descrInfo[i].bDescrType == type) {
                        if(n == num)
                                return descrInfo[i].wDescriptorLength;
                        n++;
                }
        }
        return 0;
}

void HIDUniversal::Initialize() {
        for(uint8_t i = 0; i < MAX_REPORT_PARSERS; i++) {
                rptParsers[i].rptId = 0;
                rptParsers[i].rptParser = NULL;
        }
        for(uint8_t i = 0; i < HID_MAX_HID_CLASS_DESCRIPTORS; i++) {
                descrInfo[i].bDescrType = 0;
                descrInfo[i].wDescriptorLength = 0;
        }
        for(uint8_t i = 0; i < maxHidInterfaces; i++) {
                hidInterfaces[i].bmInterface = 0;
                hidInterfaces[i].bmProtocol = 0;

                for(uint8_t j = 0; j < maxEpPerInterface; j++)
                        hidInterfaces[i].epIndex[j] = 0;
        }
        for(uint8_t i = 0; i < totalEndpoints; i++) {
                epInfo[i].epAddr = 0;
                epInfo[i].maxPktSize = (i) ? 0 : 8;
                epInfo[i].epAttribs = 0;
                epInfo[i].bmNakPower = (i) ? USB_NAK_NOWAIT : USB_NAK_MAX_POWER;
        }
        bNumEP = 1;
        bNumIface = 0;
        bConfNum = 0;
        pollInterval = 0;

        ZeroMemory(constBuffLen, prevBuf);
}

bool HIDUniversal::SetReportParser(uint8_t id, HIDReportParser *prs) {
        for(uint8_t i = 0; i < MAX_REPORT_PARSERS; i++) {
                if(rptParsers[i].rptId == 0 && rptParsers[i].rptParser == NULL) {
                        rptParsers[i].rptId = id;
                        rptParsers[i].rptParser = prs;
                        return true;
                }
        }
        return false;
}

HIDReportParser* HIDUniversal::GetReportParser(uint8_t id) {
        if(!bHasReportId)
                return ((rptParsers[0].rptParser) ? rptParsers[0].rptParser : NULL);

        for(uint8_t i = 0; i < MAX_REPORT_PARSERS; i++) {
                if(rptParsers[i].rptId == id)
                        return rptParsers[i].rptParser;
        }
        return NULL;
}

uint8_t HIDUniversal::Init(uint8_t parent, uint8_t port, bool lowspeed) {
        const uint8_t constBufSize = sizeof (USB_DEVICE_DESCRIPTOR);

        uint8_t buf[constBufSize];
        USB_DEVICE_DESCRIPTOR * udd = reinterpret_cast<USB_DEVICE_DESCRIPTOR*>(buf);
        uint8_t rcode;
        UsbDevice *p = NULL;
        EpInfo *oldep_ptr = NULL;
        uint8_t len = 0;

        uint8_t num_of_conf; // number of configurations
        //uint8_t num_of_intf; // number of interfaces

        AddressPool &addrPool = pUsb->GetAddressPool();

        USBTRACE("HU Init\r\n");

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
        rcode = pUsb->getDevDescr(0, 0, 8, (uint8_t*)buf);

        if(!rcode)
                len = (buf[0] > constBufSize) ? constBufSize : buf[0];

        if(rcode) {
                // Restore p->epinfo
                p->epinfo = oldep_ptr;

                goto FailGetDevDescr;
        }

        // Restore p->epinfo
        p->epinfo = oldep_ptr;

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

        //delay(2); //per USB 2.0 sect.9.2.6.3

        USBTRACE2("Addr:", bAddress);

        p->lowspeed = false;

        p = addrPool.GetUsbDevicePtr(bAddress);

        if(!p)
                return USB_ERROR_ADDRESS_NOT_FOUND_IN_POOL;

        p->lowspeed = lowspeed;

        if(len)
                rcode = pUsb->getDevDescr(bAddress, 0, len, (uint8_t*)buf);

        if(rcode)
                goto FailGetDevDescr;

        VID = udd->idVendor; // Can be used by classes that inherits this class to check the VID and PID of the connected device
        PID = udd->idProduct;

        num_of_conf = udd->bNumConfigurations;

        // Assign epInfo to epinfo pointer
        rcode = pUsb->setEpInfoEntry(bAddress, 1, epInfo);

        if(rcode)
                goto FailSetDevTblEntry;

        USBTRACE2("NC:", num_of_conf);

        for(uint8_t i = 0; i < num_of_conf; i++) {
                //HexDumper<USBReadParser, uint16_t, uint16_t> HexDump;
                ConfigDescParser<USB_CLASS_HID, 0, 0,
                        CP_MASK_COMPARE_CLASS> confDescrParser(this);

                //rcode = pUsb->getConfDescr(bAddress, 0, i, &HexDump);
                rcode = pUsb->getConfDescr(bAddress, 0, i, &confDescrParser);

                if(rcode)
                        goto FailGetConfDescr;

                if(bNumEP > 1)
                        break;
        } // for

        if(bNumEP < 2)
                return USB_DEV_CONFIG_ERROR_DEVICE_NOT_SUPPORTED;

        // Assign epInfo to epinfo pointer
        rcode = pUsb->setEpInfoEntry(bAddress, bNumEP, epInfo);

        USBTRACE2("Cnf:", bConfNum);

        // Set Configuration Value
        rcode = pUsb->setConf(bAddress, 0, bConfNum);

        if(rcode)
                goto FailSetConfDescr;

        for(uint8_t i = 0; i < bNumIface; i++) {
                if(hidInterfaces[i].epIndex[epInterruptInIndex] == 0)
                        continue;

                rcode = SetIdle(hidInterfaces[i].bmInterface, 0, 0);

                if(rcode && rcode != hrSTALL)
                        goto FailSetIdle;
        }

        USBTRACE("HU configured\r\n");

        OnInitSuccessful();

        bPollEnable = true;
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


FailSetIdle:
#ifdef DEBUG_USB_HOST
        USBTRACE("SetIdle:");
#endif

#ifdef DEBUG_USB_HOST
Fail:
        NotifyFail(rcode);
#endif
        Release();
        return rcode;
}

HIDUniversal::HIDInterface* HIDUniversal::FindInterface(uint8_t iface, uint8_t alt, uint8_t proto) {
        for(uint8_t i = 0; i < bNumIface && i < maxHidInterfaces; i++)
                if(hidInterfaces[i].bmInterface == iface && hidInterfaces[i].bmAltSet == alt
                        && hidInterfaces[i].bmProtocol == proto)
                        return hidInterfaces + i;
        return NULL;
}

void HIDUniversal::EndpointXtract(uint8_t conf, uint8_t iface, uint8_t alt, uint8_t proto, const USB_ENDPOINT_DESCRIPTOR *pep) {
        // If the first configuration satisfies, the others are not concidered.
        if(bNumEP > 1 && conf != bConfNum)
                return;

        //ErrorMessage<uint8_t>(PSTR("\r\nConf.Val"), conf);
        //ErrorMessage<uint8_t>(PSTR("Iface Num"), iface);
        //ErrorMessage<uint8_t>(PSTR("Alt.Set"), alt);

        bConfNum = conf;

        uint8_t index = 0;
        HIDInterface *piface = FindInterface(iface, alt, proto);

        // Fill in interface structure in case of new interface
        if(!piface) {
                piface = hidInterfaces + bNumIface;
                piface->bmInterface = iface;
                piface->bmAltSet = alt;
                piface->bmProtocol = proto;
                bNumIface++;
        }

        if((pep->bmAttributes & 0x03) == 3 && (pep->bEndpointAddress & 0x80) == 0x80)
                index = epInterruptInIndex;
        else
                index = epInterruptOutIndex;

        if(index) {
                // Fill in the endpoint info structure
                epInfo[bNumEP].epAddr = (pep->bEndpointAddress & 0x0F);
                epInfo[bNumEP].maxPktSize = (uint8_t)pep->wMaxPacketSize;
                epInfo[bNumEP].epAttribs = 0;
                epInfo[bNumEP].bmNakPower = USB_NAK_NOWAIT;

                // Fill in the endpoint index list
                piface->epIndex[index] = bNumEP; //(pep->bEndpointAddress & 0x0F);

                if(pollInterval < pep->bInterval) // Set the polling interval as the largest polling interval obtained from endpoints
                        pollInterval = pep->bInterval;

                bNumEP++;
        }
        //PrintEndpointDescriptor(pep);
}

uint8_t HIDUniversal::Release() {
        pUsb->GetAddressPool().FreeAddress(bAddress);

        bNumEP = 1;
        bAddress = 0;
        qNextPollTime = 0;
        bPollEnable = false;
        return 0;
}

bool HIDUniversal::BuffersIdentical(uint8_t len, uint8_t *buf1, uint8_t *buf2) {
        for(uint8_t i = 0; i < len; i++)
                if(buf1[i] != buf2[i])
                        return false;
        return true;
}

void HIDUniversal::ZeroMemory(uint8_t len, uint8_t *buf) {
        for(uint8_t i = 0; i < len; i++)
                buf[i] = 0;
}

void HIDUniversal::SaveBuffer(uint8_t len, uint8_t *src, uint8_t *dest) {
        for(uint8_t i = 0; i < len; i++)
                dest[i] = src[i];
}

uint8_t HIDUniversal::Poll() {
        uint8_t rcode = 0;

        if(!bPollEnable)
                return 0;

        if((long)(millis() - qNextPollTime) >= 0L) {
                qNextPollTime = millis() + pollInterval;

                uint8_t buf[constBuffLen];

                for(uint8_t i = 0; i < bNumIface; i++) {
                        uint8_t index = hidInterfaces[i].epIndex[epInterruptInIndex];
                        uint16_t read = (uint16_t)epInfo[index].maxPktSize;

                        ZeroMemory(constBuffLen, buf);

                        uint8_t rcode = pUsb->inTransfer(bAddress, epInfo[index].epAddr, &read, buf);

                        if(rcode) {
                                if(rcode != hrNAK)
                                        USBTRACE3("(hiduniversal.h) Poll:", rcode, 0x81);
                                return rcode;
                        }

                        if(read > constBuffLen)
                                read = constBuffLen;

                        bool identical = BuffersIdentical(read, buf, prevBuf);

                        SaveBuffer(read, buf, prevBuf);

                        if(identical)
                                return 0;
#if 0
                        Notify(PSTR("\r\nBuf: "), 0x80);

                        for(uint8_t i = 0; i < read; i++) {
                                D_PrintHex<uint8_t > (buf[i], 0x80);
                                Notify(PSTR(" "), 0x80);
                        }

                        Notify(PSTR("\r\n"), 0x80);
#endif
                        ParseHIDData(this, bHasReportId, (uint8_t)read, buf);

                        HIDReportParser *prs = GetReportParser(((bHasReportId) ? *buf : 0));

                        if(prs)
                                prs->Parse(this, bHasReportId, (uint8_t)read, buf);
                }
        }
        return rcode;
}

// Send a report to interrupt out endpoint. This is NOT SetReport() request!
uint8_t HIDUniversal::SndRpt(uint16_t nbytes, uint8_t *dataptr) {
        return pUsb->outTransfer(bAddress, epInfo[epInterruptOutIndex].epAddr, nbytes, dataptr);
}