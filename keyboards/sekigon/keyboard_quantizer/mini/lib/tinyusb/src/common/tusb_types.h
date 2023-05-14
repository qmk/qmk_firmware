/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * This file is part of the TinyUSB stack.
 */

/** \ingroup group_usb_definitions
 *  \defgroup USBDef_Type USB Types
 *  @{ */

#ifndef _TUSB_TYPES_H_
#define _TUSB_TYPES_H_

#include <stdbool.h>
#include <stdint.h>
#include "tusb_compiler.h"

#ifdef __cplusplus
 extern "C" {
#endif

/*------------------------------------------------------------------*/
/* CONSTANTS
 *------------------------------------------------------------------*/

/// defined base on EHCI specs value for Endpoint Speed
typedef enum
{
  TUSB_SPEED_FULL = 0,
  TUSB_SPEED_LOW  = 1,
  TUSB_SPEED_HIGH = 2,
  TUSB_SPEED_INVALID = 0xff,
}tusb_speed_t;

/// defined base on USB Specs Endpoint's bmAttributes
typedef enum
{
  TUSB_XFER_CONTROL = 0 ,
  TUSB_XFER_ISOCHRONOUS ,
  TUSB_XFER_BULK        ,
  TUSB_XFER_INTERRUPT
}tusb_xfer_type_t;

typedef enum
{
  TUSB_DIR_OUT = 0,
  TUSB_DIR_IN  = 1,

  TUSB_DIR_IN_MASK = 0x80
}tusb_dir_t;

enum
{
  TUSB_EPSIZE_BULK_FS = 64,
  TUSB_EPSIZE_BULK_HS= 512,

  TUSB_EPSIZE_ISO_FS_MAX = 1023,
  TUSB_EPSIZE_ISO_HS_MAX = 1024,
};

/// Isochronous End Point Attributes
typedef enum
{
  TUSB_ISO_EP_ATT_NO_SYNC         = 0x00,
  TUSB_ISO_EP_ATT_ASYNCHRONOUS    = 0x04,
  TUSB_ISO_EP_ATT_ADAPTIVE        = 0x08,
  TUSB_ISO_EP_ATT_SYNCHRONOUS     = 0x0C,
  TUSB_ISO_EP_ATT_DATA            = 0x00, ///< Data End Point
  TUSB_ISO_EP_ATT_EXPLICIT_FB     = 0x10, ///< Feedback End Point
  TUSB_ISO_EP_ATT_IMPLICIT_FB     = 0x20, ///< Data endpoint that also serves as an implicit feedback
}tusb_iso_ep_attribute_t;

/// USB Descriptor Types
typedef enum
{
  TUSB_DESC_DEVICE                = 0x01,
  TUSB_DESC_CONFIGURATION         = 0x02,
  TUSB_DESC_STRING                = 0x03,
  TUSB_DESC_INTERFACE             = 0x04,
  TUSB_DESC_ENDPOINT              = 0x05,
  TUSB_DESC_DEVICE_QUALIFIER      = 0x06,
  TUSB_DESC_OTHER_SPEED_CONFIG    = 0x07,
  TUSB_DESC_INTERFACE_POWER       = 0x08,
  TUSB_DESC_OTG                   = 0x09,
  TUSB_DESC_DEBUG                 = 0x0A,
  TUSB_DESC_INTERFACE_ASSOCIATION = 0x0B,

  TUSB_DESC_BOS                   = 0x0F,
  TUSB_DESC_DEVICE_CAPABILITY     = 0x10,

  TUSB_DESC_FUNCTIONAL            = 0x21,

  // Class Specific Descriptor
  TUSB_DESC_CS_DEVICE             = 0x21,
  TUSB_DESC_CS_CONFIGURATION      = 0x22,
  TUSB_DESC_CS_STRING             = 0x23,
  TUSB_DESC_CS_INTERFACE          = 0x24,
  TUSB_DESC_CS_ENDPOINT           = 0x25,

  TUSB_DESC_SUPERSPEED_ENDPOINT_COMPANION     = 0x30,
  TUSB_DESC_SUPERSPEED_ISO_ENDPOINT_COMPANION = 0x31
}tusb_desc_type_t;

typedef enum
{
  TUSB_REQ_GET_STATUS        = 0  ,
  TUSB_REQ_CLEAR_FEATURE     = 1  ,
  TUSB_REQ_RESERVED          = 2  ,
  TUSB_REQ_SET_FEATURE       = 3  ,
  TUSB_REQ_RESERVED2         = 4  ,
  TUSB_REQ_SET_ADDRESS       = 5  ,
  TUSB_REQ_GET_DESCRIPTOR    = 6  ,
  TUSB_REQ_SET_DESCRIPTOR    = 7  ,
  TUSB_REQ_GET_CONFIGURATION = 8  ,
  TUSB_REQ_SET_CONFIGURATION = 9  ,
  TUSB_REQ_GET_INTERFACE     = 10 ,
  TUSB_REQ_SET_INTERFACE     = 11 ,
  TUSB_REQ_SYNCH_FRAME       = 12
}tusb_request_code_t;

typedef enum
{
  TUSB_REQ_FEATURE_EDPT_HALT     = 0,
  TUSB_REQ_FEATURE_REMOTE_WAKEUP = 1,
  TUSB_REQ_FEATURE_TEST_MODE     = 2
}tusb_request_feature_selector_t;

typedef enum
{
  TUSB_REQ_TYPE_STANDARD = 0,
  TUSB_REQ_TYPE_CLASS,
  TUSB_REQ_TYPE_VENDOR,
  TUSB_REQ_TYPE_INVALID
} tusb_request_type_t;

typedef enum
{
  TUSB_REQ_RCPT_DEVICE =0,
  TUSB_REQ_RCPT_INTERFACE,
  TUSB_REQ_RCPT_ENDPOINT,
  TUSB_REQ_RCPT_OTHER
} tusb_request_recipient_t;

// https://www.usb.org/defined-class-codes
typedef enum
{
  TUSB_CLASS_UNSPECIFIED          = 0    ,
  TUSB_CLASS_AUDIO                = 1    ,
  TUSB_CLASS_CDC                  = 2    ,
  TUSB_CLASS_HID                  = 3    ,
  TUSB_CLASS_RESERVED_4           = 4    ,
  TUSB_CLASS_PHYSICAL             = 5    ,
  TUSB_CLASS_IMAGE                = 6    ,
  TUSB_CLASS_PRINTER              = 7    ,
  TUSB_CLASS_MSC                  = 8    ,
  TUSB_CLASS_HUB                  = 9    ,
  TUSB_CLASS_CDC_DATA             = 10   ,
  TUSB_CLASS_SMART_CARD           = 11   ,
  TUSB_CLASS_RESERVED_12          = 12   ,
  TUSB_CLASS_CONTENT_SECURITY     = 13   ,
  TUSB_CLASS_VIDEO                = 14   ,
  TUSB_CLASS_PERSONAL_HEALTHCARE  = 15   ,
  TUSB_CLASS_AUDIO_VIDEO          = 16   ,

  TUSB_CLASS_DIAGNOSTIC           = 0xDC ,
  TUSB_CLASS_WIRELESS_CONTROLLER  = 0xE0 ,
  TUSB_CLASS_MISC                 = 0xEF ,
  TUSB_CLASS_APPLICATION_SPECIFIC = 0xFE ,
  TUSB_CLASS_VENDOR_SPECIFIC      = 0xFF
}tusb_class_code_t;

typedef enum
{
  MISC_SUBCLASS_COMMON = 2
}misc_subclass_type_t;

typedef enum
{
  MISC_PROTOCOL_IAD = 1
}misc_protocol_type_t;

typedef enum
{
  APP_SUBCLASS_USBTMC = 0x03,
  APP_SUBCLASS_DFU_RUNTIME = 0x01
} app_subclass_type_t;

typedef enum
{
  DEVICE_CAPABILITY_WIRELESS_USB               = 0x01,
  DEVICE_CAPABILITY_USB20_EXTENSION            = 0x02,
  DEVICE_CAPABILITY_SUPERSPEED_USB             = 0x03,
  DEVICE_CAPABILITY_CONTAINER_id               = 0x04,
  DEVICE_CAPABILITY_PLATFORM                   = 0x05,
  DEVICE_CAPABILITY_POWER_DELIVERY             = 0x06,
  DEVICE_CAPABILITY_BATTERY_INFO               = 0x07,
  DEVICE_CAPABILITY_PD_CONSUMER_PORT           = 0x08,
  DEVICE_CAPABILITY_PD_PROVIDER_PORT           = 0x09,
  DEVICE_CAPABILITY_SUPERSPEED_PLUS            = 0x0A,
  DEVICE_CAPABILITY_PRECESION_TIME_MEASUREMENT = 0x0B,
  DEVICE_CAPABILITY_WIRELESS_USB_EXT           = 0x0C,
  DEVICE_CAPABILITY_BILLBOARD                  = 0x0D,
  DEVICE_CAPABILITY_AUTHENTICATION             = 0x0E,
  DEVICE_CAPABILITY_BILLBOARD_EX               = 0x0F,
  DEVICE_CAPABILITY_CONFIGURATION_SUMMARY      = 0x10
}device_capability_type_t;

enum {
  TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP = TU_BIT(5),
  TUSB_DESC_CONFIG_ATT_SELF_POWERED  = TU_BIT(6),
};

#define TUSB_DESC_CONFIG_POWER_MA(x)  ((x)/2)

typedef enum
{
  XFER_RESULT_SUCCESS = 0,
  XFER_RESULT_FAILED,
  XFER_RESULT_STALLED,
  XFER_RESULT_TIMEOUT,
  XFER_RESULT_INVALID
}xfer_result_t;

enum // TODO remove
{
  DESC_OFFSET_LEN  = 0,
  DESC_OFFSET_TYPE = 1
};

enum
{
  INTERFACE_INVALID_NUMBER = 0xff
};

typedef enum
{
  MS_OS_20_SET_HEADER_DESCRIPTOR       = 0x00,
  MS_OS_20_SUBSET_HEADER_CONFIGURATION = 0x01,
  MS_OS_20_SUBSET_HEADER_FUNCTION      = 0x02,
  MS_OS_20_FEATURE_COMPATBLE_ID        = 0x03,
  MS_OS_20_FEATURE_REG_PROPERTY        = 0x04,
  MS_OS_20_FEATURE_MIN_RESUME_TIME     = 0x05,
  MS_OS_20_FEATURE_MODEL_ID            = 0x06,
  MS_OS_20_FEATURE_CCGP_DEVICE         = 0x07,
  MS_OS_20_FEATURE_VENDOR_REVISION     = 0x08
} microsoft_os_20_type_t;

enum
{
  CONTROL_STAGE_IDLE,
  CONTROL_STAGE_SETUP,
  CONTROL_STAGE_DATA,
  CONTROL_STAGE_ACK
};

enum
{
  TUSB_INDEX_INVALID = 0xff
};

//--------------------------------------------------------------------+
// USB Descriptors
//--------------------------------------------------------------------+

// Start of all packed definitions for compiler without per-type packed
TU_ATTR_PACKED_BEGIN
TU_ATTR_BIT_FIELD_ORDER_BEGIN

/// USB Device Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength            ; ///< Size of this descriptor in bytes.
  uint8_t  bDescriptorType    ; ///< DEVICE Descriptor Type.
  uint16_t bcdUSB             ; ///< BUSB Specification Release Number in Binary-Coded Decimal (i.e., 2.10 is 210H). This field identifies the release of the USB Specification with which the device and its descriptors are compliant.

  uint8_t  bDeviceClass       ; ///< Class code (assigned by the USB-IF). \li If this field is reset to zero, each interface within a configuration specifies its own class information and the various interfaces operate independently. \li If this field is set to a value between 1 and FEH, the device supports different class specifications on different interfaces and the interfaces may not operate independently. This value identifies the class definition used for the aggregate interfaces. \li If this field is set to FFH, the device class is vendor-specific.
  uint8_t  bDeviceSubClass    ; ///< Subclass code (assigned by the USB-IF). These codes are qualified by the value of the bDeviceClass field. \li If the bDeviceClass field is reset to zero, this field must also be reset to zero. \li If the bDeviceClass field is not set to FFH, all values are reserved for assignment by the USB-IF.
  uint8_t  bDeviceProtocol    ; ///< Protocol code (assigned by the USB-IF). These codes are qualified by the value of the bDeviceClass and the bDeviceSubClass fields. If a device supports class-specific protocols on a device basis as opposed to an interface basis, this code identifies the protocols that the device uses as defined by the specification of the device class. \li If this field is reset to zero, the device does not use class-specific protocols on a device basis. However, it may use classspecific protocols on an interface basis. \li If this field is set to FFH, the device uses a vendor-specific protocol on a device basis.
  uint8_t  bMaxPacketSize0    ; ///< Maximum packet size for endpoint zero (only 8, 16, 32, or 64 are valid). For HS devices is fixed to 64.

  uint16_t idVendor           ; ///< Vendor ID (assigned by the USB-IF).
  uint16_t idProduct          ; ///< Product ID (assigned by the manufacturer).
  uint16_t bcdDevice          ; ///< Device release number in binary-coded decimal.
  uint8_t  iManufacturer      ; ///< Index of string descriptor describing manufacturer.
  uint8_t  iProduct           ; ///< Index of string descriptor describing product.
  uint8_t  iSerialNumber      ; ///< Index of string descriptor describing the device's serial number.

  uint8_t  bNumConfigurations ; ///< Number of possible configurations.
} tusb_desc_device_t;

