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
#include "cdcftdi.h"

const uint8_t FTDI::epDataInIndex = 1;
const uint8_t FTDI::epDataOutIndex = 2;
const uint8_t FTDI::epInterruptInIndex = 3;

FTDI::FTDI(USB *p, FTDIAsyncOper *pasync) :
pAsync(pasync),
pUsb(p),
bAddress(0),
bNumEP(1),
wFTDIType(0) {
        for(uint8_t i = 0; i < FTDI_MAX_ENDPOINTS; i++) {
                epInfo[i].epAddr = 0;
                epInfo[i].maxPktSize = (i) ? 0 : 8;
                epInfo[i].epAttribs = 0;
                epInfo[i].bmNakPower = (i==epDataInIndex) ? USB_NAK_NOWAIT: USB_NAK_MAX_POWER;
        }
        if(pUsb)
                pUsb->RegisterDeviceClass(this);
}

uint8_t FTDI::Init(uint8_t parent, uint8_t port, bool lowspeed) {
        const uint8_t constBufSize = sizeof (USB_DEVICE_DESCRIPTOR);

        uint8_t buf[constBufSize];
        USB_DEVICE_DESCRIPTOR * udd = reinterpret_cast<USB_DEVICE_DESCRIPTOR*>(buf);
        uint8_t rcode;
        UsbDevice *p = NULL;
        EpInfo *oldep_ptr = NULL;

        uint8_t num_of_conf; // number of configurations

        AddressPool &addrPool = pUsb->GetAddressPool();

        USBTRACE("FTDI Init\r\n");

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
        rcode = pUsb->getDevDescr(0, 0, sizeof (USB_DEVICE_DESCRIPTOR), buf);

        // Restore p->epinfo
        p->epinfo = oldep_ptr;

        if(rcode)
                goto FailGetDevDescr;
        if(udd->idVendor != FTDI_VID || udd->idProduct != FTDI_PID)
                return USB_DEV_CONFIG_ERROR_DEVICE_NOT_SUPPORTED;

        // Save type of FTDI chip
        wFTDIType = udd->bcdDevice;

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
                HexDumper<USBReadParser, uint16_t, uint16_t> HexDump;
                ConfigDescParser < 0xFF, 0xFF, 0xFF, CP_MASK_COMPARE_ALL> confDescrParser(this);

                rcode = pUsb->getConfDescr(bAddress, 0, i, &HexDump);

                if(rcode)
                        goto FailGetConfDescr;

                rcode = pUsb->getConfDescr(bAddress, 0, i, &confDescrParser);

                if(rcode)
                        goto FailGetConfDescr;

                if(bNumEP > 1)
                        break;
        } // for

        if(bNumEP < 2)
                return USB_DEV_CONFIG_ERROR_DEVICE_NOT_SUPPORTED;

        USBTRACE2("NumEP:", bNumEP);

        // Assign epInfo to epinfo pointer
        rcode = pUsb->setEpInfoEntry(bAddress, bNumEP, epInfo);

        USBTRACE2("Conf:", bConfNum);

        // Set Configuration Value
        rcode = pUsb->setConf(bAddress, 0, bConfNum);

        if(rcode)
                goto FailSetConfDescr;

        rcode = pAsync->OnInit(this);

        if(rcode)
                goto FailOnInit;

        USBTRACE("FTDI configured\r\n");

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

FailOnInit:
#ifdef DEBUG_USB_HOST
        USBTRACE("OnInit:");

Fail:
        NotifyFail(rcode);
#endif
        Release();
        return rcode;
}

