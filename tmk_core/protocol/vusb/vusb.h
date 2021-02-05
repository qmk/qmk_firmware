/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

#pragma once

#include "host_driver.h"

typedef struct usbDescriptorHeader {
    uchar bLength;
    uchar bDescriptorType;
} __attribute__((packed)) usbDescriptorHeader_t;

typedef struct usbDeviceDescriptor {
    usbDescriptorHeader_t header;
    unsigned              bcdUSB;
    uchar                 bDeviceClass;
    uchar                 bDeviceSubClass;
    uchar                 bDeviceProtocol;
    uchar                 bMaxPacketSize0;
    unsigned              idVendor;
    unsigned              idProduct;
    unsigned              bcdDevice;
    uchar                 iManufacturer;
    uchar                 iProduct;
    uchar                 iSerialNumber;
    uchar                 bNumConfigurations;
} __attribute__((packed)) usbDeviceDescriptor_t;

typedef struct usbConfigurationDescriptorHeader {
    usbDescriptorHeader_t header;
    unsigned              wTotalLength;
    uchar                 bNumInterfaces;
    uchar                 bConfigurationValue;
    uchar                 iConfiguration;
    uchar                 bmAttributes;
    uchar                 bMaxPower;
} __attribute__((packed)) usbConfigurationDescriptorHeader_t;

typedef struct usbStringDescriptor {
    usbDescriptorHeader_t header;
    int                   bString[];
} __attribute__((packed)) usbStringDescriptor_t;

typedef struct usbInterfaceDescriptor {
    usbDescriptorHeader_t header;
    uchar                 bInterfaceNumber;
    uchar                 bAlternateSetting;
    uchar                 bNumEndpoints;
    uchar                 bInterfaceClass;
    uchar                 bInterfaceSubClass;
    uchar                 bInterfaceProtocol;
    uchar                 iInterface;
} __attribute__((packed)) usbInterfaceDescriptor_t;

typedef struct usbEndpointDescriptor {
    usbDescriptorHeader_t header;
    uchar                 bEndpointAddress;
    uchar                 bmAttributes;
    unsigned              wMaxPacketSize;
    uchar                 bInterval;
} __attribute__((packed)) usbEndpointDescriptor_t;

typedef struct usbHIDDescriptor {
    usbDescriptorHeader_t header;
    unsigned              bcdHID;
    uchar                 bCountryCode;
    uchar                 bNumDescriptors;
    uchar                 bDescriptorType;
    unsigned              wDescriptorLength;
} __attribute__((packed)) usbHIDDescriptor_t;

typedef struct usbConfigurationDescriptor {
    usbConfigurationDescriptorHeader_t header;

#ifndef KEYBOARD_SHARED_EP
    usbInterfaceDescriptor_t keyboardInterface;
    usbHIDDescriptor_t       keyboardHID;
    usbEndpointDescriptor_t  keyboardINEndpoint;
#else
    usbInterfaceDescriptor_t sharedInterface;
    usbHIDDescriptor_t       sharedHID;
    usbEndpointDescriptor_t  sharedINEndpoint;
#endif

#if defined(RAW_ENABLE)
    usbInterfaceDescriptor_t rawInterface;
    usbHIDDescriptor_t       rawHID;
    usbEndpointDescriptor_t  rawINEndpoint;
    usbEndpointDescriptor_t  rawOUTEndpoint;
#endif

#if defined(SHARED_EP_ENABLE) && !defined(KEYBOARD_SHARED_EP)
    usbInterfaceDescriptor_t sharedInterface;
    usbHIDDescriptor_t       sharedHID;
    usbEndpointDescriptor_t  sharedINEndpoint;
#endif

#if defined(CONSOLE_ENABLE)
    usbInterfaceDescriptor_t consoleInterface;
    usbHIDDescriptor_t       consoleHID;
    usbEndpointDescriptor_t  consoleINEndpoint;
    usbEndpointDescriptor_t  consoleOUTEndpoint;
#endif
} __attribute__((packed)) usbConfigurationDescriptor_t;

#define USB_STRING_LEN(s) (sizeof(usbDescriptorHeader_t) + ((s) << 1))

host_driver_t *vusb_driver(void);
void           vusb_transfer_keyboard(void);