TU_VERIFY_STATIC( sizeof(tusb_desc_device_t) == 18, "size is not correct");

// USB Binary Device Object Store (BOS) Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength         ; ///< Size of this descriptor in bytes
  uint8_t  bDescriptorType ; ///< CONFIGURATION Descriptor Type
  uint16_t wTotalLength    ; ///< Total length of data returned for this descriptor
  uint8_t  bNumDeviceCaps  ; ///< Number of device capability descriptors in the BOS
} tusb_desc_bos_t;

TU_VERIFY_STATIC( sizeof(tusb_desc_bos_t) == 5, "size is not correct");

/// USB Configuration Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength             ; ///< Size of this descriptor in bytes
  uint8_t  bDescriptorType     ; ///< CONFIGURATION Descriptor Type
  uint16_t wTotalLength        ; ///< Total length of data returned for this configuration. Includes the combined length of all descriptors (configuration, interface, endpoint, and class- or vendor-specific) returned for this configuration.

  uint8_t  bNumInterfaces      ; ///< Number of interfaces supported by this configuration
  uint8_t  bConfigurationValue ; ///< Value to use as an argument to the SetConfiguration() request to select this configuration.
  uint8_t  iConfiguration      ; ///< Index of string descriptor describing this configuration
  uint8_t  bmAttributes        ; ///< Configuration characteristics \n D7: Reserved (set to one)\n D6: Self-powered \n D5: Remote Wakeup \n D4...0: Reserved (reset to zero) \n D7 is reserved and must be set to one for historical reasons. \n A device configuration that uses power from the bus and a local source reports a non-zero value in bMaxPower to indicate the amount of bus power required and sets D6. The actual power source at runtime may be determined using the GetStatus(DEVICE) request (see USB 2.0 spec Section 9.4.5). \n If a device configuration supports remote wakeup, D5 is set to one.
  uint8_t  bMaxPower           ; ///< Maximum power consumption of the USB device from the bus in this specific configuration when the device is fully operational. Expressed in 2 mA units (i.e., 50 = 100 mA).
} tusb_desc_configuration_t;

