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

#if !defined(_usb_h_) || defined(_ch9_h_)
#error "Never include usb_ch9.h directly; include Usb.h instead"
#else

/* USB chapter 9 structures */
#define _ch9_h_

/* Misc.USB constants */
#define DEV_DESCR_LEN   18      //device descriptor length
#define CONF_DESCR_LEN  9       //configuration descriptor length
#define INTR_DESCR_LEN  9       //interface descriptor length
#define EP_DESCR_LEN    7       //endpoint descriptor length

/* Standard Device Requests */

#define USB_REQUEST_GET_STATUS                  0       // Standard Device Request - GET STATUS
#define USB_REQUEST_CLEAR_FEATURE               1       // Standard Device Request - CLEAR FEATURE
#define USB_REQUEST_SET_FEATURE                 3       // Standard Device Request - SET FEATURE
#define USB_REQUEST_SET_ADDRESS                 5       // Standard Device Request - SET ADDRESS
#define USB_REQUEST_GET_DESCRIPTOR              6       // Standard Device Request - GET DESCRIPTOR
#define USB_REQUEST_SET_DESCRIPTOR              7       // Standard Device Request - SET DESCRIPTOR
#define USB_REQUEST_GET_CONFIGURATION           8       // Standard Device Request - GET CONFIGURATION
#define USB_REQUEST_SET_CONFIGURATION           9       // Standard Device Request - SET CONFIGURATION
#define USB_REQUEST_GET_INTERFACE               10      // Standard Device Request - GET INTERFACE
#define USB_REQUEST_SET_INTERFACE               11      // Standard Device Request - SET INTERFACE
#define USB_REQUEST_SYNCH_FRAME                 12      // Standard Device Request - SYNCH FRAME

#define USB_FEATURE_ENDPOINT_HALT               0       // CLEAR/SET FEATURE - Endpoint Halt
#define USB_FEATURE_DEVICE_REMOTE_WAKEUP        1       // CLEAR/SET FEATURE - Device remote wake-up
#define USB_FEATURE_TEST_MODE                   2       // CLEAR/SET FEATURE - Test mode

/* Setup Data Constants */

#define USB_SETUP_HOST_TO_DEVICE                0x00    // Device Request bmRequestType transfer direction - host to device transfer
#define USB_SETUP_DEVICE_TO_HOST                0x80    // Device Request bmRequestType transfer direction - device to host transfer
#define USB_SETUP_TYPE_STANDARD                 0x00    // Device Request bmRequestType type - standard
#define USB_SETUP_TYPE_CLASS                    0x20    // Device Request bmRequestType type - class
#define USB_SETUP_TYPE_VENDOR                   0x40    // Device Request bmRequestType type - vendor
#define USB_SETUP_RECIPIENT_DEVICE              0x00    // Device Request bmRequestType recipient - device
#define USB_SETUP_RECIPIENT_INTERFACE           0x01    // Device Request bmRequestType recipient - interface
#define USB_SETUP_RECIPIENT_ENDPOINT            0x02    // Device Request bmRequestType recipient - endpoint
#define USB_SETUP_RECIPIENT_OTHER               0x03    // Device Request bmRequestType recipient - other

/* USB descriptors  */

#define USB_DESCRIPTOR_DEVICE                   0x01    // bDescriptorType for a Device Descriptor.
#define USB_DESCRIPTOR_CONFIGURATION            0x02    // bDescriptorType for a Configuration Descriptor.
#define USB_DESCRIPTOR_STRING                   0x03    // bDescriptorType for a String Descriptor.
#define USB_DESCRIPTOR_INTERFACE                0x04    // bDescriptorType for an Interface Descriptor.
#define USB_DESCRIPTOR_ENDPOINT                 0x05    // bDescriptorType for an Endpoint Descriptor.
#define USB_DESCRIPTOR_DEVICE_QUALIFIER         0x06    // bDescriptorType for a Device Qualifier.
#define USB_DESCRIPTOR_OTHER_SPEED              0x07    // bDescriptorType for a Other Speed Configuration.
#define USB_DESCRIPTOR_INTERFACE_POWER          0x08    // bDescriptorType for Interface Power.
#define USB_DESCRIPTOR_OTG                      0x09    // bDescriptorType for an OTG Descriptor.

#define HID_DESCRIPTOR_HID                      0x21



/* OTG SET FEATURE Constants    */
#define OTG_FEATURE_B_HNP_ENABLE                3       // SET FEATURE OTG - Enable B device to perform HNP
#define OTG_FEATURE_A_HNP_SUPPORT               4       // SET FEATURE OTG - A device supports HNP
#define OTG_FEATURE_A_ALT_HNP_SUPPORT           5       // SET FEATURE OTG - Another port on the A device supports HNP

