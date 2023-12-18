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
#include "cdcacm.h"

const uint8_t ACM::epDataInIndex = 1;
const uint8_t ACM::epDataOutIndex = 2;
const uint8_t ACM::epInterruptInIndex = 3;

ACM::ACM(USB *p, CDCAsyncOper *pasync) :
pUsb(p),
pAsync(pasync),
bAddress(0),
bControlIface(0),
bDataIface(0),
bNumEP(1),
qNextPollTime(0),
bPollEnable(false),
ready(false) {
        _enhanced_status = enhanced_features(); // Set up features
        for(uint8_t i = 0; i < ACM_MAX_ENDPOINTS; i++) {
                epInfo[i].epAddr = 0;
                epInfo[i].maxPktSize = (i) ? 0 : 8;
                epInfo[i].epAttribs = 0;
                epInfo[i].bmNakPower = (i == epDataInIndex) ? USB_NAK_NOWAIT : USB_NAK_MAX_POWER;

        }
        if(pUsb)
                pUsb->RegisterDeviceClass(this);
}

uint8_t ACM::Init(uint8_t parent, uint8_t port, bool lowspeed) {

        const uint8_t constBufSize = sizeof (USB_DEVICE_DESCRIPTOR);

        uint8_t buf[constBufSize];
        USB_DEVICE_DESCRIPTOR * udd = reinterpret_cast<USB_DEVICE_DESCRIPTOR*>(buf);

        uint8_t rcode;
        UsbDevice *p = NULL;
        EpInfo *oldep_ptr = NULL;
        uint8_t num_of_conf; // number of configurations

        AddressPool &addrPool = pUsb->GetAddressPool();

        USBTRACE("ACM Init\r\n");

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

        USBTRACE("ACM configured\r\n");

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

void ACM::EndpointXtract(uint8_t conf, uint8_t iface, uint8_t alt, uint8_t proto, const USB_ENDPOINT_DESCRIPTOR *pep) {
        //ErrorMessage<uint8_t > (PSTR("Conf.Val"), conf);
        //ErrorMessage<uint8_t > (PSTR("Iface Num"), iface);
        //ErrorMessage<uint8_t > (PSTR("Alt.Set"), alt);

        bConfNum = conf;

        uint8_t index;

        if((pep->bmAttributes & 0x03) == 3 && (pep->bEndpointAddress & 0x80) == 0x80)
                index = epInterruptInIndex;
        else
                if((pep->bmAttributes & 0x02) == 2)
                index = ((pep->bEndpointAddress & 0x80) == 0x80) ? epDataInIndex : epDataOutIndex;
        else
                return;

        // Fill in the endpoint info structure
        epInfo[index].epAddr = (pep->bEndpointAddress & 0x0F);
        epInfo[index].maxPktSize = (uint8_t)pep->wMaxPacketSize;
        epInfo[index].epAttribs = 0;

        bNumEP++;

        PrintEndpointDescriptor(pep);
}

uint8_t ACM::Release() {
        ready = false;
        pUsb->GetAddressPool().FreeAddress(bAddress);

        bControlIface = 0;
        bDataIface = 0;
        bNumEP = 1;

        bAddress = 0;
        qNextPollTime = 0;
        bPollEnable = false;
        return 0;
}

uint8_t ACM::Poll() {
        uint8_t rcode = 0;

        if(!bPollEnable)
                return 0;

        return rcode;
}

uint8_t ACM::RcvData(uint16_t *bytes_rcvd, uint8_t *dataptr) {
        return pUsb->inTransfer(bAddress, epInfo[epDataInIndex].epAddr, bytes_rcvd, dataptr);
}

uint8_t ACM::SndData(uint16_t nbytes, uint8_t *dataptr) {
        return pUsb->outTransfer(bAddress, epInfo[epDataOutIndex].epAddr, nbytes, dataptr);
}

uint8_t ACM::SetCommFeature(uint16_t fid, uint8_t nbytes, uint8_t *dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_CDCOUT, CDC_SET_COMM_FEATURE, (fid & 0xff), (fid >> 8), bControlIface, nbytes, nbytes, dataptr, NULL));
}

uint8_t ACM::GetCommFeature(uint16_t fid, uint8_t nbytes, uint8_t *dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_CDCIN, CDC_GET_COMM_FEATURE, (fid & 0xff), (fid >> 8), bControlIface, nbytes, nbytes, dataptr, NULL));
}

uint8_t ACM::ClearCommFeature(uint16_t fid) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_CDCOUT, CDC_CLEAR_COMM_FEATURE, (fid & 0xff), (fid >> 8), bControlIface, 0, 0, NULL, NULL));
}

uint8_t ACM::SetLineCoding(const LINE_CODING *dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_CDCOUT, CDC_SET_LINE_CODING, 0x00, 0x00, bControlIface, sizeof (LINE_CODING), sizeof (LINE_CODING), (uint8_t*)dataptr, NULL));
}

uint8_t ACM::GetLineCoding(LINE_CODING *dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_CDCIN, CDC_GET_LINE_CODING, 0x00, 0x00, bControlIface, sizeof (LINE_CODING), sizeof (LINE_CODING), (uint8_t*)dataptr, NULL));
}

uint8_t ACM::SetControlLineState(uint8_t state) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_CDCOUT, CDC_SET_CONTROL_LINE_STATE, state, 0, bControlIface, 0, 0, NULL, NULL));
}

uint8_t ACM::SendBreak(uint16_t duration) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_CDCOUT, CDC_SEND_BREAK, (duration & 0xff), (duration >> 8), bControlIface, 0, 0, NULL, NULL));
}

void ACM::PrintEndpointDescriptor(const USB_ENDPOINT_DESCRIPTOR* ep_ptr) {
        Notify(PSTR("Endpoint descriptor:"), 0x80);
        Notify(PSTR("\r\nLength:\t\t"), 0x80);
        D_PrintHex<uint8_t > (ep_ptr->bLength, 0x80);
        Notify(PSTR("\r\nType:\t\t"), 0x80);
        D_PrintHex<uint8_t > (ep_ptr->bDescriptorType, 0x80);
        Notify(PSTR("\r\nAddress:\t"), 0x80);
        D_PrintHex<uint8_t > (ep_ptr->bEndpointAddress, 0x80);
        Notify(PSTR("\r\nAttributes:\t"), 0x80);
        D_PrintHex<uint8_t > (ep_ptr->bmAttributes, 0x80);
        Notify(PSTR("\r\nMaxPktSize:\t"), 0x80);
        D_PrintHex<uint16_t > (ep_ptr->wMaxPacketSize, 0x80);
        Notify(PSTR("\r\nPoll Intrv:\t"), 0x80);
        D_PrintHex<uint8_t > (ep_ptr->bInterval, 0x80);
        Notify(PSTR("\r\n"), 0x80);
}