TU_VERIFY_STATIC( sizeof(tusb_desc_configuration_t) == 9, "size is not correct");

/// USB Interface Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength            ; ///< Size of this descriptor in bytes
  uint8_t  bDescriptorType    ; ///< INTERFACE Descriptor Type

  uint8_t  bInterfaceNumber   ; ///< Number of this interface. Zero-based value identifying the index in the array of concurrent interfaces supported by this configuration.
  uint8_t  bAlternateSetting  ; ///< Value used to select this alternate setting for the interface identified in the prior field
  uint8_t  bNumEndpoints      ; ///< Number of endpoints used by this interface (excluding endpoint zero). If this value is zero, this interface only uses the Default Control Pipe.
  uint8_t  bInterfaceClass    ; ///< Class code (assigned by the USB-IF). \li A value of zero is reserved for future standardization. \li If this field is set to FFH, the interface class is vendor-specific. \li All other values are reserved for assignment by the USB-IF.
  uint8_t  bInterfaceSubClass ; ///< Subclass code (assigned by the USB-IF). \n These codes are qualified by the value of the bInterfaceClass field. \li If the bInterfaceClass field is reset to zero, this field must also be reset to zero. \li If the bInterfaceClass field is not set to FFH, all values are reserved for assignment by the USB-IF.
  uint8_t  bInterfaceProtocol ; ///< Protocol code (assigned by the USB). \n These codes are qualified by the value of the bInterfaceClass and the bInterfaceSubClass fields. If an interface supports class-specific requests, this code identifies the protocols that the device uses as defined by the specification of the device class. \li If this field is reset to zero, the device does not use a class-specific protocol on this interface. \li If this field is set to FFH, the device uses a vendor-specific protocol for this interface.
  uint8_t  iInterface         ; ///< Index of string descriptor describing this interface
} tusb_desc_interface_t;