/* USB Endpoint Transfer Types  */
#define USB_TRANSFER_TYPE_CONTROL               0x00    // Endpoint is a control endpoint.
#define USB_TRANSFER_TYPE_ISOCHRONOUS           0x01    // Endpoint is an isochronous endpoint.
#define USB_TRANSFER_TYPE_BULK                  0x02    // Endpoint is a bulk endpoint.
#define USB_TRANSFER_TYPE_INTERRUPT             0x03    // Endpoint is an interrupt endpoint.
#define bmUSB_TRANSFER_TYPE                     0x03    // bit mask to separate transfer type from ISO attributes


/* Standard Feature Selectors for CLEAR_FEATURE Requests    */
#define USB_FEATURE_ENDPOINT_STALL              0       // Endpoint recipient
#define USB_FEATURE_DEVICE_REMOTE_WAKEUP        1       // Device recipient
#define USB_FEATURE_TEST_MODE                   2       // Device recipient

/* descriptor data structures */

/* Device descriptor structure */
typedef struct {
        uint8_t bLength; // Length of this descriptor.
        uint8_t bDescriptorType; // DEVICE descriptor type (USB_DESCRIPTOR_DEVICE).
        uint16_t bcdUSB; // USB Spec Release Number (BCD).
        uint8_t bDeviceClass; // Class code (assigned by the USB-IF). 0xFF-Vendor specific.
        uint8_t bDeviceSubClass; // Subclass code (assigned by the USB-IF).
        uint8_t bDeviceProtocol; // Protocol code (assigned by the USB-IF). 0xFF-Vendor specific.
        uint8_t bMaxPacketSize0; // Maximum packet size for endpoint 0.
        uint16_t idVendor; // Vendor ID (assigned by the USB-IF).
        uint16_t idProduct; // Product ID (assigned by the manufacturer).
        uint16_t bcdDevice; // Device release number (BCD).
        uint8_t iManufacturer; // Index of String Descriptor describing the manufacturer.
        uint8_t iProduct; // Index of String Descriptor describing the product.
        uint8_t iSerialNumber; // Index of String Descriptor with the device's serial number.
        uint8_t bNumConfigurations; // Number of possible configurations.
} __attribute__((packed)) USB_DEVICE_DESCRIPTOR;

/* Configuration descriptor structure */
typedef struct {
        uint8_t bLength; // Length of this descriptor.
        uint8_t bDescriptorType; // CONFIGURATION descriptor type (USB_DESCRIPTOR_CONFIGURATION).
        uint16_t wTotalLength; // Total length of all descriptors for this configuration.
        uint8_t bNumInterfaces; // Number of interfaces in this configuration.
        uint8_t bConfigurationValue; // Value of this configuration (1 based).
        uint8_t iConfiguration; // Index of String Descriptor describing the configuration.
        uint8_t bmAttributes; // Configuration characteristics.
        uint8_t bMaxPower; // Maximum power consumed by this configuration.
} __attribute__((packed)) USB_CONFIGURATION_DESCRIPTOR;

/* Interface descriptor structure */
typedef struct {
        uint8_t bLength; // Length of this descriptor.
        uint8_t bDescriptorType; // INTERFACE descriptor type (USB_DESCRIPTOR_INTERFACE).
        uint8_t bInterfaceNumber; // Number of this interface (0 based).
        uint8_t bAlternateSetting; // Value of this alternate interface setting.
        uint8_t bNumEndpoints; // Number of endpoints in this interface.
        uint8_t bInterfaceClass; // Class code (assigned by the USB-IF).  0xFF-Vendor specific.
        uint8_t bInterfaceSubClass; // Subclass code (assigned by the USB-IF).
        uint8_t bInterfaceProtocol; // Protocol code (assigned by the USB-IF).  0xFF-Vendor specific.
        uint8_t iInterface; // Index of String Descriptor describing the interface.
} __attribute__((packed)) USB_INTERFACE_DESCRIPTOR;

/* Endpoint descriptor structure */
typedef struct {
        uint8_t bLength; // Length of this descriptor.
        uint8_t bDescriptorType; // ENDPOINT descriptor type (USB_DESCRIPTOR_ENDPOINT).
        uint8_t bEndpointAddress; // Endpoint address. Bit 7 indicates direction (0=OUT, 1=IN).
        uint8_t bmAttributes; // Endpoint transfer type.
        uint16_t wMaxPacketSize; // Maximum packet size.
        uint8_t bInterval; // Polling interval in frames.
} __attribute__((packed)) USB_ENDPOINT_DESCRIPTOR;

/* HID descriptor */
typedef struct {
        uint8_t bLength;
        uint8_t bDescriptorType;
        uint16_t bcdHID; // HID class specification release
        uint8_t bCountryCode;
        uint8_t bNumDescriptors; // Number of additional class specific descriptors
        uint8_t bDescrType; // Type of class descriptor
        uint16_t wDescriptorLength; // Total size of the Report descriptor
} __attribute__((packed)) USB_HID_DESCRIPTOR;

typedef struct {
        uint8_t bDescrType; // Type of class descriptor
        uint16_t wDescriptorLength; // Total size of the Report descriptor
} __attribute__((packed)) HID_CLASS_DESCRIPTOR_LEN_AND_TYPE;

#endif // _ch9_h_
