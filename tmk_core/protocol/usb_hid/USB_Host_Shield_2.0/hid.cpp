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

#include "hid.h"

//get HID report descriptor

/* WRONG! Endpoint is _ALWAYS_ ZERO for HID! We want the _INTERFACE_ value here!
uint8_t HID::GetReportDescr(uint8_t ep, USBReadParser *parser) {
        const uint8_t constBufLen = 64;
        uint8_t buf[constBufLen];

        uint8_t rcode = pUsb->ctrlReq(bAddress, ep, bmREQ_HID_REPORT, USB_REQUEST_GET_DESCRIPTOR, 0x00,
                HID_DESCRIPTOR_REPORT, 0x0000, 128, constBufLen, buf, (USBReadParser*)parser);

        //return ((rcode != hrSTALL) ? rcode : 0);
        return rcode;
}
 */
uint8_t HID::GetReportDescr(uint16_t wIndex, USBReadParser *parser) {
        const uint8_t constBufLen = 64;
        uint8_t buf[constBufLen];

        uint8_t rcode = pUsb->ctrlReq(bAddress, 0x00, bmREQ_HID_REPORT, USB_REQUEST_GET_DESCRIPTOR, 0x00,
                HID_DESCRIPTOR_REPORT, wIndex, 128, constBufLen, buf, (USBReadParser*)parser);

        //return ((rcode != hrSTALL) ? rcode : 0);
        return rcode;
}

//uint8_t HID::getHidDescr( uint8_t ep, uint16_t nbytes, uint8_t* dataptr )
//{
//    return( pUsb->ctrlReq( bAddress, ep, bmREQ_GET_DESCR, USB_REQUEST_GET_DESCRIPTOR, 0x00, HID_DESCRIPTOR_HID, 0x0000, nbytes, dataptr ));
//}

uint8_t HID::SetReport(uint8_t ep, uint8_t iface, uint8_t report_type, uint8_t report_id, uint16_t nbytes, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, ep, bmREQ_HID_OUT, HID_REQUEST_SET_REPORT, report_id, report_type, iface, nbytes, nbytes, dataptr, NULL));
}

uint8_t HID::GetReport(uint8_t ep, uint8_t iface, uint8_t report_type, uint8_t report_id, uint16_t nbytes, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, ep, bmREQ_HID_IN, HID_REQUEST_GET_REPORT, report_id, report_type, iface, nbytes, nbytes, dataptr, NULL));
}

uint8_t HID::GetIdle(uint8_t iface, uint8_t reportID, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_HID_IN, HID_REQUEST_GET_IDLE, reportID, 0, iface, 0x0001, 0x0001, dataptr, NULL));
}

uint8_t HID::SetIdle(uint8_t iface, uint8_t reportID, uint8_t duration) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_HID_OUT, HID_REQUEST_SET_IDLE, reportID, duration, iface, 0x0000, 0x0000, NULL, NULL));
}

uint8_t HID::SetProtocol(uint8_t iface, uint8_t protocol) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_HID_OUT, HID_REQUEST_SET_PROTOCOL, protocol, 0x00, iface, 0x0000, 0x0000, NULL, NULL));
}

uint8_t HID::GetProtocol(uint8_t iface, uint8_t* dataptr) {
        return ( pUsb->ctrlReq(bAddress, 0, bmREQ_HID_IN, HID_REQUEST_GET_PROTOCOL, 0x00, 0x00, iface, 0x0001, 0x0001, dataptr, NULL));
}

void HID::PrintEndpointDescriptor(const USB_ENDPOINT_DESCRIPTOR* ep_ptr) {
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
}

void HID::PrintHidDescriptor(const USB_HID_DESCRIPTOR *pDesc) {
        Notify(PSTR("\r\n\r\nHID Descriptor:\r\n"), 0x80);
        Notify(PSTR("bDescLength:\t\t"), 0x80);
        D_PrintHex<uint8_t > (pDesc->bLength, 0x80);

        Notify(PSTR("\r\nbDescriptorType:\t"), 0x80);
        D_PrintHex<uint8_t > (pDesc->bDescriptorType, 0x80);

        Notify(PSTR("\r\nbcdHID:\t\t\t"), 0x80);
        D_PrintHex<uint16_t > (pDesc->bcdHID, 0x80);

        Notify(PSTR("\r\nbCountryCode:\t\t"), 0x80);
        D_PrintHex<uint8_t > (pDesc->bCountryCode, 0x80);

        Notify(PSTR("\r\nbNumDescriptors:\t"), 0x80);
        D_PrintHex<uint8_t > (pDesc->bNumDescriptors, 0x80);

        Notify(PSTR("\r\nbDescrType:\t\t"), 0x80);
        D_PrintHex<uint8_t > (pDesc->bDescrType, 0x80);

        Notify(PSTR("\r\nwDescriptorLength:\t"), 0x80);
        D_PrintHex<uint16_t > (pDesc->wDescriptorLength, 0x80);
}