void FTDI::EndpointXtract(uint8_t conf, uint8_t iface, uint8_t alt, uint8_t proto, const USB_ENDPOINT_DESCRIPTOR *pep) {
        ErrorMessage<uint8_t > (PSTR("Conf.Val"), conf);
        ErrorMessage<uint8_t > (PSTR("Iface Num"), iface);
        ErrorMessage<uint8_t > (PSTR("Alt.Set"), alt);

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

uint8_t FTDI::Release() {
        pUsb->GetAddressPool().FreeAddress(bAddress);

        bAddress = 0;
        bNumEP = 1;
        qNextPollTime = 0;
        bPollEnable = false;
        return pAsync->OnRelease(this);
}

uint8_t FTDI::Poll() {
        uint8_t rcode = 0;

        //if (!bPollEnable)
        //      return 0;

        //if (qNextPollTime <= millis())
        //{
        //      USB_HOST_SERIAL.println(bAddress, HEX);

        //      qNextPollTime = millis() + 100;
        //}
        return rcode;
}

uint8_t FTDI::SetBaudRate(uint32_t baud) {
        uint16_t baud_value, baud_index = 0;
        uint32_t divisor3;

        divisor3 = 48000000 / 2 / baud; // divisor shifted 3 bits to the left

        if(wFTDIType == FT232AM) {
                if((divisor3 & 0x7) == 7)
                        divisor3++; // round x.7/8 up to x+1

                baud_value = divisor3 >> 3;
                divisor3 &= 0x7;

                if(divisor3 == 1) baud_value |= 0xc000;
                else // 0.125
                        if(divisor3 >= 4) baud_value |= 0x4000;
                else // 0.5
                        if(divisor3 != 0) baud_value |= 0x8000; // 0.25
                if(baud_value == 1) baud_value = 0; /* special case for maximum baud rate */
        } else {
                static const unsigned char divfrac [8] = {0, 3, 2, 0, 1, 1, 2, 3};
                static const unsigned char divindex[8] = {0, 0, 0, 1, 0, 1, 1, 1};

                baud_value = divisor3 >> 3;
                baud_value |= divfrac [divisor3 & 0x7] << 14;
                baud_index = divindex[divisor3 & 0x7];

                /* Deal with special cases for highest baud rates. */
                if(baud_value == 1) baud_value = 0;
                else // 1.0
                        if(baud_value == 0x4001) baud_value = 1; // 1.5
        }
        USBTRACE2("baud_value:", baud_value);
        USBTRACE2("baud_index:", baud_index);
        return pUsb->ctrlReq(bAddress, 0, bmREQ_FTDI_OUT, FTDI_SIO_SET_BAUD_RATE, baud_value & 0xff, baud_value >> 8, baud_index, 0, 0, NULL, NULL);
}

uint8_t FTDI::SetModemControl(uint16_t signal) {
        return pUsb->ctrlReq(bAddress, 0, bmREQ_FTDI_OUT, FTDI_SIO_MODEM_CTRL, signal & 0xff, signal >> 8, 0, 0, 0, NULL, NULL);
}

uint8_t FTDI::SetFlowControl(uint8_t protocol, uint8_t xon, uint8_t xoff) {
        return pUsb->ctrlReq(bAddress, 0, bmREQ_FTDI_OUT, FTDI_SIO_SET_FLOW_CTRL, xon, xoff, protocol << 8, 0, 0, NULL, NULL);
}

uint8_t FTDI::SetData(uint16_t databm) {
        return pUsb->ctrlReq(bAddress, 0, bmREQ_FTDI_OUT, FTDI_SIO_SET_DATA, databm & 0xff, databm >> 8, 0, 0, 0, NULL, NULL);
}

uint8_t FTDI::RcvData(uint16_t *bytes_rcvd, uint8_t *dataptr) {
        return pUsb->inTransfer(bAddress, epInfo[epDataInIndex].epAddr, bytes_rcvd, dataptr);
}

uint8_t FTDI::SndData(uint16_t nbytes, uint8_t *dataptr) {
        return pUsb->outTransfer(bAddress, epInfo[epDataOutIndex].epAddr, nbytes, dataptr);
}

void FTDI::PrintEndpointDescriptor(const USB_ENDPOINT_DESCRIPTOR* ep_ptr) {
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