TU_VERIFY_STATIC( sizeof(tusb_desc_interface_t) == 9, "size is not correct");

/// USB Endpoint Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength          ; // Size of this descriptor in bytes
  uint8_t  bDescriptorType  ; // ENDPOINT Descriptor Type

  uint8_t  bEndpointAddress ; // The address of the endpoint

  struct TU_ATTR_PACKED {
    uint8_t xfer  : 2;        // Control, ISO, Bulk, Interrupt
    uint8_t sync  : 2;        // None, Asynchronous, Adaptive, Synchronous
    uint8_t usage : 2;        // Data, Feedback, Implicit feedback
    uint8_t       : 2;
  } bmAttributes;

  uint16_t wMaxPacketSize   ; // Bit 10..0 : max packet size, bit 12..11 additional transaction per highspeed micro-frame
  uint8_t  bInterval        ; // Polling interval, in frames or microframes depending on the operating speed
} tusb_desc_endpoint_t;

TU_VERIFY_STATIC( sizeof(tusb_desc_endpoint_t) == 7, "size is not correct");

/// USB Other Speed Configuration Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength             ; ///< Size of descriptor
  uint8_t  bDescriptorType     ; ///< Other_speed_Configuration Type
  uint16_t wTotalLength        ; ///< Total length of data returned

  uint8_t  bNumInterfaces      ; ///< Number of interfaces supported by this speed configuration
  uint8_t  bConfigurationValue ; ///< Value to use to select configuration
  uint8_t  iConfiguration      ; ///< Index of string descriptor
  uint8_t  bmAttributes        ; ///< Same as Configuration descriptor
  uint8_t  bMaxPower           ; ///< Same as Configuration descriptor
} tusb_desc_other_speed_t;

/// USB Device Qualifier Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength            ; ///< Size of descriptor
  uint8_t  bDescriptorType    ; ///< Device Qualifier Type
  uint16_t bcdUSB             ; ///< USB specification version number (e.g., 0200H for V2.00)

  uint8_t  bDeviceClass       ; ///< Class Code
  uint8_t  bDeviceSubClass    ; ///< SubClass Code
  uint8_t  bDeviceProtocol    ; ///< Protocol Code

  uint8_t  bMaxPacketSize0    ; ///< Maximum packet size for other speed
  uint8_t  bNumConfigurations ; ///< Number of Other-speed Configurations
  uint8_t  bReserved          ; ///< Reserved for future use, must be zero
} tusb_desc_device_qualifier_t;

TU_VERIFY_STATIC( sizeof(tusb_desc_device_qualifier_t) == 10, "size is not correct");

/// USB Interface Association Descriptor (IAD ECN)
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength           ; ///< Size of descriptor
  uint8_t bDescriptorType   ; ///< Other_speed_Configuration Type

  uint8_t bFirstInterface   ; ///< Index of the first associated interface.
  uint8_t bInterfaceCount   ; ///< Total number of associated interfaces.

  uint8_t bFunctionClass    ; ///< Interface class ID.
  uint8_t bFunctionSubClass ; ///< Interface subclass ID.
  uint8_t bFunctionProtocol ; ///< Interface protocol ID.

  uint8_t iFunction         ; ///< Index of the string descriptor describing the interface association.
} tusb_desc_interface_assoc_t;

// USB String Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength         ; ///< Size of this descriptor in bytes
  uint8_t  bDescriptorType ; ///< Descriptor Type
  uint16_t unicode_string[];
} tusb_desc_string_t;

// USB Binary Device Object Store (BOS)
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength;
  uint8_t bDescriptorType ;
  uint8_t bDevCapabilityType;
  uint8_t bReserved;
  uint8_t PlatformCapabilityUUID[16];
  uint8_t CapabilityData[];
} tusb_desc_bos_platform_t;

// USB WebuSB URL Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t bLength;
  uint8_t bDescriptorType;
  uint8_t bScheme;
  char    url[];
} tusb_desc_webusb_url_t;

// DFU Functional Descriptor
typedef struct TU_ATTR_PACKED
{
  uint8_t  bLength;
  uint8_t  bDescriptorType;

  union {
    struct TU_ATTR_PACKED {
      uint8_t bitCanDnload             : 1;
      uint8_t bitCanUpload             : 1;
      uint8_t bitManifestationTolerant : 1;
      uint8_t bitWillDetach            : 1;
      uint8_t reserved                 : 4;
    } bmAttributes;

    uint8_t bAttributes;
  };

  uint16_t wDetachTimeOut;
  uint16_t wTransferSize;
  uint16_t bcdDFUVersion;
} tusb_desc_dfu_functional_t;

/*------------------------------------------------------------------*/
/* Types
 *------------------------------------------------------------------*/
typedef struct TU_ATTR_PACKED{
  union {
    struct TU_ATTR_PACKED {
      uint8_t recipient :  5; ///< Recipient type tusb_request_recipient_t.
      uint8_t type      :  2; ///< Request type tusb_request_type_t.
      uint8_t direction :  1; ///< Direction type. tusb_dir_t
    } bmRequestType_bit;

    uint8_t bmRequestType;
  };

  uint8_t  bRequest;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
} tusb_control_request_t;

TU_VERIFY_STATIC( sizeof(tusb_control_request_t) == 8, "size is not correct");


TU_ATTR_PACKED_END  // End of all packed definitions
TU_ATTR_BIT_FIELD_ORDER_END

//--------------------------------------------------------------------+
// Endpoint helper
//--------------------------------------------------------------------+

// Get direction from Endpoint address
TU_ATTR_ALWAYS_INLINE static inline tusb_dir_t tu_edpt_dir(uint8_t addr)
{
  return (addr & TUSB_DIR_IN_MASK) ? TUSB_DIR_IN : TUSB_DIR_OUT;
}

// Get Endpoint number from address
TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_edpt_number(uint8_t addr)
{
  return (uint8_t)(addr & (~TUSB_DIR_IN_MASK));
}

TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_edpt_addr(uint8_t num, uint8_t dir)
{
  return (uint8_t)(num | (dir ? TUSB_DIR_IN_MASK : 0));
}

TU_ATTR_ALWAYS_INLINE static inline uint16_t tu_edpt_packet_size(tusb_desc_endpoint_t const* desc_ep)
{
  return tu_le16toh(desc_ep->wMaxPacketSize) & TU_GENMASK(10, 0);
}

#if CFG_TUSB_DEBUG
TU_ATTR_ALWAYS_INLINE static inline const char *tu_edpt_dir_str(tusb_dir_t dir)
{
  tu_static const char *str[] = {"out", "in"};
  return str[dir];
}

TU_ATTR_ALWAYS_INLINE static inline const char *tu_edpt_type_str(tusb_xfer_type_t t)
{
  tu_static const char *str[] = {"control", "isochronous", "bulk", "interrupt"};
  return str[t];
}
#endif

//--------------------------------------------------------------------+
// Descriptor helper
//--------------------------------------------------------------------+

// return next descriptor
TU_ATTR_ALWAYS_INLINE static inline uint8_t const * tu_desc_next(void const* desc)
{
  uint8_t const* desc8 = (uint8_t const*) desc;
  return desc8 + desc8[DESC_OFFSET_LEN];
}

// get descriptor type
TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_desc_type(void const* desc)
{
  return ((uint8_t const*) desc)[DESC_OFFSET_TYPE];
}

// get descriptor length
TU_ATTR_ALWAYS_INLINE static inline uint8_t tu_desc_len(void const* desc)
{
  return ((uint8_t const*) desc)[DESC_OFFSET_LEN];
}

// find descriptor that match byte1 (type)
uint8_t const * tu_desc_find(uint8_t const* desc, uint8_t const* end, uint8_t byte1);

// find descriptor that match byte1 (type) and byte2
uint8_t const * tu_desc_find2(uint8_t const* desc, uint8_t const* end, uint8_t byte1, uint8_t byte2);

// find descriptor that match byte1 (type) and byte2
uint8_t const * tu_desc_find3(uint8_t const* desc, uint8_t const* end, uint8_t byte1, uint8_t byte2, uint8_t byte3);

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_TYPES_H_ */

/** @} */
